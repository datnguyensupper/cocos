#include "BodyLobbyLayout.h"
#include "Scene/LobbyScene.h"
#include "ButtonGameSlot.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/LanguageManager.h"
#include "Manager/ScaleManager.h"

#include "Constant/Defination.h"

#include "Views/Popup/NotificationPopup.h"

#include "AppDelegate.h"
#include "Helper/Helper4Sprite.h"

#if IS_DEBUG
/*test:testmanager*/
#include "Manager/Test/TestManager.h"
#endif

#define POSITION_Y_DOT_ICON 100
#define NUMBER_PAGE 2
USING_NS_CC;
using namespace std;

BodyLobbyLayout* BodyLobbyLayout::create(LobbyScene* parent)
{
	auto layer = BodyLobbyLayout::create();
	layer->lobbyScene = parent;
	return layer;
}
// on "init" you need to initialize your instance
bool BodyLobbyLayout::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layout::init())
	{
		return false;
	}

	return true;
}

BodyLobbyLayout::BodyLobbyLayout() {
	
}
BodyLobbyLayout::~BodyLobbyLayout() {
}

void BodyLobbyLayout::onEnter()
{
	Layout::onEnter();
	PopupManager::getInstance()->setBodyLobbyLayout(this);
}

void BodyLobbyLayout::initUI() {

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_SLOT_GAME_ICONS);

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
	float scaleUpRatio = ScaleManager::getInstance()->getScaleUpRatio();

	//BACKGROUND
	auto background = Helper4Sprite::createOptimizeSprite(PNG_LOBBY_BACKGROUND);
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(ScaleManager::getInstance()->getScaleUpRatio());
	this->addChild(background);

	//GIRL MODEL
	model = Helper4Sprite::createOptimizeSprite(PNG_BODY_GIRL_MODEL);
	model->setPosition(Vec2(model->getContentSize().width * model->getScaleX() / 2 + 10 - this->getPositionX() + origin.x,
		-(1 - scaleDownRatio)*visibleSize.height / 2)*ScaleManager::getInstance()->getScaleUpRatio());
	model->setAnchorPoint(Vec2(0.5, 0));
	model->setScale(scaleUpRatio*ScaleManager::getInstance()->getLookGoodScaleDownRatio());
	this->addChild(model);

	//DOTS ICON
	float widthAndHeightDot = Helper4Sprite::createOptimizeSprite(PNG_BODY_DOT_ICON)->getContentSize().width;
	for (int i = 0; i < NUMBER_PAGE; i++)
	{
		Rect rect = i == 0 ? Rect(0, widthAndHeightDot, widthAndHeightDot, widthAndHeightDot) : Rect(0, 0, widthAndHeightDot, widthAndHeightDot);
		auto dot = Helper4Sprite::createOptimizeSprite(PNG_BODY_DOT_ICON, rect);
		dot->setScale(1280.0f*ScaleManager::getInstance()->getScaleUpRatio() / 1920);
		dot->setAnchorPoint(Vec2(0, 0));
		dot->setPosition(visibleSize.width / 2 - 0.52 * widthAndHeightDot * NUMBER_PAGE + i * widthAndHeightDot * 1.3 * dot->getScaleX()*ScaleManager::getInstance()->getScaleUpRatio()
			, POSITION_Y_DOT_ICON + widthAndHeightDot - this->getPositionY()/2);
		this->addChild(dot);
		this->dotIconList.pushBack(dot);
	}

}

