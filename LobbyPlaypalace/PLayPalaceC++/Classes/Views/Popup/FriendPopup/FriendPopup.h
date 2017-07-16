#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-08
* file: FriendPopup.h, FriendPopup.cpp
*/
#include "Views/Popup/BasePopup.h"
#include "Custom/Common/CRadioButton.h"
#include "CellInbox.h"
#include "CellFriend.h"
#include "CellLeaderboard.h"
#include "Constant/Defination.h"
#include "Views/IUpdateLanguage.h"

enum OpenTab {
	Inbox,
	Friend,
	Leaderboard
};
struct ButtonPagesGroupNode {
	CRadioButton* btn;

	cocos2d::Sprite* oNotiBG;
	cocos2d::Label* oNotiLabel;

	/// <summary>
	/// create radio button
	/// </summary>
	/// <param name="parent">parent of group</param>
	/// <param name="group">group of radio button</param>
	/// <param name="text">text of button</param>
	/// <param name="pos">position of button</param>
	/// <param name="cb">callback after clicked button</param>
	void createRadioButton(
		cocos2d::Node* parent,
		cocos2d::ui::RadioButtonGroup* group,
		const std::string& text,
		const cocos2d::Vec2& pos,
		std::function<void(cocos2d::ui::RadioButton* btn, cocos2d::ui::RadioButton::EventType type)> cb);

	/// <summary>
	/// reload notification info
	/// </summary>
	/// <param name="num"></param>
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
class FriendPopup : public BasePopup, public IUpdateLanguage
{
private:
	cocos2d::Label *titleLabel = nullptr;
	cocos2d::ui::Button* acceptAllButton;
	cocos2d::Label* emptyGiftLabel;

	cocos2d::Label * infoFriendLabel;
	cocos2d::ui::Button * sendGiftButton;
	cocos2d::ui::Button * inviteButton;

	cocos2d::Node *inboxTab = nullptr;
	cocos2d::Node *friendTab = nullptr;
	cocos2d::Node *leaderboardTab = nullptr;

	cocos2d::ui::RadioButtonGroup *radioButtonGroup;
	ButtonPagesGroupNode inboxButton;
	ButtonPagesGroupNode friendButton;
	ButtonPagesGroupNode leaderboardButton;

	cocos2d::ui::Button *coinsLeaderboardButton = nullptr;
	cocos2d::ui::Button *totalBetLeaderboardButton = nullptr;

	std::map<long, GiftInfo*> currentGiftInfoList;
	std::map<long, LeaderboardInfo*> currentLeaderboardInfoList;
	std::map<long, FriendFBInfo*> currentFriendInfoList;

	/// <summary>
	/// init ui of inbox tab
	/// </summary>
	void initInboxTab();
	/// <summary>
	/// init ui of friend tab
	/// </summary>
	void initFriendTab();
	/// <summary>
	/// init ui of leaderboard tab
	/// </summary>
	void initLeaderboardTab();

	/**
	* 2017-10-03: Kiet: goto coin or totalbet tab in leaderboard
	*/
	void gotoChildLeaderboardTab(LeaderboardTab leaderboardTab);
	/**
	* 2017-08-03: Kiet: on accept gift touched
	*/
	void onAcceptGiftTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/// <summary>
	/// get list luckybox info from list gift
	/// </summary>
	/// <returns></returns>
	GiftsInfo* getSummaryLuckyBoxInfo();
	/**
	* 2017-08-03: Kiet: on accept gift touched
	*/
	void onAcceptGiftAllTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-08-03: Kiet: on send gift touched
	*/
	void onSendGiftTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/**
	* 2017-08-03: Kiet: on invite touched
	*/
	void onInviteTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// By Dat combile 2 function prepareDataInboxTab and gotoInboxTab
	/// </summary>
	bool prepareDataAndShowInboxTab(cocos2d::Node* parent);

	/**
	* 2017-08-03: Kiet: goto inbox tab
	*/
	void gotoInboxTab();
	/**
	* 2017-08-03: Kiet: goto friend tab
	*/
	void gotoFriendTab();
	/**
	* 2017-08-03: Kiet: goto leadeboard tab
	*/
	void gotoLeaderboardTab();
	/**
	*  Dat: update noti for inbox tab ( call to server get data ) then call callback
	*/
	void updateNotificationForInboxTab();
	/**
	* 2017-08-03: Kiet: prepare data for inbox tab ( call to server get data ) then call callback
	*/
	void prepareDataInboxTab(std::function<void()> callback);
	/**
	* 2017-08-03: Kiet: prepare data for friend tab ( call to server get data ) then call callback
	*/
	void prepareDataFriendTab(std::function<void()> callback);
	/**
	* 2017-08-03: Kiet: prepare data for leaderboard tab ( call to server get data ) then call callback
	*/
	void prepareDataLeaderboardTab(std::function<void()> callback, LeaderboardTab leaderboardTab);

	/**
	* 2017-09-03: Kiet: update inbox cell in reuse listview inbox
	*/
	void updateInboxCell(int newItemID, cocos2d::ui::Widget* templateItem);
	/**
	* 2017-09-03: Kiet: update leaderboard cell in reuse listview leaderboard
	*/
	void updateLeaderboardCell(int newItemID, cocos2d::ui::Widget* templateItem);
	/**
	* 2017-09-03: Kiet: update friend cell in reuse listview inbox
	*/
	void updateFriendCell(int newItemID, cocos2d::ui::Widget* templateItem);

	/**
	* 2017-20-03: Kiet: when open popup in friend tab, this schedule will run to check isRequestingInvitableFriendList
	* in facebook controller, util requesting is false, loading animation turn off and show popup
	*/
	void scheduleCheckAlreadyGotFriends(float dt);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// show popup friend
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="openTab">tab type friend, inbox or leaderboard</param>
	void prepareAndShow(
		cocos2d::Node *parent,
		OpenTab openTab
	);


	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(FriendPopup);
	/**
	* dat: update ui after change language
	*/
	void updateAfterChangeLanguage();
};