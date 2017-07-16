//
// Created by Duy on 5/13/2017.
//
#include "ScratchCardPopup.h"
#include "SlotGame/base/utils/GameUtils.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Info/AdditionalInfo.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/NetworkManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Custom/Common/CScratchSprite.h"
#include "Helper/Helper4Scene.h"

USING_NS_CC;
using namespace std;

bool ScratchCardPopup::init()
{
	if (!BasePopup::init()) return false;

	//UI TEST

	auto bg = Sprite::create(PNG_FRIEND_POPUP_BACKGROUND);
	bg->setPosition(origin + visibleSize / 2);
	this->addChild(bg);

	this->scratchUI = ScratchUI::create();
	this->scratchUI->setPosition(bg->getPosition());
	this->scratchUI->getScratchSprite()->setOnScratchListener(CC_CALLBACK_1(ScratchCardPopup::onScratchListener, this));
	this->addChild(this->scratchUI);

	this->txtRemaining = LabelAutoSize::createWithTTF("0", FONT_PassionOne_Regular, 50);
	this->txtRemaining->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width / 2.5f, -bg->getContentSize().height / 2.5f));
	this->addChild(this->txtRemaining);

	this->txtWin = LabelAutoSize::createWithTTF("0", FONT_PassionOne_Regular, 50);
	this->txtWin->setPosition(bg->getPosition() + Vec2(0, -bg->getContentSize().height / 2.5f));
	this->addChild(this->txtWin);

	closeBtn = this->createCloseButton();
	closeBtn->setPosition(bg->getPosition() + bg->getContentSize() / 2.2f);
	this->addChild(closeBtn);

	return true;
}

void ScratchCardPopup::hide()
{
	this->scratchUI->reset();
	BasePopup::hide();
}

void ScratchCardPopup::prepareAndShow(cocos2d::Node * parent)
{
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(parent);
	InfoManager::getInstance()->reloadAdditionalInfo([this, parent](bool isSuccess, AdditionalInfo* result) {
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		if (isSuccess) {
			this->info = result->scratchCardInfo;

			this->stopAllActions();
			this->reloadUI();

			BasePopup::showWithQueue(parent);
		}
	});
}

void ScratchCardPopup::reloadUI()
{
	this->txtRemaining->setString("x " + ToString(this->info->remainingCards));

	std::string sValues = this->info->nextInfo.empty() ? this->info->currentInfo : this->info->nextInfo;

	std::vector<std::string> aValue = GameSlot::GameUtils::splitString(sValues, ',');
	this->scratchUI->reload(aValue);
}

void ScratchCardPopup::onScratchListener(float percent)
{
	if (percent >= 90) {
		this->scratchUI->scratchAll();
		closeBtn->setVisible(false);

		auto fail = [this](std::string result) {

			closeBtn->setVisible(true);
		};
		NetworkManager::getInstance()->scratchCard([this](int coreResultCode,
			rapidjson::Value&responseAsDocument,
			std::string responseAsString) {
			if (coreResultCode == RESULT_CODE_VALID) {
				info = InfoManager::getInstance()->getAdditionalInfo()->scratchCardInfo;
				info->updateInfoByValue(responseAsDocument);
				AnimationCoinCrown::create(
					Helper4Scene::getRunningScene(),
					this->scratchUI->getPosition(),
					info->coinReward
				);

				PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp();

				//TEST
				this->txtWin->setString("Won: " + UtilFunction::FormatWithCommas(info->coinReward));
				this->runAction(Sequence::createWithTwoActions(
					DelayTime::create(3.0f), 
					CallFunc::create([this]() {
					this->reloadUI();
				})));
			}
			closeBtn->setVisible(true);
		}, fail, fail);
	}
}

bool ScratchUI::init()
{
	if (!Node::init()) return false;
	this->setCascadeOpacityEnabled(true);

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_MAGIC_ITEM);
	bg->setContentSize(Size(500, 500));
	this->addChild(bg);

	Vec2 offset = Vec2(bg->getPosition() + Vec2(-bg->getContentSize().width / 3.0f, bg->getContentSize().height / 3.0f));
	float xDistance = bg->getContentSize().width / 3.0f;
	float yDistance = bg->getContentSize().height / 3.0f;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			auto card = LabelAutoSize::createWithTTF("", FONT_PassionOne_Regular, 150);
			card->setPosition(offset + Vec2(xDistance * j, -yDistance * i));
			cards.push_back(card);
			this->addChild(card);
		}
	}

	auto mask = Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_MAGIC_ITEM);
	mask->setContentSize(Size(500, 500));
	mask->setColor(Color3B(100, 100, 100));

	this->scratchSprite = CScratchSprite::createScratchSprite(mask);
	this->addChild(this->scratchSprite);

	return true;
}

void ScratchUI::reset()
{
	this->scratchSprite->setCascadeOpacityEnabled(true);
	for (auto card : cards) {
		card->setString("");
	}
}

void ScratchUI::scratchAll()
{
	this->scratchSprite->scratchAll();
}

void ScratchUI::reload(const std::vector<std::string>& values)
{
	this->scratchSprite->setCascadeOpacityEnabled(false);

	for (int i = 0, size = values.size(); i < size; ++i) {
		cards[i]->setString(values[i]);
	}
	this->scratchSprite->reset();
	if (values.size() == 0) {
		this->scratchSprite->setEnabled(false);
	}
}
