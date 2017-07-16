#include "SettingPopup.h"
#include "Scene/LoginScene.h"
#include "Util/UtilFunction.h"
#include "Constant/LanguageConstant.h"
#include "Custom/Common/ToggleButton.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Helper/Helper4String.h"
#include "Helper/KeyboardHelper.h"
#include "Helper/Helper4Scene.h"
#include "Manager/LanguageManager.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/SoundManager.h"
#include "Manager/ScaleManager.h"
#include "NotificationPopup.h"
#include "LoadingAnimation.h"
#include "Info/AdditionalInfo.h"
#include "Views/Popup/AddRefereeCodePopup.h"
#include "Helper/Helper4Sprite.h"

#define FONT_SIZE_1 52
#define FONT_SIZE_2 36

USING_NS_CC;
using namespace std;

bool SettingPopup::init(){

	// preload settings popup button
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_SETTINGS_POPUP_PLIST);

	if (!BasePopup::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	std::string fontName = UtilFunction::getFontNameFromLanguage();

	//BACKGROUND
	float scaleXBG = 1500 / 900.0f;
	float scaleYBG = 920 / 557.0f;
	auto background = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SETTING_POPUP_BACKGROUND);
	background->setScale(scaleYBG);
	background->setScaleX(scaleXBG);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background);

	//LOGGED VIA LABEL
	this->loggedViaLabel = Label::createWithTTF(
		"",
		fontName,
		FONT_SIZE_1 - 5
		);
	loggedViaLabel->setString(LanguageManager::getInstance()->getStringForKeys(loggedViaLabel, LanguageConstant::SETTING_LOGGED_WITH_LABLE) + "Facebook");
	this->loggedViaLabel->enableShadow();
	this->loggedViaLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->loggedViaLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->loggedViaLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->loggedViaLabel->setPosition(Vec2(
		background->getPosition().x - background->getContentSize().width * scaleXBG / 2 + 50,
		background->getPosition().y + background->getContentSize().height * scaleYBG / 2 - 90));
	this->addChild(this->loggedViaLabel);

	//NAME OF USER LABEL
	this->nameLabel = LabelAutoSize::createWithTTF(
		UtilFunction::trimStringAndAdd3Dots("Anonymoussssssss", 8),
		fontName,
		FONT_SIZE_2
	);
	((LabelAutoSize*)this->nameLabel)->setAutoFitType(LabelAutoFitType::TrimString);
	((LabelAutoSize*)this->nameLabel)->setTextAreaSize(Size(230, 0));
	this->nameLabel->enableShadow();
	this->nameLabel->setTextColor(Color4B::WHITE);
	this->nameLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->nameLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->nameLabel->setPosition(Vec2(
		this->loggedViaLabel->getPosition().x + 18,
		this->loggedViaLabel->getPosition().y - 52));
	this->addChild(this->nameLabel);

	//ACCOUNT UID LABEL
#pragma region ACCOUNT UID LABEL
	this->accountUIDScrollView = ui::ScrollView::create();
	this->accountUIDScrollView->setPosition(Vec2(
		this->nameLabel->getPosition().x + 255,
		this->nameLabel->getPosition().y - 53)
	);
	this->accountUIDScrollView->setContentSize(Size(405, 100));
	this->accountUIDScrollView->setScrollBarEnabled(false);
	this->accountUIDScrollView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	this->addChild(this->accountUIDScrollView);
	auto accountUIDTitleLabel = Label::createWithTTF(
		"Account UID:",
		fontName,
		FONT_SIZE_2 - 5
	);
	accountUIDTitleLabel->enableShadow();
	accountUIDTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	accountUIDTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	accountUIDTitleLabel->setTextColor(Color4B::WHITE);
	accountUIDTitleLabel->setPosition(Vec2(
		0,
		this->accountUIDScrollView->getContentSize().height / 2
	));
	accountUIDTitleLabel->setTextColor(Color4B::WHITE);
	this->accountUIDScrollView->addChild(accountUIDTitleLabel);

	this->accountUIDLabel = Label::createWithTTF(
		"Anonymoussssssssssssssss",
		fontName,
		FONT_SIZE_2 - 5
	);
	this->accountUIDLabel->enableShadow();
	this->accountUIDLabel->setTextColor(Color4B(230, 115, 223, 255));
	this->accountUIDLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->accountUIDLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->accountUIDLabel->setPosition(Vec2(
		accountUIDTitleLabel->getPosition().x + accountUIDTitleLabel->getContentSize().width + 10,
		accountUIDTitleLabel->getPosition().y));
	accountUIDScrollView->addChild(this->accountUIDLabel);

	this->accountUIDScrollView->setInnerContainerSize(Size(
		this->accountUIDLabel->getPositionX() + this->accountUIDLabel->getContentSize().width + 5, 40));

