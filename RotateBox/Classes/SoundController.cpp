#include "SoundController.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"  
#include "ToggleButton.h"



USING_NS_CC;

SoundController::SoundController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();


	UserDefault * def = UserDefault::getInstance();
	canPlaySound = def->getBoolForKey(CACHE_CAN_PLAY_MUSIC, true);

}


void SoundController::PlayBackgroundMusic() {

	if (!canPlaySound) {
		return;
	}
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
		"sounds/background_music.mp3", true);

}

void SoundController::PlaySound(const char* pszFilePath) {

	if (!canPlaySound) {
		return;
	}

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect(
		pszFilePath, false);

}

void SoundController::PlayCoinSound() {

	PlaySound("sounds/point.mp3");

}

void SoundController::PlayLooseSound() {

	PlaySound("sounds/die.mp3");

}

void SoundController::toggleOnOffSound(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType) {
	if (touchType == cocos2d::ui::Widget::TouchEventType::BEGAN) {
		if (static_cast<ToggleButton *>(sender)->isToggle()) {
			//log("OFF");
			canPlaySound = false;
			CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
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

void SoundController::CreateSoundControl(cocos2d::Layer * layer) {
	//CCLOG("show popup game over");

		

	// layer
	auto soundControlUI = Layer::create();
	ToggleButton * soundBtn = ToggleButton::create("sound_on.png","sound_off.png", "sound_on.png", "sound_off.png");
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

	soundControlUI->setPosition(Vec2(100,100));

	layer->addChild(soundControlUI, 100);
}