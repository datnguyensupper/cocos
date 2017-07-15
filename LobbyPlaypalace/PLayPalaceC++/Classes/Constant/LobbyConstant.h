#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: LobbyConstant.h, LobbyConstant.cpp
*/
#include "cocos2d.h"
using namespace std;

/* User status - Vip type*/
enum USER_TYPE_VIP
{
	NORMAL = 0,
	SILVER = 1,
	GOLD = 2,
	PINK_DIAMOND = 3,
	BLUE_SAPPHIRE = 4,
	GREEN_EMERALD = 5
};

enum USER_ROLE {
	FACEBOOK = 0,
	BOT = 1,
	PLAYPALACE = 2,
	GUEST = 3,
	PAID_USERS = 5,
	FARMER_USERS = 6,
};

class LobbyConstant
{
public:

	static const int AVATAR_SIZE;

	static const int BONUS_DAILY;
	static const int BONUS_DAILY_FROM_FRIEND;
	static const int BONUS_DAILY_FROM_ACTIVE_FRIEND;
	static const int BONUS_HOURLY_FROM_SERVER;
	static const int BONUS_CONSECUTIVE_LOGIN;

	enum GiftType {
		GIFT_FROM_USER = 0,
		GIFT_FREE_FROM_USER = 1,
		GIFT_FROM_SYSTEM = 2,
		GIFT_SECRET_KEY_FROM_USER = 3,
		GIFT_FOR_PROMOTION_001 = 4,
		GIFT_FOR_PROMOTION_002 = 5,
		GIFT_FOR_PROMOTION_003 = 6,
		GIFT_FOR_PROMOTION_VIP_UP = 7,//
		GIFT_FROM_REFERENCE_CODE = 8,
		GIFT_FROM_BONUS_FOR_TOP_PLAYER = 9,
		GIFT_FROM_PLAY_WITH_FRIEND_WITH_BENEFIT = 10,
		GIFT_TYPE_LUCKY_BOX_1 = 11, //SILVER_CHEST
		GIFT_TYPE_LUCKY_BOX_2 = 12, //GOLD_CHEST
		GIFT_TYPE_LUCKY_BOX_3 = 13, //RED_CHEST
		GIFT_TYPE_FREE_MAGIC_ITEM_WATCHING_VIDEO = 14 //RED_CHEST
	};

	enum LuckyBoxType {
		LUCKY_BOX_SILVER_CHEST = 11,
		LUCKY_BOX_GOLD_CHEST = 12,
		LUCKY_BOX_RED_CHEST = 13
	};
	static const string LUCKY_BOX_NAME_SILVER;
	static const string LUCKY_BOX_NAME_GOLD;
	static const string LUCKY_BOX_NAME_RED;

	enum MagicItemType {
		MAGIC_ITEM_TYPE_DEFAULT = 0,
		MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN = 1,
		MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1 = 2,
		MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2 = 3,
		MAGIC_ITEM_TYPE_DOUBLE_EXP = 4,
		MAGIC_ITEM_TYPE_LUCKY_SYMBOL = 5,
		MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN = 6
	};

	enum DailyChallengeTypeID {
		LEVEL_UP = 1,
		RECEIVE_GIFT = 2,
		SEND_GIFT = 3,
		COLLECT_FREE_COIN_GIFT = 4,
		SPIN = 5,
		MAX_BET = 6,
		BIG_WIN = 7,
		MEGA_WIN = 8,
		TOTAL_BET = 9,
		TOTAL_WIN = 10
	};

	enum ProductType {
		MAGIC_ITEM_100_PERCENT_WIN = 121,
		MAGIC_ITEM_LUCKY_SPIN_10_PERCENT = 122,
		MAGIC_ITEM_LUCKY_SPIN_20_PERCENT = 123,
		MAGIC_ITEM_DOUBLE_EXP = 124,
		MAGIC_ITEM_LUCKY_SYMBOL = 125,
		MAGIC_ITEM_100_PERCENT_BIG_WIN = 126
	};

	///* ------------------------------------------------- Magic Item ------------------------------------------------- */
	//public static final int MAGIC_ITEM_TYPE_DEFAULT = 0; // normal spin without magic item
	//public static final int MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN = 1;
	//public static final int MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1 = 2;
	//public static final int MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2 = 3;
	//public static final int MAGIC_ITEM_TYPE_DOUBLE_EXP = 4;
	//public static final int MAGIC_ITEM_TYPE_LUCKY_SYMBOL = 5;
	//public static final int MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN = 6;
	///* ------------------------------------------------- Magic Item ------------------------------------------------- */


	static const int GIFT_NOT_ACCEPTED;
	static const int GIFT_ACCEPTED;

	static const int GIFT_LIST_ALL;
	static const int GIFT_LIST_ACCEPTED;
	static const int GIFT_LIST_NOT_ACCEPTED;

	static const int MESSAGE_TYPE_TECHNICAL;
	static const int MESSAGE_TYPE_LANGUAGE;
	static const int MESSAGE_TYPE_CONNECTION;
	static const int MESSAGE_TYPE_BUG;

	static const int DEFAULT_EXP_BAR;
	static const long DEFAULT_EXP;
	static const long DEFAULT_RANK;
	static const long DEFAULT_LEVEL;
	static const double DEFAULT_COINS;

	static const long BONUS_DEFAULT_COINS;
	static const long BONUS_DEFAULT_EXP;
	static const int BONUS_DEFAULT_MULTI;

	static const int DEFAULT_ROLE;
	static const long SYSTEM_UID;

	static const string AUTHENTICATION_FAIL;

	static const string SORT_ID;
	static const string SORT_USER_ID;
	static const string SORT_TIMESTAMP_LAST_MODIFIED;
	static const string SORT_TIMESTAMP_LAST_LOGIN;
	static const string SORT_LEVEL_ID;

	static const string LOBBY_ADMIN_CREDIT_USER;
	static const string LOBBY_ADMIN_DEBIT_USER;


	static const string DEFAULT_CURRENCY;

	static const string DEFAULT_STATISTIC_PAGE;
	static const string DEFAULT_STATISTIC_PAGE_SIZE;
	static const int DEFAULT_PAGE_SIZE;

	static const string STARDOM_SORT_BY_FRIEND;
	static const string STARDOM_SORT_BY_ALL;
	static const string STARDOM_BANK_ROLL;
	static const string STARDOM_SLOT_TOTAL_BET;
	static const string STARDOM_BIGGEST_WIN;
	static const string STARDOM_NET_PROFIT;
	static const string STARDOM_JACKPOT;

	static const string PROPERTY_COIN;
	static const string PROPERTY_BIGGEST_WIN;
	static const string PROPERTY_NUMBER_OF_JACKPOT;
	static const string PROPERTY_WIN;
	static const string PROPERTY_NET_PROFIT;

	static const string PROPERTY_EXP;
	static const string PROPERTY_USER_LEVEL;
	static const string PROPERTY_USER_RANK;
	static const string PROPERTY_USER_TYPE;
	static const string PROPERTY_LOGIN_COUNT;
	static const string PROPERTY_TOTAL_SPIN;

	static const int ALLOW_ENABLE;
	static const int ALLOW_DISABLE;

	static const string RELOAD_SERVER_NOTIFICATION_INTERVAL;

	/* Admin role */
	static const long SUPER_ADMIN_ROLE;
	static const long GAME_ADMIN_ROLE;
	static const long SERVER_ADMIN_ROLE;
	static const long STATISTIC_ADMIN_ROLE;
	static const long FINANCE_MANAGER_ROLE;
	static const long MARKETER_ROLE;

	static const string IS_MOBILE;