#pragma endregion

	//LOGOUT BUTTON
	this->logoutButton = ui::Button::create(PNG_FRAME_SETTING_BTN_LOGOUT, "", "", ui::Widget::TextureResType::PLIST);
	this->logoutButton->setPosition(Vec2(
		this->accountUIDScrollView->getPosition().x + this->accountUIDScrollView->getContentSize().width + 250,
		this->accountUIDScrollView->getPosition().y + 70
	));
	this->logoutButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->logoutButton->setTitleColor(Color3B::WHITE);
	this->logoutButton->setTitleFontSize(FONT_SIZE_1);
	this->logoutButton->setTitleFontName(fontName);
	this->logoutButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LOGOUT_LABLE));
	this->logoutButton->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onLogoutTouched, this));
	this->addChild(this->logoutButton);

	//GAME OPTION LABEL
	this->gameOptionTitleLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_GAME_OPTION_LABLE),
		fontName,
		FONT_SIZE_2 - 5
	);
	UtilFunction::setLabelFontByLanguage(gameOptionTitleLabel);
	this->gameOptionTitleLabel->enableShadow();
	this->gameOptionTitleLabel->setTextColor(Color4B(235, 118, 228, 255));
	this->gameOptionTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->gameOptionTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->gameOptionTitleLabel->setPosition(Vec2(
		this->nameLabel->getPosition().x + 15,
		this->nameLabel->getPosition().y - 65
	));
	this->addChild(this->gameOptionTitleLabel);

	float distanceYLabels = 69;
	//BACKGROUND MUSIC
#pragma region BACKGROUND MUSIC
	//BACKGROUND MUSIC LABEL
	this->bgMusicTitleLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BACK_GROUND_MUSIC_LABLE),
		fontName,
		FONT_SIZE_2
	);
	UtilFunction::setLabelFontByLanguage(bgMusicTitleLabel);
	this->bgMusicTitleLabel->enableShadow();
	this->bgMusicTitleLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->bgMusicTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->bgMusicTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->bgMusicTitleLabel->setPosition(Vec2(
		this->gameOptionTitleLabel->getPosition().x,
		this->gameOptionTitleLabel->getPosition().y - distanceYLabels
	));
	this->addChild(this->bgMusicTitleLabel);

	//BACKGROUND MUSIC TOGGLE
	this->toggleBGMusicItem = ToggleButton::create(
		PNG_FRAME_SETTING_BTN_ON_OFF_ON,
		PNG_FRAME_SETTING_BTN_ON_OFF_OFF,
		PNG_FRAME_SETTING_BTN_ON_OFF_ON,
		PNG_FRAME_SETTING_BTN_ON_OFF_OFF
	);
	this->toggleBGMusicItem->setPosition(Vec2(
		visibleSize.width / 2 + origin.x + 318,
		this->bgMusicTitleLabel->getPosition().y
	));
	this->toggleBGMusicItem->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onToggleBGMusicTouched, this));

	this->addChild(this->toggleBGMusicItem);
#pragma endregion

	//SOUND EFFECTS
#pragma region SOUND EFFECTS
	//SOUND EFFECTS LABEL
	this->soundEffectsTitleLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BACK_SOUND_EFFECT_LABLE),
		fontName,
		FONT_SIZE_2
	);
	UtilFunction::setLabelFontByLanguage(soundEffectsTitleLabel);
	this->soundEffectsTitleLabel->enableShadow();
	this->soundEffectsTitleLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->soundEffectsTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->soundEffectsTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->soundEffectsTitleLabel->setPosition(Vec2(
		this->bgMusicTitleLabel->getPosition().x,
		this->bgMusicTitleLabel->getPosition().y - distanceYLabels
	));

	this->addChild(this->soundEffectsTitleLabel);

	//SOUND EFFECTS TOGGLE
	this->toggleSoundEffectsItem = ToggleButton::create(
		PNG_FRAME_SETTING_BTN_ON_OFF_ON,
		PNG_FRAME_SETTING_BTN_ON_OFF_OFF,
		PNG_FRAME_SETTING_BTN_ON_OFF_ON,
		PNG_FRAME_SETTING_BTN_ON_OFF_OFF
	);
	this->toggleSoundEffectsItem->setPosition(Vec2(
		this->toggleBGMusicItem->getPosition().x,
		this->soundEffectsTitleLabel->getPosition().y
	));
	this->toggleSoundEffectsItem->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onToggleSoundEffectTouched, this));

	this->addChild(this->toggleSoundEffectsItem);
