#include "SplashScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "CLoader.h"

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
    
	auto bg = Sprite::create("tutorial.jpg");
	bg->setPosition(label->getPosition());
	this->addChild(bg);

	//auto partical = ParticleGalaxy::create();
	auto partical = ParticleFire::create();
	partical->setPosition(Vec2(visibleSize.width / 2 + origin.x + 520, visibleSize.height / 2 + origin.y-20));
	this->addChild(partical);

	auto particalSnow = ParticleSnow::create();
	
	Color4F startColor = Color4F(66.0/255, 203.0/255, 244.0/255, 1);
	particalSnow->setStartColor(startColor);
	particalSnow->setEmissionRate(10);
	particalSnow->setSpeed(20);
	particalSnow->setGravity(Vec2(0, -70));
	particalSnow->setEndColor(Color4F::WHITE);
	particalSnow->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height + origin.y));
	this->addChild(particalSnow);

	

	btn_play = Sprite::create("play_btn.png");
	btn_play->setPosition(Vec2(1331, 460));
	this->addChild(btn_play);

	btn_play->runAction(cocos2d::TintTo::create(2.0, 255, 0, 0));
	//[btn_play runAction : [CCTintTo actionWithDuration : 2 red : 255 green : 0 blue : 0]];

	// Add a "touch" event listener to our sprite
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event)->bool {
		event->getCurrentTarget()->scheduleOnce(schedule_selector(SplashScene::GoToGameScene), DISPLAY_TIME_SPLASH_SCREEN);
		return true;
	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	loadRS();

	//start timer
	this->schedule(schedule_selector(SplashScene::UpdateTimer), 2.0f);

    return true;
}

void SplashScene::loadRS(){
	std::vector<string> resources = {
	"gameover/fbshare.png",
	"gameover/gameOver.png",
	"gameover/middle.jpg",
	"gameover/play-btn.png",
	"difficultLevel.png",
	"difficultLevelBg.png",
	"emeny_blue.jpg",
	"enemy_red.jpg",
	"player.jpg",
	"shiny_spawn.jpg",
	
	};
	CLoader::getInstance()->startLoadingResources(resources,
		[]() {},
		[](float progress) {});
}

void SplashScene::UpdateTimer(float dt)
{
	auto red = cocos2d::random(0, 255);
	auto green = cocos2d::random(0, 255);
	auto blue = cocos2d::random(0, 255);
	btn_play->runAction(cocos2d::TintTo::create(2.0, red, green, blue));
}

void SplashScene::GoToGameScene(float dt) {
	//stop time
	this->unschedule(schedule_selector(SplashScene::UpdateTimer));

	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}
