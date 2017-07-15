#pragma once

#include "SlotGame/base/game/CGameBase.h"

namespace GameSlot {
	class CBonusStage1PO;
	class CBonusStage2PO;
	class CGamePO : public CGameBase 
	{
	private:
		CBonusStage1PO* oBonusStage1;
		CBonusStage2PO* oBonusStage2;

		PoolSystem* poolSystemEagle;
		/**
		* Create game background
		*/
		void initBackground() override;
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
		/**
		* SHOW THE BONUS GAINED BY THE USER
		*/
		void launchBonus() override;
	public:
		CGamePO(CMainBase* _oMain);
		~CGamePO();
		
		bool init() override;
		/**
		* GENERATE RANDOM SYMBOLS DURING REEL MOVEMENT
		* @returns {*[]} array contains 3 symbols for a reel
		* @private
		*/
		int* generateRandSymbols() override;
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
		void onBonusStage1Step0Received();
		/**
		* FUNCTION CALLED WHEN BONUS PALACE STEP 0 IS RECEIVED
		* @param iFinish: check if should finish Bonus
		* @param aWheels: array wheels info
		*/
		void onBonusStage1Step1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels);
		/**
		* FUNCTION CALLED WHEN BONUS BATTLE STEP 0 IS RECEIVED
		* @param iMode
		*/
		void onBonusStage2Step0Received(int iMode);
		/**
		* FUNCTION CALLED WHEN BONUS BATTLE STEP 0 IS RECEIVED
		* @param iFinish: check if should finish Bonus
		* @param aWheels: array wheels info
		*/
		void onBonusStage2Step1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels);
		/**
		* Exit from bonus stage 1
		*/
		void exitFromBonusStage1(const double& iWin, bool bWinBonusStage2);

		virtual void onExit();
	};
}
