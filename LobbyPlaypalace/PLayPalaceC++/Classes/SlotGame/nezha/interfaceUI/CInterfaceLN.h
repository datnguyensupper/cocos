#pragma once

#include "cocos2d.h"
#include "SlotGame/base/interfaceUI/CInterfaceBase.h"

namespace GameSlot {
	class CInterfaceLN : public CInterfaceBase
	{
	private:
		/**
		* init FreeSpin Indicator
		*/
		void initFreeSpinIndicator();
		/**
		* Function called when begin spin
		*/
		void onSpinStarted();
	public:
		CInterfaceLN(CGameBase* oGame);
	};

	class CFreeSpinIndicatorLN : public CFreeSpinIndicatorBase {
	private:
		cocos2d::Node* oContainerDragon;

		cocos2d::Sprite* oDragonWild;
	public:
		CFreeSpinIndicatorLN(CInterfaceLN* oInterface);
		~CFreeSpinIndicatorLN();
		/**
		* Show
		*/
		void show() override;
		/**
		* Hide Wild Dragon animation
		*/
		void hide() override;
		/**
		* Show Wild Dragon animation
		* @param col: current Col that should show animation
		*/
		void showDragon(int col);
		/**
		* Hide Wild Dragon animation
		*/
		void hideDragon();
	};
}
