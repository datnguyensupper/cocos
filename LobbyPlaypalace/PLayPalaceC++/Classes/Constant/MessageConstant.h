#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: MessageConstant.h, MessageConstant.cpp
*/
#include "cocos2d.h"
using namespace std;
class MessageConstant
{
public:
	/* Common */
	static const string MESSAGE_UPDATE_GAME_SLOT_PREFIX;
	static const string MESSAGE_UPDATE_GAME_SLOT;
	static const string MESSAGE_UPDATE_PP;
	static const string MESSAGE_WARNING;
	static const string MESSAGE_EMPTY;
	static const string MESSAGE_SUCCESS;
	static const string NOTICE;
	static const string MESSAGE_PLEASE_UPDATE_NEW_VERSION_ON_PLAYSTORE;
	static const string MESSAGE_OK;
	static const string MESSAGE_REMOVE;
	static const string MESSAGE_DOWNLOAD;
	static const string MESSAGE_LOGIN_FACEBOOK;
	static const string MESSAGE_STOP_DOWNLOAD;
	static const string MESSAGE_CONTINUE_DOWNLOAD;
	static const string MESSAGE_ERROR;
	static const string MESSAGE_NETWORK_ERROR;
	static const string MESSAGE_FORCE_UPDATE_NEW_VERSION;
	
	static const string MESSAGE_COMPLETE;
	static const string MESSAGE_DOLLAR;
	static const string MESSAGE_PLEASE_TRY_AGAIN_LATER;
	static const string MESSAGE_SUCCESSFUL;
	static const string MESSAGE_FAIL;
	static const string MESSAGE_DOWNLOAD_REQUIRED;
	static const string MESSAGE_EMAIL_REQUIRED;
	static const string MESSAGE_FILE_CORRUPTED;
	static const string MESSAGE_LOST_INTERNET_CONNECTION;
	static const string MESSAGE_SERVER_MAINTENANCE_TITLE;
	static const string MESSAGE_SERVER_MAINTENANCE_MESSAGE;
	static const string MESSAGE_MULTIPLE_LOGIN;

	static const string MESSAGE_NOT_ENOUGH_DISK_SPACE;
	static const string MESSAGE_SOMETHING_WRONG;
	static const string MESSAGE_USER_NOT_ACTIVE;
	static const string MESSAGE_LOGIN_MAINTENANCE;
	
	/* Collect coin */
	static const string COLLECT_COINS_SUCCESSFUL;

	/* Sign Up */
	static const string SIGNUP_SUCESS;
	static const string SIGNUP_SUCESS_MESSAGE;
	static const string SIGNUP_FAIL;
	static const string SIGNUP_FAIL_EMPTY_FIELD;
	static const string SIGNUP_FAIL_EMPTY_FIELD_EMAIL;
	static const string SIGNUP_FAIL_EMPTY_FIELD_PASSWORD;
	static const string SIGNUP_FAIL_RETYPE_PASSWORD_INCORRECT;
	static const string SIGNUP_FAIL_INVALID_EMAIL;
	static const string SIGNUP_FAIL_INVALID_PASSWORD;
	static const string SIGNUP_FAIL_PASSWORD_POLICY;
	static const string SIGNUP_FAIL_USER_EXIST;

	/* Reset password */
	static const string RESET_PASSWORD;
	static const string RESET_PASSWORD_WARNING;
	static const string NETWORK_CONNECTION_WAS_LOST;
	static const string RESET_PASSWORD_EMAIL_SENT_TO;
	static const string RESET_PASSWORD_FURTHER_INSTRUCTION;
	static const string RESET_PASSWORD_USER_NOT_EXIST;

	/* Login */
	static const string LOGIN_FAIL;
	static const string LOGIN_FAIL_INVALID_EMAIL;
	static const string LOGIN_FAIL_WRONG_USER_OR_PASSWORD;
	static const string LOGIN_FAIL_EMPTY_FIELD_PASSWORD;
	static const string LOGIN_FAIL_EMPTY_FIELD_EMAIL;

	/* About */
	static const string ABOUT_GAME_UP_TO_DATE;
	static const string ABOUT_NEW_VERSION;
	static const string ABOUT_PLEASE_UPDATE_NEW_VERSION;
	static const string ABOUT_COPIED;

	/* Friend */
	static const string FRIEND_SEND_FREE_GIFT_SUCCESS;
	static const string FRIEND_NOTICE;
	static const string FRIEND_HAVE_NOT_CHOOSE_ANY_FRIEND_YET;
	static const string FRIEND_INVITE_SUCCESS;


	/* Download */
	static const string DOWNLOAD_PLAY_OTHER_AVAILABLE_GAME;
	static const string DOWNLOAD_REMOVE_GAME;


	/* Profile */
	static const string PROFILE_USER_REJECTED_ON_FACEBOOK;


	/* Send Coin */
	static const string SEND_COIN_MUST_BE_NUMBER;
	static const string SEND_COIN_MAXIMUM_COIN;
	static const string SEND_COIN_MINIMUM_COIN;
	static const string SEND_COIN_HAS_BEEN_SEND_TO;

	/* Shop */
	static const string PURCHASE_SUCCESS_RECEIVE_COIN;


	/* Setting */
	static const string SETTING_INVALID_EMAIL;
	static const string SETTING_ISSUE_TYPE_REQUIRE;
	static const string SETTING_DESCRIPTION_REQUIRE;
	static const string SETTING_SEND_MESSAGE_SUCCESS;
	static const string LOGGED_IN_VIA;
	static const string LOGGED_IN_VIA_FACEBOOK;
	static const string LOGGED_IN_VIA_GUEST;
	static const string LOGGED_IN_VIA_PLAYPALACE;

	/* Update Name */
	static const string UPDATENAME_PLEASE_TYPE_NAME;
	static const string UPDATENAME_CHANGE_NAME_SUCCESS;
	static const string UPDATENAME_CHANGE_NAME_REACH_LIMIT;

	/* Facebook result */
	static const string ERROR_STRING_WHEN_OFFLINE;


	/* Redeem voucher */
	static const string REDEEM_CODE_TITLE;
	static const string REDEEM_CODE_DESCRIPTION;
	static const string REDEEM_CODE_GIFT_ALREADY_ACCEPTED;
	static const string REDEEM_CODE_VOUCHER_EXPIRED;
	static const string REDEEM_CODE_INVALID_VOUCHER_TOKEN;
	static const string REDEEM_CODE_SUCCESS;

	/* Slot game info */
	static const string NEW_GAME_TITLE;
	static const string NEW_GAME_DESCRIPTION;

	static const string GAME_REQUIRE_LEVEL_TITLE;
	static const string GAME_REQUIRE_CROWN_TITLE;

	static const string GAME_REQUIRE_LEVEL_UNLOCK_1;
	static const string GAME_REQUIRE_LEVEL_UNLOCK_2;

	static const string GAME_REQUIRE_CROWN_UNLOCK;

	static const string GAME_LOCK_LEVEL_TEXT;
	static const string GAME_LOCK_UNLOCK_TEXT;
	static const string GAME_LOCK_CROWNS_TEXT;
	static const string GAME_LOCK_COMING_SOON;


	static const string MESSAGE_SLOT_GAME_UNLOCKED;
	static const string MESSAGE_GAME_NOT_ENOUGH_CROWN_UNLOCK;

	static const string MESSAGE_BUY_MISSING;
	static const string MESSAGE_GO_TO_SHOP;
	static const string MESSAGE_BUY_MISSING_COIN;
	static const string MESSAGE_BUY_MISSING_CROWN;
	/* Leaderboard*/
	static const string LEADERBOARD;
};