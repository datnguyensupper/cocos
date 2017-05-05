#include "LevelOneScene.h"
#include "SpritePath.h"
#include "Controller4Score.h"

USING_NS_CC;

Scene* LevelOneScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 50));
	//scene->getPhysicsWorld()->setGravity(Vect(0, 100));
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

	Controller4Score::getInstance()->setCurrentScore(0);

	createPlayer();
	handleTouchInput();
	handlePhysicEvent();

	spritePath = SpritePath::create(player);
	addChild(spritePath);
    
    this->scheduleUpdate();
	this->schedule(schedule_selector(LevelOneScene::spawnEnemy), 10.0f);

    return true;
}

void LevelOneScene::handlePhysicEvent() {

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(LevelOneScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(LevelOneScene::onContactSeparate, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}


void LevelOneScene::spawnEnemy(float delta) {
	if (isDied) return;
	enemyController.SpawnEnemy(this, player, 0);
}

void LevelOneScene::update(float delta){
	//return;
	if (isDied) return;

	delayTime += delta;
	if (delayTime < 1.0) return;

    Vec2 pos = player->getPosition();
	pos.x = player->getPhysicsBody()->getPosition().x;
	if (pos.x < 0 || pos.x > visibleSize.width) doDead();
	
    auto cam = Camera::getDefaultCamera();
	//log("Player position x=%f y=%f physic x=%f y=%f", pos.x, pos.y,player->getPhysicsBody()->getPosition().x,player->getPhysicsBody()->getPosition().y);
	log("Player velocity x=%f y=%f",player->getPhysicsBody()->getVelocity().x,player->getPhysicsBody()->getVelocity().y);
	if (player->getPhysicsBody()->getVelocity().y < 10) deadSpace += 1;
	pos.x = visibleSize.width / 2;
	if (deadSpace > visibleSize.height / 2) doDead();
    cam->setPosition(pos + Vec2(0,deadSpace));

	Controller4Score::getInstance()->setCurrentScore(pos.y - playerFirstPosition.y);
}


void LevelOneScene::createPlayer() {

	player = Sprite::create("CloseNormal.png");
	playerFirstPosition = Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	player->setPosition(playerFirstPosition);
	playerFirstPosition.x /= 2.0;
	//playerFirstPosition.x = 0;
	player->setAnchorPoint(Vec2(0.5, 0.5));
	player->setColor(Color3B::BLUE);
	//playerRed->setScaleX(2);
	auto playerBody = PhysicsBody::createCircle(player->getContentSize().width/2,PhysicsMaterial(1.0f, 1.0f, 1.0f));
	//playerBodyRed->setPositionOffset(Vec2(0, playerRed->getContentSize().height/4));
	//set the body isn't affected by the physics world's gravitational force
	playerBody->setRotationEnable(false);
	playerBody->setGravityEnable(true);
	playerBody->setDynamic(true);
	playerBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK);
	playerBody->setContactTestBitmask(true);
	playerBody->setVelocityLimit(100);
	player->setPhysicsBody(playerBody);
	
	//playerRed->addComponent(playerBodyRed);
	addChild(player);
    
}

void LevelOneScene::handleTouchInput() {
	//Create a "one by one" touch event listener (processes one touch at a time)
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	// Example of using a lambda expression to implement onTouchBegan event callback function
	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		if (isDied) return false;
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		Point locationInNode = touch->getLocation();
		//CCLOG("pos x:%f y:%f", locationInNode.x, locationInNode.y);
		//label->setPosition(touch->getLocation() - Vec2(0, visibleSize.height / 4 + origin.y));
		Point playerPosition = player->getPosition();
		playerPosition.x = 0;
		Point translate = playerPosition - Vec2(0, playerFirstPosition.y) + Vec2(0, deadSpace);
		spritePath->adjustSprite(locationInNode + translate, locationInNode + translate);

		spritePath->removePhysic();
		return true;
	};

	//Trigger when moving touch
	listener1->onTouchMoved = [this](Touch* touch, Event* event) {
		if (isDied) return;
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		//Move the position of current button sprite
		//target->setPosition(target->getPosition() + touch->getDelta());
		Point locationInNode = touch->getLocation();
		Point playerPosition = player->getPosition();
		playerPosition.x = 0;
		Point translate = playerPosition - Vec2(0, playerFirstPosition.y) + Vec2(0, deadSpace);
		spritePath->adjustSprite(locationInNode + translate);
	};

	//Process the touch end event
	listener1->onTouchEnded = [=](Touch* touch, Event* event) {
		if (isDied) return;
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		/*Point locationInNode = touch->getLocation();
		Point playerPosition = player->getPosition();
		Point translate = playerPosition - 2 * playerFirstPosition;*/
		//spritePath->adjustSprite(locationInNode + translate);
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void LevelOneScene::doDead() {
	if (isDied) return;
	isDied = true;
	prepare2Go2SplashScene();
}

bool LevelOneScene::onContactBegin(cocos2d::PhysicsContact & contact) {

	if (isDied) {
		return false;
	}
	PhysicsBody * a = contact.getShapeA()->getBody();
	PhysicsBody * b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() > b->getCollisionBitmask()) {
		a = contact.getShapeB()->getBody();
		b = contact.getShapeA()->getBody();
	}
	cocos2d::log("a mask : %i; b mask : %i", a->getCollisionBitmask(),b->getCollisionBitmask());
	if (a->getCollisionBitmask() == PLAYER_COLLISION_BITMASK &&
		b->getCollisionBitmask() == ENEMY_COLLISION_BITMASK) {
		// do dead
		doDead();
		return false;
	}else if (a->getCollisionBitmask() == BOUND_COLLISION_BITMASK &&
		b->getCollisionBitmask() == ENEMY_COLLISION_BITMASK) {
		return false;
	}

	return true;
}

void LevelOneScene::onContactSeparate(cocos2d::PhysicsContact & contact) {
}

