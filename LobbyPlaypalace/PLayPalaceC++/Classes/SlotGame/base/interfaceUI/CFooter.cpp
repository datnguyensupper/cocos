#include "CFooter.h"
#include "SlotGame/base/game/CGameBase.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/MissingPopup.h"
#include "Views/Popup/GameSlotInfoPopup.h"
#include "Views/Tutorial/Tutorial.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include <algorithm>
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	bool CFooter::isLevelAllowToChangePayLine()
	{
		auto info = InfoManager::getInstance();
		return info->getUserInfo()->level + 1 >= info->getUnlockFeatureByLevelConfig().choosePayLine;
	}
	CFooter::CFooter(CGameBase* oGame):Node(),
		oGame(oGame)
	{
		this->autorelease();
		auto gameID = InfoManager::getInstance()->getGameIDByName(this->oGame->getMain()->getGameName());
		this->aPayLineConfig = InfoManager::getInstance()->getMapListPaylineConfig().at(gameID);

		for (auto config : aPayLineConfig) {
			unsigned bet = config.maxBetPerLine;
			if (std::find(this->aBet.begin(), this->aBet.end(), bet) == this->aBet.end()) {
				aBet.push_back(bet);
			}
		}
	}

	bool CFooter::init()
	{
		if (!Node::init()) return false;

		auto betAdjustNode = this->createAdjustGroup("Total Bet", CC_CALLBACK_1(CFooter::onAdjustBet, this));
		betAdjustNode->setPosition(85, 0);
		betAdjustNode->setName("bet");
		this->oBetAdd = (CSpriteButton*)betAdjustNode->getChildByName("btnAdd");
		this->oBetMinus = (CSpriteButton*)betAdjustNode->getChildByName("btnMinus");
		this->oBetText = (Label*)betAdjustNode->getChildByName("infoText");

		this->addChild(betAdjustNode);

		auto paylineAdjustNode = this->createAdjustGroup("Payline", CC_CALLBACK_1(CFooter::onAdjustPayLine, this));
		paylineAdjustNode->setName("payline");
		paylineAdjustNode->setPosition(-415, 0);

		this->oPaylineAdd = (CSpriteButton*)paylineAdjustNode->getChildByName("btnAdd");
		this->oPaylineMinus = (CSpriteButton*)paylineAdjustNode->getChildByName("btnMinus");
		this->oPayLineText = (Label*)paylineAdjustNode->getChildByName("infoText");

		this->addChild(paylineAdjustNode);

		auto winNode = this->createAdjustGroup("Win", nullptr);
		winNode->setPosition(585, 0);
		this->oWinText = (Label*)winNode->getChildByName("infoText");
		this->addChild(winNode);

		//Init some value when go to game
		auto bet = this->oGame->getMain()->getBet();
		this->iCurBetIndex = std::find(this->aBet.begin(), this->aBet.end(), bet) - this->aBet.begin();
		this->reloadBet(bet);

		auto payLine = this->oGame->getMain()->getLine();
		if (!this->isLevelAllowToChangePayLine()) {
			payLine = this->getMinPayLine();
		}
		this->reloadPayline(payLine);


		return true;
	}

	void CFooter::refreshWin(const double& iWin, bool bAnimation, const std::function<void()> & cb)
	{
		if (!this->oWinText) return;

		this->oWinText->stopAllActions();
		this->oWinText->setScale(1.0f);
		this->oWinText->setString(UtilFunction::FormatWithCommas(iWin));
		if (bAnimation) {
			this->oWinText->runAction(Sequence::create(
				EaseElasticIn::create(ScaleTo::create(1.0f, 2.0f)),
				DelayTime::create(0.5f),
				EaseElasticOut::create(ScaleTo::create(1.0f, 1.0f)),
				CallFunc::create([cb]() {
				if (cb) {
					cb();
				}
			}), NULL));
		}
		else {
			if (cb) {
				cb();
			}
		}
	}

	void CFooter::onAdjustBet(int value)
	{
		if (!this->checkCanChangeBet()) return;

		auto index = this->iCurBetIndex + value;
		if (index < 0 || index > this->aBet.size()) return;
		this->reloadBetByIndex(index);
	}

	void CFooter::onAdjustPayLine(int value)
	{
		if (!this->checkCanChangeBet()) return;
		if (!this->isLevelAllowToChangePayLine()) {
			//test
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				this->oGame->getMain()->getScene(),
				"More level",
				"You need to reach level " +
				ToString(InfoManager::getInstance()->getUnlockFeatureByLevelConfig().choosePayLine)
				+ " to unlock this feature."
			);
			return;
		}
		auto iLine = this->iCurPayLine + value;
		this->reloadPayline(iLine);
	}

	void CFooter::reloadBetByIndex(int index)
	{
		if (!this->reloadBet(this->aBet[index])) return;
		this->iCurBetIndex = index;
	}

	bool CFooter::reloadBet(unsigned iBet, bool force)
	{
		auto maxBet = this->getMaxBet();
		auto iTotBet = iBet * this->oGame->getMain()->getLine();
		if (!force) {
			if (iBet > maxBet) return false;
			
			//2017-05-04: Kiet: check and show missing coin popup
			auto currentCoin = PopupManager::getInstance()->getHeaderLobbyLayout()->getCoinInHeaderUI();
			if (iTotBet > currentCoin
				&& !Tutorial::getInstance())
			{
				PopupManager::getInstance()->getMissingPopup()->prepareAndShow(
					this->oGame->getMain()->getScene(),
					ppEnum::PPCurrency::COIN_CURRENCY,
					iTotBet - currentCoin);
				return false;
			}
		}

		this->setEnableBtn(this->oBetAdd, true);
		this->setEnableBtn(this->oBetMinus, true);
		if (iBet >= maxBet) {
			this->setEnableBtn(this->oBetAdd, false);
		}
		if (iBet == this->aBet[0]) {
			this->setEnableBtn(this->oBetMinus, false);
		}

		this->oGame->getMain()->setBet(iBet);
		this->oGame->getMain()->setTotalBet(iTotBet);
		this->oBetText->setString(UtilFunction::FormatWithCommas(iTotBet));

		return true;
	}

	bool CFooter::reloadPayline(unsigned iPayLine, bool force)
	{
		auto maxPayLine = this->getMaxPayLine();
		if (!force) {
			if (iPayLine < 1) return false;

			if (iPayLine > maxPayLine) iPayLine = maxPayLine;

			//2017-05-04: Kiet: check and show missing coin popup
			auto iBet = this->aBet[this->iCurBetIndex];
			auto iTotBet = iBet * iPayLine;
			auto currentCoin = PopupManager::getInstance()->getHeaderLobbyLayout()->getCoinInHeaderUI();
			if (iTotBet > currentCoin
				&& !Tutorial::getInstance())
			{
				PopupManager::getInstance()->getMissingPopup()->prepareAndShow(
					this->oGame->getMain()->getScene(),
					ppEnum::PPCurrency::COIN_CURRENCY,
					iTotBet - currentCoin);
				return false;
			}
		}

		this->setEnableBtn(this->oPaylineAdd, true);
		this->setEnableBtn(this->oPaylineMinus, true);
		if (iPayLine >= maxPayLine) {
			this->setEnableBtn(this->oPaylineAdd, false);
		}
		if (iPayLine <= 1) {
			this->setEnableBtn(this->oPaylineMinus, false);
		}

		this->iCurPayLine = iPayLine;
		this->oGame->getMain()->setLine(iPayLine);
		this->oPayLineText->setString(UtilFunction::FormatWithCommas(iPayLine));

		auto iBet = this->aBet[this->iCurBetIndex];
		auto iTotBet = iBet * this->oGame->getMain()->getLine();
		this->oGame->getMain()->setBet(iBet);
		this->oGame->getMain()->setTotalBet(iTotBet);
		this->oBetText->setString(UtilFunction::FormatWithCommas(iTotBet));

		return true;
	}

	void CFooter::setAdjustEnabled(bool isEnabled)
	{
		if (isEnabled) {
			this->reloadBetByIndex(this->iCurBetIndex);
			this->reloadPayline(this->iCurPayLine);
		}
		else {
			this->setEnableBtn(this->oBetAdd, isEnabled);
			this->setEnableBtn(this->oBetMinus, isEnabled);
			this->setEnableBtn(this->oPaylineAdd, isEnabled);
			this->setEnableBtn(this->oPaylineMinus, isEnabled);
		}
	}

	cocos2d::Node * CFooter::createAdjustGroup(const std::string& labelText, const std::function<void(int)>& onAdjust)
	{
		auto parent = Node::create();

		auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_BET_BACKGROUND);
		bg->setName("bg");
		parent->addChild(bg);

		auto label = Label::createWithTTF(labelText, FONT_PassionOne_Regular, 45, Size::ZERO, TextHAlignment::CENTER);
		label->setPositionX(-(bg->getContentSize().width + label->getContentSize().width) / 2 - 15);
		parent->addChild(label);

		if (onAdjust) {
			float extendTouch = 50;
			auto btnAdd = CSpriteButton::createButtonWithSpriteFrameName(PNG_FRAME_ADDITION_BUTTON, nullptr, [this, onAdjust]() {
				onAdjust(1);
			});
			btnAdd->setCustomTouchZone(Rect(-extendTouch/2, -extendTouch / 2,btnAdd->getContentSize().width + extendTouch, btnAdd->getContentSize().height+extendTouch));
			btnAdd->setName("btnAdd");
			btnAdd->setScaleEvent(0.9f, 1.0f);
			btnAdd->setPosition((-btnAdd->getContentSize().width + bg->getContentSize().width) / 2, 0);
			parent->addChild(btnAdd);

			auto btnMinus = CSpriteButton::createButtonWithSpriteFrameName(PNG_FRAME_MINUS_BUTTON, nullptr, [this, onAdjust]() {
				onAdjust(-1);
			});
			btnMinus->setCustomTouchZone(Rect(-extendTouch / 2, -extendTouch / 2, btnAdd->getContentSize().width + extendTouch, btnAdd->getContentSize().height + extendTouch));
			btnMinus->setName("btnMinus");
			btnMinus->setScaleEvent(0.9f, 1.0f);
			btnMinus->setPosition((btnMinus->getContentSize().width - bg->getContentSize().width) / 2, 0);
			parent->addChild(btnMinus);
		}

		auto infoText = Label::createWithTTF("0", FONT_PassionOne_Regular, 45, Size::ZERO, TextHAlignment::CENTER);
		infoText->enableWrap(true);
		infoText->setName("infoText");
		parent->addChild(infoText);

		return parent;
	}
	bool CFooter::checkCanChangeBet()
	{
		return !(
			this->oGame->isAutoSpin() ||
			this->oGame->getCurrentState() == GAME_STATE::GAME_SPINING ||
			this->oGame->getCurrentState() == GAME_STATE::GAME_SHOW_WIN ||
			this->oGame->getCurrentState() == GAME_STATE::GAME_BONUS
			);
	}
	void CFooter::setEnableBtn(CSpriteButton * oBtn, bool isEnabled)
	{
		oBtn->setTouchEnabled(isEnabled);
		oBtn->setColor(isEnabled ? Color3B::WHITE : Color3B(125, 125, 125));

		PopupManager::getInstance()->getInfoPopup()->getBetTab()->setEnableBtn(oBtn->getParent()->getName() == "bet" ? BetType::Bet : BetType::PayLine, oBtn->getName(), isEnabled) ;
	}
	PayLineConfig * CFooter::getConfigByLevel(int iLevel)
	{
		if (!this->currentConfig || this->currentConfig->level != iLevel) {
			PayLineConfig configByLevel;
			for (auto config : aPayLineConfig) {
				if (config.level > iLevel) {
					break;
				}
				configByLevel = config;
			}
			this->currentConfig = &configByLevel;
		}
		return this->currentConfig;
	}
	unsigned CFooter::getMaxBet()
	{
		auto config = this->getConfigByLevel(InfoManager::getInstance()->getUserInfo()->level + 1);
		return config->maxBetPerLine;
	}
	unsigned CFooter::getMinPayLine()
	{
		for (auto config : aPayLineConfig) {
			if (config.maxPayLine != 0) {
				return config.maxBetPerLine;
			}
		}
		return 1;
	}
	unsigned CFooter::getMaxPayLine()
	{
		auto config = this->getConfigByLevel(InfoManager::getInstance()->getUserInfo()->level + 1);
		return config->maxPayLine;
	}
}