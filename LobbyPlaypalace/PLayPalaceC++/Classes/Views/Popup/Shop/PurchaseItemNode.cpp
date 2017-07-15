#include "PurchaseItemNode.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LobbyConstant.h"
#include "Configs.h"
#include "Util/UtilFunction.h"
#include "Manager/PluginManager.h"
#include "Manager/PopupManager.h"
#include "Manager/InfoManager.h"
#include "Info/AdditionalInfo.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/Shop/ShopPopup.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Helper/Helper4Scene.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;
#define TAIL_MAGIC_ITEM_REMAINING " left"

ButtonScaleChild * PurchaseItemNode::createBuyButton(ShopItemType typeShopItemOfButton, std::string labelImagePath)
{
	ButtonScaleChild *button = nullptr;

	switch (typeShopItemOfButton)
	{
	case ShopItemType::CoinItemType:
	case ShopItemType::CrownItemType:
		button = ButtonScaleChild::create(PNG_FRAME_SHOP_COIN_BTN,"","",ui::Widget::TextureResType::PLIST);
		break;
	case ShopItemType::MagicItemType:
		button = ButtonScaleChild::create(PNG_FRAME_SHOP_MAGIC_ITEM_FREE_BTN,"","",ui::Widget::TextureResType::PLIST);
		break;
	case ShopItemType::BoostersItemType:
		button = ButtonScaleChild::create(PNG_FRAME_SHOP_BOOSTERS_BTN,"","",ui::Widget::TextureResType::PLIST);
		break;
	default:
		break;
	}
	if (button)
	{
		button->setCascadeOpacityEnabled(true);
		button->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
		auto labelImage = Helper4Sprite::createWithSpriteFrameName(labelImagePath);
		button->addScaleNode(labelImage);
		if (typeShopItemOfButton == ShopItemType::MagicItemType)
		{
			labelImage->setPosition(Vec2(-6, 0));
		}
		else if(typeShopItemOfButton == ShopItemType::BoostersItemType)
		{
			labelImage->setContentSize(labelImage->getContentSize() * 0.8f);
			labelImage->setPosition(-7, 0);
			button->setScale(1.2f);
		}

	}
	return button;
}

cocos2d::Sprite * PurchaseItemNode::createInfoGroup(ShopItemType shopItemType)
{
	Sprite *infoBG = nullptr;
	switch (shopItemType)
	{
	case ShopItemType::MagicItemType:
		infoBG = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_INFO_BG);
		break;
	case ShopItemType::BoostersItemType:
		infoBG = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_BOOSTER_INFO_BG);
		break;
	default:
		break;
	}
	if (infoBG)
	{
		infoBG->setCascadeOpacityEnabled(true);
		auto label = Label::createWithTTF(
			"",
			FONT_PassionOne_Regular,
			shopItemType == ShopItemType::MagicItemType ? 28 : 40
		);
		label->setDimensions(infoBG->getContentSize().width - 70, infoBG->getContentSize().height - 70);
		label->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
		label->setPosition(infoBG->getContentSize() / 2 + Size(0, -infoBG->getContentSize().height * 0.05f));
		infoBG->addChild(label);

		auto closeButton = ui::Button::create(PNG_FRAME_CLOSE_POPUP_BUTTON,"","",ui::Widget::TextureResType::PLIST);
		closeButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
		closeButton->setPosition(infoBG->getContentSize() - (shopItemType == ShopItemType::MagicItemType ? Size(45, 38) : Size (50, 85)));
		closeButton->setScale(0.7f);
		closeButton->addTouchEventListener([infoBG](Ref* ref, ui::Widget::TouchEventType touchEventType)
		{
			if (touchEventType != ui::Widget::TouchEventType::ENDED)
			{
				return;
			}
			infoBG->setVisible(false);
		});
		infoBG->addChild(closeButton);
	}
	return infoBG;
}

void PurchaseItemNode::callbackAfterPurchase(int core_result_code, MobilePaymentInfo mobilePaymentInfo)
{
	PopupManager::getInstance()->getLoadingAnimation()->hide();
	if (Configs::printConsoleLog)
	{
		CCLOG("@@@@@@@@@@@@@@@@@@@@@ CALL BACK AFTER PURCHASE AND VERIFY FROM SV WITH RESULT CODE : %d @@@@@@@@@@@@@@@@@@@", core_result_code);
	}

	if (core_result_code != RESULT_CODE_VALID)
	{
		PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
			PopupManager::getInstance()->getShopPopup()->getParent(),
			"",
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_SHOP_TRANSACTION_CANCELLED),
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
			""
		);
	}
}

