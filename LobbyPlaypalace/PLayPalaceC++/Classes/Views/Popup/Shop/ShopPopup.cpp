#include "ShopPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Configs.h"
#include "Custom/Common/ToggleButton.h"
#include "Info/AdditionalInfo.h"
#include "Scene/BaseScene.h"

#include "Manager/SoundManager.h"
#include "Manager/PopupManager.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"

#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"

#include "Helper/Helper4Scene.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
#define SPACE_BETWEEN_COIN_PANEL 20
#define SPACE_BETWEEN_CROWN_PANEL 30
#define SPACE_BETWEEN_MAGIC_ITEM_PANEL 5
#define SPACE_BETWEEN_BOOSTER_PANEL 0

#define INTERVAL_CHECK_ADCOLONY 1 //1 seconds
using namespace std;

void ShopPopup::gotoCoinTab()
{
	this->maskCoinBtn->setVisible(false);
	this->maskCrownBtn->setVisible(true);
	this->maskMagicBtn->setVisible(true);
	this->maskBoosterBtn->setVisible(true);

	this->coinGroupListView->setVisible(true);
	this->crownGroupListView->setVisible(false);
	this->magicItemGroupListView->setVisible(false);
	this->boosterGroupListView->setVisible(false);
}

void ShopPopup::gotoCrownTab()
{
	this->maskCoinBtn->setVisible(true);
	this->maskCrownBtn->setVisible(false);
	this->maskMagicBtn->setVisible(true);
	this->maskBoosterBtn->setVisible(true);

	this->coinGroupListView->setVisible(false);
	this->crownGroupListView->setVisible(true);
	this->magicItemGroupListView->setVisible(false);
	this->boosterGroupListView->setVisible(false);
}

void ShopPopup::gotoMagicTab()
{
#if !IS_DEBUG
	/*PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(this->getParent());
	return;*/
#endif
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(PopupManager::getInstance()->getHeaderLobbyLayout()->getParent());
	InfoManager::getInstance()->reloadAdditionalInfo(
		[this](bool isSuccess, AdditionalInfo *result)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();

		((PurchaseMagicItem*)(this->magicItemGroupListView->getChildByTag(PurchaseItemType::MAGIC_ITEM_100_BIG_WIN)))->updateStatusItem();
		((PurchaseMagicItem*)(this->magicItemGroupListView->getChildByTag(PurchaseItemType::MAGIC_ITEM_100_MEGA_WIN)))->updateStatusItem();
		((PurchaseMagicItem*)(this->magicItemGroupListView->getChildByTag(PurchaseItemType::MAGIC_ITEM_LUCKY_10)))->updateStatusItem();
		((PurchaseMagicItem*)(this->magicItemGroupListView->getChildByTag(PurchaseItemType::MAGIC_ITEM_LUCKY_20)))->updateStatusItem();
		((PurchaseMagicItem*)(this->magicItemGroupListView->getChildByTag(PurchaseItemType::MAGIC_ITEM_DOUBLE_EXP)))->updateStatusItem();
		((PurchaseMagicItem*)(this->magicItemGroupListView->getChildByTag(PurchaseItemType::MAGIC_ITEM_LUCKY_SYMBOL)))->updateStatusItem();

		this->maskCoinBtn->setVisible(true);
		this->maskCrownBtn->setVisible(true);
		this->maskMagicBtn->setVisible(false);
		this->maskBoosterBtn->setVisible(true);

		this->coinGroupListView->setVisible(false);
		this->crownGroupListView->setVisible(false);
		this->magicItemGroupListView->setVisible(true);
		this->boosterGroupListView->setVisible(false);

		BaseScene * runningScene = (BaseScene*)Helper4Scene::getRunningScene();
		int runningSceneTag = runningScene->getTag();
		if (isSuccess
			&& runningSceneTag == ppEnum::GameScene::GameSlot)
		{
			PopupManager::getInstance()->getHeaderLobbyLayout()->showMagicItemBtn(
				static_cast<LobbyConstant::MagicItemType>(
					InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType
					)
			);
		}
	}
	);
}

