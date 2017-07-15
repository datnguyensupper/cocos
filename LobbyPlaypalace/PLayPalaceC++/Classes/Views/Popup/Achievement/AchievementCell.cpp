#include "AchievementCell.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/NotificationPopup.h"
#include "Custom/Common/ButtonScaleChild.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Configs.h"
#include "Helper/Helper4Sprite.h"


USING_NS_CC;
using namespace std;

bool AchievementItemCell::init(AchievementItem * itemInfo)
{
	if (!Node::init()) return false;
	this->autorelease();

	bool isFacebookIcon = (itemInfo->id == 45);

	//create name
	auto oName = Label::createWithTTF((!isFacebookIcon ? itemInfo->sub_category_name + " - " : "") + itemInfo->name, FONT_PassionOne_Regular, 30);
	oName->setTextColor(Color4B(234, 202, 242, 255));
	oName->setAnchorPoint(Vec2(0, 0.5f));
	oName->setPosition(200, -10);
	oName->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->addChild(oName);

	//get reward number
	auto reward = itemInfo->coinReward > 0 ? itemInfo->coinReward : itemInfo->crownReward;
	//create reward symbol (crown ? coin)
	auto oRewardSymbol = Helper4Sprite::createOptimizeSprite(itemInfo->coinReward > 0 ? PNG_SHOP_COIN_ICON : PNG_SHOP_CROWN_ICON);
	oRewardSymbol->setPosition(oName->getPosition() + Vec2(30, -35));
	oRewardSymbol->setScale(0.6f);
	this->addChild(oRewardSymbol);
	//create reward text
	auto oReward = Label::createWithTTF(UtilFunction::FormatWithCommas(reward), FONT_PassionOne_Regular, 36);
	oReward->setTextColor(Color4B(255, 255, 191, 255));
	oReward->setAnchorPoint(Vec2(0, 0.5f));
	oReward->setPosition(oRewardSymbol->getPosition() + Vec2(40, 0));
	oReward->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->addChild(oReward);

	//check if is completed and is collected to show UI
	if (itemInfo->isComplete) {
		if (itemInfo->isCollected) {
			//collected -> show collected text
			auto oTextCollected = Label::createWithTTF("Achievement Completed!", FONT_PassionOne_Regular, 30);
			oTextCollected->setAnchorPoint(Vec2(1, 0.5f));
			oTextCollected->setPosition(Vec2(oName->getPositionX() + 620, oReward->getPositionY()));
			oTextCollected->setAlignment(TextHAlignment::RIGHT, TextVAlignment::CENTER);
			this->addChild(oTextCollected);
		}
		else {
			auto button = ButtonScaleChild::create(FRAME_ACHIEVEMENT_BUTTON, "", "", ui::Widget::TextureResType::PLIST);
			button->setAnchorPoint(Vec2(1.1f, 0.25f));
			button->setPosition(Vec2(oName->getPositionX() + 635, oReward->getPositionY()));
			button->setCascadeOpacityEnabled(true);
			button->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
			button->addTouchEventListener([this, itemInfo, button](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
			{
				if (type == cocos2d::ui::Widget::TouchEventType::ENDED) {
					PopupManager::getInstance()->getAchievementPopup()->onCollectAchievement(itemInfo, button->getParent()->convertToWorldSpaceAR(button->getPosition()));
				}
			});

			auto labelAutoScale = LabelAutoSize::createWithTTF(
				TTFConfig(FONT_PassionOne_Regular, 32),
				"Collect"
			);
			labelAutoScale->setTextColor(Color4B::WHITE);
			labelAutoScale->setCascadeOpacityEnabled(true);
			labelAutoScale->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
			labelAutoScale->setTextAreaSize(Size(button->getContentSize().width * button->getScaleX(), button->getContentSize().height * button->getScaleY()));
			labelAutoScale->enableShadow();

			button->setTitleLabel(labelAutoScale);
			button->addScaleNode(labelAutoScale);

			this->addChild(button);
		}
	}
	else {
		//is not Completed -> show point reward

		auto oPointBG = Sprite::createWithSpriteFrameName(FRAME_ACHIEVEMENT_POINT_BG);
		oPointBG->setAnchorPoint(Vec2(1, 0.5f));
		oPointBG->setScale(0.9f);
		oPointBG->setPosition(Vec2(oName->getPositionX() + 620, oReward->getPositionY() + oReward->getContentSize().height / 2));
		this->addChild(oPointBG);

		auto oTextCollected = Label::createWithTTF(ToString(itemInfo->pointReward), FONT_PassionOne_Regular, 40);
		oTextCollected->setPosition(oPointBG->getPosition() - Vec2(oPointBG->getContentSize().width / 2 * oPointBG->getScale(), 0));
		oTextCollected->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
		this->addChild(oTextCollected);
	}

	//progress bg
	auto oProgressBG = Sprite::createWithSpriteFrameName(FRAME_ACHIEVEMENT_PROGRESS_BG);
	oProgressBG->setAnchorPoint(Vec2(0, 0.5f));
	oProgressBG->setPosition(Vec2(oName->getPositionX(), oRewardSymbol->getPositionY() - 45));
	this->addChild(oProgressBG);
	//progress bar
	auto bar = CCSprite::createWithSpriteFrameName(FRAME_ACHIEVEMENT_PROGRESS_BAR);
	bar->setVisible(false);
	this->addChild(bar);
	auto oProgress = ProgressTimer::create(bar);
	oProgress->setType(ProgressTimer::Type::BAR);
	oProgress->setMidpoint(Vec2(0, 0.5f));
	oProgress->setBarChangeRate(Vec2(1, 0));
	oProgress->setPosition(oProgressBG->getPosition() + Vec2(oProgressBG->getContentSize().width / 2 , 0));
	oProgress->setPercentage(itemInfo->status / itemInfo->goal * 100);
	this->addChild(oProgress);

	//progress text
	auto oProgressLabel = Label::createWithTTF(UtilFunction::FormatWithCommas(itemInfo->status) + "/" + UtilFunction::FormatWithCommas(itemInfo->goal), FONT_PassionOne_Regular, 28);
	oProgressLabel->setPosition(oProgress->getPosition());
	this->addChild(oProgressLabel);


	//create icon (stars, facebook icon, ...)
	if (isFacebookIcon) {
		auto iconFrame = Sprite::createWithSpriteFrameName(FRAME_ACHIEVEMENT_ICON_FRAME);
		iconFrame->setContentSize(iconFrame->getContentSize() * 0.9f);
		iconFrame->setPositionX(100);
		iconFrame->setPositionY(oRewardSymbol->getPositionY());
		this->addChild(iconFrame);

		auto icon = Sprite::createWithSpriteFrameName(FRAME_ACHIEVEMENT_FB_ICON);
		icon->setContentSize(iconFrame->getContentSize() * 0.9f);
		icon->setPosition(iconFrame->getPosition());
		this->addChild(icon);
	}
	else {
		auto numberOfStar = 0;
		if (itemInfo->isCollected) {
			numberOfStar = 3;
		}
		else {
			// nếu là dạng nhiệm vụ chỉ có 1 bậc, mà chưa hoàn thành thì không hiển thị sao nào, ngược lai thì trừ bớt 1 sao
			if (itemInfo->isOnTimeAchieved) {
				numberOfStar = 0;
			}
			else {
				numberOfStar = itemInfo->star - 1;
			}
		}

		auto star1 = Sprite::createWithSpriteFrameName(numberOfStar > 0 ? FRAME_ACHIEVEMENT_STAR_ON : FRAME_ACHIEVEMENT_STAR_OFF);
		star1->setPositionX(40);
		star1->setPositionY(oRewardSymbol->getPositionY());
		this->addChild(star1);

		auto star2 = Sprite::createWithSpriteFrameName(numberOfStar > 1 ? FRAME_ACHIEVEMENT_STAR_ON : FRAME_ACHIEVEMENT_STAR_OFF);
		star2->setScale(1.2f);
		star2->setPositionX(100);
		star2->setPositionY(oRewardSymbol->getPositionY());
		this->addChild(star2);

		auto star3 = Sprite::createWithSpriteFrameName(numberOfStar > 2 ? FRAME_ACHIEVEMENT_STAR_ON : FRAME_ACHIEVEMENT_STAR_OFF);
		star3->setPositionX(160);
		star3->setPositionY(oRewardSymbol->getPositionY());
		this->addChild(star3);
	}

	this->setCascadeOpacityEnabled(true);

	auto totalContentSize = oName->getPositionY() + oName->getContentSize().height / 2 - (oProgressBG->getPositionY() - oProgress->getContentSize().height) + 10;
	this->setContentSize(Size(0, totalContentSize));

	return true;
}

bool AchievementCategoryCell::init(AchievementCategory * categoryInfo)
{
	if (!ui::Layout::init()) return false;
	this->setLayoutType(ui::LayoutType::VERTICAL);
	this->autorelease();

	auto catWid = ui::Widget::create();
	catWid->setCascadeOpacityEnabled(true);
	this->addChild(catWid);

	auto contentWid = ui::Widget::create();
	contentWid->setCascadeOpacityEnabled(true);
	this->addChild(contentWid);

	auto oLabelBG = ui::ImageView::create(FRAME_ACHIEVEMENT_CATEGORY_BG, ui::Widget::TextureResType::PLIST);
	oLabelBG->setAnchorPoint(Vec2(0, 1));
	catWid->addChild(oLabelBG);

	auto oLabel = Label::createWithTTF(categoryInfo->name, FONT_PassionOne_Regular, 32);
	oLabel->setPosition(Vec2(
		30,
		oLabelBG->getPosition().y - oLabelBG->getContentSize().height / 2
	));
	oLabel->setTextColor(Color4B(235, 118, 228, 255));
	oLabel->setAnchorPoint(Vec2(0, 0.5f));
	oLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	catWid->addChild(oLabel);

	auto totalHeight = oLabelBG->getContentSize().height;

	auto lastY = oLabelBG->getPosition().y - oLabelBG->getContentSize().height / 2;
	auto height = oLabelBG->getContentSize().height;

	for (auto info : categoryInfo->mItems) {
		auto item = new AchievementItemCell();
		item->init(info.second);
		item->setPositionY(lastY - height);
		lastY = item->getPositionY();
		height = item->getContentSize().height;
		totalHeight += height;
		contentWid->addChild(item);
	}

	this->setCascadeOpacityEnabled(true);
	this->setContentSize(Size(0, totalHeight));

	return true;
}
