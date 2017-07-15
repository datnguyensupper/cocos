#include "ReuseItemListView_Horizontal.h"

USING_NS_CC;
ReuseItemListView_Horizontal * ReuseItemListView_Horizontal::create(
	std::vector<cocos2d::ui::Widget*> teamplateItems,
	int totalCount, 
	float itemWidth,
	float spacing,
	float bufferZone,
	float updateInterval
)
{
	ReuseItemListView_Horizontal* listView = new (std::nothrow) ReuseItemListView_Horizontal();
	listView->_templateItems = teamplateItems;
	listView->_totalCount = totalCount;
	listView->_itemTemplateWidth = itemWidth;
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
ReuseItemListView_Horizontal::ReuseItemListView_Horizontal()
	: _spawnCount(0), //swpanCount should > listview.width / tempalteWidth + 2
	_totalCount(0),
	_bufferZone(130), //bufferZone should be larger than List item width
	_updateTimer(0),
	_updateInterval(1.0f / 24), // you could tweak this value to adjust ListView data update rate
	_lastContentPosX(0), //use this value to detect if we are scrolling left or right
	_itemTemplateWidth(0),
	_spacing(5)
{

}

ReuseItemListView_Horizontal::~ReuseItemListView_Horizontal()
{
}

bool ReuseItemListView_Horizontal::init()
{
	if (ListView::init())
	{

		this->initWithNewItems(this->_templateItems, this->_totalCount, this->_itemTemplateWidth);

		return true;
	}

	return false;
}

void ReuseItemListView_Horizontal::setInfinity(bool isInfinity)
{
	this->isInfinity = isInfinity;
	this->setBounceEnabled(false);
	/*if (this->isInfinity && !isInfinity) {
		this->_totalCount = this->_spawnCount * 2;
		float totalWidth = _itemTemplateWidth * _totalCount + (_totalCount - 1) * _spacing;
		this->setInnerContainerSize(Size(totalWidth, this->getInnerContainerSize().height));
	}else if (this->isInfinity && !isInfinity) {
		this->_totalCount = this->_spawnCount;
		float totalWidth = _itemTemplateWidth * _totalCount + (_totalCount - 1) * _spacing;
		this->setInnerContainerSize(Size(totalWidth, this->getInnerContainerSize().height));
	}*/
}

void ReuseItemListView_Horizontal::autoScroll(float x)
{
	this->_innerContainer->setPosition(this->_innerContainer->getPosition() + Vec2(x, 0));
}

float ReuseItemListView_Horizontal::getItemPositionXInView(cocos2d::ui::Widget *item) const
{
	auto worldPos = item->getParent()->convertToWorldSpaceAR(item->getPosition());
	auto viewPos = this->convertToNodeSpaceAR(worldPos);
	return viewPos.x;
}

void ReuseItemListView_Horizontal::updateItem(int itemID, int templateID)
{
	auto layoutItem = (ui::Widget*)this->getItems().at(templateID);
	layoutItem->setTag(itemID);
	if (!updateItemCallback) {
		return;
	}
	auto templateItem = (ui::Widget*)layoutItem->getChildren().at(0);
	updateItemCallback(itemID, templateItem);
}

void ReuseItemListView_Horizontal::fixInnerPosition()
{
	if (this->isInfinity) {
		bool isFixed = false;

		auto innerPosX = this->_innerContainer->getPositionX();
		auto innerSize = this->_innerContainer->getContentSize().width;
		auto contentSize = this->getContentSize().width;

		if (innerPosX >= 0) {

			innerPosX = fmodf(innerPosX, innerSize / 2);

			this->_innerContainer->setPosition(Vec2(innerPosX - innerSize / 2 - this->_spacing / 2, this->getInnerContainerPosition().y));

			isFixed = true;
		}
		else if (innerPosX <= contentSize - innerSize) {

			innerPosX = fmodf(innerPosX, innerSize / 2);

			this->_innerContainer->setPosition(Vec2(innerPosX + this->_spacing / 2, this->getInnerContainerPosition().y));

			isFixed = true;
		}
		/*if (isFixed && this->_autoScrolling) {
			this->_autoScrollStartPosition = this->_innerContainer->getPosition();
		}*/
	}
}

void ReuseItemListView_Horizontal::processAutoScrolling(float deltaTime)
{
	// Make auto scroll shorter if it needs to deaccelerate.
	float brakingFactor = (!this->isInfinity && isNecessaryAutoScrollBrake() ? 0.05f : 1);

	// Elapsed time
	_autoScrollAccumulatedTime += deltaTime * (1 / brakingFactor);

	// Calculate the progress percentage
	float percentage = MIN(1, _autoScrollAccumulatedTime / _autoScrollTotalTime);
	if (_autoScrollAttenuate)
	{
		// Use quintic(5th degree) polynomial
		percentage = tweenfunc::quintEaseOut(percentage);
	}

	// Calculate the new position
	Vec2 newPosition = _autoScrollStartPosition + (_autoScrollTargetDelta * percentage);
	bool reachedEnd = std::abs(percentage - 1) <= this->getAutoScrollStopEpsilon();

	if (reachedEnd)
	{
		newPosition = _autoScrollStartPosition + _autoScrollTargetDelta;
	}

	if (_bounceEnabled)
	{
		// The new position is adjusted if out of boundary
		newPosition = _autoScrollBrakingStartPosition + (newPosition - _autoScrollBrakingStartPosition) * brakingFactor;
	}
	else if(!this->isInfinity)
	{
		// Don't let go out of boundary
		Vec2 moveDelta = newPosition - getInnerContainerPosition();
		Vec2 outOfBoundary = getHowMuchOutOfBoundary(moveDelta);
		if (!fltEqualZero(outOfBoundary))
		{
			newPosition += outOfBoundary;
			reachedEnd = true;
		}
	}

	// Finish auto scroll if it ended
	if (reachedEnd)
	{
		_autoScrolling = false;
		dispatchEvent(cocos2d::ui::ScrollviewEventType::SCROLLVIEW_EVENT_AUTOSCROLL_ENDED, cocos2d::ui::ScrollView::EventType::AUTOSCROLL_ENDED);
	}

	moveInnerContainer(newPosition - getInnerContainerPosition(), reachedEnd);
}

void ReuseItemListView_Horizontal::update(float dt)
{
	//ListView::update(dt);
	if (this->_autoScrolling) {
		this->processAutoScrolling(dt);
	}

	if (this->isInfinity) {
		this->fixInnerPosition();
	}
	float totalWidth = _itemTemplateWidth * _totalCount + (_totalCount - 1) * this->_spacing;

	this->_updateTimer = 0;
	bool isRight = this->getInnerContainer()->getPosition().x < this->_lastContentPosX;
	auto items = this->getItems();

	for (int i = 0; i < _spawnCount && i < _totalCount; ++i) {
		auto item = items.at(i);
		auto itemPos = this->getItemPositionXInView(item);
		if (isRight) {
			if (itemPos < -_bufferZone && item->getPosition().x + _reuseItemOffset < totalWidth) {
				int itemID = item->getTag() + (int)items.size();
				item->setPositionX(item->getPositionX() + _reuseItemOffset);
				this->updateItem(itemID, i);
			}
		}
		else {
			if (itemPos > this->getContentSize().width &&
				item->getPosition().x - _reuseItemOffset >= 0) {

				item->setPositionX(item->getPositionX() - _reuseItemOffset);
				int itemID = item->getTag() - (int)items.size();

				this->updateItem(itemID, i);
			}
		}
	}
	//update ListView Items
	this->_lastContentPosX = this->getInnerContainer()->getPosition().x;
}

void ReuseItemListView_Horizontal::reset()
{
	this->_templateItems.clear();
	this->_spawnCount = 0;
	this->_totalCount = 0;
	this->_bufferZone = 0;
	this->_itemTemplateWidth = 0;
	this->_updateInterval = 0;
	this->_updateTimer = 0;
	this->_lastContentPosX = 0;
	this->_reuseItemOffset = 0;
	this->_spacing = 0;
	/*this->selectedItemEventCallback = nullptr;
	this->selectedItemEventScrollViewCallback = nullptr;
	this->updateItemCallback = nullptr;*/
	this->removeAllChildren();
}

void ReuseItemListView_Horizontal::initWithNewItems(std::vector<cocos2d::ui::Widget*> teamplateItems, int totalCount, float itemWidth)
{
	this->removeAllChildren();
	this->_totalCount = totalCount;
	this->_itemTemplateWidth = itemWidth;
	this->_templateItems = teamplateItems;
	this->_spawnCount = teamplateItems.size();
	if (this->_spawnCount == 0) {
		return;
	}
	// set list view ex direction
	this->setDirection(ui::ScrollView::Direction::HORIZONTAL);

	this->setBounceEnabled(true);
	this->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ReuseItemListView_Horizontal::selectedItemEvent, this));
	this->addEventListener((ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(ReuseItemListView_Horizontal::selectedItemEventScrollView, this));
	
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
	this->_reuseItemOffset = (_itemTemplateWidth + _spacing) * _spawnCount;

	//update listview data
	//this->scheduleUpdate();

	this->forceDoLayout();
	float totalWidth = _itemTemplateWidth * _totalCount + (_totalCount - 1) * _spacing;
	this->setInnerContainerSize(Size(totalWidth, this->getInnerContainerSize().height));
}

void ReuseItemListView_Horizontal::initWithNewData(
	std::vector<cocos2d::ui::Widget*> teamplateItems,
	int totalCount,
	float itemWidth,
	float spacing,
	float bufferZone,
	float updateInterval)
{
	this->reset();
	this->_templateItems = teamplateItems;
	this->_totalCount = totalCount;
	this->_itemTemplateWidth = itemWidth;
	this->_updateInterval = updateInterval;
	this->_spacing = spacing;
	this->_bufferZone = bufferZone;
	this->initWithNewItems(this->_templateItems, this->_totalCount, this->_itemTemplateWidth);
}

void ReuseItemListView_Horizontal::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
	if (selectedItemEventCallback) {
		selectedItemEventCallback(pSender, type);
	}
}

void ReuseItemListView_Horizontal::selectedItemEventScrollView(Ref* pSender, ui::ScrollView::EventType type)
{
	if (selectedItemEventScrollViewCallback) {
		selectedItemEventScrollViewCallback(pSender, type);
	}
}

cocos2d::ui::Widget * ReuseItemListView_Horizontal::getRealItem(int index)
{
	return this->_templateItems[index];
}
