#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

namespace GameSlot {
	class CGameBase;
	class CBonusBattleLN : public CBonusBase
	{
	private:
		cocos2d::Sprite* oBg;
		cocos2d::Sprite* oRule;

		cocos2d::Sprite* oSpearAnim;
		cocos2d::Sprite* oResultAnim;

		std::vector<cocos2d::Node*> aRingScore;

		int iCurRing;
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
		* @param pos: button position
		*/
		void createCircleButton(int index, const cocos2d::Vec2& pos);
		/**
		* Create Ring UI (yellow ring that show result of each step in Bonus)
		* @param index: index of ring
		* @param pos: ring position
		* @returns {*} node group
		*/
		void createRingScore(int index, const cocos2d::Vec2& pos);
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		bool btnGamblingClicked(int iIndex) override;
		/**
		* Setup UI and show Result Ring
		* @param win: win amount
		* @param index: ring index
		*/
		void showRingScore(double iWin, int index);
	public:
		CBonusBattleLN(CGameBase* oGame);
		~CBonusBattleLN();

		/**
		* Show Result function : called when User has selected and received info from Server
		* @param iFinish: boolean - true if finish Bonus
		* @param aWheels: array wheels info
		* @param iIndex: index User selected
		* @param isFromRestore: is from restore
		*/
		void showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore = false) override;
		/**
		* Reset function
		*/
		void resetBonus() override;
	};
}
