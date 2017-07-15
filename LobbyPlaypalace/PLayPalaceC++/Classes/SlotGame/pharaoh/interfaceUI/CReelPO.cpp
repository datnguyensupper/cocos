#include "CReelPO.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CReelPO::CReelPO(CGameBase* oGame):CReel(oGame)
	{
	}
	void CReelPO::initCols(int * aStartingWheel)
	{
		auto iXPos = CSettings::REEL_OFFSET_X;
		auto iYPos = CSettings::REEL_OFFSET_Y;

		int iCont = 0;
		int* aSymbols = new int[3];

		for (int i = 0; i < CSettings::NUM_REELS; i++) {
			aSymbols[0] = aStartingWheel[iCont];
			aSymbols[1] = aStartingWheel[iCont + 1];
			aSymbols[2] = aStartingWheel[iCont + 2];

			auto column = new CReelColumnPO(this);
			column->init(
				i,
				Vec2(iXPos, iYPos),
				aSymbols,
				this->oAttachSymbols,
				this->oAttachWinFrame);

			this->aMovingColumns.pushBack(column);

			iXPos += CSettings::SYMBOL_WIDTH + CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS;
			iCont += 3;

		}
		CC_SAFE_DELETE_ARRAY(aSymbols);
	}

	void CReelPO::startSpin()
	{
		this->iCurReelLoops = 0;
		this->iNumReelsStopped = 0;
		Vector<FiniteTimeAction*> actions;

		for (int i = aMovingColumns.size() - 1; i >= 0; --i) {
			actions.pushBack(Sequence::createWithTwoActions(
				DelayTime::create(CSettings::TIMER_DELAY_BETWEEN_TWO_COL),
				CallFunc::create([this, i]() {
				this->aMovingColumns.at(i)->moving();
			})));
		}

		this->runAction(Sequence::create(actions));
	}

	void CReelPO::reelArrived(int iReelIndex)
	{
		if (this->oGame->getMain()->isReadyToSpin() &&
			this->oGame->isReadyStopReel() &&
			this->iCurReelLoops > CSettings::MIN_REEL_LOOPS) {
			auto aCurWheel = this->oGame->getCurWheel();
			//ALERT HIM THAT IT MUST STOP
			this->aMovingColumns.at(iReelIndex)->restart(new int[3]{
				aCurWheel[0][iReelIndex],
				aCurWheel[1][iReelIndex],
				aCurWheel[2][iReelIndex] },
				true);
		}
		else {
			//...OTHERWISE IT MUST CONTINUE REPOSITIONING ITSELF
			this->aMovingColumns.at(iReelIndex)->restart(this->oGame->generateRandSymbols(), false);
			if (iReelIndex == 0) {
				this->iCurReelLoops++;
			}
		}
	}
	void CReelPO::showNextWin(const ObjectWinningLine & aWinningLine, const std::function<void()>& cb)
	{
		//If this is bonus winning
		if (aWinningLine.isBonus) {
			this->oGame->getInterface()->setButtonSpinVisible(false);
		}

		auto aList = aWinningLine.list;
		auto iCol = aWinningLine.colAnim;
		auto loopTimes = 0;
		if (iCol >= 0) {
			auto oPos = this->aMovingColumns.at(aList[iCol].col)->getSymbolPos(aList[iCol].row);

			//HIDE THE SYMBOL BEHIND THE ANIMATION
			this->aMovingColumns.at(aList[iCol].col)->hideSymbol(aList[iCol].row);

			auto iAmountWon = aWinningLine.amount;
			loopTimes = ((this->oGame->getCurrentType() == GAME_TYPE::FREE_SPIN) || this->oGame->isAutoSpin() && !aWinningLine.isBonus) ? 1 : 3;
			this->oWinAnim->show(aList[iCol], oPos, aWinningLine.value, iAmountWon, loopTimes, cb);
		}

		//HIGHLIGHT OTHER SYMBOLS INVOLVED IN THE WINNING COMBO
		for (auto cell : aList) {
			if (cell.col == iCol) {
				((CReelColumnPO*)this->aMovingColumns.at(cell.col))->highlightSymbolAnim(cell.row, loopTimes, cb);
			}
			else {
				this->aMovingColumns.at(cell.col)->highlightSymbol(cell.row);
			}
		}

		//SHOW WINNING LINE
		auto iLineIndex = aWinningLine.line;
		if (iLineIndex > 0) {
			this->oLines->showLine(iLineIndex);
		}
		this->iCurWin++;
	}

	CReelColumnPO::CReelColumnPO(CReel * oReel): CReelColumn(oReel)
	{
		this->movingTweenType = tweenfunc::TweenType::Linear;
		this->stopTweenType = tweenfunc::TweenType::Elastic_EaseOut;
	}
	void CReelColumnPO::restart(int * aSymbols, bool bReadyToStop)
	{
		CReelColumn::restart(aSymbols, bReadyToStop);
		if (this->bReadyToStop) {
			this->iMaxFrames = CSettings::MAX_FRAMES_REEL_EASE * 3;
		}
	}
	void CReelColumnPO::reset()
	{
		CReelColumn::reset();
		this->oFrameWin->stopAllActions();
	}
	void CReelColumnPO::initWinFrame(cocos2d::Node * oAttachWinFrame)
	{
		CReelColumn::initWinFrame(oAttachWinFrame);

		this->oFrameWin = Sprite::createWithSpriteFrameName("symbol_frame_winVFX_0");
		this->oHightLight->addChild(this->oFrameWin);

		this->oFrameText = Sprite::createWithSpriteFrameName("symbol-wild-en");
		this->oFrameText->setPosition(Vec2(0, -CSettings::SYMBOL_HEIGHT / 2));
		this->oFrameText->setAnchorPoint(Vec2(0.5f, 0));
		this->oHightLight->addChild(this->oFrameText);
	}
	void CReelColumnPO::highlightSymbol(int iIndex)
	{
		CReelColumn::highlightSymbol(iIndex);
		this->oFrameWin->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().mainGame["frame_win_plist"],
			"symbol_frame_winVFX_%i",
			0,
			24,
			CSettings::ANIM_SYMBOL_FPS,
			-1
			));

		switch (this->aSymbolValues[iIndex]){
		case 9:
			this->oFrameText->setSpriteFrame("symbol-bonus-en");
			this->oFrameText->setVisible(true);
			break;
		case 10:
			this->oFrameText->setSpriteFrame("symbol-scatter-en");
			this->oFrameText->setVisible(true);
			break;
		case 11:
			this->oFrameText->setSpriteFrame("symbol-wild-en");
			this->oFrameText->setVisible(true);
			break;
		default:
			this->oFrameText->setVisible(false);
			break;
		}
	}
	void CReelColumnPO::highlightSymbolAnim(int iIndex, int iLoopsTime, const std::function<void()>& cb)
	{
		CReelColumn::highlightSymbol(iIndex);
		this->oFrameWin->runAction(Sequence::createWithTwoActions(
			AnimationHelper::getInstance()->createAnimationByFrameName(
				GameConstant::getInstance()->getResources().mainGame["frame_win_plist"],
				"symbol_frame_winVFX_%i",
				0,
				24,
				CSettings::ANIM_SYMBOL_FPS,
				iLoopsTime
				),
			CallFunc::create(cb)));

		switch (this->aSymbolValues[iIndex]) {
		case 9:
			this->oFrameText->setSpriteFrame("symbol-bonus-en");
			this->oFrameText->setVisible(true);
			break;
		case 10:
			this->oFrameText->setSpriteFrame("symbol-scatter-en");
			this->oFrameText->setVisible(true);
			break;
		case 11:
			this->oFrameText->setSpriteFrame("symbol-wild-en");
			this->oFrameText->setVisible(true);
			break;
		default:
			this->oFrameText->setVisible(false);
			break;
		}
	}
}
