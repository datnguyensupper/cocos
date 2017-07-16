#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-18
* file: BasePopup.h, BasePopup.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class UserInfo;
class HeaderLobbyLayout;
class LobbyScene;
class Welcome : public cocos2d::Node {
private:
	cocos2d::ui::Button* oClaimBtn;
	cocos2d::Label* lb_welcome;
public:

	//init func
	bool init() override;
	void updateWelcomeText();
	//set on claim coin callback
	void addOnClaimListener(const std::function<void(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)>& claimCallBack);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(Welcome);
};

enum TutorialStep {
	StepWelcome = 0,
	StepSelectGame = 1,
	StepChangeBet = 2,
	StepCustomizeIntro = 3,
	StepSpin = 4,
	StepReturnLobby = 5,
	StepShowAchivement = 6,
	StepShowShop = 7,
	StepWatchVideo = 8,
	StepEnd = 9,
};

struct TutorialInfo {
	TutorialStep iCurStep = TutorialStep::StepWelcome;
	bool isFirstLogin = true;
	bool isComplete = false;
};

class Tutorial : public cocos2d::Node
{
private:
	TutorialInfo info;

	HeaderLobbyLayout* oHeaderUI;
	UserInfo* userInfo;

	Welcome* oWelcome;
	cocos2d::Node* oTutorial;

	cocos2d::DrawNode* oStencil;

	cocos2d::Node* oModel;
	cocos2d::Node* oArrow;
	cocos2d::Label* oText;

	std::vector<cocos2d::Vec2> aPos;
	std::vector<float> aSize;

	std::function<void()> finishCallback;

	bool bActive;
	bool bInited;

	cocos2d::Vec2 origin;
	cocos2d::Size visibleSize;
	float scaleDownRatio;

	/// <summary>
	/// call when the tutorial is about to go to slot game
	/// </summary>
	void loadToSlotGame();

	/// <summary>
	/// start Tutorial
	/// </summary>
	void start();

	/// <summary>
	/// set tutorial string on step
	/// </summary>
	/// <param name="step">step of tutorial</param>
	void setTutorialString(std::string tutorialString);

	/// <summary>
	/// show tutorial on step
	/// </summary>
	/// <param name="step">step of tutorial</param>
	void showStep(TutorialStep step);

	/// <summary>
	/// call when there's error on tutorial (network error)
	/// </summary>
	/// <param name="mes">message when error</param>
	void onError(const std::string& mes);

	/// <summary>
	/// call when user touch on tutorial
	/// </summary>
	/// <param name="touch">touch info</param>
	/// <param name="event">event info</param>
	/// <returns></returns>
	bool onTouched(cocos2d::Touch* touch, cocos2d::Event* event);

	/// <summary>
	/// finish Tutorial
	/// </summary>
	void finish();

	/// <summary>
	/// remove Tutorial
	/// </summary>
	void remove();

	/// <summary>
	/// load tutorial info from local
	/// </summary>
	void loadLocal();

	/// <summary>
	/// save some tutorial info to local
	/// </summary>
	void saveLocal();
public:
	//Get shared instance of Tutorial
	static Tutorial* getInstance();

	/// <summary>
	/// initialize function
	/// </summary>
	Tutorial();
	/// <summary>
	/// release function
	/// </summary>
	~Tutorial();
	/// <summary>
	/// return true if tutorial is activated
	/// </summary>
	/// <returns></returns>
	bool isActive() { return this->bActive; }

	bool init();

	/// <summary>
	/// set callback when finish tutorial
	/// </summary>
	/// <param name="cb">callback function</param>
	void setFinishCallback(const std::function<void()>& cb) { this->finishCallback = cb; }

	/// <summary>
	/// check to if we need to show tutorial
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	bool checkAndShow(cocos2d::Node* parent);

	/// <summary>
	/// Dat : update reference of tutorial vd: user info, header UI
	/// </summary>
	void updateReference();
};