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
	float delayForSetSecondPoint = 0;
	cocos2d::ui::Scale9Sprite * spriteBG;
	void adjustSprite(bool havePhysic);
	cocos2d::PhysicsBody * physicBody = nullptr;
	cocos2d::Sprite * player = nullptr;
public:

	static SpritePath* create(cocos2d::Sprite * player);
    void setPlayer(cocos2d::Sprite * _player);
    virtual bool init();
	void adjustFirstPoint();
	void adjustSecondPoint();
    void adjustSprite(cocos2d::Point _firstPoint, cocos2d::Point _secondPoint);
    void adjustSprite(cocos2d::Point _secondPoint);
    void adjustSpriteWithoutPhysic(cocos2d::Point _secondPoint);

	void updatePhysic();
	void removePhysic();

	// implement the "static create()" method manually
	CREATE_FUNC(SpritePath);
};

