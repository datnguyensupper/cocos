#pragma once

#include "ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;

class CRadioButton : public cocos2d::ui::RadioButton{
private:
	cocos2d::Label* _titleRenderer = nullptr;
	cocos2d::Color4B checkedColor;
	cocos2d::Color4B uncheckedColor;

	float _buttonScaleX = 1.0f;
	float _buttonScaleY = 1.0f;

	virtual void dispatchSelectChangedEvent(bool selected) override; 
	
	virtual void onPressStateChangedToNormal() override;
	virtual void onPressStateChangedToPressed() override;
	virtual void onPressStateChangedToDisabled() override;

	virtual void setScaleX(float scaleX) override;
	virtual void setScaleY(float scaleY) override;
public:
	/**
	* Create and return a empty RadioButton instance pointer.
	*/
	static CRadioButton* create();

	/**
	* Create a radio button with various images.
	*
	* @param backGround    backGround texture.
	* @param backGroundSelected    backGround selected state texture.
	* @param cross    cross texture.
	* @param backGroundDisabled    backGround disabled state texture.
	* @param frontCrossDisabled    cross dark state texture.
	* @param texType    @see `Widget::TextureResType`
	*
	* @return A RadioButton instance pointer.
	*/
	static CRadioButton* create(const std::string& backGround,
		const std::string& backGroundSelected,
		const std::string& cross,
		const std::string& backGroundDisabled,
		const std::string& frontCrossDisabled,
		TextureResType texType = TextureResType::LOCAL);

	/**
	* Another factory method to create a RadioButton instance.
	* This method uses less resource to create a RadioButton.
	* @param backGround The background image name in `std::string`.
	* @param cross The cross image name in `std::string`.
	* @param texType  The texture's resource type in `Widget::TextureResType`.
	* @return A RadioButton instance pointer
	*/
	static CRadioButton* create(const std::string& backGround,
		const std::string& cross,
		TextureResType texType = TextureResType::LOCAL);

	cocos2d::Label* getTitleRenderer() { return this->_titleRenderer; }

	/**
	* create Title Renderer for button, can set color change when checked/unchecked
	* currently, only support ttf
	*/
	void setTitleRenderer(const std::string& text,
		const std::string& fontName,
		int fontSize, 
		const Color4B& checkedColor = Color4B::WHITE,
		const Color4B& uncheckedColor = Color4B::GRAY);
	/**
	* set this buton state to check - using this when this button contains text
	*/
	void check();
	/**
	* set this buton state to uncheck - using this when this button contains text
	*/
	void uncheck();
};