	/* Real time notification */
	static const int REAL_TIME_NOTIFICATION_STATUS_ENABLE;
	static const int REAL_TIME_NOTIFICATION_STATUS_DISABLE;

	static const string REAL_TIME_NOTIFICATION_STRING_TYPE_WIN_JACKPOT;
	static const string REAL_TIME_NOTIFICATION_STRING_TYPE_WIN_BLACKJACK;

	static const int REAL_TIME_NOTIFICATION_TYPE_BOT_USER;
	static const int REAL_TIME_NOTIFICATION_TYPE_UNKNOWN;
	static const int REAL_TIME_NOTIFICATION_TYPE_WIN_JACKPOT;
	static const int REAL_TIME_NOTIFICATION_TYPE_WIN_BLACKJACK;
	static const int REAL_TIME_NOTIFICATION_TYPE_VIP;

	static const string BOT_USER_BIRTHDAY;

	/* User status */
	static const int USER_STATUS_ENABLE;
	static const int USER_STATUS_DISABLE;

	/* Vip benefit */
	static const int VIP_BENEFIT_TYPE_VIP_SHOP;
	static const int VIP_BENEFIT_TYPE_BONUS_COIN_PER_DAY;
	static const int VIP_BENEFIT_TYPE_BONUS_INVITATION_GIFT_PER_FRIEND;
	static const int VIP_BENEFIT_TYPE_VIP_BADGE_ON_PROFILE;
	static const int VIP_BENEFIT_TYPE_DAILY_SECRET_KEY_GIFT_KEY;
	static const int VIP_BENEFIT_TYPE_DAILY_SECRET_KEY_GIFT_BOX;
	static const int VIP_BENEFIT_TYPE_HOURLY_TIMER_BONUS_REDUCTION;
	static const int VIP_BENEFIT_TYPE_FAN_PAGE_REWARD;
	static const int VIP_BENEFIT_TYPE_XP_BOOSTER;
	static const int VIP_BENEFIT_TYPE_ACCUMULATED_TOTAL_PRICE;
	static const int VIP_BENEFIT_TYPE_INSTANT_BONUS_COIN;

	/* Vip Pre-requisite */
	static const double PREREQUISITE_USER_TYPE_VIP_1;
	static const double PREREQUISITE_USER_TYPE_VIP_2;
	static const double PREREQUISITE_USER_TYPE_VIP_3;
	static const double PREREQUISITE_USER_TYPE_VIP_4;
	static const double PREREQUISITE_USER_TYPE_VIP_5;

	/* Game type from game server */
	static const string GAME_TYPE_SLOT;
	static const string GAME_TYPE_BLACKJACK_SINGLE;
	static const string GAME_TYPE_JACK_OR_BETTER;

	/* Property count for favorite game */
	static const string PROPERTY_COUNT;
	static const string CHANGE_TYPE_GAMBLE;
	static const string CHANGE_TYPE_RESULT;

	/* Secret gift */
	static const int REQUEST_NOT_ACCEPTED;
	static const int REQUEST_ACCEPTED;

	/* Product link for key*/
	//    static const string CACHE_PRODUCT_LINK_FOR_VIP;
	//            "https://fb.playpalace.com/callback-server-for-facebook/vip.html";
	//    static const string CACHE_PRODUCT_LINK_FOR_KEY1;
	//            "https://fb.playpalace.com/callback-server-for-facebook/3keys.html";
	//    static const string CACHE_PRODUCT_LINK_FOR_KEY2;
	//            "https://fb.playpalace.com/callback-server-for-facebook/18keys.html";
	//    static const string CACHE_PRODUCT_LINK_FOR_KEY3;
	//            "https://fb.playpalace.com/callback-server-for-facebook/45keys.html";
	//    static const string CACHE_PRODUCT_LINK_FOR_KEY4;
	//            "https://fb.playpalace.com/callback-server-for-facebook/120keys.html";

	/*  */

	static const long MILLISECONDS_IN_15_MINS;
	static const long MILLISECONDS_IN_ONE_DAY;
	static const long MILLISECONDS_IN_ONE_WEEK;
	static const long MILLISECONDS_IN_ONE_MONTH;
	static const long MILLISECONDS_IN_ONE_YEAR;

	/* Slot game info */
	static const string PROPERTY_ORDER_ID;
	static const string PROPERTY_MIN_LEVEL;
	static const string PROPERTY_MIN_CROWN;

	static const string CLIENT_QUERY_SLOT_GAME_LIST_TYPE_ALL_WITH_LEVEL_CHECK;
	static const string CLIENT_QUERY_SLOT_GAME_LIST_TYPE_PROMOTE_WITHOUT_LEVEL_CHECK;
	static const int SLOT_GAME_INFO_IS_PROMOTE;
	static const int SLOT_GAME_INFO_IS_NOT_PROMOTE;

	/* Game name */
	static const string GAME_NAME_BLACKJACK_SINGLE;
	static const string GAME_NAME_JACK_OR_BETTER;

	/* Stardom game name filter */
	static const string STARDOM_GAME_NAME_SLOT;
	static const string STARDOM_GAME_NAME_BLACKJACK_SINGLE;

	/* Product */
	static const string PRODUCT_TYPE_SHOP;

	/* Promotion */
	static const long PROMOTION_ID_001;
	static const long PROMOTION_ID_002;
	static const long PROMOTION_ID_003;

	static const string MAX_USER_TO_GET_REWARD;
	static const string COIN_REWARD;
	static const string MIN_USER_TO_GET_REWARD;
	static const string DEADLINE_TIMESTAMP;
	static const string VIP_TYPE_REWARD;
	static const string PROMOTION_003_NUMBER_OF_DAY;
	static const string PROMOTION_003_COIN_REWARD_PER_DAY;

	static const int TEST_CREATE_USER;
	static const int TEST_SORT_RANK;
	static const int TEST_RELOAD_BALANCE;
	static const int TEST_USER_INFO_ID;
	static const int TEST_USER_INFO_UID;
	static const int TEST_USER_FRIEND_LIST;

	static const int TEST_BLOCK_RELOAD_BALANCE;
	static const long SUPER_BIG_TIMESTAMP;

	/* Config for user */
	static const string OPERATOR_CODE;

	static const string OPEN_SLOT_MENU_AFTER_LOADING_MAIN_MENU;

	static const string LINK_GAME_SLOT;
	static const string LINK_GAME_KENO;
	static const string LINK_GAME_TEXAS;

	// 2016-03-03: Phuoc: server_config table
	//    static const string SERVER_CONFIG_NAME_VERSION;
	//    static const string SERVER_CONFIG_NAME_FACEBOOK_TOKEN_FIELD_IN_DB;
	static const string SERVER_CONFIG_NAME_VERSION_ANDROID;
	static const string SERVER_CONFIG_NAME_VERSION_IOS;
	static const string SERVER_CONFIG_NAME_STRING_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP;
	static const string SERVER_CONFIG_NAME_SERVER_MODE;
	static const string SERVER_CONFIG_NAME_SAMPLE_WHEEL_MEGA_WIN_TUTORIAL;
	static const string SERVER_CONFIG_NAME_COIN_REWARD_FOR_ADS_UNITY;
	static const string SERVER_CONFIG_NAME_COIN_REWARD_FOR_ADS_COLONY;
	// 2016-05-04: Dac: add ads facebook
	static const string SERVER_CONFIG_NAME_COIN_REWARD_FOR_TRIAL_PAY_FACEBOOK;
	static const string SERVER_CONFIG_NAME_UNITY_ADS_KEY_FOR_HMAC_MD5_ANDROID;
	static const string SERVER_CONFIG_NAME_UNITY_ADS_KEY_FOR_HMAC_MD5_IOS;
	static const string SERVER_CONFIG_NAME_ADS_COLONY_KEY_FOR_HMAC_MD5_ANDROID;
	static const string SERVER_CONFIG_NAME_ADS_COLONY_KEY_FOR_HMAC_MD5_IOS;
	static const string SERVER_CONFIG_NAME_VERSION_LOADING_IMAGE;
	static const string SERVER_CONFIG_NAME_TRIAL_PAY_CONVERSION_RATE;

