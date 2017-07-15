#include "GameSlotInfoPopup.h"
#include "Constant/Defination.h"
#include "SlotGame/base/game/CMainBase.h"
#include "Custom/Common/CRadioButton.h"
#include "SlotGame/base/game/CMainBase.h"
#include "SlotGame/base/game/CGameBase.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;
using namespace GameSlot;

bool GameSlotInfoPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	// preload img info
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_INFO);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_INFO_POPUP_BACKGROUND);
	//bg->setScale(1.25f);
	bg->setPosition(origin + visibleSize / 2);
	this->addChild(bg);

	auto radioButtonGroup = ui::RadioButtonGroup::create();
	this->addChild(radioButtonGroup);

	btnBet = CRadioButton::create(PNG_FRAME_INFO_TOGGLE_OFF, PNG_FRAME_TRANSPARENT, PNG_FRAME_INFO_TOGGLE_ON, PNG_FRAME_TRANSPARENT, PNG_FRAME_TRANSPARENT,ui::Widget::TextureResType::PLIST);
	btnBet->setName("Bet");
	btnBet->setZoomScale(0);
	btnBet->addEventListener(CC_CALLBACK_2(GameSlotInfoPopup::onChangeTab, this));
	btnBet->setTitleRenderer("Bet", FONT_PassionOne_Regular, 65, Color4B(234, 202, 242, 255), Color4B(71, 31, 84, 255));
	btnBet->setPosition(bg->getPosition() + Vec2(-275, 205));
	radioButtonGroup->addRadioButton(btnBet);
	this->addChild(btnBet);

	btnInfo = CRadioButton::create(PNG_FRAME_INFO_TOGGLE_OFF, PNG_FRAME_TRANSPARENT, PNG_FRAME_INFO_TOGGLE_ON, PNG_FRAME_TRANSPARENT, PNG_FRAME_TRANSPARENT,ui::Widget::TextureResType::PLIST);
	btnInfo->setName("Info");
	btnInfo->setZoomScale(0);
	btnInfo->addEventListener(CC_CALLBACK_2(GameSlotInfoPopup::onChangeTab, this));
	btnInfo->setTitleRenderer("Info", FONT_PassionOne_Regular, 65, Color4B(234, 202, 242, 255), Color4B(71, 31, 84, 255));
	btnInfo->setPosition(bg->getPosition() + Vec2(275, 205));
	radioButtonGroup->addRadioButton(btnInfo);
	this->addChild(btnInfo);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(Vec2(
		bg->getPositionX() + bg->getContentSize().width / 2 * bg->getScaleX() - 25,
		bg->getPositionY() + bg->getContentSize().height / 2 * bg->getScaleY() - 25
	));
	this->addChild(closeBtn);

	this->initBetTab();
	this->initInfoTab();

	return true;
}

void GameSlotInfoPopup::initBetTab()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	betTab = new ChangeBetUI();
	betTab->setCascadeOpacityEnabled(true);
	betTab->init();
	betTab->setPosition(origin + visibleSize / 2);

	this->addChild(betTab);
}

void GameSlotInfoPopup::initInfoTab()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	infoTab = ui::PageView::create();
	infoTab->setAnchorPoint(Vec2(0.5f, 0.5f));

	infoTab->setContentSize(Size(1100, 475));
	infoTab->setPosition(origin + visibleSize / 2 - Vec2(0, 75));

	this->addChild(infoTab);
}

void GameSlotInfoPopup::onChangeTab(cocos2d::ui::RadioButton* btn, cocos2d::ui::RadioButton::EventType type)
{
	if (type == ui::RadioButton::EventType::SELECTED) {
		if (btn->getName() == "Bet") {
			betTab->setVisible(true);
			infoTab->setVisible(false);
		}
		else {
			betTab->setVisible(false);
			infoTab->setVisible(true);
		}
	}
}

void GameSlotInfoPopup::reset()
{
	BasePopup::reset();
}

void GameSlotInfoPopup::prepareAndShow(cocos2d::Node* parent)
{
	this->btnBet->check();
	this->btnInfo->uncheck();

	auto oGame = ((GameSlotScene*)parent)->getMain()->getGame();

	this->betTab->setGame(oGame);

	if (this->getParent() != parent) {
		infoTab->removeAllPages();
		for (auto i = 0; i < CSettings::NUM_INFO_PAGES; ++i) {
			auto page = ui::Layout::create();
			page->setContentSize(infoTab->getContentSize());
			page->setCascadeOpacityEnabled(true);
			infoTab->addPage(page);

			auto info = ui::ImageView::create(GameConstant::getInstance()->getResources().mainGame["info_page_" + ToString(i + 1)]);
			info->setPosition(page->getContentSize() / 2);
			info->setScale(0.9f);
			//info->setScaleX(1.3f);
			page->addChild(info);
		}
	}
	infoTab->setCurrentPageIndex(0);

	BasePopup::showWithQueue(parent);
}


