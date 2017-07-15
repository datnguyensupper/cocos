#include "CBonusPalaceLN.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "Custom/Common/LabelAutoSize.h"

USING_NS_CC;
namespace GameSlot {
	CBonusPalaceLN::CBonusPalaceLN(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iBonusType = BONUS_TYPE::BONUS_TYPE_3;

		for (auto res : GameConstant::getInstance()->getResources().bonus1) {
			this->aResources.push_back(res.second);
		}

		this->aPosNormal = new Vec2[4];
		this->aPosNormal[0] = Vec2(668, 262) * CSettings::SCALE_VALUE_TO_1920;
		this->aPosNormal[1] = Vec2(1237, 303) * CSettings::SCALE_VALUE_TO_1920;
		this->aPosNormal[2] = Vec2(1366, 870) * CSettings::SCALE_VALUE_TO_1920;
		this->aPosNormal[3] = Vec2(508, 835) * CSettings::SCALE_VALUE_TO_1920;

		this->aPosTouched = new Vec2[4];
		this->aPosTouched[0] = Vec2(686, 339) * CSettings::SCALE_VALUE_TO_1920;
		this->aPosTouched[1] = Vec2(1285, 350) * CSettings::SCALE_VALUE_TO_1920;
		this->aPosTouched[2] = Vec2(1365, 837) * CSettings::SCALE_VALUE_TO_1920;
		this->aPosTouched[3] = Vec2(502, 835) * CSettings::SCALE_VALUE_TO_1920;

		this->aNameSpriteNormal = new string[4];
		this->aNameSpriteNormal[0] = "bonuspalace_Spear-Normal";
		this->aNameSpriteNormal[1] = "bonuspalace_fenghuolun-normal";
		this->aNameSpriteNormal[2] = "bonuspalace_ring-normal";
		this->aNameSpriteNormal[3] = "bonuspalace_sash-normal";

		this->aNameSpriteTouched = new string[4];
		this->aNameSpriteTouched[0] = "bonuspalace_Spear-mouse-over";
		this->aNameSpriteTouched[1] = "bonuspalace_fenghuolun-mouse-over";
		this->aNameSpriteTouched[2] = "bonuspalace_ring-mouse-over";
		this->aNameSpriteTouched[3] = "bonuspalace_sash-mouse-over";

	}
	CBonusPalaceLN::~CBonusPalaceLN()
	{
		CC_SAFE_DELETE_ARRAY(this->aPosNormal);
		CC_SAFE_DELETE_ARRAY(this->aPosTouched);
		CC_SAFE_DELETE_ARRAY(this->aNameSpriteNormal);
		CC_SAFE_DELETE_ARRAY(this->aNameSpriteTouched);
	}
	bool CBonusPalaceLN::init()
	{
		if (!CBonusBase::init()) return false;

		auto bg = Sprite::createWithSpriteFrameName("bonuspalace_bg_bonus_palace");
		GameUtils::centerNode(bg);
		bg->setScale(1.5f);
		this->addChild(bg);

		this->aBtn.resize(4);
		this->aBox.resize(4);
		this->aText.resize(4);
		
		for (int i = 0; i < 4; ++i) {
			this->createWeaponButton(i);
		}

		this->oRule = Sprite::createWithSpriteFrameName("bonuspalace_text_bonus_palace");
		GameUtils::centerNode(this->oRule);
		this->oRule->setPositionY(CSettings::CANVAS_HEIGHT / 10);
		this->addChild(this->oRule);

		this->oExplosion = Sprite::createWithSpriteFrameName("Bonus-01-weaponExplodeEffects_1");
		this->oExplosion->setScale(2);
		this->oExplosion->setVisible(false);
		this->addChild(this->oExplosion);

		return true;
	}

	void CBonusPalaceLN::createWeaponButton(int index)
	{
		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			this->aNameSpriteNormal[index],
			nullptr,
			[this, index](){
			this->btnGamblingClicked(index + 1);
		}
		);
		oBtn->setPosition(this->aPosNormal[index]);
		this->addChild(oBtn);

		auto oBox = Sprite::createWithSpriteFrameName("bonuspalace_bonus-box");
		oBox->setPosition(oBtn->getPositionX(), 150 + floor((index + 1) / 3) * 396);
		oBox->setVisible(false);
		this->addChild(oBox);

		auto oText = LabelAutoSize::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_palace"], "0");
		oText->setTextAreaSize(Size(275, 100));
		oText->setPosition(oBox->getPosition());
		oText->setVisible(false);
		oText->setTextColor(Color4B(251, 255, 0, 255));
		this->addChild(oText);

		this->aBtn[index] = oBtn;
		this->aBox[index] = oBox;
		this->aText[index] = oText;
	}
	void CBonusPalaceLN::enableAllBtn()
	{
		for (int i = 0; i < this->aBtn.size(); i++) {
			this->aBtn[i]->setTouchEnabled(true);
			this->aBtn[i]->setSpriteFrame(this->aNameSpriteNormal[i]);
			this->aBtn[i]->setPosition(this->aPosNormal[i]);

			this->aBox[i]->setVisible(false);

			this->aText[i]->setVisible(false);
			this->aText[i]->setTextColor(Color4B(251, 255, 0, 255));
		}
	}
	bool CBonusPalaceLN::btnGamblingClicked(int iIndex)
	{
		if (CBonusBase::btnGamblingClicked(iIndex)) {
			this->oExplosion->setPosition(this->aBtn[iIndex - 1]->getPosition());
			this->oExplosion->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
				GameConstant::getInstance()->getResources().mainGame["explosion_plist"],
				"Bonus-01-weaponExplodeEffects_%i",
				1,
				15,
				15,
				1));
			this->oExplosion->setVisible(true);
			return true;
		};
		return false;
	}
	void CBonusPalaceLN::setBtnSprite(int index, double iWin, bool bSelected)
	{
		this->aText[index]->setString(UtilFunction::FormatWithCommas(iWin));
		if (bSelected) {
			this->aBtn[index]->setSpriteFrame(this->aNameSpriteTouched[index]);
			this->aBtn[index]->setPosition(this->aPosTouched[index]);
		}
		else {
			this->aText[index]->setTextColor(Color4B(63,63,63, 255));
		}
		this->aBox[index]->setVisible(true);
		this->aText[index]->setVisible(true);
	}
	void CBonusPalaceLN::showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, aWheels, iIndex, bFromRestore);
		for (int i = 0; i < aWheels.size(); i++)
		{
			auto iWin = aWheels[i].win;
			auto iSelect = aWheels[i].select;
			if (iSelect > 0)
			{
				this->iTotWin = iWin;
				this->setBtnSprite(i, iWin, true);
			}
			else {
				this->setBtnSprite(i, iWin, false);
			}
		}

		if (bFinish) {
			this->disableAllBtn();
			this->oRule->setVisible(false);
			this->scheduleOnce(schedule_selector(CBonusPalaceLN::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}
	}
	void CBonusPalaceLN::resetBonus()
	{
		CBonusBase::resetBonus();
		this->oRule->setVisible(true);
		this->oExplosion->stopAllActions();
		this->oExplosion->setVisible(false);
	}
}
