#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SlotGame/base/utils/CSpriteButton.h"

class BottomItem : public cocos2d::ui::Widget
{
private:
	std::string animFormat;
	int startFrame;
	int endFrame;

	cocos2d::Sprite* sprtSymbol = nullptr;
	cocos2d::Sprite* sprtLabel = nullptr;

	cocos2d::Sprite* sprtLock = nullptr;
	cocos2d::Sprite* sprtLockMask = nullptr;

	cocos2d::Label* noti = nullptr;

	std::function<void(BottomItem* sender)> cb;
public:
	BottomItem();
	/// <summary>
	/// create UI with data
	/// </summary>
	/// <param name="animFormat">animation key format</param>
	/// <param name="startFrame">start frame animation</param>
	/// <param name="endFrame">end frame animation</param>
	/// <param name="labelFrameName">label ui</param>
	/// <param name="bHasLock">has lock ui</param>
	/// <param name="bHasNoti">has notification ui</param>
	/// <param name="cb">callback when click to item</param>
	/// <returns></returns>
	static BottomItem* create(
		const std::string& animFormat,
		int startFrame, int endFrame,
		const std::string& labelFrameName,
		const std::function<void(BottomItem* sender)>& cb,
		bool bHasLock = false,
		bool bHasNoti = false);

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// init ui with data
	/// </summary>
	/// <param name="animFormat">animation key format</param>
	/// <param name="startFrame">start frame animation</param>
	/// <param name="endFrame">end frame animation</param>
	/// <param name="labelFrameName">label ui</param>
	/// <param name="bHasLock">has lock ui</param>
	/// <param name="bHasNoti">has notification ui</param>
	/// <returns></returns>
	virtual bool initWithData(
		const std::string& animFormat,
		int startFrame, int endFrame,
		const std::string& labelFrameName,
		bool bHasLock,
		bool bHasNoti);
	/// <summary>
	/// play item animation
	/// </summary>
	void playAnimation();
	/// <summary>
	/// show lock 
	/// </summary>
	void showLock();
	/// <summary>
	/// reload notification of item
	/// </summary>
	/// <param name="noti"></param>
	void reloadNoti(int noti);
	/// <summary>
	/// selecte item
	/// </summary>
	virtual void onSelected() { if (cb) cb(this); }
	/// <summary>
	/// set symbol for item
	/// </summary>
	/// <returns></returns>
	cocos2d::Sprite* getSpriteSymbol() { return this->sprtSymbol; }
	/// <summary>
	/// set sprite label for item
	/// </summary>
	/// <returns></returns>
	cocos2d::Sprite* getSpriteLabel() { return this->sprtLabel; }
	/// <summary>
	/// set item's child position
	/// </summary>
	/// <param name="symbolPos">symbol position</param>
	/// <param name="labelPos">label position</param>
	void setElementsPos(const cocos2d::Vec2& symbolPos, const cocos2d::Vec2& labelPos);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(BottomItem);
};

class FreeCoinGiftInfo;
class FreeCoinGiftItem : public BottomItem
{
private:
	enum FreeCoinGiftState {
		CountDown,
		WaitingForCollect,
		Collecting,
	};

	FreeCoinGiftState state;

	cocos2d::Label * oTitle;
	cocos2d::Label * oInfo;

	cocos2d::ProgressTimer* progressBar;

	FreeCoinGiftInfo* freeCoinGiftBonus;

	cocos2d::Node * oCoinGroup;
	cocos2d::ParticleSystemQuad* oParticle;
	/// <summary>
	/// update progress bar waiting for collect
	/// </summary>
	/// <param name="bAnim"></param>
	void reloadProgressBar(bool bAnim = false);
	/// <summary>
	/// change state of UI base on collect state
	/// </summary>
	/// <param name="state"></param>
	void changeState(FreeCoinGiftState state);
	/// <summary>
	/// animation for waiting collect
	/// </summary>
	/// <param name="bEnabled">is enable animation</param>
	void setEffectWaitingCollect(bool bEnabled);
public:
	FreeCoinGiftItem();

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// on selected btn collect
	/// </summary>
	virtual void onSelected() override;
	/// <summary>
	/// on enter UI
	/// </summary>
	virtual void onEnter() override;
	/// <summary>
	/// count down for left time collect
	/// </summary>
	/// <param name="dt"></param>
	void countDown(float dt);
	/// <summary>
	/// update UI
	/// </summary>
	void updateUI();

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(FreeCoinGiftItem);
};