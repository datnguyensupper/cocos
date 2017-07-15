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
	/// <summary>
	/// from milisecond to string on normal format
	/// </summary>
	/// <param name="millisecond"></param>
	/// <returns></returns>
	static string millisecondTimeToNormalTimeHourMinAndSecString(int millisecond);
};