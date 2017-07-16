#include "FacebookController.h"
#include "Configs.h"
#include "Helper/Helper4String.h"

USING_NS_CC;
#define LIMIT_INVITABLE_FRIENDS 5000
#define SEND_GIFT_TITLE "Welcome"
#define SEND_GIFT_MESS "I send a special gift up to $100,000 to you! Good luck!"
#define INVITE_TITLE "Welcome"
#define INVITE_MES "Join PlayPalace with me!"

void FacebookController::onLogin(bool isLogin, const std::string & msg)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON LOGIN: \nIsLogin = %s \n msg = %s", isLogin ? "true":"false", msg.c_str());
	}
	if (this->callbackLogin)
	{
		this->callbackLogin(isLogin, msg);
	}
}

void FacebookController::onFetchFriends(bool ok, const std::string & msg)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON FETCH FRIENDS\n ok = %s\n msg = %s", ok ? "true" : "false", msg.c_str());
	}
	if (this->callbackFetchFriends)
	{
		this->callbackFetchFriends(ok, msg);
	}
}

void FacebookController::onRequestInvitableFriends(const sdkbox::FBInvitableFriendsInfo & friends)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON REQUEST INVITABLE FRIENDS");
	}
	if (this->callbackInvitableFriends)
	{
		std::vector<InvitableFriendInfo*> inviteableFriends;
		if (Configs::printConsoleLog)
		{
			CCLOG("Request Inviteable Friends Begin");
		}
		#ifdef SDKBOX_ENABLED
				for (auto it = friends.begin(); it != friends.end(); ++it) {
					if (Configs::printConsoleLog)
					{
						CCLOG("Invitable friend: %s", it->getName().c_str());
						CCLOG("UserId: %s", it->getUserId().c_str());
						CCLOG("PictureURL: %s", it->getPictureURL().c_str());
					}
					InvitableFriendInfo *invitableFriend = new InvitableFriendInfo();
					invitableFriend->name = it->getName();
					invitableFriend->facebookUID = it->getUserId();
					invitableFriend->pictureURL = it->getPictureURL();
					inviteableFriends.push_back(invitableFriend);
			}
		#endif
		if (Configs::printConsoleLog)
		{
			CCLOG("Request Inviteable Friends End");
		}
		if (Configs::printConsoleLog)
		{
			if (0 == inviteableFriends.size()) {
				CCLOG("WARNING! Your Invitable Friends number is 0");
			}
		}
		this->callbackInvitableFriends(inviteableFriends);
		this->callbackInvitableFriends = nullptr;
	}
	if (this->requestInvitableFriendListQueue.size() > 0)
	{
		this->requestInvitableFriendListQueue.erase(this->requestInvitableFriendListQueue.begin());
	}
}

void FacebookController::onSharedSuccess(const std::string & message)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON SHARE SUCCESS\n message = %s", message.c_str());
	}
	if (this->callbackShareSuccess)
	{
		this->callbackShareSuccess(message);
	}
}

void FacebookController::onSharedFailed(const std::string & message)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON SHARE FAIL\n message = %s", message.c_str());
	}
	if (this->callbackShareFail)
	{
		this->callbackShareFail(message);
	}
}

void FacebookController::onSharedCancel()
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON SHARE CANCEL");
	}
	if (this->callbackShareCancel)
	{
		this->callbackShareCancel();
	}
}

void FacebookController::onInviteFriendsWithInviteIdsResult(bool result, const std::string & msg)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON INVITE FRIENDS WITH INVITE IDS RESULT\n result = %s\n msg = %s", result ? "true" : "false", msg.c_str());
	}
	if (this->callbackInviteFriendsWithInviteIdsResult)
	{
		this->callbackInviteFriendsWithInviteIdsResult(result, msg);
	}
}

void FacebookController::onAPI(const std::string & key, const std::string & jsonData)
{
	if (this->callbackOnAPIMap[key])
	{
		this->callbackOnAPIMap[key](key, jsonData);
	}
}

void FacebookController::onSendGiftResult(bool result, const std::string & msg)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("FACEBOOK: ON ASK GIFTS \n result = %s\n msg = %s", result ? "true" : "false", msg.c_str());
	}
	if (this->callbackSendGift)
	{
		this->callbackSendGift(result, msg);
	}
}

