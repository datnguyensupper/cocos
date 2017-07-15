#include "CGameBase.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CGameBase::CGameBase(CMainBase* oMain) : Node(),
		oMain(oMain),
		iCurState(GAME_STATE::GAME_IDLE),
		iCurType(GAME_TYPE::MAIN_GAME),
		iTimeElaps(0),
		iBonusActive(-1),
		iStepBonus(0),
		iTotFreeSpin(0),
		iMulFreeSpin(0),
		iAdditionFreeSpin(0),
		iTotWinFreespin(0),
		bAutoSpin(false),
		bReceivedSpinInfo(false),
		bDoubleUpMode(false),
		bShowTotalWinOnFreeSpin(false),
		bEndFreeSpin(false),
		aCurWheel(nullptr),
		oMagicItemAfterSpin(nullptr),
		oCharacter(nullptr),
		oReel(nullptr),
		oInterface(nullptr),
		oWinPanel(nullptr),
		oBg(nullptr),
		oBgFreeSpin(nullptr),
		oDoubleUp(nullptr)
	{
		this->autorelease();
	}

	void CGameBase::resetCurrentWheel()
	{
		if (this->aCurWheel != nullptr) {
			for (int i = 0; i < CSettings::NUM_ROWS; ++i) {
				CC_SAFE_DELETE_ARRAY(this->aCurWheel[i]);
			}
			CC_SAFE_DELETE_ARRAY(this->aCurWheel);
		}
	}

	void CGameBase::resetInfoMagicItemAfterSpin()
	{
		if (this->oMagicItemAfterSpin != nullptr) {
			CC_SAFE_DELETE(this->oMagicItemAfterSpin);
		}
	}

	CGameBase::~CGameBase()
	{
		this->resetCurrentWheel();
		CC_SAFE_DELETE(this->oCharacter);
	}

	bool CGameBase::init()
	{
		if (!Node::init()) return false;


		visibleSize = Director::getInstance()->getVisibleSize();
		origin = Director::getInstance()->getVisibleOrigin();
		scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();


		this->initBackground();

		this->initReels();

		this->initInterface();

		this->initWinPanel();

		this->initCharacter();

		return true;
	}

	void CGameBase::initBackground()
	{
		auto res = GameConstant::getInstance()->getResources().mainGame;
		this->oBg = Helper4Sprite::createOptimizeSprite(res["bg"]);
		GameUtils::centerNode(this->oBg);
		this->addChild(this->oBg, ORDER_BG);

		if (res.find("bg_freespin") != res.end()) {
			this->oBgFreeSpin = Helper4Sprite::createOptimizeSprite(res["bg_freespin"]);
			GameUtils::centerNode(this->oBgFreeSpin);
			this->oBgFreeSpin->setVisible(false);
			this->addChild(this->oBgFreeSpin, ORDER_BG);
		}
	}

	void CGameBase::initReels()
	{
		auto startingWheel = this->oMain->getStartingWheel();
		auto aStartingWheel = new int[startingWheel.size()];
		for (int i = 0; i < startingWheel.size(); ++i) {
			aStartingWheel[i] = stoi(startingWheel[i]);
		}
		
		this->oReel->init(aStartingWheel);
		CC_SAFE_DELETE_ARRAY(aStartingWheel);
	}

	void CGameBase::initCharacter()
	{
		if (oCharacter) {
			oCharacter->playIdle();
		}
	}

	void CGameBase::update(float dt)
	{
		switch (this->iCurState) {
		case GAME_STATE::GAME_IDLE:
		{
			if (this->bAutoSpin&&
				this->iCurType == GAME_TYPE::MAIN_GAME) {
				return;
			}

			if (this->iTotFreeSpin == 0) {
				this->iTimeElaps += dt;
				//MANAGES SPIN/AUTOSPIN IMAGE CHANGING
				if (this->iTimeElaps > CSettings::TIME_SPIN_BUT_CHANGE) {
					this->iTimeElaps = 0;
					this->oInterface->toggleAutoSpin();
				}
			}
			break;
		}
		case GAME_STATE::GAME_SPINING:
		{
			break;
		}
		case GAME_STATE::GAME_SHOW_ALL_WIN:
		{
			//THIS STATE SHOWS ALL THE WINNING COMBOS
			this->iTimeElaps += dt;
			if (this->iTimeElaps > CSettings::TIME_SHOW_ALL_WINS) {
				this->iTimeElaps = 0;
				this->oReel->showNextWinPayline();
				if (this->iTotFreeSpin ==  0 && this->iBonusActive == -1) {
					this->oInterface->toggleAutoSpin();
				}
			}
			break;
		}
		case GAME_STATE::GAME_SHOW_WIN:
		{
			//THIS STATE SHOWS THE CURRENT WINNING COMBO
			break;
		}
		case GAME_STATE::GAME_BONUS:
		{
			break;
		}
		}
	}

	bool CGameBase::checkLastState()
	{
		auto bonusHistory = this->oMain->getBonusHistory();
		//CHECK IF THERE IS AN OPEN BONUS
		if (bonusHistory) {
			this->iCurType = GAME_TYPE::FREE_SPIN;
			this->oInterface->setButtonSpinEnabled(false);
			this->oInterface->setButtonSpinVisible(false);
			this->iStepBonus = bonusHistory->bonus_step;
			this->iBonusActive = bonusHistory->bonus_id;
			return true;
		}
		Manager4Sound::getInstance()->reset();
		return false;
	}

	void CGameBase::generateLosingBet()
	{
		vector<std::string>  startingWheel = 
		{ 
			"2",
			"7",
			"5",
			"9",
			"3",
			"5",
			"1",
			"0",
			"7",
			"4",
			"10",
			"5",
			"0",
			"7",
			"5"
		};
		this->oMain->setStartingWheel(startingWheel);
	}
	void CGameBase::generateLosingWheel()
	{
		this->bReceivedSpinInfo = true;

		int* aLoosingWheel = new int[15]{ 1, 3, 7, 10, 5, 5, 2, 7, 2, 1, 9, 4, 1, 2, 2 };
		this->resetCurrentWheel();
		this->aCurWheel = new int*[CSettings::NUM_ROWS];

		for (int i = 0, iCont = 0; i < CSettings::NUM_ROWS; ++i) {
			this->aCurWheel[i] = new int[CSettings::NUM_REELS];
			for (int j = 0; j < CSettings::NUM_REELS; ++j, ++iCont) {
				this->aCurWheel[i][j] = aLoosingWheel[iCont];
			}
		}
		CC_SAFE_DELETE_ARRAY(aLoosingWheel);
		this->resetReel();
		this->spin();
	}
	void CGameBase::switchUI()
	{
		bool isFreeSpinState = this->iCurType == GAME_TYPE::FREE_SPIN;
		if (this->oBgFreeSpin) {
			this->oBgFreeSpin->setVisible(isFreeSpinState);
			this->oBg->setVisible(!isFreeSpinState);
		}
		if (this->oCharacter) {
			if (isFreeSpinState) {
				this->oCharacter->playFreeSpin();
			}
			else {
				this->oCharacter->playIdle();
			}
		}
	}
	void CGameBase::changeToFreeSpinState(int totalFS, int totalMulty)
	{
		this->iCurType = GAME_TYPE::FREE_SPIN;

		this->switchUI();

		this->iTotFreeSpin = totalFS;//4 - _iCurWildExp;
		this->iMulFreeSpin = totalMulty;

		this->oInterface->setButtonSpinVisible(false);
		this->oInterface->setFreeSpinIndicatorVisible(true);

		if (totalFS > 0) {
			this->oInterface->getFreeSpinIndicator()->refreshRemaining(this->iTotFreeSpin, this->iMulFreeSpin);
		}

		Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);
		Manager4Sound::getInstance()->playBackgroundMusic();
	}
	void CGameBase::spin()
	{
		Manager4Sound::getInstance()->playReelSpin();
		this->iCurState = GAME_STATE::GAME_SPINING;

		this->oInterface->setButtonDoubleUpVisible(false);
		this->oInterface->setSpinState(SPIN_STATE::SPIN_TYPE_STOP);
		this->oInterface->setFooterEnabled(false);
		this->oInterface->refreshBet();

		this->oReel->startSpin();
	}
	void CGameBase::showWin()
	{
		this->oInterface->setSpinState(SPIN_STATE::SPIN_TYPE_SKIP);
		this->iCurState = GAME_STATE::GAME_SHOW_WIN;
		this->oReel->showWin(&this->aWinningLine);
	}
	int* CGameBase::generateRandSymbols()
	{
		auto aRandSymbols = new int[3];
		auto s_aRandSymbols = CSlotSettings::getInstance()->getSymbolsOccurence();
		for (int i = 0; i < CSettings::NUM_ROWS; ++i) {
			int iRandIndex = RandomHelper::random_int(0, (int)s_aRandSymbols.size() - 1);
			aRandSymbols[i] = s_aRandSymbols[iRandIndex];
		}
		return aRandSymbols;
	}
	bool CGameBase::onSpin(tinyxml2::XMLDocument* doc)
	{
		if (this->iCurState == GAME_STATE::GAME_SPINING) return false;

		if (!this->oMain->getScene()->checkCanSpin()) return false;

		this->oMain->getScene()->onBeginSpin();

		this->bReceivedSpinInfo = false;

		this->oInterface->onSpinStarted();

		this->resetReel();

		this->spin();

		Manager4Sound::getInstance()->playSpin();

		if (doc) {
			this->oMain->onSpinReceived(doc);
		}
		else {
			Manager4Network::getInstance()->callGetSpin();
		}

		return true;
	}

	void CGameBase::onSkip()
	{
		if (this->aWinningLine.size() > 0 && 
			this->iBonusActive > 0 && 
			this->iCurState == GAME_STATE::GAME_SHOW_WIN &&
			this->iCurType == GAME_TYPE::MAIN_GAME) {
			auto win = this->aWinningLine.at(this->aWinningLine.size() - 1);
			this->oReel->showSymbolWin(win, [this]() {
				this->launchBonus();
			});
			return;
		}

		/*if (this->iCurType == GAME_TYPE::FREE_SPIN) {
			this->oInterface->setButtonSpinVisible(false);
		}*/

		this->oInterface->setButtonSpinEnabled(false);
		this->resetReel();
		this->afterStopSpin();
	}

	void CGameBase::resetReel()
	{
		this->aWinningLine.clear();
		this->oReel->resetReel();
	}

	int CGameBase::onStopOneReelColumn(int totalReelStop)
	{
		if (totalReelStop == 4 && this->iCurType == GAME_TYPE::FREE_SPIN && !this->bShowTotalWinOnFreeSpin) {
			this->oInterface->refreshFreeSpin(this->iTotFreeSpin, this->iMulFreeSpin);
		}
		auto col = this->oReel->getReelColumn(totalReelStop - 1);

		if (col->checkContainSymbol(CSettings::WILD_SYMBOL)) {
			//Manager4Sound::getInstance()->playWildStop();
			return CSettings::WILD_SYMBOL;
		}else if (col->checkContainSymbol(CSettings::SCATTER_SYMBOL)) {
			//Manager4Sound::getInstance()->playScatterStop();
			return CSettings::SCATTER_SYMBOL;
		}
		else {
			//Manager4Sound::getInstance()->playReelStop();
			return 0;
		}
	}
	void CGameBase::onStopReel()
	{
		Manager4Sound::getInstance()->stopReelSpin();

		//DISABLE GUI IF BONUS MUST BE SHOWN
		if (this->iBonusActive > 0) {
			this->oInterface->setButtonSpinEnabled(false);
		}

		this->oInterface->refreshBet(this->oMain->getWin());

		//We call update User info, only after that we could call after stop spin

		this->bWaitingRequestToFinishSpin = false;

		this->oMain->getScene()->onFinishSpin([this]() {
			if (this->bWaitingRequestToFinishSpin) {
				this->afterStopSpin();
			}
		});

		//IF THERE IS ANY WINNING COMBO
		if (this->aWinningLine.size() > 0) {
			//Play some character's wining animations (if exists)
			if (this->oCharacter &&
				this->iTotFreeSpin <= 0) {
				this->oCharacter->playWin();
			}
			if (this->bDoubleUpMode) {
				this->oInterface->setButtonDoubleUpVisible(true);
			}
			this->showWin();
		}
		else {
			this->bWaitingRequestToFinishSpin = true;
		}
	}

	void CGameBase::onSpinReceived(
		int ** aWheels,
		ObjectMagicItemReceiveAfterSpin *oMagicItemAfterSpin,
		const vector<ObjectWinPosition>& aWinPosition,
		const vector<ObjectTableWin>& aTableWin,
		int iBonus, 
		int countFreeSpin)
	{
		this->bReceivedSpinInfo = true;

		this->resetInfoMagicItemAfterSpin();
		this->oMagicItemAfterSpin = oMagicItemAfterSpin;

		this->generateFinalSymbols(aWheels, aWinPosition, aTableWin);


		if (iBonus != 1) {
			this->iBonusActive = iBonus;
			this->bDoubleUpMode = false;
			this->iTotFreeSpin = countFreeSpin;
		}
		else {
			this->bDoubleUpMode = true;
		}
	}
	void CGameBase::onBonusFreeSpinStepReceived(
		int iRemainingFreeSpin,
		int iMultyFS, 
		const vector<ObjectWinPosition>& aWinPosition,
		int ** aWheels,
		const vector<ObjectTableWin>& aTableWin,
		double iTotWin)
	{
		this->bReceivedSpinInfo = true;
		this->iStepBonus++;

		if (this->iTotFreeSpin > 0 && this->iTotFreeSpin < iRemainingFreeSpin) {
			this->bShowTotalWinOnFreeSpin = true;
			this->iAdditionFreeSpin = iRemainingFreeSpin - this->iTotFreeSpin;
		}

		this->iTotFreeSpin = iRemainingFreeSpin;
		this->iMulFreeSpin = iMultyFS;
		this->iTotWinFreespin = iTotWin;

		if (this->iTotFreeSpin == 0) {
			this->bEndFreeSpin = true;
		}

		this->generateFinalSymbols(aWheels, aWinPosition, aTableWin);

		if (!this->bShowTotalWinOnFreeSpin) {
			this->oInterface->refreshFreeSpin(this->iTotFreeSpin + 1, this->iMulFreeSpin);
		}
		this->spin();
		this->oInterface->setButtonSpinVisible(true);
	}
	void CGameBase::onDoubleUpStep0Received(double iCurWin)
	{
		this->oDoubleUp->show(iCurWin);
		this->iStepBonus++;
	}
	void CGameBase::onDoubleUpStep1Received(bool iFinish, int iResult, double iTotWin)
	{
		this->oDoubleUp->showResult(iFinish, iResult, iTotWin);
		this->iStepBonus++;
	}
	void CGameBase::generateFinalSymbols(
		int ** aWheel,
		const vector<ObjectWinPosition>& aWinPosition,
		const vector<ObjectTableWin>& aTableWin)
	{
		this->resetCurrentWheel();
		this->aCurWheel = aWheel;
		this->aWinningLine.clear();
		//STORE ALL WINNING COMBO INFOS
		for (int k = 0; k < aWinPosition.size(); k++) {
			vector<ObjectCell> aCellList;
			vector<string> aWinPos = GameUtils::splitString(aWinPosition[k].pos, ',');
			int col = -1;

			bool isHaveScatter = false;
			for (int s = 0; s < aWinPos.size(); s++) {
				if (aWinPos[s] != "0") {
					ObjectCell aReelPos = ObjectCell(stoi(aWinPos[s]) - 1, s);
					aCellList.push_back(aReelPos);
					if (this->aCurWheel[aReelPos.row][aReelPos.col] == CSettings::WILD_SYMBOL) {
						col = aCellList.size() - 1;
					}

					if (this->aCurWheel[aReelPos.row][aReelPos.col] == CSettings::SCATTER_SYMBOL) {
						isHaveScatter = true;
					}
				}
			}

			if (!isHaveScatter &&
				this->bShowTotalWinOnFreeSpin) {
				continue;
			}

			int iValue = 0;
			int row = 0;

			//DETECT WHICH REEL WE HAVE TO SHOW THE BIG ANIMATION

			if (col < 0) {
				col = 2;
			}
			if (col >= aCellList.size()) {
				col = aCellList.size() - 1;
			}

			col = this->fixColToShowAnimation(aCellList, col);

			if (col < 0) {
				col = 0;
			}

			row = (col < aCellList.size()) ? aCellList[col].row : -1;
			iValue = (col > -1 && row > -1) ? this->aCurWheel[row][aCellList[col].col] : -1;


			this->aWinningLine.push_back(
				ObjectWinningLine(
					aWinPosition[k].line,
					aWinPosition[k].mul,
					aWinPosition[k].isBonus,
					aCellList,
					iValue,
					col
					));
		}
	}

	int CGameBase::fixColToShowAnimation(
		const vector<ObjectCell>& aCellList,
		int col)
	{
		return col;
	}

	void CGameBase::afterStopSpin(bool isWin)
	{
		if (!this->oMain->isUpdateUserInfo()) {
			this->bWaitingRequestToFinishSpin = true;
			return;
		}

		this->iTimeElaps = CSettings::TIME_SPIN_BUT_CHANGE;
		if (this->iCurType == GAME_TYPE::FREE_SPIN) {
			if (this->bEndFreeSpin) {
				this->oInterface->setButtonSpinEnabled(false);
				this->iStepBonus = 0;
				this->exitFromFreeSpin();
				this->bEndFreeSpin = false;
			}
			else {
				this->oInterface->setButtonSpinEnabled(false);
				this->iCurState = GAME_STATE::GAME_IDLE;
				if (this->bShowTotalWinOnFreeSpin) {
					this->oWinPanel->showFreeSpinAdditionWinPanel(this->iAdditionFreeSpin, [this]() {
						Manager4Sound::getInstance()->playBackgroundMusic();
						this->oInterface->refreshFreeSpin(this->iTotFreeSpin + 1, this->iMulFreeSpin);
						Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);
					});
				}
				else {
					Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);
				}
			}
		}
		else if (this->iCurType == GAME_TYPE::MAIN_GAME) {
			this->iCurState = GAME_STATE::GAME_IDLE;
			if (this->iBonusActive > 0) {
				//IF THERE IS ANY ACTIVE BONUS, SHOW IT
				this->launchBonus();
			}
			else if (this->bAutoSpin) {
				/*if (delayOnAuto != 0) {
					this->scheduleOnce(schedule_selector(CGameBase::onAutoSpin), delayOnAuto);
				}
				else {*/
					this->onAutoSpin(0);
				//}
			}
			else {
				this->oInterface->setFooterEnabled(true);
				if (isWin) {
					this->iCurState = GAME_STATE::GAME_SHOW_ALL_WIN;
				}
				else {
					this->iCurState = GAME_STATE::GAME_IDLE;
				}
			}
		}
	}

	void CGameBase::launchBonus()
	{
		this->iCurState = GAME_STATE::GAME_BONUS;
		this->oInterface->setFooterEnabled(false);
		this->iStepBonus = 0;
		switch (this->iBonusActive) {
		case BONUS_TYPE::BONUS_TYPE_3:
		case BONUS_TYPE::BONUS_TYPE_4:
		{
			this->oInterface->showStartBonusBut();
			break;
		}
		case BONUS_TYPE::BONUS_FREESPIN:
		{
			this->oInterface->showStartFreeSpinBut();
			break;
		}
		}
	}

	void CGameBase::startDoubleUp()
	{
		this->oMain->getScene()->onBeginBonus();

		this->iCurType = GAME_TYPE::DOUBLE_UP;
		this->bDoubleUpMode = false;

		this->oInterface->setButtonDoubleUpVisible(false);
		this->oInterface->setButtonSpinVisible(false);

		this->resetReel();

		this->iStepBonus = 0;
		Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);

		this->oDoubleUp->show();
	}

	void CGameBase::startFreeSpin()
	{
		this->iStepBonus = 1;
		this->changeToFreeSpinState(this->iTotFreeSpin, this->iMulFreeSpin);
	}

	void CGameBase::startBonus()
	{
		this->oMain->getScene()->onBeginBonus();

		this->iCurType = GAME_TYPE::BONUS;

		this->oInterface->setButtonSpinVisible(false);
		this->oInterface->refreshBet();

		this->iStepBonus = 0;

		Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);
	}

	void CGameBase::exitFromFreeSpin()
	{
		this->iCurType = GAME_TYPE::MAIN_GAME;
		this->switchUI();

		this->oInterface->setFreeSpinIndicatorVisible(false);
		this->oInterface->setButtonSpinVisible(false);

		this->oWinPanel->showWinPanel("YOU WON", this->iTotWinFreespin, [this](){
			this->exitFromBonus(this->iTotWinFreespin);
		});
	}

	void CGameBase::exitFromBonus(const double& iWin)
	{
		auto cb = [this]() {
			this->iCurType = GAME_TYPE::MAIN_GAME;
			this->iBonusActive = -1;

			Manager4Sound::getInstance()->playBackgroundMusic();

			this->iCurState = GAME_STATE::GAME_IDLE;

			this->getMain()->removeBonusHistory();

			this->oInterface->setButtonSpinVisible(true);
			this->oInterface->setButtonSpinEnabled(true);

			this->oMain->setCurrentBonus(-1);
			this->oInterface->setSpinState(SPIN_STATE::SPIN_TYPE_SPIN); // to reset the state back to ready to Spin

			if (this->bAutoSpin) {
				this->onAutoSpin(0);
			}
			else {
				this->oInterface->setFooterEnabled(true);
			}
		};
		if (iWin > this->getMain()->getTotalBet()) {
			this->oInterface->refreshBet(iWin, true, cb);
			this->oMain->getScene()->onFinishBonus(nullptr);
		}
		else {
			this->oInterface->refreshBet(iWin, true);
			this->oMain->getScene()->onFinishBonus(cb);
		}
	}
	void CGameBase::exitFromBonusFreeSpin(int totalFreeSpin, int totalMul)
	{
		this->iCurType = GAME_TYPE::MAIN_GAME;

		this->iCurState = GAME_STATE::GAME_BONUS;

		this->iBonusActive = BONUS_TYPE::BONUS_FREESPIN;

		Manager4Sound::getInstance()->playBackgroundMusic();

		this->getMain()->removeBonusHistory();

		this->oMain->setCurrentBonus(BONUS_TYPE::BONUS_FREESPIN);

		this->iTotFreeSpin = totalFreeSpin;
		this->iMulFreeSpin = totalMul;

		this->oInterface->showStartFreeSpinBut();
	}
}