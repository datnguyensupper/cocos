#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

class CSpinWheel;
namespace GameSlot {
	class CGameBase;
	class CBonusStage2PO : public CBonusBase
	{
	private:
		cocos2d::Sprite* oRule;
		cocos2d::Node* oWheelBG;
		CSpinWheel* oWheel;

		std::vector<cocos2d::Sprite*> aGem;

		cocos2d::Label* oWinIndicator;
		cocos2d::Label* oBetIndicator;
		cocos2d::Label* oMulIndicator;

		int iModeBonus;

		int iTotMulty;
		double iTotWin1;
		double iTotWin2;
		/**
		* Initialize - Create UI
		*/
		bool init() override;
		/**
		* On Bonus Entered
		*/
		void onBonusEntered() override;
		/**
		* Create box sprite and text UI
		* @param boxSpriteName: sprite name of Box Image
		* @param pos: Position
		* @param text: string - text
		* @param scaleTextValue: text's scale value
		* @returns {*} sprite Object
		*/
		cocos2d::Label* createIndicator(const std::string& boxSpriteName, const cocos2d::Vec2& pos, const std::string& text, float scaleTextValue);
		/**
		* Update text Result after Rollong Wheel
		* @param iWin: win amount
		* @param totalMulty: total Multiplier
		*/
		void showResultAfterRol();
		/**
		* Show final win or exit when finishing Bonus
		*/
		void showFinalWin(float delay) override;
		/**
		* Reset function
		*/
		void resetBonus() override;
	public:
		CBonusStage2PO(CGameBase* oGame);
		~CBonusStage2PO();
		/**
		* Show function
		* @param iModeBonus
		*/
		void show(int iModeBonus);
		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: boolean - true if finish Bonus
		* @param aWheels: array wheels info
		* @param iIndex: index User selected
		* @param isFromRestore: is from restore
		*/
		void showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore = false) override;
	};
}