void ShopPopup::gotoBoosterTab()
{
//#if !IS_DEBUG
//	PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(this->getParent());
//	return;
//#endif
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(PopupManager::getInstance()->getHeaderLobbyLayout()->getParent());
	InfoManager::getInstance()->reloadAdditionalInfo(
		[this](bool isSuccess, AdditionalInfo *result)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		((PurchaseBoosterItem*)(this->boosterGroupListView->getChildByTag(PurchaseItemType::BOOSTER_3_DAYS)))->updateStatusItem();
		this->maskCoinBtn->setVisible(true);
		this->maskCrownBtn->setVisible(true);
		this->maskMagicBtn->setVisible(true);
		this->maskBoosterBtn->setVisible(false);

		this->coinGroupListView->setVisible(false);
		this->crownGroupListView->setVisible(false);
		this->magicItemGroupListView->setVisible(false);
		this->boosterGroupListView->setVisible(true);
	}
	);
}

void ShopPopup::checkAndSetEnableFreeCoinButton(float dt)
{
	auto watchVideo = this->coinGroupListView->getChildByTag(PurchaseItemType::FREE_COINS);
	auto status = PluginManager::getInstance()->getAdcolonyController()->getVideoStatus();
	((PurchaseCoinCrownItem*)watchVideo)->setEnableBuyButton(status == sdkbox::AdColonyAdStatus::ADCOLONY_ZONE_STATUS_ACTIVE);
}

cocos2d::ui::ListView * ShopPopup::createListViewForTabs(ShopType shopType, int count)
{
	Size itemSize;
	return nullptr;
}

void ShopPopup::playSoundOpenPopup()
{
	SoundManager::getInstance()->playSoundEffectOpenShopPopup();
}

bool ShopPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PNG_SHOP_POPUP_PLIST);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//BACKGROUND
	auto background = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_POPUP_BACKGROUND);
	background->setCascadeOpacityEnabled(true);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2.05f));
	this->addChild(background);

	//COIN GROUP
#pragma region COIN GROUP
	Size panelCoinSize = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_COIN)->getContentSize();
	this->coinGroupListView = ui::ListView::create();
	this->coinGroupListView->setPosition(Vec2(68, 35));
	this->coinGroupListView->setContentSize(Size((panelCoinSize.width + SPACE_BETWEEN_COIN_PANEL) * 5.0f- SPACE_BETWEEN_COIN_PANEL, panelCoinSize.height));
	this->coinGroupListView->setScrollBarEnabled(false);
	this->coinGroupListView->setCascadeOpacityEnabled(true);
	this->coinGroupListView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	background->addChild(this->coinGroupListView);

	PurchaseItemType purchaseItemsType[8] = {
		PurchaseItemType::FREE_COINS,
		PurchaseItemType::COINS_400K,
		PurchaseItemType::COINS_800K,
		PurchaseItemType::COINS_2M,
		PurchaseItemType::COINS_4M,
		PurchaseItemType::COINS_8M,
		PurchaseItemType::COINS_20M,
		PurchaseItemType::COINS_40M
	};
	int itemsSize = sizeof(purchaseItemsType) / sizeof(purchaseItemsType[0]);
	for (int i = 0; i < itemsSize; i++)
	{
		auto purchaseItem = PurchaseCoinCrownItem::create(purchaseItemsType[i]);
		purchaseItem->setTag(purchaseItemsType[i]);
		purchaseItem->setCascadeOpacityEnabled(true);
		purchaseItem->setContentSize(panelCoinSize);
		this->coinGroupListView->pushBackCustomItem(purchaseItem);
	}
	this->coinGroupListView->setItemsMargin(SPACE_BETWEEN_COIN_PANEL);
	this->coinGroupListView->setInnerContainerSize(Size(
		itemsSize * (panelCoinSize.width + SPACE_BETWEEN_COIN_PANEL),
		this->coinGroupListView->getContentSize().height
	));
#pragma endregion

	//CROWN GROUP
