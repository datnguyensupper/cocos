#include "DownloadFileManager.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "Helper/Helper4String.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

#pragma region init singleton
DownloadFileManager* DownloadFileManager::s_instance = nullptr;

DownloadFileManager* DownloadFileManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new DownloadFileManager();
	}
	return s_instance;
}
#pragma endregion

DownloadFileManager::DownloadFileManager()
{

}

void DownloadFileManager::downloadFileWithURL(std::string fileUrl, std::function<void(cocos2d::Image*)> callback, bool shouldReleaseImageAfterDownload) {
	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setUrl(fileUrl);
	request->setResponseCallback([=](cocos2d::network::HttpClient *client, cocos2d::network::HttpResponse *response) {
		if (response->isSucceed()) {
			auto data = response->getResponseData();
			Image *img = new Image();
			if (img->initWithImageData(reinterpret_cast<const unsigned char*>(&(data->front())), data->size())) {
				//if (img->saveToFile("garu.png", false)) {
					callback(img);
					if (shouldReleaseImageAfterDownload) {
						img->release();
					}
				//}
			}
		}
	});
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();

}


network::Downloader* DownloadFileManager::downloadFileWithURLAndSave2Device(
	std::string fileID,
	bool isStartDownload,
	network::Downloader *downloader, 
	std::string url, 
	std::string filePath,
	bool shouldDecompress, 
	std::function<void(std::string fileID, float progress, bool isFinish, bool isFail)> callback) {

	//if (url.compare("") == 0) {
	//	//url = "https://scmw.spiralworks-cloud.com/ppwebstatic/cocos_gameslot_resource/gameslot/boxing.zip";
	//	url = "https://scmw.spiralworks-cloud.com/ppwebstatic/cocos_gameslot_resource/gameslot/legendofnezha.zip";;
	//}
	//if (filePath.compare("") == 0) {
	//	std::string fileName = Helper4String::getBaseNameFromPath(url);
	//	std::string localPath = getGameSlotDirectoryGame("");
	//	filePath = localPath + fileName;
	//}

	if (downloader == nullptr) {
		downloader = new (std::nothrow) network::Downloader();
	}

	downloader->onTaskProgress = ([=](const network::DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected) {
		//downloading progress
		cocos2d::log("totalBytesReceived %i ; %i ; totalBytesExpected %i ;", totalBytesReceived, totalBytesExpected);
		callback(fileID,totalBytesReceived*1.0/ totalBytesExpected, false, false);
	});

	downloader->onFileTaskSuccess = ([=](const network::DownloadTask& task) {
		//file downloaded, do what you need next
		if (shouldDecompress) {
			callback(fileID, 1, false, false);
			uncompressInBGThread(filePath, [=](bool isSuccess) {
				if (isSuccess) {
					removeFile(filePath);
				}
				callback(fileID, 1, true, !isSuccess);
			});
			//if (uncompress(filePath)) {
			//	// remove zip file after decompress
			//}
		}
		else {
			callback(fileID, 1, true, false);
		}
	});

	downloader->onTaskError = ([=](const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr) {
		//file downloading error
		callback(fileID, -1, true, true);
	});

	// callback start download event
	callback(fileID, 0, false, false);

	if (url.compare("") == 0 || filePath.compare("") == 0) {
		//url = "https://scmw.spiralworks-cloud.com/ppwebstatic/cocos_gameslot_resource/gameslot/boxing.zip";
		//url = "https://scmw.spiralworks-cloud.com/ppwebstatic/cocos_gameslot_resource/gameslot/legendofnezha.zip";

		//std::string fileName = Helper4String::getBaseNameFromPath(url);
		//std::string localPath = getGameSlotDirectoryGame("");
		//filePath = localPath + fileName;

		return downloader;
	}
	if (isStartDownload) {
		if (_fileUtils->isFileExist(filePath)) {
			_fileUtils->removeFile(filePath);
		}
		downloader->createDownloadFileTask(url, filePath);
	}
	return downloader;
	//string url = "";
	//downloadFileWithURL(url,[=](Image * image) {
		//std::string fileName = Helper4String::getBaseNameFromPath(url);
		//std::string localPath = getDirectoryGame();
	//	localPath.append(fileName);
	//	if (image->saveToFile(localPath, false)) {
	//		callback(localPath);
	//	}
	//},true);
}

