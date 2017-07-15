#include "Manager/NetworkManager.h"
#include "PopupManager.h"
#include "Scene/LoginScene.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Login/NotiLoginPopup.h"
#include "Configs.h"
#include "Constant/JSONFieldConstant.h"
#include "Constant/Defination.h"
#include "Constant/LobbyConstant.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/MessageConstant.h"
#include "Helper/Helper4String.h"
#include "Helper/Helper4Scene.h"
#include "Util/UtilFunction.h"

using namespace std;
USING_NS_CC;
#pragma region init singleton
NetworkManager* NetworkManager::s_instance = nullptr;

NetworkManager* NetworkManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new NetworkManager();
	}
	return s_instance;
}
#pragma endregion

NetworkManager::~NetworkManager()
{
	CC_SAFE_DELETE(s_instance);
}
#pragma region core_method
void NetworkManager::sendRequestInQueue()
{
	if (this->requestQueue.size() > 0)
	{
		if (Configs::printConsoleLog)
		{
			CCLOG("REQUEST FROM URL : %s", requestQueue[0]->getUrl());
		}
		cocos2d::network::HttpClient::getInstance()->send(requestQueue[0]);
		requestQueue[0]->release();
	}
}
void NetworkManager::post(
	const std::string &url,
	std::string &postData,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut,
	float timeoutIn,
	bool isAddLoginToken
)
{
	if (isAddLoginToken
		&& !this->loginToken.empty())
	{
		postData += ((postData.empty() ? "" : "&") + (string)("loginToken=") + this->loginToken);
	}

	__String* dataToSend = __String::create(postData);
	__String* urlString = __String::create(url);
	dataToSend = Helper4String::replaceCCString(dataToSend, CCString::create("+"), CCString::create("%2B"));

	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl(urlString->getCString());
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setRequestData(dataToSend->getCString(), dataToSend->length());

	if (!this->session.empty())
	{
		std::vector<std::string> headers;
		headers.push_back("Cookie:" + this->session);
		request->setHeaders(headers);
	}

	if (Configs::printConsoleLog)
	{
		CCLOG("SESSION = %s", this->session.c_str());
	}
	request->setResponseCallback([this, callback, callbackError, callbackTimeOut,url](
		cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response) {
		onHttpRequestCompleted(
			sender,
			response,
			callback,
			callbackError,
			callbackTimeOut
		);
	});

	request->setTag(urlString->getCString());


	//cocos2d::network::HttpClient::getInstance()->setTimeoutForConnect(30);
	//cocos2d::network::HttpClient::getInstance()->setTimeoutForRead(30);

	/*AsyncTaskPool::getInstance()->enqueue(
		AsyncTaskPool::TaskType::TASK_NETWORK,
		nullptr, nullptr, [this, request, urlString]() {
		if (Configs::printConsoleLog)
		{
			CCLOG("POST FROM URL : %s", urlString->getCString());
		}
		cocos2d::network::HttpClient::getInstance()->send(request);
		request->release();
	});*/
	//cocos2d::network::HttpClient::getInstance()->send(request);
	request->retain();

	requestQueue.push_back(request);
	if (requestQueue.size() == 1)
	{
		this->sendRequestInQueue();
	}
}

