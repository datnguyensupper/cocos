#include "ButtonScaleChild.h"
#include "Constant/Defination.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"
#include "Util/UtilFunction.h"

#define ZOOM_ACTION_TIME_STEP 0.005f
USING_NS_CC;

ButtonScaleChild::ButtonScaleChild()
{
	this->scaleNode = CCNode::create();
	this->scaleNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
}

ButtonScaleChild* ButtonScaleChild::create()
{
	ButtonScaleChild* widget = new (std::nothrow) ButtonScaleChild();
	widget->addChild(widget->scaleNode);
	if (widget && widget->init())
	{
        widget->autorelease();
//        widget->initUITitleLabel();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

ButtonScaleChild* ButtonScaleChild::create(
	const std::string& normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	TextureResType texType) {
	ButtonScaleChild *btn = new (std::nothrow) ButtonScaleChild;
	if (btn && btn->init(normalImage, selectedImage, disableImage, texType))
	{
		btn->autorelease();
//        btn->initUITitleLabel();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}

/** replaces the current Label node with a new one */
void ButtonScaleChild::setTitleLabel(Label* label)
{
    cocos2d::ui::Button::setTitleLabel(label);
    initUITitleLabel();
}

bool ButtonScaleChild::initUITitleLabel()
{
    
    originalTitleScaleX = 1;
    originalTitleScaleY = 1;
    if(_titleRenderer){
        originalTitleScaleX = _titleRenderer->getScaleX();
        originalTitleScaleY = _titleRenderer->getScaleY();
    }
    
    return true;
}

void ButtonScaleChild::onPressStateChangedToNormal()
{
	auto tempTitle = this->_titleRenderer;
	this->_titleRenderer = nullptr;
	ui::Button::onPressStateChangedToNormal();
	this->_titleRenderer = tempTitle;
	if (_pressedTextureLoaded)
	{
		if (_pressedActionEnabled)
		{
			if (nullptr != this->scaleNode)
			{
				this->scaleNode->stopAllActions();
				if (_unifySize)
				{
					Action *zoomTitleAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, 1.0f, 1.0f);
					this->scaleNode->runAction(zoomTitleAction);
				}
				else
				{
					this->scaleNode->setScaleX(1.0f);
					this->scaleNode->setScaleY(1.0f);
				}
			}
			if (nullptr != _titleRenderer)
			{
				_titleRenderer->stopAllActions();
				if (_unifySize)
				{
					Action *zoomTitleAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP, originalTitleScaleX, originalTitleScaleY);
					_titleRenderer->runAction(zoomTitleAction);
				}
				else
				{
					_titleRenderer->setScaleX(originalTitleScaleX);
					_titleRenderer->setScaleY(originalTitleScaleY);
				}
			}
		}
	}
	else
	{
		if (nullptr != this->scaleNode)
		{
			this->scaleNode->stopAllActions();
			this->scaleNode->setScaleX(1.0f);
			this->scaleNode->setScaleY(1.0f);
		}
		if (nullptr != _titleRenderer)
		{
			_titleRenderer->stopAllActions();
			_titleRenderer->setScaleX(originalTitleScaleX);
			_titleRenderer->setScaleY(originalTitleScaleY);
		}
	}
}

void ButtonScaleChild::onPressStateChangedToPressed()
{
	auto tempTitle = this->_titleRenderer;
	this->_titleRenderer = nullptr;
	ui::Button::onPressStateChangedToPressed();
	this->_titleRenderer = tempTitle;
	if (_pressedTextureLoaded)
	{
		if (_pressedActionEnabled)
		{
			if (nullptr != this->scaleNode)
			{
				this->scaleNode->stopAllActions();
				Action *zoomTitleAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP,
					1.0f + _zoomScale, 1.0f + _zoomScale);
				this->scaleNode->runAction(zoomTitleAction);
			}
		}
		if (nullptr != _titleRenderer)
		{
			_titleRenderer->stopAllActions();
			Action *zoomTitleAction = ScaleTo::create(ZOOM_ACTION_TIME_STEP,
				originalTitleScaleX + _zoomScale, originalTitleScaleY + _zoomScale);
			_titleRenderer->runAction(zoomTitleAction);
		}
	}
	else
	{
		if (nullptr != this->scaleNode)
		{
			this->scaleNode->stopAllActions();
			this->scaleNode->setScaleX(1.0f + _zoomScale);
			this->scaleNode->setScaleY(1.0f + _zoomScale);
		}
		if (nullptr != _titleRenderer)
		{
			_titleRenderer->stopAllActions();
			_titleRenderer->setScaleX(originalTitleScaleX + _zoomScale);
			_titleRenderer->setScaleY(originalTitleScaleY + _zoomScale);
		}
	}
}
void ButtonScaleChild::onSizeChanged()
{
	Button::onSizeChanged();
	if (this->scaleNode)
	{
		this->scaleNode->setPosition(_contentSize.width * 0.5f, _contentSize.height * 0.5f);
	}
}
