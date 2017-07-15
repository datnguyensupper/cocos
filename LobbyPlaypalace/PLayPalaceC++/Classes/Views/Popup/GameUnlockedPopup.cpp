#include "GameUnlockedPopup.h"
#include "Constant/Defination.h"
#include "SlotGame/base/game/CMainBase.h"
#include "Info/ServerSlotGameInfo.h"
#include "Custom/Common/LabelAutoSize.h"

#include "Manager/PopupManager.h"

#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/DailyChallengePopup.h"
#include "Views/Popup/PiggyBankPopup.h"
#include "Helper/Helper4Sprite.h"
#include "Helper/Helper4Scene.h"

USING_NS_CC;
using namespace std;
using namespace GameSlot;

bool GameUnlockedPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}
	// preload img feature unlock
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_FEATURE_UNLOCKED);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_SLOT_GAME_ICONS);


	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Helper4Sprite::createOptimizeSprite(PNG_NOTIFICATION_POPUP_BACKGROUND);
	bg->setPosition(origin + visibleSize / 2);
	auto size = bg->getContentSize();
	bg->setContentSize(Size(size.width * 0.9f, size.height * 1.2f));
	this->addChild(bg);

	this->oLightRay = createLightRayBG(bg->getPosition() + Vec2(0, 35));
	this->addChild(this->oLightRay);

	auto title = Helper4Sprite::createOptimizeSprite(PNG_UNLCOKED_POPUP_TITLE);
	title->setPosition(bg->getPosition() + Vec2(0, 250));
	this->addChild(title);

	//this->oText = Label::createWithTTF("You have unlocked a new game", FONT_PassionOne_Regular, 55, Size::ZERO, TextHAlignment::CENTER);
	this->oText = LabelAutoSize::createWithTTF(Language(nullptr, LanguageConstant::YOU_HAVE_UNLOCKED_A_NEW_GAME), FONT_PassionOne_Regular, 55, Size::ZERO, TextHAlignment::CENTER);
	this->oText->setName("infoText");
	this->oText->setPosition(bg->getPosition() + Vec2(0, 170));
	((LabelAutoSize*)this->oText)->setTextAreaSize(Size(bg->getContentSize().width - 80, 100));
	this->addChild(this->oText);

	this->oGameIcon = Sprite::createWithSpriteFrameName(PNG_DEEPBLUE_GAME_ICON);
	this->oGameIcon->setPosition(oLightRay->getPosition());
	this->addChild(this->oGameIcon);

	auto oLockIcon = Helper4Sprite::createOptimizeSprite(PNG_UNLOCKED_ICON);
	oLockIcon->setPosition(this->oGameIcon->getPosition() + Vec2(this->oGameIcon->getContentSize().width / 2, -this->oGameIcon->getContentSize().height / 2) * 0.7f);
	this->addChild(oLockIcon);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(Vec2(
		bg->getPositionX() + bg->getContentSize().width / 2 - 30,
		bg->getPositionY() + bg->getContentSize().height / 2 - 30
	));
	this->addChild(closeBtn);

	this->btn = this->createGreenButton(Language(nullptr, LanguageConstant::GOTOLOBBY), 45);
	this->btn->setPosition(bg->getPosition() + Vec2(0, -195));
	this->btn->setScale(1.2f);
	/*this->btn->setTitleFontSize(45);
	this->btn->getTitleLabel()->setString("GO TO LOBBY");*/
	this->btn->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
			if (this->currentType == GameUnlockedPopupType::UNLOCK_GAME
				&& Helper4Scene::getRunningScene()->getTag() == ppEnum::GameScene::GameSlot)
			{
				PopupManager::getInstance()->popFrontShowPopup(this, true);
				((GameSlotScene*)this->getParent())->getHeader()->gotoLobbyScene();
			}else if (currentUFBL == LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK) {
				PopupManager::getInstance()->getPiggyBankPopup()->prepareAndShow(getParent());
				this->hide();
			}else{
				//this->listNewGameUnlocked.clear();
				this->hide();
			}
		}
	});
	this->addChild(this->btn);

	return true;
}

