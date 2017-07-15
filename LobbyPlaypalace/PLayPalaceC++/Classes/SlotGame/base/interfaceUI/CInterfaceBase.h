#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "../utils/CSpriteButton.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "CFooter.h"
#include "CGameEffectUI.h"

namespace GameSlot {
	class CGameBase;
	class CFreeSpinIndicatorBase;
	class CSpinAnimation;
	class CInterfaceBase : public cocos2d::Node{
	protected:
		CGameBase* oGame;
		CFooter* oFooter;

		CGameEffectUI* oGameEffect;

		cocos2d::Size visibleSize;
		cocos2d::Vec2 origin;
		float scaleDownRatio;

		SPIN_STATE currentState;
		CSpriteButton* oButSpin;

		CSpriteButton* oButDoubleUp;

		CFreeSpinIndicatorBase* oFreeSpinIndicator;

		bool bGameHasDoubleUp;
		/**
		* init FreeSpin Indicator
		*/
		virtual void initFreeSpinIndicator();
	public:
		CFooter* getFooter() { return this->oFooter; };

		CInterfaceBase(CGameBase* oGame, bool bGameHasDoubleUp);
		virtual ~CInterfaceBase();
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

		CFreeSpinIndicatorBase* getFreeSpinIndicator() { return this->oFreeSpinIndicator; };

		CGameEffectUI* getGameEffect() { return this->oGameEffect; }
		/**
		* Function called when begin spin
		*/
		virtual void onSpinStarted ();
		/**
		* FUNCTION CALLED WHEN CLICKED SPIN BUTTON
		* @param bAutoSpin: check if it need to be auto spin
		* @private
		*/
		void onSpin(bool bAutoSpin);
		/**
		* set button spin visible status
		*/
		void setButtonSpinVisible(bool isVisible) { this->oButSpin->setVisible(isVisible); }
		/**
		* set button double up visible status
		*/
		void setButtonDoubleUpVisible(bool isVisible) { if(this->oButDoubleUp) this->oButDoubleUp->setVisible(isVisible); }
		/**
		* set button spin enabled status
		*/
		void setButtonSpinEnabled(bool isEnabled) { this->oButSpin->setTouchEnabled(isEnabled); }
		/**
		* Toggle Spin button image between spin and auto spin
		*/
		void toggleAutoSpin();
		/**
		* SET SPIN BUTTON STATE
		* @param szState: spin button state
		*/
		void setSpinState(SPIN_STATE state);
		/**
		* Show Button "Start Bonus"
		*/
		void showStartBonusBut();
		/**
		* Toggle Button "Start Free Spin"
		*/
		void showStartFreeSpinBut();
		/**
		* Set Free Spin indicator visible
		*/
		void setFreeSpinIndicatorVisible(bool isVisible);
		/**
		* Refresh Free spin
		* @param iTotFreespin: number Of Free Spin
		* @param iTotMulty: number of Multiplier
		*/
		void refreshFreeSpin(int iTotFreespin, int iTotMulty);
		/**
		* REFRESH BET TEXT VALUES
		* @param iWin: current Win
		* @param isFromBonus
		* @param cb
		*/
		void refreshBet(const double& iWin = 0, bool isFromBonus = false, const std::function<void()> & cb = nullptr);
		/**
		* Set Footer's state
		*/
		void setFooterEnabled(bool isEnabled);
	};

	class CFreeSpinIndicatorBase : public cocos2d::Node {
	protected:
		cocos2d::Node* oContainerRemaining;
		cocos2d::Label* oTextNumberFS;
		cocos2d::Label* oTextNumberMulty;

		cocos2d::Size visibleSize;
		cocos2d::Vec2 origin;
		float scaleDownRatio;

	public:
		CFreeSpinIndicatorBase();
		virtual ~CFreeSpinIndicatorBase();
		/**
		* Refresh Free Spin and Multy Remaining
		* @param iTotFreespin: number Of Free Spin
		* @param iTotMulty: number of Multiplier
		*/
		virtual void refreshRemaining(int iTotFreespin, int iTotMulty);
		/**
		* Show Wild Dragon animation
		* @param col: current Col that should show animation
		*/
		virtual void hideRemaining();
		/**
		* Show
		*/
		virtual void show();
		/**
		* Hide Wild Dragon animation
		*/
		virtual void hide();
	};
}
