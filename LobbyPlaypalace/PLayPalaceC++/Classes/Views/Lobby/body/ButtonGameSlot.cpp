#include "ButtonGameSlot.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Configs.h"
#include "Constant/Defination.h"
#include "Constant/LanguageConstant.h"
#include "Constant/PPEnums.h"
#include "Util/UtilFunction.h"
#include "Scene/LobbyScene.h"
#include "Views/Popup/NotificationPopup.h"

#include "Manager/InfoManager.h"
#include "Manager/LanguageManager.h"
#include "Manager/PopupManager.h"

#include "Manager/FileManager/SlotsGameDownloadFileManager.h"

#include "Views/Effects/CrownFlareWithLensFlare.h"
#include "Helper/Helper4Sprite.h"


USING_NS_CC;

ButtonGameSlot* ButtonGameSlot::create(
	LobbyScene* lobbyScene,
	const std::string& normalImage,
	ServerSlotGameInfo* gameInfo,
	const std::string& selectedImage,
	const std::string& disableImage,
	TextureResType texType) {
	ButtonGameSlot *btn = new (std::nothrow) ButtonGameSlot;
	btn->gameInfo = gameInfo;
	btn->lobbyScene = lobbyScene;
	if (btn && btn->init(normalImage, selectedImage, disableImage, texType))
	{
		btn->autorelease();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}
/// <summary>
/// remove callback for downloading game slot avoid crash problem
/// </summary>
ButtonGameSlot::~ButtonGameSlot() {
	removeCallback4Downloading();
}

bool ButtonGameSlot::init(const std::string& normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	ui::Widget::TextureResType texType) 
{

	if (!ui::Button::init(normalImage, selectedImage, disableImage, texType))
	{
		return false;
	}

	currentState = Download;

	std::string fontName = UtilFunction::getFontNameFromLanguage();

	//STATUS LABEL
	this->statusLabel = LabelAutoSize::createWithTTF(
		//LanguageManager::getInstance()->getStringForKeys(LanguageConstant::BODY_SLOT_GAME_COMING_SOON)
		"",
		fontName,
		30
	);

	((LabelAutoSize*)this->statusLabel)->setTextAreaSize(Size(this->getContentSize().width * 0.68f, 50));
	this->statusLabel->setTextColor(Color4B::WHITE);
	this->statusLabel->setZOrder(1);
	this->addScaleNode(this->statusLabel);
	this->getScaleNode()->setPosition(_contentSize.width / 2, _contentSize.height / 2.6f);

	//PANEL LAYER COLOR FOR STATUS LABEL
	this->backgroundStatusLabel = DrawNode::create();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(-this->getContentSize().width * 0.35f, -25);
	rectangle[1] = Vec2(this->getContentSize().width * 0.35f, -25);
	rectangle[2] = Vec2(this->getContentSize().width * 0.35f, +25);
	rectangle[3] = Vec2(-this->getContentSize().width * 0.35f, +25);

	Color4F tranBlack(0, 0, 0, 0.5);
	this->backgroundStatusLabel->drawPolygon(rectangle, 4, tranBlack, 0, tranBlack);
	this->addScaleNode(this->backgroundStatusLabel);

	//LOCK SPRITE
	this->lockSprite = Helper4Sprite::createOptimizeSprite(PNG_LOCK_ICON);
	this->lockSprite->setPosition(this->getContentSize().width / 2 * 0.5f, -this->getContentSize().height / 2 * 0.5f);
	this->lockSprite->setScale(0.8f);
	this->addScaleNode(this->lockSprite);

// DOWNLOAD PROPRESS UI START

	//DOWNLOAD SPRITE
	this->downloadSprite = Helper4Sprite::createOptimizeSprite(PNG_DOWNLOAD_ICON);
	this->downloadSprite->setPosition(this->lockSprite->getPosition());
	this->downloadSprite->setScale(this->lockSprite->getScale());
	this->addScaleNode(this->downloadSprite);
	
	downloadingProgressGroup = Node::create();
	downloadingProgressGroup->setPosition(this->statusLabel->getPosition());
	this->addScaleNode(downloadingProgressGroup);

	// Downloading Text BG
	auto bgDownloadingText = Helper4Sprite::createOptimizeSprite(PNG_PROGRESS_DOWNLOAD_SLOT_TEXT_BG);
	bgDownloadingText->setAnchorPoint(Vec2(0.5, 0.5));
	bgDownloadingText->setPosition(Vec2(0,0));
	downloadingProgressGroup->addChild(bgDownloadingText);

	// Downloading progress BG
	auto downloadProgressBG = Helper4Sprite::createOptimizeSprite(PNG_PROGRESS_DOWNLOAD_SLOT_BG);
	downloadProgressBG->setPosition(
		83,
		-108);
	downloadProgressBG->setScale(0.38f);
	downloadProgressBG->setAnchorPoint(Vec2(0.5,0.5));
	downloadingProgressGroup->addChild(downloadProgressBG);

	// Downloading progress
	downloadingProgress = CCProgressTimer::create(CCSprite::create(PNG_PROGRESS_DOWNLOAD_SLOT));
	if (downloadingProgress != NULL)
	{
		downloadingProgress->setType(kCCProgressTimerTypeBar);
		downloadingProgress->setScale(downloadProgressBG->getScale());
		downloadingProgress->setMidpoint(ccp(0, 0));
		downloadingProgress->setBarChangeRate(ccp(1, 0));
		downloadingProgress->setPercentage(0);
		downloadingProgress->setPosition(downloadProgressBG->getPosition());
		downloadingProgressGroup->addChild(downloadingProgress);
	}

// DOWNLOAD PROGRESS UI FINISH

	//CROWN ANIMATION
	if (this->gameInfo->minCrown > 0)
	{
		auto crownIcon = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_CROWN_SLOT_ICON);
		crownIcon->setPosition(Vec2(-83, 117));
		//crownIcon->setRotation(-20);
		this->addScaleNode(crownIcon);

		auto crownAnimation = CrownFlareWithLensFlare::create();
		crownAnimation->setPosition(crownIcon->getContentSize() / 2);
		crownAnimation->resetAndPlay();
		crownIcon->addChild(crownAnimation);
	}

	return true;
}



