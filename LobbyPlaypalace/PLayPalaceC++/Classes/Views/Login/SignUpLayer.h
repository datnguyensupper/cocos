#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: SignUpLayer.h, SignUpLayer.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LoginScene;
class SignUpLayer : public cocos2d::Layer
{
private:
	/**
	* 2017-02-06: Kiet: process after click Back Button in SignUpLayer layer
	*/
	void onBackToLoginViewTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-06: Kiet: process after click SignUp Button in SignUpLayer layer
	*/
	void onSignUpTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	cocos2d::ui::EditBox *emailEditBox;
	cocos2d::ui::EditBox *passwordEditBox;
	cocos2d::ui::EditBox *retypePasswordEditBox;
	cocos2d::ui::EditBox *referenceCodeEditBox;
	
	LoginScene* loginScene;
public:
	/**
	* 2017-02-06: Kiet: create SignUpLayer
	*/
	static SignUpLayer* create(LoginScene* parentScene);

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
	CREATE_FUNC(SignUpLayer);
};