void PurchaseItemNode::onSelected(int purchasePos) {
#ifdef SDKBOX_ENABLED
	if (this->namePurchaseList.size() - 1 >= purchasePos
		&& !this->namePurchaseList[purchasePos].empty())
	{
		PluginManager::getInstance()->getIAPController()->purchase(
			this->namePurchaseList[purchasePos],
			[this](int core_result_code, MobilePaymentInfo mobilePaymentInfo)
		{
			this->callbackAfterPurchase(core_result_code, mobilePaymentInfo);
		},
			nullptr,
			[](sdkbox::Product const&p, const std::string&msg)
		{
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		},
			[](sdkbox::Product const&p)
		{
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		}
		);
	}
	////Adcolony show
	//else
	//{
	//	PluginManager::getInstance()->getAdcolonyController()->showVideo(CALLBACK_4(PurchaseCoinCrownItem::callbackRewardVideoAdcolony, this));
	//	this->buyButton->setEnabled(false);
	//}
#else
	PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(
		this->getParent()->getParent()->getParent()->getParent()
	);
#endif
}

void PurchaseCoinCrownItem::callbackAfterPurchase(int core_result_code, MobilePaymentInfo mobilePaymentInfo)
{
	PurchaseItemNode::callbackAfterPurchase(core_result_code, mobilePaymentInfo);
	if (core_result_code != RESULT_CODE_VALID)
	{
		return;
	}

	double coinReward = mobilePaymentInfo.coinReward;
	int crownReward = mobilePaymentInfo.crownReward;

	bool isPurchaseCoinPakage = coinReward > 0 ? true : false;

	std::string rewardString = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::PURCHASED, "reward");//my.selectlanguage.purchased.reward + Lobby.Utils.formatNumberWithCommas(amountBonusToShowInPopup);
	if (isPurchaseCoinPakage) {
		rewardString += UtilFunction::FormatWithCommas(coinReward);
		rewardString += " " + LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_USER_GAME_UNLOCK, "text5");//my.selectlanguage.popup_user_game_unlock.text5;
	}
	else {
		rewardString += UtilFunction::FormatWithCommas(crownReward);
		rewardString += " " + LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_STARDOM_PLAYER_COINS);//rewardString += " " + my.selectlanguage.popup_stardom_player_Coins.text;
	}
	//reload coin ui
	auto header = PopupManager::getInstance()->getHeaderLobbyLayout();
	if (header)
	{
		header->reloadUIHeaderAndCheckShowPopupLevelUp(nullptr, true, true);
	}

	//show notification popup
	PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
		PopupManager::getInstance()->getShopPopup()->getParent(),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::PURCHASED, "approved"),
		rewardString,
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		"",
		"",
		[coinReward, crownReward]()
	{
		auto okButtonPos = PopupManager::getInstance()->getNotificationPopup()->getOkButtonPosition();
		AnimationCoinCrown::create(
			Helper4Scene::getRunningScene(),
			okButtonPos,
			coinReward
		);
		AnimationCoinCrown::create(
			Helper4Scene::getRunningScene(),
			okButtonPos,
			crownReward,
			AnimationType::CrownAnimation
		);
	}
	);
}

void PurchaseCoinCrownItem::callbackRewardVideoAdcolony(const sdkbox::AdColonyAdInfo & info, const std::string & currencyName, int amount, bool success)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("@@@@@@@@@@@@@@@@@@@@@ CALL BACK REWARD AFTER WATCH VIDEO ADCOLONY , isSuccess = %s @@@@@@@@@@@@@@@@@@@@@", success ? "true" : "false");
	}
	PopupManager::getInstance()->getLoadingAnimation()->hide();
	if (!success) {
		return;
	}
	auto languageManager = LanguageManager::getInstance();
	PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
		PopupManager::getInstance()->getShopPopup()->getParent(),
		languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SUCCESS),
		languageManager->getStringForKeys(nullptr, LanguageConstant::FREE_COIN, "received") + " " + UtilFunction::FormatWithCommas(amount) + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_VOUCHER_DESCRIPTION, "text2"),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		"",
		"",
		[amount]()
	{
		auto okButtonPos = PopupManager::getInstance()->getNotificationPopup()->getOkButtonPosition();
		PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCoin(amount);
		AnimationCoinCrown::create(
			Helper4Scene::getRunningScene(),
			okButtonPos,
			amount
		);
	}
	);
}

void PurchaseCoinCrownItem::setEnableBuyButton(bool isEnable)
{
	this->buyButton->setEnabled(isEnable);
}

