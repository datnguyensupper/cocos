#include "EnemyController.h"
#include "Definitions.h"


USING_NS_CC;

EnemyController::EnemyController() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

cocos2d::Sprite * EnemyController::SpawnEnemy(cocos2d::Layer * layer, cocos2d::Sprite * player, float enemySpeed) {
	
	Sprite * newEnemy = nullptr;

	for (auto enemy : arrayOfEnemy) {
		int distance = (player->getPosition().y - enemy->getPosition().y);
		int availableSpace = (visibleSize.height/2 + enemy->getContentSize().height);
		if (distance > availableSpace) {
			newEnemy = enemy;
			break;
		}
	}

	if (newEnemy == nullptr) {
		newEnemy = SpawnEnemy();
		if (layer) layer->addChild(newEnemy);
		arrayOfEnemy.push_back(newEnemy);
	}
	if (player) newEnemy->setPosition( player->getPosition() + Vec2(0, visibleSize.height / 2));
	return nullptr;
}

cocos2d::Sprite * EnemyController::SpawnEnemy() {

	auto xPosition = cocos2d::random(100, (int)visibleSize.width - 100);
	Vec2 enemyPosition = Vec2::ZERO;

	////// particle create sprite
	//ParticleFlower * particleSpawnEnemy = ParticleFlower::create();
	//particleSpawnEnemy->setPosition(enemyPosition);
	//particleSpawnEnemy->setTotalParticles(30);
	////particleSpawnEnemy->setDuration(1);
	////particleSpawnEnemy->setLife(1);
	////particleSpawnEnemy->setSpeed(50);
	//layer->addChild(particleSpawnEnemy);

	/*auto shiny = Sprite::create("shiny_spawn.jpg");
	shiny->setPosition(Vec2(enemyPosition.x, enemyPosition.y));
	shiny->setAnchorPoint(Vec2(0.5, 0.5));
	shiny->setBlendFunc(BlendFunc::ADDITIVE);
	shiny->setScale(0.5);
	shiny->setOpacity(0);
	layer->addChild(shiny);*/


	cocos2d::String* enemyRS = nullptr;// String::create("player.jpg");
	Color3B enemyColor;
	//enemyRS = String::create("enemy_red.jpg");	
	enemyRS = String::create("enemy/enemy1.png");
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
