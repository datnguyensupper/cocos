#include "CRadioButton.h"

USING_NS_CC;

void CRadioButton::dispatchSelectChangedEvent(bool selected)
{
	if (this->_titleRenderer) {
		this->_titleRenderer->setTextColor(selected ? this->checkedColor : this->uncheckedColor);
	}

	ui::RadioButton::dispatchSelectChangedEvent(selected);
}

void CRadioButton::onPressStateChangedToNormal()
{
	/*ui::RadioButton::onPressStateChangedToNormal();
	if (this->_titleRenderer) {
		_titleRenderer->setScale(_backgroundTextureScaleX,
			_backgroundTextureScaleY);
	}*/
	ui::RadioButton::setScaleX(_buttonScaleX); 
	ui::RadioButton::setScaleY(_buttonScaleY);
	/*for (auto child : this->getChildren()) {
		child->setScale(_backgroundTextureScaleX,
			_backgroundTextureScaleY);
	}*/
}

void CRadioButton::onPressStateChangedToPressed()
{
	/*ui::RadioButton::onPressStateChangedToPressed();
	if (!_isBackgroundSelectedTextureLoaded && this->_titleRenderer)
	{
		_titleRenderer->setScale(_backgroundTextureScaleX + _zoomScale,
			_backgroundTextureScaleY + _zoomScale);
	}*/
	ui::RadioButton::setScaleX(_buttonScaleX + _zoomScale);
	ui::RadioButton::setScaleY(_buttonScaleY + _zoomScale);

	/*for (auto child : this->getChildren()) {
		child->setScale(_backgroundTextureScaleX + _zoomScale,
			_backgroundTextureScaleY + _zoomScale);
	}*/
}

void CRadioButton::onPressStateChangedToDisabled()
{
	/*ui::RadioButton::onPressStateChangedToDisabled();
	if (this->_titleRenderer) {
		_titleRenderer->setScale(_backgroundTextureScaleX,
			_backgroundTextureScaleY);
	}*/
	ui::RadioButton::setScaleX(_buttonScaleX);
	ui::RadioButton::setScaleY(_buttonScaleY);
	/*for (auto child : this->getChildren()) {
		child->setScale(_backgroundTextureScaleX,
			_backgroundTextureScaleY);
	}*/
}

void CRadioButton::setScaleX(float scaleX)
{
	ui::RadioButton::setScaleX(scaleX);
	this->_buttonScaleX = scaleX;
}

void CRadioButton::setScaleY(float scaleY)
{
	ui::RadioButton::setScaleY(scaleY);
	this->_buttonScaleY = scaleY;
}

CRadioButton * CRadioButton::create()
{
	CRadioButton* widget = new (std::nothrow) CRadioButton();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

CRadioButton * CRadioButton::create(const std::string & backGround, 
	const std::string & backGroundSelected, 
	const std::string & cross, 
	const std::string & backGroundDisabled, 
	const std::string & frontCrossDisabled,
	TextureResType texType)
{
	CRadioButton *pWidget = new (std::nothrow) CRadioButton;
	if (pWidget && pWidget->init(backGround,
		backGroundSelected,
		cross,
		backGroundDisabled,
		frontCrossDisabled,
		texType))
	{
		pWidget->autorelease();
		return pWidget;
	}
	CC_SAFE_DELETE(pWidget);
	return nullptr;
}

CRadioButton * CRadioButton::create(const std::string & backGround, const std::string & cross, TextureResType texType)
{
	CRadioButton *pWidget = new (std::nothrow) CRadioButton;
	if (pWidget && pWidget->init(backGround,backGround,cross,backGround,cross,texType)){
		pWidget->autorelease();
		return pWidget;
	}
	CC_SAFE_DELETE(pWidget);
	return nullptr;
}

void CRadioButton::setTitleRenderer(const std::string & text,
	const std::string & fontName,
	int fontSize,
	const Color4B & checkedColor, 
	const Color4B & uncheckedColor)
{
	if (this->_titleRenderer == nullptr) {
		this->_titleRenderer = Label::createWithTTF(text, fontName, fontSize, this->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
		this->_titleRenderer->setTextColor(this->_isSelected ? checkedColor : uncheckedColor);
		this->_titleRenderer->setPosition(this->getContentSize() / 2);
		this->_titleRenderer->setScale(_backgroundTextureScaleX,
			_backgroundTextureScaleY);
		//this->dispatchSelectChangedEvent(this->_isSelected);
		this->addChild(this->_titleRenderer);
		this->setCascadeOpacityEnabled(true);
	}
	else {
		this->_titleRenderer->initWithTTF(text, fontName, fontSize, this->getContentSize(), TextHAlignment::CENTER, TextVAlignment::CENTER);
	}
	this->checkedColor = checkedColor;
	this->uncheckedColor = uncheckedColor;
}

void CRadioButton::check()
{
	setSelected(true);
	dispatchSelectChangedEvent(true);
}

void CRadioButton::uncheck()
{
	setSelected(false);
	dispatchSelectChangedEvent(false);
}
