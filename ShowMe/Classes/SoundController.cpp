#include "SoundController.h"
#include "Definitions.h"
#include "ToggleButton.h"



USING_NS_CC;

#pragma region init singleton
SoundController* SoundController::s_instance = nullptr;

SoundController* SoundController::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new SoundController();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();

	return s_instance;
}
#pragma endregion

SoundController::SoundController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();


	UserDefault * def = UserDefault::getInstance();
	canPlaySound = def->getBoolForKey(CACHE_CAN_PLAY_MUSIC, true);

	audio = CocosDenshion::SimpleAudioEngine::sharedEngine();

	audio->playBackgroundMusic(
		"sounds/background_music.mp3", true);
	audio->pauseBackgroundMusic();
	/*audio->preloadEffect("sounds/die.mp3");
	audio->preloadEffect("sounds/Jump.mp3");
	audio->preloadEffect("sounds/point.mp3");*/


}


void SoundController::PlayBackgroundMusic() {

	if (!canPlaySound) {
		return;
	}
	audio->resumeBackgroundMusic();

}


void SoundController::StopBackgroundMusic() {

	audio->pauseBackgroundMusic();

}

void SoundController::PlaySound(const char* pszFilePath) {

	if (!canPlaySound) {
		return;
	}

	audio->playEffect(
		pszFilePath, false);

}

void SoundController::PlayCoinSound() {

	PlaySound("sounds/point.mp3");

}

void SoundController::PlayLooseSound() {

	PlaySound("sounds/die.mp3");

}

void SoundController::PlayJumpSound() {
	//return;
	PlaySound("sounds/Jump.mp3");
}

void SoundController::toggleOnOffSound(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType) {
	if (touchType == cocos2d::ui::Widget::TouchEventType::BEGAN) {
		if (static_cast<ToggleButton *>(sender)->isToggle()) {
			//log("OFF");
			canPlaySound = false;
			StopBackgroundMusic();
		}
		else {
			//log("ON");
			canPlaySound = true;
			PlayBackgroundMusic();
		}
		UserDefault * def = UserDefault::getInstance();
		def->setBoolForKey(CACHE_CAN_PLAY_MUSIC, canPlaySound);
		def->flush();
	}
}

cocos2d::Layer* SoundController::CreateSoundControl(cocos2d::Layer * layer) {
	//CCLOG("show popup game over");

		

	// layer
	auto soundControlUI = Layer::create();
	ToggleButton * soundBtn = ToggleButton::create("play_bg.png","mute_bg.png", "play_bg.png", "mute_bg.png");
	soundBtn->addTouchEventListener(
		CC_CALLBACK_2(SoundController::toggleOnOffSound, this));

	if (!canPlaySound) {
		soundBtn->setToggle(true);
	}


	//auto playBtn = ui::Button::create("sound_on.png",
	//	"sound_on.png");
	//playBtn->setScale(1.5);
	//playBtn->setPosition(Vec2(0, -bg->getContentSize().height / 1.5));
	////playBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::restartGame, static_cast<GameScene *>(layer)));
	soundControlUI->addChild(soundBtn);

	soundControlUI->setPosition(Vec2(40,visibleSize.height-20));

	layer->addChild(soundControlUI, 100);
    
    return soundControlUI;
}