	static const string SERVER_CONFIG_NAME_NUMBER_OF_TIMES_CALL_METHOD_UPDATE_FROM_TRANSACTION_HISTORY_MOBILE;

	static const string SERVER_CONFIG_NAME_LAST_ID_QUERY_MOBILE_GAMEPLAY;

	static const string SERVER_CONFIG_NAME_CURRENT_TIMESTAMP_FOR_DEBUGGING_STRATEGY;

	static const string SERVER_CONFIG_NAME_LINK_VERIFY_IOS_RECEIPT;
	static const string SERVER_CONFIG_NAME_GET_MORE_COINS_PACKAGE_COIN_REWARD;
	static const string SERVER_CONFIG_NAME_GET_MORE_COINS_PACKAGE_TIME_TO_SHOW_OFFER;

	static const string SERVER_CONFIG_NAME_TRIAL_PAY_NOTIFICATION_KEY_FOR_VERIFYING_CALLBACK_REQUEST_DATA;

	static const int SERVER_CONFIG_VALUE_MAX_TIME_CHANGE_NAME;
	static const int SERVER_CONFIG_VALUE_DEFAULT_TIME_CHANGE_NAME;

	// 2016-03-03: Phuoc: server mode
	static const int SERVER_MODE_NORMAL;
	static const int SERVER_MODE_TEST;
	static const int SERVER_MODE_MAINTENANCE;


	static const int USER_STATISTIC_LOG_TYPE_REQUEST_REAL_TIME_NOTIFICATION;
	static const int USER_STATISTIC_LOG_TYPE_REQUEST_MY_PROFILE;

	static const int ENABLE;
	static const int DISABLE;

	static const string BOT_AVATAR_LINK_LIST;

	static const string ALLOW_SEND_GIFT;
	static const string ALLOW_SEND_FREE_GIFT;
	static const string ALLOW_SEND_MESSAGE;
	static const string ALLOW_GET_BONUS_COIN_PER_TIME;

	static const string MAX_TIME_LEFT_FOR_BONUS_COIN;
	static const string MAX_BONUS_COIN_PER_TIME;
	static const string MAX_TIME_LEFT_TO_GET_FREE_GIFT;
	static const string MAX_COIN_PER_FREE_GIFT;
	static const string MAX_TIME_LEFT_TO_SEND_GIFT;
	static const string MAX_COIN_PER_GIFT;
	static const string MIN_COIN_PER_GIFT;

	static const string LAST_TIMESTAMP_QUERY;

	static const string RELOAD_REAL_TIME_NOTIFICATION_INTERVAL;

	static const string CONVERT_COIN_RATE;

	/* Enable - Disable mobile */
	static const string MOBILE_ALLOW_SEND_GIFT;
	static const string MOBILE_ALLOW_SEND_FREE_GIFT;
	static const string MOBILE_ALLOW_SEND_MESSAGE;
	static const string MOBILE_ALLOW_GET_BONUS_COIN_PER_TIME;

	/* Amount mobile */
	static const string MOBILE_AMOUNT_MAX_TIME_LEFT_FOR_BONUS_COIN;
	static const string MOBILE_AMOUNT_MAX_BONUS_COIN_PER_TIME;
	static const string MOBILE_AMOUNT_MAX_TIME_LEFT_TO_GET_FREE_GIFT;
	static const string MOBILE_AMOUNT_MAX_COIN_PER_FREE_GIFT;
	static const string MOBILE_AMOUNT_MAX_TIME_LEFT_TO_SEND_GIFT;
	static const string MOBILE_AMOUNT_MAX_COIN_PER_GIFT;
	static const string MOBILE_AMOUNT_MIN_COIN_PER_GIFT;

	/* Daily bonus */
	static const string DAILY_BONUS_FRIEND_BONUS;
	static const string DAILY_BONUS_COIN_PER_LEVEL;
	static const string DAILY_BONUS_TIMESTAMP_IN_ONE_DAY;

	/* Level */
	static const string EXP_CONSTANT_AFTER_REACH_LIMIT;

	static const string MIN_COIN_FOR_SORT;
	static const string MAX_COIN_FOR_SORT;

	/* Friend update frequency */
	static const string FRIEND_UPDATE_FREQUENCY;

	static const string SERVER_MAINTENANCE;
	static const string FORCE_USER_RELOAD;

	static const string CHECK_MULTIPLE_LOGIN;

	static const string MIN_MOBILE_UNITY_ANDROID_VERSION_TO_PLAY;
	static const string LAST_TIMESTAMP_QUERY_MOBILE_GAME_PLAY;


	/* ----------------------------------------- User Transaction Log Type ----------------------------------------- */
	static const int USER_TRANSACTION_LOG_TYPE_UNKNOWN;
	static const int USER_TRANSACTION_LOG_TYPE_ADMIN_CREDIT;
	static const int USER_TRANSACTION_LOG_TYPE_ADMIN_DEBIT;
	static const int USER_TRANSACTION_LOG_TYPE_GET_DAILY_BONUS;
	static const int USER_TRANSACTION_LOG_TYPE_GET_FREE_COIN;
	static const int USER_TRANSACTION_LOG_TYPE_DEBIT_ACCEPT_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_ACCEPT_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_COIN_PACKAGE;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_ACCEPT_FREE_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_USER_SIGN_UP;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_OPEN_SECRET_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_OPEN_THE_SAFE;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_SEND_FREE_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_USER_LOCAL_SIGN_UP;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_LEVEL_UP_REWARD;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_PROMOTION_001_REWARD;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_REDEEM_VOUCHER;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_COMEBACK_BONUS_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_UPPER_VIP_BONUS_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_GAME_PLAY_SPIN;
	static const int USER_TRANSACTION_LOG_TYPE_DEBIT_GAME_PLAY_SPIN;
	static const int USER_TRANSACTION_LOG_TYPE_COLLECTED_ACHIEVEMENT;
	static const int USER_TRANSACTION_LOG_TYPE_REDEEM_TUTORIAL_REWARD;
	static const int USER_TRANSACTION_LOG_TYPE_VIEW_ADS_UNITY_REWARD;
	static const int USER_TRANSACTION_LOG_TYPE_VIEW_ADS_COLONY_REWARD;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_MIGRATE_WALLET_DATA;
	static const int USER_TRANSACTION_LOG_TYPE_DEBIT_MIGRATE_WALLET_DATA;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_FUN_PLAYER;
	static const int USER_TRANSACTION_LOG_TYPE_REDEEM_PRE_TUTORIAL_REWARD;
	// 2016-05-04: Dac:
	static const int USER_TRANSACTION_LOG_TYPE_VIEW_TRIAL_PAY_FACEBOOK_REWARD;
	static const int USER_TRANSACTION_LOG_TYPE_DEBIT_TO_SHOW_POPUP_F2P_AND_P2P;
	// 2016-10-11: Phuoc:
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_DAILY_BONUS_STREAK;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_FREE_COIN_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_REFERENCE_CODE_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_DAILY_BONUS_LUCKY_SPIN;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_LUCKY_WHEEL;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_LUCKY_BOX;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_PIGGY_BANK;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_BONUS_FOR_TOP_PLAYER_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_PLAY_WITH_FRIEND_FOR_BENEFIT_GIFT;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_DAILY_CHALLENGE;
	static const int USER_TRANSACTION_LOG_TYPE_CREDIT_COMEBACK_BONUS;
	/* ----------------------------------------- User Transaction Log Type ----------------------------------------- */

