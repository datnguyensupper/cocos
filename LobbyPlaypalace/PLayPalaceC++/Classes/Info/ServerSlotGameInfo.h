#pragma once
#include "BaseItemInfo.h"
#include "Constant/Defination.h"
#include "Constant/PPEnums.h"
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: UserInfo.h
*/

class ServerSlotGameInfo : public BaseItemInfo
{
public:
	int orderId;
	std::string gameId;
	std::string gameIdLocal;
	std::string newestVersion;
	int minLevel;
	int platform;
	int premiumType;
	int minCrown;
	bool available;
	bool bUnlocked;

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
		this->orderId = data[JSONFieldConstant::ORDER_ID.c_str()].GetInt();
		this->gameId = data[JSONFieldConstant::GAME_ID.c_str()].GetString();


		switch (orderId)
		{
		case ppEnum::NEZHA:
			this->gameIdLocal = GAME_SLOT_ID_NEZHA;
			this->newestVersion = GAME_SLOT_RS_VERSION_NEZHA;
			break;
		case ppEnum::GOLDEN_EGGS:
			this->gameIdLocal = GAME_SLOT_ID_GOLDENEGG;
			this->newestVersion = GAME_SLOT_RS_VERSION_GOLDENEGG;
			break;
		case ppEnum::PHARAOH:
			this->gameIdLocal = GAME_SLOT_ID_PHARAOH;
			this->newestVersion = GAME_SLOT_RS_VERSION_PHARAOH;
			break;
		case ppEnum::BOXING:
			this->gameIdLocal = GAME_SLOT_ID_BOXING;
			this->newestVersion = GAME_SLOT_RS_VERSION_BOXING;
			break;
		case ppEnum::ROMAN_EMPIRE:
			this->gameIdLocal = GAME_SLOT_ID_ROMANEMPIRE;
			this->newestVersion = GAME_SLOT_RS_VERSION_ROMANEMPIRE;
			break;
		case ppEnum::DEEP_BLUE:
			this->gameIdLocal = GAME_SLOT_ID_DEEPBLUE;
			this->newestVersion = GAME_SLOT_RS_VERSION_DEEPBLUE;
			break;
		default:
			this->gameIdLocal = GAME_SLOT_RS_VERSION_DEFAULT;
			this->gameIdLocal = this->gameId;
			break;
		}

		this->minLevel = data[JSONFieldConstant::MIN_LEVEL.c_str()].GetInt();
		this->platform = data[JSONFieldConstant::PLATFORM.c_str()].GetInt();
		this->premiumType = data[JSONFieldConstant::PREMIUM_TYPE.c_str()].GetInt();
		this->minCrown = data[JSONFieldConstant::MIN_CROWN.c_str()].GetInt();
		this->available = data[JSONFieldConstant::AVAILABLE.c_str()].GetBool();
		this->bUnlocked = data[JSONFieldConstant::IS_UNLOCKED.c_str()].GetBool();
	}
};
