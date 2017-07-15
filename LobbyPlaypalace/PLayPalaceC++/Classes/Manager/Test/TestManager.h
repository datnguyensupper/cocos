#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: TestManager.h, TestManager.cpp
*/

#include "cocos2d.h"
#include "Info/BetSlotGameInfo.h"
#include "Info/LevelInfo.h"
#include "Info/ServerConfigsInfo.h"
#include "Info/ServerSlotGameInfo.h"
#include "Info/UserBonusCheckInfo.h"
#include "Info/UserInfo.h"

#include "Views/Popup/BasePopup.h"

class TestManager : BasePopup
{
private:
	static TestManager* s_instance;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float scaleDownRatio;
public:
	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static TestManager* getInstance();

	void printOutListSlotGameInfo(std::map<int, ServerSlotGameInfo*> listSlotGameInfo);
	/// <summary>
	/// createListGameSlotInfoTest
	/// </summary>
	/// <returns></returns>
	std::map<int, ServerSlotGameInfo*> createListGameSlotInfoTest();
	/// <summary>
	/// createUnlockedListGameSlotInfoTest
	/// </summary>
	/// <returns></returns>
	std::deque<ServerSlotGameInfo*> createUnlockedListGameSlotInfoTest();
	/// <summary>
	/// getFakeRespone
	/// </summary>
	/// <param name="url"></param>
	/// <param name="callback"></param>
	void getFakeRespone(std::string url, std::function<void(rapidjson::Value &responseAsDocument)> callback);
	/// <summary>
	/// testBonusWheel
	/// </summary>
	/// <param name="parent"></param>
	void testBonusWheel(cocos2d::Node * parent);
	/// <summary>
	/// testLuckyBox
	/// </summary>
	/// <param name="parent"></param>
	void testLuckyBox(cocos2d::Node * parent);
	/// <summary>
	/// testLuckyWheel
	/// </summary>
	/// <param name="parent"></param>
	void testLuckyWheel(cocos2d::Node * parent);
	/// <summary>
	/// testCombackBonus
	/// </summary>
	/// <param name="parent"></param>
	void testCombackBonus(cocos2d::Node * parent);
	/// <summary>
	/// prepareTestLuckyWheel
	/// </summary>
	/// <param name="parent"></param>
	void prepareTestLuckyWheel(cocos2d::Node * parent);
	/// <summary>
	/// testUnlockPopup
	/// </summary>
	/// <param name="parent"></param>
	void testUnlockPopup(cocos2d::Node * parent);
	/// <summary>
	/// testUnlockFeature
	/// </summary>
	/// <param name="parent"></param>
	void testUnlockFeature(cocos2d::Node * parent);
	/// <summary>
	/// testGameSlot
	/// </summary>
	/// <param name="parent"></param>
	void testGameSlot(cocos2d::Node * parent);
	/// <summary>
	/// testDailyBonusStreak
	/// </summary>
	/// <param name="parent"></param>
	void testDailyBonusStreak(cocos2d::Node * parent);
	/// <summary>
	/// testLevelUpPopup
	/// </summary>
	/// <param name="parent"></param>
	void testLevelUpPopup(cocos2d::Node * parent);
	/// <summary>
	/// testAchievementPopup
	/// </summary>
	/// <param name="parent"></param>
	void testAchievementPopup(cocos2d::Node * parent);
	/// <summary>
	/// prepareTestAchievementPopup
	/// </summary>
	/// <param name="parent"></param>
	void prepareTestAchievementPopup(cocos2d::Node * parent);
	/// <summary>
	/// prepareTestCombackBonus
	/// </summary>
	/// <param name="parent"></param>
	void prepareTestCombackBonus(cocos2d::Node * parent);
	/// <summary>
	/// prepareTestGameSlot
	/// </summary>
	/// <param name="parent"></param>
	void prepareTestGameSlot(cocos2d::Node * parent);
	/// <summary>
	/// create test button
	/// </summary>
	/// <param name="parent"></param>
	void createTestButton(cocos2d::Node * parent);
	/// <summary>
	/// check to enter what item to test
	/// </summary>
	/// <param name="parent"></param>
	void check4AutoTest(cocos2d::Node * parent);
	/// <summary>
	/// auto login with guest account
	/// </summary>
	/// <param name="parent"></param>
	void autoLogin(cocos2d::Node * parent);


	bool shouldAutoEnterGameSlots = false;
	bool shouldAutoEnterCombackBonus = false;
	bool shouldAutoTestAchievement = false;
	bool shouldAutoTestLuckyWheel = false;

protected:

	TestManager();
};
