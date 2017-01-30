#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"
#include "Definitions.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Hit.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Point.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sounds/Wing.mp3");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleOnce(schedule_selector(SplashScene::GoToMainmenuScene), DISPLAY_TIME_SPLASH_SCREEN);
    
	auto backgroundSprite = Sprite::create("Splash Screen.png");
	backgroundSprite->setPosition(Point(visibleSize.width/2 + origin.x ,
		visibleSize.height/2+origin.y));

	this->addChild(backgroundSprite);

    return true;
}

void SplashScene::GoToMainmenuScene(float dt) {
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