	/* ----------------------------------------------- Admin Log Type ----------------------------------------------- */
	static const int USER_ADMIN_LOG_TYPE_CREDIT_USER;
	static const int USER_ADMIN_LOG_TYPE_DEBIT_USER;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_GAME_CONFIG_STATUS;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_GAME_CONFIG_AMOUNT;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_SERVER_VERSION;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_MERCHANT_INFO;
	static const int USER_ADMIN_LOG_TYPE_ADD_AND_REMOVE_GAME_WITH_LEVEL_REQUIREMENT;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_SLOT_GAME_INFO;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_LEVEL_REQUIREMENT_CONFIG;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_VIP_CONFIG;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_USER_SECRET_GIFT;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_PASSWORD_USER_ADMIN;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_BOT_USER_INFO;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_USER_INFO;
	static const int USER_ADMIN_LOG_TYPE_CREATE_LEVEL;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_SERVER_CONFIG;
	static const int USER_ADMIN_LOG_TYPE_CONVERT_FACEBOOK_ACCOUNT_TO_GUEST_ACCOUNT;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_ACHIEVEMENT;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_STRATEGY_CONFIG;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_DAILY_CHALLENGE_CONFIG;
	static const int USER_ADMIN_LOG_TYPE_UPDATE_COMEBACK_BONUS_MOBILE_CONFIG;
	/* ----------------------------------------------- Admin Log Type ----------------------------------------------- */

	static const string USER_ADMIN_LOG_KEY_NAME_CREDIT_USER;
	static const string USER_ADMIN_LOG_KEY_NAME_DEBIT_USER;
	static const string USER_ADMIN_LOG_KEY_NAME_UPDATE_SERVER_VERSION;
	static const string USER_ADMIN_LOG_KEY_NAME_UPDATE_MERCHANT_INFO;
	static const string USER_ADMIN_LOG_KEY_NAME_ADD_AND_REMOVE_GAME_WITH_LEVEL_REQUIREMENT;
	//    static const string USER_ADMIN_LOG_KEY_NAME_UPDATE_MERCHANT_INFO;
	//    static const string USER_ADMIN_LOG_KEY_NAME_UPDATE_MERCHANT_INFO;
	static const string USER_ADMIN_LOG_KEY_UPDATE_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP;

	static const int ALLOW_REQUEST_KEY_FOR_SECRET_GIFT;

	static const long CACHE_MOBILE_MAX_TIME_TO_REQUEST_SECRET_KEY;

	static const long CACHE_MAX_TIME_TO_REQUEST_SECRET_KEY;

	static const long VALIDATE_TIME;

	static const long NUMBER_OF_HOUR_BEFORE_CALCULATE_GAME_ACCESS_PROCESSED_LOG;

	static const long CACHE_MIN_KEY_TO_OPEN_BOX;

	static const long MILLISECONDS_IN_ONE_HOUR;
	static const long MILLISECONDS_IN_ONE_MINUTE;
	static const long GET_CCU_TIMESTAMP_END_GAP;


	/*TYPE LOG CONSTANT  */
	static const int GET_DAILY_BONUS_LOG;
	static const int OPEN_SECRET_BOX_LOG;
	static const int OPEN_THE_SAFE_LOG;

	static const int DAILY_BONUS_SECRET_GIFT_PAGE_SIZE;
	static const int DAILY_BONUS_SORT_TYPE_USER_ID;
	static const int DAILY_BONUS_SORT_TYPE_COIN;

	static const int DAILY_BONUS_LOG_TYPE;
	static const int BOX_AND_SAFE_LOG_TYPE;

	static const int USER_PURCHASE_STATISTIC_PAGE_SIZE;
	/* Voucher */
	static const int PAGE_SIZE_VOUCHER_LIST;
	static const int PAGE_SIZE_MAINTENANCE_SCHEDULE_LIST;
	static const int VOUCHER_EXPIRED_HOUR;

	//    static const long TIMESTAMP_LAUNCH_DAY;

	/* Schedule status */
	//    static const string SCHEDULE_CALCULATE_RETURNING_USER;

	static const string SCHEDULE_CHECK_SCHEDULER_STATUS;

	static const string SCHEDULE_CALCULATE_AVG_PLAY_TIME;

	static const string SCHEDULE_GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY;
	static const string SCHEDULE_GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY;
	//    static const string SCHEDULE_GET_GAME_PLAY_HISTORY_START;
	//    static const string SCHEDULE_GET_GAME_PLAY_HISTORY_END;

	static const string SCHEDULE_UPDATE_USER_STARDOM_STATISTIC;
	//    static const string SCHEDULE_UPDATE_USER_STARDOM_STATISTIC_START;
	//    static const string SCHEDULE_UPDATE_USER_STARDOM_STATISTIC_END;

	static const string SCHEDULE_CALCULATE_GAME_ACCESS_PROCESSED_LOG;
	//    static const string SCHEDULE_CALCULATE_AVG_PLAY_TIME_START;
	//    static const string SCHEDULE_CALCULATE_AVG_PLAY_TIME_END;

	static const string SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES;
	//    static const string SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES_START;
	//    static const string SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES_END;

	static const string SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES;
	//    static const string SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES_START;
	//    static const string SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES_END;

	static const string SCHEDULE_UPDATE_RANKING;
	//    static const string SCHEDULE_UPDATE_RANKING_START;
	//    static const string SCHEDULE_UPDATE_RANKING_END;

	static const string SCHEDULE_DELETE_EXPIRED_USER;
	//    static const string SCHEDULE_DELETE_EXPIRED_USER_START;
	//    static const string SCHEDULE_DELETE_EXPIRED_USER_END;

	static const string SCHEDULE_CHECK_USER_REJECT_APP_FB;
	//    static const string SCHEDULE_CHECK_USER_REJECT_APP_FB_START;
	//    static const string SCHEDULE_CHECK_USER_REJECT_APP_FB_END;

	static const string SCHEDULE_RESET_DAILY_CHALLENGE_SCHEDULER;
	static const string SCHEDULE_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER;

	static const string SCHEDULE_CHECK_SCHEDULES_OVER_15_MINUTES;
	static const long TIME_RUNNING_FOR_SCHEDULE;
	/* User access token hashmap */
	//    static const string USER_ACCESS_TOKEN_HASHMAP;
	static const string USER_ACCESS_TOKEN;
	static const int USER_ACCESS_TOKEN_HASHMAP_EXPIRED_TIME_IN_MEMCACHED;

	/* User statistic log */
	static const int PAGE_SIZE_USER_STATISTIC_LOG;

	/* Login service type */
	static const int LOGIN_SERVICE_TYPE_WEB;
	static const int LOGIN_SERVICE_TYPE_FACEBOOK;

	static const int LOGIN_SERVICE_TYPE_IOS;

	/* Domain of facebook image link */
	static const string DOMAIN_FACEBOOK_IMAGE_LINK;

	/* Login count */
	static const int PAGE_SIZE_USER_LOGIN_STATISTIC;

	/* Redirect url after validation */
	static const string VALIDATION_REDIRECT_URL_SESSION_ATTRIBUTE;

	/* Credit/Debit type */
	static const int CREDIT_DEBIT_TYPE_UNKNOWN;
	static const int CREDIT_DEBIT_TYPE_CREDIT;
	static const int CREDIT_DEBIT_TYPE_DEBIT;

	/* Accept gift list type user gift/secret gift */
	static const int ACCEPT_GIFT_LIST_TYPE_USER_GIFT;
	static const int ACCEPT_GIFT_LIST_TYPE_SECRET_GIFT;

