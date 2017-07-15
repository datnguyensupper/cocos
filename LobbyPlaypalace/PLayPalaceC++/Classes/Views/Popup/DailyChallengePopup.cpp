#include "DailyChallengePopup.h"

#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LobbyConstant.h"
#include "Constant/LanguageConstant.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/StrategyManager.h"
#include "Manager/PopupManager.h"
#include "Manager/SoundManager.h"
#include "Manager/ScaleManager.h"
#include "Info/AdditionalInfo.h"

#include "Helper/AnimationHelper.h"
#include "Helper/Helper4String.h"
#include "Helper/Helper4Scene.h"

#include "SlotGame/base/utils/CSpriteButton.h"
#include "Custom/Common/CSpinMachine.h"

#include "Views/Popup/LoadingAnimation.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"

USING_NS_CC;
using namespace std;

bool DailyChallengePopup::init()
{
	if (!BasePopup::init()) return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_DAILY_CHALLENGE);

	auto bg = Sprite::createWithSpriteFrameName(FRAME_DAILY_CHALLENGE_BG);
	bg->setPosition(origin + visibleSize / 2);
	this->addChild(bg);

	this->txtInfo = Label::createWithTTF("Complete 5 tasks and get", FONT_PassionOne_Bold, 45);
	this->txtInfo->setTextColor(Color4B(255, 177, 49, 255));
	this->txtInfo->setPosition(bg->getPosition() + Vec2(0, bg->getContentSize().height * 1 / 3.0f));
	this->addChild(this->txtInfo);

	txtCoin = Label::createWithBMFont(FONT_BITMAP_DAILY_CHALLENGE, "50,000 ");
	txtCoin->setBMFontSize(23);

	txtCrown = Label::createWithBMFont(FONT_BITMAP_DAILY_CHALLENGE, " + 5 ");
	txtCrown->setBMFontSize(23);

	this->txtReward = ui::RichText::create();
	this->txtReward->pushBackElement(ui::RichElementCustomNode::create(0, Color3B::WHITE, 255, txtCoin));
	this->txtReward->pushBackElement(ui::RichElementImage::create(1, Color3B::WHITE, 255, PNG_SHOP_COIN_ICON));
	this->txtReward->pushBackElement(ui::RichElementCustomNode::create(2, Color3B::WHITE, 255, txtCrown));
	this->txtReward->pushBackElement(ui::RichElementImage::create(3, Color3B::WHITE, 255, PNG_SHOP_CROWN_ICON));

	this->txtReward->setPosition(bg->getPosition() + Vec2(0, bg->getContentSize().height * 1 / 3.8f));
	this->addChild(this->txtReward);

	auto bgProgress = Sprite::createWithSpriteFrameName(FRAME_DAILY_CHALLENGE_TOTAL_PROGRESS_BG);
	bgProgress->setPosition(bg->getPosition() + Vec2(0, bg->getContentSize().height * 1 / 8.0f));
	this->addChild(bgProgress);

	this->totalProgressSprite = CCSprite::createWithSpriteFrameName(FRAME_DAILY_CHALLENGE_TOTAL_PROGRESS_BAR);
	this->totalProgressSprite->setVisible(false);
	this->addChild(this->totalProgressSprite);

	this->totalProgress = ProgressTimer::create(this->totalProgressSprite);
	this->totalProgress->setPosition(bgProgress->getPosition() - Vec2(1.5f, 0));
	this->totalProgress->setType(ProgressTimerType::BAR);
	this->totalProgress->setMidpoint(Vec2(0, 0));
	this->totalProgress->setBarChangeRate(Vec2(1, 0));
	this->totalProgress->setPercentage(0);
	this->addChild(totalProgress);

	Vec2 centerPos = bg->getPosition() + Vec2(-33, bg->getContentSize().height / 8.1f);
	float xDistance = bgProgress->getContentSize().width / 4.8f;
	vector<Vec2> aPos = {
		Vec2(centerPos - Vec2(2 * xDistance, 0)),
		Vec2(centerPos - Vec2(xDistance, 0)),
		Vec2(centerPos),
		Vec2(centerPos + Vec2(xDistance, 0)),
		Vec2(centerPos + Vec2(2.18f * xDistance, 0))
	};

	this->btnCollect = GameSlot::CSpriteButton::createButtonWithSpriteFrameName(
		StringUtils::format(FRAME_DAILY_CHALLENGE_COLLECT_BUTTON_FORMAT, 1),
		nullptr,
		CC_CALLBACK_0(DailyChallengePopup::collect, this)
	);
	this->btnCollect->setPosition(aPos[4]);
	this->btnCollect->setVisible(false);
	this->addChild(this->btnCollect);

	for (int i = 0; i < 5; ++i) {
		auto txt = Label::createWithTTF(ToString(i + 1), FONT_PassionOne_Regular, 40);
		txt->setPosition(aPos[i]);
		txt->setHorizontalAlignment(TextHAlignment::CENTER);
		this->txtCollect = txt;
		this->addChild(txt);
	}

	this->oContent = ui::ListView::create();
	this->oContent->setCascadeOpacityEnabled(true);
	this->oContent->setDirection(ui::ScrollView::Direction::VERTICAL);
	this->oContent->setTouchEnabled(true);
	this->oContent->setScrollBarEnabled(false);
	this->oContent->setBounceEnabled(true);
	this->oContent->setContentSize(Size(bg->getContentSize().width, bg->getContentSize().height * 1.95f / 5.0f));
	this->oContent->setClippingEnabled(true);
	this->oContent->setPosition(bg->getPosition() - Vec2(bg->getContentSize().width * 19.1f / 40.0f, bg->getContentSize().height * 1 / 50.0f));
	this->oContent->setAnchorPoint(Vec2(0, 1));
	this->oContent->setItemsMargin(5);
	this->oContent->setGravity(ui::ListView::Gravity::CENTER_VERTICAL);
	this->oContent->setSwallowTouches(false);
	this->addChild(this->oContent);

	auto scrollDownBtn = GameSlot::CSpriteButton::createButtonWithSpriteFrameName(
		FRAME_DAILY_CHALLENGE_DROP_DOWN,
		nullptr,
		[this]() {
		this->oContent->scrollToBottom(0.5f, true);
	});
	scrollDownBtn->setPosition(bg->getPosition() - Vec2(0, bg->getContentSize().height / 2.175f));
	this->addChild(scrollDownBtn);

	for (int i = 0; i < 5; ++i) {
		auto cat = DailyChallengeTaskUI::create();
		this->oContent->pushBackCustomItem(cat);
	}

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(Vec2(
		bg->getPositionX() + bg->getContentSize().width / 2,
		bg->getPositionY() + bg->getContentSize().height / 2.2f
	));
	this->addChild(closeBtn);

	return true;
}

