#include "BottomItem.h"
#include "Info/AdditionalInfo.h"
#include "Constant/LanguageConstant.h"
#include "Constant/Defination.h"

#include "Custom/Common/LabelAutoSize.h"

#include "Helper/Helper4Time.h"
#include "Helper/Helper4String.h"
#include "Helper/Helper4ParseJSON.h"
#include "Helper/AnimationHelper.h"
#include "Helper/Helper4Scene.h"

#include "Manager/InfoManager.h"
#include "Manager/LanguageManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"

#include "Views/Effects/AnimationCoinCrown.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Lobby/body/BodyLobbyLayout.h"
#include "Helper/Helper4Sprite.h"


USING_NS_CC;
using namespace GameSlot;

BottomItem::BottomItem() : ui::Widget()
{
}

BottomItem * BottomItem::create(
	const std::string & animFormat,
	int startFrame, int endFrame,
	const std::string & labelFrameName,
	const std::function<void(BottomItem* sender)>& cb,
	bool bHasLock, 
	bool bHasNoti)
{
	auto item = BottomItem::create();

	if (item) {
		item->initWithData(animFormat, startFrame, endFrame, labelFrameName, bHasLock, bHasNoti);
		item->cb = cb;
	}

	return item;
}

bool BottomItem::init()
{
	if (ui::Widget::init())
	{
		auto bg = ui::ImageView::create(FRAME_BOTTOM_ICON_BG, ui::Widget::TextureResType::PLIST);
		bg->setPosition(bg->getContentSize() / 2);
		this->addChild(bg);

		this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		this->setContentSize(bg->getContentSize());
		return true;
	}
	return false;
}

bool BottomItem::initWithData(
	const std::string& animFormat,
	int startFrame, int endFrame,
	const std::string& labelFrameName,
	bool bHasLock,
	bool bHasNoti)
{
	this->animFormat = animFormat;
	this->startFrame = startFrame;
	this->endFrame = endFrame;

	this->sprtSymbol = Sprite::createWithSpriteFrameName(StringUtils::format(animFormat.c_str(), startFrame));
	this->sprtSymbol->setPosition(this->getContentSize().width / 3, this->getContentSize().height / 1.8f);

	this->sprtLabel = Sprite::createWithSpriteFrameName(labelFrameName);
	this->sprtLabel->setPosition(this->getContentSize().width * 2 / 3, this->sprtSymbol->getPositionY());

	this->addChild(this->sprtSymbol);
	this->addChild(this->sprtLabel);

	if (bHasLock) {
		this->sprtLockMask = Sprite::createWithSpriteFrameName(FRAME_BOTTOM_LOCK_MASK);
		this->sprtLockMask->setCascadeOpacityEnabled(true);
		this->sprtLockMask->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2.0f);
		this->addChild(this->sprtLockMask);

		this->sprtLock = Sprite::createWithSpriteFrameName(FRAME_BOTTOM_LOCK);
		this->sprtLock->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 1.9f);

		this->sprtLockMask->addChild(this->sprtLock);

		this->sprtLockMask->setVisible(false);
	}

	if (bHasNoti) {
		auto oNotiBG = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_RED_NOTIFICATION);
		oNotiBG->setAnchorPoint(Vec2(1, 0.5f));
		oNotiBG->setCascadeOpacityEnabled(true);
		oNotiBG->setPosition((Vec2)this->getContentSize() + Vec2(10, -10));
		this->addChild(oNotiBG);

		this->noti = Label::createWithTTF("0", FONT_PassionOne_Regular, 30);
		this->noti->setPosition(oNotiBG->getContentSize() / 2);
		this->noti->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
		oNotiBG->addChild(this->noti);

		this->reloadNoti(0);
	}

	return true;
}

void BottomItem::playAnimation()
{
	if (this->sprtSymbol && !this->animFormat.empty()) {
		this->sprtSymbol->stopAllActions();
		this->sprtSymbol->runAction(
			RepeatForever::create(
				Sequence::createWithTwoActions(
					AnimationHelper::getInstance()->createAnimationByFrameName(
						"",
						this->animFormat,
						this->startFrame,
						this->endFrame,
						30.0f,
						1),
					DelayTime::create(0.5f)
				)
			)
		);
	}
}

