#pragma once
#include "cocos2d.h"

class KeyboardHelper
{
public:
	/** Returns the shared instance of the AnimationHelper.
	* @return The instance of the AnimationHelper.
	*/
	static KeyboardHelper* getInstance();
	/// <summary>
	/// copy text to clipboard
	/// </summary>
	/// <param name="textNeed2Copy"></param>
	void copyText2ClipBoard(std::string textNeed2Copy);
};
