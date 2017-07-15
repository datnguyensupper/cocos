#include "CirclePink.h"
#include "Helper/AnimationHelper.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool CirclePink::init()
{
	//////////////////////////////
	// 1. super init first
	if (!cocos2d::Node::init())
	{
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/circle_pink.plist");

	circleSprite = Sprite::createWithSpriteFrameName("circle_pink1");
	this->addChild(circleSprite);

	return true;
}

void CirclePink::resetAndPlay(int loopTimes)
{
	if (!this->circleSprite) {
		return;
	}
	this->circleSprite->stopAllActions();
	this->circleSprite->setVisible(true);
	this->circleSprite->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
		"animation/circle_pink.plist", "circle_pink%i", 1, 15, 24, loopTimes));
}
