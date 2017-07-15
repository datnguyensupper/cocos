#pragma
/**
* creator: Kiet Duong
* date: 2017-02-15
* file: BodyLobbyLayout.h, BodyLobbyLayout.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Views/IUpdateLanguage.h"

class LobbyScene;
class BottomItem;
class ButtonAdjustClikableAreaSize;

struct SideOptionUI {
	cocos2d::Node * noti;
	cocos2d::Label * notiLabel;

	cocos2d::ui::Button * btn;
};
class ReuseItemListView_Horizontal;
class ReuseItemListView_Vertical;
class FreeCoinGiftItem;
struct GiftInfo;
class BottomLobbyLayout : public cocos2d::ui::Layout, public IUpdateLanguage
{
private:
	ReuseItemListView_Horizontal * bottomScrollView;

	LobbyScene* lobbyScene;
	//Achievements
	SideOptionUI achievements;
	//Gifts
	SideOptionUI gifts;
	FreeCoinGiftItem * freeCoinGiftItem;

	std::vector<cocos2d::ui::Widget*> _aItems;
	BottomItem* luckyBox;

	bool bAutoScroll = true;
	float timeNotAutoScroll = 0;
	float delayTime4StopScrollBottom = 2.0f;
	float time4ReloadNotificationGifts = 120;//2 minutes

	/// <summary>
	/// create item for footer
	/// </summary>
	/// <param name="posBtn">btn position</param>
	/// <param name="posNoti">btn noti position</param>
	/// <param name="text">btn text</param>
	/// <param name="cb">callback for clicking btn</param>
	/// <returns></returns>
	SideOptionUI createSideButton(
		const cocos2d::Vec2& posBtn,
		const cocos2d::Vec2& posNoti,
		const std::string& text,
		const std::function<void(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType)>& cb);
	/**
	* init all footer items
	*/
	void initItems();
public:
	/**
	* 2017-02-15: Dat: create BottomLobbyLayout
	*/
	static BottomLobbyLayout* create(LobbyScene* parent);

    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	virtual void onEnter() override;
    
    // implement the "static create()" method manually
    /// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(BottomLobbyLayout);

	/// <summary>
	/// update UI every frame
	/// </summary>
	/// <param name="delta"></param>
	void update(float delta);
	/// <summary>
	/// update notification achievements info
	/// </summary>
	/// <param name="numberOfAchievements"></param>
	void updateNotificationAchievements(int numberOfAchievements);
	/// <summary>
	/// update notification gifts info
	/// </summary>
	/// <param name="result">gifts info</param>
	void updateNotificationGifts(const std::vector<GiftInfo*>& result);
	/// <summary>
	/// call server and update notification achievements info
	/// </summary>
	void updateNotificationAchievementsFromSV();
	/// <summary>
	/// call sv and update notification gifts info
	/// </summary>
	void updateNotificationGiftsFromSV();

	/// <summary>
	/// achievement btn clicked
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="touchType"></param>
	void onBtnAchievementClicked(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
	/// <summary>
	/// gift btn clicked
	/// </summary>
	/// <param name="sender"></param>
	/// <param name="touchType"></param>
	void onBtnGiftClicked(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType touchType);
	/// <summary>
	/// select bottom item
	/// </summary>
	/// <param name="sender">item UI</param>
	/// <param name="type">touch event type</param>
	void onItemSelected(cocos2d::Ref* sender, cocos2d::ui::ListView::EventType type);
	/// <summary>
	/// scroll bottom
	/// </summary>
	/// <param name="pSender">scroll view</param>
	/// <param name="type">event type</param>
	void onScroll(cocos2d::Ref* pSender, cocos2d::ui::ScrollView::EventType type);

	/// <summary>
	/// click on lucky wheel button
	/// </summary>
	/// <param name="sender"></param>
	void onLuckyWheel(BottomItem* sender);
	/// <summary>
	/// click on lucky spin  button
	/// </summary>
	/// <param name="sender"></param>
	void onLuckySpin(BottomItem* sender);
	/// <summary>
	/// click on luckybox button
	/// </summary>
	/// <param name="sender"></param>
	void onLuckyBox(BottomItem* sender);
	/// <summary>
	/// click on dailychallenge button
	/// </summary>
	/// <param name="sender"></param>
	void onDailyChallenge(BottomItem* sender);
	/// <summary>
	/// click on piggybank button
	/// </summary>
	/// <param name="sender"></param>
	void onPiggyBank(BottomItem* sender);
	/**
	* dat: update ui after change language
	*/
	void updateAfterChangeLanguage();
};