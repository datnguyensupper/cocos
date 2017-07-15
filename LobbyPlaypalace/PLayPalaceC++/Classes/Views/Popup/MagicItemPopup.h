#pragma once
#include "BasePopup.h"

class HeaderMagicItemBtn;
class MagicItemPopup : public BasePopup
{
private:
	HeaderMagicItemBtn *magicItemIcon;
	cocos2d::Label *leftSpinOfTimeLabel;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// prepare and show
	/// </summary>
	/// <param name="parent">parent of popup</param>
	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(MagicItemPopup);
};