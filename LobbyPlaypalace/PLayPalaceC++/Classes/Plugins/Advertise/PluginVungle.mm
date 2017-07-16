#include "PluginVungle.h"
using namespace cocos2d;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "PluginVungle-ios.h"

static VungleListener* vungleListener = nullptr;
static PluginVungleIOS *sharedInstance = [[[PluginVungleIOS alloc] init] retain];

void PluginVungle::init(const std::string &appID) {
    [sharedInstance init:@(appID.c_str())];
}

void PluginVungle::playAd() {
    [sharedInstance playAd:nullptr];
}

void PluginVungle::playAdIncentivized(const std::string& userID) {
    [sharedInstance playAdIncentivized:@(userID.c_str())];
}

void PluginVungle::clearEventListeners() {
    [sharedInstance clearEventListeners];
}

bool PluginVungle::isPlayable() {
    return  [sharedInstance isPlayable];
}

void PluginVungle::setListener(VungleListener *listener) {
    vungleListener = listener;
}
#endif
