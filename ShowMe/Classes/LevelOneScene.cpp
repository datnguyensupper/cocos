#include "LevelOneScene.h"
#include "SpritePath.h"


USING_NS_CC;

Scene* LevelOneScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 100));
	//scene->getPhysicsWorld()->setGravity(Vect(0, 0));

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
	this->schedule(schedule_selector(LevelOneScene::spawnEnemy), 10.0f);

    return true;
}


void LevelOneScene::spawnEnemy(float delta) {
	enemyController.SpawnEnemy(this, player, 0);
}

void LevelOneScene::update(float delta){
    
    Vec2 pos = player->getPosition();
	if (pos.x < 0) {
		pos.x = 0;
		player->setPosition(pos);
	}else if (pos.x > visibleSize.width / 2) {
		pos.x = visibleSize.width;
		player->setPosition(pos);
	}
    auto cam = Camera::getDefaultCamera();
    cam->setPosition(pos);
}


void LevelOneScene::createPlayer() {

	player = Sprite::create("CloseNormal.png");
	playerFirstPosition = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 + origin.y);
	player->setPosition(playerFirstPosition);
	playerFirstPosition.x /= 2.0;
	//playerFirstPosition.x = 0;
	player->setAnchorPoint(Vec2(0.5, 0));
	player->setColor(Color3B::BLUE);
	//playerRed->setScaleX(2);
	auto playerBodyRed = PhysicsBody::createCircle(player->getContentSize().width/2,PhysicsMaterial(0.1f, 0.0f, 0.0f));
	//playerBodyRed->setPositionOffset(Vec2(0, playerRed->getContentSize().height/4));
	//set the body isn't affected by the physics world's gravitational force
	playerBodyRed->setRotationEnable(false);
	playerBodyRed->setGravityEnable(true);
	playerBodyRed->setDynamic(true);
	playerBodyRed->setCollisionBitmask(PLAYER_COLLISION_BITMASK_RED);
	playerBodyRed->setContactTestBitmask(true);
	playerBodyRed->setVelocityLimit(100);
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
		Point playerPosition = player->getPosition();
		Point translate = playerPosition - 2 * playerFirstPosition;
		spritePath->adjustSprite(locationInNode + translate, locationInNode + translate);

		spritePath->removePhysic();
		return true;
	};

	//Trigger when moving touch
	listener1->onTouchMoved = [this](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//Move the position of current button sprite
		//target->setPosition(target->getPosition() + touch->getDelta());
		Point locationInNode = touch->getLocation();
		//label->setPosition(touch->getLocation() - Vec2(0, visibleSize.height / 4 + origin.y));
		Point playerPosition = player->getPosition();
		Point translate = playerPosition - 2 * playerFirstPosition;
		spritePath->adjustSprite(locationInNode + translate);
		//CCLOG("translate x:%i y:%i", translate.x, translate.y);
	};

	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//spritePath->updatePhysic();
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