void DailyChallengePopup::prepareAndShow(cocos2d::Node * parent, bool forceShowAfterResleaseScene)
{
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(parent);
	InfoManager::getInstance()->reloadDailyChallengeInfo([this, parent, forceShowAfterResleaseScene](bool isSuccess, DailyChallengeInfo* result) {
		if (isSuccess) {
			this->reloadUI(result);

			BasePopup::showWithQueue(parent, forceShowAfterResleaseScene);
		}
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	});
}

float DailyChallengePopup::getMinRatioPopup() {
	return 0.6*ScaleManager::getInstance()->getExactlyScaleDownRatio();
}

float DailyChallengePopup::getMaxRatioPopup() {
	return ScaleManager::getInstance()->getExactlyScaleDownRatio();
}

void DailyChallengePopup::reloadUI(DailyChallengeInfo * result)
{
	this->txtCoin->setString(UtilFunction::FormatWithCommas(result->coinReward) + " ");
	this->txtCrown->setString(" + " + UtilFunction::FormatWithCommas(result->crownReward) + " ");

	int totalCompleted = 0;

	auto config = InfoManager::getInstance()->getDailyChallengeConfig();
	int curItemSize = this->oContent->getItems().size();
	int j = 0;
	for(auto info : result->listTask){
		if (config.find(info->configID) != config.end()) {
			bool completed = false;
			if (j < curItemSize) {
				completed = ((DailyChallengeTaskUI*)this->oContent->getItem(j))->updateInfo(info);
			}
			else {
				auto cat = DailyChallengeTaskUI::create();
				completed = cat->updateInfo(info);
				this->oContent->pushBackCustomItem(cat);
			}
			if (completed) totalCompleted++;
			++j;
		}
	}

	while (j < this->oContent->getItems().size()) {
		this->oContent->removeLastItem();
	}

	this->oContent->jumpToTop();

	this->reloadTotalProgress(result, totalCompleted);
}

