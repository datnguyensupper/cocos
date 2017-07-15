#pragma once
#include "../BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Info/AchievementInfo.h"
#include "Constant/LanguageConstant.h"
#include "Custom/Common/CRadioButton.h"
#include "Constant/Defination.h"
#include "Configs.h"

struct AchievementGroupNode {
	CRadioButton* btn;

	cocos2d::Sprite* oNotiBG;
	cocos2d::Label* oNotiLabel;

	/// <summary>
	/// create left button
	/// </summary>
	/// <param name="parent">parent of group</param>
	/// <param name="group">group button</param>
	/// <param name="text">text of button</param>
	/// <param name="pos"></param>
	/// <param name="cb">call back when click to button</param>
	void createRadioButton(
		cocos2d::Node* parent,
		cocos2d::ui::RadioButtonGroup* group,
		const std::string& text,
		const cocos2d::Vec2& pos,
		std::function<void(cocos2d::ui::RadioButton* btn, cocos2d::ui::RadioButton::EventType type)> cb);

	/// <summary>
	/// reload notification
	/// </summary>
	/// <param name="num">number of arhievement points</param>
	void reloadNotification(int num) {
		if (num == 0) {
			oNotiBG->setVisible(false);
		}
		else {
			oNotiBG->setVisible(true);
			oNotiLabel->setString(ToString(num));
		}
	}
};

class AchievementPopup : public BasePopup
{
private:
	bool bDirtyUpdateContent = false;

	AchievementGroupType currentType;

	cocos2d::Label* oLabel;
	cocos2d::Label* oPointLabel;
	cocos2d::Label* oPoint;

	cocos2d::ui::ListView* oContent;

	AchievementGroupNode btnGeneral;
	AchievementGroupNode btnGame;
	AchievementGroupNode btnSocial;
	/// <summary>
	/// switch tab
	/// </summary>
	/// <param name="btn">button</param>
	/// <param name="type">touch event type</param>
	void onChangeGroup(cocos2d::ui::RadioButton* btn, cocos2d::ui::RadioButton::EventType type);
	/// <summary>
	/// init UI
	/// </summary>
	/// <param name="type">type of achievement</param>
	void initContentView(AchievementGroupType type);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* prepare and show
	*/
	void prepareAndShow(cocos2d::Node* parent);
	/// <summary>
	/// collect achievement
	/// </summary>
	/// <param name="item">achievement info</param>
	/// <param name="posButtonInWorld">position of button collect to run animation</param>
	void onCollectAchievement(AchievementItem* item, cocos2d::Vec2 posButtonInWorld);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(AchievementPopup);
};