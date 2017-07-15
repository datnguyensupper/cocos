#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: Helper4String.h, Helper4String.cpp
*/
#include "cocos2d.h"
#include <iomanip>
#include <locale>

using namespace std;
class Helper4String
{
public:
	/**
	* 2017-02-09: Kiet: split string
	*/
	static vector<string> splitString(std::string stringParam, std::string delimiter);
	/// <summary>
	/// get file name from path
	/// </summary>
	/// <param name="pathname"></param>
	/// <returns></returns>
	static std::string getFileNameFromPath(std::string const& pathname);
	//static std::string getBaseNameFromPath(std::string const& pathname);

	/**
	* 2017-02-13: Kiet: replace string
	*/
	static cocos2d::CCString* replaceCCString(cocos2d::CCString* cs, const cocos2d::CCString* csearch, const cocos2d::CCString* creplace);

	/**
	* 2017-02-22: Kiet: upcase or lowcase string
	* @param upcase: 1 if upcase else lowcase
	*/
	static std::string upcaseOrLowcaseString(std::string target, int upcase = 1);

	/// <summary>
	/// Dat check if parent contain child
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="child"></param>
	/// <returns></returns>
	static bool isStringContain(std::string parent, std::string child);

	/// <summary>
	/// format number with comma
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	static std::string FormatWithCommas(int value);
};