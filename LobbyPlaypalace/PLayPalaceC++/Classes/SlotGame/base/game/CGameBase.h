#pragma once

#include "CMainBase.h"
#include "CBonusBase.h"
#include "../interfaceUI/ICharacter.h"
#include "../interfaceUI/CReel.h"
#include "../interfaceUI/CInterfaceBase.h"
#include "../interfaceUI/CWinPanelBase.h"


namespace GameSlot {
	class CGameBase : public cocos2d::Node
	{
	protected:
		CMainBase* oMain;
		ICharacter* oCharacter;
		CReel* oReel;
		CInterfaceBase* oInterface;

		CWinPanelBase* oWinPanel;

		CBonusBase* oDoubleUp;

		GAME_STATE iCurState;
		GAME_TYPE iCurType;

		cocos2d::Size visibleSize;
		cocos2d::Vec2 origin;
		float scaleDownRatio;

		float iTimeElaps;
		int iBonusActive;
		int iStepBonus;
		int iAdditionFreeSpin;
		int iTotFreeSpin;
		int iMulFreeSpin;
		double iTotWinFreespin;

		bool bAutoSpin;
		bool bReceivedSpinInfo;
		bool bDoubleUpMode;
		bool bShowTotalWinOnFreeSpin;
		bool bEndFreeSpin;

		bool bWaitingRequestToFinishSpin;

		int** aCurWheel;
		ObjectMagicItemReceiveAfterSpin *oMagicItemAfterSpin;
		vector<ObjectWinningLine> aWinningLine;

		cocos2d::Sprite* oBg;
		cocos2d::Sprite* oBgFreeSpin;
		/**
		* Create game background
		*/
		virtual void initBackground();
		/**
		* Create reel group
		*/
		virtual void initReels();
		/**
		* Create character model
		*/
		virtual void initCharacter();
		/**
		* Initialize interface UI
		*/
		virtual void initInterface() = 0;
		/**
		* Initialize win panel UI
		*/
		virtual void initWinPanel() { if (this->oWinPanel) this->oWinPanel->init(); };
		/**
		* Check Last State if there is Bonus - need to be override
		*/
		virtual bool checkLastState();
		/**
		* Change UI for Game between MainGame State and FreeSpin State
		*/
		virtual void switchUI();
		/**
		* Change to Free Spin State
		* @param totalFS: total Free Spin
		* @param totalMulty: total Multy
		*/
		virtual void changeToFreeSpinState(int totalFS, int totalMulty);
		/*
		* Function called to start spin
		*/
		void spin();
		/*
		* Function called to show win animation
		*/
		void showWin();
#pragma region API - CALLBACKS
		/**
		* FUNCTION CALLED WHEN GAME RECEIVES SPIN INFO FROM THE API
		* @param aWheels: array wheels info
		* @param aWinPosition: array Win pos
		* @param aTableWin: array Table Win
		* @param iBonus: bonus Index
		* @param countFreeSpin: total free spin
		*/
		virtual void onSpinReceived(
			int** aWheels,
			ObjectMagicItemReceiveAfterSpin *oMagicItemAfterSpin,
			const vector<ObjectWinPosition>& aWinPosition,
			const vector<ObjectTableWin>& aTableWin,
			int iBonus,
			int countFreeSpin);
		/**
		* FUNCTION CALLED WHEN FREE SPIN WITH RETRIGGER INFO IS RECEIVED
		* @param iRemainingFreeSpin: number freespin remained
		* @param iMultyFS: number of Multiplier
		* @param aWinPosition: array Win Pos
		* @param aWheels: array Wheels Info
		* @param aTableWin: array Table win
		* @param iTotWin: total Win
		*/
		virtual void onBonusFreeSpinStepReceived(
			int iRemainingFreeSpin,
			int iMultyFS,
			const vector<ObjectWinPosition>& aWinPosition,
			int** aWheels,
			const vector<ObjectTableWin>& aTableWin,
			double iTotWin);
#pragma endregion
		/**
		* THIS FUNCTION SET ALL SYMBOLS TO SHOW IN THE FINAL WHEEL
		* @param aWheel: array wheels Info
		* @param aWinPosition: array win pos
		* @param aTableWin: array table Win
		*/
		void generateFinalSymbols(
			int** aWheel,
			const vector<ObjectWinPosition>& aWinPosition,
			const vector<ObjectTableWin>& aTableWin);
		/**
		* Function called to fix col that show animation to follow the game's rule
		* @param aCellList: array list cell that contains symbols can play animation
		* @param col: current col to show animation
		*/
		virtual int fixColToShowAnimation(
			const vector<ObjectCell>& aCellList,
			int col);
		/**
		* Reset current array wheel (release)
		*/
		void resetCurrentWheel();
		void resetInfoMagicItemAfterSpin();
	public:		
		CGameBase(CMainBase* oMain);
		virtual ~CGameBase();

#pragma region getter
		GAME_TYPE getCurrentType() const { return this->iCurType; }
		GAME_STATE getCurrentState() const { return this->iCurState; }

