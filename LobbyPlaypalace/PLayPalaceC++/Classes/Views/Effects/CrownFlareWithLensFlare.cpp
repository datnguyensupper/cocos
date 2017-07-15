#include "CrownFlareWithLensFlare.h"
#include "Helper/AnimationHelper.h"

USING_NS_CC;

cocos2d::FiniteTimeAction * CrownFlareWithLensFlare::createCrownFlareAction(int loopTimes)
{
	return AnimationHelper::getInstance()->createAnimationByFrameName(
			"animation/crown_flare_animation.plist", "crown_flare_animation%i", 1, 20, 24, loopTimes > 0 ? loopTimes * 2 : loopTimes);
}

cocos2d::FiniteTimeAction * CrownFlareWithLensFlare::createLensFlareAction(int loopTimes)
{
	return AnimationHelper::getInstance()->createAnimationByFrameName(
			"animation/lens_flare_animation.plist", "lens_flare_animation%i", 1, 36, 24, loopTimes);
}

// on "init" you need to initialize your instance
bool CrownFlareWithLensFlare::init()
{
	//////////////////////////////
	// 1. super init first
	if (!cocos2d::Node::init())
	{
		return false;
	}

	//init plist
	auto actionAnimationCrownFlare = this->createCrownFlareAction(1);
	this->crownFlareAnimation = Sprite::createWithSpriteFrameName("crown_flare_animation1");
	this->addChild(this->crownFlareAnimation);

	//init plist
	auto actionAnimationLensFlare = this->createLensFlareAction(1);
	this->lensFlareAnimation = Sprite::createWithSpriteFrameName("lens_flare_animation1");
	this->lensFlareAnimation->setPosition(Vec2(5, 5));
	this->lensFlareAnimation->setBlendFunc(BlendFunc::ADDITIVE);
	this->addChild(this->lensFlareAnimation);

	return true;
}

void CrownFlareWithLensFlare::resetAndPlay(int loopTimes)
{
	if (!this->crownFlareAnimation) {
		return;
	}
	if (!this->lensFlareAnimation) {
		return;
	}

	this->crownFlareAnimation->stopAllActions();
	this->crownFlareAnimation->setVisible(true);
	this->crownFlareAnimation->runAction(this->createCrownFlareAction(loopTimes));


	this->lensFlareAnimation->stopAllActions();
	this->lensFlareAnimation->setVisible(true);
	this->lensFlareAnimation->runAction(this->createLensFlareAction(loopTimes));
}
