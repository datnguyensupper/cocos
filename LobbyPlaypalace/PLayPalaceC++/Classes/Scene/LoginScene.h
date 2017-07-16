#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: Login.h, Login.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Configs.h"
#include "Constant/MessageConstant.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/Defination.h"
#include "Constant/PPEnums.h"
#include "Constant/JSONFieldConstant.h"
#include "Manager/NetworkManager.h"
#include "Scene/InitSessionScene.h"

#include "BaseScene.h"

class MainLoginLayer;
class PPLoginLayer;
class ResetPassLayer;
class SignUpLayer;
class NotiLoginPopup;
enum LoginViews {
	MainLoginView,
	PPLoginView,
	ResetPassView,
	SignUpView
};
class LoginScene : public BaseScene
{
private:
	MainLoginLayer* mainLoginLayer;
	PPLoginLayer* ppLoginLayer;
	ResetPassLayer* resetPassLayer;
	SignUpLayer* signUpLayer;
	cocos2d::Node * parent;

	NotiLoginPopup* notificationLoginPopup;
    
public:
	/// <summary>
	/// create login scene
	/// </summary>
	/// <param name="title">title for first notification popup if error in previous scene</param>
	/// <param name="message">message for first notification popup if error in previous scene</param>
	/// <returns></returns>
    static cocos2d::Scene* createScene(std::string title, std::string message);

    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
    
    void check4AutoLogin();
    
    // implement the "static create()" method manually
    /// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LoginScene);

	/**
	* 2017-02-06: Kiet: move camera to loginView 
	* base on loginviews to determine destination
	* @param loginView LoginViews::MainLoginView, LoginViews::PPLoginView, LoginViews::ResetPassView, LoginViews::SignUpView
	*/
	void moveCameraToView(LoginViews loginView);

	/**
	* 2017-02-08: Kiet: show notification popup
	*/
	void showNotificationLoginPopup(
		std::string title,
		std::string body,
		std::function <void(void)> callbackOK = nullptr,
		std::function <void(void)> callbackCancle = nullptr
	);

	/**
	* 2017-02-08: Kiet: show popup error base on result code for onLoginTouched scene
	*/
	void handleErrorResultCodeForLoginScene(
		int coreResultCode,
		const std::string &title = ""
	);

	/**
	* 2017-02-06: Kiet: get methods
	*/
	MainLoginLayer* getMainLoginLayer() { return mainLoginLayer; }
	PPLoginLayer* getPPLoginLayer() { return ppLoginLayer; }
	ResetPassLayer* getResetPassLayer() { return resetPassLayer; }
	SignUpLayer* getSignUpLayer() { return signUpLayer; }
};