ChangeBetUI::ChangeBetUI() : Node(),
oFooter(nullptr)
{
	this->autorelease();
}

bool ChangeBetUI::init()
{
	if (!Node::init()) return false;

	this->labelPayLines = Label::createWithTTF("PAYLINES", FONT_PassionOne_Regular, 60, Size::ZERO, TextHAlignment::CENTER);
	this->labelPayLines->setPosition(-200, 25);
	this->labelPayLines->setTextColor(Color4B(234, 202, 242, 255));
	this->addChild(this->labelPayLines);

	this->numPayLine = Label::createWithTTF("0", FONT_PassionOne_Regular, 60, Size::ZERO, TextHAlignment::CENTER);
	this->numPayLine->setPosition(-200, -50);
	this->addChild(this->numPayLine);

	this->labelBet = Label::createWithTTF("BET PER LINE", FONT_PassionOne_Regular, 60, Size::ZERO, TextHAlignment::CENTER);
	this->labelBet->setPosition(200, 25);
	this->labelBet->setTextColor(Color4B(234, 202, 242, 255));
	this->addChild(this->labelBet);

	this->numBet = Label::createWithTTF("PAYLINES", FONT_PassionOne_Regular, 60, Size::ZERO, TextHAlignment::CENTER);
	this->numBet->setPosition(200, -50);
	this->addChild(this->numBet);

	betAdjustNode = this->createAdjustGroup("Total Bet", [this](int value) {
		if (this->oFooter) {
			this->oFooter->onAdjustBet(value);
			this->oBetInfoText->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getTotalBet()));
			this->numBet->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getBet()));
		}
	});
	betAdjustNode->setCascadeOpacityEnabled(true);
	betAdjustNode->setScale(0.9f);
	betAdjustNode->setPosition(350, -250);

	this->oBetInfoText = (Label*)betAdjustNode->getChildByName("infoText");

	this->addChild(betAdjustNode);

	paylineAdjustNode = this->createAdjustGroup("Payline", [this](int value) {
		if (this->oFooter) {
			this->oFooter->onAdjustPayLine(value);
			this->oPaylineInfoText->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getLine()));
			this->numPayLine->setString(this->oPaylineInfoText->getString());
			this->oBetInfoText->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getTotalBet()));
			this->numBet->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getBet()));
		}
	});
	paylineAdjustNode->setCascadeOpacityEnabled(true);
	paylineAdjustNode->setScale(0.9f);
	paylineAdjustNode->setPosition(-220, -250);

	this->oPaylineInfoText = (Label*)paylineAdjustNode->getChildByName("infoText");

	this->addChild(paylineAdjustNode);

	return true;
}

void ChangeBetUI::setEnableBtn(BetType type, const std::string & name, bool isEnabled)
{
	CSpriteButton* btn = nullptr;
	switch (type)
	{
	case Bet:
		btn = (CSpriteButton*)betAdjustNode->getChildByName(name);
		break;
	case PayLine:
		btn = (CSpriteButton*)paylineAdjustNode->getChildByName(name);
		break;
	default:
		break;
	}
	if (btn) {
		btn->setTouchEnabled(isEnabled);
		btn->setColor(isEnabled ? Color3B::WHITE : Color3B(125, 125, 125));
	}
}

void ChangeBetUI::setGame(GameSlot::CGameBase * oGame)
{
	this->oGame = oGame;
	this->oFooter = oGame->getInterface()->getFooter();

	this->oPaylineInfoText->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getLine()));
	this->numPayLine->setString(this->oPaylineInfoText->getString());
	this->oBetInfoText->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getTotalBet()));
	this->numBet->setString(UtilFunction::FormatWithCommas(this->oGame->getMain()->getBet()));
}

cocos2d::Node * ChangeBetUI::createAdjustGroup(const std::string & labelText, const std::function<void(int)>& onAdjust)
{
	auto parent = Node::create();

	auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_BET_BACKGROUND);
	bg->setName("bg");
	parent->addChild(bg);

	auto label = Label::createWithTTF(labelText, FONT_PassionOne_Regular, 53, Size::ZERO, TextHAlignment::CENTER);
	label->setPositionX(-(bg->getContentSize().width + label->getContentSize().width) / 2 - 15);
	parent->addChild(label);

	if (onAdjust) {
		auto btnAdd = CSpriteButton::createButtonWithSpriteFrameName(PNG_FRAME_ADDITION_BUTTON, nullptr, [this, onAdjust]() {
			onAdjust(1);
		});
		btnAdd->setName("btnAdd");
		btnAdd->setScaleEvent(0.9f, 1.0f);
		btnAdd->setPosition((-btnAdd->getContentSize().width + bg->getContentSize().width) / 2, 0);
		parent->addChild(btnAdd);

		auto btnMinus = CSpriteButton::createButtonWithSpriteFrameName(PNG_FRAME_MINUS_BUTTON, nullptr, [this, onAdjust]() {
			onAdjust(-1);
		});
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
