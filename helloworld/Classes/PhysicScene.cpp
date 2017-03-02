#include "PhysicScene.h"
#include "SimpleAudioEngine.h"
#include "MyBodyParser.h"

USING_NS_CC;

Scene* PhysicScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    // 'layer' is an autorelease object
    auto layer = PhysicScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PhysicScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);
	/*{

		auto sprite = Sprite::create("CloseNormal.png");
		sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 1, 0));
		spriteBody->setCollisionBitmask(1);
		spriteBody->setContactTestBitmask(true);

		sprite->setPhysicsBody(spriteBody);

		this->addChild(sprite);
	}*/
	{

		auto sprite = Sprite::create("Paddle.png");
		sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+200));

		MyBodyParser::getInstance()->parseJsonFile("Paddle");
		auto spriteBody = MyBodyParser::getInstance()->bodyFormJson(sprite, "Paddle", PhysicsMaterial(1, 1, 0));
		if (spriteBody != nullptr) {
			//spriteBody->setDynamic(false);
			sprite->setPhysicsBody(spriteBody);
		}
		//auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(), PhysicsMaterial(0, 1, 0));
		////spriteBody->setCollisionBitmask(2);
		////spriteBody->setContactTestBitmask(true);
		//sprite->setPhysicsBody(spriteBody);

		//spriteBody->setAngularVelocity(400);

		this->addChild(sprite);
	}

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicScene::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener,this);
    return true;
}

bool PhysicScene::onContactBegin(cocos2d::PhysicsContact & contact) {
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	// check if the bodies have collide
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) ||
		(2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask())) {
		CCLOG("COLLISTION HAS OCCURED");
	}
	return true;
}