		bool isAutoSpin() const { return this->bAutoSpin; }
		bool isBonus() const { return this->iBonusActive > 0; }
		int getBonusActive() const { return this->iBonusActive; }
		int getStepBonus() const { return this->iStepBonus; }
		bool isReadyStopReel() const { return this->bReceivedSpinInfo; }
		bool isEndFreeSpin() const{ return this->bEndFreeSpin; }

		int getTotFreeSpin() const { return this->iTotFreeSpin; }

		int** getCurWheel() const { return this->aCurWheel; };
		ObjectMagicItemReceiveAfterSpin *getObjectMagicItemAfterSpin() {
			return this->oMagicItemAfterSpin;
		}
		

		CMainBase* getMain() { return this->oMain; };
		CReel* getReel() { return this->oReel; };
		CWinPanelBase* getWinPanel() { return this->oWinPanel; }
		CInterfaceBase* getInterface() { return this->oInterface; };
#pragma endregion
#pragma region setter
		void setAutoSpin(bool isAuto) { this->bAutoSpin = isAuto; }
		void setState(GAME_STATE state) { this->iCurState = state; }
		void setType(GAME_TYPE type) { this->iCurType = type; }
#pragma endregion


		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/**
		* update function
		*/
		void update(float dt);
		/**
		* Generate Losing Bet when getting starting wheel failed
		*/
		virtual void generateLosingBet();/**
		 * THIS FUNCTION GENERATE A LOOSING COMBO. IT IS USED WHEN API CALL CAN'T BE LOADED OR FAILS
		 */
		virtual void generateLosingWheel();
		/**
		* GENERATE RANDOM SYMBOLS DURING REEL MOVEMENT
		* @returns {*[]} array contains 3 symbols for a reel
		* @private
		*/
		virtual int* generateRandSymbols();
		/**
		* CALL SPIN
		*/
		virtual bool onSpin(tinyxml2::XMLDocument* doc = nullptr);
		/**
		* CALL AUTO SPIN
		*/
		void onAutoSpin(float dt) { this->bAutoSpin = true; this->onSpin(); }
		/**
		* CALL SKIP
		*/
		virtual void onSkip();
		/**
		* Reset before spin
		*/
		virtual void resetReel();
		/**
		* Function called when one reel column has stopped
		* @return: 0 - normal reel, 1 - reel has scatter, 2 - reel has wild (wild > scatter > normal)
		*/
		virtual int onStopOneReelColumn(int totalReelStop);
		/**
		* Function called when the entire reel has stopped
		*/
		virtual void onStopReel();
		/**
		* Function called when complete spin and all animation
		* @param isWin: is this spin winning
		* @param delayOnAuto: delay time before auto spin
		*/
		virtual void afterStopSpin(bool isWin = false);

		/**
		* SHOW THE BONUS GAINED BY THE USER
		*/
		virtual void launchBonus();
		/**
		* FUNCTION CALLED WHEN PLAYER CHOOSES ITEM ON BONUS
		* @param iIndex: index User selected
		*/
		void chooseItem(int iIndex) { Manager4Network::getInstance()->callBonus(this->iStepBonus, iIndex); }
		/**
		* Function called to start double up
		*/
		virtual void startDoubleUp();
		/**
		* Function called to start free spin
		*/
		virtual void startFreeSpin();
		/**
		* Function called to start bonus
		*/
		virtual void startBonus();
		/**
		* FUNCTION CALLED WHEN DOUBLE UP STEP 0 IS RECEIVED
		* @param currentWin: current win
		*/
		virtual void onDoubleUpStep0Received(double iCurWin);
		/**
		* FUNCTION CALLED WHEN DOUBLE UP STEP 1 IS RECEIVED
		* @param iFinish: check if should finish double Up
		* @param iResult: result Info
		* @param iTotWin: Total Win
		*/
		virtual void onDoubleUpStep1Received(bool iFinish, int iResult, double iTotWin);
		/**
		* FUNCTION CALLED WHEN PLAYER EXIT FROM FREE SPIN
		*/
		void exitFromFreeSpin();
		/**
		* FUNCTION CALLED WHEN PLAYER EXIT FROM BONUS
		*/
		void exitFromBonus(const double& iWin);
		/**
		* FUNCTION CALLED WHEN PLAYER EXIT FROM BONUS FREE SPIN
		* @param totalFreeSpin: total FS
		* @param totalMul: total Multy
		*/
		void exitFromBonusFreeSpin(int totalFreeSpin, int totalMul = 0);

		friend class CMainBase;
	};
}
