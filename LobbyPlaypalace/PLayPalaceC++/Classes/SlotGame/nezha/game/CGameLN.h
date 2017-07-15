#pragma once

#include "SlotGame/base/game/CGameBase.h"

namespace GameSlot {
	class CBonusPalaceLN;
	class CBonusBattleLN;
	class CGameLN : public CGameBase 
	{
	private:
		int iColDragon;

		CBonusPalaceLN* oBonusPalace;
		CBonusBattleLN* oBonusBattle;
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
		/**
		* Function called to fix col that show animation to follow the game's rule
		* @param aCellList: array list cell that contains symbols can play animation
		* @param col: current col to show animation
		*/
		int fixColToShowAnimation(
			const vector<ObjectCell>& aCellList,
			int col) override;
		/**
		* Check Last State if there is Bonus - need to be override
		*/
		bool checkLastState() override;
	public:
		CGameLN(CMainBase* _oMain);
		~CGameLN();
		
		bool init() override;
		/**
		* FUNCTION CALLED WHEN FREE SPIN WITH RETRIGGER INFO IS RECEIVED
		* @param iRemainingFreeSpin: number freespin remained
		* @param iMultyFS: number of Multiplier
		* @param aWinPosition: array Win Pos
		* @param aWheels: array Wheels Info
		* @param aTableWin: array Table win
		* @param iTotWin: total Win
		*/
		void onBonusFreeSpinStepReceived(
			int iRemainingFreeSpin,
			int iMultyFS,
			const vector<ObjectWinPosition>& aWinPosition,
			int** aWheels,
			const vector<ObjectTableWin>& aTableWin,
			double iTotWin) override;
		/**
		* Function called to start bonus
		*/
		virtual void startBonus() override;
		/**
		* FUNCTION CALLED WHEN BONUS PALACE STEP 0 IS RECEIVED
		*/
		void onBonusPalaceStep0Received();
		/**
		* FUNCTION CALLED WHEN BONUS PALACE STEP 0 IS RECEIVED
		* @param iFinish: check if should finish Bonus
		* @param aWheels: array wheels info
		*/
		void onBonusPalaceStep1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels);
		/**
		* FUNCTION CALLED WHEN BONUS BATTLE STEP 0 IS RECEIVED
		*/
		void onBonusBattleStep0Received();
		/**
		* FUNCTION CALLED WHEN BONUS BATTLE STEP 0 IS RECEIVED
		* @param iFinish: check if should finish Bonus
		* @param aWheels: array wheels info
		*/
		void onBonusBattleStep1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels);
	};
}
