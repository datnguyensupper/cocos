#pragma once

#include "cocos2d.h"

#include "../constant/GameConstant.h"

using namespace std;

namespace GameSlot {
	class CGameBase;
	class CSpriteButton;
	struct ObjectBonus;
	class CBonusBase : public cocos2d::Node
	{
	protected:
		CGameBase* oGame;
		GAME_TYPE iGameType;
		BONUS_TYPE iBonusType;
		bool bButtonClicked;
		bool bInited;
		bool bLoading;
		bool bFinish;
		double iTotWin;

		cocos2d::Size visibleSize;
		cocos2d::Vec2 origin;
		float scaleDownRatio;

		bool bGoToBonus;

		std::vector<string> aResources;

		std::vector<CSpriteButton*> aBtn;

		/**
		* Check and load all image resources to cache
		*/
		void checkAndLoadAllResources();
		/**
		* Event when completing loading all image
		*/
		void onAllImagesLoaded();
		/**
		* Initialize - Create UI
		*/
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/**
		* On Bonus Entered
		*/
		virtual void onBonusEntered();
		/**
		* Disable all button
		*/
		virtual void disableAllBtn();
		/**
		* Enable all button
		*/
		virtual void enableAllBtn();
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		virtual bool btnGamblingClicked(int iIndex);
		/**
		* Restore last Bonus that hasn't finished
		*/
		virtual void restore();
		/**
		* Show final win or exit when finishing Bonus
		*/
		virtual void showFinalWin(float delay);
		/**
		* Exit Bonus to Main Game
		*/
		virtual void exitFromBonus();
		/**
		 * Reset function
		 */
		virtual void resetBonus();
	public:
		CBonusBase(CGameBase* oGame);
		virtual ~CBonusBase();
		/**
		* Show function
		* @param currentWin: number - current Win
		*/
		virtual void show(double currentWin1 = 0, double currentWin2 = 0);
		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: BOOL - true if finish Bonus
		* @param aWheels: array wheels info
		* @param iIndex: index User selected
		* @param bFromRestore: is from restore
		*/
		virtual void showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore = false);
		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: BOOL - true if finish Bonus
		* @param iResult: result game
		* @param iTotWin: current total win
		* @param bFromRestore: is from restore
		*/
		virtual void showResult(bool bFinish, int iResult, double iTotWin, bool bFromRestore = false);
		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: BOOL - true if finish Bonus
		* @param iTotFreeSpin: total free spin
		* @param iTotMulty: total multy
		* @param aWheels: array wheels info
		* @param iIndex: index User selected
		* @param bFromRestore: is from restore
		*/
		virtual void showResult(bool bFinish, int iTotFreeSpin, int iTotMulty, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore = false);
	};
}
