#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-09
* file: ReuseItemListView_Horizontal.h, ReuseItemListView_Horizontal.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ReuseItemListView_Horizontal : public cocos2d::ui::ListView
{
public:
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ReuseItemListView_Horizontal);
	/// <summary>
	/// create list view
	/// </summary>
	/// <param name="teamplateItems">list cell</param>
	/// <param name="totalCount"></param>
	/// <param name="itemHeight"></param>
	/// <param name="spacing"></param>
	/// <param name="bufferZone">addition space for scroll</param>
	/// <param name="updateInterval">time need 2 update scroll</param>
	/// <returns></returns>
	static ReuseItemListView_Horizontal* create(
		std::vector<cocos2d::ui::Widget*> teamplateItems,
		int totalCount,
		float itemWidth,
		float spacing = 5.0f,
		float bufferZone = 130.0f,
		float updateInterval = 1.0f / 24
	);

	ReuseItemListView_Horizontal();
	~ReuseItemListView_Horizontal();

	virtual bool init() override;
	virtual void update(float dt) override;

	void reset();

	void initWithNewItems(
		std::vector<cocos2d::ui::Widget*> teamplateItems,
		int totalCount,
		float itemWidth);
	/// <summary>
	/// init table with data
	/// </summary>
	/// <param name="teamplateItems">list cell</param>
	/// <param name="totalCount"></param>
	/// <param name="itemHeight"></param>
	/// <param name="spacing"></param>
	/// <param name="bufferZone">addition space for scroll</param>
	/// <param name="updateInterval">time need 2 update scroll</param>
	void initWithNewData(
		std::vector<cocos2d::ui::Widget*> teamplateItems,
		int totalCount,
		float itemWidth,
		float spacing = 5,
		float bufferZone = 130.0f,
		float updateInterval = 1.0f / 24
	);
	void setSelectedItemEventCallback(std::function<void(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type)> _selectedItemEventCallback) {
		this->selectedItemEventCallback = _selectedItemEventCallback;
	}
	void setSelectedItemEventScrollViewCallback(std::function<void(Ref* pSender, cocos2d::ui::ScrollView::EventType type)> _selectedItemEventScrollViewCallback) {
		this->selectedItemEventScrollViewCallback = _selectedItemEventScrollViewCallback;
	}
	void setUpdateItemCallback(std::function<void(int newItemID, cocos2d::ui::Widget* templateItem)> _updateItemCallback) {
		this->updateItemCallback = _updateItemCallback;
	}

	//If you want to set infinity -> the template items must push all clone of it's child
	void setInfinity(bool isInfinity);
	//call to auto scroll list view by x - this is should only call when the list view is infinity
	void autoScroll(float x);

	cocos2d::ui::Widget* getRealItem(int index);
protected:
	/// <summary>
	/// get x position of cell
	/// </summary>
	/// <param name="item"></param>
	/// <returns></returns>
	float getItemPositionXInView(cocos2d::ui::Widget* item) const;
	/// <summary>
	/// update item UI
	/// </summary>
	/// <param name="itemID"></param>
	/// <param name="templateID"></param>
	void updateItem(int itemID, int templateID);
	void fixInnerPosition();
	void processAutoScrolling(float deltaTime);
	//how many items we actually spawn, these items will be reused.
	int _spawnCount;
	// how many items we need for the ListView. Usually this is a big number.
	int _totalCount;
	//when item is away from bufferSzone, we relocate it.
	float _bufferZone;
	float _itemTemplateWidth;
	float _updateInterval;
	float _updateTimer;
	float _lastContentPosX;
	float _reuseItemOffset;
	float _spacing;

	bool isInfinity = false;

	std::vector<cocos2d::ui::Widget*> _templateItems;

	void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
	void selectedItemEventScrollView(cocos2d::Ref* sender, cocos2d::ui::ScrollView::EventType type);
	std::function<void(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type)> selectedItemEventCallback = nullptr;
	std::function<void(cocos2d::Ref* pSender, cocos2d::ui::ScrollView::EventType type)> selectedItemEventScrollViewCallback = nullptr;
	std::function<void(int newItemID, cocos2d::ui::Widget* templateItem)> updateItemCallback = nullptr;
};