#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "SlotGame/base/settings/CSettings.h"
#include "SlotGame/base/object/InfoObject.h"

namespace GameSlot {
	class CGameBase;
	class CReelColumn;
	class CWinAnim;
	class CLines;
	class CReel : public cocos2d::Node
	{
	protected:
		int iCurReelLoops;
		int iNumReelsStopped;

		int iCurWin;

		CGameBase* oGame;
		std::vector<ObjectWinningLine>* aWinningLine;

		cocos2d::Node* oAttachSymbols;
		cocos2d::Node* oAttachWinFrame;
		cocos2d::Node* oAttachWinAnim;

		cocos2d::Vector<CReelColumn*> aMovingColumns;

		CWinAnim* oWinAnim;
		CLines* oLines;
		/**
		* Show next symbol's win
		* @param aWinningLine: pointer of aWinningLine;
		* @param cb: cb after show animation
		*/
		virtual void showNextWin(const ObjectWinningLine& aWinningLine, const std::function<void()>& cb);
	public:
		CReel(CGameBase* _oGame);
		virtual ~CReel();

#pragma region getter
		CWinAnim* getWinAnim() { return this->oWinAnim; }
		CLines* getLines() { return this->oLines; }
#pragma endregion


		virtual bool init(int* aStartingWheel);
		/**
		* init columns
		*/
		virtual void initCols(int* aStartingWheel);
		/**
		* init lines
		*/
		virtual void initLines();
		/**
		* init win anim
		*/
		virtual void initWinAnim();
		/**
		* Start Spinning the reel
		*/
		virtual void startSpin();
		/**
		* Stop Spinning
		*/
		virtual void stopSpin();
		/**
		* reel arrived
		*/
		virtual void reelArrived(int iReelIndex);
		/**
		* end arrived
		*/
		virtual void stopReel();
		/**
		* Show All Win Animation
		* @param aWinningLine: pointer of aWinningLine;
		*/
		virtual void showWin(std::vector<ObjectWinningLine>* aWinningLine);
		/**
		* Check and show next win
		*/
		virtual void checkAndShowNextWin();
		/**
		* Show One Win Animation
		* @param aWinningLine: pointer of aWinningLine;
		* @param cb: cb after show animation
		*/
		virtual void showSymbolWin(const ObjectWinningLine& aWinningLine, const std::function<void()>& cb = nullptr);
		/**
		* SHOW THE WINNING LINE FOR THE CURRENT COMBO
		* @private
		*/
		virtual void showNextWinPayline();
		/**
		* Stop Win Animation
		*/
		virtual void stopWin();
		/**
		* Reset before spin
		*/
		virtual void resetReel();
		/**
		* get Reel Col
		*/
		CReelColumn* getReelColumn(int index) { return this->aMovingColumns.at(index); };
	};

	class CReelColumn : public cocos2d::Node
	{
	protected:
		int iIndex; 
		std::vector<int> aSymbolValues;
		bool bIsSpinning;
		bool bReadyToStop;
		CReel* oReel;
		REEL_STATE iCurState;

		cocos2d::Node* oHightLight;

		float iCntFrames;
		float iMaxFrames;

		int iCurStartY;
		int iFinalY;

		bool bPlayEndSound;

		cocos2d::tweenfunc::TweenType movingTweenType;
		cocos2d::tweenfunc::TweenType stopTweenType;

	public:
		CReelColumn(CReel* oReel);
		virtual ~CReelColumn();

		virtual bool init(
			int iIndex, 
			const cocos2d::Vec2& vPos, 
			int* aSymbols, 
			cocos2d::Node* oAttachSymbols,
			cocos2d::Node* oAttachWinFrame);
		/**
		* init win frame
		*/
		virtual void initWinFrame(cocos2d::Node* oAttachWinFrame);
		/**
		* RESET Y POSITION OF THE REEL
		* @param aSymbols: array of 3 symbols
		* @param bReadyToStop: boolean - check if it's ready to Stop movement
		*/
		virtual void restart(int* aSymbols, bool bReadyToStop, int* aLuckySymbols = nullptr);
		/**
		* Reset col after spin or show anim
		*/
		virtual void reset();
		/**
		* HIGHLIGHT SYMBOL WHEN IS INVOLVED IN WINNING COMBO
		* @param iIndex: index of symbol involved
		*/
		virtual void highlightSymbol(int iIndex);
		/**
		* HIDE SYMBOLS SPRITE ON ROW
		* @param iRow: row need to hide
		*/
		virtual void hideSymbol(int iRow);
		/**
		* Moving Reel Method
		*/
		virtual void moving();
		/**
		* Set array symbol for column
		* @param aSymbols: array of 3 symbols
		* @param startIndex
		*/
		virtual void setSymbol(int* aSymbols = nullptr, int startIndex = 0);
		/**
		* Update func
		*/
		virtual void updateReelSpinning(float dt);
		/**
		* Update start func
		*/
		virtual void updateStart(float dt);
		/**
		* Update moving func
		*/
		virtual void updateMoving(float dt);
		/**
		* Update stop func
		*/
		virtual void updateStop(float dt);
		/**
		* Update func
		*/
		virtual void updateReelPosition(float fLerp);
		/**
		* get a symbol's pos of this col
		* @param row: symbol's row
		*/
		cocos2d::Vec2 getSymbolPos(int row) const { return this->getPosition() + this->getChildren().at(row)->getPosition(); }
		/**
		* check reel contains symbol or not
		* @param row: symbol's row
		*/
		bool checkContainSymbol(int oSymbol) const { return std::find(this->aSymbolValues.begin(), this->aSymbolValues.end(), oSymbol) != this->aSymbolValues.end(); }
		/**
		* Kiet: 2017-04-25: setup lucky symbol effect
		*/
		void setupLuckySymbol(int *aLuckySymbol);
	};

	class CWinAnim : public cocos2d::Node {
	protected:
		CReel* oReel;
		cocos2d::Sprite* oAnimSymbol;
		std::function<void()> callback;

		cocos2d::Node* oAmountWin;
		cocos2d::Label* oAmountWinText;
	public:
		CWinAnim(CReel* oReel);
		virtual ~CWinAnim();
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/**
		* SHOW THE SYMBOL ANIMATION
		* @param ObjectCell: cell info
		* @param oPos: position of symbol
		* @param iSymbol: value of symbol
		* @param iAmountWin: win amount
		* @param loopTimes: loop times animation
		* @param cb: callback
		*/
		virtual void show(
			const ObjectCell& cell,
			const cocos2d::Vec2& oPos,
			int iSymbol, 
			int iAmountWin,
			int loopTimes,
			const std::function<void()>& cb);
		/**
		* RESET ANIMATION
		*/
		void reset();

		cocos2d::Node* getAmountWin() { return this->oAmountWin; }
		cocos2d::Label* getText() { return this->oAmountWinText; }
		void setTextColor(const cocos2d::Color4B& fillColor, const cocos2d::Color4B& outlineColor = cocos2d::Color4B::WHITE);
	};

	class CLines : public cocos2d::Sprite {
	private:
		CReel* oReel;
		cocos2d::Vec2* aPosLines;
	public:
		CLines(CReel* oReel);
		virtual ~CLines();
		/**
		* init function
		*/
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/**
		* SHOW THE CURRENT PAYLINE
		* @param iLine: line index need to show
		*/
		virtual void showLine(int iLine);
		/**
		* HIDE THE CURRENT PAYLINE
		*/
		void hideLine() { this->setVisible(false); }
	};
}
