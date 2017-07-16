#include "LevelUpPopup.h"

#include "Constant/Defination.h"
#include "Constant/PPEnums.h"

#include "SlotGame/base/game/CMainBase.h"

#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/Shop/PurchaseItemNode.h"
#include "Views/Effects/AnimationCoinCrown.h"

#include "Manager/PluginManager.h"
#include "Manager/PopupManager.h"

#include "Manager/InfoManager.h"
#include "Helper/Helper4Sprite.h"

#include "Custom/Common/LabelAutoSize.h"

USING_NS_CC;
using namespace std;
using namespace GameSlot;

#define HEIGHT_BETWEEN_LEVEL_TEXT 200
#define TEXT_LEVEL_SCALE 0.9
//#define HEIGHT_BETWEEN_LEVEL_TEXT 50

bool LevelUpPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}



	auto oContainer = Node::create();
	oContainer->setCascadeOpacityEnabled(true);
	this->addChild(oContainer);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	oContainer->setPosition(origin + visibleSize / 2);

	auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_POPUP_BACKGROUND);
	oContainer->addChild(bg);

	this->oLightRay = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_LIGHTRAY);
	this->oLightRay->setPositionY(bg->getContentSize().height * 1 / 5.5f);
	oContainer->addChild(this->oLightRay);

	auto title = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_POPUP_TITLE);
	title->setPositionY(bg->getContentSize().height/2 - title->getContentSize().height*2);
	oContainer->addChild(title);

	this->oStars = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_STARS);
	this->oStars->setPosition(this->oLightRay->getPosition());
	oContainer->addChild(this->oStars);

	auto clipNode = ClippingNode::create();
	clipNode->setCascadeOpacityEnabled(true);
	auto stencil = DrawNode::create();
	stencil->drawSolidRect(
		Point(-CSettings::CANVAS_WIDTH / 2, 93),
		Point(
			CSettings::CANVAS_WIDTH / 2,
			-107),
		Color4F(0, 0, 0, 0));
	/*test*/
	/*stencil->drawSolidRect(
		Point(-CSettings::CANVAS_WIDTH / 2, 400),
		Point(
			CSettings::CANVAS_WIDTH / 2,-400),
		Color4F(0, 0, 0, 0));*/

	clipNode->setStencil(stencil);
	clipNode->setPosition(this->oLightRay->getPosition());
	oContainer->addChild(clipNode);


	this->oCurrentLevel = Label::createWithBMFont(FONT_BITMAP_LEVELUP, "0", TextHAlignment::CENTER);
	this->oCurrentLevel->setScale(TEXT_LEVEL_SCALE*scaleDownLookGoodRatio);
	this->oCurrentLevel->setAnchorPoint(Vec2(0.5, 0.5));
	this->oCurrentLevel->setPositionY(0);

	this->oNewLevel = Label::createWithBMFont(FONT_BITMAP_LEVELUP, "0", TextHAlignment::CENTER);
	this->oNewLevel->setScale(TEXT_LEVEL_SCALE*scaleDownLookGoodRatio);
	//oNewLevel->setOpacity(255 * 0.5f);
	this->oNewLevel->setAnchorPoint(this->oCurrentLevel->getAnchorPoint());
	this->oNewLevel->setPositionY(this->oCurrentLevel->getPositionY() - HEIGHT_BETWEEN_LEVEL_TEXT);

	clipNode->addChild(this->oCurrentLevel);
	clipNode->addChild(this->oNewLevel);


	this->oCoinReward = Label::createWithTTF("0", FONT_PassionOne_Regular, 50);
	this->oCoinReward->setCascadeOpacityEnabled(true);
	this->oCoinReward->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->oCoinReward->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->oCoinReward->setPosition(-240, -100);
	oContainer->addChild(this->oCoinReward);

	auto coinIcon = Helper4Sprite::createOptimizeSprite(PNG_SHOP_COIN_ICON);
	coinIcon->setPosition(-40, coinIcon->getContentSize().height / 2);
	this->oCoinReward->addChild(coinIcon);

	this->oCrownReward = Label::createWithTTF("0", FONT_PassionOne_Regular, 50);
	this->oCrownReward->setCascadeOpacityEnabled(true);
	this->oCrownReward->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->oCrownReward->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->oCrownReward->setPosition(155, this->oCoinReward->getPositionY());
	oContainer->addChild(this->oCrownReward);

	auto crownIcon = Helper4Sprite::createOptimizeSprite(PNG_SHOP_CROWN_ICON);
	crownIcon->setPosition(-55, crownIcon->getContentSize().height / 2 + 5);
	this->oCrownReward->addChild(crownIcon);

	btnCollect = this->createGreenButton(false);
	btnCollect->setScale(1.2f);
	btnCollect->getTitleLabel()->setString("COLLECT");
	btnCollect->setPosition(Vec2(-235, -260));
	btnCollect->addTouchEventListener(CC_CALLBACK_2(LevelUpPopup::onCollect, this));
	oContainer->addChild(btnCollect);

	btnCollectAndShare = this->createBlueButton(false);
	btnCollectAndShare->getTitleLabel()->setString("COLLECT & SHARE");
	btnCollectAndShare->setPosition(Vec2(145, -260));
	btnCollectAndShare->setScale(1.05f);
	btnCollectAndShare->addTouchEventListener(CC_CALLBACK_2(LevelUpPopup::onCollectAndShare, this));
	oContainer->addChild(btnCollectAndShare);

	//NEW BOOSTER 
	this->boosterIconBg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_BOOSTER_ICON_BG);
	this->boosterIconBg->setPosition(bg->getContentSize() / 2 - Size(100, 100));
	this->boosterIconBg->setVisible(false);
	oContainer->addChild(this->boosterIconBg);

	this->boosterIcon = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_BOOSTER_ICON);
	this->boosterIcon->setPosition(bg->getContentSize() / 2 - Size(100, 100));
	this->boosterIcon->setVisible(false);
	oContainer->addChild(this->boosterIcon);

	this->boosterMultiplierCoin = ui::Button::create(PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_SMALL_BG,"","",ui::Widget::TextureResType::PLIST);
	this->boosterMultiplierCoin->setZoomScale(0);
	this->boosterMultiplierCoin->setVisible(false);
	this->boosterMultiplierCoin->setPosition(this->boosterIcon->getPosition());
	auto labelBoosterMultiplierCoin = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 50),
		"X2"
	);
	labelBoosterMultiplierCoin->setTextColor(Color4B(255, 231, 50, 255));
	
	this->boosterMultiplierCoin->setTitleLabel(labelBoosterMultiplierCoin);
	oContainer->addChild(this->boosterMultiplierCoin);

	this->boosterMultiplierCrown = ui::Button::create(PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_SMALL_BG,"","",ui::Widget::TextureResType::PLIST);
	this->boosterMultiplierCrown->setZoomScale(0);
	this->boosterMultiplierCrown->setVisible(false);
	this->boosterMultiplierCrown->setPosition(this->boosterIcon->getPosition());
	auto labelBoosterMultiplierCrown = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 50),
		"X2"
	);
	labelBoosterMultiplierCrown->setTextColor(Color4B(255, 231, 50, 255));

	this->boosterMultiplierCrown->setTitleLabel(labelBoosterMultiplierCrown);
	oContainer->addChild(this->boosterMultiplierCrown);

	this->particalBoosterCoin = ParticleSystemQuad::create("animation/particle_lvlup_booster.plist");
	this->particalBoosterCoin->setTexture(Helper4Sprite::getTextureFromSpriteFramename(PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_YELLOW));
	this->particalBoosterCoin->stop();
	oContainer->addChild(this->particalBoosterCoin);

	this->particalBoosterCrown = ParticleSystemQuad::create("animation/particle_lvlup_booster.plist");
	this->particalBoosterCrown->setTexture(Helper4Sprite::getTextureFromSpriteFramename(PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_YELLOW));
	this->particalBoosterCrown->stop();
	oContainer->addChild(this->particalBoosterCrown);

	this->infoGroup = PurchaseItemNode::createInfoGroup(ShopItemType::MagicItemType);
	this->infoGroup->setPosition(210, 120);
	this->infoGroup->setVisible(false);
	((Label*)infoGroup->getChildren().at(0))->setString("Earn extra coins\nand crowns by buying\nbooster package");
	oContainer->addChild(this->infoGroup);

	this->infoButton = ui::Button::create(PNG_FRAME_SHOP_INFO_BTN,"","",ui::Widget::TextureResType::PLIST);
	this->infoButton->setScale(1.5);
	this->infoButton->setVisible(false);
	this->infoButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->infoButton->setPosition(this->boosterIcon->getPosition());
	this->infoButton->addTouchEventListener([this](cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type) {
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->infoGroup->setVisible(!this->infoGroup->isVisible());
	});
	oContainer->addChild(this->infoButton);


	return true;
}