	/* Web background */
	static const int WEB_BACKGROUND_RED;
	static const int WEB_BACKGROUND_BLACK;

	/* Payment service */

	static const int PAYMENT_FROM_FACEBOOK;
	static const int PAYMENT_FROM_APPLE;
	static const int PAYMENT_FROM_ANDROID;

	/* Launch day */
	static const long TIMESTAMP_LAUNCH_DAY;

	/* Payment source id */
	static const int PAYMENT_SOURCE_ID_TYPE_FACEBOOK;
	static const int PAYMENT_SOURCE_ID_TYPE_APPLE;

	/* -------------------------------------------------- Payment -------------------------------------------------- */
	static const string DEFAULT_FACEBOOK_CURRENCY;
	/* Facebook product type */
	// 2016-08-26: Phuoc: dùng cho trường hợp dispute/refund/chargeback/...
	static const int FACEBOOK_PRODUCT_TYPE_INVALID;

	static const int FACEBOOK_OLD_PRODUCT_TYPE_COIN;
	static const int FACEBOOK_OLD_PRODUCT_TYPE_KEY;
	static const int FACEBOOK_OLD_PRODUCT_TYPE_STARTER;
	static const int FACEBOOK_OLD_PRODUCT_TYPE_30_DAYS_COIN;
	static const int FACEBOOK_OLD_PRODUCT_TYPE_DYNAMIC_PRODUCT_F2P;
	static const int FACEBOOK_OLD_PRODUCT_TYPE_DYNAMIC_PRODUCT_P2P;
	static const int FACEBOOK_OLD_PRODUCT_TYPE_CROWN;


	static const int FACEBOOK_PRODUCT_TYPE_UNKNOWN;
	static const int FACEBOOK_PRODUCT_TYPE_COIN_1;
	static const int FACEBOOK_PRODUCT_TYPE_COIN_2;
	static const int FACEBOOK_PRODUCT_TYPE_COIN_3;
	static const int FACEBOOK_PRODUCT_TYPE_COIN_4;
	static const int FACEBOOK_PRODUCT_TYPE_COIN_5;
	static const int FACEBOOK_PRODUCT_TYPE_COIN_6;
	static const int FACEBOOK_PRODUCT_TYPE_COIN_7;

	static const int FACEBOOK_PRODUCT_TYPE_KEY_1;
	static const int FACEBOOK_PRODUCT_TYPE_KEY_2;
	static const int FACEBOOK_PRODUCT_TYPE_KEY_3;
	static const int FACEBOOK_PRODUCT_TYPE_KEY_4;
	static const int FACEBOOK_PRODUCT_TYPE_VIP;
	static const int FACEBOOK_PRODUCT_TYPE_STARTER_PACK;
	static const int FACEBOOK_PRODUCT_TYPE_GET_MORE_COINS_PACK;
	static const int FACEBOOK_PRODUCT_TYPE_30_DAYS_COIN_PACK;

	static const int FACEBOOK_PRODUCT_TYPE_FREE_TO_PLAY_1;
	static const int FACEBOOK_PRODUCT_TYPE_FREE_TO_PLAY_2;
	static const int FACEBOOK_PRODUCT_TYPE_PAY_TO_PLAY_1;
	static const int FACEBOOK_PRODUCT_TYPE_PAY_TO_PLAY_2;
	static const int FACEBOOK_PRODUCT_TYPE_PAY_TO_PLAY_3;

	static const int FACEBOOK_PRODUCT_TYPE_CROWN_1;
	static const int FACEBOOK_PRODUCT_TYPE_CROWN_2;
	static const int FACEBOOK_PRODUCT_TYPE_CROWN_3;


	/* Facebook payment result */
	static const int FACEBOOK_PAYMENT_RESULT_FAIL_FROM_MIGRATE;
	static const int FACEBOOK_PAYMENT_RESULT_UNKNOWN;
	static const int FACEBOOK_PAYMENT_RESULT_CHARGE_COMPLETED;
	static const int FACEBOOK_PAYMENT_RESULT_CHARGE_FAILED;
	static const int FACEBOOK_PAYMENT_RESULT_DISPUTE;
	static const int FACEBOOK_PAYMENT_RESULT_REFUND;
	static const int FACEBOOK_PAYMENT_RESULT_ERROR_INVALID_PRODUCT_ID;
	static const int FACEBOOK_PAYMENT_RESULT_INVALID_PRODUCT_TYPE;
	static const int FACEBOOK_PAYMENT_RESULT_INVALID_PAYMENT_DATA;
	static const int FACEBOOK_PAYMENT_RESULT_UNSUPPORTED_PRODUCT;
	static const int FACEBOOK_PAYMENT_RESULT_PROXY_ERROR;

	/* Facebook callback json changed field */
	static const string FACEBOOK_CALLBACK_JSON_CHANGED_FIELD_ACTIONS;
	static const string FACEBOOK_CALLBACK_JSON_CHANGED_FIELD_DISPUTES;

	static const string FACEBOOK_PAYMENT_DETAIL_ACTION_TYPE_CHARGE;
	static const string FACEBOOK_PAYMENT_DETAIL_ACTION_STATUS_COMPLETED;

	/* Facebook payment test */
	static const int FACEBOOK_PAYMENT_IS_NOT_TEST;
	static const int FACEBOOK_PAYMENT_IS_TEST;

	/* Apple package type */
	static const int APPLE_PRODUCT_TYPE_UNKNOWN;

	static const int APPLE_PRODUCT_TYPE_COIN_1;
	static const int APPLE_PRODUCT_TYPE_COIN_2;
	static const int APPLE_PRODUCT_TYPE_COIN_3;
	static const int APPLE_PRODUCT_TYPE_COIN_4;
	static const int APPLE_PRODUCT_TYPE_COIN_5;
	static const int APPLE_PRODUCT_TYPE_COIN_6;
	static const int APPLE_PRODUCT_TYPE_COIN_7;

	static const int APPLE_PRODUCT_TYPE_CROWN_1;
	static const int APPLE_PRODUCT_TYPE_CROWN_2;
	static const int APPLE_PRODUCT_TYPE_CROWN_3;
	static const int APPLE_PRODUCT_TYPE_MOBILE_SPECIAL_OFFER;
	static const int APPLE_PRODUCT_TYPE_BOOSTER_1;
	static const int APPLE_PRODUCT_TYPE_BOOSTER_2;
	static const int APPLE_PRODUCT_TYPE_LUCKY_WHEEL_1;
	static const int APPLE_PRODUCT_TYPE_LUCKY_WHEEL_2;
	static const int APPLE_PRODUCT_TYPE_LUCKY_WHEEL_3;
	static const int APPLE_PRODUCT_TYPE_PIGGY_BANK_1;
	static const int APPLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_WIN;
	static const int APPLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_10_PERCENT;
	static const int APPLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_20_PERCENT;
	static const int APPLE_PRODUCT_TYPE_MAGIC_ITEM_DOUBLE_EXP;
	static const int APPLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SYMBOL;
	static const int APPLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_BIG_WIN;
	static const int APPLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_1;
	static const int APPLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_2;
	static const int APPLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_3;

