#include "AnimationCoinCrown.h"
#include "Helper/AnimationHelper.h"
#include "Constant/Defination.h"
#include "Manager/SoundManager.h"
#include "Manager/ScaleManager.h"

#define MIN_QUANTITY_OBJECT 1
#define MAX_QUANTITY_OBJECT 12
#define TAG_ACTION_MOVE_TO_HEADER 123
#define TAG_ACTION_HIDE 124
#define AREA_1 Vec2(50, 50)
#define AREA_2 Vec2(1150, 50)
USING_NS_CC;
using namespace std;

void AnimationCoinCrown::callbackAfterClickObject(cocos2d::Ref * ref)
{
	auto object = (MenuItemSprite*)ref;
	if (object->getNumberOfRunningActions() > 0
		|| !object->isVisible()) {
		return;
	}
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
	Vec2 endPos = Vec2(890 * scaleDownRatio +origin.x, visibleSize.height - 60*scaleDownRatio);
	if (this->currentType == AnimationType::CoinAnimation)
	{
		auto actionAnimationCoin =
			AnimationHelper::getInstance()->createAnimationByFrameName(
				"animation/coin-animation.plist", "coin_animation_%i", 1, 9, 15, kRepeatForever);
		object->getNormalImage()->runAction(actionAnimationCoin);
		endPos = Vec2(510 * scaleDownRatio + origin.x, endPos.y);
	}
	ccBezierConfig configsBezier;
	configsBezier.controlPoint_1 = Vec2(startPos.x, startPos.y);
	configsBezier.endPosition = endPos;
	configsBezier.controlPoint_2 = Vec2((configsBezier.endPosition - configsBezier.controlPoint_1) / 2 + Vec2(-100, 0));

	auto particleFlying = ParticleSystemQuad::create("animation/particle_flying_coin.plist");
	particleFlying->setPosition(object->getContentSize().width * object->getScaleX(), 0);
	object->addChild(particleFlying);

	auto sequenceAction = Sequence::createWithTwoActions(
		BezierTo::create(1.5f, configsBezier),
		CallFunc::create([object, this]()
		{
			object->setVisible(false);

			SoundManager::getInstance()->playSoundEffectIncludeCoin();

			/*auto particle = ParticleSystemQuad::create("animation/increaseCoinCrownParticle.plist");
			particle->setPosition(object->getPosition());
			this->addChild(particle);*/

			this->particalInclude->setPosition(object->getPosition());
			this->particalInclude->start();
		})
	);
	sequenceAction->setTag(TAG_ACTION_MOVE_TO_HEADER);
	object->runAction(sequenceAction);
}

AnimationCoinCrown* AnimationCoinCrown::create(
	cocos2d::Scene* parentScene,
	cocos2d::Vec2 startPosInWorld,
	double increment,
	AnimationType type)
{
	if (!parentScene
		|| increment <= 0) {
		return nullptr;
	}
	AnimationCoinCrown* widget = new (std::nothrow) AnimationCoinCrown();
	parentScene->addChild(widget);
	widget->startPos = startPosInWorld;
	widget->currentType = type;
	widget->increment = increment;
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

// on "init" you need to initialize your instance
bool AnimationCoinCrown::init()
{
	//////////////////////////////
	// 1. super init first
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->particalInclude = ParticleSystemQuad::create("animation/increaseCoinCrownParticle.plist");
	this->particalInclude->stop();
	this->addChild(this->particalInclude);

	//load sprite plist
	auto actionAnimationCoin =
		AnimationHelper::getInstance()->createAnimationByFrameName(
			"animation/coin-animation.plist", "coin_animation_%i", 1, 9, 20, kRepeatForever);

	int numberObject = MIN_QUANTITY_OBJECT; //min

	switch (this->currentType)
	{
	case AnimationType::CoinAnimation:
		numberObject = ceil(increment / 5000.0f) < MIN_QUANTITY_OBJECT ? MIN_QUANTITY_OBJECT : ceil(increment / 5000.0f);
		numberObject = numberObject > MAX_QUANTITY_OBJECT ? MAX_QUANTITY_OBJECT : numberObject;
		break;
	case AnimationType::CrownAnimation:
		numberObject = ceil(increment / 3.0f) < MIN_QUANTITY_OBJECT ? MIN_QUANTITY_OBJECT : ceil(increment / 3.0f);
		numberObject = numberObject > MAX_QUANTITY_OBJECT ? MAX_QUANTITY_OBJECT : numberObject;
		break;
	default:
		break;
	}


	Menu* mymenu = Menu::create();
	mymenu->setPosition(Vec2::ZERO);
	this->addChild(mymenu, 100);

	float scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
	for (int i = 0; i < numberObject; i++)
	{
		SoundManager::getInstance()->playSoundEffectCoinDrop();
		MenuItemSprite *object;
		if (this->currentType == CoinAnimation){
			object = MenuItemSprite::create(
				Sprite::createWithSpriteFrameName("coin_animation_1"), 
				nullptr, 
				CC_CALLBACK_1(AnimationCoinCrown::callbackAfterClickObject, this));
			object->setScale(1280.0f*scaleDownRatio*0.8 / 1920);
		}else{
			object = MenuItemSprite::create(
				Sprite::create(PNG_SHOP_CROWN_ICON),
				nullptr,
				CC_CALLBACK_1(AnimationCoinCrown::callbackAfterClickObject, this));
			object->setScale(1.25f*scaleDownRatio);
		}
		object->setPosition(this->startPos);

		auto defaultPos = RandomHelper::random_int(1, 10) > 5 ? AREA_1 : AREA_2;
		defaultPos *= scaleDownRatio;
		//JUMPT
		auto actionJumpTo = JumpTo::create(
			RandomHelper::random_real(0.3f, 0.8f),
			defaultPos + Vec2(RandomHelper::random_int(0, (int)(300*scaleDownRatio)), 0),
			RandomHelper::random_int((int)(100* scaleDownRatio), (int)(300* scaleDownRatio)),
			1
		);
		object->runAction(EaseIn::create(actionJumpTo, 0.7f));
		this->objects.push_back(object);

		mymenu->addChild(object);
	}

	this->scheduleOnce([this](float dt)
	{
		//bool isPlaySoundReceiveAll = false;
		for (auto child : this->objects)
		{
			if (child->getActionByTag(TAG_ACTION_MOVE_TO_HEADER)
				|| !child->isVisible()) {
				continue;
			}
			auto callFunc = CallFunc::create([this, child]()
			{
				this->callbackAfterClickObject(child);
			});
			this->runAction(Sequence::createWithTwoActions(
				DelayTime::create(RandomHelper::random_real(0.0f, 0.7f)),
				callFunc
			));
			//isPlaySoundReceiveAll = true;
			/*auto actionHide = FadeOut::create(0.5f);
			actionHide->setTag(TAG_ACTION_HIDE);
			child->runAction(actionHide);*/
		}
		/*if (isPlaySoundReceiveAll)
		{
			SoundManager::getInstance()->playSoundEffectReceiveCoin();
		}*/
	}, 1.5f, "schedule_hide_objects_animation");

	
	this->scheduleOnce([this](float dt)
	{
		if (this->getParent()) {
			this->getParent()->removeChild(this);
		}
	}, 7.5f, "remove_all");

	return true;
}