void PurchaseCoinCrownItem::onSelected(int purchasePos)
{
	if (this->isItemAdcolony)
	{
		PluginManager::getInstance()->getAdcolonyController()->showVideo(CALLBACK_4(PurchaseCoinCrownItem::callbackRewardVideoAdcolony, this));
		this->buyButton->setEnabled(false);
	}
	else
	{
		PurchaseItemNode::onSelected(purchasePos);
	}
}

PurchaseCoinCrownItem * PurchaseCoinCrownItem::create(PurchaseItemType _purchaseItemType)
{
	PurchaseCoinCrownItem * ret = new (std::nothrow) PurchaseCoinCrownItem();
	ret->currentPruchaseItemTypeList.push_back(_purchaseItemType);
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PurchaseCoinCrownItem::init()
{
	if (!cocos2d::ui::Widget::init()) {
		return false;
	}

	std::string titleImagePath = "";
	std::string bodyString = "";
	std::string iconPath = "";
	std::string labelBuyButtonPath = "";
	bool isCoinPanel = true;
	Vec2 buyBtnOffset = Vec2::ZERO;

	switch (this->currentPruchaseItemTypeList[0]){
		case FREE_COINS:
		case COINS_400K:
		case COINS_800K:
		case COINS_2M:
		case COINS_4M:
		case COINS_8M:
		case COINS_20M:
		case COINS_40M:
			buyBtnOffset = Vec2(5, 20);
			break;
	}
	switch (this->currentPruchaseItemTypeList[0])
	{
	case FREE_COINS:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_FREE_COINS;
		bodyString = "Get FREE Coins";
		iconPath = PNG_FRAME_SHOP_WATCH_VIDEO_ICON;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_FREE;
		this->isItemAdcolony = true;
		break;
	}
	case COINS_400K:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_400K;
		bodyString = "";
		iconPath = PNG_FRAME_SHOP_COINS_1;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$0_99;
		this->namePurchaseList.push_back(IAP_COINS_400K);
		break;
	}
	case COINS_800K:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_880K;
		bodyString = "Over 10% FREE";
		iconPath = PNG_FRAME_SHOP_COINS_1;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$1_99;
		this->namePurchaseList.push_back(IAP_COINS_800K);
		break;
	}
	case COINS_2M:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_2M4;
		bodyString = "Over 20% FREE";
		iconPath = PNG_FRAME_SHOP_COINS_1;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$4_99;
		this->namePurchaseList.push_back(IAP_COINS_2M);
		break;
	}
	case COINS_4M:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_7M2;
		bodyString = "Over 80% FREE";
		iconPath = PNG_FRAME_SHOP_COINS_2;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$9_99;
		this->namePurchaseList.push_back(IAP_COINS_4M);
		break;
	}
	case COINS_8M:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_24M;
		bodyString = "Over 200% FREE";
		iconPath = PNG_FRAME_SHOP_COINS_2;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$19_99;
		this->namePurchaseList.push_back(IAP_COINS_8M);
		break;
	}
	case COINS_20M:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_70M;
		bodyString = "Over 250% FREE";
		iconPath = PNG_FRAME_SHOP_COINS_3;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$49_99;
		this->namePurchaseList.push_back(IAP_COINS_20M);
		break;
	}
	case COINS_40M:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_200M;
		bodyString = "Over 400% FREE";
		iconPath = PNG_FRAME_SHOP_COINS_3;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$99_99;
		this->namePurchaseList.push_back(IAP_COINS_40M);
		break;
	}
	case CROWNS_10:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_CROWNS_TEXT_10_CROWNS;
		bodyString = "";
		iconPath = PNG_FRAME_SHOP_CROWNS_1;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$1_99;
		this->namePurchaseList.push_back(IAP_CROWNS_10);
		isCoinPanel = false;
		break;
	}
	case CROWNS_55:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_CROWNS_TEXT_55_CROWNS;
		bodyString = "Over 10% FREE";
		iconPath = PNG_FRAME_SHOP_CROWNS_2;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$9_99;
		this->namePurchaseList.push_back(IAP_CROWNS_55);
		isCoinPanel = false;
		break;
	}
	case CROWNS_120:
	{
		titleImagePath = PNG_FRAME_SHOP_TEXT_CROWNS_TEXT_120_CROWNS;
		bodyString = "Over 20% FREE";
		iconPath = PNG_FRAME_SHOP_CROWNS_3;
		labelBuyButtonPath = PNG_FRAME_SHOP_TEXT_COINS_TEXT_$19_99;
		this->namePurchaseList.push_back(IAP_CROWNS_120);
		isCoinPanel = false;
		break;
	}
	default:
		return true;
	}

	auto bg = Helper4Sprite::createWithSpriteFrameName(isCoinPanel ? PNG_FRAME_SHOP_PANEL_ITEM_COIN : PNG_FRAME_SHOP_PANEL_ITEM_CROWN);
	bg->setPosition(bg->getContentSize() / 2);
	bg->setCascadeOpacityEnabled(true);
	this->addChild(bg);

	auto titleImage = Helper4Sprite::createWithSpriteFrameName(titleImagePath);
	titleImage->setPosition(
		bg->getContentSize() / 2 + Size(0, bg->getContentSize().height / 2 - 45)
	);
	bg->addChild(titleImage);

	auto bodyLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Bold, 25),
		bodyString
	);
	bodyLabel->setPosition(Vec2(
		titleImage->getPosition() + Vec2(0, -40)
	));
	bg->addChild(bodyLabel);

	auto icon = Helper4Sprite::createWithSpriteFrameName(iconPath);
	icon->setCascadeOpacityEnabled(true);
	icon->setPosition(Vec2(
		bg->getContentSize() / 2 + Size(0, -10)
	));
	icon->setScale(0.8f);
	bg->addChild(icon);

	this->buyButton = this->createBuyButton(
		ShopItemType::CoinItemType,
		labelBuyButtonPath
	);
	this->buyButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->buyButton->setPosition(Vec2(
		buyBtnOffset + bg->getContentSize() / 2 + Size(-5, (bg->getContentSize().width - this->buyButton->getContentSize().width) / 2 - bg->getContentSize().height / 2 + this->buyButton->getContentSize().height / 2)
	));
	this->buyButton->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType touchEventType)
	{
		if (touchEventType != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->onSelected();
	});
	bg->addChild(this->buyButton);

	if (this->isItemAdcolony)
	{
		this->buyButton->setEnabled(false);
	}

	return true;
}