void DailyChallengePopup::reloadTotalProgress(DailyChallengeInfo * info, int totalComplete)
{
	if (info->canCollect) {
		this->totalProgress->setColor(Color3B::WHITE);
		this->btnCollect->setVisible(true);
		((GameSlot::CSpriteButton*)this->btnCollect)->setTouchEnabled(true);
		FiniteTimeAction* anim = AnimationHelper::getInstance()->createAnimationByFrameName(
			PLIST_DAILY_CHALLENGE,
			FRAME_DAILY_CHALLENGE_COLLECT_BUTTON_FORMAT,
			1,
			8,
			20,
			1);
		this->btnCollect->runAction(RepeatForever::create(
			Sequence::createWithTwoActions(
				anim,
				anim->reverse()
		)));
		this->txtCollect->setString(Language(txtCollect,LanguageConstant::COLLECT));
		this->txtCollect->setTextColor(Color4B(217, 255, 83, 255));
		this->txtCollect->enableOutline(Color4B(0, 255, 255, 75), 4);
	} else {
		this->totalProgress->setColor(totalComplete < 5 ? Color3B::WHITE : Color3B::GRAY);
		this->btnCollect->stopAllActions();
		this->btnCollect->setVisible(false);
		this->txtCollect->setString("5");
		this->txtCollect->setTextColor(Color4B::WHITE);
		this->txtCollect->disableEffect(LabelEffect::OUTLINE);
	}

	switch (totalComplete) {
	case 0:
		this->totalProgress->setPercentage(0);
		break;
	case 1:
		this->totalProgress->setPercentage(7600 / 1158.0f);
		break;
	case 2:
		this->totalProgress->setPercentage(32800 / 1158.0f);
		break;
	case 3:
		this->totalProgress->setPercentage(57800 / 1158.0f);
		break;
	case 4:
		this->totalProgress->setPercentage(83100 / 1158.0f);
		break;
	case 5:
	default:
		this->totalProgress->setPercentage(100);
		break;
	}
}

void DailyChallengePopup::collect()
{
	if (!InfoManager::getInstance()->getDailyChallengeInfo()->canCollect) return;

	((GameSlot::CSpriteButton*)this->btnCollect)->setTouchEnabled(false);
	NetworkManager::getInstance()->collectDailyChallenge(
		[this](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString) {
		if (coreResultCode == RESULT_CODE_VALID) {
			auto info = InfoManager::getInstance()->getDailyChallengeInfo();
			info->canCollect = false;
			PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCoin(info->coinReward);
			PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCrown(info->crownReward);
			AnimationCoinCrown::create(
				Helper4Scene::getRunningScene(),
				this->btnCollect->getPosition(),
				info->coinReward
			);
			AnimationCoinCrown::create(
				Helper4Scene::getRunningScene(),
				this->btnCollect->getPosition(),
				info->crownReward,
				AnimationType::CrownAnimation
			);
			this->reloadTotalProgress(info, 5);
		}
		else {
			NetworkFailProcessInfo info;
			info.core_result_code = coreResultCode;
			StrategyManager::getInstance()->handleFailResultNewStrategy(info, false, true);
			((GameSlot::CSpriteButton*)this->btnCollect)->setTouchEnabled(true);
		}
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	},
		[this](std::string result) {
		NetworkFailProcessInfo info;
		info.errorMessage = result;
		StrategyManager::getInstance()->handleFailResultNewStrategy(info, false, false);
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		((GameSlot::CSpriteButton*)this->btnCollect)->setTouchEnabled(true);
	},
		[this](std::string result) {
		NetworkFailProcessInfo info;
		info.errorMessage = result;
		StrategyManager::getInstance()->handleFailResultNewStrategy(info, false, false);
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		((GameSlot::CSpriteButton*)this->btnCollect)->setTouchEnabled(true);
	});
}

