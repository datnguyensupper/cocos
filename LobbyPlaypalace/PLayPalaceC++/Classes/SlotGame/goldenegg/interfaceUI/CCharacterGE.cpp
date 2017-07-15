#include "CCharacterGE.h"
#include "SlotGame/base/game/CGameBase.h"
#include "Manager/ScaleManager.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CCharacterGE::CCharacterGE()
	{
		ICharacter::init();
		//auto spritebatch = SpriteBatchNode::create(resGame["nezha_idle"]);

		this->sprite = Helper4Sprite::createOptimizeSprite();
		this->sprite->setPosition(165+origin.x, 370);
		this->sprite->setScale(0.9f*ScaleManager::getInstance()->getLookGoodScaleDownRatio());
		//spritebatch->addChild(this->nezhaSprite);
	}
	CCharacterGE::~CCharacterGE()
	{
	}
	void CCharacterGE::create(CGameBase * _oGame)
	{
		_oGame->addChild(this->sprite, ORDER_CHARACTER);
	}
	void CCharacterGE::playIdle()
	{
		this->sprite->stopAllActions();
		this->sprite->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().mainGame["farmer_plist"],
			"ui_idle_%.2i",
			1,
			24,
			30,
			-1));
	}
	void CCharacterGE::playFreeSpin()
	{
		this->sprite->stopAllActions();
		this->sprite->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().mainGame["lady_plist"],
			"ui_lady_idle_%.2i",
			1,
			24,
			30,
			-1));
	}
	void CCharacterGE::playWin()
	{
	}
}
