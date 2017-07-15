#include "ReuseItemListView_Vertical.h"

USING_NS_CC;
ReuseItemListView_Vertical * ReuseItemListView_Vertical::create(
	std::vector<cocos2d::ui::Widget*> teamplateItems,
	int totalCount, 
	float itemHeight,
	float spacing,
	float bufferZone,
	float updateInterval
)
{
	ReuseItemListView_Vertical* listView = new (std::nothrow) ReuseItemListView_Vertical();
	listView->_templateItems = teamplateItems;
	listView->_totalCount = totalCount;
	listView->_itemTemplateHeight = itemHeight;
	listView->_updateInterval = updateInterval;
	listView->_spacing = spacing;
	listView->_bufferZone = bufferZone;
	if (listView && listView->init())
	{
		listView->autorelease();
		return listView;
	}
	CC_SAFE_DELETE(listView);
	return nullptr;
}
ReuseItemListView_Vertical::ReuseItemListView_Vertical()
	: _spawnCount(0), //swpanCount should > listview.width / tempalteWidth + 2
	_totalCount(0),
	_bufferZone(130), //bufferZone should be larger than List item width
	_updateTimer(0),
	_updateInterval(1.0f / 24), // you could tweak this value to adjust ListView data update rate
	_lastContentPosY(0), //use this value to detect if we are scrolling left or right
	_itemTemplateHeight(0),
	_spacing(5)
{

}

ReuseItemListView_Vertical::~ReuseItemListView_Vertical()
{
}

bool ReuseItemListView_Vertical::init()
{
	if (ListView::init())
	{

		this->initWithNewItems(this->_templateItems, this->_totalCount, this->_itemTemplateHeight);

		return true;
	}

	return false;
}

float ReuseItemListView_Vertical::getItemPositionYInView(cocos2d::ui::Widget *item) const
{
	auto worldPos = item->getParent()->convertToWorldSpaceAR(item->getPosition());
	auto viewPos = this->convertToNodeSpaceAR(worldPos);
	return viewPos.y;
}

void ReuseItemListView_Vertical::updateItem(int itemID, int templateID)
{
	auto layoutItem = (ui::Widget*)this->getItems().at(templateID);
	layoutItem->setTag(itemID);
	if (!updateItemCallback) {
		return;
	}
	auto templateItem = (ui::Widget*)layoutItem->getChildren().at(0);
	updateItemCallback(itemID, templateItem);
}

void ReuseItemListView_Vertical::update(float dt)
{
	ListView::update(dt);
	this->_updateTimer += dt;
	if (this->_updateTimer < this->_updateInterval) {
		return;
	}

	float totalHeight = _itemTemplateHeight * _totalCount + (_totalCount - 1) * _spacing;

	auto listViewHeight = this->getContentSize().height;

	this->_updateTimer = 0;
	auto isDown = this->getInnerContainerPosition().y < this->_lastContentPosY;
	auto items = this->getItems();

	for (int i = 0; i < _spawnCount && i < _totalCount; ++i) {
		auto item = items.at(i);
		auto itemPos = this->getItemPositionYInView(item);
		if (isDown) {
			if (itemPos < -_bufferZone && item->getPosition().y + _reuseItemOffset < totalHeight) {
				int itemID = item->getTag() - (int)items.size();
				item->setPositionY(item->getPositionY() + _reuseItemOffset);
				this->updateItem(itemID, i);
			}
		}
		else {
			if (itemPos > _bufferZone + listViewHeight &&
				item->getPosition().y - _reuseItemOffset >= 0) {

				item->setPositionY(item->getPositionY() - _reuseItemOffset);
				int itemID = item->getTag() + (int)items.size();
				this->updateItem(itemID, i);
			}
		}
	}
	//update ListView Items
	this->_lastContentPosY = this->getInnerContainer()->getPosition().y;
}

void ReuseItemListView_Vertical::reset()
{
	this->_templateItems.clear();
	this->_spawnCount = 0;
	this->_totalCount = 0;
	this->_bufferZone = 0;
	this->_itemTemplateHeight = 0;
	this->_updateInterval = 0;
	this->_updateTimer = 0;
	this->_lastContentPosY = 0;
	this->_reuseItemOffset = 0;
	this->_spacing = 0;
	/*this->selectedItemEventCallback = nullptr;
	this->selectedItemEventScrollViewCallback = nullptr;
	this->updateItemCallback = nullptr;*/
	this->removeAllChildren();
}

