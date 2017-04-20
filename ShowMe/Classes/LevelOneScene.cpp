#include "LevelOneScene.h"


USING_NS_CC;

Scene* LevelOneScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 100));

	// 'layer' is an autorelease object
	auto layer = LevelOneScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool LevelOneScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !BaseScene::init() )
    {
        return false;
    }
    
    ninePath = cocos2d::ui::Scale9Sprite::create("CloseNormal.png", cocos2d::Rect::ZERO, Rect(10, 10, 20, 20));
    ninePath->setScale9Enabled(true);
    ninePath->setContentSize(Size(300,40));
//    ninePath->setScaleX(5);
    ninePath->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    ninePath->setAnchorPoint(Vec2(0.5, 0.5));
    addChild(ninePath);
    
	auto label = Label::createWithSystemFont("LevelOneScene", "Arial", 30);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(label);

	createPlayer();
    
    
    this->scheduleUpdate();

    return true;
}



void LevelOneScene::update(float delta){
    
    Vec2 pos = Vec2(player->getPositionX(), player->getPositionY());
    auto cam = Camera::getDefaultCamera();
//    cam->setPosition(pos);
}


void LevelOneScene::createPlayer() {

	player = Sprite::create("CloseNormal.png");
	player->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	player->setAnchorPoint(Vec2(0.5, 0));
	player->setColor(Color3B::RED);
	//playerRed->setScaleX(2);
	auto playerBodyRed = PhysicsBody::createBox(Size(player->getContentSize().width, player->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//playerBodyRed->setPositionOffset(Vec2(0, playerRed->getContentSize().height/4));
	//set the body isn't affected by the physics world's gravitational force
	playerBodyRed->setGravityEnable(true);
	playerBodyRed->setDynamic(true);
	playerBodyRed->setCollisionBitmask(PLAYER_COLLISION_BITMASK_RED);
	playerBodyRed->setContactTestBitmask(true);
	player->setPhysicsBody(playerBodyRed);
	//playerRed->addComponent(playerBodyRed);
	addChild(player);
    
    
}


