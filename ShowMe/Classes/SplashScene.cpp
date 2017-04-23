#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Controller4Score.h"

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
    if ( !BaseScene::init() ) return false;

	Controller4Score::getInstance()->updateMaxScore();

	auto label = Label::createWithSystemFont("Splash Scene", "Arial", 30);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(label);
    
	
	auto playBtn = ui::Button::create("CloseNormal.png");
	playBtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	playBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type) {
		if (type != ui::Widget::TouchEventType::ENDED) return;
		scheduleOnce(schedule_selector(SplashScene::Go2LevelOneScene), DISPLAY_TIME_SPLASH_SCREEN);
	});
	addChild(playBtn);

    return true;
}


