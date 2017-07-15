#include "AchievementPopup.h"
#include "AchievementCell.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Lobby/bottom/BottomLobbyLayout.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Configs.h"
#include "Constant/ResultCodeConstant.h"
#include "Helper/Helper4Scene.h"
#include "Helper/Helper4Sprite.h"
USING_NS_CC;
using namespace std;


bool AchievementPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_ACHIEVEMENT_PLIST);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//BACKGROUND
	auto bg = Helper4Sprite::createOptimizeSprite(PNG_ACHIEVEMENT_POPUP_BACKGROUND);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setContentSize(bg->getContentSize() + Size(80, 0));
	this->addChild(bg);

	//LABEL TITLE
	this->oLabel = Label::createWithTTF("ACHIEVEMENTS", FONT_PassionOne_Regular, 50);
	this->oLabel->setPosition(Vec2(
		bg->getPosition().x,
		bg->getPosition().y + bg->getContentSize().height / 2.3f
	));
	this->oLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->oLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->addChild(this->oLabel);

	auto radioButtonGroup = ui::RadioButtonGroup::create();
	this->addChild(radioButtonGroup);

	auto oPointBG = Sprite::createWithSpriteFrameName(FRAME_ACHIEVEMENT_POINT_FRAME);
	oPointBG->setCascadeOpacityEnabled(true);
	oPointBG->setPosition(Vec2(340, bg->getPositionY() + bg->getContentSize().height / 3.3f));
	this->addChild(oPointBG);

	this->oPointLabel = Label::createWithTTF(Language(nullptr, LanguageConstant::POPUP_ACHIEVEMENT_TOTAL_ACHIEVEMENT_POINT), FONT_PassionOne_Regular, 35);
	Language(oPointLabel, LanguageConstant::POPUP_ACHIEVEMENT_TOTAL_ACHIEVEMENT_POINT);
	this->oPointLabel->enableShadow();
	this->oPointLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->oPointLabel->setPosition((Vec2)oPointBG->getContentSize() / 2 + Vec2(0, 30));
	this->oPointLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->oPointLabel->setLineSpacing(-10);
	this->oPointLabel->setDimensions(oPointBG->getContentSize().width * 0.75f, oPointBG->getContentSize().height);
	oPointBG->addChild(this->oPointLabel);

	this->oPoint = Label::createWithTTF("0", FONT_PassionOne_Regular, 45);
	this->oPoint->setPosition(oPointLabel->getPosition() - Vec2(0, 60));
	this->oPoint->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	oPointBG->addChild(this->oPoint);

	this->btnGeneral.createRadioButton(this, radioButtonGroup, "General", Vec2(oPointBG->getPosition() - Vec2(0, 150)), CC_CALLBACK_2(AchievementPopup::onChangeGroup, this));
	this->btnGame.createRadioButton(this, radioButtonGroup, "Game", this->btnGeneral.btn->getPosition() - Vec2(0, 100), CC_CALLBACK_2(AchievementPopup::onChangeGroup, this));
	this->btnSocial.createRadioButton(this, radioButtonGroup, "Social", this->btnGame.btn->getPosition() - Vec2(0, 100), CC_CALLBACK_2(AchievementPopup::onChangeGroup, this));

	this->oContent = ui::ListView::create();
	this->oContent->setCascadeOpacityEnabled(true);
	this->oContent->setDirection(ui::ScrollView::Direction::VERTICAL);
	this->oContent->setTouchEnabled(true);
	this->oContent->setScrollBarEnabled(false);
	this->oContent->setBounceEnabled(true);
	this->oContent->setContentSize(Size(bg->getContentSize().width * 2.75f / 4, bg->getContentSize().height * 9 / 11));
	this->oContent->setClippingEnabled(true);
	this->oContent->setPosition(Vec2(this->btnGeneral.btn->getPositionX() + this->btnGeneral.btn->getContentSize().width * 0.72f, bg->getPositionY() + bg->getContentSize().height / 2.7f));
	this->oContent->setAnchorPoint(Vec2(0, 1));
	this->oContent->setItemsMargin(20);
	this->oContent->setGravity(ui::ListView::Gravity::CENTER_VERTICAL);
	this->oContent->setSwallowTouches(false);

	this->addChild(this->oContent);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(Vec2(
		bg->getPositionX() + bg->getContentSize().width / 2 - 30,
		bg->getPositionY() + bg->getContentSize().height / 2 - 30
	));
	this->addChild(closeBtn);

	return true;
}

