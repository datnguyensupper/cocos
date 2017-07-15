#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: Helper4String.h, Helper4String.cpp
*/
#include "cocos2d.h"
using namespace std;

class BaseScene;
class Helper4Scene
{
public:
	/// <summary>
	/// get current scene
	/// </summary>
	/// <returns></returns>
    static cocos2d::Scene* getRunningScene();
	/// <summary>
	/// check if any problem with current scene
	/// </summary>
	/// <returns></returns>
    static bool isUnexpectedProblemWithCurrentScene();
};
