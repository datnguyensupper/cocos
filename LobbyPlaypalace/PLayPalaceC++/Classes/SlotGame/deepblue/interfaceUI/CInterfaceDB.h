#pragma once

#include "cocos2d.h"
#include "SlotGame/base/interfaceUI/CInterfaceBase.h"

namespace GameSlot {
	class CInterfaceDB : public CInterfaceBase
	{
	private:
		cocos2d::ParticleSystemQuad* oBubble;
		/**
		* init FreeSpin Indicator
		*/
		void initFreeSpinIndicator();
		/**
		* Function called when begin spin
		*/
		void onSpinStarted();
	public:
		/**
		* init
		*/
		bool init() override;
		CInterfaceDB(CGameBase* oGame);
	};

	class CFreeSpinIndicatorDB : public CFreeSpinIndicatorBase {
	private:
	public:
		CFreeSpinIndicatorDB();
		virtual ~CFreeSpinIndicatorDB();
	};
}
