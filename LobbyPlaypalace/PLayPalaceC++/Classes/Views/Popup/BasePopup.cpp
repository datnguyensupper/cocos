#include "BasePopup.h"
#include "Constant/Defination.h"
#include "Constant/LanguageConstant.h"
#include "Configs.h"
#include "Manager/PopupManager.h"
#include "Manager/SoundManager.h"
#include "Manager/LanguageManager.h"
#include "Manager/ScaleManager.h"
#include "Util/UtilFunction.h"
#include "Custom/Common/ButtonScaleChild.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;

#define APLHA_DARK_LAYER 150
#define TAG_ACTION_HIDE_POPUP 2
BasePopup::BasePopup() : Layer()
{
}
bool BasePopup::init()
{
	if (!Layer::init()) {
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
    scaleDownLookGoodRatio = ScaleManager::getInstance()->getLookGoodScaleDownRatio();
	this->setVisible(false);
	return true;
}
void BasePopup::reset()
{
	this->stopAllActions();
	this->setVisible(false);
	this->_isShowing = false;
	this->setOpacity(0);
	this->setScale(getMinRatioPopup());
	this->_aEventListener.clear();
	if(this->layerDisableClickOnHide)
		this->layerDisableClickOnHide->setVisible(false);
}
cocos2d::ui::Button* BasePopup::createCloseButton()
{
	auto button = ButtonAdjustClikableAreaSize::create(PNG_FRAME_CLOSE_POPUP_BUTTON, "", "", ui::Widget::TextureResType::PLIST);
	button->setAnchorClickableAreaSize(Vec2::ANCHOR_MIDDLE);
	button->setClickableAreaSize(Size(200, 200));
	button->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	button->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->hide();
	});
	return button;
}


cocos2d::ui::Button* BasePopup::createLabelButton(ButtonScaleChild* button, std::string titleText, float fontSize) {

	std::string fontName = UtilFunction::getFontNameFromLanguage();

	auto labelAutoScale = LabelAutoSize::createWithTTF(
		TTFConfig(fontName, fontSize),
		titleText
	);
	UtilFunction::setLabelFontByLanguage(labelAutoScale);
	labelAutoScale->setString(titleText);
	labelAutoScale->setTextColor(Color4B::WHITE);
	labelAutoScale->setCascadeOpacityEnabled(true);
	labelAutoScale->enableShadow();
	//labelAutoScale->setDimensions(button->getContentSize().width * button->getScaleX(), button->getContentSize().height * button->getScaleY());
	labelAutoScale->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	labelAutoScale->setTextAreaSize(Size(button->getContentSize().width * button->getScaleX() - 20, button->getContentSize().height * button->getScaleY()));

	button->setTitleLabel(labelAutoScale);
	button->addScaleNode(labelAutoScale);
	return button;

}

cocos2d::ui::Button * BasePopup::createButton(const std::string & fileName, std::string titleText, float fontSize){

	auto button = ButtonScaleChild::create(fileName);
	button->setCascadeOpacityEnabled(true);
	button->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);

	createLabelButton(button, titleText, fontSize);

	return button;
}

cocos2d::ui::Button* BasePopup::createButtonWithFrameName(const std::string& frameName, std::string titleText, float fontSize) {
	auto button = ButtonScaleChild::create(frameName, "", "", ui::Widget::TextureResType::PLIST);
	button->setCascadeOpacityEnabled(true);
	button->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);

	createLabelButton(button, titleText, fontSize);

	return button;

}

cocos2d::ui::Button * BasePopup::createBlueButton(std::string titleText, float fontSize)
{
	if (titleText.empty()) {
		titleText = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COLLECTANDSHARE);
	}
	return this->createButtonWithFrameName(PNG_FRAME_BLUE_POPUP_BUTTON, titleText, fontSize);
}

