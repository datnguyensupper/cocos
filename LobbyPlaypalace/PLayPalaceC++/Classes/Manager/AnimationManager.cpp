#include "AnimationManager.h"
#include "SimpleAudioEngine.h"
#include "Constant/Defination.h"
#include "Helper/AnimationHelper.h"
#include "Helper/Helper4Sprite.h"


using namespace std;
USING_NS_CC;
#pragma region init singleton
AnimationManager* AnimationManager::s_instance = nullptr;

AnimationManager* AnimationManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new AnimationManager();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

AnimationManager::AnimationManager()
{

	
}

void AnimationManager::playCoinAnimation(cocos2d::Vec2 from, cocos2d::Vec2 to, cocos2d::Node * parent) {
	/*RepeatForever::create();
	this->runAction(Sequence::create(
	AnimationHelper,
	CallFunc::create(),

	))*/

	FiniteTimeAction * finitTimeAction = 
		AnimationHelper::getInstance()->createAnimationByFrameName(
		"img/animation/coin-animation.plist","coin_animation_%i",1,11,20,kRepeatForever);

	Sprite * coin = Helper4Sprite::createOptimizeSprite();
	coin->setPosition(to);
	coin->runAction(finitTimeAction);
	parent->addChild(coin);
}