void GameUnlockedPopup::reset()
{
	this->oLightRay->stopAllActions();
	BasePopup::reset();

	updateAfterChangeLanguage();

	this->oGameIcon->setPosition(oLightRay->getPosition());
	if (this->listNewGameUnlocked.size() > 0) {
		auto gameInfo = this->listNewGameUnlocked[0];
		this->listNewGameUnlocked.pop_front();

		this->prepareInfo(gameInfo);
	}
	else if(this->listNewFeatureByLevel.size() > 0) {
		auto featureInfo = this->listNewFeatureByLevel[0];
		this->listNewFeatureByLevel.pop_front();

		this->prepareInfo(featureInfo);
	}
}


void GameUnlockedPopup::updateAfterChangeLanguage() {

	if (currentUFBL == LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE) {
	}
	else if (currentUFBL == LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE) {
	}
	else if (currentUFBL == LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK) {
	}
	else {
		UtilFunction::setLabelFontByLanguage(oText, "", (LanguageManager::getInstance()->getCurrentLanguage() == vn) ? 45 : 55);
		std::string text = Language(nullptr, LanguageConstant::YOU_HAVE_UNLOCKED_A_NEW_GAME);
		this->oText->setString(text);
	}

}

void GameUnlockedPopup::prepareAndShow(const std::deque<ServerSlotGameInfo*>& listNewGameUnlocked, cocos2d::Node * parent)
{
	if (listNewGameUnlocked.size() == 0) return;

	if (this->listNewGameUnlocked.empty() && this->listNewFeatureByLevel.empty() && !this->_isShowing && !PopupManager::getInstance()->isPopupInQueue(this)) {
		reset();
		this->btn->getTitleLabel()->setString(Language(btn->getTitleLabel(),LanguageConstant::GOTOLOBBY));

		this->listNewGameUnlocked = listNewGameUnlocked;

		auto gameInfo = this->listNewGameUnlocked[0];
		this->listNewGameUnlocked.pop_front();

		this->prepareInfo(gameInfo);
	}
	else {
		for (auto info : listNewGameUnlocked) {
			this->listNewGameUnlocked.push_back(info);
		}
	}
	for (auto info : listNewGameUnlocked) {
		switch (info->orderId)
		{
		case ppEnum::NEZHA:
		case ppEnum::GOLDEN_EGGS:
		case ppEnum::PHARAOH:
		case ppEnum::BOXING:
		case ppEnum::ROMAN_EMPIRE:
		case ppEnum::DEEP_BLUE:
			BasePopup::showWithQueue(parent, true);
			break;
		default:
			break;
		}
	}

	updateAfterChangeLanguage();
}

void GameUnlockedPopup::prepareAndShow(const std::deque<std::string>& listNewFeatureByLevel, cocos2d::Node* parent)
{
	if (listNewFeatureByLevel.size() == 0) return;

	if (this->listNewGameUnlocked.empty() && this->listNewFeatureByLevel.empty() && !this->_isShowing && !PopupManager::getInstance()->isPopupInQueue(this)) {
		this->btn->getTitleLabel()->setString(Language(btn->getTitleLabel(),LanguageConstant::OK));

		this->listNewFeatureByLevel = listNewFeatureByLevel;

		auto featureInfo = this->listNewFeatureByLevel[0];
		this->listNewFeatureByLevel.pop_front();

		this->prepareInfo(featureInfo);
	}
	else {
		for (auto info : listNewFeatureByLevel) {
			this->listNewFeatureByLevel.push_back(info);
		}
	}
	for (auto info : listNewFeatureByLevel) {
		BasePopup::showWithQueue(parent, true);
		if (info == LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE) {
			PopupManager::getInstance()->getDailyChallengePopup()->prepareAndShow(parent, true);
		}
		else if (info == LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK) {
		}

	}

	updateAfterChangeLanguage();
}

