#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-15
* file: ButtonGameSlot.h, ButtonGameSlot.cpp
*/
#include "cocos2d.h"

class MascotNotificationPopup : public cocos2d::Node
{
private:
	cocos2d::Sprite* bg;
	cocos2d::Label* txtMessage;

	int soundEffect = -1;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// show mascot noti popup
	/// </summary>
	/// <param name="parent">parent of popup</param>
	/// <param name="message">message</param>
	/// <param name="pos">position of popup</param>
	void show(cocos2d::Node* parent, const std::string& message, cocos2d::Vec2 pos = cocos2d::Vec2::ZERO);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(MascotNotificationPopup);
};
