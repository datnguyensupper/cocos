#pragma once
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"
#include "SlotGame/GameSlotScene.h"
#include "ui/CocosGUI.h"
#include "SlotGame/base/interfaceUI/CFooter.h"

class CRadioButton;
class CCircularPageView;
enum BetType {
	Bet,
	PayLine
};

class ChangeBetUI : public cocos2d::Node {
private:
	GameSlot::CGameBase* oGame;
	GameSlot::CFooter* oFooter;
	cocos2d::Node* betAdjustNode;
	cocos2d::Node* paylineAdjustNode;

	cocos2d::Label* labelPayLines;
	cocos2d::Label* numPayLine;
	cocos2d::Label* labelBet;
	cocos2d::Label* numBet;

	cocos2d::Label* oBetInfoText;
	cocos2d::Label* oPaylineInfoText;
	/*
	* Create a group (bet, payline) contains 2 button ("+" and "-") and a text field between
	* @param labelText:
	* @param onAdjust: cb when btn "+" or "-" is touched
	* @param bSkipButton:
	*/
	cocos2d::Node* createAdjustGroup(const std::string& labelText, const std::function<void(int)>& onAdjust);

	/// <summary>
	/// save opening CGame info
	/// </summary>
	/// <param name="oGame">opening game</param>
	void setGame(GameSlot::CGameBase* oGame);
public:
	ChangeBetUI();

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// enable button change bet or button change payline
	/// </summary>
	/// <param name="type">bet or payline</param>
	/// <param name="name">name of button</param>
	/// <param name="isEnabled">is enable or not</param>
	void setEnableBtn(BetType type, const std::string& name, bool isEnabled);

	friend class GameSlotInfoPopup;
};

class GameSlotInfoPopup : public BasePopup
{
private:
	CRadioButton* btnBet;
	CRadioButton* btnInfo;

	ChangeBetUI* betTab;
	cocos2d::ui::PageView* infoTab;
	/// <summary>
	/// call back when click to new tab
	/// </summary>
	/// <param name="btn">button info</param>
	/// <param name="type">type of action</param>
	void onChangeTab(cocos2d::ui::RadioButton* btn, cocos2d::ui::RadioButton::EventType type);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// get ui of bet tab
	/// </summary>
	/// <returns></returns>
	ChangeBetUI* getBetTab() { return this->betTab; }

	/// <summary>
	/// init ui for bet tab
	/// </summary>
	void initBetTab();
	/// <summary>
	/// init UI for info tab
	/// </summary>
	void initInfoTab();
	/**
	* reset popup by set visible to false and ishowing to false
	*/
	void reset() override;

	/**
	* prepare and show
	*/
	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(GameSlotInfoPopup);
};