void ReuseItemListView_Vertical::jumpToTopWithNewTotalCount(int totalCount)
{
	/*if (this->_totalCount != totalCount)
	{*/
		Vector<Widget*> items;
		for (auto child : this->getItems())
		{
			child->retain();
			items.pushBack(child);
		}
		this->removeAllItems();

		for (int i = 0; i < items.size(); i++)
		{
			auto child = items.at(i);
			child->setTag(i);
			this->pushBackCustomItem(child);
		}
	//}

	this->_totalCount = totalCount;
	this->forceDoLayout();
	this->jumpToTop();
}

void ReuseItemListView_Vertical::initWithNewItems(std::vector<cocos2d::ui::Widget*> teamplateItems, int totalCount, float itemHeight)
{
	this->removeAllChildren();
	this->_totalCount = totalCount;
	this->_itemTemplateHeight = itemHeight;
	this->_templateItems = teamplateItems;
	this->_spawnCount = teamplateItems.size();
	if (this->_spawnCount == 0) {
		return;
	}
	// set list view ex direction
	this->setDirection(ui::ScrollView::Direction::VERTICAL);
	this->setBounceEnabled(true);
	this->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ReuseItemListView_Vertical::selectedItemEvent, this));
	this->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(ReuseItemListView_Vertical::selectedItemEventScrollView, this));
	
	Layout* default_item = Layout::create();
	default_item->setTouchEnabled(true);
	//default_item->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	default_item->setContentSize(teamplateItems[0]->getCustomSize());
	default_item->setCascadeOpacityEnabled(true);
	//default_item->addChild(teamplateItems[0]);

	// set model
	//this->setItemModel(default_item);

	// set all items layout gravity
	this->setGravity(ListView::Gravity::CENTER_VERTICAL);


	//initial the data
	/*for (int i = 0; i < _totalCount; ++i) {
		if (i < _spawnCount) {
			Widget* item = default_item->clone();
			item->addChild(teamplateItems[i]);
			item->setTag(i);
			this->pushBackCustomItem(item);
		}
	}*/
	for (int i = 0; i < _spawnCount; ++i) {
		Widget* item = default_item->clone();
		item->addChild(teamplateItems[i]);
		item->setTag(i);
		this->pushBackCustomItem(item);
	}

	// set items margin
	this->setItemsMargin(_spacing);
	this->_reuseItemOffset = (_itemTemplateHeight + _spacing) * _spawnCount;

	//update listview data
	this->scheduleUpdate();

	this->forceDoLayout();
	float totalHeight = _itemTemplateHeight * _totalCount + (_totalCount - 1) * _spacing;
	this->setInnerContainerSize(Size(this->getInnerContainerSize().width, totalHeight));
	this->jumpToTop();
}

void ReuseItemListView_Vertical::initWithNewData(
	std::vector<cocos2d::ui::Widget*> teamplateItems,
	int totalCount,
	float itemHeight,
	float spacing,
	float bufferZone,
	float updateInterval)
{
	this->reset();
	this->_templateItems = teamplateItems;
	this->_totalCount = totalCount;
	this->_itemTemplateHeight = itemHeight;
	this->_updateInterval = updateInterval;
	this->_spacing = spacing;
	this->_bufferZone = bufferZone;
	this->initWithNewItems(this->_templateItems, this->_totalCount, this->_itemTemplateHeight);
}

void ReuseItemListView_Vertical::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
	if (selectedItemEventCallback) {
		selectedItemEventCallback(pSender, type);
	}
	/*switch (type)
	{
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
	{
		ListView* listView = static_cast<ListView*>(pSender);
		auto item = listView->getItem(listView->getCurSelectedIndex());
		log("select child start index = %d", item->getTag());
		break;
	}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
	{
		ListView* listView = static_cast<ListView*>(pSender);
		auto item = listView->getItem(listView->getCurSelectedIndex());
		log("select child end index = %d", item->getTag());
		break;
	}
	default:
		break;
	}*/
}

void ReuseItemListView_Vertical::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
	if (selectedItemEventScrollViewCallback) {
		selectedItemEventScrollViewCallback(pSender, type);
	}
	/*switch (type) {
	case ui::ScrollView::EventType::SCROLL_TO_BOTTOM:
		CCLOG("SCROLL_TO_BOTTOM");
		break;
	case ui::ScrollView::EventType::SCROLL_TO_TOP:
		CCLOG("SCROLL_TO_TOP");
		break;
	default:
		break;
	}*/
}
