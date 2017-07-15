#pragma once

#include "SlotGame/base/interfaceUI/CWinPanelBase.h"

namespace GameSlot {
	class CGameBase;
	class CWinPanelPO : public CWinPanelBase {
	private:
		cocos2d::Label* oMessage2;
		/**
		* Show Panel
		*/
		void show() override;
	public:
		CWinPanelPO(CGameBase* oGame);
		~CWinPanelPO();
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
		void showFreeSpinWinPanel(int iTotFreeSpin, int iTotMulty, const std::function<void()> cb) override;
		/**
		* Show Free Spin Win Panel
		* @param iTotWin1: total stage 1 win
		* @param iTotWin2: total stage 2 win
		* @param cb: callback after show
		*/
		void showBonusWinPanel(double iTotWin1, double iTotWin2, const std::function<void()> cb);
	};
}
