#include "Manager4Network.h"
#include "../game/CMainBase.h"
#include "../game/CGameBase.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Info/AdditionalInfo.h"
#include "Views/Popup/NotificationPopup.h"
#include "Helper/Helper4Time.h"
#if IS_DEBUG
#include "Manager/Test/TestManager.h"
#endif

USING_NS_CC;
using namespace network;
namespace GameSlot {
	static Manager4Network *_sharedManager4Network = nullptr;
	Manager4Network* Manager4Network::getInstance()
	{
		if (!_sharedManager4Network)
		{
			_sharedManager4Network = new (std::nothrow) Manager4Network();
		}

		return _sharedManager4Network;
	}

	Manager4Network::~Manager4Network()
	{
		
	}

	void Manager4Network::get(const std::string& url,
		const std::string& params,
		APIGameCallback cb) {
		if (this->curRequest) {
			this->curRequest->release();
		}
        
#if IS_RUN_WITHOUT_NW
        CCLOG(url.c_str());
        CCLOG(url.c_str());
        TestManager::getInstance()->getFakeXMLRespone(url, [=](bool isSuccess, tinyxml2::XMLDocument* response) {
            cb(isSuccess, response);
        });
        return;
#endif
        
        
		HttpRequest* request = new HttpRequest();
		request->setUrl(url + "?" + params);
		request->setRequestType(HttpRequest::Type::GET);
		request->setResponseCallback([this, cb](cocos2d::network::HttpClient *sender,
			cocos2d::network::HttpResponse *response) {
			response->retain();

			AsyncTaskPool::getInstance()->enqueue(
				AsyncTaskPool::TaskType::TASK_NETWORK,
				std::bind(&Manager4Network::onReceivedXML, this, cb),
				nullptr,
				[this, sender, response]() {
				this->onHttpRequestCompleted(sender, response);
			});
		});
		request->setTag("GET: " + url);
		HttpClient::getInstance()->send(request);

		request->retain();
		this->curRequest = request;
	}
	void Manager4Network::post(const std::string& url,
		const std::string& params,
		APIGameCallback cb) {
		HttpRequest* request = new HttpRequest();
		request->setUrl(url);
		request->setRequestType(HttpRequest::Type::POST);
		request->setResponseCallback([this, cb](cocos2d::network::HttpClient *sender,
			cocos2d::network::HttpResponse *response) {
			response->retain();

			AsyncTaskPool::getInstance()->enqueue(
				AsyncTaskPool::TaskType::TASK_NETWORK,
				std::bind(&Manager4Network::onReceivedXML, this, cb),
				nullptr,
				[this, sender, response]() {
				this->onHttpRequestCompleted(sender, response);
			});
		});

		const char* postData = params.c_str();
		request->setRequestData(postData, strlen(postData));

		request->setTag("POST: " + url);
		HttpClient::getInstance()->send(request);
		request->release();
	}

	void Manager4Network::onHttpRequestCompleted(
		cocos2d::network::HttpClient *sender,
		cocos2d::network::HttpResponse *response) {

		if (this->curRequest) {
			this->curRequest->release();
			this->curRequest = nullptr;
		}

		if (this->_oMain == nullptr) {
			response->release();
			return;
		}

		if (response && response->isSucceed()) {
			auto buffer = response->getResponseData();
			std::string _xml = std::string(buffer->begin(), buffer->end());

			auto doc = new tinyxml2::XMLDocument();
            CCLOG(_xml.c_str());
			doc->Parse(_xml.c_str());

			this->curDoc = doc;

			response->release();
		}
		else {
			this->curDoc = nullptr;
		}
	}

	void Manager4Network::onReceivedXML(const APIGameCallback & cb){
		if (this->_oMain == nullptr) return;

		if (this->curDoc) {
			if (!this->handleError(this->curDoc, cb)) {
				if (cb) {
					cb(true, this->curDoc);
				}
			}
			CC_SAFE_DELETE(this->curDoc);
		}
		else {
			if (cb) {
				cb(false, nullptr);
			}
			else {
				this->_oMain->getScene()->gotoLoginScene(true, "", "");
			}		
		}
	}

