#pragma once

#include "cocos2d.h"
#include "SlotGame/deepblue/interfaceUI/CInterfaceDB.h"

namespace GameSlot {
	class CInterfaceBO : public CInterfaceBase
	{
	private:
		cocos2d::ParticleSystemQuad* oBubble;
		/**
		* init FreeSpin Indicator
		*/
		void initFreeSpinIndicator();
	public:
		CInterfaceBO(CGameBase* oGame);
	};

	class CFreeSpinIndicatorBO : public CFreeSpinIndicatorBase {
	private:
	public:
		CFreeSpinIndicatorBO();
		~CFreeSpinIndicatorBO();
	};
}