void BodyLobbyLayout::createListButtonGameSlot() {
	
	//PAGE VIEW
	auto pageView = ui::PageView::create();
	pageView->setAnchorPoint(Vec2(0.5f, 0.5f));
	pageView->setContentSize(Size(visibleSize.width * 0.78*ScaleManager::getInstance()->getScaleUpRatio(), visibleSize.height * 0.82));
	pageView->setPosition(Vec2(visibleSize.width - pageView->getContentSize().width / 2 + origin.x, visibleSize.height / 2 + 20));
	pageView->addEventListener([this](cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type)
	{
		this->pageViewEvent(sender, type);
	});
	this->addChild(pageView);

	//PAGE 1
	auto page1 = ui::Layout::create();
	page1->setContentSize(pageView->getContentSize());
	pageView->addPage(page1);

	//PAGE 2
	auto page2 = ui::Layout::create();
	page2->setContentSize(pageView->getContentSize());
	pageView->insertPage(page2, 1);

	std::map<int, ServerSlotGameInfo*> listSlotGameInfo = InfoManager::getInstance()->getServerSlotGameInfoMap();

#if IS_DEBUG
	/*test:create list game test*/
	if (listSlotGameInfo.size() == 0) {
		listSlotGameInfo = TestManager::getInstance()->createListGameSlotInfoTest();
	}

	/*test:print out all slot game info*/
	//TestManager::getInstance()->printOutListSlotGameInfo(listSlotGameInfo);
#endif

	for (auto &slotGameInfo : listSlotGameInfo)
	{
		//Get info UI for button
		GameSlotButtonUIInfo* gameSlotButtonInfo = this->initGameSlotButtonUIInfo(slotGameInfo.second->orderId);
		if (!gameSlotButtonInfo) {
			continue;
		}
		//Create button
		auto buttonGameSlot = ButtonGameSlot::create(
			lobbyScene,
			gameSlotButtonInfo->spritePath,
			slotGameInfo.second
		);
		//buttonGameSlot->setScale(1920.0f / 1600);
		buttonGameSlot->checkStateAndUpdateUI();
		buttonGameSlot->checkPreviousDownload();
		//Determite page index and add it to conresponse page
		switch (gameSlotButtonInfo->pageIndex)
		{
		case 0:
			page1->addChild(buttonGameSlot);
			break;
		default:
			page2->addChild(buttonGameSlot);
			break;
		}
		//set position from UI info
		auto sprite = Sprite::createWithSpriteFrameName(gameSlotButtonInfo->spritePath);
		sprite->setScale(buttonGameSlot->getScale());
		auto originPosX = sprite->getContentSize().width / 2 * sprite->getScaleX();
		auto originPosY = pageView->getContentSize().height - sprite->getContentSize().height / 2 * sprite->getScaleY();
		int additionSpace = 10;

		gameSlotButtonInfo->localPosition = Vec2(originPosX + gameSlotButtonInfo->colInPage * sprite->getContentSize().width * sprite->getScaleX() * 0.9f,
			originPosY - gameSlotButtonInfo->rowInPage * sprite->getContentSize().height * sprite->getScaleY() + additionSpace * gameSlotButtonInfo->rowInPage);
		buttonGameSlot->setPosition(gameSlotButtonInfo->localPosition);
		//on touch
		buttonGameSlot->addTouchEventListener(CC_CALLBACK_2(BodyLobbyLayout::onGameSlotTouched, this));

		//ADD TO UPDATE LANGUAGE
		LanguageManager::getInstance()->pushBackToUpdateLanguageList(buttonGameSlot, false);

		//delete gameSlotButtonInfo
		CC_SAFE_DELETE(gameSlotButtonInfo);
	}

}