	bool Manager4Network::handleError(tinyxml2::XMLDocument* oXmlDoc, const APIGameCallback& cb) {
		if (!oXmlDoc || oXmlDoc->Error()) {
			//alert("Network connection was lost");
			//this->_oMain->s_oGame.generateLosingWheel();
			return true;
		}
		long errorCode = 0;
		if (oXmlDoc->FirstChildElement("error") != nullptr &&
			oXmlDoc->FirstChildElement("error")->FirstChild() != nullptr &&
			oXmlDoc->FirstChildElement("error")->Attribute("code") != nullptr) {
			errorCode = atol(oXmlDoc->FirstChildElement("error")->Attribute("code"));
		}
		else {
			errorCode = -1;
		}

		switch (errorCode) {
		case -1:
			break;
		case ERROR_CODE::WRONG_STEP:
			//Wrong step
			//my.forceToStopBonus();
			return true;
			break;
		case ERROR_CODE::WRONG_PARAM:
			//Wrong parameter;
			//my.forceToStopBonus();
			return true;
			break;
		case ERROR_CODE::SPIN_TOO_FAST:
			if (this->_oMain->getGame()) {
				this->_oMain->getGame()->generateLosingWheel();
			}
			return true;
		case ERROR_CODE::SERVER_MAINTENANCE:
			this->_oMain->getScene()->gotoLoginSceneServerMaintenance();
			return true;
		case ERROR_CODE::LOGGED_SOMEWHERE_ELSE:
			this->_oMain->getScene()->gotoLoginSceneLoginAnotherPlace();
			return true;
		case ERROR_CODE::NOT_ENOUGH_MONEY:
			if (this->_oMain->getGame()) {
				this->_oMain->getGame()->generateLosingWheel();
			}
			return true;
		case ERROR_CODE::COMMON_ERROR:
		default:
			if(cb){
				cb(false, nullptr);
			}else{
			    this->_oMain->getScene()->gotoLoginScene(true,"","");
			}
			return true;
		}
		return false;
	}

	void Manager4Network::alertInvalidAccessToken() {

	}

	void Manager4Network::setGame(CMainBase * _oMain)
	{
		this->_oMain = _oMain;
		GameConstant::getInstance()->setGame(_oMain->getGameName());
	}

	void Manager4Network::callFunPlay()
	{
		this->get(
			"http://rslotservice.viosl.com/onlinecasino/common/getfunplaykey",
			"iid?=vista",
			nullptr);
	}

	void Manager4Network::callRealPlay()
	{
		std::string token;
		token = InfoManager::getInstance()->getUserInfo()->accessToken;
		//token = "proxy@playpalace@36d9486a-d94a-4370-ad9d-21359f474e94";//bonus random
		//token = "proxy@playpalace@3d09953b-7fa5-4ce0-8e1d-25fe97e369cf";//bonus fs
		//token = "proxy@playpalace@7dff037f-dd88-4060-909e-2711a7273ef0";//dat account
		//token = "proxy@playpalace@3d09953b-7fa5-4ce0-8e1d-25fe97e369cf";//bonus fs
		//token = "proxy@playpalace@5add83e9-b485-465f-a178-7c1f47da2fa1";//normal
																		//token = "proxy@playpalace@053016c3-9c11-4ed7-92d1-312b8922debe";//bonus 2
																		//token = "proxy@playpalace@1afb39bb-6e84-4c1f-9dc5-75d3450d7842";//bonus 1

		if (token.empty()) {
			this->alertInvalidAccessToken();
			return;
		}

		auto params = "accessToken=" + token;

		this->get(
			GameConstant::getInstance()->getDomainName().gameService.authorization,
			params,
			[this](bool isSuccess, tinyxml2::XMLDocument * oXmlDoc) {
			if (isSuccess) {
				auto szKey = oXmlDoc->FirstChildElement("string")->FirstChild()->Value();
				// 2016-03-18: handle error in authorizationByToken API
				if (szKey == "false") {
					this->alertInvalidAccessToken();
					return;
				}
				this->_oMain->onGetRealPlayKeyReceived(szKey);
			}
			else {
				PopupManager::getInstance()->getNotificationPopup()->showServerErrorPopup(this->_oMain->getScene(), [this]() {
					this->callRealPlay();
				});
			}
		});
	}

	void Manager4Network::callGetBalance(const std::string& szKey)
	{
		auto params = "key=" + szKey;

		this->get(
			GameConstant::getInstance()->getDomainName().gameService.getBalance,
			params,
			[this, &szKey](bool isSuccess, tinyxml2::XMLDocument * oXmlDoc) {
			if (isSuccess && !(oXmlDoc->FirstChildElement("BALANCE")->NoChildren() || oXmlDoc->FirstChildElement("BALANCE")->FirstChild()->Value() == "ERR")) {
				auto szCredit = atof(oXmlDoc->FirstChildElement("BALANCE")->FirstChild()->Value());
				this->_oMain->onBalanceReceived(szCredit);
			}
			else {
				PopupManager::getInstance()->getNotificationPopup()->showServerErrorPopup(this->_oMain->getScene(), [this, szKey]() {
					this->callGetBalance(szKey);
				});
			}
		});
	}

