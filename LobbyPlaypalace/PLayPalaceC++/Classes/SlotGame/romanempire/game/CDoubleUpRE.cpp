#include "CDoubleUpRE.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"

USING_NS_CC;
namespace GameSlot {
	CDoubleUpRE::CDoubleUpRE(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iGameType = GAME_TYPE::DOUBLE_UP;
		this->iBonusType = BONUS_TYPE::BONUS_DOUBLE_UP;

		for (auto res : GameConstant::getInstance()->getResources().doubleUp) {
			this->aResources.push_back(res.second);
		}
	}
	CDoubleUpRE::~CDoubleUpRE()
	{
		aResultHeadFrame.clear();
		aResultTailFrame.clear();
	}
	bool CDoubleUpRE::init()
	{
		if (!CBonusBase::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		this->oBg = Sprite::createWithSpriteFrameName("doubleup_double-up-bg");
		GameUtils::centerNode(this->oBg);
		this->addChild(this->oBg);

		this->aBtn.resize(3);

		this->initAnimaton();

		this->oBgResult = Sprite::createWithSpriteFrame(this->aResultHeadFrame.at(0));
		GameUtils::centerNode(this->oBgResult);
		this->oBgResult->setVisible(false);
		this->oBgResult->setScale(1280 / 640.0f);
		this->addChild(this->oBgResult);

		this->oInfo = Node::create();
		this->addChild(this->oInfo);

		auto btnCollect = CSpriteButton::createButtonWithSpriteFrameName("doubleup_btn_collect",
			nullptr,
			[this]() {
			this->btnGamblingClicked(0);
		});
		btnCollect->setPosition(Vec2(1290, 340) * CSettings::SCALE_VALUE_TO_1920);
		btnCollect->setScale(1.05f);
		btnCollect->setScaleEvent(1.0f, 1.05f);
		this->oInfo->addChild(btnCollect);

		this->aBtn[0] = btnCollect;

		createButtonCoin(1, "head", Vec2(1135, 640) * CSettings::SCALE_VALUE_TO_1920);
		createButtonCoin(2, "tail", Vec2(1448, 640) * CSettings::SCALE_VALUE_TO_1920);


		this->oCurrentWinTxt = Label::createWithTTF(res.fontConfigs["double_up"], "0");
		this->oCurrentWinTxt->setPosition(Vec2(1503, 820) * CSettings::SCALE_VALUE_TO_1920);
		this->oCurrentWinTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oCurrentWinTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->oInfo->addChild(this->oCurrentWinTxt);

		this->oPotentialWinTxt = Label::createWithTTF(res.fontConfigs["double_up"], "0");
		this->oPotentialWinTxt->setPosition(Vec2(1503, 772) * CSettings::SCALE_VALUE_TO_1920);
		this->oPotentialWinTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oPotentialWinTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->oInfo->addChild(this->oPotentialWinTxt);

		return true;
	}
	void CDoubleUpRE::onBonusEntered()
	{
		CBonusBase::onBonusEntered();
		this->updateTotalWinText();
	}
	void CDoubleUpRE::initAnimaton()
	{
		auto res = GameConstant::getInstance()->getResources().doubleUp;
		Rect rect = Rect::ZERO;
		Texture2D *texture;
		SpriteFrame *frame;
		for (int i = 1; i <= 36; ++i) {
			texture = Director::getInstance()->getTextureCache()->addImage(res["result_" + ToString(i)]);
			rect.size = texture->getContentSize();
			frame = SpriteFrame::createWithTexture(texture, rect);

			this->aResultHeadFrame.pushBack(frame);
			this->aResultTailFrame.pushBack(frame);
		}
		for (int i = 1; i <= 10; ++i) {
			texture = Director::getInstance()->getTextureCache()->addImage(res["result_head_" + ToString(i)]);
			rect.size = texture->getContentSize();
			frame = SpriteFrame::createWithTexture(texture, rect);

			this->aResultHeadFrame.pushBack(frame);

			texture = Director::getInstance()->getTextureCache()->addImage(res["result_tail_" + ToString(i)]);
			rect.size = texture->getContentSize();
			frame = SpriteFrame::createWithTexture(texture, rect);

			this->aResultTailFrame.pushBack(frame);
		}
	}
	void CDoubleUpRE::restore()
	{
		this->oGame->getMain()->removeBonusHistory();
	}
	void CDoubleUpRE::createButtonCoin(int index, const std::string & frameName, const cocos2d::Vec2 & pos)
	{
		auto prefixName = "doubleup_coin-" + frameName;
		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			prefixName + "-normal",
			nullptr,
			[this, index]() {
			this->btnGamblingClicked(index);
		}
		);
		oBtn->setScaleEvent(0.9f, 1.0f);
		oBtn->setCustomTouchZone(Rect(Vec2(0, -70), oBtn->getContentSize() + Size(0, 70)));
		oBtn->setImageEvent(prefixName + "-hover", prefixName + "-disabled");
		oBtn->setPosition(pos);
		this->oInfo->addChild(oBtn);

		this->aBtn[index] = oBtn;
	}
	bool CDoubleUpRE::btnGamblingClicked(int iIndex)
	{
		if (CBonusBase::btnGamblingClicked(iIndex)) {
			if (iIndex != 0) {
				for (int i = 1, size = this->aBtn.size(); i < size; ++i) {
					if (i == iIndex) {
						this->aBtn[i]->changeSpriteFrameToTouching();
					}
				}
			}
			return true;
		}
	}
	void CDoubleUpRE::playResultAnimation(bool isHead)
	{
		this->oBgResult->setVisible(true);
		this->oBg->setVisible(false);
		this->oInfo->setVisible(false);

		auto animation = Animation::createWithSpriteFrames(isHead ? this->aResultHeadFrame : this->aResultTailFrame);
		animation->setDelayPerUnit(1.0f / 18);
		this->oBgResult->runAction(Sequence::create(
			Animate::create(animation),
			CallFunc::create([this]() {
			if (!this->bFinish) {
				//user win
				Manager4Sound::getInstance()->playDoubleUpWin();
			}
			else {
				//user lose
				Manager4Sound::getInstance()->playDoubleUpLose();
			}
		}),
			DelayTime::create(2.5f),
			CallFunc::create([this]() {
			this->oCurrentWinTxt->setString(UtilFunction::FormatWithCommas(this->iTotWin)); 
			this->oPotentialWinTxt->setString(UtilFunction::FormatWithCommas(2 * this->iTotWin));

			this->oInfo->setVisible(true);

			if (this->bFinish == 1) {
				this->showFinalWin(0);
			}
			else {
				this->resetBonus();
				this->updateTotalWinText();
			}
		}), NULL));
	}
	void CDoubleUpRE::updateTotalWinText()
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
	void CDoubleUpRE::showResult(bool bFinish, int iResult, double iTotWin, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, iResult, iTotWin);
		this->disableAllBtn();

		if (iResult == 1) {
			this->playResultAnimation(true);
		}
		else if (iResult == 2) {
			this->playResultAnimation(false);
		}
		else if (bFinish) {
			this->scheduleOnce(schedule_selector(CDoubleUpRE::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}
	}
	void CDoubleUpRE::resetBonus()
	{
		CBonusBase::resetBonus();
		this->oBg->setVisible(true);
		this->oBgResult->setVisible(false);
		this->oBgResult->setSpriteFrame(this->aResultHeadFrame.at(0));
	}
}
