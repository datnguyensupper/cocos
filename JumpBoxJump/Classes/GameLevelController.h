#pragma once

#include "cocos2d.h"



enum ObstacleType {
	SPIKE,
	GOBACK
};
struct Barrier {
	int width;
	int height;
	int x;
	ObstacleType type;
};

class GameLevelController
{
public:
	GameLevelController();
	void createGameLevels();
	void setFloor(int _floorX, std::vector<int> &_floorY);
	cocos2d::Node* createFloor(int floor, cocos2d::Node * parent);
	cocos2d::Node* createFloorRandom(int floor, cocos2d::Node * parent);
private:
	cocos2d::Node* createFloor(int floor, std::vector<Barrier> floorLevelWall, cocos2d::Node * parent);
	void createObstacleWithType(Barrier barrier, cocos2d::Node* parent, int floor);
	void createGameLevelsSPIKE();
	void createGameLevelsGOBACK();

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;

	int floorX = 0;
	std::vector<int> floorY;

	std::vector<std::vector<Barrier>> gameLevels;
	std::vector<std::vector<Barrier>> gameLevelsRandom;
};