void BottomItem::showLock()
{
	if (this->sprtLockMask) {
		this->sprtLockMask->stopAllActions();
		this->sprtLock->stopAllActions();

		this->sprtLockMask->setOpacity(255);
		this->sprtLock->setScale(1);

		this->sprtLockMask->setVisible(true);
		this->sprtLockMask->runAction(Sequence::create(
			FadeIn::create(0.2f),
			DelayTime::create(0.4f),
			FadeOut::create(0.2f),
			CallFunc::create([this]() {
			this->sprtLockMask->setVisible(false);
		}), NULL));

		this->sprtLock->runAction(Sequence::create(
			DelayTime::create(0.2f),
			ScaleTo::create(0.1f, 1.2f),
			ScaleTo::create(0.1f, 1.0f),
			ScaleTo::create(0.1f, 1.2f),
			ScaleTo::create(0.1f, 1.0f), NULL));
	}
}

void BottomItem::reloadNoti(int noti)
{
	if (this->noti) {
		if (noti > 0) {
			this->noti->setString(ToString(noti));
			this->noti->getParent()->setVisible(true);
		}
		else {
			this->noti->getParent()->setVisible(false);
		}
	}
}

void BottomItem::setElementsPos(const cocos2d::Vec2 & symbolPos, const cocos2d::Vec2 & labelPos)
{
	if (this->sprtSymbol) {
		this->sprtSymbol->setPosition(symbolPos);
	}
	if (this->sprtLabel) {
		this->sprtLabel->setPosition(labelPos);
	}
}

FreeCoinGiftItem::FreeCoinGiftItem()
{
	freeCoinGiftBonus = nullptr;
}

bool FreeCoinGiftItem::init()
{
	if (!BottomItem::init()) return false;

	this->oParticle = ParticleSystemQuad::create(PARTICLE_FCG);
	this->oParticle->setPositionType(ParticleSystem::PositionType::GROUPED);
	this->oParticle->setPosition(this->getContentSize() / 2);
	this->addChild(this->oParticle);

	this->oTitle = LabelAutoSize::createWithTTF(
		Language(nullptr, LanguageConstant::FOOTER_COLLECT_LABLE),
		FONT_PassionOne_Bold,
		30
	);
	Language(oTitle, LanguageConstant::FOOTER_COLLECT_LABLE);
	((LabelAutoSize*)this->oTitle)->setTextAreaSize(Size(this->getContentSize().width * 0.8f, 50));
	this->oTitle->enableShadow();
	this->oTitle->setTextColor(Color4B(234, 201, 11, 255));
	this->oTitle->setPosition((Vec2)this->getContentSize() / 2 + Vec2(0, 35));
	this->addChild(this->oTitle);

	this->oInfo = LabelAutoSize::createWithTTF(
		"8,000",
		FONT_PassionOne_Bold,
		40
	);
	((LabelAutoSize*)this->oInfo)->setTextAreaSize(Size(this->getContentSize().width * 0.8f, 50));
	this->oInfo->enableShadow();
	this->oInfo->setTextColor(Color4B::WHITE);
	this->oInfo->setPosition((Vec2)this->getContentSize() / 2 + Vec2(0, 5));
	this->addChild(this->oInfo);

	auto progressFCGroup = Node::create();
	progressFCGroup->setPosition((Vec2)this->getContentSize() / 2 + Vec2(0, -25));
	this->addChild(progressFCGroup);

	auto bgProgress = Sprite::createWithSpriteFrameName(FRAME_BOTTOM_FCG_PROGRESS_BG);
	progressFCGroup->addChild(bgProgress);

	this->progressBar = ProgressTimer::create(CCSprite::createWithSpriteFrameName(FRAME_BOTTOM_FCG_PROGRESS_BAR));
	this->progressBar->setType(ProgressTimerType::BAR);
	this->progressBar->setMidpoint(Vec2(0, 0));
	this->progressBar->setBarChangeRate(Vec2(1, 0));
	this->progressBar->setPercentage(0);
	progressFCGroup->addChild(this->progressBar);

	auto divider1 = Sprite::createWithSpriteFrameName(FRAME_BOTTOM_FCG_PROGRESS_DIVIDE);
	divider1->setPosition(Vec2(-this->progressBar->getContentSize().width / 6, 0));
	progressFCGroup->addChild(divider1);

	auto divider2 = Sprite::createWithSpriteFrameName(FRAME_BOTTOM_FCG_PROGRESS_DIVIDE);
	divider2->setPosition(Vec2(-divider1->getPosition().x, divider1->getPosition().y));
	progressFCGroup->addChild(divider2);

	this->oCoinGroup = Node::create();
	this->oCoinGroup->setPosition(this->getContentSize() / 2);
	this->addChild(this->oCoinGroup, -1);
	for (int i = 0; i < 7; ++i) {
		auto coin = Helper4Sprite::createOptimizeSprite(PNG_SHOP_COIN_ICON);
		coin->setScale(0.5f);
		this->oCoinGroup->addChild(coin);
	}

	return true;
}