#pragma region CROWN GROUP
	Size panelCrownSize = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_CROWN)->getContentSize();
	this->crownGroupListView = ui::ListView::create();
	this->crownGroupListView->setPosition(Vec2(130, 22));
	this->crownGroupListView->setContentSize(Size((panelCrownSize.width + SPACE_BETWEEN_CROWN_PANEL) * 3.0f, panelCrownSize.height));
	this->crownGroupListView->setScrollBarEnabled(false);
	this->crownGroupListView->setCascadeOpacityEnabled(true);
	this->crownGroupListView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	background->addChild(this->crownGroupListView);

	PurchaseItemType purchaseCrownItemsType[3] = {
		PurchaseItemType::CROWNS_10,
		PurchaseItemType::CROWNS_55,
		PurchaseItemType::CROWNS_120
	};
	int crownItemsSize = sizeof(purchaseCrownItemsType) / sizeof(purchaseCrownItemsType[0]);
	for (int i = 0; i < crownItemsSize; i++)
	{
		auto purchaseItem = PurchaseCoinCrownItem::create(purchaseCrownItemsType[i]);
		purchaseItem->setTag(purchaseCrownItemsType[i]);
		purchaseItem->setCascadeOpacityEnabled(true);
		purchaseItem->setContentSize(panelCrownSize);
		this->crownGroupListView->pushBackCustomItem(purchaseItem);
	}
	this->crownGroupListView->setItemsMargin(SPACE_BETWEEN_CROWN_PANEL);
	this->crownGroupListView->setInnerContainerSize(Size(
		crownItemsSize * (panelCrownSize.width + SPACE_BETWEEN_CROWN_PANEL),
		this->crownGroupListView->getContentSize().height
	));
#pragma endregion

	//MAGIC ITEM GROUP
#pragma region MAGIC ITEM GROUP
	Size panelMagicItemSize = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_MAGIC_ITEM)->getContentSize();
	this->magicItemGroupListView = ui::ScrollView::create();
	this->magicItemGroupListView->setPosition(Vec2(40, 30));
	this->magicItemGroupListView->setContentSize(Size((panelMagicItemSize.width + SPACE_BETWEEN_MAGIC_ITEM_PANEL) * 5.0f, panelMagicItemSize.height));
	this->magicItemGroupListView->setScrollBarEnabled(false);
	this->magicItemGroupListView->setCascadeOpacityEnabled(true);
	this->magicItemGroupListView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	background->addChild(this->magicItemGroupListView);

	PurchaseItemType purchaseMagicItemsType[6] = {
		PurchaseItemType::MAGIC_ITEM_100_BIG_WIN,
		PurchaseItemType::MAGIC_ITEM_100_MEGA_WIN,
		PurchaseItemType::MAGIC_ITEM_LUCKY_10,
		PurchaseItemType::MAGIC_ITEM_LUCKY_20,
		PurchaseItemType::MAGIC_ITEM_DOUBLE_EXP,
		PurchaseItemType::MAGIC_ITEM_LUCKY_SYMBOL
	};
	int magicItemsSize = sizeof(purchaseMagicItemsType) / sizeof(purchaseMagicItemsType[0]);
	for (int i = 0; i < magicItemsSize; i++)
	{
		auto infoGroup = PurchaseItemNode::createInfoGroup(
			ShopItemType::MagicItemType
		);
		infoGroup->setVisible(false);

		auto purchaseItem = PurchaseMagicItem::create(purchaseMagicItemsType[i], infoGroup);
		purchaseItem->setTag(purchaseMagicItemsType[i]);
		purchaseItem->setCascadeOpacityEnabled(true);
		purchaseItem->setPosition(Vec2(
			i * (panelMagicItemSize.width + SPACE_BETWEEN_MAGIC_ITEM_PANEL),
			purchaseItem->getPositionY()
		));
		//purchaseItem->setContentSize(panelMagicItemSize);
		//this->magicItemGroupListView->pushBackCustomItem(purchaseItem);
		this->magicItemGroupListView->addChild(purchaseItem);

		//setup info group
		if (infoGroup)
		{
			//get label
			((Label*)infoGroup->getChildren().at(0))->setString(purchaseItem->infoString);
			infoGroup->setPosition(
				panelMagicItemSize / 2 + Size(purchaseItem->getPositionX()+5, 65)
			);
			if (i == 0) infoGroup->setPositionX(infoGroup->getPositionX() + 20);
			else if(i == magicItemsSize-1) infoGroup->setPositionX(infoGroup->getPositionX() - 30);
			this->magicItemGroupListView->addChild(infoGroup, 10);
		}
	}
	//this->magicItemGroupListView->setItemsMargin(SPACE_BETWEEN_MAGIC_ITEM_PANEL);
	this->magicItemGroupListView->setInnerContainerSize(Size(
		magicItemsSize * (panelMagicItemSize.width + SPACE_BETWEEN_MAGIC_ITEM_PANEL),
		this->magicItemGroupListView->getContentSize().height
	));
#pragma endregion

	//BOOSTER GROUP
