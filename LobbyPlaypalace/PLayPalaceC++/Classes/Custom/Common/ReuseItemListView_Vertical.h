#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-09
* file: ReuseItemListView_Vertical.h, ReuseItemListView_Vertical.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ReuseItemListView_Vertical : public cocos2d::ui::ListView
{
public:
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ReuseItemListView_Vertical);
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
	static ReuseItemListView_Vertical* create(
		std::vector<cocos2d::ui::Widget*> teamplateItems,
		int totalCount,
		float itemHeight,
		float spacing = 5.0f,
		float bufferZone = 130.0f,
		float updateInterval = 1.0f / 24
	);

	ReuseItemListView_Vertical();
	~ReuseItemListView_Vertical();

	virtual bool init() override;
	virtual void update(float dt) override;

	void reset();
	/// <summary>
	/// jump to top of table
	/// </summary>
	/// <param name="totalCount"></param>
	void jumpToTopWithNewTotalCount(int totalCount);
	void initWithNewItems(
		std::vector<cocos2d::ui::Widget*> teamplateItems,
		int totalCount,
		float itemHeight);
	/// <summary>
	/// init data for table
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
		float itemHeight,
		float spacing = 5,
		float bufferZone = 130.0f,
		float updateInterval = 1.0f / 24
	);
	/// <summary>
	/// set callback for selected cell
	/// </summary>
	void setSelectedItemEventCallback(std::function<void(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type)> _selectedItemEventCallback) {
		this->selectedItemEventCallback = _selectedItemEventCallback;
	}
	/// <summary>
	/// set call back for scroll table
	/// </summary>
	void setSelectedItemEventScrollViewCallback(std::function<void(Ref* pSender, cocos2d::ui::ScrollView::EventType type)> _selectedItemEventScrollViewCallback) {
		this->selectedItemEventScrollViewCallback = _selectedItemEventScrollViewCallback;
	}
	/// <summary>
	/// set update for item cell
	/// </summary>
	/// <param name="_updateItemCallback"></param>
	void setUpdateItemCallback(std::function<void(int newItemID, cocos2d::ui::Widget* templateItem)> _updateItemCallback) {
		this->updateItemCallback = _updateItemCallback;
	}
protected:
	float getItemPositionYInView(cocos2d::ui::Widget* item) const;
	void updateItem(int itemID, int templateID);

	//how many items we actually spawn, these items will be reused.
	int _spawnCount;
	// how many items we need for the ListView. Usually this is a big number.
	int _totalCount;
	//when item is away from bufferSzone, we relocate it.
	float _bufferZone;
	float _itemTemplateHeight;
	float _updateInterval;
	float _updateTimer;
	float _lastContentPosY;
	float _reuseItemOffset;
	float _spacing;

	std::vector<cocos2d::ui::Widget*> _templateItems;

	void selectedItemEvent(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
	void selectedItemEventScrollView(cocos2d::Ref* sender, cocos2d::ui::ScrollView::EventType type);
	std::function<void(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type)> selectedItemEventCallback = nullptr;
	std::function<void(cocos2d::Ref* pSender, cocos2d::ui::ScrollView::EventType type)> selectedItemEventScrollViewCallback = nullptr;
	std::function<void(int newItemID, cocos2d::ui::Widget* templateItem)> updateItemCallback = nullptr;
};