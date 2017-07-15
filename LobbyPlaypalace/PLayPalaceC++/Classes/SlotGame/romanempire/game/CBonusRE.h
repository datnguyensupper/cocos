#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

class CSpinWheel;
namespace GameSlot {
	class CGameBase;
	class CBonusRE : public CBonusBase
	{
	private:
		int iTotMul;

		CSpinWheel* oWheel;
		cocos2d::Sprite* oRule;
		/**
		* Initialize - Create UI
		*/
		bool init() override;
		/**
		* Restore last Bonus that hasn't finished
		*/
		void restore() override;
		/**
		* Show final win or exit when finishing Bonus
		*/
		void showFinalWin(float delay) override;
	public:
		CBonusRE(CGameBase* oGame);
		~CBonusRE();
		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: boolean - true if finish Bonus
		* @param iTotMulty: total multy
		* @param iTotWin: total win
		*/
		virtual void showResult(bool bFinish, int iTotMulty, double iTotWin);
		/**
		* Reset function
		*/
		void resetBonus() override;
	};
}