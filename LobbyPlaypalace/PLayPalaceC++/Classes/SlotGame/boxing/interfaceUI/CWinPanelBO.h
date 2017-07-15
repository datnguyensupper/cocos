#pragma once

#include "SlotGame/base/interfaceUI/CWinPanelBase.h"


namespace GameSlot {
	class CGameBase;
	class CWinPanelBO : public CWinPanelBase {
	private:
		cocos2d::Label* oMessage2;
		/**
		* Show Panel
		*/
		void show() override;
	public:
		CWinPanelBO(CGameBase* oGame);
		~CWinPanelBO();
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
		* @param iTotFreeSpin: total FreeSpin won
		* @param iTotMulty: total Multiplier won
		* @param cb: callback after show
		* @param isAdditionWin: is this is Addition FreeSpin
		*/
		void showFreeSpinAdditionWinPanel(int iTotFreeSpinconst, std::function<void()> cb) override { 
			this->showFreeSpinWinPanel(iTotFreeSpinconst, 0, cb);
		};
	};
}
