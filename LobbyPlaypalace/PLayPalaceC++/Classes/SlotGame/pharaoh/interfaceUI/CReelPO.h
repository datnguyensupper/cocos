#pragma once

#include "SlotGame/base/interfaceUI/CReel.h"

namespace GameSlot {
	class CGameBase;
	class CReelPO : public CReel {
	private:
		/**
		* Show next symbol's win
		* @param aWinningLine: pointer of aWinningLine;
		* @param cb: cb after show animation
		*/
		void showNextWin(const ObjectWinningLine& aWinningLine, const std::function<void()>& cb) override;
	public:
		CReelPO(CGameBase* oGame);
		/**
		* init columns
		*/
		void initCols(int* aStartingWheel) override;
		/**
		* Start Spinning the reel
		*/
		void startSpin() override;
		/**
		* reel arrived
		*/
		void reelArrived(int iReelIndex) override;
	};
	class CReelColumnPO : public CReelColumn {
	private:
		cocos2d::Sprite* oFrameWin;
		cocos2d::Sprite* oFrameText;
	public:
		CReelColumnPO(CReel* oReel);
		/**
		* RESET Y POSITION OF THE REEL
		* @param aSymbols: array of 3 symbols
		* @param bReadyToStop: boolean - check if it's ready to Stop movement
		*/
		virtual void restart(int* aSymbols, bool bReadyToStop);
		/**
		* Reset col after spin or show anim
		*/
		virtual void reset();
		/**
		* init win frame
		*/
		void initWinFrame(cocos2d::Node* oAttachWinFrame) override;
		/**
		* HIGHLIGHT SYMBOL WHEN IS INVOLVED IN WINNING COMBO
		* @param iIndex: index of symbol involved
		*/
		void highlightSymbol(int iIndex) override;
		/**
		* HIGHLIGHT SYMBOL THAT CONTROL SHOW WIN
		* @param iIndex: index of symbol
		*/
		void highlightSymbolAnim(int iIndex, int iLoopsTime, const std::function<void()>& cb);
	};
}