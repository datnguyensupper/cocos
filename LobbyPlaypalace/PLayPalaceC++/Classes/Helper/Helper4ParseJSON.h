#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: Helper4String.h, Helper4String.cpp
*/
#include "cocos2d.h"
#include "json/writer.h"
#include "json/document.h"

using namespace std;
class Helper4ParseJSON
{
public:
	/// <summary>
	/// get list size from object json
	/// </summary>
	/// <param name="responseAsDocument"></param>
	/// <returns></returns>
	static int getListSize(rapidjson::Value &responseAsDocument);
	/// <summary>
	/// get item member from object json
	/// </summary>
	/// <param name="responseAsDocument"></param>
	/// <returns></returns>
	static rapidjson::GenericArray<0, rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>> getMember(rapidjson::Value &responseAsDocument);
	/// <summary>
	/// get bean type from object json
	/// </summary>
	/// <param name="responseAsDocument"></param>
	/// <returns></returns>
	static std::string getBeanType(rapidjson::Value &responseAsDocument);
	/// <summary>
	/// get item bean from object json
	/// </summary>
	/// <param name="responseAsDocument"></param>
	/// <returns></returns>
	static rapidjson::Value& getBeanData(rapidjson::Value &responseAsDocument);

};