#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: LanguageManager.h, LanguageManager.cpp
*/

#include "cocos2d.h"

class Helper4Calculate
{
private:
	Helper4Calculate();
	static Helper4Calculate* s_instance;
public:
	static Helper4Calculate* getInstance();

	float distance(cocos2d::Vec2 firstPoint, cocos2d::Vec2 secondPoint );
	float angle(cocos2d::Vec2 firstPoint, cocos2d::Vec2 secondPoint );
};