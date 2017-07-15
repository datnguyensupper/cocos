#include "CInterfaceGE.h"

#include "Helper/AnimationHelper.h"
#include "SlotGame/base/settings/CSettings.h"

USING_NS_CC;
namespace GameSlot {
	void CInterfaceGE::initFreeSpinIndicator()
	{
		this->oFreeSpinIndicator = new CFreeSpinIndicatorGE();
		this->addChild(oFreeSpinIndicator);
	}

	CInterfaceGE::CInterfaceGE(CGameBase* oGame):CInterfaceBase(oGame, true)
	{
	}
	CFreeSpinIndicatorGE::CFreeSpinIndicatorGE(): CFreeSpinIndicatorDB()
	{
		this->oTextNumberFS->setPositionY(this->oTextNumberFS->getPositionY() - 10);
		this->oTextNumberMulty->setPositionY(this->oTextNumberMulty->getPositionY() - 10);
	}
	CFreeSpinIndicatorGE::~CFreeSpinIndicatorGE()
	{
	}
}
