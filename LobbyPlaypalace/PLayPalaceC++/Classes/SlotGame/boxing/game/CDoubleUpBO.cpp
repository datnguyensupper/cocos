#include "CDoubleUpBO.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"
#include <algorithm>
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CDoubleUpBO::CDoubleUpBO(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iGameType = GAME_TYPE::DOUBLE_UP;
		this->iBonusType = BONUS_TYPE::BONUS_DOUBLE_UP;

		for (auto res : GameConstant::getInstance()->getResources().doubleUp) {
			this->aResources.push_back(res.second);
		}
	}
	CDoubleUpBO::~CDoubleUpBO()
	{

	}
	bool CDoubleUpBO::init()
	{
		if (!CBonusBase::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		auto oBg = Helper4Sprite::createOptimizeSprite(res.doubleUp["bg"]);
		GameUtils::centerNode(oBg);
		this->addChild(oBg);

		this->aBtn.resize(3);
		this->aPickCard.resize(4);

		//Create Choose Option Button
		auto createChooseButton = [this](int iIndex, 
			const std::string& framePrefixName,
			const Vec2& pos) {
			auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(framePrefixName + "-on",
				nullptr,
				[this, iIndex]() {
				this->btnGamblingClicked(iIndex);
			}
				);
			oBtn->setScaleEvent(0.9f, 1.0f);
			oBtn->setPosition(pos);
			oBtn->setImageEvent("", framePrefixName + "-off");
			this->addChild(oBtn);

			return oBtn;
		};
		this->aBtn[0] = createChooseButton(0, "doubleup_collect", Vec2(CSettings::CANVAS_WIDTH / 2 - 335, 120));
		this->aBtn[1] = createChooseButton(1, "doubleup_doubleHalf", Vec2(CSettings::CANVAS_WIDTH / 2, 120));
		this->aBtn[2] = createChooseButton(2, "doubleup_double", Vec2(CSettings::CANVAS_WIDTH / 2 + 335, 120));

		//Create Dealer card

		this->oDealerCard = Sprite::createWithSpriteFrameName("doubleup_Card2");
		this->oDealerCard->setPosition(335, 445);
		this->oDealerCard->setScale(1.2f);
		this->oDealerCard->setRotation(20);
		this->addChild(this->oDealerCard);

		auto dealerText = Sprite::createWithSpriteFrameName("doubleup_Dealer");
		dealerText->setScale(0.5);
		dealerText->setPosition(this->oDealerCard->getPosition() + Vec2(-100, -125) * CSettings::SCALE_VALUE_TO_1920);
		dealerText->setRotation(28);
		this->addChild(dealerText);

		//Create Card to pick
		createCardButton(0, 0, 18, Vec2(670, 475) * CSettings::SCALE_VALUE_TO_1920, Vec2(-50, -150) * CSettings::SCALE_VALUE_TO_1920);
		createCardButton(1, 13, 0, Vec2(960, 450) * CSettings::SCALE_VALUE_TO_1920, Vec2(0, -150) * CSettings::SCALE_VALUE_TO_1920);
		createCardButton(2, 16, -15, Vec2(1221, 475) * CSettings::SCALE_VALUE_TO_1920, Vec2(50, -150) * CSettings::SCALE_VALUE_TO_1920);
		createCardButton(3, -16, -28, Vec2(1480, 535) * CSettings::SCALE_VALUE_TO_1920, Vec2(100, -125) * CSettings::SCALE_VALUE_TO_1920);

		this->oPlayerText = Sprite::createWithSpriteFrameName("doubleup_Player");
		this->oPlayerText->setVisible(false);
		this->oPlayerText->setScale(0.5);
		this->addChild(this->oPlayerText);

		//Create Text Header
		this->oHeaderRule = Sprite::createWithSpriteFrameName("doubleup_choose_option");
		this->oHeaderRule->setPosition(CSettings::CANVAS_WIDTH / 2, 740);
		this->addChild(this->oHeaderRule);

		this->oWin = Label::createWithTTF(res.fontConfigs["double_up_label"], "0");
		this->oWin->setAnchorPoint(Vec2(0, 0.5f));
		this->oWin->setPosition(CSettings::CANVAS_WIDTH / 2 + 45, 740);
		this->oWin->setTextColor(Color4B(194, 194, 194, 255));
		this->oWin->enableOutline(Color4B(1, 0, 0, 255));
		this->oWin->setVisible(false);
		this->addChild(this->oWin);

		this->oBank = Label::createWithTTF(res.fontConfigs["double_up_label"], "0");
		this->oBank->setPosition(475, 645);
		this->oBank->setTextColor(Color4B::WHITE);
		this->oBank->enableOutline(Color4B::BLACK);
		this->addChild(this->oBank);

		this->oDoubleHalf = Label::createWithTTF(res.fontConfigs["double_up_label"], "0");
		this->oDoubleHalf->setPosition(762, 645);
		this->oDoubleHalf->setTextColor(Color4B::WHITE);
		this->oDoubleHalf->enableOutline(Color4B::BLACK);
		this->addChild(this->oDoubleHalf);

		this->oDouble = Label::createWithTTF(res.fontConfigs["double_up_label"], "0");
		this->oDouble->setPosition(1056, 645);
		this->oDouble->setTextColor(Color4B::WHITE);
		this->oDouble->enableOutline(Color4B::BLACK);
		this->addChild(this->oDouble);

		this->oBet = Label::createWithTTF(res.fontConfigs["double_up_label"], "0");
		this->oBet->setPosition(835, 788);
		this->oBet->setTextColor(Color4B::WHITE);
		this->oBet->enableOutline(Color4B::BLACK);
		this->addChild(this->oBet);

		this->disableAllPickBtn();

		return true;
	}
	void CDoubleUpBO::onBonusEntered()
	{
		CBonusBase::onBonusEntered();
		this->updateTotalWinText(0, this->iTotWin, 0, 0);
	}
	void CDoubleUpBO::restore()
	{
		auto aHistory = this->oGame->getMain()->getBonusHistory();

		if (!aHistory || aHistory->bonus_step <= 0) {
			return;
		}

		for (auto i = 0; i < aHistory->history.size(); i++) {
			this->showCardToPick(aHistory->finish,
				aHistory->history,
				*(ObjectCardDoubleUpBO*)aHistory->oInfo);
		}

		this->oGame->getMain()->removeBonusHistory();
	}

	bool CDoubleUpBO::btnCardClicked(int iIndex)
	{
		this->disableAllPickBtn();
		Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["double_up_card_selected"]);
		this->oGame->chooseItem(iIndex);
		return true;
	}

	void CDoubleUpBO::disableAllPickBtn()
	{
		for (auto card : this->aPickCard) {
			card.btn->setTouchEnabled(false);
		}
	}

	void CDoubleUpBO::enableAllPickBtn()
	{
		for (auto card : this->aPickCard) {
			card.btn->setTouchEnabled(true);
		}
	}

	void CDoubleUpBO::createCardButton(int index,
		float angleSprite,
		float angleText,
		const cocos2d::Vec2 & pos,
		const cocos2d::Vec2& posText)
	{
		auto btn = CSpriteButton::createButtonWithSpriteFrameName(StringUtils::format("doubleup_Card%i", index + 2),
			nullptr,
			[this, index]() {
			this->btnCardClicked(index + 1);
		}
			);
		btn->setScale(1.2f);
		btn->setScaleEvent(1.1f, 1.2f);
		btn->setPosition(pos);
		this->addChild(btn);

		ObjectCardUI card;
		card.btn = btn;
		card.angleSprite = angleSprite;
		card.angleText = angleText;
		card.posText = posText;

		this->aPickCard[index] = card;
	}
	void CDoubleUpBO::updateTotalWinText(int select, double bank, double bet, double winPot)
	{
		//base on which option user select (collect, double, double half) we show right info
		switch (select) {
		case 0:
			this->oBank->setString(UtilFunction::FormatWithCommas(bank));
			this->oBet->setString("");
			this->oDouble->setString(UtilFunction::FormatWithCommas(bank * 2.0f));
			this->oDoubleHalf->setString(UtilFunction::FormatWithCommas(bank * 1.5f));
			break;
		case 1:
			this->oBank->setString(UtilFunction::FormatWithCommas(bank));
			this->oBet->setString(UtilFunction::FormatWithCommas(bet));
			this->oDouble->setString("");
			this->oDoubleHalf->setString(UtilFunction::FormatWithCommas(winPot));
			break;
		case 2:
			this->oBank->setString(UtilFunction::FormatWithCommas(bank));
			this->oBet->setString(UtilFunction::FormatWithCommas(bet));
			this->oDouble->setString(UtilFunction::FormatWithCommas(winPot));
			this->oDoubleHalf->setString("");
			break;
		}
	}
	int const CDoubleUpBO::getCardID(int suit, int value)
	{
		//52 cards' texture are store in a spritesheet with frameName is from "1" ... "52"
		//"1"..."13": club
		//"14"..."26": diamond
		//"27"..."39": heart
		//"40"..."52": spade
		//card suit.
		// 1 heart
		// 2 diamond
		// 3 club
		// 4 spade
		// card value
		// 2-10 : card with number 2-10
		// 11 : jack
		// 12 : queen
		// 13 : king
		// 14 : ace
		int iFirstSuitCard = 0;
		switch (suit) {
		case 1: iFirstSuitCard = 27; break;
		case 2: iFirstSuitCard = 14; break;
		case 3: iFirstSuitCard = 1; break;
		case 4: iFirstSuitCard = 40; break;
		}
		//we get the right frameName for card
		return iFirstSuitCard + value - 2;
	}
	void CDoubleUpBO::showCard(int index, int cardID, int opacity, bool isDealer)
	{
		//Notice: dont play animation flick card if this card is show when we restore the last game
		if (isDealer) {
			//if this is dealer's card
			this->oDealerCard->setScale(1.2f);
			if (!this->oGame->getMain()->getBonusHistory()) {
				this->oDealerCard->runAction(Sequence::create(
					ScaleTo::create(0.2f, 1.5f),
					CallFunc::create([this, cardID]() {
					this->oDealerCard->setSpriteFrame("doubleup_" + ToString(cardID));
					this->oDealerCard->setRotation(0);
				}), ScaleTo::create(0.1f, 1.2f), 
					CallFunc::create([this, cardID]() {
					//enable pick card after finishing flick dealer card
					this->enableAllPickBtn();
				}), NULL
					));
			}
			else {
				this->oDealerCard->setSpriteFrame("doubleup_" + ToString(cardID));
				this->oDealerCard->setRotation(0);
				//enable pick card after finishing flick dealer card
				this->enableAllPickBtn();
			}
		}
		else {
			auto show = [this, index, cardID, opacity]() {
				auto card = this->aPickCard[index - 1];
				card.btn->setSpriteFrame("doubleup_" + ToString(cardID));
				card.btn->setRotation(card.angleSprite);
				card.btn->setOpacity(opacity);
				//if this opacity is 255 === this card is selected by user -> show player text below this card
				if (opacity == 255) {
					this->oPlayerText->setPosition(card.btn->getPosition() + card.posText);
					this->oPlayerText->setRotation(card.angleText);
					this->oPlayerText->setVisible(true);
				}
			};
			if (!this->oGame->getMain()->getBonusHistory()) {
				auto btn = this->aPickCard[index - 1].btn;
				btn->setScale(1.2f);
				btn->runAction(Sequence::create(
					ScaleTo::create(0.2f, 1.5f),
					CallFunc::create([this, cardID, btn, show]() {
					show();
				}), ScaleTo::create(0.1f, 1.2f), NULL
					));
			}
			else {
				show();
			}
		}
	}
	void CDoubleUpBO::showOtherCard(const std::vector<ObjectCardDoubleUpBO>& aCard, int iSelect)
	{
		int dealderCardID = this->getCardID(aCard[0].suit, aCard[0].value);
		int playerCardID = this->getCardID(aCard[iSelect].suit, aCard[iSelect].value);

		std::vector<int> aCardNumber{
			1 ,2 ,3 ,4 ,5 ,6 ,7 ,8 ,9 ,10,11,12,
			13 ,14 ,15 ,16 ,17 ,18 ,19 ,20 ,21 ,22 ,23,24,25,
			26, 27 ,28 ,29 ,30 ,31 ,32 ,33 ,34 ,35 ,36,37,38,
			39, 40 ,41 ,42 ,43 ,44 ,45 ,46 ,47 ,48 ,49,50,51,52
		};
		std::random_shuffle(aCardNumber.begin(), aCardNumber.end());

		//Show cards that not selected from list
		for (auto i = 1, k = 0; i < aCard.size(); i++, ++k) {
			if (i != iSelect) {
				int id = aCardNumber[k];
				while (id == dealderCardID || id == playerCardID) {
					id = aCardNumber[++k];
				}
				this->showCard(aCard[i].id, id, 100);
			}
		}
		if (this->bFinish) {
			//if user lose
			this->scheduleOnce(schedule_selector(CDoubleUpBO::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}
		else {
			//if user win
			Director::getInstance()->getScheduler()->schedule([this, aCard, iSelect](float dt) {
				this->updateTotalWinText(0, this->iTotWin, 0, 0);
				this->resetBonus();
			}, this, 0, 0, CSettings::TIMER_DELAY_SHOW_WIN_BONUS, false, "CDoubleUpBO_reset");
		}
	}
	void CDoubleUpBO::showCardToPick(bool bFinish, const std::vector<ObjectBonus>& aInfo, const ObjectCardDoubleUpBO & cardDealer)
	{
		this->bFinish = bFinish;
		if (this->bFinish) {
			this->disableAllBtn();
			this->disableAllPickBtn();
			//if user select collect
			this->scheduleOnce(schedule_selector(CDoubleUpBO::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}
		else {
			this->disableAllBtn();
			this->enableAllPickBtn();
			//if user select to continue to play
			this->oHeaderRule->setSpriteFrame("doubleup_pick_card");
			
			auto info = aInfo[0];
			this->updateTotalWinText(info.select, info.win, info.bet, info.win_pot);

			this->showCard(cardDealer.id, this->getCardID(cardDealer.suit, cardDealer.value), 255, true);
		}
	}
	void CDoubleUpBO::showResult(bool bFinish, const std::vector<ObjectCardDoubleUpBO>& aCard, double iBank, int iSelect, double iTotWin)
	{
		this->bFinish = bFinish;
		this->iTotWin = iBank;
		this->showCard(aCard[iSelect].id, this->getCardID(aCard[iSelect].suit, aCard[iSelect].value), 255);

		Director::getInstance()->getScheduler()->schedule([this, aCard, iSelect](float dt) {
			this->showOtherCard(aCard, iSelect);
		}, this, 0, 0, 0.5f, false, "CDoubleUpBO_showResult");

		if (this->bFinish) {
			this->oHeaderRule->setSpriteFrame("doubleup_dealer_win");
			Manager4Sound::getInstance()->playDoubleUpLose();
		}
		else {
			this->oHeaderRule->setSpriteFrame("doubleup_you_win");
			//Show win text
			this->oWin->setString(UtilFunction::FormatWithCommas(iTotWin));
			this->oWin->setVisible(true);
			Manager4Sound::getInstance()->playDoubleUpWin();
		}
	}
	void CDoubleUpBO::resetBonus()
	{
		this->enableAllBtn();
		this->bButtonClicked = false;
		this->oHeaderRule->setSpriteFrame("doubleup_choose_option");
		for (int i = 0, size = this->aPickCard.size(); i < size; ++i) {
			auto btn = this->aPickCard[i].btn;
			btn->setSpriteFrame(StringUtils::format("doubleup_Card%i", i + 2));
			btn->setTouchEnabled(false);
			btn->setOpacity(255);
			btn->setRotation(0);
		}
		this->oPlayerText->setVisible(false);
		this->oWin->setVisible(false);
		this->oDealerCard->setSpriteFrame("doubleup_Card2");
	}
}
