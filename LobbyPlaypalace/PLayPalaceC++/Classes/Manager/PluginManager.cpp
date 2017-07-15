#include "PluginManager.h"

USING_NS_CC;
#pragma region init singleton
PluginManager* PluginManager::s_instance = nullptr;

PluginManager::PluginManager()
{
	facebookController = new FacebookController();
	iapController = new IAPController();
	adcolonyController = new AdcolonyController();
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
	
}