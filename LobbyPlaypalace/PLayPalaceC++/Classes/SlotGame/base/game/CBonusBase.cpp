#include "CBonusBase.h"
#include "CGameBase.h"
#include "Manager/PopupManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"


USING_NS_CC;
namespace GameSlot {
	CBonusBase::CBonusBase(CGameBase* oGame): Node(),
		oGame(oGame),
		bButtonClicked(false),
		bInited(false),
		bLoading(false),
		iTotWin(0),
		bFinish(false),
		iGameType(GAME_TYPE::BONUS),
		iBonusType(BONUS_TYPE::BONUS_TYPE_3)
	{
		this->autorelease();
		oGame->getMain()->addChild(this, ORDER_BONUS);
		this->setVisible(false);
	}
	CBonusBase::~CBonusBase()
	{
	}
	void CBonusBase::show(double currentWin1, double currentWin2)
	{
		Manager4Sound::getInstance()->turnOffAllSound();

		this->iTotWin = currentWin1;

		this->checkAndLoadAllResources();

		this->oGame->setType(iGameType);

		if (!this->bGoToBonus) {
			this->bGoToBonus = true;
			this->oGame->setVisible(false);
			this->oGame->getMain()->getScene()->onBeginBonus();
		}
	}
	void CBonusBase::checkAndLoadAllResources()
	{
		if (this->iGameType == GAME_TYPE::BONUS) {
			this->oGame->getMain()->getLoadingUI()->setBackgroundLoading(GameConstant::getInstance()->getResources().mainGame["bonus_loading"]);
		}
		else {
			this->oGame->getMain()->getLoadingUI()->setBackgroundLoading(GameConstant::getInstance()->getResources().mainGame["double_up_loading"]);
		}

		if (this->bInited) {
			this->onAllImagesLoaded();
			return;
		}

		if (this->bLoading == true)
			return;
		this->bLoading = true;

		this->oGame->getMain()->getLoadingUI()->preload(aResources, CC_CALLBACK_0(CBonusBase::onAllImagesLoaded, this));
	}
	void CBonusBase::onAllImagesLoaded()
	{
		this->aResources.clear();

		this->oGame->getMain()->getLoadingUI()->showLoading(100);
		if (!this->bInited) {
			this->init();
			this->bInited = true;
		}
        log("this->oGame->getMain()->isReceivedBonus() %i",this->oGame->getMain()->isReceivedBonus());
        log("this->oGame->getMain()->getBonusHistory() %i",this->oGame->getMain()->getBonusHistory() != nullptr);
		if (this->oGame->getMain()->isReceivedBonus() ||
			this->oGame->getMain()->getBonusHistory()) {
            
            log("this->oGame->getMain()->isReceivedBonus() ||this->oGame->getMain()->getBonusHistory()");
            Director::getInstance()->getScheduler()->schedule([this](float dt) {
                log("Director::getInstance()->getScheduler()->schedule");
				this->bLoading = false;
                this->onBonusEntered();
                log("log('Director::getInstance()->getScheduler()->schedule');");
                this->restore();
                log("this->restore();");
			}, this, 0, 0, 0.5f, false, "CBonusBase_entered");
        }else if(!this->oGame->getMain()->isReceivedBonus()){
            log("this->oGame->getMain()->isReceivedBonus() ||this->oGame->getMain()->getBonusHistory() FAIL");
//            Director::getInstance()->getScheduler()->schedule([this](float dt) {
//            PopupManager::getInstance()->getHeaderLobbyLayout()->scheduleOnce([](float dt){
//                PopupManager::getInstance()->getHeaderLobbyLayout()->gotoLobbyScene();
//            }, 1.0f, "CBonusBase_entered");
            
//            }, this, 0, 0, 0.5f, false, "CBonusBase_entered");
        }
	}
	bool CBonusBase::init(){

		visibleSize = Director::getInstance()->getVisibleSize();
		origin = Director::getInstance()->getVisibleOrigin();
		scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();

		return true;
	}
	void CBonusBase::onBonusEntered()
	{
		this->bButtonClicked = false;
		Manager4Sound::getInstance()->playBackgroundMusic();
		this->oGame->setVisible(false);
		this->setVisible(true);
		this->oGame->getMain()->getLoadingUI()->hideLoading();
	}
	void CBonusBase::disableAllBtn()
	{
		for (auto btn : this->aBtn) {
			btn->setTouchEnabled(false);
		}
	}
	void CBonusBase::enableAllBtn()
	{
		for (auto btn : this->aBtn) {
			btn->setTouchEnabled(true);
		}
	}
	bool CBonusBase::btnGamblingClicked(int iIndex)
	{
		if (this->bButtonClicked) {
			return false;
		}
		this->bButtonClicked = true;
		this->disableAllBtn();
		this->oGame->chooseItem(iIndex);

		switch (this->iBonusType)
		{
		case BONUS_TYPE::BONUS_DOUBLE_UP:
			Manager4Sound::getInstance()->playBtnDoubleUpClicked();
			break;
		case BONUS_TYPE::BONUS_TYPE_3:
			Manager4Sound::getInstance()->playBtnBonusType3Clicked();
			break;
		case BONUS_TYPE::BONUS_TYPE_4:
			Manager4Sound::getInstance()->playBtnBonusType4Clicked();
			break;
		default:
			break;
		}

		return true;
	}
	void CBonusBase::restore()
	{
		auto aHistory = this->oGame->getMain()->getBonusHistory();

		if (!aHistory || aHistory->bonus_step <= 0) {
			return;
		}

		for (auto i = 0; i < aHistory->history.size(); i++) {
			this->showResult(aHistory->finish,
				aHistory->history,
				i,
				true);
		}

		this->oGame->getMain()->removeBonusHistory();
	}
	void CBonusBase::showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
	{
		this->bButtonClicked = false;
		this->bFinish = bFinish;
		this->enableAllBtn();
	}
	void CBonusBase::showResult(bool bFinish, int iResult, double iTotWin, bool bFromRestore)
	{
		this->bButtonClicked = false;
		this->bFinish = bFinish;
		this->enableAllBtn();
		this->iTotWin = iTotWin;
	}
	void CBonusBase::showResult(bool bFinish, int iTotFreeSpin, int iTotMulty, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
	{
		this->bButtonClicked = false;
		this->bFinish = bFinish;
		this->enableAllBtn();
	}
	void CBonusBase::showFinalWin(float delay)
	{
		if (this->iTotWin == 0) {
			this->exitFromBonus();
		}
		else {
			this->oGame->getWinPanel()->showWinPanel("TOTAL WIN", this->iTotWin, [this](){
				this->exitFromBonus();
			});
		}
	}
	void CBonusBase::exitFromBonus()
	{
		this->oGame->setVisible(true);

		this->bGoToBonus = false;

		this->setVisible(false);
		this->oGame->exitFromBonus(this->iTotWin);

		this->resetBonus();
	}
	void CBonusBase::resetBonus()
	{
		this->iTotWin = 0;
		this->enableAllBtn();
	}
}