void PurchaseMagicItem::onActivateMagicItemBtnClicked(cocos2d::Ref * ref, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}

	int magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DEFAULT;
	int currentActivatedMagicItem = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType;
	std::string packageName = "";
	switch (InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo->activeMagicItemType)
	{
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN:
		packageName = "100% Big Win";
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN:
		packageName = "100% Mega Win";
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1:
		packageName = "Lucky Spin 10%";
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2:
		packageName = "Lucky Spin 20%";
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DOUBLE_EXP:
		packageName = "Double Exp";
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SYMBOL:
		packageName = "Lucky Symbol";
		break;
	default:
		break;
	}
	switch (this->currentPruchaseItemTypeList[0])
	{
	case MAGIC_ITEM_100_BIG_WIN:
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN;
		break;
	case MAGIC_ITEM_100_MEGA_WIN:
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN;
		break;
	case MAGIC_ITEM_LUCKY_10:
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1;
		break;
	case MAGIC_ITEM_LUCKY_20:
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2;
		break;
	case MAGIC_ITEM_DOUBLE_EXP:
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DOUBLE_EXP;
		break;
	case MAGIC_ITEM_LUCKY_SYMBOL:
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SYMBOL;
		break;
	default:
		return;
	}

	if (!packageName.empty())
	{
		PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
			PopupManager::getInstance()->getShopPopup()->getParent(),
			"Warning",
			"Your " + packageName + " is activating. Are you sure you want to deactivate?",
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::CANCEL),
			"",
			[magicItemTypeIdOfServer]()
		{
			PopupManager::getInstance()->getShopPopup()->activateMagicItem(magicItemTypeIdOfServer);
		}
		);
	}
	else
	{
		PopupManager::getInstance()->getShopPopup()->activateMagicItem(magicItemTypeIdOfServer);
	}
}

