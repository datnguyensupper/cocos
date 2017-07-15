#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: PPLoginLayer.h, PPLoginLayer.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"


class LoginScene;
class PPLoginLayer : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
private:
	/**
	* 2017-02-06: Kiet: process after click Login button in PPLogin layer
	*/
	void onLoginTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-06: Kiet: process after click "Create new account" in PPLogin layer
	*/
	void onCreateNewAccountTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-06: Kiet: process after click "Forgot your password!" in PPLogin layer
	*/
	void onForgotPasswordTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-06: Kiet: process after click Back Button in PPLogin layer
	*/
	void onBackToMainViewTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);


	cocos2d::ui::EditBox *emailEditBox;
	cocos2d::ui::EditBox *passwordEditBox;

	LoginScene* loginScene;
public:
	/**
	* 2017-02-06: Kiet: create PPLoginLayer
	*/
	static PPLoginLayer* create(LoginScene* parentScene);

    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEndWithAction(cocos2d::ui::EditBox* editBox, cocos2d::ui::EditBoxDelegate::EditBoxEndAction action) override;
	
    // implement the "static create()" method manually
    /// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(PPLoginLayer);
};
