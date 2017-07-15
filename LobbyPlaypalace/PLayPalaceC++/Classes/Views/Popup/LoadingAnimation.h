#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-23
* file: LoadingAnimation.h, LoadingAnimation.cpp
*/
#include "BasePopup.h"

class LoadingAnimation : public BasePopup
{
private:
	cocos2d::Sprite* loadingAnimationLogin;
	cocos2d::Sprite* loadingAnimationLobby;

	virtual void playSoundOpenPopup() override {};
	virtual void playSoundClosePopup() override {};
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// 2017-02-18: Kiet: prepare and show
	/// </summary>
	/// <param name="parent">parent of popup</param>
	void prepareAndShow(
		cocos2d::Node* parent
	);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LoadingAnimation);
};