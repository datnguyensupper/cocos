#include "PromotionsManager.h"
#include "PopupManager.h"
#include "InfoManager.h"
#include "NetworkManager.h"
#include "Constant/ResultCodeConstant.h"
#include "Views/Popup/Promotions/SpecialOfferPopup.h"
#include "Views/Popup/Promotions/StarterPackPopup.h"
#include "Views/Popup/Promotions/FreeToPlayPopup.h"
#include "Views/Popup/Promotions/PayToPlayPopup.h"
#include "Views/Popup/Promotions/GetMoreCoinsPopup.h"
#include "Helper/Helper4Scene.h"
#include "Helper/Helper4Time.h"

using namespace std;
USING_NS_CC;

#define STORE_KEY_NUMBER_SHOW_F2P_CONSECUTIVE_FORMAT "NUMBER_SHOW_F2P_CONSECUTIVE_"
#define STORE_KEY_TS_LAST_SHOW_F2P_FORMAT "TS_LAST_SHOW_F2P_"
#define STORE_KEY_STARTER_CLICKED_BUY_FORMAT "STARTER_CLICKED_BUY_"

#define MINIUM_COIN_SHOW_FREE_TO_PLAY 100000
#define MINIUM_COIN_SHOW_GET_MORE_COIN 100000

static PromotionsManager* s_instance = nullptr;

PromotionsManager::PromotionsManager()
{
}

PromotionsManager* PromotionsManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new (std::nothrow)PromotionsManager();
	}
	return s_instance;
}

void PromotionsManager::checkStartupPromotions(const std::function<void(bool isHavePromotion)> cb)
{
	if (isCheckStartup) {
		this->isLobbyBegin = true;
		this->checkRepeatedPromotions(cb);
		return;
	}
	isCheckStartup = true;
	bool isHavePromotions = false;
	isHavePromotions |= this->checkStarterPack();
	isHavePromotions |= this->checkPayToPlay();

	if (isHavePromotions) {
		this->checkSpecialOffer(nullptr);
		if (cb) {
			cb(true);
		}
	}
	else {
		this->checkSpecialOffer(cb);
	}
}

void PromotionsManager::checkRepeatedPromotions(const std::function<void(bool isHavePromotion)> cb)
{
	bool isHavePromotions = false;
	if (this->isLobbyBegin || Helper4Scene::getRunningScene()->getTag() == ppEnum::GameScene::GameSlot) {
		isHavePromotions |= this->checkFreeToPlay();
		isHavePromotions |= this->checkGetMoreCoins();
	}
	if (cb) {
		cb(isHavePromotions);
	}
	this->isLobbyBegin = false;
}

void PromotionsManager::checkSpecialOffer(const std::function<void(bool isHavePromotion)> cb)
{
	NetworkManager::getInstance()->checkSpecialOffer([cb](int coreResultCode, rapidjson::Value& responseDoc, std::string responseString) {
		bool isHavePromotion = false;
		if (coreResultCode == RESULT_CODE_VALID) {
			isHavePromotion = PopupManager::getInstance()->getSpecialOfferPopup()->prepareAndShow(
				Helper4ParseJSON::getMember(responseDoc)[0], 
				Helper4Scene::getRunningScene());
		}
		if (cb) {
			cb(isHavePromotion);
		}
	}, [cb](std::string responseString) {
		if (cb) {
			cb(false);
		}
	}, [cb](std::string responseString) {
		if (cb) {
			cb(false);
		}
	});
}

bool PromotionsManager::checkStarterPack()
{
	auto currentTimeStamp = Helper4Time::getCurrentTimeStamp();
	auto totalTsFromSignUp = currentTimeStamp - InfoManager::getInstance()->getUserInfo()->timestampOfCreated;

	if (totalTsFromSignUp <= Helper4Time::ONE_DAY_MILLISECOND * 5 && InfoManager::getInstance()->getUserInfo()->purchaseAmount == 0) {
		PopupManager::getInstance()->getStarterPackPopup()->prepareAndShow(Helper4Scene::getRunningScene());
		return true;
	}
	return false;
}

