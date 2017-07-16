#pragma once
#include "BaseItemInfo.h"
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: LevelInfo.h
*/

class LevelInfo : public BaseItemInfo
{
public:
	int levelId;
	double coinReward;
	double crownReward;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
//		if (data == NULL)
//		{
//			return;
//		}
		BaseItemInfo::updateBaseItemInfoByValue(data);
		this->levelId = data[JSONFieldConstant::LEVEL_ID.c_str()].GetInt();
		this->coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		this->crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetDouble();
	}
};