void AchievementPopup::onChangeGroup(
	cocos2d::ui::RadioButton * btn, 
	cocos2d::ui::RadioButton::EventType type)
{
	if (type == cocos2d::ui::RadioButton::EventType::SELECTED) {
		//((CRadioButton*)btn)->check();
		AchievementGroupType type;
		if (btn->getName() == "General") {
			type = AchievementGroupType::GENERAL;
		}
		else if (btn->getName() == "Game") {
			type = AchievementGroupType::GAME;
		}
		else {
			type = AchievementGroupType::SOCIAL;
		}
		this->initContentView(type);
		this->oContent->jumpToTop();
	}
}

void AchievementPopup::initContentView(AchievementGroupType type)
{
	if (!bDirtyUpdateContent && type == this->currentType) {
		return;
	}
	this->bDirtyUpdateContent = false;
	this->currentType = type;

	this->oContent->removeAllItems();
	auto totalHeight = 0;

	auto achievementInfo = InfoManager::getInstance()->getAchievementInfo();

	this->btnGeneral.reloadNotification(achievementInfo->getGroup(AchievementGroupType::GENERAL)->iTotalCollectableAchievement);
	this->btnGame.reloadNotification(achievementInfo->getGroup(AchievementGroupType::GAME)->iTotalCollectableAchievement);
	this->btnSocial.reloadNotification(achievementInfo->getGroup(AchievementGroupType::SOCIAL)->iTotalCollectableAchievement);

	auto group = achievementInfo->getGroup(this->currentType);

	for (auto category : group->mCategories) {
		auto cat = new AchievementCategoryCell();
		cat->init(category.second);
		totalHeight += cat->getContentSize().height;
		this->oContent->pushBackCustomItem(cat);
	}
	this->oContent->setInnerContainerSize(Size(this->oContent->getContentSize().width, totalHeight + group->mCategories.size() * this->oContent->getItemsMargin()));
}

void AchievementPopup::prepareAndShow(cocos2d::Node * parent)
{
	this->bDirtyUpdateContent = true;
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(parent);
	InfoManager::getInstance()->reloadAchievementInfo([this, parent](bool isSuccess, AchievementInfo* result) {
		if (isSuccess) {
			//update notification for bottom
			PopupManager::getInstance()->getBottomLobbyLayout()->updateNotificationAchievements(result->getTotalCollectableAchievement());


			this->btnGeneral.btn->check();
			this->btnGame.btn->uncheck();
			this->btnSocial.btn->uncheck();

			this->oPoint->setString(ToString(InfoManager::getInstance()->getUserInfo()->achievementPoint));

			this->oLabel->setString(Language(oLabel,LanguageConstant::POPUP_ACHIEVEMENT_TITLE));


			UtilFunction::setLabelFontByLanguage(oPointLabel, "", (LanguageManager::getInstance()->getCurrentLanguage() == vn) ? 25 : 35);
			this->oPointLabel->setString(Language(nullptr,LanguageConstant::POPUP_ACHIEVEMENT_TOTAL_ACHIEVEMENT_POINT));


			int fontSize = (LanguageManager::getInstance()->getCurrentLanguage() == vn) ? 40 : 50;

			UtilFunction::setLabelFontByLanguage(this->btnGeneral.btn->getTitleRenderer(), "", fontSize);
			this->btnGeneral.btn->getTitleRenderer()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_ACHIEVEMENT_GROUP_TITLE_GENERAL));

			UtilFunction::setLabelFontByLanguage(this->btnGame.btn->getTitleRenderer(), "", fontSize);
			this->btnGame.btn->getTitleRenderer()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_ACHIEVEMENT_GROUP_TITLE_GAME));

			UtilFunction::setLabelFontByLanguage(this->btnSocial.btn->getTitleRenderer(), "", fontSize);
			this->btnSocial.btn->getTitleRenderer()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_ACHIEVEMENT_GROUP_TITLE_SOCIAL));


			BasePopup::show(parent);
		}
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	});
}

