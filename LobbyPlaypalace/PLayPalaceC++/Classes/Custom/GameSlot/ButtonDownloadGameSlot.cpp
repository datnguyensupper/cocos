#include "Custom/GameSlot/ButtonDownloadGameSlot.h"

USING_NS_CC;

void ButtonDownloadGameSlot::firstSetUp() {

	//auto label = Label::createWithSystemFont(_gameId, "Arial", 40);
	//label->setColor(Color3B::BLUE);
	//label->setAnchorPoint(Vec2(0.5, 0.5));
	//label->setPosition(Vec2(getContentSize().width / 2, getContentSize().height / 2));
	//this->addChild(label, 1);
	this->setTitleFontName("Arial");
	this->setTitleFontSize(40);
	this->setTitleColor(Color3B::BLUE);
	this->setTitleText(_gameId);

}

ButtonDownloadGameSlot::ButtonDownloadGameSlot() : Button()
{
	//this->setAnchorPoint(Vec2(0.5, 0.5));
}



ButtonDownloadGameSlot* ButtonDownloadGameSlot::create()
{
	ButtonDownloadGameSlot* widget = new (std::nothrow) ButtonDownloadGameSlot();
	if (widget && widget->init())
	{
		widget->autorelease();
		return widget;
	}
	CC_SAFE_DELETE(widget);
	return nullptr;
}

ButtonDownloadGameSlot* ButtonDownloadGameSlot::create(
	const std::string &gameId,
	const std::string &gameVersion,
	const std::string &normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	TextureResType texType) {
	ButtonDownloadGameSlot *btn = new (std::nothrow) ButtonDownloadGameSlot;
	if (btn && btn->init(normalImage, selectedImage, disableImage, texType))
	{
		btn->autorelease();
		btn->_gameId = gameId;
		btn->_gameVersion = gameVersion;
		btn->firstSetUp();
		return btn;
	}
	CC_SAFE_DELETE(btn);
	return nullptr;
}
