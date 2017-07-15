#include "CInterfaceBase.h"
#include "SlotGame/base/game/CGameBase.h"
#include "Constant/Defination.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Manager/ScaleManager.h"

USING_NS_CC;
namespace GameSlot {
	CInterfaceBase::CInterfaceBase(CGameBase* oGame, bool bGameHasDoubleUp) : Node(),
		oGame(oGame),
		currentState(SPIN_STATE::SPIN_TYPE_SPIN),
		oButSpin(nullptr),
		oButDoubleUp(nullptr),
		oFreeSpinIndicator(nullptr),
		bGameHasDoubleUp(bGameHasDoubleUp)
	{
		this->autorelease();

		visibleSize = Director::getInstance()->getVisibleSize();
		origin = Director::getInstance()->getVisibleOrigin();
		scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();

		this->oGame->addChild(this, ORDER_INTERFACE);

	}
	CInterfaceBase::~CInterfaceBase()
	{
	}
	bool CInterfaceBase::init()
	{
		auto res = GameConstant::getInstance()->getResources().mainGame;

		GameUtils::centerNode(this);

		this->oButSpin = CSpriteButton::createButtonWithSpriteFrameName("spin_type_spin",
			[this]() {
			if (this->oGame->getCurrentState() == GAME_STATE::GAME_BONUS) {
				return;
			}
		},
			[this]() {
			if (this->oGame->getCurrentState() == GAME_STATE::GAME_BONUS) {
				switch (this->oGame->getBonusActive()) {
				case BONUS_TYPE::BONUS_FREESPIN:
					this->oGame->startFreeSpin();
					break;
				default:
					this->oGame->startBonus();
					break;
				}
			}
			else {
				this->onSpin(false);
			}
		}
			);
		this->oButSpin->setLongTouch(CSettings::TIME_HOLD_AUTOSPIN, [this]() {
			if (this->currentState == SPIN_STATE::SPIN_TYPE_SPIN ||
				this->currentState == SPIN_STATE::SPIN_TYPE_AUTO_SPIN) {
				this->currentState = SPIN_STATE::SPIN_TYPE_AUTO_SPIN;
				this->onSpin(true);
			}
		});


		this->oButSpin->setScaleEvent(0.9f, 1.0f);
		this->oButSpin->setPositionX(CSettings::CANVAS_WIDTH / 2 - this->oButSpin->getContentSize().width * 0.55f - origin.x);
		this->addChild(this->oButSpin, 100);

		if (this->bGameHasDoubleUp) {
			this->oButDoubleUp = CSpriteButton::createButtonWithSpriteFrameName(
				"btn-double-up",
				nullptr,
				[this]() {
				this->oGame->startDoubleUp();
			}
			);
			this->oButDoubleUp->setPosition(this->oButSpin->getPosition() + Vec2(0, -190));
			this->oButDoubleUp->setScaleEvent(0.9f, 1.0f);
			this->addChild(oButDoubleUp, 100);
			this->setButtonDoubleUpVisible(false);
		}

		this->initFreeSpinIndicator();

		this->oFooter = new CFooter(this->oGame);
		this->oFooter->init();
		this->oFooter->setPosition(0, -CSettings::CANVAS_HEIGHT * 0.425f - (1-scaleDownRatio)*this->oFooter->getContentSize().height/2);
		this->oFooter->setScale(scaleDownRatio);

		//this->oFooter->setScale(CSettings::CANVAS_WIDTH / Director::getInstance()->getVisibleSize().width);
		this->addChild(this->oFooter, 1000);

		this->oGameEffect = new CGameEffectUI(this->oGame->getMain());

		this->refreshBet();

		return true;
	}

	void CInterfaceBase::onSpinStarted()
	{
		this->oGameEffect->getSpinEffect()->playFlyingStarAnimation(this->oButSpin->getPosition(), Vec2(-visibleSize.width/2 + (/*headerPosition*/70+/*starPosition*/100)*scaleDownRatio, visibleSize.height/2 - (/*starPosition*/80)*scaleDownRatio));
	}

	void CInterfaceBase::initFreeSpinIndicator()
	{

	}

	void CInterfaceBase::toggleAutoSpin()
	{
		this->setButtonSpinEnabled(true);
		if (this->currentState == SPIN_STATE::SPIN_TYPE_SPIN) {
			if (this->oGame->getCurrentType() == GAME_TYPE::MAIN_GAME) {
				this->setSpinState(SPIN_STATE::SPIN_TYPE_AUTO_SPIN);
			}
		}
		else {
			this->setSpinState(SPIN_STATE::SPIN_TYPE_SPIN);
		}
	}
	void CInterfaceBase::setSpinState(SPIN_STATE state)
	{
		if (state == this->currentState) {
			return;
		}
		this->setButtonSpinEnabled(true);
		this->currentState = state;
		std::string frameName = "";
		switch (this->currentState)
		{
		case SPIN_STATE::SPIN_TYPE_SPIN:
			frameName = "spin_type_spin";
			break;
		case SPIN_STATE::SPIN_TYPE_STOP:
			if (this->oGame->isAutoSpin() &&
				this->oGame->getCurrentType() == GAME_TYPE::MAIN_GAME)
			{
				//if this is stop mode when auto spin
				frameName = "spin_type_stop";
			}
			else
			{
				// if this is stop mode when normal spin -> change frame to frame "spin" and disable button
				frameName = "spin_type_spin";
				this->setButtonSpinEnabled(false);
			}
			break;
		case SPIN_STATE::SPIN_TYPE_AUTO_SPIN:
			frameName = "spin_type_autospin";
			break;
		case SPIN_STATE::SPIN_TYPE_SKIP:
			frameName = "spin_type_skip";
			break;
		case SPIN_STATE::SPIN_TYPE_BONUS:
			frameName = "spin_type_bonus";
			break;
		case SPIN_STATE::SPIN_TYPE_FREE_SPIN:
			frameName = "spin_type_freespin";
			break;
		default:
			break;
		}
		this->oButSpin->setSpriteFrame(frameName);
	}

