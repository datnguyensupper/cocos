#pragma once
#include "SlotGame/base/game/CGameBase.h"

namespace GameSlot {
	class CBonusRE;
	class CGameRE : public CGameBase 
	{
	protected:
		std::vector<cocos2d::Sprite*> aExpand;

		CBonusRE* oBonus;
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
		* Show expand man on Specific column
		* @param col: column that contains Expand man
		*/
		void showExpand(int iCol);
		/**
		* Hide all Expand man
		*/
		void hideExpand();
		/**
		* Check if the column can contains Expand Symbol
		* @param iCol: column that need to check
		* @returns {boolean} true - the column can contains expand symbol
		*/
		bool checkExpandColumn(int iCol);
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
		CGameRE(CMainBase* _oMain);
		~CGameRE();

		bool init() override;
		/**
		* CALL SPIN
		*/
		bool onSpin(tinyxml2::XMLDocument* doc = nullptr) override;
		/**
		* Function called when one reel column has stopped
		* @return: 0 - normal reel, 1 - reel has scatter, 2 - reel has wild (wild > scatter > normal)
		*/
		virtual int onStopOneReelColumn(int totalReelStop);
		/**
		* Function called to start bonus
		*/
		virtual void startBonus() override;
		/**
		* FUNCTION CALLED WHEN BONUS STEP 0 IS RECEIVED
		*/
		void onBonusStep0Received();
		/**
		* FUNCTION CALLED WHEN BONUS STEP 1 IS RECEIVED
		* @param iFinish: check if should finish FreeSpin
		* @param iTotMul: total multiplier won
		* @param iTotWin: total win
		*/
		void onBonusStep1Received(bool iFinish, int iTotMul, double iTotWin);
	};
}