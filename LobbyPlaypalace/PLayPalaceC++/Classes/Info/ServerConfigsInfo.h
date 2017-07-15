#pragma once
#include "BaseItemInfo.h"
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: ServerConfigsInfo.h
*/

class ServerConfigsInfo : public BaseItemInfo
{
public:
	int deltaTimeCallRealTimeNotification;
	int deltaTimeCallUpdateFriend;
	int coinRewardAfterUpLevel;
	int crownRewardAfterUpLevel;
	std::string sampleResponseSpinInTutorial;
};