#pragma endregion

	//LANGUAGE
#pragma region LANGUAGE
	//LANGUAGE LABEL
	this->languageTitleLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LANGUAGE),
		fontName,
		FONT_SIZE_2
	);
	LanguageManager::getInstance()->getStringForKeys(languageTitleLabel, LanguageConstant::SETTING_LANGUAGE);
	this->languageTitleLabel->enableShadow();
	this->languageTitleLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->languageTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->languageTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->languageTitleLabel->setPosition(Vec2(
		this->soundEffectsTitleLabel->getPosition().x,
		this->soundEffectsTitleLabel->getPosition().y - distanceYLabels
	));
	this->addChild(this->languageTitleLabel);

	//LANGUAGE SHOW COMBO BOX BUTTON
	this->languageButton = ui::Button::create(PNG_FRAME_SETTING_BTN_ISSUE_TYPE, "", "", ui::Widget::TextureResType::PLIST);
	this->languageButton->setPosition(Vec2(
		this->toggleBGMusicItem->getPosition().x,
		this->languageTitleLabel->getPosition().y
	));
	this->languageButton->setOpacity(0);
	this->languageButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->languageComboBox->setVisible(!this->languageComboBox->isVisible());
	});
	this->addChild(this->languageButton);

	//CURRENT LANGUAGE LABEL
	this->currentLanguageLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LANGUAGE_LABLE),
		fontName,
		FONT_SIZE_2 - 7
	);
	LanguageManager::getInstance()->getStringForKeys(currentLanguageLabel,LanguageConstant::SETTING_LANGUAGE_LABLE);
	this->currentLanguageLabel->enableShadow();
	this->currentLanguageLabel->setTextColor(Color4B::WHITE);
	this->currentLanguageLabel->setPositionY(this->languageButton->getPosition().y);
	this->currentLanguageLabel->setPositionX(this->languageButton->getPosition().x - 5);
	this->addChild(this->currentLanguageLabel);

	//LANGUAGE COMBO BOX
	this->languageComboBox = Node::create();
	this->languageComboBox->setCascadeOpacityEnabled(true);
	this->addChild(this->languageComboBox, 2);
	auto setupButtonPickLanguage = [this](ui::Button* target)
	{
		auto fontNameLabel = FONT_PassionOne_Regular;
		switch (target->getTag())
		{
		case cn:
		case tran_cn:
			/*todo:comming soon*/
			//fontNameLabel = FONT_CHINA;
			break;
		case vn:
			fontNameLabel = FONT_VIETNAME;
			break;
		default:
			break;
		}

		auto labelButton = Label::create(
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LANGUAGE_LABLE),
			"Arial",
			FONT_SIZE_2 - 5
		);
		UtilFunction::setFontForLabel(labelButton, "Arial", FONT_SIZE_2 - 5, true);
		labelButton->enableShadow();
		/*auto labelButton = Label::createWithTTF(
			TTFConfig(fontNameLabel, FONT_SIZE_2 - 5),
			LanguageManager::getInstance()->getStringForKeys(LanguageConstant::SETTING_LANGUAGE_LABLE)
		);*/
		//labelButton->setTTFConfig(TTFConfig(fontName, FONT_SIZE_2 - 5));
		target->setTitleLabel(labelButton);
		target->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onChangeLanguageTouched, this));
		target->setCascadeOpacityEnabled(true);
		target->setZoomScale(0);
	};
	auto buttonEng = ui::Button::create(PNG_FRAME_SETTING_BTN_ISSUE_TYPE, "", "", ui::Widget::TextureResType::PLIST);
	buttonEng->setPosition(Vec2(
		this->languageButton->getPosition().x,
		this->languageButton->getPosition().y - buttonEng->getContentSize().height 
	));
	buttonEng->setTag(SupportLanguage::en);
	setupButtonPickLanguage(buttonEng);
	buttonEng->getTitleLabel()->setString(ENGLISH_TEXT);
	this->languageComboBox->addChild(buttonEng);

	auto buttonVn = ui::Button::create(PNG_FRAME_SETTING_BTN_ISSUE_TYPE, "", "", ui::Widget::TextureResType::PLIST);
	buttonVn->setPosition(Vec2(
		buttonEng->getPosition().x,
		buttonEng->getPosition().y - buttonEng->getContentSize().height 
	));
	buttonVn->setTag(SupportLanguage::vn);
	setupButtonPickLanguage(buttonVn);
	std::string vnText = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LANGUAGES, "vn");
	buttonVn->getTitleLabel()->setString(vnText);
	this->languageComboBox->addChild(buttonVn);

	auto buttonCn = ui::Button::create(PNG_FRAME_SETTING_BTN_ISSUE_TYPE, "", "", ui::Widget::TextureResType::PLIST);
	buttonCn->setPosition(Vec2(
		buttonVn->getPosition().x,
		buttonVn->getPosition().y - buttonVn->getContentSize().height
	));
	buttonCn->setTag(SupportLanguage::cn);
	setupButtonPickLanguage(buttonCn);
	buttonCn->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr,LanguageConstant::SETTING_LANGUAGES, "cn"));
	this->languageComboBox->addChild(buttonCn);

	auto buttonTaiwan = ui::Button::create(PNG_FRAME_SETTING_BTN_ISSUE_TYPE, "", "", ui::Widget::TextureResType::PLIST);
	buttonTaiwan->setPosition(Vec2(
		buttonCn->getPosition().x,
		buttonCn->getPosition().y - buttonCn->getContentSize().height 
	));
	buttonTaiwan->setTag(SupportLanguage::tran_cn);
	setupButtonPickLanguage(buttonTaiwan);
	buttonTaiwan->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr,LanguageConstant::SETTING_LANGUAGES, "taiwan"));
	this->languageComboBox->addChild(buttonTaiwan);

	auto buttonMalay = ui::Button::create(PNG_FRAME_SETTING_BTN_ISSUE_TYPE, "", "", ui::Widget::TextureResType::PLIST);
	buttonMalay->setPosition(Vec2(
		buttonTaiwan->getPosition().x,
		buttonTaiwan->getPosition().y - buttonTaiwan->getContentSize().height 
	));
	buttonMalay->setTag(SupportLanguage::my);
	setupButtonPickLanguage(buttonMalay);
	buttonMalay->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LANGUAGES, "malay"));
	this->languageComboBox->addChild(buttonMalay);

	auto buttonIndo = ui::Button::create(PNG_FRAME_SETTING_BTN_ISSUE_TYPE, "", "", ui::Widget::TextureResType::PLIST);
	buttonIndo->setPosition(Vec2(
		buttonMalay->getPosition().x,
		buttonMalay->getPosition().y - buttonMalay->getContentSize().height 
	));
	buttonIndo->setTag(SupportLanguage::indo);
	setupButtonPickLanguage(buttonIndo);
	buttonIndo->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LANGUAGES, "indo"));
	this->languageComboBox->addChild(buttonIndo);

	this->languageComboBox->setVisible(false);