FacebookController::FacebookController()
{
#ifdef SDKBOX_ENABLED
	if (Configs::printConsoleLog)
	{
		CCLOG("INIT FB IN CONTRUCTOR FUNCTION");
	}
	sdkbox::PluginFacebook::init();
	sdkbox::PluginFacebook::setListener(this);
    sdkbox::PluginFacebook::setAppURLSchemeSuffix("Cocos");
#endif
}

void FacebookController::login(std::function<void(bool isLogin, const std::string&msg)> callback)
{
	this->callbackLogin = callback;
#ifdef SDKBOX_ENABLED
	bool isLoggedIn = isLogined();
	if (isLoggedIn)
	{
		sdkbox::PluginFacebook::logout();
	}
	if (Configs::printConsoleLog)
	{
		CCLOG("LOGIN FB with IsLoggedIn = %s", isLoggedIn ? "true" : "false");
	}
	std::vector<std::string> permissions;
	permissions.push_back(sdkbox::FB_PERM_READ_PUBLIC_PROFILE);
	permissions.push_back(sdkbox::FB_PERM_READ_EMAIL);
	permissions.push_back(sdkbox::FB_PERM_READ_USER_FRIENDS);
	sdkbox::PluginFacebook::login(permissions);
	
#endif
}

bool FacebookController::isLogined(){
#ifdef SDKBOX_ENABLED
    bool isLoggedIn = sdkbox::PluginFacebook::isLoggedIn();
    return isLoggedIn;
#else
    return false;
#endif
}

void FacebookController::getMyFriends(std::function<void(bool ok, const std::string&msg)> callback)
{
	this->callbackFetchFriends = callback;
#ifdef SDKBOX_ENABLED
	if (Configs::printConsoleLog)
	{
		CCLOG("GET FRIENDS FB");
	}
	sdkbox::PluginFacebook::fetchFriends();
#endif
}

void FacebookController::getInvitableFriends(std::function<void(std::vector<InvitableFriendInfo*>& friends)> callback)
{
	this->requestInvitableFriendListQueue.push_back(1);
	//this->callbackInvitableFriends = callback; 
//#ifdef SDKBOX_ENABLED
//	if (Configs::printConsoleLog)
//	{
//		CCLOG("GET INVITABLE FRIENDS FB");
//	}
//	sdkbox::FBAPIParam param;
//	param["fields"] = "picture.type(normal).width(100).height(100),name";
//	param["limit"] = StringUtils::toString(LIMIT_INVITABLE_FRIENDS);
//	sdkbox::PluginFacebook::requestInvitableFriends(param);
//#endif
	std::string tagCallback = StringUtils::toString(cocos2d::utils::getTimeInMilliseconds());
	auto callbackGetPerPage = [this, callback](
		const std::string& key, 
		const std::string& jsonData)
	{
		if (Configs::printConsoleLog)
		{
			CCLOG("callbackGetPerPage key: %s ; jsonData: %s", key.c_str(), jsonData.c_str());
		}
		if (jsonData.empty()) {
			return;
		}
		rapidjson::Document document;
		document.Parse(jsonData.c_str());

		std::vector<InvitableFriendInfo*> inviteableFriends;
		if (document.HasMember("data"))
		{
			if (Configs::printConsoleLog)
			{
				CCLOG("callbackGetPerPage key: %s ; jsonData: %s", key.c_str(), jsonData.c_str());
			}
			auto dataArray = document["data"].GetArray();
			if (Configs::printConsoleLog)
			{
				CCLOG("callbackGetPerPage data size: %d", dataArray.Size());
			}
			for (int i = 0; i < dataArray.Size(); i++)
			{
				InvitableFriendInfo* invitableFriendInfo = new InvitableFriendInfo();
				if (Configs::printConsoleLog)
				{
					CCLOG("before get name");
				}
				if (dataArray[i].HasMember("name"))
				{
					invitableFriendInfo->name = dataArray[i]["name"].GetString();
				}
				if (Configs::printConsoleLog)
				{
					CCLOG("before get id");
				}
				if (dataArray[i].HasMember("id"))
				{
					invitableFriendInfo->facebookUID = dataArray[i]["id"].GetString();
				}
				if (Configs::printConsoleLog)
				{
					CCLOG("before get picture url");
				}
				if (dataArray[i].HasMember("picture")
					&& dataArray[i]["picture"].HasMember("data")
					&& dataArray[i]["picture"]["data"].HasMember("url"))
				{
					invitableFriendInfo->pictureURL = dataArray[i]["picture"]["data"]["url"].GetString();
				}
				inviteableFriends.push_back(invitableFriendInfo);
				if (Configs::printConsoleLog)
				{
					CCLOG("Invitable friend: %s", invitableFriendInfo->name.c_str());
					CCLOG("UserId: %s", invitableFriendInfo->facebookUID.c_str());
					CCLOG("PictureURL: %s", invitableFriendInfo->pictureURL.c_str());
				}
			}
		}

		//if (document.HasMember("paging")
		//	&& document["paging"].HasMember("next"))
		//{
		//	//get path by subtring https://graph.facebook.com/ + version text + "/"
		//	std::string nextPage = document["paging"]["next"].GetString();
		//	if (!nextPage.empty()) {
		//		std::string pageAfterSubHostName
		//			= Helper4String::replaceCCString(
		//				__String::create(nextPage), 
		//				__String::create("https://graph.facebook.com/"),
		//				__String::create(""))->_string;
		//		int versionFBNameSize = Helper4String::splitString(pageAfterSubHostName, "/")[0].size();
		//		std::string completePath = pageAfterSubHostName.substr(versionFBNameSize + 1, pageAfterSubHostName.size() - versionFBNameSize - 1);
		//		if (Configs::printConsoleLog)
		//		{
		//			CCLOG("COMPLETE PATH FOR NEXT PAGE INVITABLE FRIENDS: %s", completePath.c_str());
		//		}

		//		std::string tagCallback = StringUtils::toString(cocos2d::utils::getTimeInMilliseconds());
		//		this->callbackOnAPIMap[tagCallback] = callbackGetPerPage;
		//		sdkbox::FBAPIParam param;
		//		sdkbox::PluginFacebook::api(
		//			completePath,
		//			"GET",
		//			param,
		//			tagCallback
		//		);
		//		return;//request next page, not call callback
		//	}
		//}
		if (callback)
		{
			callback(inviteableFriends);
		}
		if (this->requestInvitableFriendListQueue.size() > 0)
		{
			this->requestInvitableFriendListQueue.erase(this->requestInvitableFriendListQueue.begin());
		}
	};
	this->callbackOnAPIMap[tagCallback] = callbackGetPerPage;

#ifdef SDKBOX_ENABLED
	sdkbox::FBAPIParam param;
	param["fields"] = "picture.type(normal).width(100).height(100),name";
	param["limit"] = StringUtils::toString(LIMIT_INVITABLE_FRIENDS);
	sdkbox::PluginFacebook::api(
		"/me/invitable_friends",
		"GET",
		param,
		tagCallback
	);
#endif
}