/// <summary>
/// Update Download Progress By Dat
/// </summary>
/// <param name="progress">from 0->1</param>
/// <param name="isFinish">is finish downloading</param>
/// <param name="isFail">is download fail when finish</param>
void ButtonGameSlot::updateDownloadProgress(float progress, bool isFinish, bool isFail) {
	if (lobbyScene == nullptr) {
		return;
	}
	if (isFinish) {
		//currentState = Unzipping;
		//this->scheduleOnce([=](float dt) {
			if (!isFail) {
				currentState = CanPlay;
			}
			else {

				currentState = Download;
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
					lobbyScene,
					"Download failed",
					"Do you want to retry download?",
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "stop"),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "download"),
					"",
					[=]() {
					// stop download
						currentState = Download;
						checkStateAndUpdateUI();
					},
					[=]() {
					// redownload
						startDownloadGameSlotInGameBG();
					}

				);
			}
			checkStateAndUpdateUI();
		//}, 2.0f,ToString(gameInfo->orderId));
	}else {

		if (progress > 1) {
			progress = 1;
		}
		if (downloadingProgress->getActionByTag(100) == nullptr) {
			ProgressTo * moveProgress = ProgressTo::create(0.1, progress * 100);
			moveProgress->setTag(100);
			downloadingProgress->runAction(moveProgress);
		}
		//downloadingProgress->setPercentage(progress * 100);


		UtilFunction::setFontForLabel(statusLabel, FONT_PassionOne_Regular, 30, false);
		std::string progressStr = StringUtils::format("%i", (int)(progress * 100)) + "%";
		statusLabel->setString(progressStr);
	}
}

void ButtonGameSlot::checkPreviousDownload() {
	if (currentState != Download) {
		return;
	}
	if (SlotsGameDownloadFileManager::getInstance()->isGameDownloading(gameInfo->gameIdLocal)) {
		this->currentState = ButtonGameSlotState::Downloading;

		SlotsGameDownloadFileManager::getInstance()->downloadSlotGameInMainUI(
			gameInfo->gameIdLocal,gameInfo->newestVersion,
			CC_CALLBACK_3(ButtonGameSlot::updateDownloadProgress, this));
	}

	checkStateAndUpdateUI();
}


