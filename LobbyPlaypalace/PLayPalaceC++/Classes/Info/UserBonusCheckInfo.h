#pragma once
#include "BaseItemInfo.h"
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: UserBonusCheck.h
*/

class UserBonusCheck : public BaseItemInfo
{
public:
	long timeLeft;
	long countDown;
	long timeLeftFreeGift;
	long timeLeftSendGift;
	double coinBonus;
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
		this->timeLeft = data[JSONFieldConstant::CHECK_TIME_LEFT.c_str()].GetInt64();
		this->countDown = data[JSONFieldConstant::TOTAL_TIME_LEFT.c_str()].GetInt64();
		this->timeLeftFreeGift = data[JSONFieldConstant::FREE_GIFT_TIME_LEFT.c_str()].GetInt64();
		this->timeLeftSendGift = data[JSONFieldConstant::GIFT_TIME_LEFT.c_str()].GetInt64();
		this->coinBonus = data[JSONFieldConstant::COIN_BONUS.c_str()].GetDouble();
	}
};

