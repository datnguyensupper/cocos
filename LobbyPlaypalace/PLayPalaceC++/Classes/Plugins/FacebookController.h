#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-01
* file: FacebookController.h, FacebookController.cpp
*/
//THAM KHAO: https://github.com/sdkbox/sdkbox-sample-facebook/blob/master/cpp/Classes/HelloWorldScene.h
//THAM KHAO: http://docs.sdkbox.com/en/plugins/facebook/v3-cpp/
#include "cocos2d.h"
#include "Info/FacebookFriendInfo.h"

#ifdef SDKBOX_ENABLED
#include "PluginFacebook/PluginFacebook.h"
#else
#include "proj.android-studio/app/jni/pluginfacebook/PluginFacebook.h"
#endif

class FacebookController : public sdkbox::FacebookListener
{
private:
	/**
	* 2017-03-01: Kiet: callbacks and listeners
	*/
	std::function<void(bool isLogin, const std::string& msg)> callbackLogin = nullptr;
	std::function<void(bool ok, const std::string& msg)> callbackFetchFriends = nullptr;
	std::function<void(std::vector<InvitableFriendInfo*>& friends)> callbackInvitableFriends = nullptr;
	std::function<void(const std::string& message)> callbackShareSuccess = nullptr;
	std::function<void(const std::string& message)> callbackShareFail = nullptr;
	std::function<void(void)> callbackShareCancel = nullptr;
	std::function<void(bool result, const std::string& msg)> callbackInviteFriendsWithInviteIdsResult = nullptr;
	std::map <std::string, std::function<void(const std::string& key, const std::string& jsonData)>> callbackOnAPIMap;
	std::function<void(bool result, const std::string& msg)> callbackSendGift = nullptr;
	
	void onLogin(bool isLogin, const std::string& msg);
	void onFetchFriends(bool ok, const std::string& msg);
	//@deprecated: using onAPI instead
	void onRequestInvitableFriends(const sdkbox::FBInvitableFriendsInfo& friends);
	void onSharedSuccess(const std::string& message);
	void onSharedFailed(const std::string& message);
	void onSharedCancel();
	void onInviteFriendsWithInviteIdsResult(bool result, const std::string& msg);
	void onAPI(const std::string& key, const std::string& jsonData);
	void onSendGiftResult(bool result, const std::string& msg);
	/**
	* 2017-03-01: Kiet: unuse listeners
	*/
	void onPermission(bool isLogin, const std::string& msg) {};
	void onInviteFriendsResult(bool result, const std::string& msg) {};
	void onGetUserInfo(const sdkbox::FBGraphUser& userInfo) {};

	std::vector<int> requestInvitableFriendListQueue;
public:
	FacebookController();
	bool getIsRequestingInvitableFriendList() {
		return this->requestInvitableFriendListQueue.size() > 0;
	}
	/**
	* 2017-03-01: Kiet: login facebook
	*/
	void login(std::function<void(bool isLogin, const std::string& msg)> callback);
    
    /**
     * Dat: check is logined facebook
     */
    bool isLogined();
    
	/**
	* 2017-03-01: Kiet: get friends
	*/
	void getMyFriends(std::function<void(bool ok, const std::string& msg)> callback);
	/**
	* 2017-03-01: Kiet: invitable friends
	*/
	void getInvitableFriends(std::function<void(std::vector<InvitableFriendInfo*>& friends)> callback);
	/**
	* 2017-03-01: Kiet: share
	*/
	void share(
		sdkbox::FBShareInfo fbShareInfo, 
		std::function<void(const std::string& message)> callbackSuccess,
		std::function<void(const std::string& message)> callbackFail,
		std::function<void(void)> callbackCancel
	);
	/**
	* 2017-03-01: Kiet: invites
	*/
	void inviteFriends(
		const std::vector <std::string>& invite_ids,
		std::function<void(bool result, const std::string& msg)> callback
	);
	/**
	* 2017-03-01: Kiet: get access token
	*/
	std::string getAccessToken();

	/**
	* 2017-03-22: Kiet: send gift
	*/
	void sendGifts(std::vector<std::string> facebookUIDs, std::function<void(bool result, const std::string& msg)> callback);
};
