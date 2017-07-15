#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

namespace GameSlot {
	class CDoubleUpRE : public CBonusBase
	{
	private:
		cocos2d::Sprite* oBg;
		cocos2d::Sprite* oBgResult;

		cocos2d::Node* oInfo;

		cocos2d::Vector<cocos2d::SpriteFrame*> aResultHeadFrame;
		cocos2d::Vector<cocos2d::SpriteFrame*> aResultTailFrame;

		cocos2d::Label* oCurrentWinTxt;
		cocos2d::Label* oPotentialWinTxt;
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
		* @param nameType
		* @param pos: button position
		*/
		void createButtonCoin(int index, const std::string& nameType, const cocos2d::Vec2& pos);
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		bool btnGamblingClicked(int iIndex) override;
		/**
		* Play Result Animation
		*/
		void playResultAnimation(bool isHead);
		/**
		* Update Win Text
		*/
		void updateTotalWinText();
	public:
		CDoubleUpRE(CGameBase* oGame);
		~CDoubleUpRE();

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