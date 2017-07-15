#include "CInterfacePO.h"
#include "Helper/AnimationHelper.h"
#include "SlotGame/base/settings/CSettings.h"

USING_NS_CC;
namespace GameSlot {
	void CInterfacePO::initFreeSpinIndicator()
	{
		this->oFreeSpinIndicator = new CFreeSpinIndicatorPO();
		this->addChild(oFreeSpinIndicator);
	}

	CInterfacePO::CInterfacePO(CGameBase* oGame):CInterfaceBase(oGame, false)
	{
	}

	CFreeSpinIndicatorPO::CFreeSpinIndicatorPO() : CFreeSpinIndicatorBase()
	{
		//CREATE TEXT UI
		auto res = GameConstant::getInstance()->getResources();

		auto oBoxFP = Sprite::createWithSpriteFrameName("box-freespins-bonus");
		oBoxFP->setPosition(-585+origin.x, -290);
		this->oContainerRemaining->addChild(oBoxFP);

		auto oTextFS = Sprite::createWithSpriteFrameName("freespins-en");
		oTextFS->setPosition(oBoxFP->getPosition() - Vec2(0, 60));
		this->oContainerRemaining->addChild(oTextFS);

		this->oTextNumberFS = Label::createWithTTF(res.fontConfigs["freespin"], "0");
		this->oTextNumberFS->setPosition(oBoxFP->getPosition());
		this->oContainerRemaining->addChild(this->oTextNumberFS);

		this->oContainerRemaining->setPosition(-45, 45);

		this->hide();
	}
	CFreeSpinIndicatorPO::~CFreeSpinIndicatorPO()
	{

	}
}