void LevelUpPopup::reset()
{
	BasePopup::reset();

	this->oStars->stopAllActions();
	this->oLightRay->stopAllActions();

	this->oCurrentLevel->stopAllActions();
	this->oNewLevel->stopAllActions();

	this->oCurrentLevel->setPositionY(40);
	this->oNewLevel->setPositionY(this->oCurrentLevel->getPositionY() - HEIGHT_BETWEEN_LEVEL_TEXT);

	this->oCurrentLevel->setString("0");
	this->oNewLevel->setString("0");

	//ToUpper(collect);
	this->btnCollect->getTitleLabel()->setString(Language(btnCollect->getTitleLabel(), LanguageConstant::COLLECT));

	// rest button collect position 
	if (!InfoManager::getInstance()->getUserInfo()->loginFrom == ppEnum::Facebook) {
		btnCollectAndShare->setVisible(false);
		// center button collect
		btnCollect->setPosition(Vec2(0, btnCollect->getPosition().y));
	}
	else {
		//ToUpper(collect);
		this->btnCollectAndShare->getTitleLabel()->setString(Language(btnCollectAndShare->getTitleLabel(), LanguageConstant::COLLECTANDSHARE));

		btnCollectAndShare->setVisible(true);
		btnCollect->setPosition(Vec2(-235, btnCollect->getPosition().y));

	}
	this->boosterIcon->setVisible(false);
	this->boosterIconBg->setVisible(false);
	this->boosterIcon->stopAllActions();
	this->infoButton->stopAllActions();
	this->boosterMultiplierCoin->setVisible(false);
	this->boosterMultiplierCrown->setVisible(false);
	this->boosterMultiplierCoin->stopAllActions();
	this->boosterMultiplierCrown->stopAllActions();
	this->boosterMultiplierCoin->setPosition(this->boosterIcon->getPosition());
	this->boosterMultiplierCrown->setPosition(this->boosterIcon->getPosition());
	this->particalBoosterCoin->stop();
	this->particalBoosterCrown->stop();

	this->infoGroup->setVisible(false);
	this->infoButton->setVisible(false);
	//prepareAndShow(101, 106, 1000000, 1000000);

}