	/* Apple payment type */
	static const int APPLE_PAYMENT_RESULT_UNKNOWN;
	static const int APPLE_PAYMENT_RESULT_CHARGE;
	static const int APPLE_PAYMENT_RESULT_ERROR_VERIFY_GOOGLE_RECEIPT_FAIL;
	static const int APPLE_PAYMENT_RESULT_ERROR_INVALID_APP_ID;
	static const int APPLE_PAYMENT_RESULT_ERROR_CODE_FROM_APPLE_SERVER;
	static const int APPLE_PAYMENT_RESULT_ERROR_PAYMENT_EXIST;
	static const int APPLE_PAYMENT_RESULT_ERROR_INVALID_PRODUCT_ID;
	static const int APPLE_PAYMENT_RESULT_ERROR_CAN_NOT_REWARD_USER;
	static const int APPLE_PAYMENT_RESULT_INVALID_PRODUCT_TYPE;
	static const int APPLE_PAYMENT_RESULT_INVALID_PAYMENT_API_VERSION;
	static const int APPLE_PAYMENT_RESULT_INVALID_PAYMENT_DATA;
	static const int APPLE_PAYMENT_RESULT_UNSUPPORTED_PRODUCT;
	static const int APPLE_PAYMENT_RESULT_PROXY_ERROR;

	/* Google package type */
	static const int GOOGLE_PRODUCT_TYPE_UNKNOWN;

	static const int GOOGLE_PRODUCT_TYPE_COIN_1;
	static const int GOOGLE_PRODUCT_TYPE_COIN_2;
	static const int GOOGLE_PRODUCT_TYPE_COIN_3;
	static const int GOOGLE_PRODUCT_TYPE_COIN_4;
	static const int GOOGLE_PRODUCT_TYPE_COIN_5;
	static const int GOOGLE_PRODUCT_TYPE_COIN_6;
	static const int GOOGLE_PRODUCT_TYPE_COIN_7;

	static const int GOOGLE_PRODUCT_TYPE_CROWN_1;
	static const int GOOGLE_PRODUCT_TYPE_CROWN_2;
	static const int GOOGLE_PRODUCT_TYPE_CROWN_3;
	static const int GOOGLE_PRODUCT_TYPE_MOBILE_SPECIAL_OFFER;
	static const int GOOGLE_PRODUCT_TYPE_BOOSTER_1;
	static const int GOOGLE_PRODUCT_TYPE_BOOSTER_2;
	static const int GOOGLE_PRODUCT_TYPE_LUCKY_WHEEL_1;
	static const int GOOGLE_PRODUCT_TYPE_LUCKY_WHEEL_2;
	static const int GOOGLE_PRODUCT_TYPE_LUCKY_WHEEL_3;
	static const int GOOGLE_PRODUCT_TYPE_PIGGY_BANK_1;
	static const int GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_WIN;
	static const int GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_10_PERCENT;
	static const int GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_20_PERCENT;
	static const int GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_DOUBLE_EXP;
	static const int GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SYMBOL;
	static const int GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_BIG_WIN;
	static const int GOOGLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_1;
	static const int GOOGLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_2;
	static const int GOOGLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_3;

	/* Google payment type */
	static const int GOOGLE_PAYMENT_RESULT_UNKNOWN;
	static const int GOOGLE_PAYMENT_RESULT_CHARGE;
	static const int GOOGLE_PAYMENT_RESULT_ERROR_VERIFY_GOOGLE_RECEIPT_FAIL;
	static const int GOOGLE_PAYMENT_RESULT_ERROR_INVALID_APP_ID;
	static const int GOOGLE_PAYMENT_RESULT_ERROR_CODE_FROM_GOOGLE_SERVER;
	static const int GOOGLE_PAYMENT_RESULT_ERROR_PAYMENT_EXIST;
	static const int GOOGLE_PAYMENT_RESULT_ERROR_INVALID_PRODUCT_ID;
	static const int GOOGLE_PAYMENT_RESULT_ERROR_CAN_NOT_REWARD_USER;
	static const int GOOGLE_PAYMENT_RESULT_INVALID_PRODUCT_TYPE;
	static const int GOOGLE_PAYMENT_RESULT_INVALID_PAYMENT_API_VERSION;
	static const int GOOGLE_PAYMENT_RESULT_INVALID_PAYMENT_DATA;
	static const int GOOGLE_PAYMENT_RESULT_UNSUPPORTED_PRODUCT;
	static const int GOOGLE_PAYMENT_RESULT_PROXY_ERROR;
	/* -------------------------------------------------- Payment -------------------------------------------------- */

	/* Package status */
	static const string PACKAGE_STATUS;

	static const string FB_PURCHASE_STATUS_COMPLETE;
	static const string GGPLAY_PURCHASE_STATUS_COMPLETE;

	/* Payment log type */
	static const int PAYMENT_INVALID;
	static const int PAYMENT_APPROVE;
	static const int PAYMENT_CANCEL;
	static const int PAYMENT_ERROR;
	static const int PAYMENT_REFUND;
	static const int PAYMENT_EXISTED;
	static const int USER_CLICK_PAYMENT;
	static const int APP_STORE_READY;

	/* Admin : filter list user */
	static const int FILTER_BY_NAME;
	static const int FILTER_BY_FB_UID;
	static const int FILTER_BY_LEVEL;
	static const int FILTER_BY_EMAIL;
	static const int FILTER_BY_RANK;
	static const int FILTER_BY_COIN;
	static const int FILTER_BY_ID;
	static const int FILTER_BY_TS_CREATED;
	static const int FILTER_BY_TS_LAST_MODIFIED;
	static const int FILTER_BY_USER_TYPE;
	static const int FILTER_BY_LOGIN_COUNT;

	static const int FILTER_BY_FARMER_AMOUNT_SEND;
	static const int FILTER_BY_FARMER_TOTAL_SEND_TIMES;


	/* Coin reward after level up */
	static const string COIN_REWARD_AFTER_LEVEL_UP;
	static const string CROWN_REWARD_AFTER_LEVEL_UP;

	/* Default locale */
	static const string DEFAULT_LOCALE_PP_LANGUAGE;
	static const string DEFAULT_LOCALE_FB_LANGUAGE;

	static const string DYNAMIC_PACK_STRING;

	// 2015-11-11: Toan
	static const int NOT_LOGIN_IN_A_DAY;
	static const int LOGIN_MORE_THAN_ONCE_IN_A_DAY;
	static const string LOGIN_IN_DAY;
	static const double AMOUNT_BUY_GET_MORE_COIN;

	static const int MIN_RANDOM_ID_FOR_NAME_OF_GUEST_USER;
	static const int MAX_RANDOM_ID_FOR_NAME_OF_GUEST_USER;

	static const int NAMING_STRATEGY_USING_WRAPPER;
	static const int NAMING_STRATEGY_USING_PUBLIC_FOLDER;

	static const string GRAPH_API;

	static const int PLATFORM_WEB;
	static const int PLATFORM_MOBILE;

	// 2016-03-11: Phuoc: dùng trong các API phân biệt android/ios
	static const int PLATFORM_ANDROID;
	static const int PLATFORM_IOS;

	static const int DEFAULT_MEMCACHED_EXPIRED_TIME;

	static const int DEFAULT_ANDROID_VERSION_CODE;

	// 2016-1-13 : Toan
	//static const string MOBILE_GAME_DEEP_BLUE_MOBILE_WITHOUT_PREFIX;
	//static const string MOBILE_GAME_GOLDEN_EGG_MOBILE_WITHOUT_PREFIX;
	//static const string MOBILE_GAME_NEZHA_MOBILE_WITHOUT_PREFIX;
	//static const string MOBILE_GAME_PHARAOH_MOBILE_WITHOUT_PREFIX;
	//static const string MOBILE_GAME_ROMAN_EMPIRE_MOBILE_WITHOUT_PREFIX;
	//static const string MOBILE_GAME_BOXING_MOBILE_WITHOUT_PREFIX;