void PurchaseMagicItem::callbackAfterPurchase(int core_result_code, MobilePaymentInfo mobilePaymentInfo)
{
	PurchaseItemNode::callbackAfterPurchase(core_result_code, mobilePaymentInfo);
	if (core_result_code != RESULT_CODE_VALID)
	{
		return;
	}
	PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
		PopupManager::getInstance()->getShopPopup()->getParent(),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::PURCHASED, "approved"),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_CHANGE_LANGUAGE, "success"),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		"",
		""
	);
	auto magicItemInfo = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo;
	/*magicItemInfo->remainingPackageOfMagicItem100PercentMegaWin += mobilePaymentInfo.magicItem100PercentWinReward;
	magicItemInfo->remainingPackageOfMagicItemLuckySpinType1 += mobilePaymentInfo.magicItemLuckySpinType1Reward;
	magicItemInfo->remainingPackageOfMagicItemLuckySpinType2 += mobilePaymentInfo.magicItemLuckySpinType2Reward;
	magicItemInfo->remainingPackageOfMagicItemDoubleExp += mobilePaymentInfo.magicItemDoubleExpDurationTimeReward;
	magicItemInfo->remainingPackageOfMagicItemLuckySymbol += mobilePaymentInfo.magicItemLuckySymbolDurationTimeReward;*/

	switch (mobilePaymentInfo.productType)
	{
	case LobbyConstant::ProductType::MAGIC_ITEM_100_PERCENT_BIG_WIN:
		magicItemInfo->remainingPackageOfMagicItem100PercentBigWin++;
		break;
	case LobbyConstant::ProductType::MAGIC_ITEM_100_PERCENT_WIN:
		magicItemInfo->remainingPackageOfMagicItem100PercentMegaWin++;
		break;
	case LobbyConstant::ProductType::MAGIC_ITEM_LUCKY_SPIN_10_PERCENT:
		magicItemInfo->remainingPackageOfMagicItemLuckySpinType1++;
		break;
	case LobbyConstant::ProductType::MAGIC_ITEM_LUCKY_SPIN_20_PERCENT:
		magicItemInfo->remainingPackageOfMagicItemLuckySpinType2++;
		break;
	case LobbyConstant::ProductType::MAGIC_ITEM_DOUBLE_EXP:
		magicItemInfo->remainingPackageOfMagicItemDoubleExp++;
		break;
	case LobbyConstant::ProductType::MAGIC_ITEM_LUCKY_SYMBOL:
		magicItemInfo->remainingPackageOfMagicItemLuckySymbol++;
		break;
	default:
		break;
	}
	this->updateStatusItem();
}

