#pragma once

#include "cocos2d.h"

class Helper
{
private:
	Helper();
	~Helper();
public:
	static Helper* getInstance();

	cocos2d::Vec2 normalizeDirection(cocos2d::Vec2 direction);
	cocos2d::Vec2 randomDirection();
	float randomDirectionOneDimention();
};

