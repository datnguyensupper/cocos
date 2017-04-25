#pragma once

#include "cocos2d.h"

class EnemyController
{
public:
	EnemyController();

	cocos2d::Sprite * SpawnEnemy(cocos2d::Layer * layer, cocos2d::Sprite * player, float enemySpeed);
	cocos2d::Sprite * SpawnEnemy();
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	std::vector<cocos2d::Sprite *> arrayOfEnemy;
};