	//static const string MOBILE_GAME_BOXING_MOBILE_WITH_WRONG_PREFIX;
	//static const string MOBILE_GAME_DEEP_BLUE_MOBILE_WITH_WRONG_PREFIX;
	//static const string MOBILE_GAME_GOLDEN_EGG_MOBILE_WITH_WRONG_PREFIX;
	//static const string MOBILE_GAME_NEZHA_MOBILE_WITH_WRONG_PREFIX;
	//static const string MOBILE_GAME_PHARAOH_MOBILE_WITH_WRONG_PREFIX;
	//static const string MOBILE_GAME_ROMAN_EMPIRE_MOBILE_WITH_WRONG_PREFIX;

	//static const string MOBILE_GAME_BOXING_MOBILE_WITH_RIGHT_PREFIX;
	//static const string MOBILE_GAME_DEEP_BLUE_MOBILE_WITH_RIGHT_PREFIX;
	//static const string MOBILE_GAME_GOLDEN_EGG_MOBILE_WITH_RIGHT_PREFIX;
	//static const string MOBILE_GAME_NEZHA_MOBILE_WITH_RIGHT_PREFIX;
	//static const string MOBILE_GAME_PHARAOH_MOBILE_WITH_RIGHT_PREFIX;
	//static const string MOBILE_GAME_ROMAN_EMPIRE_MOBILE_WITH_RIGHT_PREFIX;


	static const double PRICE_OF_SPECIAL_OFFER_PACKAGE;

	static const int VOUCHER_PLATFORM_WEB;
	static const int VOUCHER_PLATFORM_MOBILE;
	static const string VOUCHER_PICTURE_URL_MOBILE;
	static const string VOUCHER_CAPTION_MOBILE;

	static const int TRANSACTION_HISTORY_SOURCE_TYPE_DESKTOP;
	static const int TRANSACTION_HISTORY_SOURCE_TYPE_MOBILE;

	static const bool ACHIEVEMENT_FLAG_COMPLETE;
	static const bool ACHIEVEMENT_FLAG_NOT_COMPLETE;

	static const bool ACHIEVEMENT_FLAG_COLLECTED;
	static const bool ACHIEVEMENT_FLAG_NOT_COLLECTED;

	static const int ACHIEVEMENT_GROUP_TYPE_GENERAL;
	static const int ACHIEVEMENT_GROUP_TYPE_GAME;
	static const int ACHIEVEMENT_GROUP_TYPE_SOCIAL;

	static const int ACHIEVEMENT_TYPE_COMPLETE_TUTORIAL;
	static const int ACHIEVEMENT_TYPE_CONTINUOUSLY_LOGIN;
	static const int ACHIEVEMENT_TYPE_LEVEL_ACHIEVED;
	static const int ACHIEVEMENT_TYPE_SPIN_ON_SLOT;
	static const int ACHIEVEMENT_TYPE_FIRST_TIME_DEPOSIT;
	static const int ACHIEVEMENT_TYPE_ACHIEVEMENT_MILESTONE;
	static const int ACHIEVEMENT_TYPE_SPIN_COMPLETED_MILESTONE;
	static const int ACHIEVEMENT_TYPE_TOTAL_WIN_MILESTONE;
	static const int ACHIEVEMENT_TYPE_TOTAL_BET_MILESTONE;
	static const int ACHIEVEMENT_TYPE_SEND_INVITE_TO_FRIEND;
	static const int ACHIEVEMENT_TYPE_SEND_GIFT_TO_FRIEND;
	static const int ACHIEVEMENT_TYPE_RECEIVED_GIFT_FROM_FRIEND;
	static const int ACHIEVEMENT_TYPE_LINK_ACCOUNT_TO_FACEBOOK;

	// 2016-02-26: Phuoc:
	static const int ACHIEVEMENT_CATEGORY_ID_PERSONAL_PROGRESSION;
	static const int ACHIEVEMENT_CATEGORY_ID_SPIN_MANIA;
	static const int ACHIEVEMENT_CATEGORY_ID_LOYALIST;
	static const int ACHIEVEMENT_CATEGORY_ID_WINNINGS;
	static const int ACHIEVEMENT_CATEGORY_ID_BETTING_MANIA;
	static const int ACHIEVEMENT_CATEGORY_ID_FRIENDS_WITH_BENEFITS;
	static const int ACHIEVEMENT_CATEGORY_ID_SOCIALLY_CONNECTED;

	static const int ACHIEVEMENT_SUB_CATEGORY_ID_READY_TO_PLAY;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_LOYALTY;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_JOURNEYMAN;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_EXPLORER;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_MASTER;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_SPIN_JUNIOR;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_SPIN_SENIOR;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_LOYAL_SUPPORTER;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_ACHIEVER;

	static const int ACHIEVEMENT_SUB_CATEGORY_ID_NOVICE;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_APPRENTICE;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_JUNIOR_ROLLER;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_MASTER_ROLLER;

	static const int ACHIEVEMENT_SUB_CATEGORY_ID_PARTY_ORGANISER;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_GOOD_SAMARITAN;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_SOCIALITE;
	static const int ACHIEVEMENT_SUB_CATEGORY_ID_LINK_ACCOUNT_TO_FACEBOOK;


	static const int INVALID_RESULT_UPDATE_SQL_COMMAND;

	static const string STRING_CALCULATE_AVG_PLAY_TIME_SCHEDULER;
	static const string STRING_GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY_SCHEDULER;
	static const string STRING_GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY_SCHEDULER;
	static const string STRING_UPDATE_USER_STARDOM_STATISTIC_SCHEDULER;
	static const string STRING_CALCULATE_GAME_ACCESS_PROCESSED_LOG;
	static const string STRING_CALCULATE_CCUS_EVERY_60_MINUTES_SCHEDULER;
	static const string STRING_CALCULATE_CCUS_EVERY_5_MINUTES_SCHEDULER;
	static const string STRING_DELETE_EXPIRED_USER_SCHEDULER;
	static const string STRING_CHECK_USER_REJECT_APP_FB_SCHEDULER;
	static const string STRING_CHECK_RESET_DAILY_CHALLENGE_SCHEDULER;
	static const string STRING_CHECK_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER;


	static const string TIME_TO_SHOW_OFFER;
	static const string COIN_FOR_SHOW_OFFER;

	static const double DEFAULT_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP;

	static const double TUTORIAL_REWARD;
	static const double GET_PRE_TUTORIAL_REWARD;

	// 2016-04-04: Phuoc:
	static const int ADS_ERROR_LOG_TYPE_UNKNOWN;
	static const int ADS_ERROR_LOG_TYPE_IP_INVALID;

	static const string MESSAGE_UNITY_ADS_OK;
	// Toan: chuoi thanh cong nay anh Dat yeu cau phai tra ve la "vc_success"
	static const string MESSAGE_COLONY_ADS_OK;
	static const string MESSAGE_ERROR_IP_INVALID;
	static const string MESSAGE_ERROR_INTERNAL_SERVER_ERROR;
	static const string MESSAGE_ERROR_INVALID_USER_ID;
	static const string MESSAGE_ERROR_FAIL_TO_CHECK_MD5;
	static const string MESSAGE_ERROR_FAIL_TO_SAVE;
	static const string MESSAGE_ERROR_TRANSACTION_ID_EXIST;
	static const string MESSAGE_ERROR_WRONG_PLATFORM;

	// 2016-04-28: Toan
	static const bool DISABLE_ALLOW_GET_PRE_TUTORIAL_REWARD;

	static const bool DISABLE_RESET_PASSWORD_FOR_USER_ADMIN;
	static const bool ENABLE_RESET_PASSWORD_FOR_USER_ADMIN;

	static const int USER_FACEBOOK_EVENT_LOG_TYPE_UNKNOWN;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_LAUNCH_APP;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_CALL_LOGIN_API;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP_SUCCESSFULLY;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP_FAILED;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP_INIT_FAILED;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_LOGIN_FAILED;
	static const int USER_FACEBOOK_EVENT_LOG_TYPE_DEAUTHORIZE_APP;

