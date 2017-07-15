#include "CBonusStage2PO.h"
#include "SlotGame/base/game/CGameBase.h"
#include "../interfaceUI/CWinPanelPO.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "Custom/Common/CSpinWheel.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CBonusStage2PO::CBonusStage2PO(CGameBase* oGame) :CBonusBase(oGame),
		iModeBonus(0),
		iTotMulty(0),
		iTotWin1(0),
		iTotWin2(0)
	{
		this->iBonusType = BONUS_TYPE::BONUS_TYPE_3;

		for (auto res : GameConstant::getInstance()->getResources().bonus2) {
			this->aResources.push_back(res.second);
		}
	}
	CBonusStage2PO::~CBonusStage2PO()
	{

	}
	void CBonusStage2PO::show(int iModeBonus)
	{
		this->iModeBonus = iModeBonus;
		CBonusBase::show(0);
	}
	bool CBonusStage2PO::init()
	{
		if (!CBonusBase::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		auto oBG = Helper4Sprite::createOptimizeSprite(res.bonus2["bg"]);
		GameUtils::centerNode(oBG);
		this->addChild(oBG);

		this->oWheelBG = Node::create();
		this->oWheelBG->setPosition(CSettings::CANVAS_WIDTH / 2 + 16, CSettings::CANVAS_HEIGHT / 2);
		this->addChild(this->oWheelBG);
			
		auto wheelBG = Sprite::createWithSpriteFrameName("bonus_2_wheel_bg");
		this->oWheelBG->addChild(wheelBG);

		std::vector<float> aInfo;
		this->oWheel = CSpinWheel::createSpinWheelWithSpriteFrameName("bonus_2_wheel_1", aInfo, 3, 9.0f);
		this->oWheel->setPosition(this->oWheelBG->getPosition());
		this->addChild(oWheel);

		auto arrow = Sprite::createWithSpriteFrameName("bonus_2_arrow");
		arrow->setPosition(this->oWheelBG->getPosition() + Vec2(0, 267));
		this->addChild(arrow);

		this->aGem.resize(3);

		auto posGem = new Vec2[3]{ Vec2(-360, 125), Vec2(7, 380),Vec2(362, 115) };
		auto angleGem = new int[3]{ -72, 0, 72 };

		for (int i = 0, size = this->aGem.size(); i < size; ++i) {
			auto oGem = Sprite::createWithSpriteFrameName("bonus_2_gem");
			oGem->setPosition(posGem[i] * CSettings::SCALE_VALUE_TO_1920);
			oGem->setRotation(angleGem[i]);
			this->oWheelBG->addChild(oGem);
			this->aGem[i] = oGem;
		}
		CC_SAFE_DELETE_ARRAY(posGem);
		CC_SAFE_DELETE_ARRAY(angleGem);

		this->aBtn.resize(1);

		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			"bonus_2_aim",
			nullptr,
			[this]() {
			this->btnGamblingClicked(1);
		});
		oBtn->setImageEvent("", "bonus_2_aim-pressed");
		oBtn->setPosition(this->oWheelBG->getPosition());
		this->addChild(oBtn);

		this->aBtn[0] = oBtn;

		this->oBetIndicator = this->createIndicator("bonus_2_box-total-bet", Vec2(CSettings::CANVAS_WIDTH / 2 - 335, 670), "", 0.6f);
		this->oMulIndicator = this->createIndicator("bonus_2_box-multiplier", Vec2(CSettings::CANVAS_WIDTH / 2 + 365, 670), "", 0.6f);
		this->oWinIndicator = this->createIndicator("bonus_2_box-totalwin", Vec2(CSettings::CANVAS_WIDTH / 2 + 16, 85), "", 1);

		this->oRule = Sprite::createWithSpriteFrameName("bonus_2_instruction");
		GameUtils::centerNode(this->oRule);
		this->oRule->setPositionY(85);
		this->addChild(this->oRule);

		return true;
	}

	void CBonusStage2PO::onBonusEntered()
	{
		CBonusBase::onBonusEntered();
		for (auto gem : this->aGem) {
			gem->setOpacity(100);
		}
		this->oBetIndicator->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getTotalBet()));

		std::vector<float> aWheelInfo;
		switch (this->iModeBonus)
		{
		case 1:
			aWheelInfo = std::vector<float>{
				4,
				80,
				8,
				10,
				50,
				5,
				20,
				100,
				15,
				3
			};
			break;
		case 2:
			aWheelInfo = std::vector<float>{
				4,
				3,
				5,
				60,
				8,
				10,
				15,
				200,
				25,
				100
			};
			break;
		case 3:
			aWheelInfo = std::vector<float>{
				200,
				100,
				10,
				80,
				5,
				50,
				20,
				300,
				8,
				15
			};
			break;
		default:
			break;
		}
		this->oWheel->setSpriteFrame("bonus_2_wheel_" + ToString(this->iModeBonus));
		this->oWheel->initWheelInfo(aWheelInfo);

		this->oWheelBG->runAction(RepeatForever::create(RotateBy::create(5.0f, -60)));

	}
	cocos2d::Label* CBonusStage2PO::createIndicator(const std::string & boxSpriteName, const cocos2d::Vec2 & pos, const std::string & text, float scaleTextValue)
	{
		auto oSprite = Sprite::createWithSpriteFrameName(boxSpriteName);
		oSprite->setPosition(pos);

		auto fontConfig = GameConstant::getInstance()->getResources().fontConfigs["bonus_4"];
		fontConfig.fontSize *= scaleTextValue;

		auto oText = LabelAutoSize::createWithTTF(fontConfig, text);
		oText->setTextAreaSize(Size(oSprite->getContentSize().width * (0.55f + (1 - scaleTextValue) / 5), 100));
		oText->setTextColor(Color4B(232, 201, 46, 255));
		oText->enableOutline(Color4B(133, 71, 3, 255));
		oText->setPosition((Vec2)oSprite->getContentSize() / 2 - Vec2(0, (1 - scaleTextValue) * 16));
		oSprite->addChild(oText);

		oSprite->setVisible(false);
		this->addChild(oSprite);

		return oText;
	}

	void CBonusStage2PO::showResultAfterRol()
	{
		this->oBetIndicator->getParent()->setVisible(true);
		this->oMulIndicator->getParent()->setVisible(true);
		this->oWinIndicator->getParent()->setVisible(true);

		this->oMulIndicator->setString(UtilFunction::FormatWithCommas(this->iTotMulty));
		this->oWinIndicator->setString(UtilFunction::FormatWithCommas(this->iTotWin));
	}

	void CBonusStage2PO::showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, aWheels, iIndex, bFromRestore);

		this->disableAllBtn();

		this->iTotWin = aWheels[iIndex].win;
		auto iSelect = aWheels[iIndex].select - 1;
		auto iPrize = aWheels[iIndex].type;
		this->iTotMulty += iPrize;

		this->aGem[iIndex]->setOpacity(255);
		this->oRule->setVisible(false);

		if (!bFromRestore)
		{
			int soundID = Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["bonus_4_wheel_spin"]);
			this->oWheel->spin(iPrize,
				[this, soundID, aWheels]() {
				Manager4Sound::getInstance()->stopEffect(soundID);
				Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["bonus_4_wheel_stop"]);

				if (this->bFinish) {
					this->iTotWin1 = aWheels[2].win;
					this->iTotWin2 = aWheels[2].win_pot;
					this->iTotWin = this->iTotWin2;
					this->scheduleOnce(schedule_selector(CBonusStage2PO::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS / 2);
				}
				else {
					this->enableAllBtn();
				}
				this->showResultAfterRol();
			});
		}
		else {
			this->showResultAfterRol();
			this->enableAllBtn();
		}
	}

	void CBonusStage2PO::showFinalWin(float delay)
	{
		this->iTotWin = this->iTotWin1 + this->iTotWin2;
		((CWinPanelPO*)this->oGame->getWinPanel())->showBonusWinPanel(this->iTotWin1, this->iTotWin2, CC_CALLBACK_0(CBonusStage2PO::exitFromBonus, this));
	}

	void CBonusStage2PO::resetBonus()
	{
		CBonusBase::resetBonus();
		this->iTotMulty = 0;
		this->iTotWin1 = 0;
		this->iTotWin2 = 0;
		this->oRule->setVisible(true);
		this->oBetIndicator->getParent()->setVisible(false);
		this->oWinIndicator->getParent()->setVisible(false);
		this->oMulIndicator->getParent()->setVisible(false);
		this->oWheelBG->stopAllActions();
	}
}
