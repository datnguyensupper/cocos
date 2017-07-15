#pragma once

#include "cocos2d.h"
#include "SlotGame/deepblue/interfaceUI/CInterfaceDB.h"

namespace GameSlot {
	class CInterfaceGE : public CInterfaceBase
	{
	private:
		/**
		* init FreeSpin Indicator
		*/
		void initFreeSpinIndicator();
	public:
		CInterfaceGE(CGameBase* oGame);
	};

	class CFreeSpinIndicatorGE : public CFreeSpinIndicatorDB {
	private:
	public:
		CFreeSpinIndicatorGE();
		~CFreeSpinIndicatorGE();
	};
}
