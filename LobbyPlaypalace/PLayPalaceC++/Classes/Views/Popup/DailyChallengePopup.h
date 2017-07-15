#pragma once
#include "Views/Popup/BasePopup.h"

struct DailyChallengeInfo;
struct DailyChallengeTask;

class DailyChallengeTaskUI : public cocos2d::ui::Layout {
private:
	cocos2d::Sprite* icon;
	cocos2d::Label* text;
	cocos2d::ProgressTimer* progress;
	cocos2d::Label* progressTxt;
public:
	static DailyChallengeTaskUI* create();

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/**
	* update info
	* return true is it's completed
	*/
	bool updateInfo(DailyChallengeTask* taskInfo);
};

class DailyChallengePopup : public BasePopup
{
private:
	cocos2d::ui::ListView* oContent;

	cocos2d::Label* txtInfo;

	cocos2d::ui::RichText* txtReward;
	cocos2d::Label* txtCoin;
	cocos2d::Label* txtCrown;

	cocos2d::Sprite* totalProgressSprite;
	cocos2d::ProgressTimer* totalProgress;

	cocos2d::Sprite* btnCollect;
	cocos2d::Label* txtCollect;
	/**
	* reload ui
	*/
	void reloadUI(DailyChallengeInfo* info);

	/// <summary>
	/// reload totalProgresss
	/// </summary>
	/// <param name="info"></param>
	/// <param name="totalComplete">total task complete</param>
	void reloadTotalProgress(DailyChallengeInfo* info, int totalComplete);
	/**
	* on collect
	*/
	void collect();

protected:
	/// <summary>
	/// Dat: get min ratio popup for scale from animation
	/// </summary>
	/// <returns></returns>
	virtual float getMinRatioPopup();

	/// <summary>
	/// Dat: get real ratio popup show on multiple device
	/// </summary>
	/// <returns></returns>
	virtual float getMaxRatioPopup();
public:
	/**
	* init function
	*/
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// show popup
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="forceShowAfterResleaseScene">show this popup after change scene</param>
	void prepareAndShow(cocos2d::Node* parent, bool forceShowAfterResleaseScene = false);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(DailyChallengePopup);
};