#pragma region BOOSTER GROUP
	Size panelBoosterItemSize = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_BOOSTER)->getContentSize();
	this->boosterGroupListView = ui::ListView::create();
	this->boosterGroupListView->setPosition(Vec2(background->getContentSize().width / 2 - 200 - panelBoosterItemSize.width / 2, 42));
	this->boosterGroupListView->setContentSize(Size((panelBoosterItemSize.width + SPACE_BETWEEN_BOOSTER_PANEL) * 1.0f + 350, panelBoosterItemSize.height));
	this->boosterGroupListView->setScrollBarEnabled(false);
	this->boosterGroupListView->setCascadeOpacityEnabled(true);
	this->boosterGroupListView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
	background->addChild(this->boosterGroupListView);

	PurchaseItemType purchaseBoosterItemsType[2] = {
		PurchaseItemType::BOOSTER_3_DAYS,
		PurchaseItemType::BOOSTER_7_DAYS
	};
	int boosterItemsSize = sizeof(purchaseBoosterItemsType) / sizeof(purchaseBoosterItemsType[0]) / 2;
	for (int i = 0; i < boosterItemsSize; i++)
	{
		auto infoGroup = PurchaseItemNode::createInfoGroup(
			ShopItemType::BoostersItemType
		);
		infoGroup->setVisible(false);

		auto purchaseItem = PurchaseBoosterItem::create(purchaseMagicItemsType[i], purchaseMagicItemsType[i + 1], infoGroup);
		purchaseItem->setTag(purchaseBoosterItemsType[i]);
		purchaseItem->setCascadeOpacityEnabled(true);
		purchaseItem->setContentSize(panelBoosterItemSize);
		this->boosterGroupListView->pushBackCustomItem(purchaseItem);

		//setup info group
		if (infoGroup)
		{
			//get label
			((Label*)infoGroup->getChildren().at(0))->setString(purchaseItem->infoString);
			infoGroup->setPosition(
				purchaseItem->getContentSize() / 2 + Size(i * (purchaseItem->getContentSize().width + SPACE_BETWEEN_BOOSTER_PANEL) + 230, -30)
			);
			this->boosterGroupListView->addChild(infoGroup, 10);
		}
	}
	this->boosterGroupListView->setItemsMargin(SPACE_BETWEEN_BOOSTER_PANEL);
	this->boosterGroupListView->setInnerContainerSize(Size(
		boosterItemsSize * (panelBoosterItemSize.width + SPACE_BETWEEN_BOOSTER_PANEL),
		this->boosterGroupListView->getContentSize().height
	));
#pragma endregion

	//TOGGLE EXAMPLE
	/*CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
	CCMenuItemSprite* p1 = CCMenuItemSprite::create(
	Sprite::create(PNG_SHOP_TOGGLE_ON),
	Sprite::create(PNG_SHOP_TOGGLE_OFF));
	CCMenuItemSprite* p2 = CCMenuItemSprite::create(
	Sprite::create(PNG_SHOP_TOGGLE_OFF),
	Sprite::create(PNG_SHOP_TOGGLE_ON));
	p2->setPosition(Vec2(300, 100));
	CCMenuItemToggle* pToggle = CCMenuItemToggle::createWithTarget(this, menu_selector(ShopPopup::asdsf, this), p1, p2, NULL);
	pToggle->setPosition(500.0f, 300.0f);
	pMenu->addChild(pToggle);*/


	//TOGGLE COIN
#pragma region TOGGLE COIN
	Size buttonToggleSize = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_MASK_TOGGLE)->getContentSize();
	this->maskCoinBtn = ui::Button::create(PNG_FRAME_SHOP_MASK_TOGGLE,"","",ui::Widget::TextureResType::PLIST);
	this->maskCoinBtn->setCascadeOpacityEnabled(true);
	this->maskCoinBtn->setZoomScale(0);
	this->maskCoinBtn->setPosition(Vec2(
		buttonToggleSize.width / 2 + 38,
		background->getContentSize().height * 2 / 3.0f + buttonToggleSize.height / 2 + 1
	));
	this->maskCoinBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType touchEventType)
	{
		if (touchEventType != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->gotoCoinTab();
	});
	background->addChild(this->maskCoinBtn);

#pragma endregion


	//TOGGLE CROWN
