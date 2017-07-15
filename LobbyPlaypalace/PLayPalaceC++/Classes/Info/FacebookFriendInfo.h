#pragma once
#include "UserInfo.h"
#include "Helper/Helper4ParseJSON.h"
/**
* creator: Kiet Duong
* date: 2017-03-10
* file: FacebookFriendInfo.h
*/

using namespace rapidjson;
using namespace std;

struct InvitableFriendInfo
{
	std::string name;
	std::string facebookUID;
	std::string pictureURL;
};
class FacebookFriendInfo
{
private:
	long long lastTsGetFriendList = 0;
	long userIdCurrentFriendList = 0;
	std::map<std::string, UserInfo*> friendList;
	std::map<std::string, InvitableFriendInfo*> invitableFriendList;
public:
	/// <summary>
	/// get timestamp of last time get friend list
	/// </summary>
	/// <returns></returns>
	long long getLastTsGetFriendList() {
		return this->lastTsGetFriendList;
	}
	/// <summary>
	/// get login user id
	/// </summary>
	/// <returns></returns>
	long getUserIdCurrentFriendList() {
		return this->userIdCurrentFriendList;
	}
	/// <summary>
	/// set login user id
	/// </summary>
	/// <param name="userId"></param>
	void setUserIdCurrentFriendList(long userId) {
		this->userIdCurrentFriendList = userId;
	}

	std::map<std::string, UserInfo*> getFriendList() {
		return this->friendList;
	}
	std::map<std::string, InvitableFriendInfo*> getInvitableFriendList() {
		return this->invitableFriendList;
	}
	/// <summary>
	/// update facebook pp friend list
	/// </summary>
	/// <param name="friendListData"></param>
	void updateFriendList(rapidjson::Value &friendListData)
	{
		for (auto child : friendList)
		{
			CC_SAFE_DELETE(child.second);
		}
		friendList.clear();

		auto listSize = Helper4ParseJSON::getListSize(friendListData);
		auto members = Helper4ParseJSON::getMember(friendListData);
		for (int i = 0; i < listSize; i++)
		{
			auto userInfo = new UserInfo();
			userInfo->updateUserInfoByValue(members[i]);

			friendList[userInfo->facebookUID] = userInfo;
		}
		this->lastTsGetFriendList = cocos2d::utils::getTimeInMilliseconds();
	}
	/// <summary>
	/// update facebook invitable friend list
	/// </summary>
	/// <param name="invitableFriendInfoList"></param>
	void updateInvitableFriendList(vector<InvitableFriendInfo*> invitableFriendInfoList)
	{
		CCLOG("updateInvitableFriendList ");
		for (auto child : invitableFriendList)
		{
			CC_SAFE_DELETE(child.second);
		}
		invitableFriendList.clear();

		for (auto child : invitableFriendInfoList)
		{
			invitableFriendList[child->facebookUID] = child;
		}
		CCLOG("invitableFriendList size = %d ", invitableFriendList.size());
	}
};