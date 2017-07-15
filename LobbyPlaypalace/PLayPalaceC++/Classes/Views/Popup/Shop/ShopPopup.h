#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-01
* file: ShopPopup.h, ShopPopup.cpp
*/
#include "Views/Popup/BasePopup.h"
#include "PurchaseItemNode.h"

enum ShopType
{
	CoinShop,
	CrownShop,
	MagicItemShop,
	BoostersShop
};
class ShopPopup : public BasePopup
{
private:
	cocos2d::ui::ListView* coinGroupListView;
	cocos2d::ui::ListView* crownGroupListView;
	cocos2d::ui::ScrollView* magicItemGroupListView;
	cocos2d::ui::ListView* boosterGroupListView;

	cocos2d::ui::Button* maskCoinBtn;
	cocos2d::ui::Button* maskCrownBtn;
	cocos2d::ui::Button* maskMagicBtn;
	cocos2d::ui::Button* maskBoosterBtn;

	/**
	* 2017-02-18: Kiet: go to coin tab
	*/
	void gotoCoinTab();
	/**
	* 2017-02-18: Kiet: go to crown tab
	*/
	void gotoCrownTab();
	/**
	* 2017-02-18: Kiet: go to magic tab
	*/
	void gotoMagicTab();
	/**
	* 2017-02-18: Kiet: go to booster tab
	*/
	void gotoBoosterTab();
	/**
	* 2017-03-29: Kiet: check and set enable button free coin
	*/
	void checkAndSetEnableFreeCoinButton(float dt);
	/// <summary>
	/// 2017-04-08: Kiet: create list view for tabs
	/// </summary>
	/// <param name="shopType"></param>
	/// <param name="count">number of items</param>
	/// <returns></returns>
	cocos2d::ui::ListView *createListViewForTabs(
		ShopType shopType,
		int count
	);
	virtual void playSoundOpenPopup() override;
public:
	/**
	* 2017-02-18: Kiet: init shop popup
	*/
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// 2017-02-18: Kiet: prepare and show
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="shopType">type of shop</param>
	void prepareAndShow(
		cocos2d::Node* parent,
		ShopType shopType
	);

	/**
	* 2017-02-18: Kiet: activate magic item
	*/
	void activateMagicItem(int magicItemTypeIdOfServer);
	/**
	* select item manually
	*/
	void selecteItem(PurchaseItemType itemType);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ShopPopup);
};