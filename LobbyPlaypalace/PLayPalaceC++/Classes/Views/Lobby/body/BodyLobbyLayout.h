#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-15
* file: BodyLobbyLayout.h, BodyLobbyLayout.cpp
*/
#include "cocos2d.h"

#include "ui/CocosGUI.h"

struct GameSlotButtonUIInfo
{
	int orderIdFromServer;
	std::string spritePath;
	cocos2d::Vec2 localPosition;
	int pageIndex;
	int rowInPage;
	int colInPage;
};

class LobbyScene;
class ButtonGameSlot;
class BodyLobbyLayout : public cocos2d::ui::Layout
{
private:
	cocos2d::Vector<cocos2d::Sprite*> dotIconList;

	LobbyScene* lobbyScene;
	cocos2d::Sprite * model;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float scaleDownRatio;

	void initUI();
	void createListButtonGameSlot();
	/**
	* 2017-02-15: Kiet: base on order id determine GameSlotButtonUIInfo correspond
	*/
	GameSlotButtonUIInfo* initGameSlotButtonUIInfo(int orderId);

	/// <summary>
	/// 2017-02-18: Kiet: process after click a game slot button
	/// </summary>
	/// <param name="sender">button ui</param>
	/// <param name="type">touch event type</param>
	void onGameSlotTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/// <summary>
	/// 2017-02-18: Kiet: page view game slot event
	/// </summary>
	/// <param name="sender">page view UI</param>
	/// <param name="type">event on page type</param>
	void pageViewEvent(cocos2d::Ref* sender, cocos2d::ui::PageView::EventType type);

public:

	BodyLobbyLayout();
	/// <summary>
	/// remove callback for downloading game slot avoid crash problem
	/// </summary>
	~BodyLobbyLayout();

	/// <summary>
	/// call each time show body
	/// </summary>
	virtual void onEnter() override;

	/**
	* 2017-02-15: Kiet: create BodyLobbyLayout
	*/
	static BodyLobbyLayout* create(LobbyScene* parent);

    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// Dat: enable or disable mascot for tutorial
	/// </summary>
	/// <param name="isVisible"></param>
	void setVisibleMascot(bool isVisible);
	/// <summary>
	/// Dat: reset child position for scale problem
	/// </summary>
	void resetChildPosition4ScaleProblem();
    
    // implement the "static create()" method manually
    /// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(BodyLobbyLayout);
};
