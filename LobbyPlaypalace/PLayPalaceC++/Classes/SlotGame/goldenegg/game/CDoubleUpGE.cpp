#include "CDoubleUpGE.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CDoubleUpGE::CDoubleUpGE(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iGameType = GAME_TYPE::DOUBLE_UP;
		this->iBonusType = BONUS_TYPE::BONUS_DOUBLE_UP;

		for (auto res : GameConstant::getInstance()->getResources().doubleUp) {
			this->aResources.push_back(res.second);
		}
	}
	CDoubleUpGE::~CDoubleUpGE()
	{

	}
	bool CDoubleUpGE::init()
	{
		if (!CBonusBase::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		auto oBg = Helper4Sprite::createOptimizeSprite(res.doubleUp["bg"]);
		GameUtils::centerNode(oBg);
		this->addChild(oBg);

		this->aBtn.resize(3);

		auto btnCollect = CSpriteButton::createButtonWithSpriteFrameName(
			"doubleup_btn_collect-start",
			nullptr,
			[this]() {
			this->btnGamblingClicked(0);
		}
		);
		btnCollect->setPosition(CSettings::CANVAS_WIDTH / 2. - 375, CSettings::CANVAS_HEIGHT / 2 + 115);
		btnCollect->setScaleEvent(0.9f, 1.0f);
		btnCollect->setImageEvent("doubleup_btn_collect-over");
		this->addChild(btnCollect);
		this->aBtn[0] = btnCollect;

		createEggButton(1, "normal", Vec2(CSettings::CANVAS_WIDTH / 2 - 500+origin.x/4, CSettings::CANVAS_HEIGHT / 2 - 85));
		createEggButton(2, "golden", Vec2(CSettings::CANVAS_WIDTH / 2 + 500-origin.x/4, CSettings::CANVAS_HEIGHT / 2 - 85));

		auto currentWinBG = Sprite::createWithSpriteFrameName("doubleup_current-win");
		currentWinBG->setPosition(CSettings::CANVAS_WIDTH / 2 - 415, 150);
		currentWinBG->setAnchorPoint(Vec2(0.5f, 0.65f));
		this->addChild(currentWinBG);

		auto potentialWinBG = Sprite::createWithSpriteFrameName("doubleup_potential-win");
		potentialWinBG->setPosition(CSettings::CANVAS_WIDTH / 2 + 415, 150);
		potentialWinBG->setAnchorPoint(Vec2(0.5f, 0.65f));
		this->addChild(potentialWinBG);

		this->oCurrentWinTxt = Label::createWithTTF(res.fontConfigs["double_up"], "0");
		this->oCurrentWinTxt->setPosition(currentWinBG->getPosition());
		this->oCurrentWinTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oCurrentWinTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oCurrentWinTxt);

		this->oPotentialWinTxt = Label::createWithTTF(res.fontConfigs["double_up"], "0");
		this->oPotentialWinTxt->setPosition(potentialWinBG->getPosition());
		this->oPotentialWinTxt->setTextColor(Color4B(134, 240, 33, 255));
		this->oPotentialWinTxt->enableOutline(Color4B(30, 45, 19, 255));
		this->addChild(this->oPotentialWinTxt);

		auto oRule = Sprite::createWithSpriteFrameName("doubleup_guess-the-next-egg-laid");
		oRule->setScale(scaleDownRatio);
		oRule->setPosition(CSettings::CANVAS_WIDTH / 2 + 35, CSettings::CANVAS_HEIGHT - 165);
		oRule->setAnchorPoint(Vec2(0, 1));
		this->addChild(oRule);

		this->oResultEgg = Helper4Sprite::createOptimizeSprite();
		this->oResultEgg->setPositionX(CSettings::CANVAS_WIDTH / 2);
		this->oResultEgg->setRotation(80);
		this->oResultEgg->setVisible(false);
		this->addChild(this->oResultEgg);

		return true;
	}
	void CDoubleUpGE::onBonusEntered()
	{
		CBonusBase::onBonusEntered();

		this->updateTotalWinText();
	}
	void CDoubleUpGE::restore()
	{
		this->oGame->getMain()->removeBonusHistory();
	}
	void CDoubleUpGE::createEggButton(
		int index, 
		const std::string & eggName, 
		const cocos2d::Vec2 & pos)
	{
		bool isNormalEgg = eggName.compare("normal") == 0;

		auto egg = Sprite::createWithSpriteFrameName("doubleup_" + eggName + "-egg-option");
		this->addChild(egg);

		auto basket = Sprite::createWithSpriteFrameName("doubleup_basket");
		basket->setScale(0.8f);
		this->addChild(basket);

		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			"doubleup_" + eggName + "-egg-start",
			nullptr,
			[this, index]() {
			this->btnGamblingClicked(index);
		}
		);
		oBtn->setScaleEvent(0.9f, 1.0f);
		oBtn->setImageEvent("doubleup_" + eggName + "-egg-over");
		oBtn->setPosition(pos);
		this->addChild(oBtn);


		if (isNormalEgg) {
			egg->setPosition(pos + Vec2(240, 25));
			basket->setPosition(egg->getPosition() + Vec2(8, -70));
			oBtn->setCustomTouchZone(Rect(Vec2(0, -8), oBtn->getContentSize() + Size(250, 8)));
		}
		else {
			egg->setPosition(pos + Vec2(-240, 20));
			basket->setPosition(egg->getPosition() + Vec2(-8, -70));
			oBtn->setCustomTouchZone(Rect(Vec2(-250, -8), oBtn->getContentSize() + Size(250, 8)));
		}

		this->aBtn[index] = oBtn;
	}
	bool CDoubleUpGE::btnGamblingClicked(int iIndex)
	{
		if (this->bButtonClicked) {
			return false;
		}
		this->bButtonClicked = true;
		this->disableAllBtn();
		this->oGame->chooseItem(iIndex);

		if (iIndex == 0) {
			Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["double_up_collect"]);
		}
		else {
			Manager4Sound::getInstance()->playBtnDoubleUpClicked();
		}
		return true;
	}
	void CDoubleUpGE::playResultAnimation(bool isNormalEgg)
	{
		this->oResultEgg->setSpriteFrame(isNormalEgg ? "doubleup_normal-egg-option" : "doubleup_golden-egg-option");
		this->oResultEgg->setPositionY(CSettings::CANVAS_HEIGHT / 2 + 85);
		this->oResultEgg->setScale(0.5f);
		this->oResultEgg->setOpacity(255);
		this->oResultEgg->runAction(EaseQuinticActionOut::create(MoveTo::create(2.0f, Vec2(this->oResultEgg->getPositionX(), 170))));
		this->oResultEgg->runAction(Sequence::create(
			EaseQuinticActionOut::create(ScaleTo::create(2.0f, 1.0f)),
			FadeOut::create(0.5f),
			CallFunc::create([this]() {
			this->oResultEgg->setVisible(false);

			if (this->bFinish) {
				this->scheduleOnce(schedule_selector(CDoubleUpGE::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
			}
			else {
				this->enableAllBtn();
			}
		}),
			NULL));
		this->oResultEgg->setVisible(true);
	}
	void CDoubleUpGE::updateTotalWinText()
	{
		if (this->iTotWin > 0) {
			this->oCurrentWinTxt->setString(UtilFunction::FormatWithCommas(this->iTotWin));
			this->oPotentialWinTxt->setString(UtilFunction::FormatWithCommas(this->iTotWin * 2));

			this->oCurrentWinTxt->runAction(Sequence::createWithTwoActions(
				EaseBounceOut::create(ScaleTo::create(0.1f, 1.5f)),
				EaseCubicActionIn::create(ScaleTo::create(0.1f, 1.0f))));

			this->oPotentialWinTxt->runAction(Sequence::createWithTwoActions(
				EaseBounceOut::create(ScaleTo::create(0.1f, 1.5f)),
				EaseCubicActionIn::create(ScaleTo::create(0.1f, 1.0f))));
		}
	}
	void CDoubleUpGE::showResult(bool bFinish, int iResult, double iTotWin, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, iResult, iTotWin);
		this->disableAllBtn();

		if (iResult != 0) {
			Manager4Sound::getInstance()->setVolumeBackgroundMusic(0.0f);

			Director::getInstance()->getScheduler()->schedule([this](float dt) {
				Manager4Sound::getInstance()->setVolumeBackgroundMusic(1.0f);
			}, this, 0, 0, 0.8f, false, "CDoubleUpGE_result");

			if (!this->bFinish) {
				//user win
				Manager4Sound::getInstance()->playDoubleUpWin();
			}
			else {
				//user lose
				Manager4Sound::getInstance()->playDoubleUpLose();
			}
		}

		if (iResult == 1) {
			this->playResultAnimation(true);
		}
		else if (iResult == 2) {
			this->playResultAnimation(false);
		}
		else if (bFinish) {
			this->scheduleOnce(schedule_selector(CDoubleUpGE::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}


		this->updateTotalWinText();
	}
	void CDoubleUpGE::resetBonus()
	{
		CBonusBase::resetBonus();
		this->oResultEgg->stopAllActions();
		this->oResultEgg->setVisible(false);
	}
}
