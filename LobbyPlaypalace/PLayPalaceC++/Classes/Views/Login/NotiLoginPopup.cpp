#include "NotiLoginPopup.h"

#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Util/UtilFunction.h"
#include "Scene/LoginScene.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;

#define APLHA_DARK_LAYER 150

NotiLoginPopup* NotiLoginPopup::create(LoginScene* parentScene)
{
	auto layer = NotiLoginPopup::create();
	layer->loginScene = parentScene;
	return layer;
}

// on "init" you need to initialize your instance
bool NotiLoginPopup::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//BACKGROUND
	auto background = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LOGIN_NOTIFICATION_BG);
	background->setScale(1.25f);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background);

	//LABEL TITLE
	this->titleLabel = Label::createWithTTF("", FONT_HelveticaNeue_Light, 35);
	this->titleLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 + 130));
	this->titleLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->titleLabel->setTextColor(Color4B::BLACK);
	this->titleLabel->setDimensions(400, 200);
	this->addChild(this->titleLabel);

	//LABEL BODY
	this->bodyLabel = Label::createWithTTF("", FONT_HelveticaNeue_Thin, 35);
	this->bodyLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->bodyLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->bodyLabel->setTextColor(Color4B::BLACK);
	this->bodyLabel->setDimensions(800, 300);
	this->addChild(this->bodyLabel);

	//EXIT BUTTON
	auto exitButton = ButtonAdjustClikableAreaSize::create(PNG_FRAME_LOGIN_CLOSE_POPUP,"","",ui::Widget::TextureResType::PLIST);
	exitButton->setClickableAreaSize(Size(150, 150));
	exitButton->setAnchorClickableAreaSize(Vec2::ANCHOR_MIDDLE);
	exitButton->setPosition(Vec2(origin.x + visibleSize.width / 2 + 380, origin.y + visibleSize.height / 2 + 160));
	exitButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	exitButton->addTouchEventListener(CC_CALLBACK_2(NotiLoginPopup::closePopupButtonTouched, this));
	this->addChild(exitButton);

	//OK BUTTON
	auto buttonOK = ui::Button::create(PNG_FRAME_LOGIN_BUTTON_LOGIN_PP,"","",ui::Widget::TextureResType::PLIST);
	buttonOK->setTitleText(MessageConstant::MESSAGE_OK);
	buttonOK->setTitleFontName(FONT_HelveticaNeue_Thin);
	buttonOK->setTitleFontSize(35);
	buttonOK->setTitleColor(Color3B::BLACK);
	buttonOK->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2 - 135));
	buttonOK->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	buttonOK->addTouchEventListener(CC_CALLBACK_2(NotiLoginPopup::okButtonTouched, this));
	this->addChild(buttonOK);

	this->setScale(0.1f);
    return true;
}

void NotiLoginPopup::okButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		if (callbackOK)
		{
			callbackOK();
		}
		BasePopup::hide();
	}
}

void NotiLoginPopup::closePopupButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		if (callbackCancel)
		{
			callbackCancel();
		}
		BasePopup::hide();
	}
}

void NotiLoginPopup::show(
	LoginScene* parentScene,
	std::string title,
	std::string body,
	std::function <void(void)> callbackOK,
	std::function <void(void)> callbackCancel
)
{
	this->setPosition(-parentScene->getPosition());
	UtilFunction::setLabelFontByLanguage(this->titleLabel, FONT_HelveticaNeue_Thin);
	this->titleLabel->setString(title);
	UtilFunction::setLabelFontByLanguage(this->bodyLabel, FONT_HelveticaNeue_Light);
	this->bodyLabel->setString(body);
	this->callbackOK = callbackOK;
	this->callbackCancel = callbackCancel;

	BasePopup::show(parentScene);
}
