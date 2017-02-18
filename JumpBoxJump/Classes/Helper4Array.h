#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: LanguageManager.h, LanguageManager.cpp
*/

#include "cocos2d.h"

class Helper4Array
{
private:
	Helper4Array();
	static Helper4Array* s_instance;
public:
	static Helper4Array* getInstance();

	cocos2d::Color3B removeRandomItemFromVector(std::vector<cocos2d::Color3B> &vector );
};