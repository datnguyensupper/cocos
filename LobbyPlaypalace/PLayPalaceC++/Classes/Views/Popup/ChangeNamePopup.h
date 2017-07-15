#pragma once
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"

class ChangeNamePopup : public BasePopup
{
protected:
	cocos2d::Label* titleLabel;
	cocos2d::Label* bodyLabel;
	cocos2d::ui::EditBox* nameEditBox;

	cocos2d::ui::Button* btnSend;
	cocos2d::ui::Button* btnCancel;

	/// <summary>
	/// process after click Send Button
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	virtual void sendButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* prepare and show
	*/
	virtual void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ChangeNamePopup);
};