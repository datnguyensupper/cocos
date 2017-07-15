#pragma once

#include "ui/CocosGUI.h"
#include "SlotGame/base/game/CBonusBase.h"
#include "SlotGame/base/object/InfoObject.h"

namespace GameSlot {
	struct ObjectCardDoubleUpBO : ObjectAdditionInfo
	{
		int id;
		int suit;
		int value;

		ObjectCardDoubleUpBO() {
			this->id = this->suit = this->value = 0;
		}
		ObjectCardDoubleUpBO(int id,
			int suit,
			int value) {
			this->id = id;
			this->suit = suit;
			this->value = value;
		}
	};
	struct ObjectCardUI
	{
		CSpriteButton* btn = nullptr;
		float angleSprite;
		float angleText;
		cocos2d::Vec2 posText;
	};
	class CDoubleUpBO : public CBonusBase
	{
	private:
		cocos2d::Sprite* oDealerCard;

		cocos2d::Sprite* oHeaderRule;

		cocos2d::Sprite* oPlayerText;

		cocos2d::Label* oWin;
		cocos2d::Label* oBet;
		cocos2d::Label* oBank;
		cocos2d::Label* oDoubleHalf;
		cocos2d::Label* oDouble;

		std::vector<ObjectCardUI> aPickCard;
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
		virtual void restore();
		/**
		* Call back when user touch button
		* @param iIndex: button Index
		*/
		bool btnCardClicked(int iIndex);
		/**
		* Disable all button
		*/
		void disableAllPickBtn();
		/**
		* Enable all button
		*/
		void enableAllPickBtn();
		/**
		* Create Game Button on the Scene and manage its input event
		* @param index: index of icon
		* @param frameName: sprite frame name
		* @param pos: button position
		*/
		void createCardButton(int index,
			float angleSprite,
			float angleText, 
			const cocos2d::Vec2& pos,
			const cocos2d::Vec2& posText);
		/**
		* Update texts
		* @param select: selection of User (Double or Double Half)
		* @param bank: current double up's balance of user (not game balance)
		* @param bet: bet amount
		* @param winPot: potential win amount
		*/
		void updateTotalWinText(int select, double bank, double bet, double winPot);
		int const getCardID(int suit, int value);
		/**
		* Show CARD UI
		* @param index: card index
		* @param cardID: Id of card
		* @param opacity: Sprite's opacity value
		* @param isDealer: boolean - true if this card is from Dealer(not User)
		*/
		void showCard(int index, int cardID, int opacity, bool isDealer = false);
		/**
		* Show other Card that User didn't select
		* @param listCard
		* @param iSelect
		*/
		void showOtherCard(const std::vector<ObjectCardDoubleUpBO>& aCard, int iSelect);
	public:
		CDoubleUpBO(CGameBase* oGame);
		~CDoubleUpBO();
		/**
		* Update UI when User go to step select Card
		* @param bFinish: boolean - true if User select Collect -> Finish Game
		* @param aInfo: Double up Info
		* @param cardDealer: Dealer's card info
		*/
		void showCardToPick(bool bFinish,
			const std::vector<ObjectBonus>& aInfo,
			const ObjectCardDoubleUpBO& cardDealer);
		/**
		* Show Result function : called when User has selected a card and received info from Server
		* @param bFinish: boolean - true if finish Double up
		* @param iResult: info of 5 cards
		* @param iBank: User's new double balance
		* @param iSelect: index of Card that user selected
		* @param iTotWin: win amount
		*/
		void showResult(bool bFinish,
			const std::vector<ObjectCardDoubleUpBO>& aCard,
			double iBank, 
			int iSelect,
			double iTotWin);
		/**
		* Reset function
		*/
		void resetBonus() override;
	};
}
