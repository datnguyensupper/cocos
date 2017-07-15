#pragma once

#include "SlotGame/base/interfaceUI/CWinPanelBase.h"

namespace GameSlot {
	class CGameBase;
	class CWinPanelRE : public CWinPanelBase {
	private:
		cocos2d::Label* oMessage2;
		/**
		* Show Panel
		*/
		void show() override;
	public:
		CWinPanelRE(CGameBase* oGame);
		~CWinPanelRE();
		/**
		* init Panel
		*/
		bool init() override;
		/**
		* Show Free Spin Win Panel
		* @param iTotFreeSpin: total FreeSpin won
		* @param iTotMulty: total Multiplier won
		* @param cb: callback after show
		*/
		void showBonusWinPanel(double iTotWin, int iTotMulty, const std::function<void()> cb);
	};
}
