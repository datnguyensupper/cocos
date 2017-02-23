#pragma once

#include "cocos2d.h"

class EnemyController
{
public:
	EnemyController();

	void SpawnEnemy(cocos2d::Layer * layer, cocos2d::Sprite * player, float enemySpeed);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};