GameSlotButtonUIInfo* BodyLobbyLayout::initGameSlotButtonUIInfo(int orderId)
{
	GameSlotButtonUIInfo* gameSlotUIInfo = new GameSlotButtonUIInfo();
	gameSlotUIInfo->orderIdFromServer = orderId;
	switch (orderId)
	{
	case ppEnum::NEZHA:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 0;
		gameSlotUIInfo->spritePath = PNG_NEZHA_GAME_ICON;
		break;
	case ppEnum::GOLDEN_EGGS:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 2;
		gameSlotUIInfo->spritePath = PNG_GOLDENEGG_GAME_ICON;
		break;
	case ppEnum::PHARAOH:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 3;
		gameSlotUIInfo->spritePath = PNG_PHARAOH_GAME_ICON;
		break;
	case ppEnum::BOXING:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 1;
		gameSlotUIInfo->colInPage = 0;
		gameSlotUIInfo->spritePath = PNG_BOXING_GAME_ICON;
		break;
	case ppEnum::ROMAN_EMPIRE:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 1;
		gameSlotUIInfo->colInPage = 1;
		gameSlotUIInfo->spritePath = PNG_ROMANEMPIRE_GAME_ICON;
		break;
	case ppEnum::CANDYLICIOUS:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 1;
		gameSlotUIInfo->colInPage = 3;
		gameSlotUIInfo->spritePath = PNG_CANDYLICIOUS_GAME_ICON;
		break;
	case ppEnum::FRUITILICIOUS:
		gameSlotUIInfo->pageIndex = 1;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 0;
		gameSlotUIInfo->spritePath = PNG_FRUITILICIOUS_GAME_ICON;
		break;
	case ppEnum::KPOP:
		gameSlotUIInfo->pageIndex = 1;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 2;
		gameSlotUIInfo->spritePath = PNG_KPOP_GAME_ICON;
		break;
	case ppEnum::LITTLE_MONSTERS:
		gameSlotUIInfo->pageIndex = 1;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 3;
		gameSlotUIInfo->spritePath = PNG_LITTLEMONSTERS_GAME_ICON;
		break;
	case ppEnum::MAFIA:
		gameSlotUIInfo->pageIndex = 1;
		gameSlotUIInfo->rowInPage = 1;
		gameSlotUIInfo->colInPage = 0;
		gameSlotUIInfo->spritePath = PNG_MAFIA_GAME_ICON;
		break;
	case ppEnum::SHERLOCK:
		gameSlotUIInfo->pageIndex = 1;
		gameSlotUIInfo->rowInPage = 1;
		gameSlotUIInfo->colInPage = 1;
		gameSlotUIInfo->spritePath = PNG_SHERLOCK_GAME_ICON;
		break;
	case ppEnum::MAGIC_QUEST:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 1;
		gameSlotUIInfo->colInPage = 2;
		gameSlotUIInfo->spritePath = PNG_MAGICQUEST_GAME_ICON;
		break;
	case ppEnum::BIKINI_BEACH:
		gameSlotUIInfo->pageIndex = 1;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 1;
		gameSlotUIInfo->spritePath = PNG_BIKINIBEACH_GAME_ICON;
		break;
	case ppEnum::FOUR_BEAUTIES:
		gameSlotUIInfo->pageIndex = 1;
		gameSlotUIInfo->rowInPage = 1;
		gameSlotUIInfo->colInPage = 2;
		gameSlotUIInfo->spritePath = PNG_4BEAUTIES_GAME_ICON;
		break;
	case ppEnum::ZEUS:
		CC_SAFE_DELETE(gameSlotUIInfo);
		return nullptr;
	case ppEnum::DEEP_BLUE:
		gameSlotUIInfo->pageIndex = 0;
		gameSlotUIInfo->rowInPage = 0;
		gameSlotUIInfo->colInPage = 1;
		gameSlotUIInfo->spritePath = PNG_DEEPBLUE_GAME_ICON;
		break;
	default:
		CC_SAFE_DELETE(gameSlotUIInfo);
		return nullptr;
	}

	return gameSlotUIInfo;
}

void removeCallbac4AllDownloadingOnBtnGameSlot() {

}