void LevelUpPopup::show()
{
	this->oStars->setScale(0);
	this->oStars->setOpacity(255);

	this->oStars->runAction(Sequence::createWithTwoActions(
		DelayTime::create(0.25f),
		EaseBackOut::create(ScaleTo::create(0.5f, 1.5f))));
	this->oStars->runAction(Sequence::createWithTwoActions(
		DelayTime::create(0.25f),
		FadeOut::create(0.8f)));

	this->oLightRay->runAction(RepeatForever::create(RotateBy::create(0.5f, 60)));

	this->runAction(Sequence::createWithTwoActions(
		DelayTime::create(1.0f),
		CallFunc::create([this]() {
		this->runNumberAnimation(iCurrentLevel, iNewLevel);
	})));

	BasePopup::show();
	updateAfterChangeLanguage();
}

void LevelUpPopup::prepareAndShow(
	int iCurrentLevel,
	int iNewLevel,
	const int64_t& iCoinReward,
	const int64_t& iCrownReward,
	bool isBoosterPackage,
	bool isX10
)
{
	this->isCollected = false;

	this->iCoinReward = iCoinReward;
	this->iCrownReward = iCrownReward;
	this->iCurrentLevel = iCurrentLevel;
	this->iNewLevel = iNewLevel;

	this->oCoinReward->setString(UtilFunction::FormatWithCommas(iCoinReward));
	this->oCrownReward->setString(UtilFunction::FormatWithCommas(iCrownReward));

	/*if (iCoinReward < 1000) {
		oCoinReward->setAnchorPoint(Vec2(0, 0.5));
		this->oCoinReward->setPosition(-120, -105);
	}else if (iCoinReward < 1000000) {
		oCoinReward->setAnchorPoint(Vec2(0, 0.5));
		this->oCoinReward->setPosition(-140, -105);
	}else {
		oCoinReward->setAnchorPoint(Vec2(0.5, 0.5));
		this->oCoinReward->setPosition(-35, -105);
	}
	if (iCrownReward < 1000) {
		oCrownReward->setAnchorPoint(Vec2(0, 0.5));
		this->oCrownReward->setPosition(-120 + 355, oCoinReward->getPosition().y);
	}else if (iCrownReward < 1000000) {
		oCrownReward->setAnchorPoint(Vec2(0, 0.5));
		this->oCrownReward->setPosition(-140 + 355, oCoinReward->getPosition().y);
	}else {
		oCrownReward->setAnchorPoint(Vec2(0.5, 0.5));
		this->oCrownReward->setPosition(-35 + 355, oCoinReward->getPosition().y);
	}*/

	string extra0 = "";
	if (iCurrentLevel < 10) {
		extra0 = "0";
	}
	this->oCurrentLevel->setString(extra0+ToString(iCurrentLevel));
	extra0 = "";
	if (iNewLevel < 10) {
		extra0 = "0";
	}
	this->oNewLevel->setString(extra0+ToString(iNewLevel));

	if (isBoosterPackage)
	{
		this->oCoinReward->setPosition(-this->oCoinReward->getContentSize().width - 50, -100);
		this->boosterIcon->setVisible(true);
		this->boosterIconBg->setVisible(true);
		this->boosterIcon->runAction(
			RepeatForever::create(Sequence::createWithTwoActions(
				ScaleTo::create(1.0f, -1, 1),
				ScaleTo::create(1.0f, 1, 1)
			)));
		this->boosterMultiplierCoin->setVisible(true);
		this->boosterMultiplierCrown->setVisible(true);
		this->runActionForBoosterCoin();
		this->runActionForBoosterCrown();
		if (isX10)
		{
			this->boosterMultiplierCoin->getTitleLabel()->setString("X10");
			this->boosterMultiplierCrown->getTitleLabel()->setString("X10");
			this->boosterMultiplierCoin->loadTextureNormal(PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_LARGE_BG,ui::Widget::TextureResType::PLIST);
			this->boosterMultiplierCrown->loadTextureNormal(PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_LARGE_BG,ui::Widget::TextureResType::PLIST);
		}
		else
		{
			this->boosterMultiplierCoin->getTitleLabel()->setString("X2");
			this->boosterMultiplierCrown->getTitleLabel()->setString("X2");
			this->boosterMultiplierCoin->loadTextureNormal(PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_SMALL_BG,ui::Widget::TextureResType::PLIST);
			this->boosterMultiplierCrown->loadTextureNormal(PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_SMALL_BG,ui::Widget::TextureResType::PLIST);
		}
	}
	else {
		this->oCoinReward->setPosition(-this->oCoinReward->getContentSize().width, -100);
		this->infoButton->setVisible(true);
		this->infoButton->runAction(
			RepeatForever::create(Sequence::createWithTwoActions(
				FadeTo::create(0.5f,255*0.3f),
				FadeIn::create(0.5f)
			)));
	}

	//BasePopup::showWithQueue(this->scene);
	BasePopup::showWithQueue(_director->getRunningScene());

}