#pragma endregion

	//REFEREN CODE LABEL
	this->myReferenceCodeTitleLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_REF_LABLE),
		fontName,
		FONT_SIZE_2 - 5
	);
	LanguageManager::getInstance()->getStringForKeys(myReferenceCodeTitleLabel, LanguageConstant::SETTING_REF_LABLE);
	this->myReferenceCodeTitleLabel->enableShadow();
	this->myReferenceCodeTitleLabel->setTextColor(Color4B(235, 118, 228, 255));
	this->myReferenceCodeTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->myReferenceCodeTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->myReferenceCodeTitleLabel->setPosition(Vec2(
		this->languageTitleLabel->getPosition().x,
		this->languageTitleLabel->getPosition().y - distanceYLabels - 5
	));
	this->addChild(this->myReferenceCodeTitleLabel);

	//MY CODE
#pragma region MY CODE
	//MY CODE TITLE LABEL
	this->myCodeTitleLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_MYCODE_LABLE),
		fontName,
		FONT_SIZE_2
	);
	this->myCodeTitleLabel->enableShadow();
	this->myCodeTitleLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->myCodeTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->myCodeTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->myCodeTitleLabel->setPosition(Vec2(
		this->myReferenceCodeTitleLabel->getPosition().x,
		this->myReferenceCodeTitleLabel->getPosition().y - distanceYLabels
	));
	this->addChild(this->myCodeTitleLabel);

	//MY CODE LABEL
	this->myCodeLabel = Label::createWithTTF(
		"30VNKw",
		fontName,
		FONT_SIZE_2
	);
	this->myCodeLabel->enableShadow();
	this->myCodeLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->myCodeLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->myCodeLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->myCodeLabel->setPosition(Vec2(
		this->myCodeTitleLabel->getPosition().x + 280,
		this->myCodeTitleLabel->getPosition().y
	));
	this->addChild(this->myCodeLabel);

	//COPY BUTTON
	this->copyButton = ui::Button::create(PNG_FRAME_SETTING_BTN_PINK,"",PNG_FRAME_TRANSPARENT, ui::Widget::TextureResType::PLIST);
	this->copyButton->setPosition(Vec2(
		this->toggleBGMusicItem->getPosition().x-2,
		this->myCodeTitleLabel->getPosition().y-2
	));
	this->copyButton->setTitleFontName(fontName);
	this->copyButton->setTitleFontSize(FONT_SIZE_2 - 5);
	this->copyButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COPY, "text_copy"));
	this->copyButton->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onCopyMyCodeTouched, this));
	this->addChild(this->copyButton);
