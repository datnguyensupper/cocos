#include "CBonusRE.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "Custom/Common/CSpinWheel.h"
#include "../interfaceUI/CWinPanelRE.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CBonusRE::CBonusRE(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iBonusType = BONUS_TYPE::BONUS_TYPE_3;

		for (auto res : GameConstant::getInstance()->getResources().bonus1) {
			this->aResources.push_back(res.second);
		}
	}
	CBonusRE::~CBonusRE()
	{

	}
	bool CBonusRE::init()
	{
		if (!CBonusBase::init()) return false;

		auto oBg = Helper4Sprite::createOptimizeSprite(GameConstant::getInstance()->getResources().bonus1["bg"]);
		GameUtils::centerNode(oBg);
		this->addChild(oBg);

		this->oWheel = CSpinWheel::createSpinWheelWithSpriteFrameName(
			"bonus_wheel",
			std::vector<float>{
			2, 5, 25, 80, 30, 20, 60, 50, 25, 35, 12,
				20, 5, 15, 25, 10, 8, 5, 40, 15, 25, 3
		}, 3, 9.0f);
		this->oWheel->setPosition(CSettings::CANVAS_WIDTH / 2 + 14,
			CSettings::CANVAS_HEIGHT / 2 + 25);
		this->addChild(this->oWheel);

		auto needle = Sprite::createWithSpriteFrameName("bonus_needle");
		needle->setPosition(this->oWheel->getPosition());
		this->addChild(needle);

		this->aBtn.resize(1);

		auto btnSpin = CSpriteButton::createButtonWithSpriteFrameName(
			"bonus_btn_spin_normal",
			nullptr,
			[this]() {
			this->btnGamblingClicked(1);
		});
		btnSpin->setScaleEvent(0.9f, 1.0f);
		auto btnSize = btnSpin->getContentSize();
		btnSpin->setCustomTouchZone(Rect(Vec2(-btnSize.width / 2, -btnSize.height / 2), btnSize * 2));
		btnSpin->setImageEvent("bonus_btn_spin_hover");
		btnSpin->setPosition(this->oWheel->getPosition() - Vec2(0, 45));
		this->addChild(btnSpin);

		this->aBtn[0] = btnSpin;

		this->oRule = Sprite::createWithSpriteFrameName("bonus_text_bonus_fs");
		this->oRule->setPosition(CSettings::CANVAS_WIDTH / 2 ,
			85);
		this->addChild(this->oRule);

		return true;
	}

	void CBonusRE::restore()
	{
		auto aHistory = this->oGame->getMain()->getBonusHistory();

		if (!aHistory || aHistory->bonus_step <= 0) {
			return;
		}

		this->showResult(aHistory->finish,
			aHistory->multiplier,
			aHistory->win);

		this->oGame->getMain()->removeBonusHistory();
	}
	void CBonusRE::showResult(bool bFinish, int iTotMulty, double iTotWin)
	{
		if (iTotMulty == 0) return;

		this->bButtonClicked = true;
		this->disableAllBtn();

		this->iTotMul = iTotMulty;
		this->iTotWin = iTotWin;
		this->oRule->setVisible(false);
		this->bFinish = bFinish;
		if (!this->bFinish) {
			int soundID = Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["bonus_3_wheel"], true);
			this->oWheel->spin(iTotMulty, [this, soundID]() {
				this->oGame->chooseItem(1);
				Manager4Sound::getInstance()->stopEffect(soundID);
				Manager4Sound::getInstance()->playDoubleUpWin();
			});
		}
		else {
			this->scheduleOnce(schedule_selector(CBonusRE::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}
	}
	void CBonusRE::showFinalWin(float delay)
	{
		if (this->iTotWin == 0) {
			this->exitFromBonus();
		}
		else {
			((CWinPanelRE*)this->oGame->getWinPanel())->showBonusWinPanel(this->iTotWin, this->iTotMul, [this]() {
				this->exitFromBonus();
			});
		}
	}
	void CBonusRE::resetBonus()
	{
		CBonusBase::resetBonus();
		this->iTotMul = 0;
		this->oWheel->setRotation(0);
		this->oRule->setVisible(true);
	}
}
