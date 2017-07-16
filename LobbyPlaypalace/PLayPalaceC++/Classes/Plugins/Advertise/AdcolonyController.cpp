#include "AdcolonyController.h"
#include "Configs.h"
#include "Manager/NetworkManager.h"
#include "Manager/InfoManager.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/Defination.h"

USING_NS_CC;

void AdcolonyController::onAdColonyChange(const sdkbox::AdColonyAdInfo & info, bool available)
{
	CCLOG("ADCOLONY: onAdColonyChange");
	CCLOG("info.name: %s", info.name.c_str());
	CCLOG("info.shown: %s", info.shown ? "true" : "false");
	CCLOG("info.zoneID: %s", info.zoneID.c_str());
	CCLOG("info.iapEnabled: %s", info.iapEnabled ? "true" : "false");
	CCLOG("info.iapProductID: %s", info.iapProductID.c_str());
	CCLOG("info.iapQuantity: %d", info.iapQuantity);
	CCLOG("info.iapEngagementType: %d", info.iapEngagementType);
}

void AdcolonyController::onAdColonyReward(const sdkbox::AdColonyAdInfo & info, const std::string & currencyName, int amount, bool success)
{
	CCLOG("ADCOLONY: onAdColonyReward, currencyName: %s, amount: %d, success: %s", currencyName.c_str(), amount, success ? "true" : "false");
	CCLOG("info.name: %s", info.name.c_str());
	CCLOG("info.shown: %s", info.shown ? "true" : "false");
	CCLOG("info.zoneID: %s", info.zoneID.c_str());
	CCLOG("info.iapEnabled: %s", info.iapEnabled ? "true" : "false");
	CCLOG("info.iapProductID: %s", info.iapProductID.c_str());
	CCLOG("info.iapQuantity: %d", info.iapQuantity);
	CCLOG("info.iapEngagementType: %d", info.iapEngagementType);
	if (this->callbackReward)
	{
		this->callbackReward(info, currencyName, amount, success);
		this->callbackReward = nullptr;
	}
}

void AdcolonyController::onAdColonyStarted(const sdkbox::AdColonyAdInfo & info)
{
	CCLOG("ADCOLONY: onAdColonyStarted");
	CCLOG("info.name: %s", info.name.c_str());
	CCLOG("info.shown: %s", info.shown ? "true" : "false");
	CCLOG("info.zoneID: %s", info.zoneID.c_str());
	CCLOG("info.iapEnabled: %s", info.iapEnabled ? "true" : "false");
	CCLOG("info.iapProductID: %s", info.iapProductID.c_str());
	CCLOG("info.iapQuantity: %d", info.iapQuantity);
	CCLOG("info.iapEngagementType: %d", info.iapEngagementType);
}

void AdcolonyController::onAdColonyFinished(const sdkbox::AdColonyAdInfo & info)
{
	CCLOG("ADCOLONY: onAdColonyFinished");
	CCLOG("info.name: %s", info.name.c_str());
	CCLOG("info.shown: %s", info.shown ? "true" : "false");
	CCLOG("info.zoneID: %s", info.zoneID.c_str());
	CCLOG("info.iapEnabled: %s", info.iapEnabled ? "true" : "false");
	CCLOG("info.iapProductID: %s", info.iapProductID.c_str());
	CCLOG("info.iapQuantity: %d", info.iapQuantity);
	CCLOG("info.iapEngagementType: %d", info.iapEngagementType);
}

AdcolonyController::AdcolonyController()
{
#ifdef SDKBOX_ENABLED
	/*if (Configs::printConsoleLog)
	{
	CCLOG("ADCOLONY: CONTRUCTOR FUCTION CALLED + CUSTOM ID = %s", sdkbox::PluginAdColony::getCustomID().c_str());
	}*/
	//sdkbox::PluginAdColony::setListener(this);
	//sdkbox::PluginAdColony::init();
#endif
}

void AdcolonyController::initWithCustomId(std::string customId)
{
	if (!this->customIdFirstSetup.empty())
	{
		return;
	}
#ifdef SDKBOX_ENABLED

    CCLOG("ADCOLONY START INIT**********************************************");

	this->setCustomId(customId);
	if (Configs::printConsoleLog)
	{
		CCLOG("ADCOLONY: CONTRUCTOR FUCTION CALLED + CUSTOM ID = %s", customId.c_str());
	}
	sdkbox::PluginAdColony::init();
	sdkbox::PluginAdColony::setListener(this);

    CCLOG("ADCOLONY FINISH INIT**********************************************");
#endif
}

void AdcolonyController::showVideo(std::function<void(const sdkbox::AdColonyAdInfo& info,
	const std::string& currencyName, int amount, bool success)> _callbackReward)
{
	this->callbackReward = _callbackReward;
#ifdef SDKBOX_ENABLED

	if (this->getVideoStatus() != sdkbox::AdColonyAdStatus::ADCOLONY_ZONE_STATUS_ACTIVE) {
		if (Configs::printConsoleLog)
		{
			CCLOG("ADCOLONY: STATUS NOT ACTIVE TO SHOW VIDEO");
			sdkbox::AdColonyAdInfo info;
            std::string currencyName = "";
			_callbackReward(info, currencyName, 0, false);
		}
		return;
	}
	sdkbox::PluginAdColony::show("v4vc");
#endif
}

void AdcolonyController::setCustomId(const std::string & customId)
{
#ifdef SDKBOX_ENABLED
	if (Configs::printConsoleLog)
	{
		CCLOG("ADCOLONY: SET CUSTOM ID: %s", customId.c_str());
	}
	sdkbox::PluginAdColony::setCustomID(customId);
#endif
	this->customIdFirstSetup = customId;
	auto previousCustomId = UserDefault::getInstance()->getStringForKey(STORING_KEY_PREVIOUS_CUSTOM_ID_ADCOLONY);
	if (!previousCustomId.empty()
		&& previousCustomId != customId)
	{
		this->canShowVideo = false;
	}
	UserDefault::getInstance()->setStringForKey(STORING_KEY_PREVIOUS_CUSTOM_ID_ADCOLONY, customId);
	UserDefault::getInstance()->flush();
}

sdkbox::AdColonyAdStatus AdcolonyController::getVideoStatus()
{
	if (!this->canShowVideo
		|| ToString(InfoManager::getInstance()->getUserInfo()->id) != this->customIdFirstSetup)
	{
		if (Configs::printConsoleLog)
		{
			//CCLOG("ADCOLONY: GET VIDEO STATUS FAIL BECAUSE OF canShowVideo OR customIdFirstSetup");
		}
		return sdkbox::AdColonyAdStatus::ADCOLONY_ZONE_STATUS_UNKNOWN;
	}
#ifdef SDKBOX_ENABLED
	sdkbox::AdColonyAdStatus status = sdkbox::PluginAdColony::getStatus("v4vc");;
	if (Configs::printConsoleLog)
	{
        CCLOG("ADCOLONY: GET VIDEO STATUS: %d", status == sdkbox::AdColonyAdStatus::ADCOLONY_ZONE_STATUS_ACTIVE ? 1 : 0);
        CCLOG("ADCOLONY: GET VIDEO STATUS: %i", status);
	}
	return status;
#endif
	return sdkbox::AdColonyAdStatus::ADCOLONY_ZONE_STATUS_UNKNOWN;
}
