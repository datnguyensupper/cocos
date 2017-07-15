#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: NotiLoginPopup.h, NotiLoginPopup.cpp
*/
#include "cocos2d.h"


#include "ui/CocosGUI.h"
#include "Views/Popup/BasePopup.h"


class LoginScene;
class NotiLoginPopup : public BasePopup
{
private:
	cocos2d::Label* titleLabel;
	cocos2d::Label* bodyLabel;
	LoginScene* loginScene;

	std::function <void(void)> callbackOK; //when click button ok
	std::function <void(void)> callbackCancel; //when click close popup
	/**
	* 2017-02-08: Kiet: process after click OK Button in main layer
	*/
	void okButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-08: Kiet: process after click Close Popup in main layer
	*/
	void closePopupButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

public:
	/**
	* 2017-02-06: Kiet: create NotiLoginPopup
	*/
	static NotiLoginPopup* create(LoginScene* parentScene);

	/**
	* 2017-02-08: Kiet: show this popup
	*/
	void show(
		LoginScene* parentScene,
		std::string title,
		std::string body,
		std::function <void(void)> callbackOK = nullptr,
		std::function <void(void)> callbackCancel = nullptr
	);

    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
    
    // implement the "static create()" method manually
    /// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(NotiLoginPopup);
};
