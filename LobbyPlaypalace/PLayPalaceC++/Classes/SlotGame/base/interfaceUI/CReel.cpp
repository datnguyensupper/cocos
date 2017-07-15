#include "CReel.h"
#include "../game/CGameBase.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
#pragma region CReel
	CReel::CReel(CGameBase * oGame): Node(),
		oGame(oGame),
		iNumReelsStopped(0),
		iCurReelLoops(0),
		iCurWin(0),
		aWinningLine(nullptr),
		oWinAnim(nullptr),
		oLines(nullptr)
	{
		this->autorelease();
		this->oGame->addChild(this, ORDER_REEL);
	}
	CReel::~CReel()
	{
		aMovingColumns.clear();
	}
	bool CReel::init(int* aStartingWheel)
	{
		if (!Node::init()) return false;

		auto resGame = GameConstant::getInstance()->getResources().mainGame;

		this->oAttachSymbols = ClippingNode::create();
		this->oAttachWinFrame = Node::create();

		if (resGame.find("reel") != resGame.end()) {
			auto bg = Helper4Sprite::createOptimizeSprite(resGame["reel"]);
			GameUtils::centerNode(bg);
			this->addChild(bg, ORDER_REEL_BG);
		}

		auto iXPos = CSettings::REEL_OFFSET_X;
		auto iYPos = CSettings::REEL_OFFSET_Y;

		auto stencil = DrawNode::create();
		stencil->drawSolidRect(
			Point(iXPos, iYPos),
			Point(
				iXPos + CSettings::WIDTH_REEL,
				iYPos - CSettings::HEIGHT_REEL),
			Color4F(0, 0, 0, 0));

		((ClippingNode*)this->oAttachSymbols)->setStencil(stencil);

		this->initCols(aStartingWheel);

		this->addChild(this->oAttachSymbols, ORDER_REEL_SYMBOLS);
		this->addChild(this->oAttachWinFrame, ORDER_REEL_FRAMEWIN);

		if (this->oGame->getMain()->isReadyToSpin()) {
			this->initLines();
		}
		this->initWinAnim();

		return true;
	}
	void CReel::initCols(int* aStartingWheel)
	{
		auto iXPos = CSettings::REEL_OFFSET_X;
		auto iYPos = CSettings::REEL_OFFSET_Y;

		int iCont = 0;
		int* aSymbols = new int[3];

		for (int i = 0; i < CSettings::NUM_REELS; i++) {
			aSymbols[0] = aStartingWheel[iCont];
			aSymbols[1] = aStartingWheel[iCont + 1];
			aSymbols[2] = aStartingWheel[iCont + 2];

			auto column = new CReelColumn(this);
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
	void CReel::initLines()
	{
		if (this->oLines) {
			return;
		}
		this->oLines = new CLines(this);
		this->oLines->init();
	}
	void CReel::initWinAnim()
	{
		this->oWinAnim = new CWinAnim(this);
		this->oWinAnim->init();
	}
	void CReel::startSpin()
	{
		this->iCurReelLoops = 0;
		this->iNumReelsStopped = 0;
		Vector<FiniteTimeAction*> actions;

		for (auto col : aMovingColumns) {
			actions.pushBack(Sequence::createWithTwoActions(
				DelayTime::create(CSettings::TIMER_DELAY_BETWEEN_TWO_COL),
				CallFunc::create([this, col]() {
				col->moving();
			})));
		}

		this->runAction(Sequence::create(actions));
	}
	void CReel::stopSpin()
	{

	}
	void CReel::reelArrived(int iReelIndex)
	{
		if (this->oGame->getMain()->isReadyToSpin() &&
			this->oGame->isReadyStopReel() &&
			this->iCurReelLoops > CSettings::MIN_REEL_LOOPS) {
			//IF THE CURRENT REEL IS THE NEXT ONE THAT MUST STOP...
			if (this->iNumReelsStopped == iReelIndex) {
				auto aCurWheel = this->oGame->getCurWheel();
				if (this->oGame->getObjectMagicItemAfterSpin()) {
					auto aLuckySymbolWheel = this->oGame->getObjectMagicItemAfterSpin()->aLuckySymbolWheels;
					//ALERT HIM THAT IT MUST STOP
					this->aMovingColumns.at(iReelIndex)->restart(new int[3]{
						aCurWheel[0][iReelIndex],
						aCurWheel[1][iReelIndex],
						aCurWheel[2][iReelIndex] },
						true,
						new int[3]{
						aLuckySymbolWheel[0][iReelIndex],
						aLuckySymbolWheel[1][iReelIndex],
						aLuckySymbolWheel[2][iReelIndex] }
					);
				}
				else {
					this->aMovingColumns.at(iReelIndex)->restart(new int[3]{
						aCurWheel[0][iReelIndex],
						aCurWheel[1][iReelIndex],
						aCurWheel[2][iReelIndex] },
						true
					);

				}
			}
			else {
				//OTHERWISE CONTINUE LOOPING
				this->aMovingColumns.at(iReelIndex)->restart(this->oGame->generateRandSymbols(), false);
			}
		}
		else {
			//...OTHERWISE IT MUST CONTINUE REPOSITIONING ITSELF
			this->aMovingColumns.at(iReelIndex)->restart(this->oGame->generateRandSymbols(), false);
			if (iReelIndex == 0) {
				this->iCurReelLoops++;
			}
		}
	}
	void CReel::stopReel()
	{
		this->iNumReelsStopped++;
		this->oGame->onStopOneReelColumn(this->iNumReelsStopped);
		if (this->iNumReelsStopped == this->aMovingColumns.size()) {
			this->oGame->onStopReel();
		}
	}

	void CReel::showNextWin(const ObjectWinningLine& aWinningLine, const std::function<void()>& cb)
	{
		//If this is bonus winning
		if (aWinningLine.isBonus) {
			this->oGame->getInterface()->setButtonSpinVisible(false);
		}

		auto aList = aWinningLine.list;

		auto iCol = aWinningLine.colAnim;
		if (iCol >= 0) {
			auto oPos = this->aMovingColumns.at(aList[iCol].col)->getSymbolPos(aList[iCol].row);

			//HIDE THE SYMBOL BEHIND THE ANIMATION
			this->aMovingColumns.at(aList[iCol].col)->hideSymbol(aList[iCol].row);

			auto iAmountWon = aWinningLine.amount;
			auto loopTimes = ((this->oGame->getTotFreeSpin() > 0 || this->oGame->isEndFreeSpin()) || this->oGame->isAutoSpin() && !aWinningLine.isBonus) ? 1 : 3;
			this->oWinAnim->show(aList[iCol], oPos, aWinningLine.value, iAmountWon, loopTimes, cb);
		}

		//HIGHLIGHT OTHER SYMBOLS INVOLVED IN THE WINNING COMBO
		for (auto cell : aList) {
			if (cell.col != aList[iCol].col) {
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
	void CReel::showWin(std::vector<ObjectWinningLine>* aWinningLine)
	{
		this->iCurWin = 0;
		this->aWinningLine = aWinningLine;
		this->checkAndShowNextWin();
	}
	void CReel::checkAndShowNextWin()
	{
		if (!this->aWinningLine) {
			return;
		}
		this->resetReel();
		if (this->iCurWin >= this->aWinningLine->size()) {
			this->iCurWin = 0;
			this->oGame->setState(GAME_STATE::GAME_IDLE);
			this->oGame->afterStopSpin(true);
			return;
		}

		this->showNextWin(this->aWinningLine->at(iCurWin), CC_CALLBACK_0(CReel::checkAndShowNextWin, this));
	}
	void CReel::showSymbolWin(const ObjectWinningLine& aWinningLine, const std::function<void()> & cb)
	{
		this->resetReel();
		this->showNextWin(aWinningLine, [this, cb]() {
			this->resetReel();
			this->iCurWin = 0;
			if (cb != nullptr) {
				cb();
			}
		});
	}
	void CReel::showNextWinPayline()
	{
		if (this->aWinningLine == nullptr || this->aWinningLine->size() == 0) {
			return;
		}
		if (this->iCurWin > 0) {
			this->resetReel();
		}

		if (this->iCurWin == this->aWinningLine->size()) {
			this->iCurWin = 0;
			if (this->oGame->isAutoSpin()) {
				this->oGame->onSpin();
				return;
			}
		}

		auto iLineIndex = this->aWinningLine->at(this->iCurWin).line;
		if (iLineIndex > 0) {
			this->oLines->showLine(iLineIndex);
		}

		auto aList = this->aWinningLine->at(this->iCurWin).list;

		//HIGHLIGHT OTHER SYMBOLS INVOLVED IN THE WINNING COMBO
		for (auto cell : aList) {
			this->aMovingColumns.at(cell.col)->highlightSymbol(cell.row);
		}

		this->iCurWin++;
	}
	void CReel::stopWin()
	{
	}
	void CReel::resetReel()
	{
		for (auto col : this->aMovingColumns) {
			col->reset();
		}
		if (this->oWinAnim) {
			this->oWinAnim->reset();
		}
		if (this->oLines) {
			this->oLines->hideLine();
		}
	}
#pragma endregion

#pragma region CReelColumn
	CReelColumn::CReelColumn(CReel* oReel) : Node(),
		bIsSpinning(false),
		bReadyToStop(false),
		oReel(oReel),
		iCntFrames(0),
		movingTweenType(tweenfunc::TweenType::Linear),
		stopTweenType(tweenfunc::TweenType::Back_EaseOut)
	{
		this->autorelease();
	}
	CReelColumn::~CReelColumn()
	{
		//CC_SAFE_DELETE_ARRAY(this->aSymbolValues);
	}
	bool CReelColumn::init(int iIndex,
		const Vec2& vPos,
		int * aSymbols,
		cocos2d::Node * oAttachSymbols,
		cocos2d::Node * oAttachWinFrame)
	{
		this->iIndex = iIndex;

		this->setPosition(vPos);
		// create sprite object for this reel
		int iX = 0;
		int iY = 0;
		this->aSymbolValues.resize(3);
		for (int i = 0; i < CSettings::NUM_ROWS * 2; ++i) {
			int iSymbol = aSymbols[i % 3];

			auto oSymbolData = Sprite::createWithSpriteFrameName("symbol_" + ToString(iSymbol) + "-0-5");
			oSymbolData->setPosition(iX, iY);
			oSymbolData->setScale(CSettings::SCALE_SYMBOL);
			oSymbolData->setAnchorPoint(Vec2(0, 1));

			this->addChild(oSymbolData);
			this->aSymbolValues[i % 3] = iSymbol;

			iY -= CSettings::SYMBOL_HEIGHT + CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS;
		}
		oAttachSymbols->addChild(this);

		this->initWinFrame(oAttachWinFrame);

		this->reset();

		this->iCurState = REEL_STATE::REEL_START;

		return true;
	}
	void CReelColumn::initWinFrame(cocos2d::Node * oAttachWinFrame)
	{
		this->oHightLight = Node::create();

		auto symbol = Sprite::createWithSpriteFrameName("symbol_0-0-5");
		symbol->setScale(CSettings::SCALE_SYMBOL);
		//symbol->setAnchorPoint(Vec2(0, 1));
		this->oHightLight->addChild(symbol);
		if (SpriteFrameCache::getInstance()->getSpriteFrameByName("frame_win")) {
			auto frameWin = Sprite::createWithSpriteFrameName("frame_win");
			frameWin->setPosition(CSettings::FRAME_WIN_POSITION);
			frameWin->setScale(CSettings::SCALE_FRAME_WIN);
			this->oHightLight->addChild(frameWin);
		}
		oAttachWinFrame->addChild(this->oHightLight);
	}
	void CReelColumn::restart(int* aSymbols, bool bReadyToStop, int* aLuckySymbols)
	{
		//Is this reel about to stop to show to screen?
		this->bReadyToStop = bReadyToStop;

		this->setPositionY(this->iCurStartY);
		this->setSymbol(aSymbols);

		if (this->bReadyToStop) {
			this->iCntFrames = 0;
			this->iMaxFrames = CSettings::MAX_FRAMES_REEL_EASE * 2;
			this->iCurState = REEL_STATE::REEL_STOP;
			this->setupLuckySymbol(aLuckySymbols);
		}
	}
	void CReelColumn::reset()
	{
		for (auto child : this->getChildren()) {
			child->setVisible(true);
		}
		this->oHightLight->setVisible(false);
	}
	void CReelColumn::highlightSymbol(int iIndex)
	{
		((Sprite*)this->oHightLight->getChildren().at(0))->setSpriteFrame("symbol_" + ToString(this->aSymbolValues[iIndex]) + "-0-5");
		auto symbol = this->getChildren().at(0);
		auto size = symbol->getContentSize() * symbol->getScale() / 2;
		this->oHightLight->setPosition(this->getSymbolPos(iIndex) + Vec2(size.width, -size.height));
		this->oHightLight->setVisible(true);

		this->hideSymbol(iIndex);
	}
	void CReelColumn::hideSymbol(int iRow)
	{
		this->getChildren().at(iRow)->setVisible(false);
	}
	void CReelColumn::moving()
	{
		if (this->bIsSpinning) {
			return;
		}

		this->iCurState = REEL_STATE::REEL_START;
		this->bIsSpinning = true;
		this->iCntFrames = 0;
		this->iMaxFrames = CSettings::MAX_FRAMES_REEL_EASE * 2;

		this->iCurStartY = CSettings::REEL_START_Y;
		this->iFinalY = CSettings::REEL_OFFSET_Y;

		/*this->iCurStartY = CSettings::REEL_OFFSET_Y;
		this->iFinalY = CSettings::REEL_ARRIVAL_Y;*/

		this->setPositionY(this->iCurStartY);

		this->schedule(schedule_selector(CReelColumn::updateReelSpinning), CSettings::TIMER_DELAY_UPDATE_REEL);
	}
	void CReelColumn::setSymbol(int* aSymbols, int startIndex)
	{
		auto children = this->getChildren();
		if (aSymbols) {
			for (int i = 0; i < CSettings::NUM_ROWS; ++i) {
				((Sprite*)children.at(startIndex + i))->setSpriteFrame("symbol_" + ToString(aSymbols[i]) + "-0-5");
				this->aSymbolValues[i] = aSymbols[i];
			}
		}
		else {
			for (int i = 0; i < CSettings::NUM_ROWS; ++i) {
				((Sprite*)children.at(startIndex + i))->setSpriteFrame("symbol_" + ToString(this->aSymbolValues[i]) + "-0-5");
			}
		}

		CC_SAFE_DELETE_ARRAY(aSymbols);
	}
	void CReelColumn::updateReelSpinning(float dt)
	{
		if (!this->bIsSpinning) {
			return;
		}
		switch (this->iCurState) {
		case REEL_STATE::REEL_START:
			this->updateStart(dt);
			break;
		case REEL_STATE::REEL_MOVING:
			this->updateMoving(dt);
			break;
		case REEL_STATE::REEL_STOP:
			this->updateStop(dt);
			break;
		}
	}
	void CReelColumn::updateStart(float dt)
	{
		/*this->iCntFrames += dt;
		if (this->getPositionY() < CSettings::REEL_OFFSET_Y)
		{*/
			this->iCntFrames = 0;
			this->iMaxFrames = CSettings::MAX_FRAMES_REEL_EASE;
			this->iCurState = REEL_STATE::REEL_MOVING;

			this->iCurStartY = CSettings::REEL_START_Y;
			this->iFinalY = CSettings::REEL_OFFSET_Y;

	/*		this->oReel->reelArrived(this->iIndex);
		}
		else {
			float fLerpY = tweenfunc::backEaseIn(this->iCntFrames / this->iMaxFrames);

			this->updateReelPosition(fLerpY);
		}*/
	}
	void CReelColumn::updateMoving(float dt)
	{
		this->iCntFrames += dt;
		if (this->iCntFrames > this->iMaxFrames)
		{
			this->iCntFrames = 0;

			this->setSymbol(nullptr, 3);
			this->oReel->reelArrived(this->iIndex);
		}
		else {

			float fLerpY = tweenfunc::tweenTo(this->iCntFrames / this->iMaxFrames, this->movingTweenType, nullptr);

			this->updateReelPosition(fLerpY);
		}
	}
	void CReelColumn::updateStop(float dt)
	{
		this->iCntFrames += dt;

		if (this->bReadyToStop && this->getPositionY() <= CSettings::REEL_OFFSET_Y) {
			this->bPlayEndSound = false;
			this->bReadyToStop = false;
			this->iCurStartY = CSettings::REEL_START_Y + CSettings::HEIGHT_REEL;
			this->iFinalY = CSettings::REEL_START_Y;
			this->setSymbol(nullptr, 3);
			this->setPositionY(CSettings::REEL_START_Y);
		}

		if (this->iCntFrames > this->iMaxFrames)
		{
			this->unschedule(schedule_selector(CReelColumn::updateReelSpinning));
			this->bIsSpinning = false;
			this->iCntFrames = 0;
			this->setPositionY(CSettings::REEL_OFFSET_Y);
			this->oReel->stopReel();
		}
		else
		{
			float fLerpY = tweenfunc::tweenTo(this->iCntFrames / this->iMaxFrames, this->stopTweenType, nullptr);

			this->updateReelPosition(fLerpY);

			if (!this->bPlayEndSound && this->iCntFrames / this->iMaxFrames >= (CSettings::MAX_FRAMES_REEL_EASE / this->iMaxFrames * 1.0f)) {
				this->bPlayEndSound = true;
				

				if (this->checkContainSymbol(CSettings::SCATTER_SYMBOL)) {
					Manager4Sound::getInstance()->playScatterStop();
				}else if (this->checkContainSymbol(CSettings::BONUS_3_SYMBOL)) {
					Manager4Sound::getInstance()->playBonusStop(3);
				}
				else if (this->checkContainSymbol(CSettings::BONUS_4_SYMBOL)) {
					Manager4Sound::getInstance()->playBonusStop(4);
				}
				else if (this->checkContainSymbol(CSettings::WILD_SYMBOL)) {
					Manager4Sound::getInstance()->playWildStop();
				}
				else {
					Manager4Sound::getInstance()->playReelStop();
				}
			}
		}
	}
	void CReelColumn::updateReelPosition(float fLerp)
	{
		this->setPositionY(this->iCurStartY + fLerp * (this->iFinalY - this->iCurStartY));
	}
	void CReelColumn::setupLuckySymbol(int *aLuckySymbol)
	{
		auto children = this->getChildren();
		if (aLuckySymbol) {
			for (int i = 0; i < CSettings::NUM_ROWS; ++i) {
				if (aLuckySymbol[i] > 0)
				{
					auto symbolSprite = children.at(i);

					auto luckySymbolSprite = Sprite::createWithSpriteFrameName(PNG_FRAME_MAGIC_ITEM_LUCKY_SYMBOL_FULL_ICON);
					luckySymbolSprite->setPosition(
						Vec2(symbolSprite->getContentSize())
						- Size(luckySymbolSprite->getContentSize() / 2 * 0.7f)
					);
					luckySymbolSprite->setScale(0.7f);

					symbolSprite->addChild(luckySymbolSprite);

					luckySymbolSprite->runAction(
						Sequence::createWithTwoActions(
							DelayTime::create(1.7f),
							CallFunc::create([luckySymbolSprite, symbolSprite]()
					{
						if (luckySymbolSprite->getParent())
						{
							auto worldPos = symbolSprite->convertToWorldSpace(luckySymbolSprite->getPosition());
							//luckySymbolSprite->retain();
							luckySymbolSprite->getParent()->removeChild(luckySymbolSprite, true);
							/*symbolSprite->getParent()->getParent()->getParent()->addChild(luckySymbolSprite);
							luckySymbolSprite->setPosition(symbolSprite->convertToWorldSpace(luckySymbolSprite->getPosition()));
							luckySymbolSprite->autorelease();*/

							auto oParticle = ParticleSystemQuad::create(PNG_STAR_EFFECT_SPIN_PARTICLE);
							oParticle->setPositionType(ParticleSystem::PositionType::FREE);
							oParticle->setPosition(worldPos);
							oParticle->setTexture(Helper4Sprite::getTextureFromSpriteFramename(PNG_FRAME_MAGIC_ITEM_LUCKY_SYMBOL_FULL_ICON));
							//luckySymbolSprite->addChild(oParticle);
							symbolSprite->getParent()->getParent()->getParent()->addChild(oParticle, 100);

							oParticle->runAction(
								Sequence::createWithTwoActions(
									JumpTo::create(
										1.2f * Vec2(1420, 60).getDistance(worldPos) / 1000,
										Vec2(1420, 60),
										30,
										1
									),
									CallFunc::create([oParticle]()
							{
								if (oParticle && oParticle->getParent())
								{
									oParticle->getParent()->removeChild(oParticle);
								}
							})
								));
						}
					}
							)
						)
					);
				}
			}
			CC_SAFE_DELETE_ARRAY(aLuckySymbol);
		}
	}
#pragma endregion

#pragma region CWinAnim
	CWinAnim::CWinAnim(CReel * oReel): Node(),
		oReel(oReel)
	{
		this->autorelease();
		this->oReel->addChild(this, ORDER_REEL_WINANIM);
	}
	CWinAnim::~CWinAnim()
	{
		this->callback = nullptr;
	}
	bool CWinAnim::init()
	{
		if (!Node::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		this->setScale(CSettings::SCALE_SYMBOL_MIN);
		this->oAnimSymbol = Helper4Sprite::createOptimizeSprite();
		this->oAnimSymbol->setScale(CSettings::SCALE_SYMBOL_ANIM);
		this->addChild(this->oAnimSymbol);

		if (CSettings::IS_SHOW_ANIMATION_FRAMEWIN) {
			if (SpriteFrameCache::getInstance()->getSpriteFrameByName("frame_win")) {
				auto frameWin = Sprite::createWithSpriteFrameName("frame_win");
				frameWin->setPosition(CSettings::FRAME_WIN_POSITION);
				frameWin->setScale(CSettings::SCALE_FRAME_WIN);
				this->addChild(frameWin);
			}
		}

		this->oAmountWin = Node::create();
		this->oAmountWin->setVisible(false);
		this->oAmountWin->setPosition(CSettings::AMOUNT_WIN_POSITION);
		this->addChild(this->oAmountWin);

		auto oAmountBG = Sprite::createWithSpriteFrameName("amount-win");
		this->oAmountWin->addChild(oAmountBG);

		this->oAmountWinText = Label::createWithTTF(res.fontConfigs["win_anim"], "x0");
		this->oAmountWin->addChild(this->oAmountWinText);
		this->oAmountWinText->setTextColor(Color4B(255, 255, 204, 255));
		this->setVisible(false);
		return true;
	}
	void CWinAnim::show(const ObjectCell& cell, const cocos2d::Vec2& oPos, int iSymbol, int iAmountWin, int loopTimes, const std::function<void()>& cb)
	{
		this->stopAllActions();
		this->oAnimSymbol->stopAllActions();
		this->callback = cb;
		//Set position
		this->setPositionX(oPos.x + CSettings::SYMBOL_WIDTH / 2);
		this->setPositionY(oPos.y - (CSettings::SYMBOL_HEIGHT / 2));

		//Show Win Text UI
		if (iAmountWin > 0) {
		    this->oAmountWinText->setString("x" + ToString(iAmountWin));
			this->oAmountWin->setVisible(true);
		} else {
			this->oAmountWin->setVisible(false);
		}

		auto res = GameConstant::getInstance()->getResources().symbolAnims;
		
		if (res.size() > 0) {
			auto animation = AnimationHelper::getInstance()->createAnimationByFrameName(
				res["symbol_" + ToString(iSymbol) + "_plist"],
				"symbol" + ToString(iSymbol) + "_%i",
				1,
				CSlotSettings::getInstance()->getSymbolAnimFrames()[iSymbol],
				CSettings::ANIM_SYMBOL_FPS,
				loopTimes);
			auto aAnchorPoint = CSlotSettings::getInstance()->getAnchorPoints();
			if (aAnchorPoint) {
				this->oAnimSymbol->setAnchorPoint(aAnchorPoint[iSymbol]);
			}
			this->oAnimSymbol->setSpriteFrame("symbol" + ToString(iSymbol) + "_1");

			this->oAnimSymbol->runAction(Sequence::createWithTwoActions(animation, CallFunc::create([this, iSymbol]() {
				this->oAnimSymbol->setSpriteFrame("symbol" + ToString(iSymbol) + "_1");
				this->runAction(Sequence::createWithTwoActions(EaseCubicActionOut::create(ScaleTo::create(CSettings::TIMER_ANIM_ZOOM_DOWN, CSettings::SCALE_SYMBOL_MIN)), CallFunc::create([this]() {
					this->reset();
					if (this->callback) {
						this->callback();
					}
				})));
			})));

			this->setScale(CSettings::SCALE_SYMBOL_MIN);

			if (CSettings::SCALE_SYMBOL_MIN != CSettings::SCALE_SYMBOL_MAX) {
				this->runAction(EaseBounceOut::create(ScaleTo::create(CSettings::TIMER_ANIM_ZOOM_UP, CSettings::SCALE_SYMBOL_MAX)));
			}
		}

		Manager4Sound::getInstance()->playSymbolAnimation(iSymbol);

		this->setVisible(true);
	}
	void CWinAnim::reset()
	{
		Manager4Sound::getInstance()->stopSymolAnimation();

		this->stopAllActions();

		this->oAnimSymbol->stopAllActions();

		this->setVisible(false);
	}
	void CWinAnim::setTextColor(const cocos2d::Color4B & fillColor, const cocos2d::Color4B & outlineColor)
	{
		this->oAmountWinText->setTextColor(fillColor);
		this->oAmountWinText->enableOutline(outlineColor);
	}
#pragma endregion

#pragma region CLines
	CLines::CLines(CReel * oReel): Sprite(),
		oReel(oReel)
	{
		this->autorelease();
		this->oReel->addChild(this, ORDER_REEL_LINES);
	}
	CLines::~CLines()
	{
		CC_SAFE_DELETE_ARRAY(this->aPosLines);
	}
	bool CLines::init()
	{
		if (!Sprite::init()) return false;
		this->initWithFile(GameConstant::getInstance()->getResources().lines["1"]);
		this->setAnchorPoint(Vec2(0, 1));
		//ATTACH ALL THE PAYLINES AND HIDE THEM
		this->aPosLines = new Vec2[30]{
			Vec2(369, 519), Vec2(369, 299), Vec2(369, 730), Vec2(369, 312), Vec2(369, 275), Vec2(369, 291),
			Vec2(369, 521), Vec2(369, 530), Vec2(369, 323), Vec2(369, 319), Vec2(369, 479), Vec2(369, 292),
			Vec2(369, 503), Vec2(369, 283), Vec2(369, 543), Vec2(369, 312), Vec2(369, 532), Vec2(369, 305),
			Vec2(369, 306), Vec2(369, 287), Vec2(369, 297), Vec2(369, 313), Vec2(369, 303), Vec2(369, 335),
			Vec2(369, 276), Vec2(369, 280), Vec2(369, 331), Vec2(369, 315), Vec2(369, 321), Vec2(369, 339)
		};
		this->hideLine();
		return true;
	}
	void CLines::showLine(int iLine)
	{
		this->setPosition(this->aPosLines[iLine - 1].x * CSettings::SCALE_VALUE_TO_1920, CSettings::CANVAS_HEIGHT - this->aPosLines[iLine - 1].y * CSettings::SCALE_VALUE_TO_1920);
		this->setTexture(GameConstant::getInstance()->getResources().lines[ToString(iLine)]);
		this->setVisible(true);
	}
#pragma endregion
}