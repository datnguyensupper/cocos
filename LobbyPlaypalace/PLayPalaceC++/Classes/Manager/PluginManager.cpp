#include "PluginManager.h"

USING_NS_CC;
#pragma region init singleton
PluginManager* PluginManager::s_instance = nullptr;

PluginManager::PluginManager()
{
	facebookController = new FacebookController();
	iapController = new IAPController();
	advertiseController = new AdvertiseController();
	gamePlugin = new GamePlugin();
	imagePickerController = new ImagePicker();
}

PluginManager* PluginManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new PluginManager();
	}
	return s_instance;
}
#pragma endregion

PluginManager::~PluginManager()
{
	CC_SAFE_DELETE(facebookController);
	CC_SAFE_DELETE(iapController);
	CC_SAFE_DELETE(advertiseController);
	CC_SAFE_DELETE(gamePlugin);
	CC_SAFE_DELETE(imagePickerController);
}