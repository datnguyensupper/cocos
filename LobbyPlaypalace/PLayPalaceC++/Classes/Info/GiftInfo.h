#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: GiftInfo.h
*/
#include "BaseItemInfo.h"
#include "Manager/LanguageManager.h"

struct GiftInfo : public BaseItemInfo
{
	std::string message;
	std::string message_en;
	std::string message_vn;
	std::string message_cn;
	std::string message_tw;
	std::string message_my;
	std::string message_indo;
	double coinReward;
	int crownReward;
	int luckyWheelReward;
	int keyReward;
	int64_t fromUserId;
	int64_t toUserId;
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
		if (data.HasMember(JSONFieldConstant::MESSAGE_EN.c_str()))
			this->message_en = data[JSONFieldConstant::MESSAGE_EN.c_str()].GetString();
		if (data.HasMember(JSONFieldConstant::MESSAGE_VN.c_str()))
			this->message_vn = data[JSONFieldConstant::MESSAGE_VN.c_str()].GetString();
		if (data.HasMember(JSONFieldConstant::MESSAGE_CN.c_str()))
			this->message_cn = data[JSONFieldConstant::MESSAGE_CN.c_str()].GetString();
		if (data.HasMember(JSONFieldConstant::MESSAGE_TW.c_str()))
			this->message_tw = data[JSONFieldConstant::MESSAGE_TW.c_str()].GetString();
		if (data.HasMember(JSONFieldConstant::MESSAGE_MY.c_str()))
			this->message_my = data[JSONFieldConstant::MESSAGE_MY.c_str()].GetString();
		if (data.HasMember(JSONFieldConstant::MESSAGE_INDO.c_str()))
			this->message_indo = data[JSONFieldConstant::MESSAGE_INDO.c_str()].GetString();

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

	std::string getMessage() {
		std::string mes = "";
		switch (LanguageManager::getInstance()->getCurrentLanguage()) {
		case SupportLanguage::en:
			mes = this->message_en;
			break;
		case SupportLanguage::vn:
			mes = this->message_vn;
			break;
		case SupportLanguage::cn:
			mes = this->message_cn;
			break;
		case SupportLanguage::tran_cn:
			mes = this->message_tw;
			break;
		case SupportLanguage::my:
			mes = this->message_my;
			break;
		case SupportLanguage::indo:
			mes = this->message_indo;
			break;
		}
		if (mes.empty()) {
			mes = this->message;
		}
		return mes;
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