#pragma region TOGGLE CROWN
	this->maskCrownBtn = ui::Button::create(PNG_FRAME_SHOP_MASK_TOGGLE, "", "", ui::Widget::TextureResType::PLIST);
	this->maskCrownBtn->setCascadeOpacityEnabled(true);
	this->maskCrownBtn->setZoomScale(0);
	this->maskCrownBtn->setPosition(Vec2(
		this->maskCoinBtn->getPosition() + Vec2(buttonToggleSize.width + 4, 0)
	));
	this->maskCrownBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType touchEventType)
	{
		if (touchEventType != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->gotoCrownTab();
	});
	background->addChild(this->maskCrownBtn);
#pragma endregion

	//TOGGLE MAGIC ITEM
#pragma region TOGGLE MAGIC ITEM
	this->maskMagicBtn = ui::Button::create(PNG_FRAME_SHOP_MASK_TOGGLE, "", "", ui::Widget::TextureResType::PLIST);
	this->maskMagicBtn->setCascadeOpacityEnabled(true);
	this->maskMagicBtn->setZoomScale(0);
	this->maskMagicBtn->setPosition(Vec2(
		this->maskCrownBtn->getPosition() + Vec2(buttonToggleSize.width + 4, 0)
	));
	this->maskMagicBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType touchEventType)
	{
		if (touchEventType != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->gotoMagicTab();
	});
	background->addChild(this->maskMagicBtn);
#pragma endregion

	//TOGGLE BOOSTER
#pragma region TOGGLE BOOSTER
	this->maskBoosterBtn = ui::Button::create(PNG_FRAME_SHOP_MASK_TOGGLE, "", "", ui::Widget::TextureResType::PLIST);
	this->maskBoosterBtn->setCascadeOpacityEnabled(true);
	this->maskBoosterBtn->setZoomScale(0);
	this->maskBoosterBtn->setPosition(Vec2(
		this->maskMagicBtn->getPosition() + Vec2(buttonToggleSize.width + 4, 0)
	));
	this->maskBoosterBtn->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType touchEventType)
	{
		if (touchEventType != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->gotoBoosterTab();
	});
	background->addChild(this->maskBoosterBtn);
#pragma endregion

	//CLOSE BUTTON
	auto closeButton = this->createCloseButton();
	closeButton->setPosition(Vec2(
		background->getPosition().x + background->getContentSize().width / 2 - 30,
		background->getPosition().y + background->getContentSize().height / 2 - 30
	));
	this->addChild(closeButton);

	return true;
}

void ShopPopup::prepareAndShow(cocos2d::Node * parent, ShopType shopType)
{
	switch (shopType)
	{
	case CoinShop:
		this->gotoCoinTab();
		this->coinGroupListView->scrollToLeft(0,false);
		break;
	case CrownShop:
		this->gotoCrownTab();
		break;
	case MagicItemShop:
		this->gotoMagicTab();
		break;
	case BoostersShop:
		this->gotoBoosterTab();
		break;
	default:
		return;
	}

	//PluginManager::getInstance()->getIAPController()->refresh();
	this->checkAndSetEnableFreeCoinButton(0);
	this->schedule(schedule_selector(ShopPopup::checkAndSetEnableFreeCoinButton), INTERVAL_CHECK_ADCOLONY);

	BasePopup::showWithQueue(parent);
}

void ShopPopup::activateMagicItem(int magicItemTypeIdOfServer)
{
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(
		this->getParent()
	);
	NetworkManager::getInstance()->activateMagicItem(
		magicItemTypeIdOfServer,
		[this, magicItemTypeIdOfServer](int coreResultCode, rapidjson::Value &response, std::string responseAsString)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		this->gotoMagicTab();
	},
		[](std::string result)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	},
		[](std::string result)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	}
	);
}

void ShopPopup::selecteItem(PurchaseItemType itemType)
{
	auto item = this->coinGroupListView->getChildByTag(itemType);
	if(!item) item = this->crownGroupListView->getChildByTag(itemType);
	if (item) {
		((PurchaseCoinCrownItem*)item)->onSelected();
	}
	if (!item) item = this->magicItemGroupListView->getChildByTag(itemType);
	if (item) {
		((PurchaseMagicItem*)item)->onSelected();
	}
	if (!item) item = this->boosterGroupListView->getChildByTag(itemType);
	if (item) {
		((PurchaseBoosterItem*)item)->onSelected(itemType);
	}
}