void FreeCoinGiftItem::reloadProgressBar(bool bAnim)
{
	int index = freeCoinGiftBonus->numberOfTimeCollectFreeCoin;
	float progress = index*100.0f / InfoManager::getInstance()->mapFreeCoinGiftConfig.size();
	if (progress > 100) {
		progress = 100;
	}
	// run progress bar animation
	if (bAnim) {
		this->progressBar->runAction(ProgressTo::create(0.5f, progress));
	}
	else this->progressBar->setPercentage(progress);
}

void FreeCoinGiftItem::changeState(FreeCoinGiftState state)
{
	this->state = state;
	updateUI();
}

void FreeCoinGiftItem::updateUI(){
	switch (this->state)
	{
	case FreeCoinGiftState::CountDown:
		this->oTitle->setString(Language(oTitle,LanguageConstant::FOOTER_COLLECT_TIME_BONUS_IN_LABLE));
		if (freeCoinGiftBonus) {
			this->oInfo->setString(Helper4Time::millisecondTimeToNormalTimeHourMinAndSecString(freeCoinGiftBonus->waitingTime));
		}
		this->schedule(schedule_selector(FreeCoinGiftItem::countDown), 1);
		this->setEffectWaitingCollect(false);
		break;
	case FreeCoinGiftState::WaitingForCollect:
		this->oTitle->setString(Language(oTitle,LanguageConstant::FOOTER_COLLECT_LABLE));
		if (freeCoinGiftBonus) {
			this->oInfo->setString(UtilFunction::FormatWithCommas(this->freeCoinGiftBonus->nextCoinReward));
		}
		this->unschedule(schedule_selector(FreeCoinGiftItem::countDown));
		this->setEffectWaitingCollect(true);
		break;
	case FreeCoinGiftState::Collecting:
		this->unschedule(schedule_selector(FreeCoinGiftItem::countDown));
		this->setEffectWaitingCollect(false);
		break;
	}
}