/**
* 2017-02-06: Kiet: post method.
*
* @param data (example: data = "username=kiet@gmail.com&password=12345678" for login_web)
* @param callback callback after get response and passed handleSpecialErrorResultCode
*/
void NetworkManager::post(
	const std::string &url,
	std::string &data,
	std::function<void(int coreResultCode, bool isSuccess, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	float timeoutIn,
	bool isAddLoginToken
) {
	post(
		url, 
		data, 
		//request success
		[callback](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString) {
		callback(coreResultCode, coreResultCode == RESULT_CODE_VALID, responseAsDocument, responseAsString);
	},
		// network error
		[callback](std::string result) {
		rapidjson::Value responseAsDocument;
		callback(RESULT_CODE_NETWORK_ERROR, false, responseAsDocument, result);
	},
		// callback timeout
		[callback](std::string result) {
		rapidjson::Value responseAsDocument;
		callback(RESULT_CODE_NETWORK_TIME_OUT, false, responseAsDocument, result);
	
	}, timeoutIn, isAddLoginToken);
}

void NetworkManager::postMultipart(
	const std::string & url,
	const std::map<std::string, std::string>& formData,
	const std::string &dataFieldName, const char* dataBinary, size_t dataLen,
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut, 
	float timeoutIn)
{
	std::string boundary = UtilFunction::getRandomBoundary();

	string postString = UtilFunction::getPostString(formData, boundary);
	postString += UtilFunction::getMultipartData(dataFieldName, dataBinary, dataLen, boundary);

	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setRequestData(postString.c_str(), postString.size());

	std::vector<std::string> headers;
	if (!this->session.empty())
	{
		headers.push_back("Cookie:" + this->session);
	}
	headers.push_back("Content-Type: multipart/form-data; boundary=" + boundary);
	request->setHeaders(headers);

	if (Configs::printConsoleLog)
	{
		CCLOG("SESSION = %s", this->session.c_str());
	}
	request->setResponseCallback([this, callback, callbackError, callbackTimeOut](
		cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response) {
		onHttpRequestCompleted(
			sender,
			response,
			callback,
			callbackError,
			callbackTimeOut
		);
	});

	request->setTag(url.c_str());

	//cocos2d::network::HttpClient::getInstance()->send(request);
	request->retain();
	requestQueue.push_back(request);
	if (requestQueue.size() == 1)
	{
		sendRequestInQueue();
	}
}

void NetworkManager::get(
	const std::string &url,
	std::string &data,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut,
	float timeoutIn,
	bool isAddLoginToken
)
{
	if (isAddLoginToken
		&& !this->loginToken.empty())
	{
		data += ((data.empty() ? "?" : "&") + (string)("loginToken=") + this->loginToken);
	}
	__String* urlString = __String::create(url + data);


	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl(urlString->getCString());
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);

	if (!this->session.empty())
	{
		std::vector<std::string> headers;
		headers.push_back("Cookie:" + this->session);
		request->setHeaders(headers);
	}

	request->setResponseCallback([this, callback, callbackError, callbackTimeOut](
		cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response) {
		onHttpRequestCompleted(
			sender,
			response,
			callback,
			callbackError,
			callbackTimeOut
		);
	});

	request->setTag(urlString->getCString());

	//cocos2d::network::HttpClient::getInstance()->send(request);
	//request->release();
	request->retain();
	requestQueue.push_back(request);
	if (requestQueue.size() == 1)
	{
		if (Configs::printConsoleLog)
		{
			CCLOG("REQUEST FROM URL : %s", urlString->getCString());
		}
		cocos2d::network::HttpClient::getInstance()->send(request);
		requestQueue[0]->release();
	}
}
void NetworkManager::onHttpRequestCompleted(
	cocos2d::network::HttpClient* sender,
	cocos2d::network::HttpResponse* response,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	requestQueue.erase(requestQueue.begin());
	sendRequestInQueue();

	//request sucess
	if (response
		&& response->isSucceed()
		&& response->getResponseCode() == 200) {
		if (Configs::printConsoleLog)
		{
			CCLOG("onHttpRequestCompleted success");
		}
		try
		{
			if (Configs::printConsoleLog)
			{
				CCLOG("response data size = %d", response->getResponseData()->size());
			}
			string stringResult = "";
			std::vector<char> *buffer = response->getResponseData();
			for (unsigned int i = 0; i < buffer->size(); i++)
			{
				stringResult += (*buffer)[i];
			}
			if (Configs::printConsoleLog)
			{
				CCLOG("API: %s \n response from server: %s", response->getHttpRequest()->getUrl(), stringResult.c_str());
			}
			//get session if session empty
			if (this->session.empty())
			{
				this->getSession(response);
			}
			Document responseAsDocument;
			responseAsDocument.Parse(stringResult.c_str());
			rapidjson::Value beanResponseAsDocument;
			if (responseAsDocument.HasMember(JSONFieldConstant::BEAN.c_str()))
			{
				beanResponseAsDocument = responseAsDocument[JSONFieldConstant::BEAN.c_str()];
			}
			if (!this->handleSpecialErrorResultCode(responseAsDocument[JSONFieldConstant::RESULT_CODE.c_str()].GetInt())){
				if (callback){
					if (responseAsDocument.HasMember(JSONFieldConstant::RESULT_CODE.c_str())){
						callback(
							responseAsDocument[JSONFieldConstant::RESULT_CODE.c_str()].GetInt(),
							beanResponseAsDocument,
							stringResult
						);
					}
				}
			}else {
				callbackError(stringResult);
			}
		}
		catch (const std::exception&)
		{

		}
	}
	//request error
	else {
		if (Configs::printConsoleLog)
		{
			CCLOG("onHttpRequestCompleted fail");
		}
		if (!response)
		{
			CCLOG("onHttpRequestCompleted fail response null");
		}
		else if (!response->isSucceed())
		{
			CCLOG("onHttpRequestCompleted fail response not sucess");
			if (response->getResponseCode() != 200)
			{
				CCLOG("onHttpRequestCompleted fail response code : %lu", response->getResponseCode());
			}
		}
			
		this->handleErrorRequest(
			response,
			callbackError,
			callbackTimeOut
		);
	}
}
void NetworkManager::getSession(cocos2d::network::HttpResponse* response)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("@@@@@@@@@@@@@@@ GET SESSION @@@@@@@@@@@@@@@");
	}
	string stringHeader = "";
	std::vector<char> *buffer = response->getResponseHeader();
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		stringHeader += (*buffer)[i];
	}
	if (Configs::printConsoleLog)
	{
		CCLOG("stringHeader :\n %s ", stringHeader.c_str());
	}
	vector<string> keyList = Helper4String::splitString(stringHeader, "\n");
	for (auto &line : keyList)
	{
		if (line.find("Set-Cookie") != std::string::npos)
		{
			vector<string> sessionData = Helper4String::splitString(line, "; ");
			for (auto &lineSessionData : sessionData)
			{
				vector<string> stringsSplit = Helper4String::splitString(lineSessionData, ",");
				if (stringsSplit.size() < 2)
				{
					stringsSplit = Helper4String::splitString(stringsSplit[0], ": ");
				}
				if (stringsSplit.size() < 2)
				{
					stringsSplit = Helper4String::splitString(stringsSplit[0], ":");
				}
				for (auto stringParseByComma : stringsSplit)
				{
					if (stringParseByComma.find("JSESSIONID") != std::string::npos)
					{
						this->session = stringParseByComma;
						return;
					}
				}
			}
		}
	}
}
void NetworkManager::handleErrorRequest(
	cocos2d::network::HttpResponse* response,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut){

	PopupManager::getInstance()->getLoadingAnimation()->hide();

	BaseScene * runningScene = (BaseScene*)Helper4Scene::getRunningScene();
	int runningSceneTag = runningScene->getTag();
	switch (runningSceneTag)
	{
	case ppEnum::GameScene::Login:
		if (response&& (response->getResponseCode() == 404 || response->getResponseCode() == 405 || response->getResponseCode() == 500))
			PopupManager::getInstance()->getNotificationLoginPopup()->show(
				(LoginScene*)runningScene,
				MessageConstant::MESSAGE_SERVER_MAINTENANCE_TITLE,
				MessageConstant::MESSAGE_LOGIN_MAINTENANCE
			);
		else
			PopupManager::getInstance()->getNotificationLoginPopup()->show(
				(LoginScene*)runningScene,
				MessageConstant::MESSAGE_NETWORK_ERROR,
				MessageConstant::MESSAGE_LOST_INTERNET_CONNECTION
			);
		
		break;
	case ppEnum::GameScene::InitSession:
		if (response&& (response->getResponseCode() == 404 || response->getResponseCode() == 405 || response->getResponseCode() == 500))
			runningScene->gotoLoginSceneServerMaintenance();
		else
			runningScene->gotoLoginSceneLostConnection();
		break;
	case ppEnum::GameScene::Lobby:
	case ppEnum::GameScene::LuckyWheel:
	case ppEnum::GameScene::GameSlot:
		if (response&& (response->getResponseCode() == 404 || response->getResponseCode() == 405 || response->getResponseCode() == 500))
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(runningScene,"Warning","Server Maintenance",
				"OK","","",[runningScene](){
				runningScene->gotoLoginScene("","");
			}, [runningScene]() {
				runningScene->gotoLoginScene("", "");
			});
		else
			PopupManager::getInstance()->getNotificationPopup()->showServerErrorPopup(runningScene,nullptr,true,[runningScene](){
				runningScene->gotoLoginScene("","");
			},[runningScene](){
				runningScene->gotoLoginScene("","");
			});
		
		break;
	}
	if (callbackError)	callbackError(response->getResponseDataString());
	
}
bool NetworkManager::handleSpecialErrorResultCode(
	int coreResultCode
)
{
	BaseScene * runningScene = (BaseScene *)Helper4Scene::getRunningScene();
	std::string title = "";
	std::string body = "";
	std::function<void()> okCallback = nullptr; 
	std::function <void()> callbackCancel = nullptr;
	bool returnWithValue = false;
	switch (coreResultCode)
	{
	case RESULT_CODE_NOT_LOGIN:  // not login
		title = MessageConstant::MESSAGE_ERROR;
		body = MessageConstant::MESSAGE_NETWORK_ERROR;
		returnWithValue = true;
		break;
	case RESULT_CODE_FORCE_CLIENT_UPDATE_APP_LOBBY:  // for update new app
		title = "";
		body = MessageConstant::MESSAGE_FORCE_UPDATE_NEW_VERSION;
		returnWithValue = true;
		break;
	case RESULT_CODE_SERVER_MAINTENANCE:
		title = MessageConstant::MESSAGE_SERVER_MAINTENANCE_TITLE;
		body = MessageConstant::MESSAGE_LOGIN_MAINTENANCE;
		returnWithValue = true;
		break;
	case RESULT_CODE_USER_LOGIN_IN_ANOTHER_LOCATION:
		title = LanguageManager::getInstance()->getStringForKeys(nullptr,LanguageConstant::POPUP_GIFT_WARNING);
		body = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::LOGIN_SOME_WHERE);
		returnWithValue = true;
		break;
	default:
		break;
	}

	if (returnWithValue){
		okCallback = [this, runningScene]() {
			runningScene->gotoLoginScene("", "");
		};
		callbackCancel = okCallback;
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		if (runningScene->getTag() == ppEnum::GameScene::Login){
			PopupManager::getInstance()->getNotificationLoginPopup()->show(
				(LoginScene*)runningScene,title,body,
				okCallback,callbackCancel
			);
		}else {
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				runningScene,title,body,"OK","","",
				okCallback,callbackCancel
			);
		}
	}

	return returnWithValue;
}