void AchievementPopup::onCollectAchievement(AchievementItem * item, cocos2d::Vec2 posButtonInWorld)
{
	if (item->isCollectable()) {
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		NetworkManager::getInstance()->collectAchievement(item->id, [this, item, posButtonInWorld](int coreResultCode,
			rapidjson::Value &doc,
			string responseAsString) {
			PopupManager::getInstance()->getLoadingAnimation()->hide();
			if (coreResultCode == RESULT_CODE_VALID) {
				InfoManager::getInstance()->getUserInfo()->achievementPoint += item->pointReward;
				//increase coin + crown for header
				PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCoin(item->coinReward);
				PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCrown(item->crownReward);
				//animation
				AnimationCoinCrown::create(
                    Helper4Scene::getRunningScene(),
					posButtonInWorld,
					item->coinReward
				);
				AnimationCoinCrown::create(
					Helper4Scene::getRunningScene(),
					posButtonInWorld,
					item->crownReward,
					AnimationType::CrownAnimation
				);

				InfoManager::getInstance()->reloadAchievementInfo([this](bool isSuccess, AchievementInfo* result) {
					if (isSuccess) {
						//update notification for bottom
						PopupManager::getInstance()->getBottomLobbyLayout()->updateNotificationAchievements(result->getTotalCollectableAchievement());

						//set POS for list view
						this->oPoint->setString(ToString(InfoManager::getInstance()->getUserInfo()->achievementPoint));

						this->bDirtyUpdateContent = true;
						auto position = this->oContent->getInnerContainerPosition();
						auto totalDistance = abs(this->oContent->getContentSize().height - this->oContent->getInnerContainerSize().height);

						auto percent = 1.0f - abs(position.y / totalDistance);

						this->initContentView(this->currentType);
						this->oContent->jumpToPercentVertical(min(max(0.0f, percent * 100), 100.0f));
					}
				});
			}
		}, [](std::string result) {
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		}, [](std::string result) {
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		});
	}
}


void AchievementGroupNode::createRadioButton(
	cocos2d::Node * parent, 
	cocos2d::ui::RadioButtonGroup * group, 
	const std::string & text, 
	const cocos2d::Vec2 & pos,
	std::function<void(cocos2d::ui::RadioButton*btn, cocos2d::ui::RadioButton::EventType type)> cb)
{
	btn = CRadioButton::create(PNG_FRAME_SWITCH_TAB_BUTTON_OFF, PNG_FRAME_TRANSPARENT, PNG_FRAME_SWITCH_TAB_BUTTON_ON, PNG_FRAME_TRANSPARENT,PNG_FRAME_TRANSPARENT,  ui::Widget::TextureResType::PLIST);

	btn->setName(text);
	btn->setZoomScale(-0.1f);
	btn->addEventListener(cb);
	btn->setPosition(pos);
	btn->setTitleRenderer(text, FONT_PassionOne_Regular, 50, Color4B::WHITE, Color4B::WHITE);
	btn->getTitleRenderer()->enableShadow();
	group->addRadioButton(btn);

	oNotiBG = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_RED_NOTIFICATION);
	oNotiBG->setAnchorPoint(Vec2(1, 0.5f));
	oNotiBG->setCascadeOpacityEnabled(true);
	oNotiBG->setPosition((Vec2)btn->getContentSize() + Vec2(10, -10));
	btn->addChild(oNotiBG);

	oNotiLabel = Label::createWithTTF("0", FONT_PassionOne_Regular, 30);
	oNotiLabel->setPosition(oNotiBG->getContentSize() / 2);
	oNotiLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	oNotiBG->addChild(oNotiLabel);

	parent->addChild(btn);
}
