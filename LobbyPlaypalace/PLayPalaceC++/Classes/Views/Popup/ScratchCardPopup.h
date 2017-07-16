//
// Created by Duy on 5/13/2017.
//
#pragma once
#include "BasePopup.h"

class ScratchCardInfo;
class CScratchSprite;
class ScratchUI : public cocos2d::Node {
private:
	CScratchSprite* scratchSprite;
	std::vector<cocos2d::Label*> cards;
public:
	CScratchSprite* getScratchSprite() { return scratchSprite; }

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// reset after hide popup
	/// </summary>
	void reset();

	/// <summary>
	/// scratch All
	/// </summary>
	void scratchAll();

	/// <summary>
	/// relaod info
	/// </summary>
	void reload(const std::vector<std::string>& values);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ScratchUI);
};

class ScratchCardPopup : public BasePopup {
private:
	ScratchCardInfo* info;

	cocos2d::Label* txtRemaining;

	//test
	cocos2d::Label* txtWin;

	ScratchUI* scratchUI;

	cocos2d::ui::Button* closeBtn;

	/**
	* reload ui
	*/
	void reloadUI();

	/**
	* on Scratch Card Listener
	*/
	void onScratchListener(float percent);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* hide popup with animation
	*/
	virtual void hide();

	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ScratchCardPopup);
};
