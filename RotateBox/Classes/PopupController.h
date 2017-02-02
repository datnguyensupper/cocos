#pragma once

#include "cocos2d.h"


class PopupController
{
public:
	PopupController();

	void CreatePopupGameOver(cocos2d::Layer * layer);
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
};