cocos2d::ui::Button* BasePopup::createGreenButton(std::string titleText, float fontSize)
{
	if (titleText.empty()) {
		titleText = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::COLLECT);
	}
	return this->createButtonWithFrameName(PNG_FRAME_GREEN_POPUP_BUTTON, titleText, fontSize);
}

cocos2d::ui::Button* BasePopup::createPurpleButton(std::string titleText, float fontSize)
{
	if (titleText.empty()) {
		titleText = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::CANCEL);
	}
	return this->createButtonWithFrameName(PNG_FRAME_PURPLE_POPUP_BUTTON, titleText, fontSize);
}

std::vector<Action*> BasePopup::animationShowPopup()
{
	//Animation show popup
	float fadeIn = 0.2f;
	float scaleIn = 0.4f;


	auto actionOpacity = FadeIn::create(fadeIn);

	auto actionScaleTo = ScaleTo::create(scaleIn, getMaxRatioPopup());
	auto ease_out_back = EaseBackOut::create(actionScaleTo);

	std::vector<Action*> actionlist;
	actionlist.push_back(actionOpacity);
	actionlist.push_back(ease_out_back);
	return actionlist;
}

std::vector<Action*> BasePopup::animationHidePopup()
{
	float fadeIn = 0.2f;
	float scaleIn = 0.4f;

	auto actionOpacity = FadeOut::create(fadeIn);
	auto actionScaleTo = ScaleTo::create(scaleIn, 0.4f);
	auto ease_in_back = EaseBackIn::create(actionScaleTo);

	std::vector<Action*> actionList;
	actionList.push_back(actionOpacity);
	actionList.push_back(ease_in_back);
	return actionList;
}
void BasePopup::playSoundOpenPopup()
{
	SoundManager::getInstance()->playSoundEffectOpenOrClosePopup();
}
void BasePopup::playSoundClosePopup()
{
	SoundManager::getInstance()->playSoundEffectOpenOrClosePopup();
}

float BasePopup::getMinRatioPopup() {
	return 0.6*ScaleManager::getInstance()->getLookGoodScaleDownRatio();
}

float BasePopup::getMaxRatioPopup() {
	return ScaleManager::getInstance()->getLookGoodScaleDownRatio();
}

cocos2d::Action* BasePopup::createActionRotateLightRay() {
	return RepeatForever::create(Sequence::create(
		Spawn::createWithTwoActions(RotateBy::create(0.5f, 60), ScaleTo::create(0.5f, 1.0f)),
		Spawn::createWithTwoActions(RotateBy::create(0.5f, 60), ScaleTo::create(0.5f, 1.5f)),
		nullptr));
}

cocos2d::Sprite* BasePopup::createLightRayBG(cocos2d::Vec2 position) {
	Sprite * oLightRay = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_LIGHTRAY);
	oLightRay->setScale(1.5f);
	oLightRay->setPosition(position);

	return oLightRay;
}

void BasePopup::show(cocos2d::Node* parent, bool isCleanUp)
{
	if (!parent) {
		return;
	}
	if (this->getParent() != parent) {
		//remove in old parent and add to new parent
		if (this->getParent()) {
			//this->retain();
			this->getParent()->removeChild(this, isCleanUp);
		}
		parent->addChild(this);
	}
	this->show();
}

void BasePopup::callback4Click2DarkLayer() {

}

