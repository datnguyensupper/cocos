#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"  


class SoundController
{
public:
	static SoundController* getInstance();


	void PlayBackgroundMusic();
	void StopBackgroundMusic();
	void PlayCoinSound();
	void PlayLooseSound();
	void PlayJumpSound();
	cocos2d::Layer* CreateSoundControl(cocos2d::Layer * layer);
private:

	SoundController();
	static SoundController* s_instance;

	void PlaySound(const char* pszFilePath);
	void toggleOnOffSound(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	bool canPlaySound;
	CocosDenshion::SimpleAudioEngine* audio;

};
