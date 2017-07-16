#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: Helper4String.h, Helper4String.cpp
*/
#include "cocos2d.h"
using namespace std;

class Helper4Time
{
public:
	static const int64_t ONE_MINUTE_MILLISECOND = 60 * 1000;
	static const int64_t ONE_HOUR_MILLISECOND = 3600 * 1000;
	static const int64_t ONE_DAY_MILLISECOND = 24 * 3600 * 1000;
	/// <summary>
	/// from milisecond to string on normal format
	/// </summary>
	/// <param name="millisecond"></param>
	/// <returns></returns>
	static string millisecondTimeToNormalTimeHourMinAndSecString(double millisecond);
	/// <summary>
	/// get current timestamp (millisecond)
	/// </summary>
	/// <param name="millisecond"></param>
	/// <returns></returns>
	static int64_t getCurrentTimeStamp();
};