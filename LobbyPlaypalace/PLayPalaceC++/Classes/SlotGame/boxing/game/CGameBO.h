#pragma once

#include "SlotGame/base/game/CGameBase.h"

namespace GameSlot {
	struct ObjectCardDoubleUpBO;
	class CGameBO : public CGameBase 
	{
	protected:
		/**
		* Create character model
		*/
		void initInterface() override;
		/**
		* Initialize win panel UI
		*/
		virtual void initWinPanel() override;
		/**
		* Create reel group
		*/
		void initReels() override;
		/**
		* Check Last State if there is Bonus - need to be override
		*/
		bool checkLastState() override;
		/**
		* SHOW THE BONUS GAINED BY THE USER
		*/
		virtual void launchBonus();
	public:
		CGameBO(CMainBase* _oMain);
		~CGameBO();

		bool init() override;
		/**
		* FUNCTION CALLED WHEN DOUBLE UP STEP 1 IS RECEIVED
		* @param bFinish: boolean - true if User select Collect -> Finish Game
		* @param aInfo: Double up Info
		* @param cardDealer: Dealer's card info
		*/
		void onDoubleUpStep1Received(bool bFinish,
			const std::vector<ObjectBonus>& aInfo,
			const ObjectCardDoubleUpBO& cardDealer);
		/**
		* FUNCTION CALLED WHEN DOUBLE UP STEP 2 IS RECEIVED
		* @param bFinish: boolean - true if finish Double up
		* @param iResult: info of 5 cards
		* @param iBank: User's new double balance
		* @param iSelect: index of Card that user selected
		* @param iTotWin: win amount
		*/
		void onDoubleUpStep2Received(bool bFinish,
			const std::vector<ObjectCardDoubleUpBO>& aCard,
			double iBank,
			int iSelect,
			double iTotWin);
	};
}
