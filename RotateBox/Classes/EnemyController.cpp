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

	

	
	auto xPosition = cocos2d::random(100, (int)visibleSize.width - 100);
	Vec2 enemyPosition = Vec2(xPosition, visibleSize.height - 40);

	//// particle create sprite
	ParticleFlower * particleSpawnEnemy = ParticleFlower::create();
	particleSpawnEnemy->setPosition(enemyPosition);
	particleSpawnEnemy->setTotalParticles(30);
	//particleSpawnEnemy->setDuration(1);
	//particleSpawnEnemy->setLife(1);
	//particleSpawnEnemy->setSpeed(50);
	layer->addChild(particleSpawnEnemy);

	auto shiny = Sprite::create("shiny_spawn.jpg");
	shiny->setPosition(Vec2(enemyPosition.x, enemyPosition.y));
	shiny->setAnchorPoint(Vec2(0.5, 0.5));
	shiny->setBlendFunc(BlendFunc::ADDITIVE);
	shiny->setScale(0.5);
	shiny->setOpacity(0);
	layer->addChild(shiny);

	CallFunc *runCallback = CallFunc::create([=]() {
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
		enemy->setAnchorPoint(Vec2(0.5, 0.5));

		particleSpawnEnemy->stopSystem();
		layer->removeChild(particleSpawnEnemy);
		layer->removeChild(shiny);
		auto enemyBody = PhysicsBody::createBox(enemy->getContentSize(),
			PhysicsMaterial(0.1f, 1.0f, 0.0f));
		//enemyBody->setDynamic(false);
		enemyBody->setCollisionBitmask(enemyBitmask);
		enemyBody->setContactTestBitmask(true);

		enemy->setPosition(enemyPosition);
		enemy->setPhysicsBody(enemyBody);


		auto direction = Helper::getInstance()->normalizeDirection(player->getPosition()-enemy->getPosition());
		enemyBody->setVelocity(Vec2(ENEMY_SPEED*visibleSize.width*direction.x, ENEMY_SPEED*visibleSize.height*direction.y));

		layer->addChild(enemy);
		
	});

	
	shiny->runAction(Sequence::create(FadeIn::create(3), runCallback, nullptr));
	//shiny->runAction(Sequence::ScaleTo::create(3,0.7), runCallback, nullptr));
	//player->runAction(Sequence::create(DelayTime::create(4), runCallback, nullptr));
	return;


}