#include "CBonusFreeSpinDB.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"

USING_NS_CC;
namespace GameSlot {
	CBonusFreeSpinDB::CBonusFreeSpinDB(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iBonusType = BONUS_TYPE::BONUS_TYPE_3;

		for (auto res : GameConstant::getInstance()->getResources().bonus1) {
			this->aResources.push_back(res.second);
		}
	}
	CBonusFreeSpinDB::~CBonusFreeSpinDB()
	{

	}
	void CBonusFreeSpinDB::show(double currentWin1, double currentWin2)
	{
		this->iTotFreeSpin = currentWin1;
		this->iTotMulty = currentWin2;
		CBonusBase::show(currentWin1, currentWin2);
	}
	bool CBonusFreeSpinDB::init()
	{
		if (!CBonusBase::init()) return false;

		auto oBg = Sprite::createWithSpriteFrameName("bonus_freespin_bg_bonus_freespin");
		GameUtils::centerNode(oBg);
		this->addChild(oBg);

		this->aBtn.resize(5);

		auto aPos = new Vec2[5]
		{ 
			Vec2(450, 580) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(700, 380) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(950, 580) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(1200, 380) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(1450, 580) * CSettings::SCALE_VALUE_TO_1920
		};

		for (int i = 0; i < 5; ++i) {
			createFish(i, aPos[i], i % 2 == 0? 1.0f : 1.5f);
		}

		this->aTextWin.resize(2);

		for (int i = 0; i < 2; ++i) {
			auto oText = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_freespin_fish"], "");
			oText->setVisible(false);
			oText->setTextColor(Color4B(255, 254, 197, 255));
			oText->enableOutline(Color4B(135, 72, 41, 255));
			oText->setAlignment(TextHAlignment::CENTER);
			this->addChild(oText);

			this->aTextWin[i] = oText;
		}

		CC_SAFE_DELETE_ARRAY(aPos);

		this->oRule = Sprite::createWithSpriteFrameName("bonus_freespin_text_bonus_fs");
		this->oRule->setPosition(CSettings::CANVAS_WIDTH / 2, 85);
		this->addChild(this->oRule);

		this->oTotalTxt = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_freespin"], "");
		this->oTotalTxt->setPosition(CSettings::CANVAS_WIDTH - 250-origin.x, CSettings::CANVAS_HEIGHT - 165);
		this->oTotalTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oTotalTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oTotalTxt);

		return true;
	}

	void CBonusFreeSpinDB::onBonusEntered()
	{
		CBonusBase::onBonusEntered();

		this->iCurStep = 0;
		for (auto btn : this->aBtn) {
			btn->stopAllActions();
			btn->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
				GameConstant::getInstance()->getResources().bonus1["bonus_freespin_fish"],
				"bonus_freespin_bonus_jellyfish_idle_00%i",
				1,
				30,
				30,
				-1
				));
		}

		this->showWinAmountText();
	}

	void CBonusFreeSpinDB::restore()
	{
		auto aHistory = this->oGame->getMain()->getBonusHistory();

		if (!aHistory || aHistory->bonus_step <= 0) {
			return;
		}

		for (auto i = 0; i < aHistory->history.size(); i++) {
			this->showResult(aHistory->finish,
				aHistory->counter,
				aHistory->multiplier,
				aHistory->history,
				i,
				true);
		}

		this->oGame->getMain()->removeBonusHistory();
	}

	bool CBonusFreeSpinDB::btnGamblingClicked(int iIndex)
	{
		if (this->bButtonClicked) {
			return false;
		}
		this->bButtonClicked = true;
		this->disableAllBtn();

		auto scale = this->aBtn[iIndex - 1]->getScale();

		this->aBtn[iIndex - 1]->runAction(Sequence::create(
			ScaleTo::create(0.1f, 2 * scale),
			ScaleTo::create(0.1f, scale),
			CallFunc::create([this, iIndex]() {
			this->oGame->chooseItem(iIndex);
		}), NULL));

		Manager4Sound::getInstance()->playBtnBonusType3Clicked();

		return true;
	}

	void CBonusFreeSpinDB::createFish(int index, const cocos2d::Vec2& pos, float scale)
	{
		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			"bonus_freespin_bonus_jellyfish_idle_001",
			[this, index]() {
			this->btnGamblingClicked(index + 1);
		}, nullptr);
		//oBtn->setScaleEvent(scale * 2, scale);
		oBtn->setPosition(pos);
		oBtn->setScale(scale);

		this->addChild(oBtn);
		this->aBtn[index] = oBtn;
	}

	void CBonusFreeSpinDB::showWinAmountText()
	{
		this->oTotalTxt->setString(ToString(this->iTotFreeSpin) + " FREE SPINS" + "\n" +
			"x" + ToString(this->iTotMulty) + " MULTIPLIER");
	}

	void CBonusFreeSpinDB::showFinalWin(float delay)
	{
		this->oGame->getWinPanel()->showFreeSpinWinPanel(this->iTotFreeSpin, this->iTotMulty,[this]() {
			this->exitFromBonus();
		});
	}

	void CBonusFreeSpinDB::showResult(bool bFinish, int iTotFreeSpin, int iTotMulty, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, iTotFreeSpin, iTotMulty, aWheels, bFromRestore);

		this->iTotFreeSpin = iTotFreeSpin;
		this->iTotMulty = iTotMulty;

		auto iWin = aWheels[iIndex].win;
		auto iSelect = aWheels[iIndex].select - 1;
		auto type = aWheels[iIndex].type;

		auto typeBonus = "";
		if (type == 3) {
			typeBonus = "FREE SPINS";
		}
		else if (type == 2) {
			typeBonus = "MULTIPLIER";
		}
		//Get text
		auto text = this->aTextWin[this->iCurStep++];
		text->setPosition(this->aBtn[iSelect]->getPosition());
		text->setString("+" +ToString(iWin) + "\n" + typeBonus);
		text->setVisible(true);
		//disabled that button after selecting
		this->aBtn[iSelect]->setTouchEnabled(false);

		if (bFinish) {
			this->disableAllBtn();
			this->oRule->setVisible(false);
			this->scheduleOnce(schedule_selector(CBonusFreeSpinDB::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}

		this->showWinAmountText();
	}
	void CBonusFreeSpinDB::exitFromBonus()
	{
		this->resetBonus();

		this->setVisible(false);
		this->oGame->setVisible(true);

		this->oGame->exitFromBonusFreeSpin(iTotFreeSpin, iTotMulty);
	}
	void CBonusFreeSpinDB::resetBonus()
	{
		CBonusBase::resetBonus();
		this->iTotFreeSpin = 0;
		this->iTotMulty = 0;
		for (auto btn : this->aBtn) {
			btn->stopAllActions();
		}

		for (auto text : this->aTextWin) {
			text->setVisible(false);
		}
		this->oRule->setVisible(true);
	}
}
