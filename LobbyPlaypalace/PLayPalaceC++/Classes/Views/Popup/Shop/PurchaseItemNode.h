#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-01
* file: PurchaseItemNode.h, PurchaseItemNode.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Manager/PluginManager.h"
#include "Custom/Common/ButtonScaleChild.h"

enum PurchaseItemType
{
	FREE_COINS,

	COINS_400K,
	COINS_800K,
	COINS_2M,
	COINS_4M,
	COINS_8M,
	COINS_20M,
	COINS_40M,

	CROWNS_10,
	CROWNS_55,
	CROWNS_120,

	MAGIC_ITEM_100_BIG_WIN, //free
	MAGIC_ITEM_100_MEGA_WIN,
	MAGIC_ITEM_LUCKY_10,
	MAGIC_ITEM_LUCKY_20,
	MAGIC_ITEM_DOUBLE_EXP,
	MAGIC_ITEM_LUCKY_SYMBOL,

	BOOSTER_3_DAYS,
	BOOSTER_7_DAYS
};
enum ShopItemType
{
	CoinItemType,
	CrownItemType,
	MagicItemType,
	BoostersItemType
};
class PurchaseItemNode : public cocos2d::ui::Widget
{
protected:
	std::vector<std::string> namePurchaseList; //many purchase in a node
	std::vector<PurchaseItemType> currentPruchaseItemTypeList; //many purchase in a node
	
	/**
	* 2017-04-10: Kiet: create buy button
	*/
	ButtonScaleChild* createBuyButton(
		ShopItemType typeShopItemOfButton,
		std::string labelImagePath);


	/// <summary>
	/// callback after purchase
	/// </summary>
	/// <param name="core_result_code">0 if buying sucess</param>
	/// <param name="mobilePaymentInfo">info of purchase</param>
	virtual void callbackAfterPurchase(
		int core_result_code,
		MobilePaymentInfo mobilePaymentInfo);

public:
	/**
	* callback when touch item
	* @param purchasePos determine position of purchase in namePurchaseList
	*/
	virtual void onSelected(int purchasePos = 0);

	/**
	* 2017-04-10: Kiet: create info group (using for magic item + booster)
	* @param shopType : magic item or booster
	*/
	static cocos2d::Sprite *createInfoGroup(
		ShopItemType shopItemType
	);
};

class PurchaseCoinCrownItem : public PurchaseItemNode
{
private:
	cocos2d::ui::Button* buyButton;
	bool isItemAdcolony = false;

	/// <summary>
	/// callback after purchase
	/// </summary>
	/// <param name="core_result_code">0 if buying sucess</param>
	/// <param name="mobilePaymentInfo">info of purchase</param>
	void callbackAfterPurchase(
		int core_result_code,
		MobilePaymentInfo mobilePaymentInfo) override;

	/// <summary>
	/// 2017-02-03: Kiet: callback after on reward adcolony call
	/// </summary>
	/// <param name="info">info of ad video</param>
	/// <param name="currencyName">currency of reward after watching video</param>
	/// <param name="amount">amount of reward</param>
	/// <param name="success">is watch video success</param>
	void callbackRewardVideoAdcolony(
		const sdkbox::AdColonyAdInfo& info,
		const std::string& currencyName,
		int amount,
		bool success);
public:
	static PurchaseCoinCrownItem* create(PurchaseItemType _purchaseItemType);
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* 2017-03-13: Kiet: set enable buy button
	*/
	void setEnableBuyButton(bool isEnable);
	/// <summary>
	/// selected buy button
	/// </summary>
	/// <param name="purchasePos">position of item</param>
	void onSelected(int purchasePos = 0) override;
};

class PurchaseMagicItem : public PurchaseItemNode
{
private:
	cocos2d::ui::Button *buyButton;
	cocos2d::Sprite *activatedSprite;
	cocos2d::Label *remaningLabel;
	cocos2d::Sprite *infoGroup;
	cocos2d::Label *remainingActivateTimeLabel;
	cocos2d::ui::Button *activateButton;

	/**
	* 2017-03-13: Kiet: on activate magic item button clicked
	*/
	void onActivateMagicItemBtnClicked(cocos2d::Ref *ref, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// callback after purchase
	/// </summary>
	/// <param name="core_result_code">0 if buying sucess</param>
	/// <param name="mobilePaymentInfo">info of purchase</param>
	void callbackAfterPurchase(
		int core_result_code,
		MobilePaymentInfo mobilePaymentInfo) override;
public:
	std::string infoString = "";
	/// <summary>
	/// create magic item ui
	/// </summary>
	/// <param name="_purchaseItemType"></param>
	/// <param name="_infoGroup"></param>
	/// <returns></returns>
	static PurchaseMagicItem* create(
		PurchaseItemType _purchaseItemType,
		cocos2d::Sprite *_infoGroup);
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// update ui of items
	/// </summary>
	void updateStatusItem();
};

class PurchaseBoosterItem : public PurchaseItemNode
{
private:
	cocos2d::ui::Button *buyButton1;
	cocos2d::ui::Button *buyButton2;
	cocos2d::Sprite *activatedSprite;
	cocos2d::Label *remaningLabel;
	cocos2d::Sprite *infoGroup;
	/// <summary>
	/// callback after purchase
	/// </summary>
	/// <param name="core_result_code">0 if buying sucess</param>
	/// <param name="mobilePaymentInfo">info of purchase</param>
	void callbackAfterPurchase(
		int core_result_code,
		MobilePaymentInfo mobilePaymentInfo) override;
public:
	std::string infoString = "";
	/// <summary>
	/// create booster item 
	/// </summary>
	/// <param name="_purchaseItemType1">item type of booster 1</param>
	/// <param name="_purchaseItemType2">item type of booster 2</param>
	/// <param name="_infoGroup">group of info</param>
	/// <returns></returns>
	static PurchaseBoosterItem* create(
		PurchaseItemType _purchaseItemType1,
		PurchaseItemType _purchaseItemType2,
		cocos2d::Sprite *_infoGroup);
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// buy button clicked
	/// </summary>
	/// <param name="purchaseItemType"></param>
	void onSelected(int purchaseItemType = PurchaseItemType::BOOSTER_3_DAYS) override;
	/// <summary>
	/// update ui of item in tab
	/// </summary>
	void updateStatusItem();
};
