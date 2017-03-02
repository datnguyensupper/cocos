#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	layer->setPhysicWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	this->scheduleOnce(schedule_selector(GameScene::createWorldBounds), 0.0f);
	//createWorldBounds();

    return true;
}

void GameScene::createWorldBounds(float dt) {


	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	edgeBody->setCollisionBitmask(BOUND_COLLISION_BITMASK);
	edgeBody->setContactTestBitmask(true);
	edgeBody->setDynamic(false);

	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	this->addChild(edgeNode);

	auto stringBody = PhysicsBody::createEdgeBox(Size(5,200), PHYSICSBODY_MATERIAL_DEFAULT, 1);
	stringBody->setCollisionBitmask(BOUND_COLLISION_BITMASK);
	stringBody->setContactTestBitmask(true);
	stringBody->setDynamic(false);
	auto string = Node::create();
	string->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+100));
	string->setPhysicsBody(stringBody);

	this->addChild(string);

	auto ballBody = PhysicsBody::createCircle(50, PHYSICSBODY_MATERIAL_DEFAULT);
	ballBody->setCollisionBitmask(BOUND_COLLISION_BITMASK);
	ballBody->setContactTestBitmask(true);
	ballBody->setDynamic(true);
	auto ball = Sprite::create("CloseNormal.png");
	ball->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y-50));
	ball->setPhysicsBody(ballBody);

	PhysicsJoint *co = PhysicsJointSpring::construct(stringBody,
		ballBody, Vec2(0.5, 0.5), Vec2(0.5, 0.5),100,100);

	physicWorld->addJoint(co);

	this->addChild(ball);

}

