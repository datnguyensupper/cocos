#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-10
* file: CellFriend.h, CellFriend.cpp
*/
#include "Custom/Common/ButtonAdjustClikableAreaSize.h"
#include "Custom/Common/ToggleButton.h"
#include "Info/BaseItemInfo.h"

struct FriendFBInfo
{
	bool _isPPUser;
	std::string _name;
	std::string _levelAsString;
	std::string _facebookUID;
	std::string _avatarURL;
	bool _isSelected = false;
	/// <summary>
	/// init cell info
	/// </summary>
	/// <param name="isPPUser">is playpalace user</param>
	/// <param name="name"></param>
	/// <param name="levelAsString">level of user</param>
	/// <param name="facebookUID">facebook id</param>
	/// <param name="avatarURL">url of avatar</param>
	FriendFBInfo(
		bool isPPUser,
		std::string name,
		std::string levelAsString,
		std::string facebookUID,
		std::string avatarURL)
	{
		this->_isPPUser = isPPUser;
		this->_name = name;
		this->_levelAsString = levelAsString;
		this->_facebookUID = facebookUID;
		this->_avatarURL = avatarURL;
	}
};
class CellFriend : public cocos2d::ui::Widget
{
private:
	cocos2d::Sprite *avatarSprite = nullptr;
	cocos2d::Sprite *stardom = nullptr;
	cocos2d::Label *nameLabel = nullptr;
	cocos2d::Label *levelLabel = nullptr;
	ToggleButton *toggleButton = nullptr;

	FriendFBInfo* friendFBInfo;
	cocos2d::Size cellSize;
public:
	/// <summary>
	/// create cell ui for friend
	/// </summary>
	/// <param name="_friendFBInfo"></param>
	/// <param name="cellSize">size of cell</param>
	/// <returns></returns>
	static CellFriend* create(FriendFBInfo *_friendFBInfo, cocos2d::Size cellSize);
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* 2017-08-03: Kiet: get gift info
	*/
	FriendFBInfo* getFriendFBInfo() {
		return this->friendFBInfo;
	}

	/**
	* 2017-08-03: Kiet: update cell
	*/
	void updateCell(FriendFBInfo *_friendFBInfo);
	/**
	* 2017-08-03: Kiet: update toggle is visible base on friend fb info
	*/
	void updateToggleVisible();
};