#include "Manager/DownloadImageManager.h"
#include "Manager/NetworkManager.h"
#include "Configs.h"
#include "Constant/JSONFieldConstant.h"
#include "Constant/Defination.h"
#include "Constant/LobbyConstant.h"
#include "Constant/ResultCodeConstant.h"
#include "Helper/Helper4String.h"
#include "Util/UtilFunction.h"
#include "Manager/PluginManager.h"
using namespace std;
USING_NS_CC;
#pragma region init singleton
DownloadImageManager* DownloadImageManager::s_instance = nullptr;

DownloadImageManager* DownloadImageManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new DownloadImageManager();
	}
	return s_instance;
}
#pragma endregion


void DownloadImageManager::onHttpRequestLoadImageCompleted(
	cocos2d::network::HttpClient* sender,
	cocos2d::network::HttpResponse* response
)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("onHttpRequestLoadImageCompleted");
	}
	this->downloadImageQueue.erase(this->downloadImageQueue.begin());
	this->checkAndDownload();
	if (!response)
	{
		if (Configs::printConsoleLog)
		{
			CCLOG("onHttpRequestLoadImageCompleted response null");
		}
		return;
	}
	if (Configs::printConsoleLog)
	{
		CCLOG("onHttpRequestCompleted - Response code: %lu", response->getResponseCode());
	}

	std::string url = response->getHttpRequest()->getUrl();
	auto callbackList = this->downloadingImageWithCallback[url];
	auto callbackWhenError = [this, callbackList, url]()
	{
		if (Configs::printConsoleLog)
		{
			CCLOG("onHttpRequestCompleted - callbackWhenError");
		}
		for (auto callback : callbackList)
		{
			if (callback)
			{
				callback(nullptr);
			}
		}
		this->downloadingImageWithCallback[url].clear();
		return;
	};
	if (!response->isSucceed()
		|| (response->getResponseCode() != 200
		&& response->getResponseCode() != 302))
	{
		log("onHttpRequestCompleted - Response failed");
		log("onHttpRequestCompleted - Error buffer: %s", response->getErrorBuffer());
		callbackWhenError();
		return;
	}
	if (Configs::printConsoleLog)
	{
		CCLOG("onHttpRequestCompleted - Response data string: %s", response->getResponseDataString());
	}

	//if (Helper4String::isStringContain(url, "graph"))
	if (response->getResponseCode() == 302)
	{
		NetworkManager::getInstance()->getRedirectFBPicture(
			url,
			[this, callbackList, url](std::string urlRedirect)
		{
			this->loadImageFromCacheOrDownload(urlRedirect, [urlRedirect, this, url](cocos2d::Texture2D* texture)
			{
				for (auto callback : this->downloadingImageWithCallback[url])
				{
					if (callback)
					{
						callback(texture);
					}
				}
				this->downloadingImageWithCallback[url].clear();
				this->redirectMap[url] = urlRedirect;
			});
		}
		);
		return;
	}
	if (response->getResponseDataString() == "") {

		if (Configs::printConsoleLog)
		{
			CCLOG("onHttpRequestCompleted - error response->getResponseDataString() is empty");
		}
		callbackWhenError();
		return;
	}
	std::vector<char> *buffer = response->getResponseData();

	const char* data = buffer->data();
	auto len = buffer->size();

	if(CALL_NATIVE_CROP_AVATAR){
		response->retain();

		AsyncTaskPool::getInstance()->enqueue(
			AsyncTaskPool::TaskType::TASK_NETWORK,
			std::bind(&DownloadImageManager::onReceivedCircleImage, this, url, response),
			nullptr,
			[this, data, len, response]() {
                this->currentImage = PluginManager::getInstance()->getGamePlugin()->circleImage((unsigned char*)data, len);

                if (!this->currentImage) {
                    log("Circle Image Failed");
                    this->currentImage = new Image();
                    this->currentImage->initWithImageData(reinterpret_cast<const unsigned char*>(data), len);
                }
		});
	}
	else {
		Image * image = new Image();
		image->initWithImageData(reinterpret_cast<const unsigned char*>(data), len);

		if (Configs::printConsoleLog)
		{
			CCLOG("onHttpRequestCompleted - sucess create image");
		}

		Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(image, response->getHttpRequest()->getUrl());

		for (auto callback : callbackList)
		{
			if (callback)
			{
				callback(texture);
			}
		}
		this->downloadingImageWithCallback[url].clear();
	}
}

void DownloadImageManager::onReceivedCircleImage(const std::string & url,
                                                 cocos2d::network::HttpResponse* response)
{
	if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS) {
		response->release();
	}

	if (Configs::printConsoleLog)
	{
		CCLOG("onHttpRequestCompleted - sucess create image");
	}
	/*Texture2D * texture = new  Texture2D();
	texture->initWithImage(this->currentImage);*/
	Texture2D * texture = Director::getInstance()->getTextureCache()->addImage(this->currentImage, url);

	auto callbackList = this->downloadingImageWithCallback[url];

	for (auto callback : callbackList)
	{
		if (callback)
		{
			callback(texture);
		}
	}
	this->downloadingImageWithCallback[url].clear();
}

void DownloadImageManager::downloadImage(const std::string & url)
{
    
#if IS_RUN_WITHOUT_NW
    return;
#endif
	cocos2d::network::HttpRequest* request = new (std::nothrow) cocos2d::network::HttpRequest();
	request->setUrl(url);
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setResponseCallback(CC_CALLBACK_2(DownloadImageManager::onHttpRequestLoadImageCompleted, this));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void DownloadImageManager::addDownloadToQueueAndCheckDownload(
	const std::string & url, 
	std::function<void(cocos2d::Texture2D*texture)> callback)
{
#if IS_RUN_WITHOUT_NW
    return;
#endif
	this->downloadingImageWithCallback[url].push_back(callback);
	this->downloadImageQueue.push_back(url);
	if (this->downloadImageQueue.size() <= 1) {
		this->checkAndDownload();
	}
}

void DownloadImageManager::checkAndDownload()
{
#if IS_RUN_WITHOUT_NW
    return;
#endif
	if (this->downloadImageQueue.size() > 0) {
		this->downloadImage(this->downloadImageQueue[0]);
	}
}

void DownloadImageManager::loadImageFromCacheOrDownload(
	const std::string &url, 
	std::function<void(cocos2d::Texture2D* texture)> callback)

{
#if IS_RUN_WITHOUT_NW
    return;
#endif
	std::string realUrl = this->redirectMap[url].empty() ? url : this->redirectMap[url];
	if (url.empty()) {
		if (callback)
		{
			callback(nullptr);
		}
		return;
	}
	//load texture from cache if exist then call dicrectly callback and return
	auto texture = Director::getInstance()->getTextureCache()->getTextureForKey(realUrl);
	if (texture) {
		if (callback)
		{
			callback(texture);
		}
		return;
	}
	this->addDownloadToQueueAndCheckDownload(
		realUrl,
		callback
	);
}
