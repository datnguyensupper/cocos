#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: LevelInfo.h
*/

#include "Info/BaseItemInfo.h"

struct LeaderboardInfo : public BaseItemInfo
{
	long level;
	double coin;
	double slotTotalBet;
	std::string facebookUID;
	std::string urlFullAvatar;
	int vipType;
	long userId;
	int rank;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		if (data.HasMember(JSONFieldConstant::Level.c_str()))
		{
			this->level = data[JSONFieldConstant::Level.c_str()].GetInt64();
		}
		if (data.HasMember(JSONFieldConstant::Coin.c_str()))
		{
			this->coin = data[JSONFieldConstant::Coin.c_str()].GetDouble();
		}
		if (data.HasMember(JSONFieldConstant::SLOT_TOTAL_BET.c_str()))
		{
			this->slotTotalBet = data[JSONFieldConstant::SLOT_TOTAL_BET.c_str()].GetDouble();
		}
		if (data.HasMember(JSONFieldConstant::FB_UID.c_str()))
		{
			this->facebookUID = data[JSONFieldConstant::FB_UID.c_str()].GetString();
		}
		if (data.HasMember(JSONFieldConstant::URL_FULL_AVATAR.c_str()))
		{
			this->urlFullAvatar = data[JSONFieldConstant::URL_FULL_AVATAR.c_str()].GetString();
		}
		if (data.HasMember(JSONFieldConstant::VIP_TYPE.c_str()))
		{
			this->vipType = data[JSONFieldConstant::VIP_TYPE.c_str()].GetInt();
		}
		this->userId = this->id;
	}
};