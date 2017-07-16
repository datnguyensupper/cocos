#include "PluginVungleController.h"
#include "Constant/Defination.h"
#include "Manager/InfoManager.h"

USING_NS_CC;
PluginVungleController::PluginVungleController() {

}

void PluginVungleController::init() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    PluginVungle::init("592ba81530b8b0102c0005c4");
#elif  (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    PluginVungle::init("592ba9ef573ae5270800087c");
#endif
    PluginVungle::setListener(this);
}

void PluginVungleController::playAd(const std::function<void(bool isSuccess)> &callbackEnd,
                                    const std::function<void()>& callbackStart) {
    this->callbackEnd = callbackEnd;
    this->callbackStart = callbackStart;
    PluginVungle::playAdIncentivized(ToString(InfoManager::getInstance()->getUserInfo()->id));
}

void PluginVungleController::onAdStart() {
    if(this->callbackStart){
        this->callbackStart();
    }
}

void PluginVungleController::onAdUnavailable(const std::string &reason) {
    if(this->callbackEnd){
        this->callbackEnd(false);
    }
}

void PluginVungleController::onAdEnd(bool wasSuccessfulView) {
    if(this->callbackEnd){
        this->callbackEnd(wasSuccessfulView);
    }
}

void PluginVungleController::onAdPlayableChanged(bool isAdPlayable) {

}