void LevelUpPopup::collectCoin()
{
	PopupManager::getInstance()->getLoadingAnimation()->hide();
	if (this->isCollected) {
		return;
	}
	this->isCollected = false;

	this->hide();
	this->scene->onLevelUpCollected(this->iCoinReward, this->iCrownReward);
}

void LevelUpPopup::onCollect(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		this->collectCoin();

		//tmp disable coin, crown animation
		AnimationCoinCrown::create(
			_director->getRunningScene(),
			this->btnCollect->getParent()->convertToWorldSpaceAR(this->btnCollect->getPosition()),
			this->iCoinReward
		);
		AnimationCoinCrown::create(
			_director->getRunningScene(),
			this->btnCollect->getParent()->convertToWorldSpaceAR(this->btnCollect->getPosition()),
			this->iCrownReward,
			AnimationType::CrownAnimation
		);
	}
}

void LevelUpPopup::onCollectAndShare(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {

		auto user = InfoManager::getInstance()->getUserInfo();

		sdkbox::FBShareInfo info;

		info.type = sdkbox::FBShareType::FB_LINK;
		info.link = Configs::AppDomain;
		info.image = Configs::LevelUpThumbnailLink;
		info.title = LanguageText(nullptr, LanguageConstant::SHARE_FACEBOOK_LEVELUP, "caption");
		info.text = user->name + " " +
			LanguageText(nullptr, LanguageConstant::SHARE_FACEBOOK_LEVELUP, "info") + " " + ToString(user->level);

		auto animationCoinCrown = [this]()
		{
			AnimationCoinCrown::create(
				_director->getRunningScene(),
				this->btnCollectAndShare->getParent()->convertToWorldSpaceAR(this->btnCollectAndShare->getPosition()),
				this->iCoinReward
			);
			AnimationCoinCrown::create(
				_director->getRunningScene(),
				this->btnCollectAndShare->getParent()->convertToWorldSpaceAR(this->btnCollectAndShare->getPosition()),
				this->iCrownReward,
				AnimationType::CrownAnimation
			);
		};
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		PluginManager::getInstance()->getFacebookController()->share(info, [this, animationCoinCrown](const std::string& mes) {
			this->collectCoin();
			animationCoinCrown();
		}, [this, animationCoinCrown](const std::string& mes) {
			this->collectCoin();
			animationCoinCrown();
		}, [this, animationCoinCrown]() {
			this->collectCoin();
			animationCoinCrown();
		});
	}
}

