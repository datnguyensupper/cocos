#include "CInterfaceLN.h"
#include "Helper/AnimationHelper.h"
#include "SlotGame/base/settings/CSettings.h"
#include "SlotGame/base/game/CGameBase.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	void CInterfaceLN::initFreeSpinIndicator()
	{
		this->oFreeSpinIndicator = new CFreeSpinIndicatorLN(this);
		this->addChild(oFreeSpinIndicator);
	}

	void CInterfaceLN::onSpinStarted()
	{
		CInterfaceBase::onSpinStarted();
		((CFreeSpinIndicatorLN*)this->oFreeSpinIndicator)->hideDragon();
	}

	CInterfaceLN::CInterfaceLN(CGameBase* oGame):CInterfaceBase(oGame, false)
	{
	}

	CFreeSpinIndicatorLN::CFreeSpinIndicatorLN(CInterfaceLN* oInterface) : CFreeSpinIndicatorBase()
	{
		//CREATE DRAGON
		this->oContainerDragon = Node::create();
		GameUtils::centerNode(this->oContainerDragon);
		((CGameBase*)oInterface->getParent())->getReel()->addChild(this->oContainerDragon, ORDER_REEL_WINANIM - 1);

		auto oDragonStatic = Node::create();
		this->oContainerDragon->addChild(oDragonStatic);

		auto dragonBody1 = Sprite::createWithSpriteFrameName("Freespin-DragonBody");
		dragonBody1->setPosition(-255, -4);
		oDragonStatic->addChild(dragonBody1);
		auto dragonBody2 = Sprite::createWithSpriteFrameName("Freespin-DragonBody2");
		dragonBody2->setPosition(530, 0);
		oDragonStatic->addChild(dragonBody2);
		auto dragonHead = Sprite::createWithSpriteFrameName("Freespin-DragonHead");
		dragonHead->setPosition(470, 240);
		oDragonStatic->addChild(dragonHead);

		this->oDragonWild = Helper4Sprite::createOptimizeSprite();
		this->oContainerDragon->addChild(this->oDragonWild);

		this->hideDragon();

		//CREATE TEXT UI
		auto res = GameConstant::getInstance()->getResources();

		auto oBoxFP = Sprite::createWithSpriteFrameName("box-freespins-bonus");
		oBoxFP->setPosition(-585, -290);
		this->oContainerRemaining->addChild(oBoxFP);

		auto oTextFS = Sprite::createWithSpriteFrameName("freespins-en");
		oTextFS->setPosition(oBoxFP->getPosition() - Vec2(0, 58));
		this->oContainerRemaining->addChild(oTextFS);

		this->oTextNumberFS = Label::createWithTTF(res.fontConfigs["freespin"], "0");
		this->oTextNumberFS->setPosition(oBoxFP->getPosition());
		this->oContainerRemaining->addChild(this->oTextNumberFS);

		this->oContainerRemaining->setPosition(-60 + origin.x, 40);
		
		
	}
	CFreeSpinIndicatorLN::~CFreeSpinIndicatorLN()
	{

	}
	void CFreeSpinIndicatorLN::show()
	{
		CFreeSpinIndicatorBase::show();
		this->oContainerDragon->getChildren().at(0)->setVisible(true);
		this->oContainerDragon->setVisible(true);
	}
	void CFreeSpinIndicatorLN::showDragon(int col)
	{
		auto res = GameConstant::getInstance()->getResources().mainGame;
		this->oDragonWild->setVisible(false);
		this->oDragonWild->stopAllActions();
		this->oDragonWild->setScale(1.15f);
		this->oDragonWild->setPosition(
			CSettings::REEL_OFFSET_X + (CSettings::SYMBOL_WIDTH + CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS)*col + CSettings::SYMBOL_WIDTH / 2 - CSettings::CANVAS_WIDTH / 2 - 5,
			0);
		this->oDragonWild->runAction(
			Sequence::create(CallFunc::create([this]() {
			this->oDragonWild->setVisible(true);
		}), AnimationHelper::getInstance()->createAnimationByFrameName(
			res["free_spin_dragon_wild_plist_0"],
			"Dragon_ExpandingWild_action_HD_%i",
			1,
			14,
			15,
			1),
			CallFunc::create([this, col]() {
			this->oDragonWild->setPosition(this->oDragonWild->getPositionX() - 38, -4);
			this->oDragonWild->setScale(1.05f);
			this->oDragonWild->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
				GameConstant::getInstance()->getResources().mainGame["dragon_wild_plist"],
				"Dragon_ExpandingWild_idle_HD_%i",
				0,
				10,
				20,
				-1));
		}),
			NULL
		));
	}
	void CFreeSpinIndicatorLN::hideDragon()
	{
		this->hideRemaining();
		//CFreeSpinIndicatorBase::hide();
		this->oDragonWild->stopAllActions();
		this->oDragonWild->setVisible(false);
		this->oContainerDragon->setVisible(false);
	}
	void CFreeSpinIndicatorLN::hide()
	{
		this->hideRemaining();
		this->oContainerDragon->getChildren().at(0)->setVisible(false);
	}
}
