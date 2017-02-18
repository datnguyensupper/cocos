#pragma once

#include "cocos2d.h"


class PopupController
{
public:
	PopupController();

	void CreatePopupGameOver(cocos2d::Layer * layer, int score, int maxScore);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};