#pragma endregion

	//MY REF CODE
#pragma region MY REF CODE
	//MY REF CODE TITLE LABEL
	this->myRefCodeTitleLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_MYREFCODE_LABLE),
		fontName,
		FONT_SIZE_2
	);
	this->myRefCodeTitleLabel->enableShadow();
	this->myRefCodeTitleLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->myRefCodeTitleLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->myRefCodeTitleLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->myRefCodeTitleLabel->setPosition(Vec2(
		this->myCodeTitleLabel->getPosition().x,
		this->myCodeTitleLabel->getPosition().y - distanceYLabels
	));
	this->addChild(this->myRefCodeTitleLabel);

	//MY REF CODE LABEL
	this->myRefCodeLabel = Label::createWithTTF(
		"30VNKw",
		fontName,
		FONT_SIZE_2
	);
	this->myRefCodeLabel->enableShadow();
	this->myRefCodeLabel->setTextColor(Color4B(235, 118, 228, 255));
	this->myRefCodeLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	this->myRefCodeLabel->setAnchorPoint(Vec2(0, 0.5f));
	this->myRefCodeLabel->setPosition(Vec2(
		this->myCodeLabel->getPosition().x,
		this->myCodeLabel->getPosition().y - distanceYLabels
	));
	this->addChild(this->myRefCodeLabel);

	//ADD BUTTON
	this->addButton = ui::Button::create(PNG_FRAME_SETTING_BTN_PINK,"", PNG_FRAME_TRANSPARENT, ui::Widget::TextureResType::PLIST);
	this->addButton->setPosition(Vec2(this->copyButton->getPosition().x,
		this->copyButton->getPosition().y - distanceYLabels-2));
	this->addButton->setTitleFontName(fontName);
	this->addButton->setTitleFontSize(FONT_SIZE_2 - 5);
	this->addButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::ADD, "text_add"));
	this->addButton->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onAddRefCodeTouched, this));
	this->addChild(this->addButton);
