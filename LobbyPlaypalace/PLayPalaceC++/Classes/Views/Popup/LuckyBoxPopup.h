#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-18
* file: NotificationPopup.h, NotificationPopup.cpp
*/
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"
#include "Info/GiftInfo.h"

enum ChestUIState
{
	CHEST_UI_STATE_START,
	CHEST_UI_STATE_COLLECTING,
	CHEST_UI_STATE_FINISHED_ANIMATION,
	CHEST_UI_STATE_COLLECTED,
	CHEST_UI_STATE_CAN_RELOAD,
	CHEST_UI_STATE_RELOADING,
	CHEST_UI_STATE_FINISH,
	CHEST_UI_STATE_DISABLE
};
class LuckyBoxPopup;
struct LuckyBox;
class LuckyBoxChestUI : public cocos2d::Node
{
private:

	cocos2d::Sprite * chest;
	cocos2d::Node * groupOpenChestAnimation;
	ChestUIState currentState;
	LuckyBoxPopup * parent;
	float chestScale = 1.2f;
	cocos2d::Label * labelChest;
	cocos2d::Label * labelTouch2Open;
	/// <summary>
	/// update text message on chest base on chest info
	/// </summary>
	void updateTextMessage();
	/// <summary>
	/// create sprite for open chest animation
	/// </summary>
	void createSprite4OpenChestAnimation();
	/// <summary>
	/// play open chest animaiton
	/// </summary>
	void playOpenChestAnimation();//step1A
	/// <summary>
	/// play increasing coin text animation
	/// </summary>
	void playTextAnimation();//step1A
	/// <summary>
	/// call api accept gift
	/// </summary>
	void callAPIAcceptGift();//step1B
	/// <summary>
	/// function call after finish animation open chest
	/// </summary>
	void reloadAndTimerPlayAnimateCoinInfo();//step2
	/// <summary>
	/// call api get profile and close popup
	/// </summary>
	/// <param name="dt">delay time 4 call this function</param>
	void callAPIAndAnimReloadHeaderAndClosePopup(float dt);//step3
	
public:
	LuckyBoxChestUI();
	/// <summary>
	/// create chest
	/// </summary>
	/// <param name="_parent"></param>
	/// <returns></returns>
	static LuckyBoxChestUI* create(LuckyBoxPopup * _parent);

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	void reset();
	/// <summary>
	/// touche on chest
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	/// <summary>
	/// reset animation for idle chest
	/// </summary>
	void resetChestTransformAndAction();
	/// <summary>
	/// reset animation for open chest
	/// </summary>
	void resetGroupOpenChestTransformAndAction();
	/// <summary>
	/// shake chest
	/// </summary>
	void playLittleShakeAnimation();
	/// <summary>
	/// hide chest UI
	/// </summary>
	void hide();
	/// <summary>
	/// enable for chest UI
	/// </summary>
	/// <param name="enable"></param>
	void setEnabled(bool enable);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LuckyBoxChestUI);
};

class BuyAndDoubleUI : public cocos2d::Node{
private:
	LuckyBoxPopup * parent;
	cocos2d::Label * labelSale;
	cocos2d::ui::Button* buyButton;
	cocos2d::Sprite* chest1;
	cocos2d::Sprite* chest2;
public:
	static BuyAndDoubleUI * create(LuckyBoxPopup * _parent);
	void setUpUI();
	void setEnabled(bool enable);
	void reset();

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(BuyAndDoubleUI);

	cocos2d::Sprite* background;
};

class LuckyBoxPopup : public BasePopup
{
private:
	cocos2d::Sprite * oLightRay;
	LuckyBoxChestUI * chestUI;
	cocos2d::Sprite* background;
	cocos2d::Sprite* oLogo;

	bool isBuyingDouble;
protected:
	/// <summary>
	/// callback when click to background
	/// </summary>
	virtual void callback4Click2DarkLayer();

public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// prepare and show popup
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="_giftInfo"></param>
	/// <param name="_numberOfLuckyBox">more than 1</param>
	/// <param name="_isCollectAll">collect all popup</param>
	/// <param name="callback">callback after collect</param>
	void prepareAndShow(cocos2d::Node* parent,GiftInfo* _giftInfo, int _numberOfLuckyBox, bool _isCollectAll, std::function<void(void)> callback);
	/// <summary>
	/// hide popup
	/// </summary>
	virtual void hide();
	/// <summary>
	/// create green button
	/// </summary>
	/// <param name="titleText">title button</param>
	/// <param name="fontSize"></param>
	/// <returns></returns>
	cocos2d::ui::Button* createButton(std::string titleText, float fontSize);
	/// <summary>
	/// enable popup
	/// </summary>
	/// <param name="enable">is enable</param>
	/// <param name="_isBuyingDouble">is enable for buying double</param>
	void setEnabled(bool enable, bool _isBuyingDouble);
	/// <summary>
	/// callback after buy double
	/// </summary>
	/// <param name="isSuccess"></param>
	/// <param name="buyInfo"></param>
	void callbackAfterBuyingDouble(bool isSuccess, LuckyBox buyInfo);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LuckyBoxPopup);

	GiftInfo* giftInfo;
	std::string chestSpriteName;
	std::string luckyBoxMessageName;
	std::string saleBuyAndDoubleText;
	std::string packagePurchaseX2Name;
	int numberOfLuckyBox;
	bool isCollectAll;
	BuyAndDoubleUI * buyAndDoubleUI;
	std::function<void(void)> callbackWhenCollectLuckyBoxDone;
};