void ButtonGameSlot::checkStateAndUpdateUI()
{
	if (!this->gameInfo) {
		return;
	}
	//CHECK AND SET STATE
	if (!UtilFunction::isAvailableGameSlot((ppEnum::GameSlotOrderId)this->gameInfo->orderId))
	{
		this->currentState = ButtonGameSlotState::ComingSoon;
	}
	else if (InfoManager::getInstance()->getUserInfo()->level + 1 < this->gameInfo->minLevel)
	{
		this->currentState = ButtonGameSlotState::Locked;
	}
	else if(SlotsGameDownloadFileManager::getInstance()->isGameInCache(gameInfo->gameIdLocal))
	{
		this->currentState = ButtonGameSlotState::CanPlay;
	}

	//UPDATE UI
	switch (currentState)
	{
	case CanPlay:
	{
		this->getScaleNode()->setVisible(false);
		this->statusLabel->setVisible(false);
		this->backgroundStatusLabel->setVisible(false);
		downloadingProgressGroup->setVisible(false);
		break;
	}
	case Locked:
	{
		UtilFunction::setLabelFontByLanguage(statusLabel);
		std::string statusString = LanguageManager::getInstance()->getStringForKeys(nullptr,LanguageConstant::POPUP_USER_GAME_UNLOCK, "text4") + " - " +
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_USER_GAME_UNLOCK, "text1") + " " + StringUtils::toString(gameInfo->minLevel);
		this->statusLabel->setString(statusString);
		
		this->getScaleNode()->setVisible(true);
		this->statusLabel->setVisible(true);
		this->backgroundStatusLabel->setVisible(true);
		downloadingProgressGroup->setVisible(false);

		this->downloadSprite->setVisible(false);
		this->lockSprite->setVisible(true);
		break;
	}
	case ComingSoon:
	{
		this->statusLabel->setString(LanguageManager::getInstance()->getStringForKeys(statusLabel,LanguageConstant::BODY_SLOT_GAME_COMING_SOON));
		
		this->getScaleNode()->setVisible(true);
		this->statusLabel->setVisible(true);
		this->backgroundStatusLabel->setVisible(true);
		downloadingProgressGroup->setVisible(false);

		this->downloadSprite->setVisible(false);
		this->lockSprite->setVisible(true);
		break;
	}
	case Download:
	{
		this->getScaleNode()->setVisible(true);
		this->statusLabel->setVisible(false);
		this->backgroundStatusLabel->setVisible(false);
		downloadingProgressGroup->setVisible(false);

		this->downloadSprite->setVisible(true);
		this->lockSprite->setVisible(false);
		break;
	}
	case Downloading:
	{
		this->getScaleNode()->setVisible(true);
		this->statusLabel->setVisible(false);
		this->backgroundStatusLabel->setVisible(false);
		downloadingProgressGroup->setVisible(true);

		this->downloadSprite->setVisible(true);
		this->lockSprite->setVisible(false);
		this->statusLabel->setVisible(true);
		break;
	}
	default:
		break;
	}
	//downloadingProgressGroup->setVisible(true);

}

void ButtonGameSlot::startDownloadGameSlotInGameBG() {
	this->currentState = ButtonGameSlotState::Downloading;
	checkStateAndUpdateUI();
	
	SlotsGameDownloadFileManager::getInstance()->downloadSlotGameInMainUI(
		gameInfo->gameIdLocal,
		gameInfo->newestVersion,
		CC_CALLBACK_3(ButtonGameSlot::updateDownloadProgress, this));
}

void ButtonGameSlot::removeCallback4Downloading() {
	if (this->currentState != ButtonGameSlotState::Downloading) {
		return;
	}
	SlotsGameDownloadFileManager::getInstance()->downloadSlotGameInMainUI(
		gameInfo->gameIdLocal,gameInfo->newestVersion,nullptr);
}

bool ButtonGameSlot::isGameCanCancelDownload() {
	return SlotsGameDownloadFileManager::getInstance()->isGameCanCancelDownload(
		gameInfo->gameIdLocal);
}

void ButtonGameSlot::cancelDownloadGameSlot() {
	if (SlotsGameDownloadFileManager::getInstance()->cancelGameSlotWithGameIdInDownloadingQueue(
		gameInfo->gameIdLocal)) {
		this->currentState = ButtonGameSlotState::Download;
		checkStateAndUpdateUI();
	}
}
void ButtonGameSlot::updateAfterChangeLanguage()
{
	UtilFunction::setLabelFontByLanguage(this->statusLabel);
	this->checkStateAndUpdateUI();
}

/// <summary>
/// By dat
/// cancel download game slot
/// </summary>
/// <returns></returns>
void ButtonGameSlot::removeGameSlot() {
	SlotsGameDownloadFileManager::getInstance()->removeGameSlotWithGameId(gameInfo->gameIdLocal);
	this->currentState = ButtonGameSlotState::Download;
	checkStateAndUpdateUI();
}


bool ButtonGameSlot::fileIsExpireByVersion() {
	if (gameInfo->orderId == ppEnum::GameSlotOrderId::NEZHA) return false;
	return SlotsGameDownloadFileManager::getInstance()->fileIsExpireByVersion(gameInfo->gameIdLocal,gameInfo->newestVersion);
}
