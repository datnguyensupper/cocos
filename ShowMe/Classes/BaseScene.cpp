#include "BaseScene.h"
#include "LevelOneScene.h"
#include "SplashScene.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool BaseScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    return true;
}

void BaseScene::Go2LevelOneScene(float dt) {
	auto scene = LevelOneScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void BaseScene::prepare2Go2LevelOneScene() {
	scheduleOnce(schedule_selector(BaseScene::Go2LevelOneScene), DISPLAY_TIME_GAME_SCREEN);
}

void BaseScene::Go2SplashScene(float dt) {
	auto scene = SplashScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void BaseScene::prepare2Go2SplashScene() {
	scheduleOnce(schedule_selector(BaseScene::Go2SplashScene), DISPLAY_TIME_SPLASH_SCREEN);
}
