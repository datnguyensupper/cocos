#pragma once

#include "SlotGame/base/interfaceUI/CWinPanelBase.h"

namespace GameSlot {
	class CGameBase;
	class CWinPanelLN : public CWinPanelBase {
	private:
		cocos2d::Sprite* oExplosion;
		/**
		* Show Panel
		*/
		void show() override;
		/**
		* Hide Panel
		*/
		void hide() override;
	public:
		CWinPanelLN(CGameBase* oGame);
		~CWinPanelLN();
		/**
		* init Panel
		*/
		bool init() override;
	};
}