void NetworkManager::gotoPlayStore2UpdateGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) // XXX means your platform
	Application::getInstance()->openURL("market://details?id=" + Configs::appBundleID_android);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	Application::getInstance()->openURL("itms-apps://itunes.apple.com/app/id/" + Configs::appBundleID_IOS);
#endif
}
#pragma endregion

#pragma region Requests
void NetworkManager::getRedirectFBPicture(const std::string &rootUrl, std::function<void(std::string redirectUrl)> callback)
{
	//example get
	/*{
		"data": {
			"height": 320,
				"is_silhouette" : false,
				"url" : "https://scontent.xx.fbcdn.net/v/t1.0-1/p320x320/17203192_1827656270784821_7887027973054471372_n.jpg?oh=da09e75906b354fc538790685ee56539&oe=5925DB87",
				"width" : 320
		}
	}*/
	std::string getUrl = rootUrl + "&redirect=false";

	cocos2d::network::HttpRequest* request = new (std::nothrow) cocos2d::network::HttpRequest();
	request->setUrl(getUrl);
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);
	request->setResponseCallback([callback](
		cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response)
	{
		if (!response
			|| !response->isSucceed())
		{
			if (callback)
			{
				callback("");
			}
			return;
		}
		string stringResult = "";
		std::vector<char> *buffer = response->getResponseData();
		for (unsigned int i = 0; i < buffer->size(); i++)
		{
			stringResult += (*buffer)[i];
		}
		Document responseAsDocument;
		responseAsDocument.Parse(stringResult.c_str());
		if (!responseAsDocument.HasMember("data")) {
			if (!callback)
			{
				callback("");
			}
			return;
		}
		rapidjson::Value &data = responseAsDocument["data"];
		if (!data.HasMember("url")) {
			if (!callback)
			{
				callback("");
			}
			return;
		}
		if (callback)
		{
			callback(data["url"].GetString());
		}
	});
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

