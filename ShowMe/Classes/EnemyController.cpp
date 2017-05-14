#include "EnemyController.h"
#include "Definitions.h"


USING_NS_CC;

EnemyController::EnemyController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void EnemyController::initEnemy(cocos2d::Layer * layer) {

	for (int i = 0; i < 10; i++) {
		auto newEnemy = SpawnEnemy((EnemyType)cocos2d::random(1,11));
		newEnemy->setPositionY(-visibleSize.height);
		if (layer) layer->addChild(newEnemy);
		arrayOfEnemy.push_back(newEnemy);
		newEnemy->setVisible(false);
	}
}

cocos2d::Sprite * EnemyController::SpawnEnemy(cocos2d::Layer * layer, cocos2d::Sprite * player, float enemySpeed) {
	
	Sprite * newEnemy = nullptr;

	for (auto enemy : arrayOfEnemy) {
		int distance = (player->getPosition().y - enemy->getPosition().y);
		int availableSpace = (visibleSize.height/2 + enemy->getContentSize().height);
		if (distance > availableSpace) {
			newEnemy = enemy;
			newEnemy->setVisible(false);
			//break;
		}
	}

	if (newEnemy == nullptr) {
		newEnemy = SpawnEnemy(EnemyType::ENEMY_TYPE_1);
		if (layer) layer->addChild(newEnemy);
		arrayOfEnemy.push_back(newEnemy);
	}
	newEnemy->setVisible(true);
	if (player) newEnemy->setPosition( player->getPosition() + Vec2(0, visibleSize.height / 2));
	return nullptr;
}

cocos2d::Sprite * EnemyController::SpawnEnemy(EnemyType enemyType) {

	auto xPosition = cocos2d::random(100, (int)visibleSize.width - 100);
	Vec2 enemyPosition = Vec2::ZERO;

	cocos2d::String* enemyRS = nullptr;// String::create("player.jpg");
	Color3B enemyColor;
	//enemyRS = String::create("enemy_red.jpg");	
	std::string enemyFilePath = "enemy/enemy" + std::to_string((int)enemyType) + ".png";
	enemyRS = String::create(enemyFilePath);
	enemyColor = Color3B::RED;

	auto enemy = Sprite::create(enemyRS->getCString());
//	enemy->setColor(enemyColor);
	enemy->setAnchorPoint(Vec2(0.5, 0.5));

	auto enemyBody = PhysicsBody::createBox(enemy->getContentSize(),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	//enemyBody->setDynamic(false);
	enemyBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	enemyBody->setContactTestBitmask(true);
	enemyBody->setRotationEnable(true);
	enemyBody->setGravityEnable(false);
	enemyBody->setDynamic(false);

	enemy->setPosition(enemyPosition);
	enemy->setPhysicsBody(enemyBody);

	return enemy;
}
