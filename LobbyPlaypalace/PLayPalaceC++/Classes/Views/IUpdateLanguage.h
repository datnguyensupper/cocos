#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-22
* file: IUpdateLanguage.h
*/
#include "cocos2d.h"
class IUpdateLanguage
{
public:
	virtual ~IUpdateLanguage() {}
	virtual void updateAfterChangeLanguage() = 0;
};