bool PromotionsManager::checkPayToPlay()
{
	auto currentTimeStamp = Helper4Time::getCurrentTimeStamp();
	auto totalTsFromLastLogin = currentTimeStamp - InfoManager::getInstance()->getUserInfo()->timestampLastLogin;

	if (totalTsFromLastLogin >= Helper4Time::ONE_DAY_MILLISECOND * 7 && InfoManager::getInstance()->getUserInfo()->purchaseAmount > 0) {
		PopupManager::getInstance()->getPayToPlayPopup()->prepareAndShow(Helper4Scene::getRunningScene());
		return true;
	}
	return false;
}

bool PromotionsManager::checkFreeToPlay()
{
	bool result = false;
	if (InfoManager::getInstance()->getUserInfo()->coin < MINIUM_COIN_SHOW_FREE_TO_PLAY &&
		InfoManager::getInstance()->getUserInfo()->purchaseAmount == 0 &&
		(
			(!bF2PShowedInGame && Helper4Scene::getRunningScene()->getTag() == ppEnum::GameScene::GameSlot) ||
			(!bF2PShowedInLobby && Helper4Scene::getRunningScene()->getTag() == ppEnum::GameScene::Lobby)
		)) {

		auto numberShowedF2PConsecutive = UserDefault::getInstance()->getIntegerForKey(
			(STORE_KEY_NUMBER_SHOW_F2P_CONSECUTIVE_FORMAT + ToString(InfoManager::getInstance()->getUserInfo()->id)).c_str(), 0);
		auto lastTimeShowed = UserDefault::getInstance()->getDoubleForKey(
			(STORE_KEY_TS_LAST_SHOW_F2P_FORMAT + ToString(InfoManager::getInstance()->getUserInfo()->id)).c_str(), 0);
		if (numberShowedF2PConsecutive >= 2) {
			if (lastTimeShowed != 0) {
				auto timeSpan = Helper4Time::getCurrentTimeStamp() - lastTimeShowed;
				if (timeSpan > Helper4Time::ONE_DAY_MILLISECOND * 3) {
					numberShowedF2PConsecutive = 0;
					lastTimeShowed = 0;
				}
			}
		}

		if (numberShowedF2PConsecutive < 2) {
			numberShowedF2PConsecutive++;
			UserDefault::getInstance()->setIntegerForKey(
				(STORE_KEY_NUMBER_SHOW_F2P_CONSECUTIVE_FORMAT + ToString(InfoManager::getInstance()->getUserInfo()->id)).c_str(), numberShowedF2PConsecutive);
			if (lastTimeShowed == 0) {
				UserDefault::getInstance()->setDoubleForKey(
					(STORE_KEY_TS_LAST_SHOW_F2P_FORMAT + ToString(InfoManager::getInstance()->getUserInfo()->id)).c_str(), lastTimeShowed);
			}
			UserDefault::getInstance()->flush();

			auto currentScene = Helper4Scene::getRunningScene();
			if (currentScene->getTag() == ppEnum::GameScene::Lobby) {
				bF2PShowedInLobby = true;
			}
			else {
				bF2PShowedInGame = true;
			}

			result = PopupManager::getInstance()->getFreeToPlayPopup()->prepareAndShow(Helper4Scene::getRunningScene());
		}
	}
	return result;
}

bool PromotionsManager::checkGetMoreCoins()
{
	bool result = false;
	if (InfoManager::getInstance()->getUserInfo()->coin < MINIUM_COIN_SHOW_GET_MORE_COIN && this->getMoreCoinTotalShowed < 3) {
		result = PopupManager::getInstance()->getGetMoreCoinsPopup()->prepareAndShow(Helper4Scene::getRunningScene());
		this->getMoreCoinTotalShowed += result ? 1 : 0;
	}
	return result;
}

void PromotionsManager::reset()
{
	isCheckStartup = false;
	isLobbyBegin = false;
	bF2PShowedInGame = false;
	bF2PShowedInLobby = false;
	getMoreCoinTotalShowed = 0;
}

