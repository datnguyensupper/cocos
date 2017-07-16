#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"


namespace GameSlot {
	class CDoubleUpDB : public CBonusBase
	{
	private:
		cocos2d::Size oCurrentWinBgOriginalSize;
		cocos2d::ui::Scale9Sprite * oCurrentWinBg;
		cocos2d::Label* oCurrentWinTxt;
		cocos2d::Size oPotentialWinBgOriginalSize;
		cocos2d::ui::Scale9Sprite * oPotentialWinBg;
		cocos2d::Label* oPotentialWinTxt;

		cocos2d::Node* oFishContainer;

		cocos2d::Sprite* oAnglerFishLeft;
		cocos2d::Sprite* oAnglerFishRight;
		cocos2d::Sprite* oBlueFish;

		cocos2d::Sprite* oResult;
		/**
		* Initialize - Create UI
		*/
		bool init() override;
		/**
		* On Bonus Entered
		*/
		void onBonusEntered() override;
		/**
		* Init Animation
		*/
		void initAnimaton();
		/**
		* Restore last Bonus that hasn't finished
		*/
		virtual void restore() override;
		/**
		* Create Game Button on the Scene and manage its input event
		* @param index: index of icon
		* @param frameName: sprite frame name
		* @param pos: button position
		*/
		void createButton(int index, const std::string& frameName, const cocos2d::Vec2& pos);
		/**
		* Play Result Animation
		*/
		void playResultAnimation(bool isEscape);
		/**
		* Update Win Text
		*/
		void updateTotalWinText();
	public:
		CDoubleUpDB(CGameBase* oGame);
		~CDoubleUpDB();

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
