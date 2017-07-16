#pragma once
#include "cocos2d.h"
#include "Advertise/AdcolonyController.h"
#include "Advertise/PluginVungleController.h"
#include "cocos2d.h"

class AdvertiseController
{
private:
	AdcolonyController* adcolony;
	PluginVungleController* vungle;
public:
	AdvertiseController();
	~AdvertiseController();
	void init();
	bool isShowable();
	void showVideo(const std::function<void(int amount, bool isSuccess)>& cb);
};