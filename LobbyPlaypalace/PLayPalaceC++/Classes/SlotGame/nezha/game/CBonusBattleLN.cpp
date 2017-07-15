#include "CBonusBattleLN.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CBonusBattleLN::CBonusBattleLN(CGameBase* oGame):CBonusBase(oGame),
		iCurRing(0)
	{
		this->iBonusType = BONUS_TYPE::BONUS_TYPE_4;

		for (auto res : GameConstant::getInstance()->getResources().bonus2) {
			this->aResources.push_back(res.second);
		}
	}
	CBonusBattleLN::~CBonusBattleLN()
	{

	}
	bool CBonusBattleLN::init()
	{
		if (!CBonusBase::init()) return false;

		auto res = GameConstant::getInstance()->getResources().bonus2;

		this->oBg = Helper4Sprite::createOptimizeSprite(res["bg_anim_0"]);
		GameUtils::centerNode(this->oBg);
		this->oBg->setScale(2 * 1280 / 1920.0f);
		this->addChild(this->oBg);

		this->aBtn.resize(5);
		createCircleButton(0, Vec2(1114, 709) * CSettings::SCALE_VALUE_TO_1920);
		createCircleButton(1, Vec2(1220, 880) * CSettings::SCALE_VALUE_TO_1920);
		createCircleButton(2, Vec2(1582, 859) * CSettings::SCALE_VALUE_TO_1920);
		createCircleButton(3, Vec2(1382, 769) * CSettings::SCALE_VALUE_TO_1920);
		createCircleButton(4, Vec2(877, 573) * CSettings::SCALE_VALUE_TO_1920);

		this->aRingScore.resize(3);
		for (int i = 0; i < 3; i++) {
			this->createRingScore(i, Vec2(125 + i * 210 + origin.x, 735));
		}

		this->oRule = Sprite::createWithSpriteFrameName("bonusbattle_text_bonus_battle");

		oRule->setScale(scaleDownRatio);
		GameUtils::centerNode(this->oRule);
		this->oRule->setPositionY(CSettings::CANVAS_HEIGHT / 10);
		this->addChild(this->oRule);

		this->oSpearAnim = Sprite::createWithSpriteFrameName("bonusbattle_Bonus-02-spearFX_0");
		this->oSpearAnim->setAnchorPoint(Vec2(1, 1));
		this->oSpearAnim->setVisible(false);
		this->oSpearAnim->setScale(2);
		this->addChild(this->oSpearAnim);

		this->oResultAnim = Helper4Sprite::createOptimizeSprite();
		this->oResultAnim->setVisible(false);
		this->addChild(this->oResultAnim);

		return true;
	}

	void CBonusBattleLN::onBonusEntered()
	{
		CBonusBase::onBonusEntered();
		auto res = GameConstant::getInstance()->getResources().bonus2;
		auto fileNameFormat = "slotgame/nezha/sprites/bonusbattle/bg/Bonus-02-nezha_idle_%i.png";
		this->oBg->stopAllActions();
		this->oBg->runAction(AnimationHelper::getInstance()->createAnimationByFileName(fileNameFormat, 0, 16, 20, -1));
	}

	void CBonusBattleLN::createCircleButton(int index, const cocos2d::Vec2& pos)
	{
		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			"bonusbattle_battle_but",
			nullptr,
			[this, index](){
			this->btnGamblingClicked(index + 1);
		}
		);
		oBtn->setScaleEvent(0.9f, 1.0f);
		oBtn->setPosition(pos);
		this->addChild(oBtn);

		this->aBtn[index] = oBtn;
	}
	void CBonusBattleLN::createRingScore(int index, const cocos2d::Vec2& pos)
	{
		auto parent = Node::create();

		auto bg = Sprite::createWithSpriteFrameName("bonusbattle_universe_ring");

		auto missSymbol = Sprite::createWithSpriteFrameName("bonusbattle_miss_bonus_battle");
		missSymbol->setVisible(false);

		auto winText = LabelAutoSize::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_battle"], "0");
		winText->setTextAreaSize(Size(200, 100));
		winText->setVisible(false);
		winText->setTextColor(Color4B(251, 255, 0, 255));
		winText->enableOutline(Color4B(255, 0, 0, 255));

		parent->addChild(bg);
		parent->addChild(missSymbol);
		parent->addChild(winText);

		parent->setPosition(pos);

		parent->setVisible(false);

		this->addChild(parent);

		this->aRingScore[index] = parent;
	}
	bool CBonusBattleLN::btnGamblingClicked(int iIndex)
	{
		if (this->bButtonClicked) {
			return false;
		}
		this->bButtonClicked = true;
		this->disableAllBtn();

		this->oSpearAnim->setPosition(this->aBtn[iIndex - 1]->getPosition() + Vec2(85, 85));
		this->oSpearAnim->setVisible(true);
		this->oSpearAnim->runAction(Sequence::createWithTwoActions(
			AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().bonus2["bonus_plist_0"],
			"bonusbattle_Bonus-02-spearFX_%i",
			0,
			13,
			60,
			1
			),
			CallFunc::create([this] {
			this->oSpearAnim->setVisible(false);
		})));

		Manager4Sound::getInstance()->playBtnBonusType4Clicked();

		Director::getInstance()->getScheduler()->schedule([this, iIndex](float dt)
		{
			this->oGame->chooseItem(iIndex);
		}, this, 0, 0, 0.5f, false, "CBonusBattleLN_Clicked");
		return true;
	}
	void CBonusBattleLN::showRingScore(double iWin, int index)
	{
		auto ring = this->aRingScore[index];
		ring->setVisible(true);
		if (iWin == 0) {
			ring->getChildren().at(1)->setVisible(true);
			ring->getChildren().at(2)->setVisible(false);
		}
		else {
			ring->getChildren().at(1)->setVisible(false);

			auto oText = (Label*)ring->getChildren().at(2);
			oText->setVisible(true);
			oText->setString(UtilFunction::FormatWithCommas(iWin));
		}
	}
	void CBonusBattleLN::showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, aWheels, iIndex, bFromRestore);

		this->bButtonClicked = true;

		auto iWin = aWheels[iIndex].win;
		auto iSelect = aWheels[iIndex].select - 1;

		this->showRingScore(iWin, this->iCurRing++);

		if (!bFromRestore)
		{
			string frameFormat;
			if (iWin == 0) {
				this->oResultAnim->setSpriteFrame("bonusbattle_Bonus-02-dragon_fireBreath_0");
				this->oResultAnim->setScale(2.92f);
				this->oResultAnim->setPosition(CSettings::CANVAS_WIDTH / 2 - 250, CSettings::CANVAS_HEIGHT / 2 - 85);
				frameFormat = "bonusbattle_Bonus-02-dragon_fireBreath_%i";
			}
			else {
				this->oResultAnim->setPosition(this->aBtn[iSelect]->getPosition());
				this->oResultAnim->setScale(2.0f);
				this->oResultAnim->setSpriteFrame("bonusbattle_Bonus-02-attackImpactFX_0");
				frameFormat = "bonusbattle_Bonus-02-attackImpactFX_%i";
			}
			this->oResultAnim->runAction(Sequence::createWithTwoActions(
				AnimationHelper::getInstance()->createAnimationByFrameName(
				GameConstant::getInstance()->getResources().bonus2["bonus_plist_0"],
				frameFormat,
				0,
				8,
				20,
				1
				),
				CallFunc::create([this]() {
				this->oResultAnim->setVisible(false);
			})));
			this->oResultAnim->setVisible(true);
		}


		this->aBtn[iSelect]->setVisible(false);
		this->aBtn[iSelect]->setTouchEnabled(false);

		if (this->bFinish) {

			this->disableAllBtn();
			this->oRule->setVisible(false);

			for (auto wheel : aWheels) {
				this->iTotWin += wheel.win;
			}
			this->scheduleOnce(schedule_selector(CBonusBattleLN::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}
		else {
			Director::getInstance()->getScheduler()->schedule([this](float dt)
			{
				this->bButtonClicked = false;
			}, this, 0, 0, 1.0f, false, "CBonusBattleLN");
		}
	}
	void CBonusBattleLN::resetBonus()
	{
		CBonusBase::resetBonus();
		for (auto btn : this->aBtn) {
			btn->setVisible(true);
		}
		for (auto ring : this->aRingScore) {
			ring->setVisible(false);
		}
		this->oBg->stopAllActions();
		this->oRule->setVisible(true);
		this->oSpearAnim->stopAllActions();
		this->oSpearAnim->setVisible(false);
		this->oResultAnim->stopAllActions();
		this->oResultAnim->setVisible(false);

		this->iCurRing = 0;
	}
}
