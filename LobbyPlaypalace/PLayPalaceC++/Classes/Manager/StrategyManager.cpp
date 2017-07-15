#include "StrategyManager.h"

#include "json/writer.h"
#include "json/document.h"

#include "Constant/ResultCodeConstant.h"

#include "Helper/Helper4ParseJSON.h"

#include "Info/AdditionalInfo.h"

#include "NetworkManager.h"

#include "Configs.h"


using namespace std;
USING_NS_CC;
#pragma region init singleton
StrategyManager* StrategyManager::s_instance = nullptr;

StrategyManager* StrategyManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new StrategyManager();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

StrategyManager::~StrategyManager()
{

}
StrategyManager::StrategyManager()
{

}
//DEPRECATED
void StrategyManager::getAdditionalInfo(std::function<void(bool isSuccess)> callback, bool isReloadUI) {
	NetworkManager::getInstance()->getAdditionalInfo([callback](
		int coreResultCode,
		rapidjson::Value &responseAsDocument,
		std::string responseAsString)
	{
		if (coreResultCode == RESULT_CODE_VALID)
		{
			auto listSize = Helper4ParseJSON::getListSize(responseAsDocument);
			auto members = Helper4ParseJSON::getMember(responseAsDocument);
			for (auto i = 0; i < listSize; i++) {

				rapidjson::Value &beanData = Helper4ParseJSON::getBeanData(members[i]);

				std::string beanType = Helper4ParseJSON::getBeanType(beanData);
				if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_STREAK)
					InfoManager::getInstance()->getAdditionalInfo()->dailyBonusStreakInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_FREE_COIN_GIFT)
					InfoManager::getInstance()->getAdditionalInfo()->freeCoinGiftInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_REFERENCE_CODE)
					InfoManager::getInstance()->getAdditionalInfo()->referenceCodeInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_LUCKY_SPIN)
					InfoManager::getInstance()->getAdditionalInfo()->dailyBonusLuckySpinInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_WHEEL)
					InfoManager::getInstance()->getAdditionalInfo()->dailyBonusWheelInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_LUCKY_WHEEL)
					InfoManager::getInstance()->getAdditionalInfo()->luckyWheelInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_LUCKY_BOX)
					InfoManager::getInstance()->getAdditionalInfo()->luckyBoxInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_PIGGY_BANK)
					InfoManager::getInstance()->getAdditionalInfo()->piggyBankInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_BOOSTER)
					InfoManager::getInstance()->getAdditionalInfo()->boosterInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_COMEBACK_BONUS)
					InfoManager::getInstance()->getAdditionalInfo()->comebackBonusMobileInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_MAGIC_ITEM)
					InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->updateInfoByValue(beanData);
			}
			if (callback != nullptr) callback(true);
		}
		else
		{
			if (Configs::printConsoleLog) CCLOG("ERROR AT GET ADDITIONAL INFO");
			if (callback != nullptr) callback(false);
		}
	});
}

//DEPRECATED
void StrategyManager::handleFailResultNewStrategy(NetworkFailProcessInfo failInfo, bool isShowFailPopup, bool isReloadAdditionalInfo) {
	
	if (isShowFailPopup) log("show fail popup");

	if (isReloadAdditionalInfo) {
		getAdditionalInfo(nullptr, false);
	}
}