#pragma region LoginScene
void NetworkManager::loginFB(
	const std::string & accessToken,
	std::function<void(int coreResultCode,
	rapidjson::Value&responseAsDocument, 
	std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "token=" + accessToken;
	postData += "&platform=" + ToString(Configs::mobilePlatform);
	postData += "&isMobile=1";
	this->session = "";

	post(
		Configs::webServiceFullUrl + "/user/loginFacebook",
		postData,
		callback,
		callbackError,
		callbackTimeOut,
		10000,
		false
	);
}
void NetworkManager::loginPPAcount(
	const std::string &username,
	const std::string &password,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "username=" + username;
	postData += "&password=" + password;
	this->session = "";

	post(
		Configs::webServiceFullUrl + "/user/login_web",
		postData,
		callback,
		callbackError,
		callbackTimeOut,
		10000,
		false
	);
}
void NetworkManager::authorizePPAccount(
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut 
)
{
	string postData = "";

	get(
		Configs::webServiceFullUrl + "/user/authorize",
		postData,
		callback,
		callbackError,
		callbackTimeOut,
		10000,
		false
	);
}

void NetworkManager::signUpPlayPalaceAccount(
	const std::string &username,
	const std::string &password,
	const std::string &referenceCode,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "username=" + username;
	postData += "&password=" + password;
	postData += "&referenceCode=" + referenceCode;

	post(
		Configs::webServiceFullUrl + "/user/sign_up",
		postData,
		callback,
		callbackError,
		callbackTimeOut,
		10000,
		false
	);
}

void NetworkManager::generateGuessAcount(
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/local/signUp",
		postData,
		callback,
		callbackError,
		callbackTimeOut,
		10000,
		false
	);
}

