#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

namespace GameSlot {
	class CDoubleUpGE : public CBonusBase
	{
	private:
		cocos2d::Label* oCurrentWinTxt;
		cocos2d::Label* oPotentialWinTxt;

		cocos2d::Sprite* oResultEgg;
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
		virtual void restore() override;
		/**
		* Create Game Button on the Scene and manage its input event
		* @param index: index of icon
		* @param eggName: egg type name
		* @param pos: button position
		*/
		void createEggButton(int index,
			const std::string& eggName, 
			const cocos2d::Vec2& pos);
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		bool btnGamblingClicked(int iIndex) override;
		/**
		* Play Result Animation
		* @param isNormalEgg: 
		*/
		void playResultAnimation(bool isNormalEgg);
		/**
		* Update Win Text
		*/
		void updateTotalWinText();
	public:
		CDoubleUpGE(CGameBase* oGame);
		~CDoubleUpGE();

		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: boolean - true if finish Bonus
		* @param iResult: result game
		* @param iTotWin: current total win
		* @param bFromRestore: is from restore
		*/
		virtual void showResult(bool bFinish, int iResult, double iTotWin, bool bFromRestore = false);
		/**
		* Reset function
		*/
		void resetBonus() override;
	};
}
