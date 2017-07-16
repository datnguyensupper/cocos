#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: BaseItemInfo.h
*/
#include "cocos2d.h"
#include "json/writer.h"
#include "json/document.h"
#include "Constant/JSONFieldConstant.h"

using namespace std;

class BaseItemInfo
{
public:
#pragma region fields

	int64_t id;
	int64_t timestampOfCreated;
	int64_t timestampOfLastModified;
	string info;
	string name;

#pragma endregion

	/**
	* 2017-02-13: Kiet: update base item info
	*/
	void updateBaseItemInfoByValue(rapidjson::Value &beanData)
	{
//		if (beanData == NULL)
//		{
//			return;
//		}
		if (beanData.HasMember(JSONFieldConstant::ID.c_str())){
			this->id = beanData[JSONFieldConstant::ID.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::TS_CREATED.c_str())){
			this->timestampOfCreated = beanData[JSONFieldConstant::TS_CREATED.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::TS_LAST_MODIFIED.c_str())){
			this->timestampOfLastModified = beanData[JSONFieldConstant::TS_LAST_MODIFIED.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::INFO.c_str())){
			this->info = beanData[JSONFieldConstant::INFO.c_str()].GetString();
		}
		if (beanData.HasMember(JSONFieldConstant::NAME.c_str())){
			this->name = beanData[JSONFieldConstant::NAME.c_str()].GetString();
		}
	}

	void update(BaseItemInfo * baseItemInfo) {
		if (baseItemInfo) {
			this->id = baseItemInfo->id;
			this->timestampOfCreated = baseItemInfo->timestampOfCreated;
			this->timestampOfLastModified = baseItemInfo->timestampOfLastModified;
			this->info = baseItemInfo->info;
			this->name = baseItemInfo->name;
		}
	}
};
