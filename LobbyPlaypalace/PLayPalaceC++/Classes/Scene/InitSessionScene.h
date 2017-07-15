#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: InitSession.h, InitSession.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Constant/PPEnums.h"
#include "BaseScene.h"

class InitSessionScene : public BaseScene
{
private:
	cocos2d::ProgressTimer *loadingProgessTimer;
	cocos2d::Label *loadingLabel;

	ppEnum::LoginAndInitSSFrom loginFrom;

	/**
	* server request step1
	* 2017-02-13: Kiet: after init function, if:
	* login as Guess: getDataFromServer
	* login as PP account: authorizeSession->getDataFromServer
	* login FB: call FB to get token->call to server login with facebook token -> getDataFromServer
	*/
	void processAfterInit();
	/**
	* server request step2
	* 2017-02-13: Kiet: call API /user/getAllData and get configs server, list game slot, ...
	*/
	void getDataFromServer();
	/// <summary>
	/// server request step3
	/// Dat: call API /user/featureConfig/getAll
	/// </summary>
	void getFeatureConfigInfoAndCollectDataInfo(std::function<void()> callbackAfterGet);
	/**
	* 2017-02-13: Kiet: call API /user/getAdditionalInfo and get data
	* server request step4
	*/
	void getAdditionalInfo();
	/**
	* Dat : check and go to next scene
	* server request step 5
	*/
	void checkAndGoToNextScene(bool isSuccess);

	/**
	* 2017-03-15: Kiet: update progress timer loading
	* @param loadingLabel empty if not change
	*/
	void updateProgressTimerLoading(float percent, bool isRunAnimation = true, std::string loadingLabel = "");
public:
	static cocos2d::Scene* createScene(ppEnum::LoginAndInitSSFrom _loginFrom);
    void onEnter();
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
    /// <summary>
    /// update function call after each frame
    /// </summary>
    /// <param name="delta"></param>
    void update(float delta);

	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(InitSessionScene);
};
