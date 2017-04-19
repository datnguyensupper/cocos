#pragma once

#include "cocos2d.h"
#include "Definitions.h"

class BaseScene : public cocos2d::Layer
{
protected:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
public:

    virtual bool init();
	void Go2LevelOneScene(float dt);
};

