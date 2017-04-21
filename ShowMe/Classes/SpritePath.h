#pragma once

#include "cocos2d.h"
#include "Definitions.h"
#include "ui/CocosGUI.h"

class SpritePath : public cocos2d::Node
{
protected:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Point firstPoint;
	cocos2d::Point secondPoint;
	cocos2d::ui::Scale9Sprite * spriteBG;
	void adjustSprite();
public:

    virtual bool init();
    void adjustSprite(cocos2d::Point _firstPoint, cocos2d::Point _secondPoint);
    void adjustSprite(cocos2d::Point _secondPoint);

	// implement the "static create()" method manually
	CREATE_FUNC(SpritePath);
};

