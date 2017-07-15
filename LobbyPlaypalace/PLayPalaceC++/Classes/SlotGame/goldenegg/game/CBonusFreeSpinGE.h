#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

namespace GameSlot {
	class CGameBase;
	class CBonusFreeSpinGE : public CBonusBase
	{
	private:
		int iTotFreeSpin;
		int iTotMulty;

		int iCurStep;

		cocos2d::Sprite* oRule;

		std::vector<cocos2d::Node*> aEggResult;

		cocos2d::Label* oTotalFreeSpinTxt;
		cocos2d::Label* oTotalMultyTxt;
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
		* Create Circle Button on the Scene and manage its input event
		* @param index: index of icon
		* @param pos: button position
		*/
		void createFish(int index, const cocos2d::Vec2& pos);
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		bool btnGamblingClicked(int iIndex) override;
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
		CBonusFreeSpinGE(CGameBase* oGame);
		~CBonusFreeSpinGE();

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
