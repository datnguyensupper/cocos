#include "LevelOneScene.h"
#include "SpritePath.h"


USING_NS_CC;

Scene* LevelOneScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

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
    
    
    
	label = Label::createWithSystemFont("LevelOneScene", "Arial", 30);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(label);


	createPlayer();
	handleTouchInput();
    
	spritePath = SpritePath::create();
	addChild(spritePath);
    
    this->scheduleUpdate();

    return true;
}



void LevelOneScene::update(float delta){
    
    Vec2 pos = Vec2(player->getPositionX(), player->getPositionY());
    auto cam = Camera::getDefaultCamera();
    cam->setPosition(pos);
}


void LevelOneScene::createPlayer() {

	player = Sprite::create("CloseNormal.png");
	playerFirstPosition = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y);
	player->setPosition(playerFirstPosition);
	playerFirstPosition.x = 0;
	player->setAnchorPoint(Vec2(0.5, 0));
	player->setColor(Color3B::RED);
	//playerRed->setScaleX(2);
	auto playerBodyRed = PhysicsBody::createBox(Size(player->getContentSize().width, player->getContentSize().height),
		PhysicsMaterial(0.1f, 0.0f, 0.0f));
	//playerBodyRed->setPositionOffset(Vec2(0, playerRed->getContentSize().height/4));
	//set the body isn't affected by the physics world's gravitational force
	playerBodyRed->setGravityEnable(true);
	playerBodyRed->setDynamic(true);
	playerBodyRed->setCollisionBitmask(PLAYER_COLLISION_BITMASK_RED);
	playerBodyRed->setContactTestBitmask(true);
	//playerBodyRed->setVelocity(Vec2(0, 500));
	player->setPhysicsBody(playerBodyRed);
	
	//playerRed->addComponent(playerBodyRed);
	addChild(player);
    
}

void LevelOneScene::handleTouchInput() {
	//Create a "one by one" touch event listener (processes one touch at a time)
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	// Example of using a lambda expression to implement onTouchBegan event callback function
	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = touch->getLocation();
		CCLOG("pos x:%f y:%f", locationInNode.x, locationInNode.y);
		//label->setPosition(touch->getLocation() - Vec2(0, visibleSize.height / 4 + origin.y));
		spritePath->adjustSprite(locationInNode- playerFirstPosition, locationInNode- playerFirstPosition);
		return true;
	};

	//Trigger when moving touch
	listener1->onTouchMoved = [this](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//Move the position of current button sprite
		//target->setPosition(target->getPosition() + touch->getDelta());
		Point locationInNode = touch->getLocation();
		//label->setPosition(touch->getLocation() - Vec2(0, visibleSize.height / 4 + origin.y));
		spritePath->adjustSprite(locationInNode- playerFirstPosition);
		//CCLOG("translate x:%i y:%i", translate.x, translate.y);
	};

	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