void BasePopup::show()
{
	if (this->_isShowing
		|| this->isVisible())
	{
		return;
	}
	this->_isShowing = true;
	//if dark layer not exist-> init dark layer and swallow touches
	if (!this->darkLayer)
	{
		//swallow touch
		auto listener1 = EventListenerTouchOneByOne::create();
		listener1->setSwallowTouches(true);
		listener1->onTouchBegan = [this](Touch* touch, Event* event) {
			if (Configs::printConsoleLog)	CCLOG("DARK LAYER SWALLOW TOUCH");
			
			callback4Click2DarkLayer();
			if (this->isVisible()) return true;
			return false;
		};

		//DARK LAYER
		this->darkLayer = CCLayerColor::create(ccc4(0, 0, 0, APLHA_DARK_LAYER));
		this->darkLayer->setScale(100);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->darkLayer);
		this->addChild(this->darkLayer, -1);
		//set first time to show
		this->setCascadeOpacityEnabled(true);
		this->setOpacity(0);
		this->setScale(getMinRatioPopup());
	}

	this->setVisible(true);

	//Animation show popup
	std::vector<Action*> actionList = this->animationShowPopup();
	FiniteTimeAction* longestAction = nullptr;
	for (auto &action : actionList)
	{
		if (!longestAction
			|| ((FiniteTimeAction*)action)->getDuration() > longestAction->getDuration()) {
			longestAction = ((FiniteTimeAction*)action);
		}
	}
	//sound
	this->playSoundOpenPopup();

	auto sequenseAction = Sequence::create(longestAction, CallFunc::create([this]()
	{
		this->_isShowing = false;
		for (auto listener : _aEventListener) {
			listener(this, PopupStateType::Popup_State_Open);
		}
	}), nullptr);

	for (auto &action : actionList)
	{
		if (action == longestAction) {
			this->runAction(sequenseAction);
		}
		else {
			this->runAction(action);
		}
	}
}

void BasePopup::showWithQueue(cocos2d::Node* parent, bool forceShowAfterReleaseScene)
{
	PopupManager::getInstance()->pushBackShowPopup(this, parent, forceShowAfterReleaseScene);
}

void BasePopup::hide()
{
	if (!this->isVisible()
		|| this->getActionByTag(TAG_ACTION_HIDE_POPUP))
	{
		return;
	}
	if (!this->layerDisableClickOnHide)
	{
		//swallow touch
		auto listener1 = EventListenerTouchOneByOne::create();
		listener1->setSwallowTouches(true);
		listener1->onTouchBegan = [this](Touch* touch, Event* event) {
			if (Configs::printConsoleLog)
			{
				CCLOG("layerDisableClickOnHide SWALLOW TOUCH");
			}
			return this->layerDisableClickOnHide->isVisible();
		};

		//DARK LAYER
		this->layerDisableClickOnHide = CCLayerColor::create(ccc4(0, 0, 0, 0));
		this->layerDisableClickOnHide->setScale(100);
		this->layerDisableClickOnHide->setVisible(false);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this->layerDisableClickOnHide);
		this->addChild(this->layerDisableClickOnHide, 200);
	}

	//Animation hide popup
	std::vector<Action*> actionList = this->animationHidePopup();
	FiniteTimeAction* longestAction = nullptr;
	for (auto &action : actionList)
	{
		if (!longestAction
			|| ((FiniteTimeAction*)action)->getDuration() > longestAction->getDuration()) {
			longestAction = ((FiniteTimeAction*)action);
		}
	}
	//layer swalles touch
	this->layerDisableClickOnHide->setVisible(true);
	//sound
	this->playSoundClosePopup();

	auto hideCallback = CallFunc::create([this]() {
		for (auto listener : _aEventListener) {
			listener(this, PopupStateType::Popup_State_Close);
		}
		this->layerDisableClickOnHide->setVisible(false);
		this->reset();
		PopupManager::getInstance()->popFrontShowPopup(this);
	});
	auto sequenseAction = Sequence::create(longestAction, hideCallback, nullptr);
	sequenseAction->setTag(TAG_ACTION_HIDE_POPUP);
	for (auto &action : actionList)
	{
		if (action == longestAction) {
			this->runAction(sequenseAction);
		}
		else {
			this->runAction(action);
		}
	}
}

void BasePopup::addPopupEventListener(const std::function<void(BasePopup*, PopupStateType)>& listener)
{
	if (listener) {
		_aEventListener.push_back(listener);
	}
}


void BasePopup::updateAfterChangeLanguage() {

}