#pragma endregion

	//TERMS OF SERVICE BUTTON
	this->termsOfServiceButton = ui::Button::create(PNG_FRAME_SETTING_BTN_TERM_OF_SERVICE, "", "", ui::Widget::TextureResType::PLIST);
	this->termsOfServiceButton->setAnchorPoint(Vec2(0, 0.5f));
	this->termsOfServiceButton->setPosition(Vec2(
		this->myRefCodeTitleLabel->getPosition().x,
		this->myRefCodeTitleLabel->getPosition().y - 100
	));
	this->termsOfServiceButton->setZoomScale(0);
	this->termsOfServiceButton->setScale(1.3f, 1.0f);
	this->termsOfServiceButton->setCascadeOpacityEnabled(true);
	this->termsOfServiceButton->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onTermsOfServiceTouched, this));

	auto termsOfServiceLabel = Label::createWithTTF(
		TTFConfig(fontName, FONT_SIZE_1 - 10),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BTN_TEARM_LABLE)
	);
	termsOfServiceLabel->setPosition(termsOfServiceButton->getContentSize() / 2);
	termsOfServiceLabel->setScaleX(1.0f / 1.3f);
	termsOfServiceLabel->setName("termsOfServiceLabel");
	this->termsOfServiceButton->addChild(termsOfServiceLabel);

	/*this->termsOfServiceButton->setTitleFontName(fontName);
	this->termsOfServiceButton->setTitleFontSize(FONT_SIZE_1 - 10);
	this->termsOfServiceButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(LanguageConstant::SETTING_BTN_TEARM_LABLE));
	this->termsOfServiceButton->getTitleRenderer()->setScaleX(1.0f / 1.3f);*/
	this->addChild(this->termsOfServiceButton);

	//TERMS OF SERVICE BUTTON
	this->privacyPolicyButton = ui::Button::create(PNG_FRAME_SETTING_BTN_PRIVACY_POLICY, "", "", ui::Widget::TextureResType::PLIST);
	this->privacyPolicyButton->setAnchorPoint(Vec2(0, 0.5f));
	this->privacyPolicyButton->setPosition(Vec2(
		this->termsOfServiceButton->getPosition().x + this->termsOfServiceButton->getContentSize().width * this->termsOfServiceButton->getScaleX() + 40,
		this->termsOfServiceButton->getPosition().y
	));
	this->privacyPolicyButton->setZoomScale(0);
	this->privacyPolicyButton->setScale(1.6f, 1.0f);
	this->privacyPolicyButton->setCascadeOpacityEnabled(true);
	this->privacyPolicyButton->addTouchEventListener(CC_CALLBACK_2(SettingPopup::onPrivacyPolicyTouched, this));

	auto privacyPolicyLabel = Label::createWithTTF(
		TTFConfig(fontName, FONT_SIZE_1 - 10),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BTN_PRIVACY_LABLE)
	);
	privacyPolicyLabel->setPosition(privacyPolicyButton->getContentSize() / 2);
	privacyPolicyLabel->setScaleX(1.0f / 1.6f);
	privacyPolicyLabel->setName("privacyPolicyLabel");
	this->privacyPolicyButton->addChild(privacyPolicyLabel);
	/*this->privacyPolicyButton->setTitleFontName(fontName);
	this->privacyPolicyButton->setTitleFontSize(FONT_SIZE_1 - 10);
	this->privacyPolicyButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(LanguageConstant::SETTING_BTN_PRIVACY_LABLE));
	this->privacyPolicyButton->getTitleRenderer()->setScaleX(1.0f / 1.3f);*/
	this->addChild(this->privacyPolicyButton);

	//VERSION LABEL
	this->versionLabel = Label::createWithTTF(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_VERSION_LABLE) + ": " + Configs::versionName,
		FONT_PassionOne_Regular,
		FONT_SIZE_2 - 5
	);
	this->versionLabel->enableShadow();
	this->versionLabel->setTextColor(Color4B(235, 118, 228, 255));
	this->versionLabel->setHorizontalAlignment(TextHAlignment::RIGHT);
	this->versionLabel->setAnchorPoint(Vec2(1, 0.5f));
	this->addChild(versionLabel, 1);

	Node * fakeNode = Node::create();
	fakeNode->setContentSize(Size(100, 100));
	CCMenuItemLabel* menuItemLabel = CCMenuItemLabel::create(fakeNode, [this](Ref* sender)
	{
		this->numberLabelVersionTextTouched++;
		if (this->numberLabelVersionTextTouched % 5 == 0
			&& InfoManager::getInstance()->getUserInfo())
		{
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				this->getParent(),
				"USER ID",
				ToString(InfoManager::getInstance()->getUserInfo()->id)
			);
		}
	});
	menuItemLabel->setAnchorPoint(Vec2(1, 0.5f));
	menuVersionLabel = CCMenu::create(menuItemLabel, NULL);
	menuVersionLabel->setAnchorPoint(Vec2(1, 0.5f));
	this->addChild(menuVersionLabel, 1);

	float menuVersionLabelX = this->privacyPolicyButton->getPosition().x + 710;
	menuVersionLabel->setPosition(Vec2(menuVersionLabelX,this->privacyPolicyButton->getPosition().y - 18));
	versionLabel->setPosition(menuVersionLabel->getPosition());


	//CLOSE BUTTON
	auto closeButton = this->createCloseButton();
	closeButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + background->getContentSize().width / 2.1f * scaleXBG,
		origin.y + visibleSize.height / 2 + background->getContentSize().height / 2.2f * scaleYBG
	));
	this->addChild(closeButton);

	LanguageManager::getInstance()->pushBackToUpdateLanguageList(this);
	this->updateAfterChangeLanguage();
	return true;
}

