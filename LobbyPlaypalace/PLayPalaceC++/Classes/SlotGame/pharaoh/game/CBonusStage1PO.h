#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

namespace GameSlot {
	class CBonusStage1PO : public CBonusBase
	{
	private:
		std::vector<cocos2d::Sprite*> aHeaderSymbols;

		cocos2d::Sprite* oRule;

		cocos2d::Sprite* oLeftDoor;
		cocos2d::Sprite* oRightDoor;

		bool bWinBonusStage2;
		int iCurHeaderSymbol;
		/**
		* Initialize - Create UI
		*/
		bool init() override;
		/**
		* On Bonus Entered
		*/
		void onBonusEntered() override;
		/**
		* Create Weapon Group (Sprite + Button) on the Scene and manage its input event
		* @param index: index of icon
		*/
		void createDoorButton(int index);
		/**
		* Run animation prepare to go to bonus stage 2
		* @param aWheels: array wheels info
		*/
		void readyForBonusStage2(const std::vector<ObjectBonus>& aWheels);
		/**
		* Show Info Of Button (SPRITE + TEXT WIN)
		* @param index: button index
		* @param symbolPrize: symbol Value
		* @param symbolWin: win amount
		* @param isWin
		*/
		void showSymbolBtnInfo(int index, int symbolPrize, int symbolWin, bool isWin);
		/**
		* Exit Bonus to Main Game
		*/
		virtual void exitFromBonus();
		/**
		* Reset function
		*/
		void resetBonus() override;
	public:
		CBonusStage1PO(CGameBase* oGame);
		~CBonusStage1PO();
		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: boolean - true if finish Bonus
		* @param aWheels: array wheels info
		* @param iIndex: index User selected
		* @param isFromRestore: is from restore
		*/
		void showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore = false) override;
		std::vector<ObjectBonus> createFakeWheel(std::vector<ObjectBonus> awheel) ;
	};
}
