#include "CoinFlare.h"
#include "Helper/AnimationHelper.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool CoinFlare::init()
{
	//////////////////////////////
	// 1. super init first
	if (!cocos2d::Node::init())
	{
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("animation/coin_flare_animation.plist");

	coinSprite = Sprite::createWithSpriteFrameName("coin_flare_animation_1");
	coinSprite->setBlendFunc(BlendFunc::ADDITIVE);
	this->coinSprite->setVisible(false);
	this->addChild(coinSprite);

	return true;
}

void CoinFlare::resetAndPlay(int loopTimes)
{
	if (!this->coinSprite) {
		return;
	}

	auto spriteFrameAnimation = AnimationHelper::getInstance()->createAnimationByFrameName(
		"animation/coin_flare_animation.plist", "coin_flare_animation_%i", 1, 16, 24, loopTimes);
	auto callFunc = CallFunc::create([this]()
	{
		this->coinSprite->setVisible(false);
	});

	this->coinSprite->setVisible(true);
	this->coinSprite->stopAllActions();
	this->coinSprite->runAction(Sequence::createWithTwoActions(spriteFrameAnimation, callFunc));
}
