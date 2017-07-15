#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: ButtonAdjustClikableAreaSize.h, ButtonAdjustClikableAreaSize.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class ButtonAdjustClikableAreaSize : public cocos2d::ui::Button {
cocos2d::Size _clickableAreaSize;
cocos2d::Vec2 _anchorClickableAreaSize;
public:
	ButtonAdjustClikableAreaSize() : Button()
	{
		_clickableAreaSize = Size::ZERO;
		_anchorClickableAreaSize = Vec2::ZERO;
	}

	static ButtonAdjustClikableAreaSize* create() 
	{
		ButtonAdjustClikableAreaSize* widget = new (std::nothrow) ButtonAdjustClikableAreaSize();
		if (widget && widget->init())
		{
			widget->autorelease();
			return widget;
		}
		CC_SAFE_DELETE(widget);
		return nullptr;
	}

	static ButtonAdjustClikableAreaSize* create(
		const std::string &normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::LOCAL) {
		ButtonAdjustClikableAreaSize *btn = new (std::nothrow) ButtonAdjustClikableAreaSize;
		if (btn && btn->init(normalImage, selectedImage, disableImage, texType))
		{
			btn->autorelease();
			return btn;
		}
		CC_SAFE_DELETE(btn);
		return nullptr;
	}
	/// <summary>
	/// set size for clickable region
	/// </summary>
	/// <param name="clickableAreaSize"></param>
	void setClickableAreaSize(Size clickableAreaSize) {
		_clickableAreaSize = clickableAreaSize;
	}
	/// <summary>
	/// set anchor for clickable region
	/// </summary>
	/// <param name="anchorClickableAreaSize"></param>
	void setAnchorClickableAreaSize(Vec2 anchorClickableAreaSize) {
		_anchorClickableAreaSize = anchorClickableAreaSize;
	}
	/// <summary>
	/// check 2 Size if equal
	/// </summary>
	/// <param name="size1"></param>
	/// <param name="size2"></param>
	/// <returns></returns>
	bool compare(Size size1, Size size2) const {
		bool retBool = true;
		retBool = retBool && size1.width == size2.width;
		retBool = retBool && size1.height == size2.height;
		return retBool;
	}
	/// <summary>
	/// change region of click
	/// </summary>
	/// <param name="pt"></param>
	/// <param name="camera"></param>
	/// <param name="p"></param>
	/// <returns></returns>
	bool hitTest(const Vec2 &pt, const Camera* camera, Vec3 *p) const{
		Rect rect;
		rect.size = compare(_clickableAreaSize, Size::ZERO) ? getContentSize() : _clickableAreaSize;
		rect.origin = Vec2(-_anchorClickableAreaSize.x * rect.size.width + getContentSize().width * _anchorClickableAreaSize.x,
			-_anchorClickableAreaSize.y * rect.size.height + getContentSize().height * _anchorClickableAreaSize.y);
		return isScreenPointInRect(pt, camera, getWorldToNodeTransform(), rect, p);
	}
};