void NetworkManager::loginGuessAcount(
	const std::string &usernameLocal,
	const std::string &passwordLocal,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "username=" + usernameLocal;
	postData += "&password=" + passwordLocal;
	postData += "&platform=" + String::createWithFormat("%d", Configs::versionCode)->_string;

	this->session = "";
	post(
		Configs::webServiceFullUrl + "/user/local/login",
		postData,
		callback,
		callbackError,
		callbackTimeOut,
		10000,
		false
	);
}

void NetworkManager::resetPassword(
	const std::string &username,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "username=" + username;

	post(
		Configs::webServiceFullUrl + "/user/requestResetPassword",
		postData,
		callback,
		callbackError,
		callbackTimeOut,
		10000,
		false
	);
}
#pragma endregion

#pragma region InitSessionScene
void NetworkManager::getAllData(
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "androidVersionCode=" + String::createWithFormat("%d", Configs::versionCode)->_string;
	postData += "&androidVersionName=" + Configs::versionName;
	postData += "&platformGetMyProfile=" + StringUtils::toString(Configs::mobilePlatform);
	postData += "&getStatisticData=true";
	postData += "&specialOfferAPIVersion=1";

	post(
		Configs::webServiceFullUrl + "/user/getAllData",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

void NetworkManager::getAdditionalInfo(
	std::function<void(int coreResultCode, 
	rapidjson::Value&responseAsDocument,
	std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/getAdditionalInfo",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

/// <summary>
/// Dat : call api /user/featureConfig/getAll get Info:
/// DAILY_BONUS_STREAK, FREE_COIN_GIFT, UNLOCK_BY_LEVEL, LUCKY_WHEEL, 
/// DAILY_CHALLENGE, BOOSTER, MOBILE_SLOT_GAME_CONFIG, SLOT_GAME_PAY_LINE_CONFIG, 
/// LUCKY_BOX_CONFIG, 
/// </summary>
/// <param name="callback"></param>
/// <param name="callbackError"></param>
/// <param name="callbackTimeOut"></param>
void NetworkManager::getAllFeatureConfig(
	std::function<void(int coreResultCode, bool isSuccess, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback
)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/featureConfig/getAll",
		postData,
		callback
	);
}
/// <summary>
/// Dat : call api /user/freeCoinGift/collect 
/// to collect freecoin gift
/// </summary>
/// <param name="callback"></param>
/// <param name="callbackError"></param>
/// <param name="callbackTimeOut"></param>
void NetworkManager::collectFreeCoinGift(
	std::function<void(int coreResultCode, bool isSuccess, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback
)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/freeCoinGift/collect",
		postData,
		callback
	);
}

void NetworkManager::getUserInfo(
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "androidVersionCode=" + String::createWithFormat("%d", Configs::versionCode)->_string;
	postData += "&androidVersionName=" + Configs::versionName;
	postData += "&platform=" + ToString(Configs::mobilePlatform);
	postData += "&getStatisticData=true";

	post(
		Configs::webServiceFullUrl + "/user/profile",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

void NetworkManager::getGameSlotList(
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "platform=" + ToString(Configs::mobilePlatform);

	post(
		Configs::webServiceFullUrl + "/user/me/game/slot/listAll",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Setting Popup


void NetworkManager::logout(
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/logout",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

#pragma endregion

#pragma region gift + leaderboard
void NetworkManager::getAllGift(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, 
	std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/gift/getAll",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::acceptGift(long giftId, std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "id=" + ToString(giftId);

	post(
		Configs::webServiceFullUrl + "/user/gift/accept",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::acceptGiftAll(std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/gift/acceptAll",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::getFriendList(std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";

	post(
		Configs::webServiceFullUrl + "/user/friendList",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::sendGiftToUserList(
	std::vector<std::string> userIds,
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "giftType=" + ToString(LobbyConstant::GIFT_FREE_FROM_USER);
	for (auto userId : userIds)
	{
		postData += "&userIdList[]=" + userId;
	}

	post(
		Configs::webServiceFullUrl + "/user/gift/sendToUserList",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

void NetworkManager::sendInviteFriend(std::vector<std::string> facebookUIDs, std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "listFacebookUID=";
	for (auto facebookUID : facebookUIDs)
	{
		postData += (facebookUID + ",");
	}

	post(
		Configs::webServiceFullUrl + "/user/me/inviteFriends",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}


void NetworkManager::getLeaderboard(
	int type,
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut
)
{
	string postData = "type=" + String::createWithFormat("%d", type)->_string;

	post(
		Configs::webServiceFullUrl + "/user/me/getLeaderboard",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Purchase
void NetworkManager::verifyAndroidPayment(
	const std::string &receipt,
	const std::string &receiptCipheredPayload,
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "transactionReceipt=" + receipt;
	postData += "&transactionSignature=" + receiptCipheredPayload;
	postData += "&paymentAPIVersion=" + ToString(LobbyConstant::PAYMENT_API_VERSION_COCOS);

	post(
		Configs::webServiceFullUrl + "/user/payment/android/verify",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

void NetworkManager::verifyIOSPayment(
  const std::string &receipt,
  const std::string &appStoreReceipt,
  std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback,
  std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
    string postData = "transactionReceipt=" + receipt;
    postData += "&appStoreReceipt=" + appStoreReceipt;
    postData += "&paymentAPIVersion=" + ToString(LobbyConstant::PAYMENT_API_VERSION_COCOS);
    
    post(
         Configs::webServiceFullUrl + "/user/payment/ios/verify",
         postData,
         callback,
         callbackError,
         callbackTimeOut
         );
}

void NetworkManager::uploadAvatar(
	const char* data, size_t len,
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	map<string, string> postData;
	postData["loginToken"] = this->loginToken;

	postMultipart(
	Configs::webServiceFullUrl + "/user/updateAvatar",
		postData,
		"avatar", data, len,
		callback,
		callbackError,
		callbackTimeOut
	);
}

void NetworkManager::updateName(const std::string & newName,
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "name=" + newName;

	post(
		Configs::webServiceFullUrl + "/user/updateName",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

void NetworkManager::submitReferenceCode(const std::string & referenceCode,
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "referenceCode=" + referenceCode;

	post(
		Configs::webServiceFullUrl + "/user/inputReferenceCode",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Achievement
void NetworkManager::getAchievementList(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/achievement/listAllOfCurrentUser",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}

void NetworkManager::collectAchievement(int id, 
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "achievementId=" + ToString(id);
	post(
		Configs::webServiceFullUrl + "/user/me/collectAchievement",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::collectDailyBonusWheel(std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/dailyBonusWheel/collect",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Comeback Bonus Mobile
void NetworkManager::collectComebackBonusMobile(std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/comebackBonusMobile/collect",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion


#pragma region Tutorial
void NetworkManager::redeemPreTutorialReward(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/me/redeemPreTutorialReward",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::redeemTutorialReward(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/me/redeemTutorialReward",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::finishTutorial(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/me/completeTutorial",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Daily Bonus Streak
void NetworkManager::collectDailyBonusStreak(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/dailyBonusStreak/collect",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Lucky Wheel
/**
* Collect daily bosnus wheel
*/
void NetworkManager::spinLuckyWheel(
	std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
	std::function<void(std::string result)> callbackError,
	std::function<void(std::string result)> callbackTimeOut) 
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/luckyWheel/spin",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::buyLuckyWheelUsingCrow(
	const std::string& packageType,
	const std::function<void(int coreResultCode,rapidjson::Value&responseAsDocument,std::string responseAsString)>& callback,
	const std::function<void(std::string result)>& callbackError, 
	const std::function<void(std::string result)>& callbackTimeOut)
{
	string postData = "packageType=" + packageType;
	post(
		Configs::webServiceFullUrl + "/user/luckyWheel/buySpinUsingCrown",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Lucky Daily Spin
void NetworkManager::collectDailyBonusLuckySpin(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/dailyBonusLuckySpin/spin",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Daily Challenge
void NetworkManager::getDailyChallengeInfo(
	std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, 
	std::function<void(std::string result)> callbackError, 
	std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/dailyChallenge/getInfo",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
void NetworkManager::collectDailyChallenge(
	const std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)>& callback, 
	const std::function<void(std::string result)>& callbackError, 
	const std::function<void(std::string result)>& callbackTimeOut)
{
	string postData = "";
	post(
		Configs::webServiceFullUrl + "/user/dailyChallenge/collect",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma region Shop
void NetworkManager::activateMagicItem(int magicItemType, std::function<void(int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString)> callback, std::function<void(std::string result)> callbackError, std::function<void(std::string result)> callbackTimeOut)
{
	string postData = "magicItemType=" + ToString(magicItemType);
	post(
		Configs::webServiceFullUrl + "/user/magicItem/activate",
		postData,
		callback,
		callbackError,
		callbackTimeOut
	);
}
#pragma endregion

#pragma endregion
