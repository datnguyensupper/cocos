#include "SplashScene.h"
#include "Definitions.h"
#include "GameScene.h"

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithSystemFont("Splash Scene", "Arial", 30);
	label->setPosition(Vec2(visibleSize.width/2+origin.x, visibleSize.height/2+origin.y));
	this->addChild(label);
    
	this->scheduleOnce(schedule_selector(SplashScene::GoToGameScene), DISPLAY_TIME_SPLASH_SCREEN);

    return true;
}

void SplashScene::GoToGameScene(float dt) {
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
