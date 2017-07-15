#pragma once

#include "cocos2d.h"

class GamePlugin
{
private:
public:
	/// <summary>
	/// crop circle image
	/// </summary>
	/// <param name="data">image data</param>
	/// <param name="len">size of image data</param>
	/// <returns></returns>
	cocos2d::Image* circleImage(unsigned char* data, size_t len);
};