	void Manager4Network::callGetBet(const std::string& szKey)
	{
		this->_lTs = Helper4Time::getCurrentTimeStamp();
		std::string params = "key=" + szKey + "&" +
			"ts=" + ToString(_lTs);

		this->get(
			GameConstant::getInstance()->getDomainName().gameService.getBet,
			params,
			[this, &szKey](bool isSuccess, tinyxml2::XMLDocument * oXmlDoc) {
			if (isSuccess) {
				this->_oMain->onBetsReceived(oXmlDoc);
			}
			else {
				PopupManager::getInstance()->getNotificationPopup()->showServerErrorPopup(this->_oMain->getScene(), [this, szKey]() {
					this->callGetBet(szKey);
				});
			}
		});
	}

	void Manager4Network::callGetSpin(const std::function<void()>& cb)
	{
		//string xmlData = "<?xml version=\"1.0\" encoding =\"UTF-8\" standalone=\"yes\"?><spin bet=\"3000.0\" lines = \"30\" multiplier = \"1\" scatter = \"1\" ts = \"1456996029\" totalbet = \"90000.0\" type = \"s\" wild = \"0\" ><balance>250000.0</balance><bonus/><bonusposition/><jackpot/><tablewin/><wheels height=\"3\" type=\"normal\" val=\"7,6,1,6,0,1,5,6,1,0,6,4,8,5,10\" width=\"5\"/><win jackpot=\"0.0\">150000.0</win><winposition><item line=\"3\" mul=\"15\" win=\"67500.0\">3,3,3,0,0</item><item line=\"10\" mul=\"75\" win=\"337500.0\">2,1,2,0,0</item></winposition></spin>";
		//this->currentDoc = new tinyxml2::XMLDocument();
		//this->currentDoc->Parse(xmlData.c_str());
		//this->onReceivedXML([this](bool isSuccess, tinyxml2::XMLDocument * oXmlDoc) {
		//	this->_oMain->onSpinReceived(this->currentDoc);
		//});
		////this->_oMain->getGame()->generateLosingWheel();
		//return;
		auto params = "key=" + this->_oMain->getRealPlayKey() + "&" +
			"bet=" + ToString(this->_oMain->getBet()) + "&" +
			"lineBet=" + ToString(this->_oMain->getLine()) + "&" +
			"multiply=" + ToString(this->_oMain->getMul()) + "&" +
			"ts=" + ToString(this->_lTs) + "&" +
			"magicItemType=" + ToString(InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType);

		this->get(
			GameConstant::getInstance()->getDomainName().gameService.spin,
			params,
			[this, &cb](bool isSuccess, tinyxml2::XMLDocument * oXmlDoc) {
			if (isSuccess) {
				if (this->_oMain) {
					//LobbyC.MainMenu.handleMagicItemUsed(oXmlDoc);
					this->_oMain->onSpinReceived(oXmlDoc);
				}
			}
			else {
				PopupManager::getInstance()->getNotificationPopup()->showServerErrorPopup(this->_oMain->getScene(), [this]() {
					this->callGetSpin();
				});
			}
		});
	}

	void Manager4Network::callBonus(int iStep, int iParam)
	{
		this->_oMain->setReceivedBonus(false);
		auto params = "key=" + this->_oMain->getRealPlayKey() + "&" +
			"bonus=" + this->_oMain->getBonusKey() + "&" +
			"step=" + ToString(iStep) + "&" +
			"param=" + ToString(iParam) + "&" +
			"ts=" + ToString(this->_lTs);

		this->get(
			GameConstant::getInstance()->getDomainName().gameService.bonusGame,
			params,
			[this, iStep, iParam](bool isSuccess, tinyxml2::XMLDocument * oXmlDoc) {
			if (isSuccess) {
				this->_oMain->setReceivedBonus(true);
				this->_oMain->onBonusReceived(oXmlDoc);
			}
			else {
				//LobbyC.MainMenu.showServerErroPopup(function () {
				//    //self.callBonus(iStep, iParam);
				//}, true);
			}
		});
	}
	void Manager4Network::release()
	{
		this->curDoc = nullptr;
		this->_oMain = nullptr;
		if (this->curRequest) {
			this->curRequest->setResponseCallback(nullptr);
			this->curRequest->release();
			this->curRequest = nullptr;
		}
	}
}
