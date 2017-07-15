#pragma once
#include "BaseItemInfo.h"
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: BetSlotGameInfo.h
*/

class BetSlotGameInfo : public BaseItemInfo
{
public:
	int betSize;
	long betSizePerLine;
	int payline;
	int levelRestriction;

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
		this->betSize = data[JSONFieldConstant::BET_SIZE.c_str()].GetInt();
		this->betSizePerLine = data[JSONFieldConstant::BET_SIZE_PER_LINE.c_str()].GetInt64();
		this->payline = data[JSONFieldConstant::PAYLINE.c_str()].GetInt();
		this->levelRestriction = data[JSONFieldConstant::LEVEL_RESTRICTION.c_str()].GetInt();
	}
};