void FreeCoinGiftItem::setEffectWaitingCollect(bool bEnabled)
{
	if (bEnabled) {
		this->setEffectWaitingCollect(false);
		int i = 0;
		int iDis = 150 / this->oCoinGroup->getChildren().size();
		this->oTitle->runAction(RepeatForever::create(Sequence::createWithTwoActions(
			EaseCubicActionOut::create(ScaleTo::create(0.1f, 1.1f)),
			EaseCubicActionIn::create(ScaleTo::create(0.1f, 1.0f))
		)));
		this->oParticle->start();
		for (auto coin : this->oCoinGroup->getChildren()) {
			auto from = -75 + i * iDis;
			coin->setPositionX(RandomHelper::random_int(from, from + iDis));
			coin->scheduleOnce([coin, i, iDis](float dt) {
				int xDis = RandomHelper::random_int(-20, 20);
				coin->runAction(RepeatForever::create(
					Sequence::create(
						JumpBy::create(1.0f, Vec2(xDis, 0), 75, 1),
						CallFunc::create([coin, xDis, i, iDis]() mutable {
							auto from = -75 + i * iDis;
							coin->setPositionX(RandomHelper::random_int(from, from + iDis));
							xDis = RandomHelper::random_int(-20, 20);
				}),		DelayTime::create(1.0f),
						NULL)));
				coin->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
			}, RandomHelper::random_int(100, 120) / 100.0f, "bottom_coin_" + ToString(i++));
		}
		this->oCoinGroup->setVisible(true);
	}
	else {
		this->oCoinGroup->setVisible(false);
		this->oTitle->setScale(1.0f);
		this->oTitle->stopAllActions();
		this->oParticle->stop();
		for (auto coin : this->oCoinGroup->getChildren()) {
			coin->setPosition(Vec2::ZERO);
			coin->unscheduleAllCallbacks();
			coin->stopAllActions();
		}
	}
}

void FreeCoinGiftItem::onSelected()
{
	//PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
	//	PopupManager::getInstance()->getBodyLobbyLayout()->getParent()
	//);
	//return;
	if (this->state != FreeCoinGiftState::WaitingForCollect) return;
	this->changeState(FreeCoinGiftState::Collecting);

	NetworkManager::getInstance()->collectFreeCoinGift([this](
		int coreResultCode,
		bool isSuccess,
		rapidjson::Value &responseAsDocument,
		std::string responseAsString) {
		auto currentSceneTag = Helper4Scene::getRunningScene()->getTag();
		if (isSuccess) {
			InfoManager::getInstance()->getAdditionalInfo()->freeCoinGiftInfo->updateInfoByValue(responseAsDocument);
			if (currentSceneTag == ppEnum::GameScene::Lobby)
			{
				PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCoin(freeCoinGiftBonus->coinReward);
				Vec2 origin = Director::getInstance()->getVisibleOrigin();
				AnimationCoinCrown::create(
					Helper4Scene::getRunningScene(),
					Vec2(Director::getInstance()->getVisibleSize().width / 2+ origin.x, 78),
					freeCoinGiftBonus->coinReward
				);
				this->changeState(FreeCoinGiftState::CountDown);
				this->reloadProgressBar(true);
			}
		}
		else {
			/*NetworkFailProcessInfo networkFailInfo;
			networkFailInfo.core_result_code = coreResultCode;
			StrategyManager::getInstance()->handleFailResultNewStrategy(networkFailInfo, false, true);*/
			InfoManager::getInstance()->reloadAdditionalInfo(nullptr);
			this->changeState(FreeCoinGiftState::WaitingForCollect);
		}
	});
}

void FreeCoinGiftItem::onEnter()
{
	Node::onEnter();
	this->setEffectWaitingCollect(false);

	this->oTitle->setString("");
	this->oInfo->setString("");

	InfoManager::getInstance()->reloadAdditionalInfo([this](bool isSuccess, AdditionalInfo * result) {
		this->freeCoinGiftBonus = result->freeCoinGiftInfo;
		this->reloadProgressBar();
		if (this->freeCoinGiftBonus->canCollect) {
			this->changeState(FreeCoinGiftState::WaitingForCollect);
		}
		else {
			this->changeState(FreeCoinGiftState::CountDown);
		}
	});
}

void FreeCoinGiftItem::countDown(float dt)
{
	if (this->state != FreeCoinGiftState::CountDown) return;
	if (this->freeCoinGiftBonus->waitingTime > 0) {
		freeCoinGiftBonus->waitingTime -= (dt * 1000);
		this->oInfo->setString(Helper4Time::millisecondTimeToNormalTimeHourMinAndSecString(freeCoinGiftBonus->waitingTime));
	}
	else {
		this->changeState(FreeCoinGiftState::WaitingForCollect);
	}
}
