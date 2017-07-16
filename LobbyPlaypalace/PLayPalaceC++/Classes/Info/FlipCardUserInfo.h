#pragma once
#include "BaseItemInfo.h"
#include "Helper/Helper4ParseJSON.h"
#include "Constant/JSONFieldConstant.h"
#include "Constant/LobbyConstant.h"

using namespace rapidjson;
using namespace std;

class FlipCardUserInfo
{
private:
	std::map<LobbyConstant::FlipCardType, int> info;
public:
	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data) {
		auto dataArray = Helper4ParseJSON::getMember(data);
		info.clear();
		for (int i = 0, size = dataArray.Size(); i < size; ++i) {
			auto type = (LobbyConstant::FlipCardType)dataArray[i][JSONFieldConstant::CARD_TYPE.c_str()].GetInt();
			auto level = dataArray[i][JSONFieldConstant::CARD_LEVEL.c_str()].GetInt();
			info[type] = level;
		}
	}

	std::map<LobbyConstant::FlipCardType, int> getInfo() { return info; }
};