void FacebookController::share(sdkbox::FBShareInfo fbShareInfo, std::function<void(const std::string&message)> callbackSuccess, std::function<void(const std::string&message)> callbackFail, std::function<void(void)> callbackCancel)
{
	this->callbackShareSuccess = callbackSuccess;
	this->callbackShareFail = callbackFail;
	this->callbackShareCancel = callbackCancel;
#ifdef SDKBOX_ENABLED
	if (Configs::printConsoleLog)
	{
		CCLOG("SHARE FB");
	}
	//sdkbox::PluginFacebook::share(fbShareInfo);
	sdkbox::PluginFacebook::dialog(fbShareInfo);
#endif

}

void FacebookController::inviteFriends(const std::vector<std::string>& invite_ids, std::function<void(bool result, const std::string&msg)> callback)
{
	this->callbackInviteFriendsWithInviteIdsResult = callback;
#ifdef SDKBOX_ENABLED
	if (Configs::printConsoleLog)
	{
		CCLOG("INVITE FRIEND WITH IDS FB");
	}
	sdkbox::PluginFacebook::inviteFriendsWithInviteIds(
		invite_ids, 
		INVITE_TITLE,
		INVITE_MES
	);
#endif
}

std::string FacebookController::getAccessToken()
{
#ifdef SDKBOX_ENABLED
	if (Configs::printConsoleLog)
	{
		CCLOG("GET ACCESS TOKEN FB");
	}
	return sdkbox::PluginFacebook::getAccessToken();
#endif
	return "";
}

void FacebookController::sendGifts(std::vector<std::string> facebookUIDs, std::function<void(bool result, const std::string& msg)> callback)
{
	this->callbackSendGift = callback;
#ifdef SDKBOX_ENABLED
	sdkbox::PluginFacebook::sendGift(facebookUIDs, Configs::freeGiftFacebookProductId,SEND_GIFT_TITLE, SEND_GIFT_MESS);
#endif
}
