#pragma once

#include "cocos2d.h"
#include "SlotGame/base/interfaceUI/CInterfaceBase.h"

namespace GameSlot {
	class CInterfacePO : public CInterfaceBase
	{
	private:
		/**
		* init FreeSpin Indicator
		*/
		void initFreeSpinIndicator();
	public:
		CInterfacePO(CGameBase* oGame);
	};

	class CFreeSpinIndicatorPO : public CFreeSpinIndicatorBase {
	private:
	public:
		CFreeSpinIndicatorPO();
		~CFreeSpinIndicatorPO();
	};
}