	static const int DEFAULT_NUMBER_OF_BITS_FOR_GENERATING_SECURE_RANDOM_STRING;

	static const string API_COMBINATION_BEAN_NAME_GET_MY_PROFILE;
	static const string API_COMBINATION_BEAN_NAME_CHECK_COLLECT_COIN;
	static const string API_COMBINATION_BEAN_NAME_GET_SPECIAL_OFFER;
	static const string API_COMBINATION_BEAN_NAME_GET_ALL_CONFIG;
	static const string API_COMBINATION_BEAN_NAME_GET_LINK_GAME;
	static const string API_COMBINATION_BEAN_NAME_GET_LEVEL_CONFIG;
	static const string API_COMBINATION_BEAN_NAME_GET_ALL_LIST_SLOT_GAME_INFO;
	static const string API_COMBINATION_BEAN_NAME_GET_LIST_BET_SIZE_RESTRICTION;

	static const string API_FEATURE_BEAN_TYPE_DAILY_BONUS_STREAK;
	static const string API_FEATURE_BEAN_TYPE_FREE_COIN_GIFT;
	static const string API_FEATURE_BEAN_TYPE_UNLOCK_BY_LEVEL;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_WHEEL;
	static const string API_FEATURE_BEAN_TYPE_DAILY_CHALLENGE;
	static const string API_FEATURE_BEAN_TYPE_BOOSTER;
	static const string API_FEATURE_BEAN_TYPE_MOBILE_SLOT_GAME_CONFIG;
	static const string API_FEATURE_BEAN_TYPE_MOBILE_SLOT_GAME_PAY_LINE_CONFIG;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_CONFIG;
	static const string API_FEATURE_BEAN_TYPE_MAGIC_ITEM_CONFIG;

	static const int PAYMENT_API_VERSION_UNKNOWN;
	static const int PAYMENT_API_VERSION_FACEBOOK;
	static const int PAYMENT_API_VERSION_UNITY;
    static const int PAYMENT_API_VERSION_CORDOVA;
    static const int PAYMENT_API_VERSION_COCOS;

	static const int SPECIAL_OFFER_API_VERSION_UNITY;
	static const int SPECIAL_OFFER_API_VERSION_CORDOVA;

	static const int SCHEDULER_LOG_TYPE_CHECK_SCHEDULER_STATUS_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_CALCULATE_AVG_PLAY_TIME_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_UPDATE_USER_STARDOM_STATISTIC_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_CALCULATE_GAME_ACCESS_PROCESSED_LOG;
	static const int SCHEDULER_LOG_TYPE_CALCULATE_CCUS_EVERY_60_MINUTES_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_CALCULATE_CCUS_EVERY_5_MINUTES_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_DELETE_EXPIRED_USER_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_CHECK_USER_REJECT_APP_FB_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_RESET_DAILY_CHALLENGE_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER;

	static const int SCHEDULER_LOG_TYPE_GET_USER_TRANSACTION_LOG_FROM_PROXY_DATABASE_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_GET_TRANSACTION_HISTORY_FROM_GAME_PLAY_DESKTOP_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_PROCESS_DATA_MERCHANT_STATISTIC_IN_PROXY_DATABASE_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_GET_TRANSACTION_HISTORY_FROM_GAME_PLAY_MOBILE_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_CALCULATE_AND_SEND_EMAIL_STATISTIC_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_CHECK_COMPANY_LOSS_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_RESET_COMPANY_LOSS_EACH_QUARTER_SCHEDULER;
	static const int SCHEDULER_LOG_TYPE_RECALCULATE_MERCHANT_STATISTIC;

	static const int SCHEDULER_LOG_TYPE_SYNC_WALLET_PROXY_AND_THIRD_PARTY;

	static const string TRANSACTION_HISTORY_CHANGE_TYPE_RESULT;
	static const string TRANSACTION_HISTORY_CHANGE_TYPE_FREE_SPIN;
	static const string TRANSACTION_HISTORY_CHANGE_TYPE_BONUS;
	static const string TRANSACTION_HISTORY_CHANGE_TYPE_GAMBLE;

	static const int BONUS_RTP_RATIO_TYPE_COMEBACK_BONUS_MOBILE;

	static const int MOBILE_GAME_PLAY_TRANSACTION_HISTORY_VERSION_DEFAULT;
	static const int MOBILE_GAME_PLAY_TRANSACTION_HISTORY_VERSION_WITH_FEATURE_BONUS_RTP_RATIO;

	static const int SPECIAL_OFFER_TYPE_LIMITED;

	static const int FACEBOOK_ACTIVATE_TRUE;
	static const int FACEBOOK_ACTIVATE_FALSE;

	static const string ALGORITHM_NAME_IN_PAYLOAD_DATA_OF_DEAUTHORIZATION_FACEBOOK_CALLBACK;
	static const string ALGORITHM_FOR_VALIDATE_PAYLOAD_DATA_OF_DEAUTHORIZATION_FACEBOOK_CALLBACK;
	static const string ALGORITHM_FOR_VALIDATE_PAYLOAD_DATA_OF_TRIAL_PAY_CALLBACK;
	static const string ALGORITHM_FOR_VALIDATE_PAYLOAD_DATA_OF_ADS_COLONY;

	static const string TRIAL_PAY_REQUEST_HEADER_FOR_HMAC_MD5;

	static const int ENCODE_METHOD_FOR_VALIDATING_TRIAL_PAY_PAYLOAD;
	static const int ENCODE_METHOD_FOR_VALIDATING_FACEBOOK_SIGNED_REQUEST_PAYLOAD;

	// FEATURE CONFIG
	static const string FREE_COIN_GIFT_COIN_REWARD_PREFIX;
	static const string FREE_COIN_WAITING_TIME_PREFIX;
	static const string API_BONUS_NAME_UFBL_DAILY_CHANLLENGE;
	static const string API_BONUS_NAME_UFBL_PIGGY_BANK;
	static const string API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE;
	static const string API_FEATURE_BEAN_TYPE_BOOSTER_FACTOR_1;
	static const string API_FEATURE_BEAN_TYPE_BOOSTER_FACTOR_2;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_COINS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_CROWNS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_LUCKY_WHEELS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_PRICE;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_COINS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_CROWNS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_LUCKY_WHEELS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_PRICE;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_COINS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_CROWNS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_LUCKY_WHEELS_REWARD;
	static const string API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_PRICE;
	static const string API_FEATURE_BEAN_TYPE_MIN_NUMBER_OF_CONSECUTIVE_VIDEO_VIEW_TO_RECEIVE_MAGIC_ITEM_REWARD;

	//ADDITIONAL INFO
	static const string API_BONUS_BEAN_TYPE_DAILY_BONUS_STREAK;
	static const string API_BONUS_BEAN_TYPE_FREE_COIN_GIFT;
	static const string API_BONUS_BEAN_TYPE_REFERENCE_CODE;
	static const string API_BONUS_BEAN_TYPE_DAILY_BONUS_LUCKY_SPIN;
	static const string API_BONUS_BEAN_TYPE_DAILY_BONUS_WHEEL;
	static const string API_BONUS_BEAN_TYPE_LUCKY_WHEEL;
	static const string API_BONUS_BEAN_TYPE_LUCKY_BOX;
	static const string API_BONUS_BEAN_TYPE_PIGGY_BANK;
	static const string API_BONUS_BEAN_TYPE_BOOSTER;
	static const string API_BONUS_BEAN_TYPE_COMEBACK_BONUS;
	static const string API_BONUS_BEAN_TYPE_MAGIC_ITEM;
};
