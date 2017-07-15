#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

namespace GameSlot {
	class CGameBase;
	class CBonusFreeSpinDB : public CBonusBase
	{
	private:
		int iTotFreeSpin;
		int iTotMulty;

		cocos2d::Sprite* oRule;

		cocos2d::Label* oTotalTxt;

		std::vector<cocos2d::Label*> aTextWin;
		int iCurStep = 0;
		/**
		* Initialize - Create UI
		*/
		bool init() override;
		/**
		* On Bonus Entered
		*/
		void onBonusEntered() override;
		/**
		* Restore last Bonus that hasn't finished
		*/
		virtual void restore();
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		virtual bool btnGamblingClicked(int iIndex);
		/**
		* Create Circle Button on the Scene and manage its input event
		* @param index: index of icon
		* @param pos: button position
		*/
		void createFish(int index, const cocos2d::Vec2& pos, float scale);
		/**
		* Setup Win Amount Text
		* @param win: win amount
		* @param iType: win type
		*/
		void showWinAmountText();
		/**
		* Show final win or exit when finishing Bonus
		*/
		void showFinalWin(float delay) override;
		/**
		* Exit Bonus to Main Game
		*/
		void exitFromBonus() override;
	public:
		CBonusFreeSpinDB(CGameBase* oGame);
		~CBonusFreeSpinDB();

		/**
		* Show function
		* @param currentWin: number - current Win
		*/
		void show(double currentWin1 = 0, double currentWin2 = 0) override;
		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: boolean - true if finish Bonus
		* @param iTotFreeSpin: total free spin
		* @param iTotMulty: total multy
		* @param aWheels: array wheels info
		* @param iIndex: index User selected
		* @param bFromRestore: is from restore
		*/
		virtual void showResult(bool bFinish, int iTotFreeSpin, int iTotMulty, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore = false);
		/**
		* Reset function
		*/
		void resetBonus() override;
	};
}
