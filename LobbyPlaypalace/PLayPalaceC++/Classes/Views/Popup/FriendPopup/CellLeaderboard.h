#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-08
* file: CellLeaderboard.h, CellLeaderboard.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Info/LeaderboardInfo.h"

enum LeaderboardTab
{
	COINS_TAB = 1,
	TOTAL_BET_TAB = 2
};
class CellLeaderboard : public cocos2d::ui::Widget
{
private:
	cocos2d::Sprite *avatarSprite = nullptr;
	cocos2d::Sprite *stardom = nullptr;
	cocos2d::Label *nameLabel = nullptr;
	cocos2d::Label *levelLabel = nullptr;
	cocos2d::Label *coinOrTotalBetLabel = nullptr;


	LeaderboardInfo* leaderboardInfo;
	cocos2d::Size cellSize;
	LeaderboardTab leaderboardTab;
public:
	static CellLeaderboard* create(
		LeaderboardTab _leaderboardTab, 
		LeaderboardInfo *_leaderboardInfo,
		cocos2d::Size cellSize
	);
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// kiet: get leaderboard info of cell
	/// </summary>
	/// <returns></returns>
	LeaderboardInfo* getLeaderboardInfo() {
		return this->leaderboardInfo;
	}

	/// <summary>
	/// 2017-08-03: Kiet: update leaderboard cell
	/// </summary>
	/// <param name="_leaderboardInfo">cell info</param>
	void updateCell(LeaderboardInfo* _leaderboardInfo);
};