#include "DailyLuckySpinPopup.h"
#include "DailyLuckySpinInfoPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/StrategyManager.h"
#include "Manager/PopupManager.h"
#include "Manager/SoundManager.h"
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


bool DailyLuckySpinPopup::init()
{
	if (!BasePopup::init()) return false;

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_DAILY_LUCKY_SPIN);

	this->infoPopup = DailyLuckySpinInfoPopup::create();
	this->addChild(this->infoPopup, 1);

	auto bg = Sprite::createWithSpriteFrameName(FRAME_DAILY_LUCKY_SPIN_BG);
	bg->setPosition(origin + visibleSize / 2);
	this->addChild(bg);

	auto title = Sprite::createWithSpriteFrameName(FRAME_DAILY_LUCKY_SPIN_TITLE);
	title->setPosition(bg->getPosition() + Vec2(0, bg->getContentSize().height * 0.45f));
	this->addChild(title);

	auto reelBG = Sprite::createWithSpriteFrameName(FRAME_DAILY_LUCKY_SPIN_BG_REEL);
	reelBG->setPosition(bg->getPosition() - Vec2(bg->getContentSize().width * 1 / 7.0f, 0));
	this->addChild(reelBG);

	this->spinMachine = CSpinMachine::create(
		SpinMachineCellType::LABEL,
		{"0" ,"1" ,"2" ,"3" ,"4" ,"5" ,"6" ,"7" ,"8" ,"9" },
		1,
		3,
		reelBG->getContentSize().width / 3.2f,
		reelBG->getContentSize().height / 1.3f,
		SpinMachineLabelType(FONT_BITMAP_LEVELUP, SpinMachineLabelType::BMFONT, 50),
		SpinMachineSpriteType::LOCAL,
		1,
		1
	);
	this->spinMachine->setPosition(reelBG->getPosition() + Vec2(-this->spinMachine->getContentSize().width * 1 / 3, 5));
	this->spinMachine->setMinStepStop(50);
	this->spinMachine->setStepDelayStopBetweenCol(20);
	this->spinMachine->setCellOffsetPos(Vec2(0, 50));
	this->addChild(this->spinMachine);

	auto maskReel = Sprite::createWithSpriteFrameName(FRAME_DAILY_LUCKY_SPIN_MASK_REEL);
	maskReel->setPosition(reelBG->getPosition() + Vec2(0, 7));
	this->addChild(maskReel);

	this->btn = GameSlot::CSpriteButton::createButtonWithSpriteFrameName(
		StringUtils::format(FRAME_DAILY_LUCKY_SPIN_BUTTON_FORMAT, 1),
		nullptr,
		CC_CALLBACK_0(DailyLuckySpinPopup::onSpin, this));
	((GameSlot::CSpriteButton*)this->btn)->setScaleEvent(0.9f);
	this->btn->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width * 1 / 3.25f, 0));
	this->addChild(this->btn);

	auto infoBtn = GameSlot::CSpriteButton::createButtonWithSpriteFrameName(PNG_FRAME_SHOP_INFO_BTN,
		nullptr,
		[this]() mutable {
		this->infoPopup->prepareAndShow(this);
	});
	infoBtn->setScale(1.2f);
	infoBtn->setScaleEvent(1.1f, 1.2f);
	infoBtn->setPosition(bg->getPosition() + Vec2(bg->getContentSize().width * 0.43f, -bg->getContentSize().height * 0.325f));
	this->addChild(infoBtn);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + bg->getContentSize().width / 2.075f,
		origin.y + visibleSize.height / 2 + bg->getContentSize().height / 2.25f
	));
	this->addChild(closeBtn);

	return true;
}

void DailyLuckySpinPopup::setBtnEnabled(bool isEnable)
{
	this->btn->setColor(isEnable ? Color3B::WHITE : Color3B::GRAY);
	((GameSlot::CSpriteButton*)this->btn)->setTouchEnabled(isEnable);
}

void DailyLuckySpinPopup::onSpin()
{
	if (!this->info->canCollect) return;

	((GameSlot::CSpriteButton*)this->btn)->setTouchEnabled(false);

	this->btn->runAction(Sequence::createWithTwoActions(
		AnimationHelper::getInstance()->createAnimationByFrameName(
			PLIST_DAILY_LUCKY_SPIN,
			FRAME_DAILY_LUCKY_SPIN_BUTTON_FORMAT,
			1,
			21,
			30.0f,
			1),
		CallFunc::create([this]() {
		this->setBtnEnabled(false);
	})));

	int result = RESULT_CODE_VALID;

	NetworkManager::getInstance()->collectDailyBonusLuckySpin(
		[this, result](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString) mutable {
		result = coreResultCode;
		if (coreResultCode == RESULT_CODE_VALID) {
			this->info->updateInfoByValue(responseAsDocument);
			if (!this->info->reelValues.empty()) {
				std::vector<std::string> value = Helper4String::splitString(this->info->reelValues, ",");
				this->spinMachine->stopSpin({ { value[0] }, { value[1] }, { value[2] } });
			}
		}
		else {
			NetworkFailProcessInfo failInfo;
			failInfo.core_result_code = coreResultCode;
			StrategyManager::getInstance()->handleFailResultNewStrategy(failInfo, true, false);
		}
	});

	SoundManager::getInstance()->playSoundEffectLuckySpinStart();
	this->spinMachine->startSpin([this](int col) {
		SoundManager::getInstance()->playSoundEffectLuckySpinReelStop();
	},
		[this, result]() {
		SoundManager::getInstance()->playSoundEffectLuckySpinStop();
		if (result == RESULT_CODE_VALID) {
			PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp();
			Vec2 pos = this->spinMachine->getPosition() + Vec2(this->spinMachine->getContentSize().width / 3, 0);
			if (info->coinReward > 0) {
				AnimationCoinCrown::create(Helper4Scene::getRunningScene(), pos, info->coinReward, AnimationType::CoinAnimation);
			}
			if (info->crownReward > 0) {
				AnimationCoinCrown::create(Helper4Scene::getRunningScene(), pos, info->crownReward, AnimationType::CrownAnimation);
			}
		}
	});
}

void DailyLuckySpinPopup::prepareAndShow(cocos2d::Node * parent)
{
	this->spinMachine->refreshData({ { "8" },{ "8" } ,{ "8" } });
	this->setBtnEnabled(true);

	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(parent);
	InfoManager::getInstance()->reloadAdditionalInfo([this](bool isSuccess, AdditionalInfo* result) {
		this->info = InfoManager::getInstance()->getAdditionalInfo()->dailyBonusLuckySpinInfo;
		this->setBtnEnabled(this->info->canCollect);
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	});

	BasePopup::showWithQueue(parent);
}
