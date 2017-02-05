#include "EnemyController.h"
#include "Definitions.h"
#include "Helper.h"

USING_NS_CC;

EnemyController::EnemyController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void EnemyController::SpawnEnemy(cocos2d::Layer * layer, cocos2d::Sprite * player) {
	//CCLOG("SPAWN ENEMY");

	cocos2d::String* enemyRS = nullptr;// String::create("player.jpg");
	int enemyBitmask = 0;
	float enemyType = Helper::getInstance()->randomDirectionOneDimention();
	Color3B enemyColor;
	//enemyType = 1;
	if (enemyType < 0) {
		//enemyRS = String::create("enemy_blue.jpg");
		enemyRS = String::create("enemy.png");
		enemyBitmask = ENEMY_COLLISION_BITMASK_BLUE;
		enemyColor = Color3B::BLUE;
	}
	else {
		//enemyRS = String::create("enemy_red.jpg");	
		enemyRS = String::create("enemy.png");	
		enemyBitmask = ENEMY_COLLISION_BITMASK_RED;
		enemyColor = Color3B::RED;	
	}

	auto enemy = Sprite::create(enemyRS->getCString());
	enemy->setScale(0.5);
	enemy->setColor(enemyColor);

	auto enemyBody = PhysicsBody::createBox(enemy->getContentSize(),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//enemyBody->setDynamic(false);
	enemyBody->setCollisionBitmask(enemyBitmask);
	enemyBody->setContactTestBitmask(true);

	auto xPosition = cocos2d::random(enemy->getContentSize().width / 2, visibleSize.width - enemy->getContentSize().width / 2);
	enemy->setPosition(Vec2(xPosition,visibleSize.height+origin.y - enemy->getContentSize().width / 2 - 20));
	enemy->setPhysicsBody(enemyBody);


	auto direction = Helper::getInstance()->normalizeDirection(player->getPosition()-enemy->getPosition());
	enemyBody->setVelocity(Vec2(ENEMY_SPEED*visibleSize.width*direction.x, ENEMY_SPEED*visibleSize.height*direction.y));

	layer->addChild(enemy);


}