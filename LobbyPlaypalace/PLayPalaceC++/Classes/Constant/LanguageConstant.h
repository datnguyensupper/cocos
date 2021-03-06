#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: LanguageConstant.h, LanguageConstant.cpp
*/
#include "cocos2d.h"
using namespace std;
class LanguageConstant
{
public:
	static const string POPUP_NEED_LEVEL_TO_PLAY_GAME;
	static const string SETTING_LANGUAGE_LABLE;
	static const string SETTING_LOGGED_WITH_LABLE;
	static const string SETTING_LOGOUT_LABLE;
	static const string SETTING_LOGIN_LABLE;
	static const string SETTING_GAME_OPTION_LABLE;
	static const string SETTING_BACK_GROUND_MUSIC_LABLE;
	static const string SETTING_BACK_SOUND_EFFECT_LABLE;
	static const string SETTING_LANGUAGE;
	static const string SETTING_REF_LABLE;
	static const string SETTING_MYCODE_LABLE;
	static const string SETTING_MYREFCODE_LABLE;
	static const string SETTING_FRIEND_REQUEST_LABLE;
	static const string SETTING_BTN_TEARM_LABLE;
	static const string SETTING_BTN_PRIVACY_LABLE;
	static const string SETTING_VERSION_LABLE;
	static const string SETTING_LANGUAGES;
	static const string FOOTER_COLLECT_LABLE;
	static const string FOOTER_COLLECT_TIME_BONUS_IN_LABLE;
	static const string FOOTER_ACHIEVEMENT_LABLE;
	static const string POPUP_PROFILE_TO_LEVEL_UP_LABLE;
	static const string FOOTER_GIFT_LABLE;
	static const string HEADER_PROFILE_TOOLTIP;
	static const string HEADER_INVITE_TOOLTIP;
	static const string HEADER_SENDGIFT_TOOLTIP;
	static const string HEADER_SHOP_TOOLTIP;
	static const string HEADER_STARDOM_TOOLTIP;
	static const string HEADER_LEVEL;
	static const string HEADER_RECENT_WINNER_TEXT;
	static const string POPUP_SHOP_TRANSACTION_CANCELLED;
	static const string POPUP_ACHIEVEMENT_TITLE;
	static const string POPUP_ACHIEVEMENT_TOTAL_ACHIEVEMENT_POINT;
	static const string POPUP_ACHIEVEMENT_GROUP_TITLE_GENERAL;
	static const string POPUP_ACHIEVEMENT_GROUP_TITLE_GAME;
	static const string POPUP_ACHIEVEMENT_GROUP_TITLE_SOCIAL;
	static const string POPUP_PROFILE_LOGO;
	static const string POPUP_PROFILE_LEVEL;
	static const string POPUP_PROFILE_RANK;
	static const string POPUP_PROFILE_MAXIMUMCOINS;
	static const string POPUP_PROFILE_PLAYEDSINCE;
	static const string POPUP_PROFILE_BTN_SENDFREEGIFT;
	static const string POPUP_PROFILE_BTN_SENDCOINS;
	static const string POPUP_PROFILE_SLOT_NUMBEROFJACKPOT;
	static const string POPUP_PROFILE_SLOT_WIN;
	static const string POPUP_PROFILE_SLOT_BIGGESTWIN;
	static const string POPUP_PROFILE_SLOT_TOTALSPIN;
	static const string POPUP_PROFILE_SLOT_NETPROFIT;
	static const string POPUP_PROFILE_BLACKJACK_NUMBEROFBLACKJACK;
	static const string POPUP_PROFILE_BLACKJACK_PLAYEDHAND;
	static const string POPUP_PROFILE_BLACKJACK_BIGGESTWIN;
	static const string POPUP_PROFILE_BLACKJACK_WIN;
	static const string POPUP_PROFILE_BLACKJACK_NETPROFIT;
	static const string POPUP_PROFILE_CHANGE_AVATAR;
	static const string POPUP_PROFILE_BLACKJACK_MAXWININAROW;
	static const string POPUP_GIFT_LEADERBOARD;
	static const string POPUP_GIFT_FRIENDS;
	static const string POPUP_GIFT_INBOX;
	static const string POPUP_GIFT_INBOX_EMPTY;
	static const string POPUP_GIFT_ERROR_OOP;
	static const string POPUP_GIFT_ERROR_MESSAGE;
	static const string POPUP_GIFT_SELECT;
	static const string POPUP_GIFT_SUCCESS;
	static const string POPUP_GIFT_SEND_FREE_GIFT_SUCCESS;
	static const string POPUP_GIFT_INVITE_SUCCESS;
	static const string POPUP_GIFT_INFO;
	static const string POPUP_GIFT_WARNING;
	static const string POPUP_GIFT_WARNING_MESSAGE;
	static const string POPUP_GIFT_ACCEPT_SUCCESS;
	static const string POPUP_GIFT_ANONYMOUS;
	static const string POPUP_EDIT_NAME;
	static const string POPUP_REFERENCE;
	static const string POPUP_CHANGE_LANGUAGE;
	static const string POPUP_INVITE_DESCRIPTION;
	static const string POPUP_INVITE_TAB_FRIENDTOSENDGIFT;
	static const string POPUP_INVITE_TAB_ALLFRIENDS;
	static const string POPUP_INVITE_FRIENDSSELECTED;
	static const string POPUP_INVITE_BTN_UNSELECTALL;
	static const string POPUP_INVITE_BTN_SELECTALL;
	static const string POPUP_INVITE_BTN_SENDGIFT;
	static const string POPUP_INVITE_BTN_INVITE;
	static const string POPUP_INVITE_ERROR_NON_SELECT;
	static const string POPUP_INVITE_TAB_GAMEFRIEND;
	static const string POPUP_ASKFRIEND_DESCRIPTION;
	static const string POPUP_ASKFRIEND_BTN_LABEL;
	static const string POPUP_SENDGIFT_DESCRIPTION;
	static const string POPUP_SHOP_BTN_BUYNOW;
	static const string POPUP_STARDOM_LEVEL;
	static const string POPUP_STARDOM_BANKROLL;
	static const string POPUP_STARDOM_BIGGESTWIN;
	static const string POPUP_STARDOM_JACKPOT;
	static const string POPUP_STARDOM_LABEL_PLAYER;
	static const string POPUP_STARDOM_PLAYER_ALLPLAYERS;
	static const string POPUP_STARDOM_PLAYER_FRIENDS;
	static const string POPUP_STARDOM_PLAYER_BANKROLL;
	static const string POPUP_STARDOM_PLAYER_NETPROFIT;
	static const string POPUP_STARDOM_PLAYER_BIGGESTWIN;
	static const string POPUP_STARDOM_PLAYER_JACKPOT;
	static const string POPUP_STARDOM_PLAYER_RANKING;
	static const string POPUP_STARDOM_PLAYER_PLAYERS;
	static const string POPUP_STARDOM_PLAYER_COINS;
	static const string POPUP_STARDOM_PLAYER_PLAYTOGETHER;
	static const string POPUP_STARDOM_PLAYER_GAME;
	static const string POPUP_SECRETGIFT_DESCRIPTION;
	static const string POPUP_SMALLBOX_DESCRIPTION;
	static const string POPUP_INBOX_BTN_ACCEPT;
	static const string POPUP_INBOX_BTN_ACCEPT_SENDGIFT;
	static const string POPUP_INBOX_BTN_SENDKEY;
	static const string POPUP_INBOX_BTN_ACCEPT_SENDGIFT_ALL;
	static const string POPUP_INBOX_MESSAGE_GIFT;
	static const string POPUP_INBOX_MESSAGE_FREE_MAGIC_ITEM_WATCHING_VIDEO;
	static const string POPUP_INBOX_MESSAGE_DEFAULT_GIFT;
	static const string POPUP_INBOX_MESSAGE_FREEGIFT;
	static const string POPUP_INBOX_MESSAGE_SYSTEMGIFT;
	static const string POPUP_INBOX_MESSAGE_REQUESTKEY;
	static const string POPUP_INBOX_MESSAGE_PROMOTE;
	static const string POPUP_INBOX_MESSAGE_VIP;
	static const string POPUP_INBOX_FRIEND_BENEFIT;
	static const string POPUP_INBOX_REFERENCE_CODE;
	static const string POPUP_INBOX_TOP_PLAYER_GIFT;
	static const string POPUP_INBOX_MESSAGE_VIP_UP;
	static const string POPUP_SHOP_VIP;
	static const string POPUP_SHOP_STANDARD;
	static const string POPUP_SHOP_MOBILE;
	static const string MENU_SETTING_LABEL;
	static const string MENU_SETTING_GRAPHICQUALITY;
	static const string MENU_SETTING_MUSIC;
	static const string MENU_SETTING_SOUND;
	static const string MENU_SETTING_LANGUAGE;
	static const string POPUP_VOUCHER_DESCRIPTION;
	static const string POPUP_WARNING_SWITCH_TO_APP_FB;
	static const string POPUP_WARNING_SWITCH_TO_APP_FB_TO_INVITE;
	static const string POPUP_WARNING_SWITCH_TO_APP_FB_TO_SEND_GIFT;
	static const string POPUP_WARNING_SWITCH_TO_APP_FB_TO_SHARE;
	static const string SHARE_FACEBOOK_LEVELUP;
	static const string SHARE_FACEBOOK_GAME_UNLOCK;
	static const string POPUP_USER_LEVEL_UP;
	static const string POPUP_USER_GAME_UNLOCK;
	static const string FOOTER_COLLECT_COIN;
	static const string FOOTER_TIME_BONUS;
	static const string MAIN_MENU_NOT_SUPPORT_REGION;
	static const string BODY_SLOT_GAME_COMING_SOON;
	static const string POPUP_INBOX_BUTTON_ACCEPT_ALL;
	static const string OK;
	static const string PAY;
	static const string COPY;
	static const string ADD;
	static const string LOGINFACEBOOK;
	static const string COLLECT;
	static const string COLLECTANDSHARE;
	static const string CANCEL;
	static const string BUY;
	static const string BUYNOW;
	static const string GOTOLOBBY;
	static const string SEND;
	static const string VOUCHER_HAS_EXPIRED;
	static const string VOUCHER_HAS_ALREADY_BEEN_REDEEMED;
	static const string YOU_HAVE_UNLOCKED_A_NEW_GAME;
	static const string CROWN_PURCHASE_SUCCESSFULLY;
	static const string COIN_PURCHASE_SUCCESSFULLY;
	static const string NEW_GAME_TILE;
	static const string NEW_GAME_DESCRIPTION;
	static const string CANT_GET_IMAGE;
	static const string DOWNLOAD_REMOVE;
	static const string EXIT_GAME;
	static const string NOT_ENOUGH_SPACE;
	static const string LOGIN_SOME_WHERE;
	static const string CANT_GET_DATA_FB;
	static const string FB_TOKEN_EXPIRED;
	static const string PURCHASED;
	static const string FREE_COIN;
};