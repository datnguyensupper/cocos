#include "Configs.h"
#pragma region app configs

const bool Configs::isProduction = false;
const string Configs::AppDomain = "https://scmw.spiralworks-cloud.com";

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
const string Configs::AppDomainTest = "http://scmw.spiralworks-cloud.com";
#endif
const bool Configs::printConsoleLog = true;
#if IS_DEBUG
//const string Configs::webServiceFullUrl = Configs::AppDomain + "/lobby-server-pp-strategiesV2";
const string Configs::webServiceFullUrl = Configs::AppDomain + "/lobby-server-pp-strategies";
#else
const string Configs::webServiceFullUrl = Configs::AppDomain + "/lobby-server-pp-strategies";
//const string Configs::webServiceFullUrl = Configs::AppDomain + "/lobby-server-pp-strategiesV2";
#endif
const string Configs::appBundleID_android = "com.lobbyteam.playpalace.unity";
const string Configs::appBundleID_IOS = "1109211273";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
const string Configs::downloadGameSlotPathTest = Configs::AppDomainTest + "/ppwebstatic/cocos_gameslot_resource/gameslot/";
#endif
const string Configs::downloadGameSlotPath = Configs::AppDomain + "/ppwebstatic/cocos_gameslot_resource/gameslot/";
const string Configs::freeGiftFacebookProductId = "1476689462646842"; //1468607626792468 in production?

const int Configs::mobilePlatform = 1;
const int Configs::versionCode = 30;
const string Configs::versionName = "1.0.13";//or versionApp

const string Configs::FanPage = "https://www.facebook.com/pplobby";
const string Configs::PageTerm = "https://www.playpalace.com/term";
const string Configs::PagePrivacy = "https://www.playpalace.com/privacy";

const string Configs::LevelUpThumbnailLink = "http://uat-pp-resource.playpalace.com/ppwebstatic/web_pp_img_share/level_up.png";
#pragma endregion

#pragma region plugins configs

#pragma endregion

#pragma region game settings
const float Configs::SCALE_RESOUCE_VALUE = 1600.0 / 1280.0f;
const float Configs::SCALE_RESOUCE_VALUE_LOW_RAM_DEVICE = 1600.0 / 1024.0f;
const float Configs::BUTTON_ZOOM_SCALE_VALUE = -0.2f;
const float Configs::TIME_TRANSITION_FADE_SCENE = 0.4f;
const float Configs::TIME_4_RELOADING_BOTTOM = 120; // minute
#pragma endregion

