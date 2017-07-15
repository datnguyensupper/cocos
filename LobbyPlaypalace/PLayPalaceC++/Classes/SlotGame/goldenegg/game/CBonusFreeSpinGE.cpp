#include "CBonusFreeSpinGE.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"

USING_NS_CC;
namespace GameSlot {
	CBonusFreeSpinGE::CBonusFreeSpinGE(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iBonusType = BONUS_TYPE::BONUS_TYPE_3;

		for (auto res : GameConstant::getInstance()->getResources().bonus1) {
			this->aResources.push_back(res.second);
		}
		this->aResources.push_back(GameConstant::getInstance()->getResources().doubleUp[""]);
	}
	CBonusFreeSpinGE::~CBonusFreeSpinGE()
	{

	}
	void CBonusFreeSpinGE::show(double currentWin1, double currentWin2)
	{
		this->iTotFreeSpin = currentWin1;
		this->iTotMulty = currentWin2;
		CBonusBase::show(currentWin1, currentWin2);
	}
	bool CBonusFreeSpinGE::init()
	{
		if (!CBonusBase::init()) return false;

		auto oBg = Sprite::createWithSpriteFrameName("bonus_freespin_bg_bonus_freespin");
		GameUtils::centerNode(oBg);
		this->addChild(oBg);

		this->aEggResult.resize(2);

		for (int i = 0; i < 2; ++i) {
			auto parent = Node::create();
			auto egg = Sprite::createWithSpriteFrameName("bonus_freespin_gold-egg-option");
			egg->setScale(0.6f);
			egg->setRotation(65);
			egg->setPosition(0, -85);
			auto mulNumber = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_freespin_egg"], "");
			mulNumber->setTextColor(Color4B(255, 254, 197, 255));
			mulNumber->setHorizontalAlignment(TextHAlignment::CENTER);
			parent->addChild(egg);
			parent->addChild(mulNumber);

			this->addChild(parent);
			this->aEggResult[i] = parent;
		}

		this->aBtn.resize(5);

		auto aPos = new Vec2[5]
		{ 
			Vec2(1300, 780) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(950, 780) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(800, 330) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(650, 780) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(1200, 330) * CSettings::SCALE_VALUE_TO_1920
		};

		for (int i = 0; i < 5; ++i) {
			createFish(i, aPos[i]);
		}

		CC_SAFE_DELETE_ARRAY(aPos);

		this->oRule = Sprite::createWithSpriteFrameName("bonus_freespin_text_bonus_fs");
		this->oRule->setPosition(CSettings::CANVAS_WIDTH / 2, CSettings::CANVAS_HEIGHT / 2 - 40);
		this->addChild(this->oRule);

		this->oTotalFreeSpinTxt = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_freespin"], "");
		this->oTotalFreeSpinTxt->setPosition(328, 405);
		this->oTotalFreeSpinTxt->setRotation(-15);
		this->oTotalFreeSpinTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oTotalFreeSpinTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oTotalFreeSpinTxt);

