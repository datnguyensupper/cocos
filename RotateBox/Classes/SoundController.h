#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"


class SoundController
{
public:
	SoundController();

	void PlayBackgroundMusic();
	void SoundController::PlayCoinSound();
	void SoundController::PlayLooseSound();
	void SoundController::CreateSoundControl(cocos2d::Layer * layer);
private:
	void PlaySound(const char* pszFilePath);
	void toggleOnOffSound(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	bool canPlaySound;

};
