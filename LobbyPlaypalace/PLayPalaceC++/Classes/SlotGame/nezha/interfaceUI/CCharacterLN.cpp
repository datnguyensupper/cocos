#include "CCharacterLN.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CCharacterLN::CCharacterLN()
	{
		ICharacter::init();
		//auto spritebatch = SpriteBatchNode::create(resGame["nezha_idle"]);

		this->nezhaSprite = Sprite::createWithSpriteFrameName("Ui_Nezha_idle_0");

		//spritebatch->addChild(this->nezhaSprite);
	}
	CCharacterLN::~CCharacterLN()
	{
	}
	void CCharacterLN::create(CGameBase * _oGame)
	{
		_oGame->getInterface()->getFreeSpinIndicator()->addChild(this->nezhaSprite, 5);
	}
	void CCharacterLN::playIdle()
	{
		this->nezhaSprite->stopAllActions();
		this->nezhaSprite->setPosition(-CSettings::CANVAS_WIDTH / 2 + 125 + origin.x/2, -85);

		this->nezhaSprite->setScale(1.0f);
		this->nezhaSprite->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().mainGame["nezha_idle_plist_0"],
			"Ui_Nezha_idle_%i",
			0,
			13,
			20,
			-1));
	}
	void CCharacterLN::playFreeSpin()
	{
		this->nezhaSprite->stopAllActions();

		this->nezhaSprite->setPosition(-CSettings::CANVAS_WIDTH / 2 + 275, - 15);

		this->nezhaSprite->setScale(1.25f);

		this->nezhaSprite->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().mainGame["nezha_freespin_plist_0"],
			"Freespin-Nezha_%i",
			0,
			17,
			20,
			-1));
	}
	void CCharacterLN::playWin()
	{
	}
}
