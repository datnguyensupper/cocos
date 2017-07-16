#include "AdvertiseController.h"
#include "Constant/Defination.h"
#include "Manager/InfoManager.h"
#include "AdvertiseController.h"

USING_NS_CC;
using namespace std;

#define USING_ADCOLONY true
#define USING_VUNGLE true

AdvertiseController::AdvertiseController()
{
	if (USING_ADCOLONY) {
		adcolony = new AdcolonyController();
	}
	if (USING_VUNGLE) {
		vungle = new PluginVungleController();
	}
}

AdvertiseController::~AdvertiseController()
{
	CC_SAFE_DELETE(adcolony);
	CC_SAFE_DELETE(vungle);
}

void AdvertiseController::init()
{
	if (USING_ADCOLONY) {
		adcolony->initWithCustomId(ToString(InfoManager::getInstance()->getUserInfo()->id));
	}
	if (USING_VUNGLE) {
		vungle->init();
	}
}

bool AdvertiseController::isShowable()
{
	bool result = false;
	if (USING_ADCOLONY) {
		result |= adcolony->getVideoStatus() == sdkbox::AdColonyAdStatus::ADCOLONY_ZONE_STATUS_ACTIVE;
	}
	if (USING_VUNGLE) {
		result |= vungle->isAdPlayable();
	}
	return result;
}

void AdvertiseController::showVideo(const std::function<void(int amount, bool isSuccess)>& cb)
{
	if (USING_ADCOLONY && adcolony->getVideoStatus() == sdkbox::AdColonyAdStatus::ADCOLONY_ZONE_STATUS_ACTIVE) {
		adcolony->showVideo([cb](const sdkbox::AdColonyAdInfo& info, const std::string& currencyName, int amount, bool success) {
			if (cb) {
				cb(amount, success);
			}
		});
	}
	else if (USING_VUNGLE && vungle->isAdPlayable()) {
		vungle->playAd([cb](bool success) {
			if (cb) {
				cb(50000, success);
			}
		});
	}else{
		if (cb) {
			cb(0, false);
		}
	}
}
