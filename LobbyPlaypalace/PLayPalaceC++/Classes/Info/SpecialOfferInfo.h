#pragma once
#include "BaseItemInfo.h"

class SpecialOfferInfo : public BaseItemInfo
{
public:
	double remainingTime;
	double remainingAmount;
	double coinReward;
	float bonusPercent;
	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		this->remainingTime = data[JSONFieldConstant::REMAINING_TIME.c_str()].GetDouble();
		this->remainingAmount = data[JSONFieldConstant::REMAINING_AMOUNT.c_str()].GetDouble();
		this->coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		this->bonusPercent = data[JSONFieldConstant::BONUS_PERCENT.c_str()].GetFloat();
	}
};
