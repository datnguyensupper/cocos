#pragma once

#include "cocos2d.h"

class PayLineConfig;
namespace GameSlot {
	class CGameBase;
	class CSpriteButton;
	class CFooter : public cocos2d::Node {
	private:
		CGameBase* oGame;
		std::vector<PayLineConfig> aPayLineConfig;
		std::vector<unsigned> aBet;
		PayLineConfig* currentConfig = nullptr;

		cocos2d::Label* oBetText;
		cocos2d::Label* oPayLineText;
		cocos2d::Label* oWinText = nullptr;

		CSpriteButton* oBetAdd;
		CSpriteButton* oBetMinus;

		CSpriteButton* oPaylineAdd;
		CSpriteButton* oPaylineMinus;

		int iCurBetIndex = 0;
		int iCurPayLine = 0;
		/*
		* Create a group (bet, payline) contains 2 button ("+" and "-") and a text field between
		* @param labelText:
		* @param onAdjust: cb when btn "+" or "-" is touched
		* @param bSkipButton: 
		*/
		cocos2d::Node* createAdjustGroup(const std::string& labelText, const std::function<void(int)>& onAdjust);
	public:
		bool checkCanChangeBet();

		void setEnableBtn(CSpriteButton* oBtn, bool isEnabled);

		PayLineConfig* getConfigByLevel(int iLevel);
		unsigned getMaxBet();
		unsigned getMinPayLine();
		unsigned getMaxPayLine();

		/**
		* Check if this user is allowed to change payline
		* @returns {BOOL}
		*/
		bool isLevelAllowToChangePayLine();

		CFooter(CGameBase* oGame);

		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/**
		* Refresh win Text
		* @param iWin: current Win
		* @param bAnimation: BOOL - true if playing scale animation when user win big
		*/
		void refreshWin(const double& iWin, bool bAnimation, const std::function<void()> & cb = nullptr);

		void onAdjustBet(int value);
		void onAdjustPayLine(int value);

		void reloadBetByIndex(int index);
		virtual bool reloadBet(unsigned iBet, bool force = false);
		virtual bool reloadPayline(unsigned iPayLine, bool force = false);
		/**
		* Set Footer's state
		*/
		void setAdjustEnabled(bool isEnabled);
	};
}