PurchaseMagicItem * PurchaseMagicItem::create(PurchaseItemType _purchaseItemType, cocos2d::Sprite *_infoGroup)
{
	PurchaseMagicItem * ret = new (std::nothrow) PurchaseMagicItem();
	ret->currentPruchaseItemTypeList.push_back(_purchaseItemType);
	ret->infoGroup = _infoGroup;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PurchaseMagicItem::init()
{
	if (!cocos2d::ui::Widget::init()) {
		return false;
	}
	std::vector<std::string> iconPaths;
	std::string labelMagicItemImagePath = "";
	std::string labelBuyButtonImagePath = "";

	auto buyBtnSeparator = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_ITEM_FREE_BTN_SEPARATOR);
	switch (this->currentPruchaseItemTypeList[0])
	{
	case MAGIC_ITEM_100_BIG_WIN:
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_100_BIG_WIN);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_100_BIG_WIN_1);
		labelMagicItemImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_100_BIG_WIN;
		labelBuyButtonImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_3_SPINS_$0_99;
		infoString = "Win immediately, up to 100,000 bonus coins";
		this->namePurchaseList.push_back(IAP_MAGIC_ITEM_100_BIG_WIN);
		break;
	case MAGIC_ITEM_100_MEGA_WIN:
		buyBtnSeparator->setPositionX(10);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_100_MEGA_WIN);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_100_MEGA_WIN_1);
		labelMagicItemImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_100_MEGA_WIN;
		labelBuyButtonImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_10_SPINS_$1_99;
		infoString = "Win immediately, up to 1,000,000 bonus coins";
		this->namePurchaseList.push_back(IAP_MAGIC_ITEM_100_MEGA_WIN);
		break;
	case MAGIC_ITEM_LUCKY_10:
		buyBtnSeparator->setPositionX(-5);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_10);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_10_1);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_10_2);
		labelMagicItemImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_LUCKY_10;
		labelBuyButtonImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_1_SPIN_$0_99;
		infoString = "10% chance of win-\nning up to 4,000,000 coins in 1 single spin";
		this->namePurchaseList.push_back(IAP_MAGIC_ITEM_LUCKY_10);
		break;
	case MAGIC_ITEM_LUCKY_20:
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_20);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_20_1);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_20_2);
		labelMagicItemImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_LUCKY_20;
		labelBuyButtonImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_1_SPIN_$1_99;
		infoString = "20% chance of win-\nning up to 4,000,000 coins in 1 single spin";
		this->namePurchaseList.push_back(IAP_MAGIC_ITEM_LUCKY_20);
		break;
	case MAGIC_ITEM_DOUBLE_EXP:
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_DOUBLE_EXP);
		labelMagicItemImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_DOUBLE_EXP;
		labelBuyButtonImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_1_HOUR_$4_99;
		infoString = "Double EXP for every spin in 1 hour";
		this->namePurchaseList.push_back(IAP_MAGIC_ITEM_DOUBLE_EXP);
		break;
	case MAGIC_ITEM_LUCKY_SYMBOL:
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL_1);
		iconPaths.push_back(PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL_2);
		labelMagicItemImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_LUCKY_SYMBOL;
		labelBuyButtonImagePath = PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_1_HOUR_$4_99;
		infoString = "Earn special bonus coin by winning lucky symbol, win up to 2,400,000 coins";
		this->namePurchaseList.push_back(IAP_MAGIC_ITEM_LUCKY_SYMBOL);
		break;
	default:
		return true;
	}
	auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_MAGIC_ITEM);
	bg->setPosition(bg->getContentSize() / 2 + Size(5, 0));
	bg->setCascadeOpacityEnabled(true);
	this->addChild(bg);

	auto infoButton = ui::Button::create(PNG_FRAME_SHOP_INFO_BTN,"","",ui::Widget::TextureResType::PLIST);
	infoButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	infoButton->setPosition(
		bg->getContentSize() - infoButton->getContentSize() / 2 - Size(15, 10)
	);
	infoButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType)
	{
		if (touchType != cocos2d::ui::Widget::TouchEventType::ENDED
			|| !infoGroup)
		{
			return;
		}
		this->infoGroup->setVisible(true);
	});
	bg->addChild(infoButton);

	for (auto iconPath : iconPaths)
	{
		auto iconSprite = Helper4Sprite::createWithSpriteFrameName(iconPath);
		iconSprite->setPosition(
			bg->getContentSize() / 2 + Size(0, 120)
		);
		bg->addChild(iconSprite);
	}

	auto labelSprite = Helper4Sprite::createWithSpriteFrameName(labelMagicItemImagePath);
	labelSprite->setPosition(
		bg->getContentSize() / 2 + Size(0, 20)
	);
	bg->addChild(labelSprite);

	this->buyButton = this->createBuyButton(ShopItemType::MagicItemType,labelBuyButtonImagePath);
	((ButtonScaleChild *)buyButton)->addScaleNode(buyBtnSeparator);

	this->buyButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType)
	{
		if (touchType != cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			return;
		}
		this->onSelected();
	});
	this->buyButton->setPosition(
		bg->getContentSize() / 2 + Size(0, -55)
	);
	bg->addChild(this->buyButton);

	this->activatedSprite = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_MAGIC_ACTIVATED_BOTTOM);
	this->activatedSprite->setVisible(false);
	this->activatedSprite->setCascadeOpacityEnabled(true);
	this->activatedSprite->setPosition(
		bg->getContentSize() / 2 + Size(0, -bg->getContentSize().height / 2 + this->activatedSprite->getContentSize().height / 2)
	);
	bg->addChild(this->activatedSprite);

	this->remaningLabel = Label::createWithBMFont(FONT_BITMAP_ACTIVED_MAGIC_ITEM_SHOP, "15 minutes remaining ");
	this->remaningLabel->setVisible(false);
	this->remaningLabel->setBMFontSize(28);
	this->remaningLabel->setAnchorPoint(Vec2(0.5, 0.5));
	this->remaningLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->remaningLabel->setPosition(
		this->activatedSprite->getContentSize() / 2 + Size(0, -20)
	);
	this->activatedSprite->addChild(remaningLabel);

	this->remainingActivateTimeLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 40),
		"x 1"
	);
	this->remainingActivateTimeLabel->setVisible(false);
	this->remainingActivateTimeLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	this->remainingActivateTimeLabel->setPosition(Vec2(
		10,
		bg->getContentSize().height - 30
	));
	bg->addChild(this->remainingActivateTimeLabel);

	this->activateButton = ui::Button::create(PNG_FRAME_GREEN_POPUP_BUTTON, "", "", ui::Widget::TextureResType::PLIST);
	this->activateButton->setVisible(false);
	auto labelActivateButton = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 40),
		"Activate"
	);
	this->activateButton->setTitleLabel(labelActivateButton);
	this->activateButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	this->activateButton->setPosition(bg->getContentSize() / 2 + Size(0 , -bg->getContentSize().height / 2 + 50));
	this->activateButton->setScale(0.8f);
	this->activateButton->addTouchEventListener(CC_CALLBACK_2(PurchaseMagicItem::onActivateMagicItemBtnClicked, this));

	bg->addChild(this->activateButton);

	return true;
}

