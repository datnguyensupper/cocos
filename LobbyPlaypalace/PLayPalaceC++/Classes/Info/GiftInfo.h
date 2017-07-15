#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: GiftInfo.h
*/
#include "BaseItemInfo.h"

struct GiftInfo : public BaseItemInfo
{
	std::string message;
	double coinReward;
	int crownReward;
	int luckyWheelReward;
	int keyReward;
	long fromUserId;
	long toUserId;
	int status;
	int type;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data){
		BaseItemInfo::updateBaseItemInfoByValue(data);
		if (data.HasMember(JSONFieldConstant::MESSAGE.c_str()))	
			this->message = data[JSONFieldConstant::MESSAGE.c_str()].GetString();
		if (data.HasMember(JSONFieldConstant::COIN_REWARD.c_str()))
			this->coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		if (data.HasMember(JSONFieldConstant::CROWN_REWARD.c_str()))
			this->crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetInt();
		if (data.HasMember(JSONFieldConstant::LUCKY_WHEEL_REWARD.c_str()))
			this->luckyWheelReward = data[JSONFieldConstant::LUCKY_WHEEL_REWARD.c_str()].GetInt();
		if (data.HasMember(JSONFieldConstant::KEY_REWARD.c_str()))
			this->keyReward = data[JSONFieldConstant::KEY_REWARD.c_str()].GetInt();
		if (data.HasMember(JSONFieldConstant::FROM_USER_ID.c_str()))
			this->fromUserId = data[JSONFieldConstant::FROM_USER_ID.c_str()].GetInt64();
		if (data.HasMember(JSONFieldConstant::TO_USER_ID.c_str()))
			this->toUserId = data[JSONFieldConstant::TO_USER_ID.c_str()].GetInt64();
		if (data.HasMember(JSONFieldConstant::Status.c_str()))
			this->status = data[JSONFieldConstant::Status.c_str()].GetInt();
		if (data.HasMember(JSONFieldConstant::Type.c_str()))
			this->type = data[JSONFieldConstant::Type.c_str()].GetInt();
		
	
	}

	void update(GiftInfo* gift){
		if (gift) {
			BaseItemInfo::update(gift);
			this->message = gift->message;
			this->coinReward = gift->coinReward;
			this->crownReward = gift->crownReward;
			this->luckyWheelReward = gift->luckyWheelReward;
			this->keyReward = gift->keyReward;
			this->fromUserId = gift->fromUserId;
			this->toUserId = gift->toUserId;
			this->status = gift->status;
			this->type = gift->type;
		}
	}

	static GiftInfo* create(GiftInfo* gift){
		
		GiftInfo* newGift = new GiftInfo();
		newGift->update(gift);
		return newGift;
	}
};


struct GiftsInfo : public GiftInfo{
	int numberOfGifts;
};