#pragma once

#include "SlotGame/base/interfaceUI/CWinPanelBase.h"

namespace GameSlot {
	class CGameBase;
	class CWinPanelGE : public CWinPanelBase {
	private:
	public:
		CWinPanelGE(CGameBase* oGame);
		~CWinPanelGE();
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
		virtual void showFreeSpinWinPanel(int iTotFreeSpin, int iTotMulty, const std::function<void()> cb);
	};
}
