#include "Helper4ParseJSON.h"
#include "Constant/JSONFieldConstant.h"

USING_NS_CC;



int Helper4ParseJSON::getListSize(rapidjson::Value &responseAsDocument) {
	return responseAsDocument[JSONFieldConstant::LIST_SIZE.c_str()].GetInt();
}
rapidjson::GenericArray<0, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>> Helper4ParseJSON::getMember(rapidjson::Value &responseAsDocument) {
	return responseAsDocument[JSONFieldConstant::MEMBER.c_str()].GetArray();
}

std::string Helper4ParseJSON::getBeanType(rapidjson::Value &responseAsDocument) {
	return responseAsDocument[JSONFieldConstant::BEAN_TYPE.c_str()].GetString();
}

rapidjson::Value& Helper4ParseJSON::getBeanData(rapidjson::Value &responseAsDocument) {
	return responseAsDocument[JSONFieldConstant::BEAN.c_str()];
}