void GameUnlockedPopup::prepareInfo(ServerSlotGameInfo* info)
{
	std::string spriteName = "";
	switch (info->orderId)
	{
	case ppEnum::NEZHA:
		spriteName = PNG_NEZHA_GAME_ICON;
		break;
	case ppEnum::GOLDEN_EGGS:
		spriteName = PNG_GOLDENEGG_GAME_ICON;
		break;
	case ppEnum::PHARAOH:
		spriteName = PNG_PHARAOH_GAME_ICON;
		break;
	case ppEnum::BOXING:
		spriteName = PNG_BOXING_GAME_ICON;
		break;
	case ppEnum::ROMAN_EMPIRE:
		spriteName = PNG_ROMANEMPIRE_GAME_ICON;
		break;
	/*case ppEnum::CANDYLICIOUS:
		gameSlotUIInfo->spritePath = PNG_CANDYLICIOUS_GAME_ICON;
		break;
	case ppEnum::FRUITILICIOUS:
		gameSlotUIInfo->spritePath = PNG_FRUITILICIOUS_GAME_ICON;
		break;
	case ppEnum::KPOP:
		gameSlotUIInfo->spritePath = PNG_KPOP_GAME_ICON;
		break;
	case ppEnum::LITTLE_MONSTERS:
		gameSlotUIInfo->spritePath = PNG_LITTLEMONSTERS_GAME_ICON;
		break;
	case ppEnum::MAFIA:
		gameSlotUIInfo->spritePath = PNG_MAFIA_GAME_ICON;
		break;
	case ppEnum::SHERLOCK:
		gameSlotUIInfo->spritePath = PNG_SHERLOCK_GAME_ICON;
		break;
	case ppEnum::MAGIC_QUEST:
		gameSlotUIInfo->spritePath = PNG_MAGICQUEST_GAME_ICON;
		break;
	case ppEnum::BIKINI_BEACH:
		gameSlotUIInfo->spritePath = PNG_BIKINIBEACH_GAME_ICON;
		break;
	case ppEnum::FOUR_BEAUTIES:
		gameSlotUIInfo->spritePath = PNG_4BEAUTIES_GAME_ICON;
		break;
	case ppEnum::ZEUS:
		CC_SAFE_DELETE(gameSlotUIInfo);
		break;*/
	case ppEnum::DEEP_BLUE:
		spriteName = PNG_DEEPBLUE_GAME_ICON;
		break;
	default:
		break;
	}

	if (spriteName.empty()) {
		this->reset();
		return;
	}

	this->currentType = GameUnlockedPopupType::UNLOCK_GAME;

	if (this->currentType == GameUnlockedPopupType::UNLOCK_GAME
		&& Helper4Scene::getRunningScene()->getTag() == ppEnum::GameScene::GameSlot)
	{
		this->btn->getTitleLabel()->setString(Language(btn->getTitleLabel(),LanguageConstant::GOTOLOBBY));
	}
	else
	{
		this->btn->getTitleLabel()->setString(Language(btn->getTitleLabel(),LanguageConstant::OK));
	}

	//this->oGameIcon->setTexture(spriteName);
	this->oGameIcon->setSpriteFrame(spriteName);

	this->oLightRay->runAction(createActionRotateLightRay());
}

void GameUnlockedPopup::prepareInfo(std::string & info)
{
	std::string spriteName = "";
	std::string featureName = "";
	this->currentUFBL = info;
	this->btn->getTitleLabel()->setString(Language(btn->getTitleLabel(),LanguageConstant::OK));
	if (info == LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE) {
		spriteName = PNG_FRAME_UFBL_PAYLINE;
		featureName = "You've unlock PAY LINE !!!";
		this->oGameIcon->setPosition(oLightRay->getPosition() + Vec2(0, -30));
	}
	else if (info == LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE) {
		spriteName = PNG_FRAME_UFBL_DAILY_CHALLENGE;
		featureName = "YouPass DAILY CHALLENGE  to get coin !!!";
	}
	else if (info == LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK) {
		spriteName = PNG_FRAME_UFBL_PIGGY_BANK;
		featureName = "You've unlock PIGGY BANK !!!";
		this->btn->getTitleLabel()->setString(Language(btn->getTitleLabel(),LanguageConstant::PAY));
	}

	if (spriteName.empty() || featureName.empty()) {
		this->reset();
		return;
	}

	this->currentType = GameUnlockedPopupType::UNLOCK_FEATURE;

	this->oText->setString(featureName);

	//this->oGameIcon->setTexture(spriteName);
	this->oGameIcon->setSpriteFrame(spriteName);

	this->oLightRay->runAction(createActionRotateLightRay());

}