void SettingPopup::updateAfterChangeLanguage()
{
	std::string fontName = UtilFunction::getFontNameFromLanguage();
	std::string currentLanguage = LanguageManager::getInstance()->getCurrentLanguageName();
	bool isVNLanguage = LanguageManager::getInstance()->getCurrentLanguage() == vn;
	bool isEnLanguage = LanguageManager::getInstance()->getCurrentLanguage() == en;




	//RESET FONT NAME
	UtilFunction::setLabelFontByLanguage(this->loggedViaLabel);
	UtilFunction::setLabelFontByLanguage(this->gameOptionTitleLabel);
	UtilFunction::setLabelFontByLanguage(this->bgMusicTitleLabel);
	UtilFunction::setLabelFontByLanguage(this->soundEffectsTitleLabel);
	UtilFunction::setLabelFontByLanguage(this->languageTitleLabel);
	UtilFunction::setLabelFontByLanguage(this->currentLanguageLabel);
	UtilFunction::setLabelFontByLanguage(this->myReferenceCodeTitleLabel);

	UtilFunction::setLabelFontByLanguage(this->myCodeTitleLabel);

	UtilFunction::setLabelFontByLanguage(this->myRefCodeTitleLabel);

	int fontSize = isVNLanguage ? FONT_SIZE_2 - 5 : FONT_SIZE_2;
	UtilFunction::setLabelFontByLanguage(versionLabel,fontName,fontSize);

	auto termOfServiceText = (Label *) this->termsOfServiceButton->getChildByName("termsOfServiceLabel");
	UtilFunction::setLabelFontByLanguage(termOfServiceText);
	auto privacyPolicyText = (Label*) this->privacyPolicyButton->getChildByName("privacyPolicyLabel");
	UtilFunction::setLabelFontByLanguage(privacyPolicyText);
	this->logoutButton->setTitleFontName("Arial");
	this->copyButton->setTitleFontName("Arial");
	this->addButton->setTitleFontName("Arial");
	UtilFunction::setLabelFontByLanguage(this->logoutButton->getTitleLabel());
	UtilFunction::setLabelFontByLanguage(this->copyButton->getTitleLabel());
	UtilFunction::setLabelFontByLanguage(this->addButton->getTitleLabel());

	//RESET TEXT
	this->logoutButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LOGOUT_LABLE));
	this->bgMusicTitleLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BACK_GROUND_MUSIC_LABLE));
	this->soundEffectsTitleLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BACK_SOUND_EFFECT_LABLE));
	this->languageTitleLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_LANGUAGE));
	this->gameOptionTitleLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_GAME_OPTION_LABLE));
	this->myReferenceCodeTitleLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_REF_LABLE));
	this->myCodeTitleLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_MYCODE_LABLE));
	this->myRefCodeTitleLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_MYREFCODE_LABLE));
	termOfServiceText->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BTN_TEARM_LABLE));
	privacyPolicyText->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_BTN_PRIVACY_LABLE));
	this->versionLabel->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::SETTING_VERSION_LABLE) + ": " + Configs::versionName);
	this->copyButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COPY, "text_copy"));
	this->addButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::ADD, "text_add"));
	
	//check and scale button big
	/*auto checkAndScaleLongTitleForButton = [](ui::Button* target)
	{
		if (target->getTitleRenderer()->getContentSize().width - target->getContentSize().width > 0) {
			float lol = target->getContentSize().width * target->getScale() * 1.0f / target->getTitleRenderer()->getContentSize().width + 0.1f;
			target->getTitleRenderer()->setScale(
				target->getContentSize().width * target->getScale() * 1.0f / target->getTitleRenderer()->getContentSize().width + 0.1f);
		}
		else
		{
			target->getTitleRenderer()->setScale(1);
		}
	};
	checkAndScaleLongTitleForButton(this->termsOfServiceButton);
	checkAndScaleLongTitleForButton(this->privacyPolicyButton);*/

	this->prepareData();
}

void SettingPopup::onChangeLanguageTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
		return;
	}
	this->languageComboBox->setVisible(!this->languageComboBox->isVisible());
	auto button = (ui::Button*) sender;
	//if pick again current language
	if (button->getTag() == static_cast<int>(LanguageManager::getInstance()->getCurrentLanguage())) {
		return;
	}
	//tat tam thoi chuc nang nay
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);
	return;*/
	//coming soon china language
	SupportLanguage supportLanguage = static_cast<SupportLanguage>(button->getTag());

	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
	//change language
	LanguageManager::getInstance()->setCurrentLanguage(supportLanguage);
	//update language for all popup and ui
	LanguageManager::getInstance()->updateLanguageForApp();
	PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
		this->getParent(),
		"",
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_CHANGE_LANGUAGE, "success"),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		""
	);
	PopupManager::getInstance()->getLoadingAnimation()->hide();
}

void SettingPopup::onLogoutTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
		return;
	}
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
	NetworkManager::getInstance()->logout([this](
		int coreResultCode,
		rapidjson::Value &doc,
		string responseAsString){
        NetworkManager::getInstance()->resetJSESSIONID();
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		if (coreResultCode == RESULT_CODE_VALID) {
			SoundManager::getInstance()->stopAll();
			Director::getInstance()->replaceScene(
				TransitionFade::create(
					Configs::TIME_TRANSITION_FADE_SCENE,
					LoginScene::createScene("","")
				)
			);
		}
    },[](std::string msg){
        NetworkManager::getInstance()->resetJSESSIONID();
    },[](std::string msg){
        NetworkManager::getInstance()->resetJSESSIONID();
    });
}

void SettingPopup::onCopyMyCodeTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
		return;
	}
    
	std::string myCode = this->myCodeLabel->getString();
    KeyboardHelper::getInstance()->copyText2ClipBoard(myCode);
    
    
    enableBtnCopy(false);
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);*/
}