	void CInterfaceBase::showStartBonusBut()
	{
		this->setSpinState(SPIN_STATE::SPIN_TYPE_BONUS);
		this->setButtonSpinVisible(true);
	}

	void CInterfaceBase::showStartFreeSpinBut()
	{
		this->setSpinState(SPIN_STATE::SPIN_TYPE_FREE_SPIN);
		this->setButtonSpinVisible(true);
	}

	void CInterfaceBase::setFreeSpinIndicatorVisible(bool isVisible)
	{
		if (!this->oFreeSpinIndicator) {
			return;
		}
		if (isVisible) {
			this->oFreeSpinIndicator->show();
		}
		else {
			this->oFreeSpinIndicator->hide();
		}
	}

	void CInterfaceBase::refreshFreeSpin(int iTotFreespin, int iTotMulty)
	{
		if (!this->oFreeSpinIndicator) {
			return;
		}
		this->oFreeSpinIndicator->refreshRemaining(iTotFreespin, iTotMulty);
	}

	void CInterfaceBase::refreshBet(const double & iWin, bool isFromBonus, const std::function<void()> & cb)
	{
		auto totalBet = this->oGame->getMain()->getTotalBet();
		this->oFooter->refreshWin(iWin, iWin > totalBet, cb);

		if (isFromBonus || iWin == 0 || this->oGame->getCurrentType() == GAME_TYPE::FREE_SPIN) return;

		this->oGameEffect->getWinEffect()->checkAndShowWinEffect(
			iWin,
			totalBet,
			this->oGame->getObjectMagicItemAfterSpin()
		);
	}

	void CInterfaceBase::setFooterEnabled(bool isEnabled)
	{
		this->oFooter->setAdjustEnabled(isEnabled);
	}

	void CInterfaceBase::onSpin(bool bAutoSpin)
	{
		switch (this->currentState) {
		case SPIN_STATE::SPIN_TYPE_SPIN:
		case SPIN_STATE::SPIN_TYPE_AUTO_SPIN:
			if (this->oGame->getCurrentType() == GAME_TYPE::FREE_SPIN ||
				this->oGame->isAutoSpin()) {
				return;
			}
			if (bAutoSpin) {
				this->oGame->onAutoSpin(0);
			}
			else {
				this->oGame->onSpin();
			}
			break;
		case SPIN_STATE::SPIN_TYPE_SKIP:
			//if spin button is on skip mode
			this->oGame->onSkip();
			break;
		case SPIN_STATE::SPIN_TYPE_STOP:
			if (this->oGame->isAutoSpin() &&
				this->oGame->getCurrentType() != GAME_TYPE::FREE_SPIN) {

				this->oButSpin->setSpriteFrame("spin_type_spin");
				this->oGame->setAutoSpin(false);

				this->setButtonSpinEnabled(false);
			}
			break;
		}
	}

	CFreeSpinIndicatorBase::CFreeSpinIndicatorBase() : Node(),
		oTextNumberFS(nullptr),
		oTextNumberMulty(nullptr)
	{
		visibleSize = Director::getInstance()->getVisibleSize();
		origin = Director::getInstance()->getVisibleOrigin();
		scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();

		this->autorelease();
		//CREATE TEXT UI
		this->oContainerRemaining = Node::create();
		this->addChild(oContainerRemaining, 10);
	}
	CFreeSpinIndicatorBase::~CFreeSpinIndicatorBase()
	{
	}
	void CFreeSpinIndicatorBase::hideRemaining()
	{
		this->oContainerRemaining->setVisible(false);
	}
	void CFreeSpinIndicatorBase::show()
	{
		this->setVisible(true);
	}
	void CFreeSpinIndicatorBase::hide()
	{
		this->hideRemaining();
		this->setVisible(false);
	}
	void CFreeSpinIndicatorBase::refreshRemaining(int iTotFreespin, int iTotMulty)
	{
		this->oContainerRemaining->setVisible(true);
		if (oTextNumberFS) {
			oTextNumberFS->setString(ToString(iTotFreespin));
		}
		if (oTextNumberMulty) {
			oTextNumberMulty->setString(ToString(iTotMulty));
		}
	}
}
