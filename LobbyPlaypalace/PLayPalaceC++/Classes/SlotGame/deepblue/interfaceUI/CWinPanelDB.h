#pragma once

#include "SlotGame/base/interfaceUI/CWinPanelBase.h"

namespace GameSlot {
	class CGameBase;
	class CWinPanelDB : public CWinPanelBase {
	private:
		cocos2d::Sprite* oJellyFish;
		/**
		* Show Panel
		*/
		void show() override;
		/**
		* Hide Panel
		*/
		void hide() override;
	public:
		CWinPanelDB(CGameBase* oGame);
		~CWinPanelDB();
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