void LevelUpPopup::runNumberAnimation(
	int iCurrentLevel,
	int iNewLevel)
{

	//return;
	auto aCurrentLetter = this->oCurrentLevel->getStringLength();
	auto aNewLetter = this->oNewLevel->getStringLength();

	if (aCurrentLetter == aNewLetter) {
		for (int i = aCurrentLetter - 1; i >= 0; --i, iCurrentLevel /= 10, iNewLevel /= 10) {
			auto iCur = iCurrentLevel % 10;
			auto iNew = iNewLevel % 10;
			if (iCur == iNew) {
				continue;
			}
			this->oCurrentLevel->getLetter(i)->runAction(MoveBy::create(1.0, Vec2(0, HEIGHT_BETWEEN_LEVEL_TEXT/ (TEXT_LEVEL_SCALE*scaleDownLookGoodRatio))));
			this->oNewLevel->getLetter(i)->runAction(MoveBy::create(1.0, Vec2(0, HEIGHT_BETWEEN_LEVEL_TEXT / (TEXT_LEVEL_SCALE*scaleDownLookGoodRatio))));
		}
	}
	else {
		this->oCurrentLevel->runAction(MoveBy::create(1.0, Vec2(0, HEIGHT_BETWEEN_LEVEL_TEXT / (TEXT_LEVEL_SCALE*scaleDownLookGoodRatio))));
		this->oNewLevel->runAction(MoveBy::create(1.0, Vec2(0, HEIGHT_BETWEEN_LEVEL_TEXT / (TEXT_LEVEL_SCALE*scaleDownLookGoodRatio))));
	}
}

