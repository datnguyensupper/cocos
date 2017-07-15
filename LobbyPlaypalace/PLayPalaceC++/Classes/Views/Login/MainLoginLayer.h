#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: MainLoginLayer.h, MainLoginLayer.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"
#include "Constant/Defination.h"

class LoginScene;
class MainLoginLayer : public cocos2d::Layer
{
private:
	/**
	* 2017-02-06: Kiet: process after click "Login As Guess" in main layer 
	*/
	void onLoginGuessTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-06: Kiet: process after click "Login with PP acount" in main layer
	*/
	void onLoginAccountPPTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-06: Kiet: process after click "Login Facebook" in main layer
	*/
	void onLoginFacebookTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-08: Kiet: onLoginTouched guess account
	*/
	void loginGuess(
		std::string username,
		std::string password
	);

	LoginScene* loginScene;

	bool isClickedLogin = false;
public:
	/**
	* 2017-02-06: Kiet: create MainLoginLayer
	*/
	static MainLoginLayer* create(LoginScene* parentScene);

    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();


#if IS_DEBUG
	void forceCallBtnLoginGuest(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
#endif

    // implement the "static create()" method manually
    /// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(MainLoginLayer);
};