//void DownloadFileManager::releasAssetManagerEvent() {
//	if (_am != nullptr &&
//		_am->getReferenceCount() != 0) {
//		_am->release();
//	}
//	if (_amListener != nullptr &&
//		_am->getReferenceCount() != 0) {
//		_amListener->release();
//	}
//	_am = nullptr;
//	_amListener = nullptr;
//}

/// <summary>
/// download game slot with asset manager
/// </summary>
/// <param name="prefix">prefix of file</param>
/// <param name="callback">update progress when download</param>
cocos2d::extension::AssetsManagerEx * DownloadFileManager::downloadFileWithAssetManager(
	std::string fileID,
	bool isStartDownload,
	cocos2d::extension::AssetsManagerEx * _am,
	std::string url,
	std::string filePath,
	bool shouldDecompress,
	std::function<void(std::string fileID, float progress, bool isFinish, bool isFail)> callback) {

	//releasAssetManagerEvent();
	

	//std::string fileName = Helper4String::getBaseNameFromPath(url);
	std::string storagePath = getDirectoryGame();
	std::string manifestPath = "res/"+ fileID +"_local.manifest";

	// force remove each time call this function
	removeFile(storagePath+"project.manifest");
	removeFile(storagePath+"version.manifest");
	//return;

	if (_am == nullptr && isStartDownload) {
		_am = AssetsManagerEx::create(manifestPath, storagePath);
		// As the process is asynchronies, you need to retain the assets manager to make sure it won't be released before the process is ended.
		_am->retain();
	}

	
	cocos2d::extension::EventListenerAssetsManagerEx *_amListener = cocos2d::extension::EventListenerAssetsManagerEx::create(_am, [=](EventAssetsManagerEx* event) {
		bool shouldRelease = false;
		static int failCount = 0;
		//AssetsManagerExTestScene *scene;
		EventAssetsManagerEx::EventCode eventCode = event->getEventCode();
		switch (eventCode)
		{
		case EventAssetsManagerEx::EventCode::UPDATE_PROGRESSION:
		{
			std::string assetId = event->getAssetId();
			float percent = event->getPercent();
			log(percent);
			//std::string str;
			if (assetId == AssetsManagerEx::VERSION_ID)
			{//version file 1%
				percent = percent * 0.01;
			}
			else if (assetId == AssetsManagerEx::MANIFEST_ID)
			{//manifest file 1%
				percent = percent * 0.01;
				percent += 1;
			}
			else
			{//data file 90%
				percent = percent * 0.98;
				percent += 2;
			}
				//str = StringUtils::format("%.2f", percent) + "%";
				CCLOG("%.2f Percent", percent);
			callback(fileID,percent, false,false);
			return;
			/*if (_progress != nullptr)
				_progress->setString(str);*/
		}
		break;
		case EventAssetsManagerEx::EventCode::ALREADY_UP_TO_DATE:
		case EventAssetsManagerEx::EventCode::UPDATE_FINISHED:
		{
			CCLOG("Update finished. %s", event->getMessage().c_str());
			shouldRelease = true;
			callback(fileID,1, true,false);
		}
		break;
		case EventAssetsManagerEx::EventCode::UPDATE_FAILED:
		{
			CCLOG("Update failed. %s", event->getMessage().c_str());

			failCount++;
			if (failCount < 5)
			{
				_am->downloadFailedAssets();
			}
			else
			{
				CCLOG("Reach maximum fail count, exit update process");
				failCount = 0;
			}
		}
		break;
		case EventAssetsManagerEx::EventCode::ERROR_NO_LOCAL_MANIFEST:
		{
			CCLOG("No local manifest file found, skip assets update.");
		}
		case EventAssetsManagerEx::EventCode::ERROR_DOWNLOAD_MANIFEST:
		case EventAssetsManagerEx::EventCode::ERROR_PARSE_MANIFEST:
		{
			CCLOG("Fail to download manifest file, update skipped.");
		}
		case EventAssetsManagerEx::EventCode::ERROR_UPDATING:
		{
			//CCLOG("Asset %s : %s", event->getAssetId().c_str(), event->getMessage().c_str());
		}
		case EventAssetsManagerEx::EventCode::ERROR_DECOMPRESS:
		{
			//CCLOG("%s", event->getMessage().c_str());
			shouldRelease = true;
			callback(fileID,-1, true,true);
		}
		break;
		default:
			break;
		}
		if (shouldRelease) {
			_am->release();
			//releasAssetManagerEvent();
		}
	});

	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_amListener, 1);

	if (isStartDownload) {
		_am->update();
	}
	return _am;
}
