#include "CoinAnimationTestScene.h"
#include "Manager/SoundManager.h"
#include "Constant/Defination.h"
#include "Configs.h"
#include "Helper/AnimationHelper.h"
#include "Manager/AnimationManager.h"

USING_NS_CC;
Scene* CoinAnimationTestScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = BaseScene::create();
    scene->setTag(ppEnum::GameScene::Lobby);
    
    // 'layer' is an autorelease object
    auto layer = CoinAnimationTestScene::create();
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return (Scene*)scene;
}

// on "init" you need to initialize your instance
bool CoinAnimationTestScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseScene::init() )
    {
        return false;
    }

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/*test:know what your scene*/
	auto label = Label::createWithSystemFont("COIN ANIMATION TEST SCENE", "Arial", 96);
	label->setColor(Color3B::BLUE);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(label, 1);

	/*test:Play background music*/
	SoundManager::getInstance()->stopBackgroundMusic();

	AnimationManager::getInstance()->playCoinAnimation(Vec2(0,0),Vec2(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y),this);

    return true;
}