DailyChallengeTaskUI * DailyChallengeTaskUI::create()
{
	DailyChallengeTaskUI* taskUI = new DailyChallengeTaskUI();
	if (taskUI->init()) {
		taskUI->autorelease();

		return taskUI;
	}

	CC_SAFE_RELEASE_NULL(taskUI);
}
bool DailyChallengeTaskUI::init()
{
	if (!ui::Layout::init()) return false;
	this->setCascadeOpacityEnabled(true);

	auto bg = Sprite::createWithSpriteFrameName(FRAME_DAILY_CHALLENGE_ROW_BG);
	bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	bg->setCascadeOpacityEnabled(true);
	this->addChild(bg);

	icon = Sprite::createWithSpriteFrameName(FRAME_DAILY_CHALLENGE_ICON_LEVEL_UP);
	icon->setPosition(Vec2(30, 0));
	icon->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	icon->setScale(0.4f);
	bg->addChild(icon);

	text = Label::createWithTTF("", FONT_PassionOne_Regular, 38);
	text->setHorizontalAlignment(TextHAlignment::CENTER);
	text->setPosition(Vec2(bg->getContentSize().width / 3.5f, bg->getContentSize().height / 2));
	text->enableOutline(Color4B(102, 21, 114, 125), 6);
	bg->addChild(text);

	//progress bg
	auto oProgressBG = Sprite::createWithSpriteFrameName(FRAME_DAILY_CHALLENGE_PROGRESS_BG);
	oProgressBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	oProgressBG->setPosition(Vec2(bg->getContentSize().width / 2.0f, bg->getContentSize().height / 2));
	bg->addChild(oProgressBG);

	auto progress = CCSprite::createWithSpriteFrameName(FRAME_DAILY_CHALLENGE_PROGRESS_BAR);
	progress->setVisible(false);
	this->addChild(progress);
	//progress bar
	this->progress = ProgressTimer::create(progress);
	this->progress->setType(ProgressTimer::Type::BAR);
	this->progress->setMidpoint(Vec2(0, 0.5f));
	this->progress->setBarChangeRate(Vec2(1, 0));
	this->progress->setPosition(oProgressBG->getPosition() + Vec2(oProgressBG->getContentSize().width / 2, 0));
	this->progress->setPercentage(0);
	bg->addChild(this->progress);

	//progress text
	progressTxt = Label::createWithTTF("0%", FONT_PassionOne_Regular, 28);
	progressTxt->setPosition(this->progress->getPosition());
	bg->addChild(progressTxt);

	this->setContentSize(bg->getContentSize());

	return true;
}
bool DailyChallengeTaskUI::updateInfo(DailyChallengeTask * taskInfo)
{
	string frame = "";
	string infoText = "";

	switch ((LobbyConstant::DailyChallengeTypeID)taskInfo->configID)
	{
	case LobbyConstant::LEVEL_UP:
		frame = FRAME_DAILY_CHALLENGE_ICON_LEVEL_UP;
		infoText = "Level up";
		break;
	case LobbyConstant::RECEIVE_GIFT:
		frame = FRAME_DAILY_CHALLENGE_ICON_RECEIVE_GIFT;
		infoText = "Receive gift from 5 friends";
		break;
	case LobbyConstant::SEND_GIFT:
		frame = FRAME_DAILY_CHALLENGE_ICON_SEND_GIFT;
		infoText = "Send gift to 5 friends";
		break;
	case LobbyConstant::COLLECT_FREE_COIN_GIFT:
		frame = FRAME_DAILY_CHALLENGE_ICON_COLLECT;
		infoText = "Collect time bonus 10 times";
		break;
	case LobbyConstant::SPIN:
		frame = FRAME_DAILY_CHALLENGE_ICON_SPIN;
		infoText = "Spin 100 times";
		break;
	case LobbyConstant::MAX_BET:
		frame = FRAME_DAILY_CHALLENGE_ICON_MAX_BET;
		infoText = "Max bet 20 times";
		break;
	case LobbyConstant::BIG_WIN:
		frame = FRAME_DAILY_CHALLENGE_ICON_BIG_WIN;
		infoText = "Big win 20 times";
		break;
	case LobbyConstant::MEGA_WIN:
		frame = FRAME_DAILY_CHALLENGE_ICON_MEGA_WIN;
		infoText = "Mega win 10 times";
		break;
	case LobbyConstant::TOTAL_BET:
		frame = FRAME_DAILY_CHALLENGE_ICON_TOTAL_BET;
		infoText = "Total bet 100,000";
		break;
	case LobbyConstant::TOTAL_WIN:
		frame = FRAME_DAILY_CHALLENGE_ICON_TOTAL_WIN;
		infoText = "Total win 100,000";
		break;
	default:
		break;
	}

	auto goal = InfoManager::getInstance()->getDailyChallengeConfig()[taskInfo->configID].goal;
	float percent = min(100.0, taskInfo->currentProgress * 100.0f / goal);

	icon->setSpriteFrame(frame);
	text->setString(infoText);
	progress->setPercentage(percent);
	progressTxt->setString(ToString((int)percent) + "%");

	return taskInfo->currentProgress >= goal;
}