void PurchaseMagicItem::updateStatusItem()
{
	auto magicItemInfo = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo;
	int quantityActivate = 0;
	int magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DEFAULT;
	std::string remainingString = "";
	switch (this->currentPruchaseItemTypeList[0])
	{
	case MAGIC_ITEM_100_BIG_WIN:
		quantityActivate = magicItemInfo->remainingPackageOfMagicItem100PercentBigWin;
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN;
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItem100PercentBigWin) 
			+ (magicItemInfo->remainingSpinOfMagicItem100PercentBigWin > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case MAGIC_ITEM_100_MEGA_WIN:
		quantityActivate = magicItemInfo->remainingPackageOfMagicItem100PercentMegaWin;
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN;
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItem100PercentMegaWin)
			+ (magicItemInfo->remainingSpinOfMagicItem100PercentMegaWin > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case MAGIC_ITEM_LUCKY_10:
		quantityActivate = magicItemInfo->remainingPackageOfMagicItemLuckySpinType1;
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1;
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItemLuckySpinType1) 
			+ (magicItemInfo->remainingSpinOfMagicItemLuckySpinType1 > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case MAGIC_ITEM_LUCKY_20:
		quantityActivate = magicItemInfo->remainingPackageOfMagicItemLuckySpinType2;
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2;
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItemLuckySpinType2)
			+ (magicItemInfo->remainingSpinOfMagicItemLuckySpinType2 > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case MAGIC_ITEM_DOUBLE_EXP:
		quantityActivate = magicItemInfo->remainingPackageOfMagicItemDoubleExp;
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DOUBLE_EXP;
		remainingString = UtilFunction::timeStampToSimpleString(magicItemInfo->remainingTimeOfMagicItemDoubleExp) + TAIL_MAGIC_ITEM_REMAINING;
		break;
	case MAGIC_ITEM_LUCKY_SYMBOL:
		quantityActivate = magicItemInfo->remainingPackageOfMagicItemLuckySymbol;
		magicItemTypeIdOfServer = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SYMBOL;
		remainingString = UtilFunction::timeStampToSimpleString(magicItemInfo->remainingTimeOfMagicItemLuckySymbol) + TAIL_MAGIC_ITEM_REMAINING;
		break;
	default:
		return;
	}

	//if this item is activated
	if (magicItemInfo->activeMagicItemType == magicItemTypeIdOfServer) 
	{
		this->remaningLabel->setString(remainingString);
		this->remaningLabel->setVisible(true);
		this->activatedSprite->setVisible(true);
		this->activateButton->setVisible(false);
	}
	else 
	{
		this->remaningLabel->setVisible(false);
		this->activatedSprite->setVisible(false);
		this->activateButton->setVisible(true);
	}

	if (quantityActivate > 0) {
		this->remainingActivateTimeLabel->setString("x " + ToString(quantityActivate));
		this->remainingActivateTimeLabel->setVisible(true);
	}
	else {
		this->remainingActivateTimeLabel->setVisible(false);
		this->activateButton->setVisible(false);
	}
}

void PurchaseBoosterItem::callbackAfterPurchase(int core_result_code, MobilePaymentInfo mobilePaymentInfo)
{
	PurchaseItemNode::callbackAfterPurchase(core_result_code, mobilePaymentInfo);
	if (core_result_code != RESULT_CODE_VALID)
	{
		return;
	}
	PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
		PopupManager::getInstance()->getShopPopup()->getParent(),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::PURCHASED, "approved"),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_CHANGE_LANGUAGE, "success"),
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		"",
		""
	);
	auto boosterInfo = InfoManager::getInstance()->getAdditionalInfo()->boosterInfo;
	boosterInfo->remainingTimeOfBoosterLevelUpBonus += mobilePaymentInfo.boosterLevelUpBonusDurationTimeReward;
	this->updateStatusItem();
}