		this->oTotalMultyTxt = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_freespin"], "");
		this->oTotalMultyTxt->setPosition(1262, this->oTotalFreeSpinTxt->getPositionY());
		this->oTotalMultyTxt->setRotation(15);
		this->oTotalMultyTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oTotalMultyTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oTotalMultyTxt);

		return true;
	}

	void CBonusFreeSpinGE::onBonusEntered()
	{
		CBonusBase::onBonusEntered();
		this->iCurStep = 0;
		this->showWinAmountText();
	}

	void CBonusFreeSpinGE::restore()
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

	void CBonusFreeSpinGE::createFish(int index, const cocos2d::Vec2& pos)
	{
		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			index == 1 || index == 3 ?
			"bonus_front_fly_bonus_front_fly_00":"bonus_side_fly_bonus_side_fly_00",
			nullptr,
			[this, index](){
			this->btnGamblingClicked(index + 1);
		}
		);
		oBtn->setPosition(pos);
		oBtn->setCustomTouchZone(Rect(Vec2(-7, -15), Size(oBtn->getContentSize()) + Size(-15, -30)));
		this->addChild(oBtn);

		this->aBtn[index] = oBtn;
	}

	bool CBonusFreeSpinGE::btnGamblingClicked(int iIndex)
	{
		if (this->bButtonClicked) {
			return false;
		}
		this->bButtonClicked = true;
		this->disableAllBtn();

		auto res = GameConstant::getInstance()->getResources().bonus1;
		std::string plist = "bonus_anim_side";
		std::string frameFormat = "bonus_side_fly_bonus_side_fly_%.2i";
		int endFrame = 13;
		if (iIndex == 2 || iIndex == 4) {
			plist = "bonus_anim_front";
			frameFormat = "bonus_front_fly_bonus_front_fly_%.2i";
			endFrame = 10;
		}


		this->aBtn[iIndex - 1]->runAction(Sequence::createWithTwoActions(
			AnimationHelper::getInstance()->createAnimationByFrameName(
				res[plist],
				frameFormat,
				0,
				endFrame,
				20,
				1
				),
			CallFunc::create([this, iIndex]() {
			this->aBtn[iIndex - 1]->setVisible(false);
			this->oGame->chooseItem(iIndex);
		})
			));
			
		Manager4Sound::getInstance()->playBtnBonusType3Clicked();

		return true;
	}

	void CBonusFreeSpinGE::showWinAmountText()
	{
		this->oTotalFreeSpinTxt->setString(ToString(this->iTotFreeSpin));
		this->oTotalMultyTxt->setString("x" + ToString(this->iTotMulty));
	}

	void CBonusFreeSpinGE::showFinalWin(float delay)
	{
		this->oGame->getWinPanel()->showFreeSpinWinPanel(this->iTotFreeSpin, this->iTotMulty,[this]() {
			this->exitFromBonus();
		});
	}

	void CBonusFreeSpinGE::showResult(bool bFinish, int iTotFreeSpin, int iTotMulty, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
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
		auto text = ((Label*)this->aEggResult[this->iCurStep]->getChildren().at(1));
		text->setString("+" + ToString(iWin) + " " + typeBonus);
		this->aEggResult[this->iCurStep]->setVisible(true);
		this->aEggResult[this->iCurStep++]->setPosition(this->aBtn[iSelect]->getPosition() + Vec2(0, -40));
		Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["bonus_3_reward"]);
		//disabled that button after selecting
		this->aBtn[iSelect]->setTouchEnabled(false);
		this->aBtn[iSelect]->setVisible(false);
		if (bFinish) {
			this->disableAllBtn();
			this->oRule->setVisible(false);
			this->scheduleOnce(schedule_selector(CBonusFreeSpinGE::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}

		this->showWinAmountText();
	}
	void CBonusFreeSpinGE::exitFromBonus()
	{
		this->resetBonus();

		this->setVisible(false);
		this->oGame->setVisible(true);

		this->oGame->exitFromBonusFreeSpin(iTotFreeSpin, iTotMulty);
	}
	void CBonusFreeSpinGE::resetBonus()
	{
		CBonusBase::resetBonus();
		this->iTotFreeSpin = 0;
		this->iTotMulty = 0;

		std::string frameName = "";
		for (int i = 0; i < this->aBtn.size(); ++i) {
			if (i % 2 == 1) {
				frameName = "bonus_front_fly_bonus_front_fly_00";
			}
			else {
				frameName = "bonus_side_fly_bonus_side_fly_00";
			}
			this->aBtn[i]->stopAllActions();
			this->aBtn[i]->setVisible(true);
			this->aBtn[i]->setSpriteFrame(frameName);
		}

		for (auto egg : this->aEggResult) {
			egg->setVisible(false);
		}

		this->oRule->setVisible(true);
	}
}
