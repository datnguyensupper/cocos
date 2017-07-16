#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: Configs.h, Configs.cpp
*/
#include "cocos2d.h"
#include "Constant/Defination.h"

using namespace std;

class Configs
{
public:
#pragma region app configs
	static const bool isProduction;
	static const string AppDomain;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const string AppDomainTest;
#endif
	static const bool printConsoleLog;
	static const string webServiceFullUrl;
	static const string appBundleID_android;
	static const string appBundleID_IOS;
	static const string downloadGameSlotPath;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	static const string downloadGameSlotPathTest;
#endif
	static const string freeGiftFacebookProductId;

	static const int mobilePlatform;
	static const int versionCode;
	static const string versionName;//or versionApp

	static const string FanPage;
	static const string PageTerm;
	static const string PagePrivacy;

	static const string LevelUpThumbnailLink;
#pragma endregion

#pragma region plugins configs

#pragma endregion

#pragma region game settings
	static const float SCALE_RESOUCE_VALUE;
    static const float SCALE_RESOUCE_VALUE_LOW_RAM_DEVICE;
	static const float BUTTON_ZOOM_SCALE_VALUE;
	static const float TIME_TRANSITION_FADE_SCENE;
	static const float TIME_4_RELOADING_BOTTOM;
#pragma endregion
};