void SettingPopup::onAddRefCodeTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
		return;
	}
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()
	);*/
    
    //PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
	PopupManager::getInstance()->getAddRefereeCodePopup()->prepareAndShow(this->getParent());
}

void SettingPopup::onToggleBGMusicTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::BEGAN) {
		return;
	}
	ToggleButton* toggleButton = (ToggleButton*)sender;
	SoundManager::getInstance()->stopBackgroundMusic();
	SoundManager::getInstance()->setCanPlayBackgroundMusic(!toggleButton->isToggle());
	SoundManager::getInstance()->playBackgroundMusic(static_cast<ppEnum::GameScene>(Helper4Scene::getRunningScene()->getTag()));
}

void SettingPopup::onToggleSoundEffectTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::BEGAN) {
		return;
	}
	ToggleButton* toggleButton = (ToggleButton*)sender;
	SoundManager::getInstance()->setCanPlaySoundEffect(!toggleButton->isToggle());
	SoundManager::getInstance()->stopAllSoundEffect();
}

void SettingPopup::onTermsOfServiceTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
		return;
	}
	Application::getInstance()->openURL(Configs::PageTerm);
}

void SettingPopup::onPrivacyPolicyTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
		return;
	}
	Application::getInstance()->openURL(Configs::PagePrivacy);
}

void SettingPopup::prepareData()
{
	auto userInfo = InfoManager::getInstance()->getUserInfo();
	if (!userInfo) {
		return;
	}
	std::string loginVia = "Facebook";
	std::string accountUID = userInfo->facebookUID;
	if (userInfo->facebookUID.empty()) {
		loginVia = "PlayPalace";
		accountUID = userInfo->name;
	}
	this->loggedViaLabel->setString(LanguageManager::getInstance()->getStringForKeys(loggedViaLabel,LanguageConstant::SETTING_LOGGED_WITH_LABLE) + loginVia);
	UtilFunction::detectFontAndSetStringForLabel(this->nameLabel, FONT_PassionOne_Regular, userInfo->name);
	UtilFunction::detectFontAndSetStringForLabel(this->accountUIDLabel, FONT_PassionOne_Regular, accountUID);

	this->toggleBGMusicItem->setToggle(!SoundManager::getInstance()->getCanPlayBackgroundMusic());
	this->toggleSoundEffectsItem->setToggle(!SoundManager::getInstance()->getCanPlaySoundEffect());
	this->currentLanguageLabel->setString(LanguageManager::getInstance()->getStringForKeys(currentLanguageLabel,LanguageConstant::SETTING_LANGUAGE_LABLE));
	this->accountUIDScrollView->setInnerContainerSize(Size(
		accountUIDLabel->getPositionX()+ this->accountUIDLabel->getContentSize().width + 5, 40));

	this->myCodeLabel->setString(InfoManager::getInstance()->getAdditionalInfo()->referenceCodeInfo->referenceCode);

	updateRefereeCode();

	this->languageComboBox->setVisible(false);
    
    enableBtnCopy(true);
}

void SettingPopup::enableBtnCopy(bool enable){
    if(enable){
        this->copyButton->setEnabled(true);
		this->copyButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COPY, "text_copy"));
        this->copyButton->setTitleColor(cocos2d::Color3B::WHITE);
        
    }else{
        this->copyButton->setEnabled(false);
		this->copyButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COPY, "text_copied"));
        this->copyButton->setTitleColor(cocos2d::Color3B(71,31,84));
    }
}

void SettingPopup::enableBtnAdd(bool enable){
    if(enable){
        this->addButton->setEnabled(true);
        this->addButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::ADD, "text_add"));
        this->addButton->setTitleColor(cocos2d::Color3B::WHITE);
        
    }else{
        this->addButton->setEnabled(false);
        this->addButton->setTitleText(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::ADD, "text_added"));
        this->addButton->setTitleColor(cocos2d::Color3B(71,31,84));
    }
    this->myRefCodeLabel->setString(InfoManager::getInstance()->getAdditionalInfo()->referenceCodeInfo->refereeReferenceCode);
    
}

void SettingPopup::prepareAndShow(
	cocos2d::Node* parent
)
{
	this->prepareData();
	BasePopup::showWithQueue(parent);
}

void SettingPopup::updateRefereeCode() {

	std::string myRefCodeValue = InfoManager::getInstance()->getAdditionalInfo()->referenceCodeInfo->refereeReferenceCode;
	if (myRefCodeValue == "") enableBtnAdd(true);
	else enableBtnAdd(false);
}