PurchaseBoosterItem * PurchaseBoosterItem::create(PurchaseItemType _purchaseItemType1, PurchaseItemType _purchaseItemType2, cocos2d::Sprite * _infoGroup)
{
	PurchaseBoosterItem * ret = new (std::nothrow) PurchaseBoosterItem();
	ret->currentPruchaseItemTypeList.push_back(_purchaseItemType1);
	ret->currentPruchaseItemTypeList.push_back(_purchaseItemType2);
	ret->namePurchaseList.push_back(IAP_BOOSTER_1);
	ret->namePurchaseList.push_back(IAP_BOOSTER_2);
	ret->infoGroup = _infoGroup;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool PurchaseBoosterItem::init()
{
	if (!cocos2d::ui::Widget::init()) {
		return false;
	}

	infoString = "Get X10 your Level Up Bonus when you reach levels ending with '0' AND X2 on all other level up bonuses for your purchased duration";
	
	
	auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_PANEL_ITEM_BOOSTER);
	bg->setPosition(bg->getContentSize() / 2 + Size(200, 0));
	bg->setCascadeOpacityEnabled(true);
	this->addChild(bg);

	auto infoButton = ui::Button::create(PNG_FRAME_SHOP_INFO_BTN,"","",ui::Widget::TextureResType::PLIST);
	infoButton->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);
	infoButton->setPosition(
		bg->getContentSize() - infoButton->getContentSize() / 2 - Size(15, 15)
	);
	infoButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType)
	{
		if (touchType != cocos2d::ui::Widget::TouchEventType::ENDED
			|| !infoGroup)
		{
			return;
		}
		this->infoGroup->setVisible(true);
	});
	bg->addChild(infoButton);

	auto icon = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_BOOSTERS);
	icon->setPosition(
		bg->getContentSize() / 2 + Size(0, 155)
	);
	bg->addChild(icon);

	auto boosterText = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_TEXT_BOOSTERS_TEXT_BOOSTERS);
	boosterText->setPosition(
		bg->getContentSize() / 2 + Size(0, 60)
	);
	bg->addChild(boosterText);

	this->buyButton1 = this->createBuyButton(
		ShopItemType::BoostersItemType,
		PNG_FRAME_SHOP_TEXT_BOOSTERS_TEXT_3_DAYS_$2_99
	);
	this->buyButton1->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType)
	{
		if (touchType != cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			return;
		}
		this->onSelected();
	});
	this->buyButton1->setPosition(
		bg->getContentSize() / 2 + Size(0, -10)
	);
	bg->addChild(this->buyButton1);

	this->buyButton2 = this->createBuyButton(
		ShopItemType::BoostersItemType,
		PNG_FRAME_SHOP_TEXT_BOOSTERS_TEXT_7_DAYS_$3_99
	);
	this->buyButton2->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType)
	{
		if (touchType != cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			return;
		}
		this->onSelected(PurchaseItemType::BOOSTER_7_DAYS);
	});
	this->buyButton2->setPosition(
		this->buyButton1->getPosition() + Vec2(0, - this->buyButton2->getContentSize().height - 20)
	);
	bg->addChild(this->buyButton2);

	this->activatedSprite = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SHOP_BOOSTER_ACTIVATED_BOTTOM);
	this->activatedSprite->setVisible(false);
	this->activatedSprite->setCascadeOpacityEnabled(true);
	this->activatedSprite->setPosition(
		bg->getContentSize() / 2 + Size(0, -bg->getContentSize().height / 2 + this->activatedSprite->getContentSize().height / 2)
	);
	bg->addChild(this->activatedSprite);

	this->remaningLabel = Label::createWithBMFont(FONT_BITMAP_ACTIVED_MAGIC_ITEM_SHOP, "15 minutes remaining");
	this->remaningLabel->setVisible(false);
	this->remaningLabel->setAnchorPoint(Vec2(0.5, 0.5));
	//this->remaningLabel->setBMFontSize(30);
	this->remaningLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->remaningLabel->setPosition(
		this->activatedSprite->getContentSize() / 2 + Size(0, -23)
	);
	this->activatedSprite->addChild(remaningLabel);

	return true;
}

void PurchaseBoosterItem::onSelected(int purchaseItemType)
{
	PurchaseItemNode::onSelected(purchaseItemType == PurchaseItemType::BOOSTER_3_DAYS ? 0 : 1);
}

void PurchaseBoosterItem::updateStatusItem()
{
	long remainingTimeBooster = InfoManager::getInstance()->getAdditionalInfo()->boosterInfo->remainingTimeOfBoosterLevelUpBonus;
	if (remainingTimeBooster > 0) {
		this->activatedSprite->setVisible(true);
		this->remaningLabel->setVisible(true);
		this->remaningLabel->setString(UtilFunction::timeStampToSimpleString(remainingTimeBooster) + TAIL_MAGIC_ITEM_REMAINING);
	}
	else {
		this->activatedSprite->setVisible(false);
		this->remaningLabel->setVisible(false);
	}
}
