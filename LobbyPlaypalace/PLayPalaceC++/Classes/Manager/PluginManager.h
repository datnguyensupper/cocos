#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-01
* file: PluginManager.h, PluginManager.cpp
*/

#include "cocos2d.h"
#include "Plugins/FacebookController.h"
#include "Plugins/IAPController.h"
#include "Plugins/GamePlugin.h"
#include "Plugins/ImagePicker/ImagePicker.h"
#include "Plugins/AdvertiseController.h"

class PluginManager
{
private:
	PluginManager();
	static PluginManager* s_instance;

	FacebookController* facebookController;
	IAPController* iapController;
	AdvertiseController* advertiseController;
	GamePlugin* gamePlugin;
	cocos2d::ImagePicker* imagePickerController;
public:
	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static PluginManager* getInstance();

	/**
	* 2017-02-27: Kiet: destructor
	*/
	~PluginManager();


	/**
	* 2017-03-01: Kiet: get facebook controller
	*/
	FacebookController* getFacebookController() {
		return this->facebookController;
	}
	/**
	* 2017-03-01: Kiet: get iap controller
	*/
	IAPController* getIAPController() {
		return this->iapController;
	}
	/**
	* get Vungle Controller
	*/
	AdvertiseController* getAdvertiseController() {
		return this->advertiseController;
	}

	/**
	* get game plugin
	*/
	GamePlugin* getGamePlugin() {
		return this->gamePlugin;
	}
	/**
	* 2017-03-15: Kiet: get image picker controller
	*/
	cocos2d::ImagePicker* getImagePickerController() {
		return this->imagePickerController;
	}
};