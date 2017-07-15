#pragma once

#include "SlotGame/deepblue/game/CGameDB.h"

namespace GameSlot {
	class CBonusFreeSpinGE;
	class CDoubleUpGE;
	class CGameGE : public CGameDB
	{
	private:
		/**
		* Create game background
		*/
		void initBackground() override;
		/**
		* Create character model
		*/
		void initCharacter() override;
		/**
		* Create character model
		*/
		void initInterface() override;
		/**
		* Initialize win panel UI
		*/
		virtual void initWinPanel() override;
		/**
		* Create reel group
		*/
		void initReels() override;
	public:
		CGameGE(CMainBase* _oMain);
		~CGameGE();

		bool init() override;
	};
}
