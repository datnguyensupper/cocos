#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"

namespace GameSlot {
	class CBonusPalaceLN : public CBonusBase
	{
	private:
		cocos2d::Vec2* aPosNormal;
		cocos2d::Vec2* aPosTouched;

		std::string* aNameSpriteNormal;
		std::string* aNameSpriteTouched;


		std::vector<cocos2d::Sprite*> aBox;
		std::vector<cocos2d::Label*> aText;

		cocos2d::Sprite* oRule;
		cocos2d::Sprite* oExplosion;
		/**
		* Initialize - Create UI
		*/
		bool init() override;
		/**
		* Create Weapon Group (Sprite + Button) on the Scene and manage its input event
		* @param index: index of icon
		*/
		void createWeaponButton(int index);
		/**
		* Enable all button
		*/
		void enableAllBtn() override;
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		bool btnGamblingClicked(int iIndex) override;
		/**
		 * Set the sprite and text UI of Weapon icon
		 * @param index: index of icon
		 * @param iWin: win amount
		 * @param bSelected: boolean - check if this is selected by User
		 */
		void setBtnSprite(int index, double iWin, bool bSelected);
	public:
		CBonusPalaceLN(CGameBase* oGame);
		~CBonusPalaceLN();

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
