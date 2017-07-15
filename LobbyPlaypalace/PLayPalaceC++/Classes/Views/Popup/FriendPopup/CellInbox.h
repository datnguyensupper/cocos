#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-08
* file: CellInbox.h, CellInbox.cpp
*/
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Info/GiftInfo.h"

class CellInbox : public ButtonAdjustClikableAreaSize
{
private:
	cocos2d::ClippingNode *avatarUserClippingNode;
	cocos2d::Sprite *avatarUserSprite;
	cocos2d::Sprite *avatarIconSprite;
	cocos2d::Label *messageLabel;

	GiftInfo* giftInfo;
	cocos2d::Size cellSize;
public:
	/// <summary>
	/// create cell UI
	/// </summary>
	/// <param name="_giftInfo"></param>
	/// <param name="cellSize"></param>
	/// <returns></returns>
	static CellInbox* create(GiftInfo *_giftInfo, cocos2d::Size cellSize);
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* 2017-08-03: Kiet: get gift info
	*/
	GiftInfo* getGiftInfo() {
		return this->giftInfo;
	}

	/// <summary>
	/// get size of cell
	/// </summary>
	/// <returns></returns>
	virtual cocos2d::Size getContentSize() {
		return this->getCustomSize();
	}

	/**
	* 2017-08-03: Kiet: update cell
	*/
	void updateCell(GiftInfo *_giftInfo);
};