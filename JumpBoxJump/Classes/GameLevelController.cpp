#include "GameLevelController.h"
#include "Definitions.h"
//#include "Helper.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"


USING_NS_CC;

GameLevelController::GameLevelController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
void GameLevelController::createGameLevels(){
	createGameLevelsSPIKE();
	createGameLevelsGOBACK();
	// set up first 4 level
	gameLevels = gameLevelsRandom;
	/*gameLevels.push_back(gameLevelsRandom[0]);
	gameLevels.push_back(gameLevelsRandom[1]);
	gameLevels.push_back(gameLevelsRandom[2]);
	gameLevels.push_back(gameLevelsRandom[3]);*/
}
void GameLevelController::setFloor(int _floorX, std::vector<int> &_floorY) {
	floorX = _floorX;
	floorY = _floorY;
}

void GameLevelController::createGameLevelsSPIKE() {

	//std::vector<std::vector<Barrier>> gameLevelsRandom;
	std::vector<Barrier> level;
	Barrier barrier;

	//floor 0
	level = std::vector<Barrier>();
	barrier = { 60,30,200,SPIKE };
	level.push_back(barrier);
	barrier = { 60,30,400,SPIKE };
	level.push_back(barrier);
	barrier = { 60,30,600,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 1
	level = std::vector<Barrier>();
	barrier = { 70,25,350,SPIKE };
	level.push_back(barrier);
	barrier = { 30,20,100,SPIKE };
	level.push_back(barrier);
	barrier = { 40,30,700,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 2
	level = std::vector<Barrier>();
	barrier = { 10,35,150,SPIKE };
	level.push_back(barrier);
	barrier = { 10,35,400,SPIKE };
	level.push_back(barrier);
	barrier = { 10,35,650,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 3
	level = std::vector<Barrier>();
	barrier = { 80,10,280,SPIKE };
	level.push_back(barrier);
	barrier = { 80,10,480,SPIKE };
	level.push_back(barrier);
	barrier = { 80,10,960,SPIKE };
	level.push_back(barrier);
	barrier = { 80,10,1160,SPIKE };
	level.push_back(barrier);
	barrier = { 80,10,1440,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 4
	level = std::vector<Barrier>();
	barrier = { 10,10,100,SPIKE };
	level.push_back(barrier);
	barrier = { 10,10,200,SPIKE };
	level.push_back(barrier);
	barrier = { 10,10,300,SPIKE };
	level.push_back(barrier);
	barrier = { 10,10,400,SPIKE };
	level.push_back(barrier);
	barrier = { 10,10,500,SPIKE };
	level.push_back(barrier);
	barrier = { 10,10,600,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 5
	level = std::vector<Barrier>();
	barrier = { 10,40,200,SPIKE };
	level.push_back(barrier);
	barrier = { 10,40,400,SPIKE };
	level.push_back(barrier);
	barrier = { 10,40,600,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

}

void GameLevelController::createGameLevelsGOBACK() {

	//std::vector<std::vector<Barrier>> gameLevelsRandom;
	std::vector<Barrier> level;
	Barrier barrier;

	//floor 6
	level = std::vector<Barrier>();
	barrier = { 60,30,200,GOBACK };
	level.push_back(barrier);
	barrier = { 60,30,400,GOBACK };
	level.push_back(barrier);
	barrier = { 60,30,600,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 7
	level = std::vector<Barrier>();
	barrier = { 70,25,350,GOBACK };
	level.push_back(barrier);
	barrier = { 30,20,100,GOBACK };
	level.push_back(barrier);
	barrier = { 40,30,700,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 8
	level = std::vector<Barrier>();
	barrier = { 10,35,150,GOBACK };
	level.push_back(barrier);
	barrier = { 10,35,400,GOBACK };
	level.push_back(barrier);
	barrier = { 10,35,650,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 9
	level = std::vector<Barrier>();
	barrier = { 80,10,280,GOBACK };
	level.push_back(barrier);
	barrier = { 80,10,480,GOBACK };
	level.push_back(barrier);
	barrier = { 80,10,960,GOBACK };
	level.push_back(barrier);
	barrier = { 80,10,1160,GOBACK };
	level.push_back(barrier);
	barrier = { 80,10,1440,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 10
	level = std::vector<Barrier>();
	barrier = { 10,10,100,GOBACK };
	level.push_back(barrier);
	barrier = { 10,10,200,GOBACK };
	level.push_back(barrier);
	barrier = { 10,10,300,GOBACK };
	level.push_back(barrier);
	barrier = { 10,10,400,GOBACK };
	level.push_back(barrier);
	barrier = { 10,10,500,GOBACK };
	level.push_back(barrier);
	barrier = { 10,10,600,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 11
	level = std::vector<Barrier>();
	barrier = { 10,40,200,GOBACK };
	level.push_back(barrier);
	barrier = { 10,40,400,GOBACK };
	level.push_back(barrier);
	barrier = { 10,40,600,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 12
	level = std::vector<Barrier>();
	barrier = { 60,30,200,SPIKE };
	level.push_back(barrier);
	barrier = { 60,30,400,GOBACK };
	level.push_back(barrier);
	barrier = { 60,30,600,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 13
	level = std::vector<Barrier>();
	barrier = { 30,20,100,SPIKE };
	level.push_back(barrier);
	barrier = { 70,25,350,SPIKE };
	level.push_back(barrier);
	barrier = { 40,30,700,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 14
	level = std::vector<Barrier>();
	barrier = { 10,35,150,GOBACK };
	level.push_back(barrier);
	barrier = { 10,35,400,SPIKE };
	level.push_back(barrier);
	barrier = { 10,35,650,SPIKE };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

	//floor 15
	level = std::vector<Barrier>();
	barrier = { 10,40,200,SPIKE };
	level.push_back(barrier);
	barrier = { 10,40,400,SPIKE };
	level.push_back(barrier);
	barrier = { 10,40,600,GOBACK };
	level.push_back(barrier);
	gameLevelsRandom.push_back(level);

}

cocos2d::Node* GameLevelController::createFloor(int floor, cocos2d::Node * parent) {
	return createFloor(floor, gameLevels[floor], parent);
}
cocos2d::Node* GameLevelController::createFloorRandom(int floor, cocos2d::Node * parent) {
	int floorLevelID = cocos2d::random(0, static_cast<int>(gameLevelsRandom.size() - 1));
	return createFloor(floor, gameLevelsRandom[floorLevelID], parent);
}

cocos2d::Node* GameLevelController::createFloor(int floor, std::vector<Barrier> floorLevelWall, cocos2d::Node * parent) {

	Node *groupSpikeOfThisLevel = Node::create();
	for (int i = 0; i < floorLevelWall.size(); i++) {

		createObstacleWithType(floorLevelWall[i], groupSpikeOfThisLevel, floor);
		//__String * scoreStr = __String::createWithFormat("%i", cocos2d::random(0,1000));
		//this->scheduleOnce([=](float dt) {
		//
		//}, 0, scoreStr->getCString());

	}
	parent->addChild(groupSpikeOfThisLevel, 2);
	return groupSpikeOfThisLevel;

}

void GameLevelController::createObstacleWithType(Barrier barrier, cocos2d::Node* parent, int floor) {
	//barrier.type = GOBACK;
	switch (barrier.type)
	{
	case ObstacleType::SPIKE: {
		auto spike = Sprite::create("sprites/pattern4.png");
		spike->setAnchorPoint(Vec2(0.5, 0));
		spike->setContentSize(Size(barrier.width, barrier.height));
		spike->setPosition(Vec2(
			floorX + barrier.x,
			visibleSize.height - floorY[floor]));
		parent->addChild(spike, 2);

		//create count point
		auto coinPoint = Node::create();
		coinPoint->setPosition(Vec2(spike->getPosition().x, spike->getPosition().y + spike->getContentSize().height + 25));
		parent->addChild(coinPoint);

		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
			auto spikeBody = PhysicsBody::createBox(Size(
				//floor->getContentSize().width-100, 
				spike->getContentSize().width,
				spike->getContentSize().height),
				PhysicsMaterial(0.0f, 0.0f, 0.0f));
			spikeBody->setDynamic(false);
			spikeBody->setContactTestBitmask(true);
			spikeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
			spike->setPhysicsBody(spikeBody);

			auto coinPointBody = PhysicsBody::createBox(Size(
				//floor->getContentSize().width-100, 
				4,
				50),
				PhysicsMaterial(0.0f, 0.0f, 0.0f));
			coinPointBody->setDynamic(false);
			coinPointBody->setContactTestBitmask(true);
			coinPointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
			coinPoint->setPhysicsBody(coinPointBody);

		});
		break;
	}
	case ObstacleType::GOBACK: {
		auto particleGoback = ParticleSystemQuad::create("sprites/particle_goback.plist");
		particleGoback->setPosition(
			floorX + barrier.x,
			visibleSize.height - floorY[floor] + 20);
		particleGoback->setTexture(TextureCache::sharedTextureCache()->addImage("sprites/particle_goback.png"));
		parent->addChild(particleGoback);

		//create count point
		auto coinPoint = Node::create();
		coinPoint->setPosition(Vec2(particleGoback->getPosition().x, particleGoback->getPosition().y + 45));
		parent->addChild(coinPoint);

		Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]() {
			auto spikeBody = PhysicsBody::createBox(Size(
				//floor->getContentSize().width-100, 
				10,
				40),
				PhysicsMaterial(0.0f, 0.0f, 0.0f));
			spikeBody->setDynamic(false);
			spikeBody->setContactTestBitmask(true);
			spikeBody->setCollisionBitmask(OBSTACLE_GOBACK_COLLISION_BITMASK);
			particleGoback->setPhysicsBody(spikeBody);

			auto coinPointBody = PhysicsBody::createBox(Size(
				//floor->getContentSize().width-100, 
				4,
				50),
				PhysicsMaterial(0.0f, 0.0f, 0.0f));
			coinPointBody->setDynamic(false);
			coinPointBody->setContactTestBitmask(true);
			coinPointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
			coinPoint->setPhysicsBody(coinPointBody);

		});
		break;
	}
	default:
		break;
	}
}