void BodyLobbyLayout::onGameSlotTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
	auto buttonGameSlot = (ButtonGameSlot*)sender;
	this->scheduleOnce([=](float dt) {
		buttonGameSlot->isLongPress = true;
		ButtonGameSlotState currentState = buttonGameSlot->getCurrentState();
		if (currentState == CanPlay && buttonGameSlot->getGameInfo()->orderId != ppEnum::GameSlotOrderId::NEZHA) {
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				lobbyScene,
				"",
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "message_remove"),
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "remove"),
				"",
				"",
				[buttonGameSlot]() {
				// remove game slot
				buttonGameSlot->removeGameSlot();
			},
				nullptr
				);

		}
	}, buttonGameSlot->minimumPressDuration,buttonGameSlot->getGameInfo()->gameId);

	if (type == cocos2d::ui::Widget::TouchEventType::BEGAN) {
		buttonGameSlot->isLongPress = false;
	}
	if (type == cocos2d::ui::Widget::TouchEventType::CANCELED ||
		type == cocos2d::ui::Widget::TouchEventType::ENDED) {
		this->unschedule(buttonGameSlot->getGameInfo()->gameId);
	}

	if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
		return;
	}

	ButtonGameSlotState currentState = buttonGameSlot->getCurrentState();

	if (buttonGameSlot->isLongPress && buttonGameSlot->getGameInfo()->orderId != ppEnum::GameSlotOrderId::NEZHA) {
		buttonGameSlot->isLongPress = false;
	}
	else {

		/*lobbyScene->gotoGameSlotScene(buttonGameSlot->getGameInfo()->orderId);
		return;*/
		//Duy - test go to game
		//return;

		switch (currentState)
		{
		case CanPlay:
			if (buttonGameSlot->fileIsExpireByVersion()) {
				buttonGameSlot->removeGameSlot();
				buttonGameSlot->checkStateAndUpdateUI();
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
					lobbyScene,
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE,"update"),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE,"message_update"),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::CANCEL), "",
					[buttonGameSlot]() {//OK
						buttonGameSlot->startDownloadGameSlotInGameBG();
					},
					[]() {//Cancel
					}
				);
				break;

			} else if (

				buttonGameSlot->getGameInfo()->orderId == ppEnum::GameSlotOrderId::NEZHA
				|| buttonGameSlot->getGameInfo()->orderId == ppEnum::GameSlotOrderId::DEEP_BLUE 
				|| buttonGameSlot->getGameInfo()->orderId == ppEnum::GameSlotOrderId::GOLDEN_EGGS 
				|| buttonGameSlot->getGameInfo()->orderId == ppEnum::GameSlotOrderId::PHARAOH
				|| buttonGameSlot->getGameInfo()->orderId == ppEnum::GameSlotOrderId::BOXING
				|| buttonGameSlot->getGameInfo()->orderId == ppEnum::GameSlotOrderId::ROMAN_EMPIRE
				) {
				lobbyScene->gotoGameSlotScene(buttonGameSlot->getGameInfo()->orderId);
			}
			else {
				PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
					this->getParent()
				);
			}
			//lobbyScene->gotoGameSlotScene(buttonGameSlot->getGameInfo()->orderId);
			/*PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				lobbyScene,
				"//Kiet vo game",
				"//Kiet vo game"
			);*/
			break;
		case Locked:
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				lobbyScene,
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_ERROR_OOP),
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_NEED_LEVEL_TO_PLAY_GAME, "text1")
				+ ToString(buttonGameSlot->getGameInfo()->minLevel)
				+ LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_NEED_LEVEL_TO_PLAY_GAME, "text2"),
				"",
				""
			);
			break;
		case ComingSoon:
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				lobbyScene,
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::NEW_GAME_TILE),
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::NEW_GAME_DESCRIPTION)
			);
			break;
		case Download:
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
				lobbyScene,
				"",
				buttonGameSlot->getGameInfo()->name
				+ LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "message_download"),
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "download"),
				"",
				LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "info_remove"),
				[buttonGameSlot]() {
				// User Chose Download
				buttonGameSlot->startDownloadGameSlotInGameBG();
			}
			);
			break;
		case Downloading:
			if (buttonGameSlot->isGameCanCancelDownload()) {
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
					lobbyScene,
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "download"),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "downloading") + buttonGameSlot->getGameInfo()->name
					+ LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "cancle_download"),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "stop"),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::DOWNLOAD_REMOVE, "continue"),
					"",
					[buttonGameSlot]() {
					// cancel download game slot
					buttonGameSlot->cancelDownloadGameSlot();
				},
					nullptr
					);
			}
			break;
		default:
			break;
		}
	}
}

void BodyLobbyLayout::pageViewEvent(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type)
{
	if (type != cocos2d::ui::PageView::EventType::TURNING) {
		return;
	}
	auto pageView = (cocos2d::ui::PageView*)sender;
	int currentPageIndex = pageView->getCurPageIndex();
	float widthAndHeightDot = Helper4Sprite::createOptimizeSprite(PNG_BODY_DOT_ICON)->getContentSize().width;
	int index = 0;
	for (auto &dot : this->dotIconList)
	{
		if (index == currentPageIndex) {
			dot->setTextureRect(cocos2d::Rect(0, widthAndHeightDot, widthAndHeightDot, widthAndHeightDot));
			//dot->setPosition(dot->getPosition().x, POSITION_Y_DOT_ICON);
		}
		else {
			dot->setTextureRect(cocos2d::Rect(0, 0, widthAndHeightDot, widthAndHeightDot));
			//dot->setPosition(dot->getPosition().x, POSITION_Y_DOT_ICON + widthAndHeightDot);
		}
		index++;
	}
}

void BodyLobbyLayout::setVisibleMascot(bool isVisible) {
	model->setVisible(isVisible);
}

void BodyLobbyLayout::resetChildPosition4ScaleProblem() {

	initUI();
	createListButtonGameSlot();
}

