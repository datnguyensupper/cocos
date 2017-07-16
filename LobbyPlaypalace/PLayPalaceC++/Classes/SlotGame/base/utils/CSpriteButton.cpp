#include "CSpriteButton.h"

USING_NS_CC;
namespace GameSlot {
	CSpriteButton::CSpriteButton() :
		touchRect(cocos2d::Rect::ZERO),
		scaleDown(1.0f),
		scaleUp(1.0f),
		frameNormal(""),
		frameTouching(""),
		frameDisable(""),
		isBlock(false),
		isCallOnUpWithouCheck(false),
		onDown(nullptr),
		onUp(nullptr),
		onMove(nullptr),
		onLongTouch(nullptr)
	{
	}
	CSpriteButton::~CSpriteButton()
	{
	}
	CSpriteButton * CSpriteButton::createButtonWithFile(
		const std::string& fileName,
		const std::function<void()>& onDown,
		const std::function<void()>& onUp)
	{
		CSpriteButton* pSprite = new CSpriteButton();

		if (pSprite->initWithFile(fileName))
		{
			pSprite->onDown = onDown;

			pSprite->onUp = onUp;

			pSprite->autorelease();

			pSprite->addEvents();

			return pSprite;
		}
		

		CC_SAFE_DELETE(pSprite);
		return NULL;
	}

	CSpriteButton * CSpriteButton::createButtonWithSpriteFrameName(
		const std::string& spriteName,
		const std::function<void()>& onDown,
		const std::function<void()>& onUp)
	{
		CSpriteButton* pSprite = new CSpriteButton();

		if (pSprite->initWithSpriteFrameName(spriteName))
		{
			pSprite->frameNormal = spriteName;

			pSprite->onDown = onDown;

			pSprite->onUp = onUp;

			pSprite->autorelease();

			pSprite->addEvents();

			return pSprite;
		}


		CC_SAFE_DELETE(pSprite);
		return NULL;
	}

	CSpriteButton * CSpriteButton::createInvisibleButton(
		const cocos2d::Rect& rect,
		const std::function<void()>& onDown,
		const std::function<void()>& onUp)
	{
		CSpriteButton* pSprite = new CSpriteButton();

		if (pSprite->init())
		{
			pSprite->touchRect = rect;

			pSprite->onDown = onDown;

			pSprite->onUp = onUp;

			pSprite->autorelease();

			pSprite->addEvents();

			return pSprite;
		}

		CC_SAFE_DELETE(pSprite);
		return NULL;
	}

	void CSpriteButton::setOnTouchDown(const std::function<void()>& onDown)
	{
		this->onDown = onDown;
	}

	void CSpriteButton::setOnTouchUp(const std::function<void()>& onUp)
	{
		this->onUp = onUp;
	}

	void CSpriteButton::setLongTouch(float duration, const std::function<void()>& onLongTouch)
	{
		this->longTouchDuration = duration;
		this->onLongTouch = onLongTouch;
	}

	void CSpriteButton::setOnTouchMove(std::function<void(cocos2d::Touch*touch)> onMove)
	{
		this->onMove = onMove;
	}

	void CSpriteButton::setTouchEnabled(bool isEnabled)
	{
		if (!this->frameDisable.empty()) {
			this->setSpriteFrame(isEnabled ? this->frameNormal : this->frameDisable);
		}
		listener->setEnabled(isEnabled);
	}

	void CSpriteButton::changeSpriteFrameToNormal()
	{
		this->setSpriteFrame(this->frameNormal);
	}

	void CSpriteButton::changeSpriteFrameToTouching()
	{
		if (!this->frameTouching.empty()) {
			this->setSpriteFrame(this->frameTouching);
		}
	}

	void CSpriteButton::changeSpriteFrameToDisable()
	{
		if (!this->frameDisable.empty()) {
			this->setSpriteFrame(this->frameDisable);
		}
	}

	void CSpriteButton::addEvents()
	{
		listener = cocos2d::EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			if (this->checkCanRunListener(touch))
			{
				this->isTouching = true;
				this->isTouchBegin = true;
				if (!this->isBlock) {
					this->onDownEvent();
				}
				return true; // to indicate that we have consumed it.
			}

			return false; // we did not consume this event, pass thru.
		};

		listener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			if (!this->isTouchBegin) return;

			auto isTouching = this->checkCanRunListener(touch);
			if (!this->isBlock) {
				if (this->isTouching && !isTouching) {
					this->normalState();
				}
				else if(isTouching){
					if (!this->isTouching) {
						this->pressedState();
					}
					if (this->onMove) {
						this->onMove(touch);
					}
				}
			}
			this->isTouching = isTouching;
		};

		listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
		{
			if (!this->isBlock) {

				if (this->isTouching || isCallOnUpWithouCheck)
				{
					this->onUpEvent();
				}
			}
		};

		cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
	}
	bool CSpriteButton::isButtonVisible()
	{
		auto node = this->getParent();

		while (node) {
			if (!node->isVisible()) return false;
			node = node->getParent();
		}

		return this->isVisible();
	}
	void CSpriteButton::onDownEvent()
	{
		this->pressedState();
		if (this->onDown != nullptr) {
			this->onDown();
		}
	}
	void CSpriteButton::onUpEvent()
	{
		this->normalState();
		if (this->onUp != nullptr) {
			this->onUp();
		}
		this->isTouchBegin = false;
	}
	bool CSpriteButton::checkCanRunListener(cocos2d::Touch* touch)
	{
		if (!this->isButtonVisible()) {
			return false;
		}
		cocos2d::Vec2 p = this->convertToNodeSpace(touch->getLocation());

		cocos2d::Rect rect = this->touchRect;

		if (rect.equals(cocos2d::Rect::ZERO)) {
			rect = cocos2d::Rect(Vec2::ZERO, this->getContentSize());
		}

		if (rect.containsPoint(p))
		{
			return true; // to indicate that we have consumed it.
		}

		return false;
	}
	void CSpriteButton::longTouchUpdate(float dt)
	{
		if (this->isTouching) {
			this->longTouchTime += dt;
			if (this->longTouchTime >= this->longTouchDuration) {
				this->longTouchTime = 0;
				this->onLongTouch();
				this->normalState();
				this->isTouchBegin = false;
			}
		}
	}
	void CSpriteButton::normalState()
	{
		if (!this->frameTouching.empty()) {
			this->setSpriteFrame(this->frameNormal);
		}
		if (scaleDown != scaleUp) {
			this->setScale(scaleUp);
		}
		this->isTouching = false;
		if (this->onLongTouch) {
			this->longTouchTime = 0;
			this->unschedule(schedule_selector(CSpriteButton::longTouchUpdate));
		}
	}
	void CSpriteButton::pressedState()
	{
		if (!this->frameTouching.empty()) {
			this->setSpriteFrame(this->frameTouching);
		}
		if (scaleDown != scaleUp) {
			this->setScale(scaleDown);
		}
		this->isTouching = true;
		if (this->onLongTouch) {
			this->longTouchTime = 0;
			this->schedule(schedule_selector(CSpriteButton::longTouchUpdate));
		}
	}
}