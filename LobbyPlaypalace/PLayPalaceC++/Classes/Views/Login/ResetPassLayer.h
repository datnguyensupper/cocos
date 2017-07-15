#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: ResetPassLayer.h, ResetPassLayer.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"

class LoginScene;
class ResetPassLayer : public cocos2d::Layer
{
private:
	/**
	* 2017-02-06: Kiet: process after click Back Button in ResetPassLayer layer
	*/
	void onBackToLoginViewTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-06: Kiet: process after click Submit Button in ResetPassLayer layer
	*/
	void onSubmitResetPasswordTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);


	cocos2d::ui::EditBox *emailEditBox;
	LoginScene* loginScene;
public:
	/**
	* 2017-02-06: Kiet: create ResetPassLayer
	*/
	static ResetPassLayer* create(LoginScene* parentScene);

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
	CREATE_FUNC(ResetPassLayer);
};
