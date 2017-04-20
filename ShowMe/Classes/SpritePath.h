#pragma once

#include "cocos2d.h"
#include "Definitions.h"

class SpritePath : public cocos2d::Node
{
protected:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
public:

    virtual bool init();
    public void adjustSprite();
};