void LevelUpPopup::runActionForBoosterCoin()
{
	auto actionCoin1 = MoveTo::create(
		0.8f,
		Vec2(
			this->oCoinReward->getPosition().x + this->oCoinReward->getContentSize().width - 15,
			this->oCoinReward->getPosition().y - 55
		)
	);
	auto actionCoin2 = MoveTo::create(
		1.2f,
		Vec2(
			this->oCoinReward->getPosition().x + this->oCoinReward->getContentSize().width + 55,
			this->oCoinReward->getPosition().y
		)
	);
	this->boosterMultiplierCoin->runAction(
		Sequence::create(
			actionCoin1,
			actionCoin2,
			CallFunc::create([this]()
			{
		this->particalBoosterCoin->setPosition(this->boosterMultiplierCoin->getPosition() + Size(0, this->boosterMultiplierCoin->getContentSize().width / 4));
		this->particalBoosterCoin->start();
			}),
			nullptr
		)
	);
}

void LevelUpPopup::runActionForBoosterCrown()
{
	auto actionCrown1 = MoveTo::create(
		0.4f,
		Vec2(
			this->oCrownReward->getPosition().x + this->oCrownReward->getContentSize().width + 55,
			this->oCrownReward->getPosition().y + 5
		)
	);
	auto actionCrown2 = MoveTo::create(
		0.3f,
		Vec2(
			this->oCrownReward->getPosition().x + this->oCrownReward->getContentSize().width + 55,
			this->oCrownReward->getPosition().y + 55
		)
	);
	auto actionCrown3 = EaseBounceOut::create(MoveTo::create(
		1.3f,
		Vec2(
			this->oCrownReward->getPosition().x + this->oCrownReward->getContentSize().width + 55,
			this->oCrownReward->getPosition().y
		)
	));
	this->boosterMultiplierCrown->runAction(
		Sequence::create(
			actionCrown1,
			actionCrown2,
			actionCrown3,
			CallFunc::create([this]()
	{
		this->particalBoosterCrown->setPosition(this->boosterMultiplierCrown->getPosition() + Size(0, this->boosterMultiplierCrown->getContentSize().width / 4));
		this->particalBoosterCrown->start();
	}),
			nullptr
		)
	);
}

void LevelUpPopup::updateAfterChangeLanguage() {

	float maxScaleBtnCollect = 1;
	float minScaleBtnCollect = 0;
	
	float maxScaleBtnShare = 1;
	float minScaleBtnShare = 0;


	if (LanguageManager::getInstance()->getCurrentLanguage() == indo) {
		minScaleBtnCollect = 0.6;
		maxScaleBtnShare = 0.75;
	}else if (LanguageManager::getInstance()->getCurrentLanguage() == my) {
		minScaleBtnCollect = 0.7;
	}else if (LanguageManager::getInstance()->getCurrentLanguage() == en) {
		maxScaleBtnCollect = 0.9;
	}else if (LanguageManager::getInstance()->getCurrentLanguage() == cn ||
		LanguageManager::getInstance()->getCurrentLanguage() == tran_cn) {
		maxScaleBtnCollect = 0.85;
	}else if (LanguageManager::getInstance()->getCurrentLanguage() == vn ) {
		maxScaleBtnCollect = 0.9;
		maxScaleBtnShare = 0.9;
	}
	((LabelAutoSize*)this->btnCollect->getTitleLabel())->setString(LanguageManager::getInstance()->getStringForKeys(this->btnCollect->getTitleLabel(), LanguageConstant::COLLECT), minScaleBtnCollect, maxScaleBtnCollect);
	((LabelAutoSize*)this->btnCollectAndShare->getTitleLabel())->setString(LanguageManager::getInstance()->getStringForKeys(this->btnCollectAndShare->getTitleLabel(), LanguageConstant::COLLECTANDSHARE), 0, maxScaleBtnShare);
}
