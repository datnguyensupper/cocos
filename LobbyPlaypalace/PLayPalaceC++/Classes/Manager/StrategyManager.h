#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: StrategyManager.h, StrategyManager.cpp
*/

#include "cocos2d.h"
#include "Constant/PPEnums.h"
#include "NetworkManager.h"
//DEPRECATED
//DEPRECATED
//DEPRECATED
//DEPRECATED
class StrategyManager
{
private:
	StrategyManager();
	static StrategyManager* s_instance;
public:
	static StrategyManager* getInstance();
	~StrategyManager();
	/// <summary>
	/// get additional info from server
	/// </summary>
	/// <param name="callback">callback after call api</param>
	/// <param name="isReloadUI">should reload UI after get info</param>
	void getAdditionalInfo(std::function<void(bool isSuccess)> callback, bool isReloadUI);
	/// <summary>
	/// handle fail for strategy
	/// </summary>
	/// <param name="failInfo">fail info</param>
	/// <param name="isShowFailPopup">should show notification fail popup</param>
	/// <param name="isReloadAdditionalInfo">get strategy info again</param>
	void handleFailResultNewStrategy(NetworkFailProcessInfo failInfo, bool isShowFailPopup, bool isReloadAdditionalInfo);
};