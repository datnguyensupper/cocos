#pragma once

#include "cocos2d.h"

enum EnemyType {
	ENEMY_TYPE_1 = 1,
	ENEMY_TYPE_2 = 2,
	ENEMY_TYPE_3 = 3,
	ENEMY_TYPE_4 = 4,
	ENEMY_TYPE_5 = 5,
	ENEMY_TYPE_6 = 6,
	ENEMY_TYPE_7 = 7,
	ENEMY_TYPE_8 = 8,
	ENEMY_TYPE_9 = 9,
	ENEMY_TYPE_10 = 10,
	ENEMY_TYPE_11 = 11
};
class EnemyController
{
public:
	EnemyController();

	void initEnemy(cocos2d::Layer * layer);
	cocos2d::Sprite * SpawnEnemy(cocos2d::Layer * layer, cocos2d::Sprite * player, float enemySpeed);
	cocos2d::Sprite * SpawnEnemy(EnemyType enemyType);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	std::vector<cocos2d::Sprite *> arrayOfEnemy;
};

