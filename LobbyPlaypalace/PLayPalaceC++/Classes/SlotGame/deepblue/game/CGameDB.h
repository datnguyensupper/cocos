#pragma once

#include "SlotGame/base/game/CGameBase.h"

namespace GameSlot {
	class CBonusBase;
	class CJellyFishDB;
	class CGameDB : public CGameBase 
	{
	protected:
		CBonusBase* oBonusFreeSpin;

		cocos2d::Vector<CJellyFishDB*> aJellyFish;
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
		* Check Last State if there is Bonus - need to be override
		*/
		bool checkLastState() override;
		/**
		* FUNCTION CALLED WHEN GAME RECEIVES SPIN INFO FROM THE API
		* @param aWheels: array wheels info
		* @param aWinPosition: array Win pos
		* @param aTableWin: array Table Win
		* @param iBonus: bonus Index
		* @param countFreeSpin: total free spin
		*/
		void onSpinReceived(
			int** aWheels,
			ObjectMagicItemReceiveAfterSpin *oMagicItemAfterSpin,
			const vector<ObjectWinPosition>& aWinPosition,
			const vector<ObjectTableWin>& aTableWin,
			int iBonus,
			int countFreeSpin) override;
	public:
		CGameDB(CMainBase* _oMain);
		~CGameDB();

		bool init() override;
		/**
		* Function called to start bonus
		*/
		virtual void startBonus() override;
		/**
		* FUNCTION CALLED WHEN FREE SPIN BONUS STEP 0 IS RECEIVED
		* @param totalFreeSpins: total freespins
		* @param totalMulty: total multiplier
		*/
		void onBonusFreeSpinStep0Received(int totalFreeSpins, int totalMulty);
		/**
		* FUNCTION CALLED WHEN FREE SPIN BONUS STEP 1 IS RECEIVED
		* @param iFinish: check if should finish FreeSpin
		* @param totalFreeSpins: total freespins won
		* @param totalMulty: total multiplier won
		* @param aWheels: array wheels info
		*/
		void onBonusFreeSpinStep1Received(bool iFinish, int totalFreeSpins, int totalMulty, const std::vector<ObjectBonus>& aWheels);
	};
}
