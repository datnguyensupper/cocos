#include "LobbyConstant.h"

const int LobbyConstant::AVATAR_SIZE = 255;

const int LobbyConstant::BONUS_DAILY = 0;
const int LobbyConstant::BONUS_DAILY_FROM_FRIEND = 1;
const int LobbyConstant::BONUS_DAILY_FROM_ACTIVE_FRIEND = 2;
const int LobbyConstant::BONUS_HOURLY_FROM_SERVER = 3;
const int LobbyConstant::BONUS_CONSECUTIVE_LOGIN = 4;


const string LobbyConstant::LUCKY_BOX_NAME_SILVER = "COMMONER TREASURE CHEST";
const string LobbyConstant::LUCKY_BOX_NAME_GOLD = "NOBLE TREASURE CHEST";
const string LobbyConstant::LUCKY_BOX_NAME_RED = "KING TREASURE CHEST";

const int LobbyConstant::GIFT_NOT_ACCEPTED = 0;
const int LobbyConstant::GIFT_ACCEPTED = 1;

const int LobbyConstant::GIFT_LIST_ALL = 2;
const int LobbyConstant::GIFT_LIST_ACCEPTED = 1;
const int LobbyConstant::GIFT_LIST_NOT_ACCEPTED = 0;

const int LobbyConstant::MESSAGE_TYPE_TECHNICAL = 0;
const int LobbyConstant::MESSAGE_TYPE_LANGUAGE = 1;
const int LobbyConstant::MESSAGE_TYPE_CONNECTION = 2;
const int LobbyConstant::MESSAGE_TYPE_BUG = 3;

const int LobbyConstant::DEFAULT_EXP_BAR = 0;
const long LobbyConstant::DEFAULT_EXP = 0;
const long LobbyConstant::DEFAULT_RANK = 0;
const long LobbyConstant::DEFAULT_LEVEL = 0;
const double LobbyConstant::DEFAULT_COINS = 0.0;

const long LobbyConstant::BONUS_DEFAULT_COINS = 1000;
const long LobbyConstant::BONUS_DEFAULT_EXP = 1000;
const int LobbyConstant::BONUS_DEFAULT_MULTI = 2;

const int LobbyConstant::DEFAULT_ROLE = 0;
const long LobbyConstant::SYSTEM_UID = -1;

const string LobbyConstant::AUTHENTICATION_FAIL = "Authentication Failed";

const string LobbyConstant::SORT_ID = "id";
const string LobbyConstant::SORT_USER_ID = "userId";
const string LobbyConstant::SORT_TIMESTAMP_LAST_MODIFIED = "timestampLastModified";
const string LobbyConstant::SORT_TIMESTAMP_LAST_LOGIN = "timestampLastLogin";
const string LobbyConstant::SORT_LEVEL_ID = "levelId";

const string LobbyConstant::LOBBY_ADMIN_CREDIT_USER = "Credit";
const string LobbyConstant::LOBBY_ADMIN_DEBIT_USER = "Debit";


const string LobbyConstant::DEFAULT_CURRENCY = "USD";

const string LobbyConstant::DEFAULT_STATISTIC_PAGE = "1";
const string LobbyConstant::DEFAULT_STATISTIC_PAGE_SIZE = "500";
const int LobbyConstant::DEFAULT_PAGE_SIZE = 100;

const string LobbyConstant::STARDOM_SORT_BY_FRIEND = "friends";
const string LobbyConstant::STARDOM_SORT_BY_ALL = "all";
const string LobbyConstant::STARDOM_BANK_ROLL = "bank_roll";
const string LobbyConstant::STARDOM_SLOT_TOTAL_BET = "slot_total_bet";
const string LobbyConstant::STARDOM_BIGGEST_WIN = "biggest_win";
const string LobbyConstant::STARDOM_NET_PROFIT = "net_profit";
const string LobbyConstant::STARDOM_JACKPOT = "jackpot";

const string LobbyConstant::PROPERTY_COIN = "coin";
const string LobbyConstant::PROPERTY_BIGGEST_WIN = "biggestWin";
const string LobbyConstant::PROPERTY_NUMBER_OF_JACKPOT = "numberOfJackpot";
const string LobbyConstant::PROPERTY_WIN = "win";
const string LobbyConstant::PROPERTY_NET_PROFIT = "netProfit";

const string LobbyConstant::PROPERTY_EXP = "exp";
const string LobbyConstant::PROPERTY_USER_LEVEL = "level";
const string LobbyConstant::PROPERTY_USER_RANK = "rank";
const string LobbyConstant::PROPERTY_USER_TYPE = "vip";
const string LobbyConstant::PROPERTY_LOGIN_COUNT = "loginCount";
const string LobbyConstant::PROPERTY_TOTAL_SPIN = "totalSpin";

const int LobbyConstant::ALLOW_ENABLE = 0;
const int LobbyConstant::ALLOW_DISABLE = 1;

const string LobbyConstant::RELOAD_SERVER_NOTIFICATION_INTERVAL = "reload_server_notification_interval";

/* Admin role */
const long LobbyConstant::SUPER_ADMIN_ROLE = 999;
const long LobbyConstant::GAME_ADMIN_ROLE = 1;
const long LobbyConstant::SERVER_ADMIN_ROLE = 2;
const long LobbyConstant::STATISTIC_ADMIN_ROLE = 3;
const long LobbyConstant::FINANCE_MANAGER_ROLE = 4;
const long LobbyConstant::MARKETER_ROLE = 5;

const string LobbyConstant::IS_MOBILE = "isMobile";

/* Real time notification */
const int LobbyConstant::REAL_TIME_NOTIFICATION_STATUS_ENABLE = 1;
const int LobbyConstant::REAL_TIME_NOTIFICATION_STATUS_DISABLE = 0;

const string LobbyConstant::REAL_TIME_NOTIFICATION_STRING_TYPE_WIN_JACKPOT = "win_jackpot";
const string LobbyConstant::REAL_TIME_NOTIFICATION_STRING_TYPE_WIN_BLACKJACK = "win_blackjack";

const int LobbyConstant::REAL_TIME_NOTIFICATION_TYPE_BOT_USER = -1;
const int LobbyConstant::REAL_TIME_NOTIFICATION_TYPE_UNKNOWN = 0;
const int LobbyConstant::REAL_TIME_NOTIFICATION_TYPE_WIN_JACKPOT = 1;
const int LobbyConstant::REAL_TIME_NOTIFICATION_TYPE_WIN_BLACKJACK = 2;
const int LobbyConstant::REAL_TIME_NOTIFICATION_TYPE_VIP = 3;

const string LobbyConstant::BOT_USER_BIRTHDAY = "01/01/1990";

/* User status */
const int LobbyConstant::USER_STATUS_ENABLE = 1;
const int LobbyConstant::USER_STATUS_DISABLE = 0;

/* Vip benefit */
const int LobbyConstant::VIP_BENEFIT_TYPE_VIP_SHOP = 0;
const int LobbyConstant::VIP_BENEFIT_TYPE_BONUS_COIN_PER_DAY = 1;
const int LobbyConstant::VIP_BENEFIT_TYPE_BONUS_INVITATION_GIFT_PER_FRIEND = 2;
const int LobbyConstant::VIP_BENEFIT_TYPE_VIP_BADGE_ON_PROFILE = 3;
const int LobbyConstant::VIP_BENEFIT_TYPE_DAILY_SECRET_KEY_GIFT_KEY = 4;
const int LobbyConstant::VIP_BENEFIT_TYPE_DAILY_SECRET_KEY_GIFT_BOX = 5;
const int LobbyConstant::VIP_BENEFIT_TYPE_HOURLY_TIMER_BONUS_REDUCTION = 6;
const int LobbyConstant::VIP_BENEFIT_TYPE_FAN_PAGE_REWARD = 7;
const int LobbyConstant::VIP_BENEFIT_TYPE_XP_BOOSTER = 8;
const int LobbyConstant::VIP_BENEFIT_TYPE_ACCUMULATED_TOTAL_PRICE = 9;
const int LobbyConstant::VIP_BENEFIT_TYPE_INSTANT_BONUS_COIN = 10;

/* Vip Pre-requisite */
const double LobbyConstant::PREREQUISITE_USER_TYPE_VIP_1 = 10;
const double LobbyConstant::PREREQUISITE_USER_TYPE_VIP_2 = 50;
const double LobbyConstant::PREREQUISITE_USER_TYPE_VIP_3 = 99;
const double LobbyConstant::PREREQUISITE_USER_TYPE_VIP_4 = 149.99;
const double LobbyConstant::PREREQUISITE_USER_TYPE_VIP_5 = 199.99;

/* Game type from game server */
const string LobbyConstant::GAME_TYPE_SLOT = "1";
const string LobbyConstant::GAME_TYPE_BLACKJACK_SINGLE = "5";
const string LobbyConstant::GAME_TYPE_JACK_OR_BETTER = "2";

/* Property count for favorite game */
const string LobbyConstant::PROPERTY_COUNT = "count";
const string LobbyConstant::CHANGE_TYPE_GAMBLE = "Gamble";
const string LobbyConstant::CHANGE_TYPE_RESULT = "Result";

/* Secret gift */
const int LobbyConstant::REQUEST_NOT_ACCEPTED = 0;
const int LobbyConstant::REQUEST_ACCEPTED = 1;

/* Product link for key*/
//    const string LobbyConstant::CACHE_PRODUCT_LINK_FOR_VIP =
//            "https://fb.playpalace.com/callback-server-for-facebook/vip.html";
//    const string LobbyConstant::CACHE_PRODUCT_LINK_FOR_KEY1 =
//            "https://fb.playpalace.com/callback-server-for-facebook/3keys.html";
//    const string LobbyConstant::CACHE_PRODUCT_LINK_FOR_KEY2 =
//            "https://fb.playpalace.com/callback-server-for-facebook/18keys.html";
//    const string LobbyConstant::CACHE_PRODUCT_LINK_FOR_KEY3 =
//            "https://fb.playpalace.com/callback-server-for-facebook/45keys.html";
//    const string LobbyConstant::CACHE_PRODUCT_LINK_FOR_KEY4 =
//            "https://fb.playpalace.com/callback-server-for-facebook/120keys.html";

/*  */

const long LobbyConstant::MILLISECONDS_IN_15_MINS = 15L * 60L * 1000L;
const long LobbyConstant::MILLISECONDS_IN_ONE_DAY = 24L * 3600L * 1000L;
const long LobbyConstant::MILLISECONDS_IN_ONE_WEEK = MILLISECONDS_IN_ONE_DAY * 7;
const long LobbyConstant::MILLISECONDS_IN_ONE_MONTH = 30L * MILLISECONDS_IN_ONE_DAY;
const long LobbyConstant::MILLISECONDS_IN_ONE_YEAR = 365L * MILLISECONDS_IN_ONE_DAY;

/* Slot game info */
const string LobbyConstant::PROPERTY_ORDER_ID = "orderId";
const string LobbyConstant::PROPERTY_MIN_LEVEL = "minLevel";
const string LobbyConstant::PROPERTY_MIN_CROWN = "minCrown";

const string LobbyConstant::CLIENT_QUERY_SLOT_GAME_LIST_TYPE_ALL_WITH_LEVEL_CHECK = "all_with_level_check";
const string LobbyConstant::CLIENT_QUERY_SLOT_GAME_LIST_TYPE_PROMOTE_WITHOUT_LEVEL_CHECK = "promote";
const int LobbyConstant::SLOT_GAME_INFO_IS_PROMOTE = 1;
const int LobbyConstant::SLOT_GAME_INFO_IS_NOT_PROMOTE = 0;

/* Game name */
const string LobbyConstant::GAME_NAME_BLACKJACK_SINGLE = "Black Jack Single";
const string LobbyConstant::GAME_NAME_JACK_OR_BETTER = "Jack or Better";

/* Stardom game name filter */
const string LobbyConstant::STARDOM_GAME_NAME_SLOT = "slot";
const string LobbyConstant::STARDOM_GAME_NAME_BLACKJACK_SINGLE = "blackjack";

/* Product */
const string LobbyConstant::PRODUCT_TYPE_SHOP = "coin";

/* Promotion */
const long LobbyConstant::PROMOTION_ID_001 = 1;
const long LobbyConstant::PROMOTION_ID_002 = 2;
const long LobbyConstant::PROMOTION_ID_003 = 3;

const string LobbyConstant::MAX_USER_TO_GET_REWARD = "max_user_to_get_reward";
const string LobbyConstant::COIN_REWARD = "coin_reward";
const string LobbyConstant::MIN_USER_TO_GET_REWARD = "min_user_to_get_reward";
const string LobbyConstant::DEADLINE_TIMESTAMP = "deadline_timestamp";
const string LobbyConstant::VIP_TYPE_REWARD = "vip_type_reward";
const string LobbyConstant::PROMOTION_003_NUMBER_OF_DAY = "promotion_003_number_of_day";
const string LobbyConstant::PROMOTION_003_COIN_REWARD_PER_DAY = "promotion_003_coin_reward_per_day";

const int LobbyConstant::TEST_CREATE_USER = 0;
const int LobbyConstant::TEST_SORT_RANK = 1;
const int LobbyConstant::TEST_RELOAD_BALANCE = 2;
const int LobbyConstant::TEST_USER_INFO_ID = 3;
const int LobbyConstant::TEST_USER_INFO_UID = 4;
const int LobbyConstant::TEST_USER_FRIEND_LIST = 5;

const int LobbyConstant::TEST_BLOCK_RELOAD_BALANCE = 6;
const long LobbyConstant::SUPER_BIG_TIMESTAMP = 30037148397000L;

/* Config for user */
const string LobbyConstant::OPERATOR_CODE = "operator_code";

const string LobbyConstant::OPEN_SLOT_MENU_AFTER_LOADING_MAIN_MENU = "open_slot_menu_after_loading_main_menu";

const string LobbyConstant::LINK_GAME_SLOT = "slot";
const string LobbyConstant::LINK_GAME_KENO = "keno";
const string LobbyConstant::LINK_GAME_TEXAS = "texas";

// 2016-03-03: Phuoc: server_config table
//    const string LobbyConstant::SERVER_CONFIG_NAME_VERSION = "version";
//    const string LobbyConstant::SERVER_CONFIG_NAME_FACEBOOK_TOKEN_FIELD_IN_DB = "facebook_token";
const string LobbyConstant::SERVER_CONFIG_NAME_VERSION_ANDROID = "version_android";
const string LobbyConstant::SERVER_CONFIG_NAME_VERSION_IOS = "version_ios";
const string LobbyConstant::SERVER_CONFIG_NAME_STRING_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP = "total_bet_multiplier_for_calculating_exp";
const string LobbyConstant::SERVER_CONFIG_NAME_SERVER_MODE = "server_mode";
const string LobbyConstant::SERVER_CONFIG_NAME_SAMPLE_WHEEL_MEGA_WIN_TUTORIAL = "sample_wheel_mega_win_in_tutorial";
const string LobbyConstant::SERVER_CONFIG_NAME_COIN_REWARD_FOR_ADS_UNITY = "coin_reward_for_ads_unity";
const string LobbyConstant::SERVER_CONFIG_NAME_COIN_REWARD_FOR_ADS_COLONY = "coin_reward_for_ads_colony";
// 2016-05-04: Dac: add ads facebook
const string LobbyConstant::SERVER_CONFIG_NAME_COIN_REWARD_FOR_TRIAL_PAY_FACEBOOK = "coin_reward_for_trial_pay_facebook";
const string LobbyConstant::SERVER_CONFIG_NAME_UNITY_ADS_KEY_FOR_HMAC_MD5_ANDROID = "unity_ads_key_for_hmac_md5_android";
const string LobbyConstant::SERVER_CONFIG_NAME_UNITY_ADS_KEY_FOR_HMAC_MD5_IOS = "unity_ads_key_for_hmac_md5_ios";
const string LobbyConstant::SERVER_CONFIG_NAME_ADS_COLONY_KEY_FOR_HMAC_MD5_ANDROID = "ads_colony_key_for_hmac_md5_android";
const string LobbyConstant::SERVER_CONFIG_NAME_ADS_COLONY_KEY_FOR_HMAC_MD5_IOS = "ads_colony_key_for_hmac_md5_ios";
const string LobbyConstant::SERVER_CONFIG_NAME_VERSION_LOADING_IMAGE = "version_loading_image";
const string LobbyConstant::SERVER_CONFIG_NAME_TRIAL_PAY_CONVERSION_RATE = "trial_pay_conversion_rate";

const string LobbyConstant::SERVER_CONFIG_NAME_NUMBER_OF_TIMES_CALL_METHOD_UPDATE_FROM_TRANSACTION_HISTORY_MOBILE
= "number_of_times_call_method_update_from_transaction_history_mobile";
const string LobbyConstant::SERVER_CONFIG_NAME_LAST_ID_QUERY_MOBILE_GAMEPLAY = "last_id_query_mobile_gameplay";

const string LobbyConstant::SERVER_CONFIG_NAME_CURRENT_TIMESTAMP_FOR_DEBUGGING_STRATEGY
= "current_timestamp_for_debugging_strategy";

const string LobbyConstant::SERVER_CONFIG_NAME_LINK_VERIFY_IOS_RECEIPT = "link_verify_ios_receipt";
const string LobbyConstant::SERVER_CONFIG_NAME_GET_MORE_COINS_PACKAGE_COIN_REWARD = "get_more_coins_package_coin_reward";
const string LobbyConstant::SERVER_CONFIG_NAME_GET_MORE_COINS_PACKAGE_TIME_TO_SHOW_OFFER = "get_more_coins_package_time_to_show_offer";

const string LobbyConstant::SERVER_CONFIG_NAME_TRIAL_PAY_NOTIFICATION_KEY_FOR_VERIFYING_CALLBACK_REQUEST_DATA =
"trial_pay_notification_key_for_verifying_callback_request_data";

const int LobbyConstant::SERVER_CONFIG_VALUE_MAX_TIME_CHANGE_NAME = 2;
const int LobbyConstant::SERVER_CONFIG_VALUE_DEFAULT_TIME_CHANGE_NAME = 0;

// 2016-03-03: Phuoc: server mode
const int LobbyConstant::SERVER_MODE_NORMAL = 0;
const int LobbyConstant::SERVER_MODE_TEST = 1;
const int LobbyConstant::SERVER_MODE_MAINTENANCE = 2;


const int LobbyConstant::USER_STATISTIC_LOG_TYPE_REQUEST_REAL_TIME_NOTIFICATION = 0;
const int LobbyConstant::USER_STATISTIC_LOG_TYPE_REQUEST_MY_PROFILE = 1;

const int LobbyConstant::ENABLE = 1;
const int LobbyConstant::DISABLE = 0;

const string LobbyConstant::BOT_AVATAR_LINK_LIST = "bot_avatar_link_list";

const string LobbyConstant::ALLOW_SEND_GIFT = "allow_send_gift";
const string LobbyConstant::ALLOW_SEND_FREE_GIFT = "allow_send_free_gift";
const string LobbyConstant::ALLOW_SEND_MESSAGE = "allow_send_message";
const string LobbyConstant::ALLOW_GET_BONUS_COIN_PER_TIME = "allow_get_bonus_coin_per_time";

const string LobbyConstant::MAX_TIME_LEFT_FOR_BONUS_COIN = "max_time_left_for_bonus_coin";
const string LobbyConstant::MAX_BONUS_COIN_PER_TIME = "max_bonus_coin_per_time";
const string LobbyConstant::MAX_TIME_LEFT_TO_GET_FREE_GIFT = "max_time_left_to_send_free_gift";
const string LobbyConstant::MAX_COIN_PER_FREE_GIFT = "max_coin_per_free_gift";
const string LobbyConstant::MAX_TIME_LEFT_TO_SEND_GIFT = "max_time_left_to_send_gift";
const string LobbyConstant::MAX_COIN_PER_GIFT = "max_coin_per_gift";
const string LobbyConstant::MIN_COIN_PER_GIFT = "min_coin_per_gift";

const string LobbyConstant::LAST_TIMESTAMP_QUERY = "last_timestamp_query";

const string LobbyConstant::RELOAD_REAL_TIME_NOTIFICATION_INTERVAL = "reload_real_time_notification_interval";

const string LobbyConstant::CONVERT_COIN_RATE = "convert_coin_rate";

/* Enable - Disable mobile */
const string LobbyConstant::MOBILE_ALLOW_SEND_GIFT = "mobile_allow_send_gift";
const string LobbyConstant::MOBILE_ALLOW_SEND_FREE_GIFT = "mobile_allow_send_free_gift";
const string LobbyConstant::MOBILE_ALLOW_SEND_MESSAGE = "mobile_allow_send_message";
const string LobbyConstant::MOBILE_ALLOW_GET_BONUS_COIN_PER_TIME = "mobile_allow_get_bonus_coin_per_time";

/* Amount mobile */
const string LobbyConstant::MOBILE_AMOUNT_MAX_TIME_LEFT_FOR_BONUS_COIN = "mobile_amount_max_time_left_for_bonus_coin";
const string LobbyConstant::MOBILE_AMOUNT_MAX_BONUS_COIN_PER_TIME = "mobile_amount_max_bonus_coin_per_time";
const string LobbyConstant::MOBILE_AMOUNT_MAX_TIME_LEFT_TO_GET_FREE_GIFT = "mobile_amount_max_time_left_to_send_free_gift";
const string LobbyConstant::MOBILE_AMOUNT_MAX_COIN_PER_FREE_GIFT = "mobile_amount_max_coin_per_free_gift";
const string LobbyConstant::MOBILE_AMOUNT_MAX_TIME_LEFT_TO_SEND_GIFT = "mobile_amount_max_time_left_to_send_gift";
const string LobbyConstant::MOBILE_AMOUNT_MAX_COIN_PER_GIFT = "mobile_amount_max_coin_per_gift";
const string LobbyConstant::MOBILE_AMOUNT_MIN_COIN_PER_GIFT = "mobile_amount_min_coin_per_gift";

/* Daily bonus */
const string LobbyConstant::DAILY_BONUS_FRIEND_BONUS = "daily_bonus_friend_bonus";
const string LobbyConstant::DAILY_BONUS_COIN_PER_LEVEL = "daily_bonus_bonus_coin_per_level";
const string LobbyConstant::DAILY_BONUS_TIMESTAMP_IN_ONE_DAY = "daily_bonus_time_left_to_get_bonus";

/* Level */
const string LobbyConstant::EXP_CONSTANT_AFTER_REACH_LIMIT = "exp_constant_after_reach_limit";

const string LobbyConstant::MIN_COIN_FOR_SORT = "min_coin_for_sort";
const string LobbyConstant::MAX_COIN_FOR_SORT = "max_coin_for_sort";

/* Friend update frequency */
const string LobbyConstant::FRIEND_UPDATE_FREQUENCY = "friend_update_frequency";

const string LobbyConstant::SERVER_MAINTENANCE = "allow_server_maintenance";
const string LobbyConstant::FORCE_USER_RELOAD = "allow_force_user_reload";

const string LobbyConstant::CHECK_MULTIPLE_LOGIN = "allow_check_multiple_login";

const string LobbyConstant::MIN_MOBILE_UNITY_ANDROID_VERSION_TO_PLAY = "min_mobile_unity_android_version_to_play";
const string LobbyConstant::LAST_TIMESTAMP_QUERY_MOBILE_GAME_PLAY = "last_timestamp_query_mobile_gameplay";


/* ----------------------------------------- User Transaction Log Type ----------------------------------------- */
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_UNKNOWN = 0;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_ADMIN_CREDIT = 1;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_ADMIN_DEBIT = 2;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_GET_DAILY_BONUS = 3;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_GET_FREE_COIN = 4;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_DEBIT_ACCEPT_GIFT = 5;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_ACCEPT_GIFT = 6;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_COIN_PACKAGE = 7;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_ACCEPT_FREE_GIFT = 8;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_USER_SIGN_UP = 9;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_OPEN_SECRET_GIFT = 10;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_OPEN_THE_SAFE = 11;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_SEND_FREE_GIFT = 12;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_USER_LOCAL_SIGN_UP = 13;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_LEVEL_UP_REWARD = 14;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_PROMOTION_001_REWARD = 15;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_REDEEM_VOUCHER = 16;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_COMEBACK_BONUS_GIFT = 17;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_UPPER_VIP_BONUS_GIFT = 18;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_GAME_PLAY_SPIN = 19;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_DEBIT_GAME_PLAY_SPIN = 20;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_COLLECTED_ACHIEVEMENT = 21;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_REDEEM_TUTORIAL_REWARD = 22;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_VIEW_ADS_UNITY_REWARD = 23;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_VIEW_ADS_COLONY_REWARD = 24;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_MIGRATE_WALLET_DATA = 25;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_DEBIT_MIGRATE_WALLET_DATA = 26;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_FUN_PLAYER = 27;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_REDEEM_PRE_TUTORIAL_REWARD = 28;
// 2016-05-04: Dac:
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_VIEW_TRIAL_PAY_FACEBOOK_REWARD = 29;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_DEBIT_TO_SHOW_POPUP_F2P_AND_P2P = 30;
// 2016-10-11: Phuoc:
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_DAILY_BONUS_STREAK = 31;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_FREE_COIN_GIFT = 32;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_REFERENCE_CODE_GIFT = 33;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_DAILY_BONUS_LUCKY_SPIN = 34;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_LUCKY_WHEEL = 35;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_LUCKY_BOX = 36;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_PIGGY_BANK = 37;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_BONUS_FOR_TOP_PLAYER_GIFT = 38;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_PLAY_WITH_FRIEND_FOR_BENEFIT_GIFT = 39;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_DAILY_CHALLENGE = 40;
const int LobbyConstant::USER_TRANSACTION_LOG_TYPE_CREDIT_COMEBACK_BONUS = 41;
/* ----------------------------------------- User Transaction Log Type ----------------------------------------- */

/* ----------------------------------------------- Admin Log Type ----------------------------------------------- */
const int LobbyConstant::USER_ADMIN_LOG_TYPE_CREDIT_USER = 0;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_DEBIT_USER = 1;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_GAME_CONFIG_STATUS = 2;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_GAME_CONFIG_AMOUNT = 3;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_SERVER_VERSION = 4;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_MERCHANT_INFO = 5;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_ADD_AND_REMOVE_GAME_WITH_LEVEL_REQUIREMENT = 6;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_SLOT_GAME_INFO = 7;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_LEVEL_REQUIREMENT_CONFIG = 8;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_VIP_CONFIG = 9;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_USER_SECRET_GIFT = 10;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_PASSWORD_USER_ADMIN = 11;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_BOT_USER_INFO = 12;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_USER_INFO = 13;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_CREATE_LEVEL = 14;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP = 15;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_SERVER_CONFIG = 16;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_CONVERT_FACEBOOK_ACCOUNT_TO_GUEST_ACCOUNT = 17;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_ACHIEVEMENT = 18;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_STRATEGY_CONFIG = 19;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_DAILY_CHALLENGE_CONFIG = 20;
const int LobbyConstant::USER_ADMIN_LOG_TYPE_UPDATE_COMEBACK_BONUS_MOBILE_CONFIG = 21;
/* ----------------------------------------------- Admin Log Type ----------------------------------------------- */

const string LobbyConstant::USER_ADMIN_LOG_KEY_NAME_CREDIT_USER = "credit";
const string LobbyConstant::USER_ADMIN_LOG_KEY_NAME_DEBIT_USER = "debit";
const string LobbyConstant::USER_ADMIN_LOG_KEY_NAME_UPDATE_SERVER_VERSION = "server_version";
const string LobbyConstant::USER_ADMIN_LOG_KEY_NAME_UPDATE_MERCHANT_INFO = "merchant_info";
const string LobbyConstant::USER_ADMIN_LOG_KEY_NAME_ADD_AND_REMOVE_GAME_WITH_LEVEL_REQUIREMENT =
"addAndRemoveGameWithLevelRequiment";

const string LobbyConstant::USER_ADMIN_LOG_KEY_UPDATE_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP = "update_total_bet_multiplier_for_calculating_exp";

const int LobbyConstant::ALLOW_REQUEST_KEY_FOR_SECRET_GIFT = LobbyConstant::ENABLE;

const long LobbyConstant::CACHE_MOBILE_MAX_TIME_TO_REQUEST_SECRET_KEY = 86400000;

const long LobbyConstant::CACHE_MAX_TIME_TO_REQUEST_SECRET_KEY = 86400000;

const long LobbyConstant::VALIDATE_TIME = 259200000;

const long LobbyConstant::NUMBER_OF_HOUR_BEFORE_CALCULATE_GAME_ACCESS_PROCESSED_LOG = 5;

const long LobbyConstant::CACHE_MIN_KEY_TO_OPEN_BOX = 3;

const long LobbyConstant::MILLISECONDS_IN_ONE_HOUR = 3600000L;
const long LobbyConstant::MILLISECONDS_IN_ONE_MINUTE = 60000L;
const long LobbyConstant::GET_CCU_TIMESTAMP_END_GAP = 30000L;


/*TYPE LOG CONSTANT  */
const int LobbyConstant::GET_DAILY_BONUS_LOG = 0;
const int LobbyConstant::OPEN_SECRET_BOX_LOG = 1;
const int LobbyConstant::OPEN_THE_SAFE_LOG = 2;

const int LobbyConstant::DAILY_BONUS_SECRET_GIFT_PAGE_SIZE = 100;
const int LobbyConstant::DAILY_BONUS_SORT_TYPE_USER_ID = 0;
const int LobbyConstant::DAILY_BONUS_SORT_TYPE_COIN = 1;

const int LobbyConstant::DAILY_BONUS_LOG_TYPE = 0;
const int LobbyConstant::BOX_AND_SAFE_LOG_TYPE = 1;

const int LobbyConstant::USER_PURCHASE_STATISTIC_PAGE_SIZE = 100;
/* Voucher */
const int LobbyConstant::PAGE_SIZE_VOUCHER_LIST = 100;
const int LobbyConstant::PAGE_SIZE_MAINTENANCE_SCHEDULE_LIST = 100;
const int LobbyConstant::VOUCHER_EXPIRED_HOUR = 9;

//    const long LobbyConstant::TIMESTAMP_LAUNCH_DAY = 1438189201000L;

/* Schedule status */
//    const string LobbyConstant::SCHEDULE_CALCULATE_RETURNING_USER = "SCHEDULE_CALCULATE_RETURNING_USER";

const string LobbyConstant::SCHEDULE_CHECK_SCHEDULER_STATUS = "SCHEDULE_CHECK_SCHEDULER_STATUS";

const string LobbyConstant::SCHEDULE_CALCULATE_AVG_PLAY_TIME = "SCHEDULE_CALCULATE_AVG_PLAY_TIME";

const string LobbyConstant::SCHEDULE_GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY = "SCHEDULE_GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY";
const string LobbyConstant::SCHEDULE_GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY = "SCHEDULE_GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY";
//    const string LobbyConstant::SCHEDULE_GET_GAME_PLAY_HISTORY_START = "SCHEDULE_GET_GAME_PLAY_HISTORY_START";
//    const string LobbyConstant::SCHEDULE_GET_GAME_PLAY_HISTORY_END = "SCHEDULE_GET_GAME_PLAY_HISTORY_END";

const string LobbyConstant::SCHEDULE_UPDATE_USER_STARDOM_STATISTIC = "SCHEDULE_UPDATE_USER_STARDOM_STATISTIC";
//    const string LobbyConstant::SCHEDULE_UPDATE_USER_STARDOM_STATISTIC_START = "SCHEDULE_UPDATE_USER_STARDOM_STATISTIC_START";
//    const string LobbyConstant::SCHEDULE_UPDATE_USER_STARDOM_STATISTIC_END = "SCHEDULE_UPDATE_USER_STARDOM_STATISTIC_END";

const string LobbyConstant::SCHEDULE_CALCULATE_GAME_ACCESS_PROCESSED_LOG = "SCHEDULE_CALCULATE_GAME_ACCESS_PROCESSED_LOG";
//    const string LobbyConstant::SCHEDULE_CALCULATE_AVG_PLAY_TIME_START = "SCHEDULE_CALCULATE_AVG_PLAY_TIME_START";
//    const string LobbyConstant::SCHEDULE_CALCULATE_AVG_PLAY_TIME_END = "SCHEDULE_CALCULATE_AVG_PLAY_TIME_END";

const string LobbyConstant::SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES = "SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES";
//    const string LobbyConstant::SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES_START = "SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES_START";
//    const string LobbyConstant::SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES_END = "SCHEDULE_CALCULATE_CCUS_EVERY_60_MINUTES_END";

const string LobbyConstant::SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES = "SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES";
//    const string LobbyConstant::SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES_START = "SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES_START";
//    const string LobbyConstant::SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES_END = "SCHEDULE_CALCULATE_CCUS_EVERY_5_MINUTES_END";

const string LobbyConstant::SCHEDULE_UPDATE_RANKING = "SCHEDULE_UPDATE_RANKING";
//    const string LobbyConstant::SCHEDULE_UPDATE_RANKING_START = "SCHEDULE_UPDATE_RANKING_START";
//    const string LobbyConstant::SCHEDULE_UPDATE_RANKING_END = "SCHEDULE_UPDATE_RANKING_END";

const string LobbyConstant::SCHEDULE_DELETE_EXPIRED_USER = "SCHEDULE_DELETE_EXPIRED_USER";
//    const string LobbyConstant::SCHEDULE_DELETE_EXPIRED_USER_START = "SCHEDULE_DELETE_EXPIRED_USER_START";
//    const string LobbyConstant::SCHEDULE_DELETE_EXPIRED_USER_END = "SCHEDULE_DELETE_EXPIRED_USER_END";

const string LobbyConstant::SCHEDULE_CHECK_USER_REJECT_APP_FB = "SCHEDULE_CHECK_USER_REJECT_APP_FB";
//    const string LobbyConstant::SCHEDULE_CHECK_USER_REJECT_APP_FB_START = "SCHEDULE_CHECK_USER_REJECT_APP_FB_START";
//    const string LobbyConstant::SCHEDULE_CHECK_USER_REJECT_APP_FB_END = "SCHEDULE_CHECK_USER_REJECT_APP_FB_END";

const string LobbyConstant::SCHEDULE_RESET_DAILY_CHALLENGE_SCHEDULER = "SCHEDULE_RESET_DAILY_CHALLENGE_SCHEDULER";
const string LobbyConstant::SCHEDULE_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER = "SCHEDULE_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER";

const string LobbyConstant::SCHEDULE_CHECK_SCHEDULES_OVER_15_MINUTES = "SCHEDULE_CHECK_SCHEDULES_OVER_15_MINUTES";
const long LobbyConstant::TIME_RUNNING_FOR_SCHEDULE = 15 * 60;
/* User access token hashmap */
//    const string LobbyConstant::USER_ACCESS_TOKEN_HASHMAP = "USER_ACCESS_TOKEN_HASHMAP";
const string LobbyConstant::USER_ACCESS_TOKEN = "USER_ACCESS_TOKEN";
const int LobbyConstant::USER_ACCESS_TOKEN_HASHMAP_EXPIRED_TIME_IN_MEMCACHED = 1800;

/* User statistic log */
const int LobbyConstant::PAGE_SIZE_USER_STATISTIC_LOG = 100;

/* Login service type */
const int LobbyConstant::LOGIN_SERVICE_TYPE_WEB = 0;
const int LobbyConstant::LOGIN_SERVICE_TYPE_FACEBOOK = 1;

const int LobbyConstant::LOGIN_SERVICE_TYPE_IOS = 2;

/* Domain of facebook image link */
const string LobbyConstant::DOMAIN_FACEBOOK_IMAGE_LINK = "fbcdn.net";

/* Login count */
const int LobbyConstant::PAGE_SIZE_USER_LOGIN_STATISTIC = 100;

/* Redirect url after validation */
const string LobbyConstant::VALIDATION_REDIRECT_URL_SESSION_ATTRIBUTE = "validationRedirectUrl";

/* Credit/Debit type */
const int LobbyConstant::CREDIT_DEBIT_TYPE_UNKNOWN = 0;
const int LobbyConstant::CREDIT_DEBIT_TYPE_CREDIT = 1;
const int LobbyConstant::CREDIT_DEBIT_TYPE_DEBIT = 2;

/* Accept gift list type user gift/secret gift */
const int LobbyConstant::ACCEPT_GIFT_LIST_TYPE_USER_GIFT = 0;
const int LobbyConstant::ACCEPT_GIFT_LIST_TYPE_SECRET_GIFT = 1;

/* Web background */
const int LobbyConstant::WEB_BACKGROUND_RED = 0;
const int LobbyConstant::WEB_BACKGROUND_BLACK = 1;

/* Payment service */

const int LobbyConstant::PAYMENT_FROM_FACEBOOK = 0;
const int LobbyConstant::PAYMENT_FROM_APPLE = 1;
const int LobbyConstant::PAYMENT_FROM_ANDROID = 2;

/* Launch day */
const long LobbyConstant::TIMESTAMP_LAUNCH_DAY = 1435683600000L;

/* Payment source id */
const int LobbyConstant::PAYMENT_SOURCE_ID_TYPE_FACEBOOK = 0;
const int LobbyConstant::PAYMENT_SOURCE_ID_TYPE_APPLE = 1;

/* -------------------------------------------------- Payment -------------------------------------------------- */
const string LobbyConstant::DEFAULT_FACEBOOK_CURRENCY = "USD";
/* Facebook product type */
// 2016-08-26: Phuoc: dùng cho trường hợp dispute/refund/chargeback/...
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_INVALID = -1;

const int LobbyConstant::FACEBOOK_OLD_PRODUCT_TYPE_COIN = 1;
const int LobbyConstant::FACEBOOK_OLD_PRODUCT_TYPE_KEY = 2;
const int LobbyConstant::FACEBOOK_OLD_PRODUCT_TYPE_STARTER = 3;
const int LobbyConstant::FACEBOOK_OLD_PRODUCT_TYPE_30_DAYS_COIN = 4;
const int LobbyConstant::FACEBOOK_OLD_PRODUCT_TYPE_DYNAMIC_PRODUCT_F2P = 5;
const int LobbyConstant::FACEBOOK_OLD_PRODUCT_TYPE_DYNAMIC_PRODUCT_P2P = 6;
const int LobbyConstant::FACEBOOK_OLD_PRODUCT_TYPE_CROWN = 7;


const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_UNKNOWN = 0;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_COIN_1 = 11;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_COIN_2 = 12;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_COIN_3 = 13;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_COIN_4 = 14;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_COIN_5 = 15;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_COIN_6 = 16;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_COIN_7 = 17;

const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_KEY_1 = 21;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_KEY_2 = 22;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_KEY_3 = 23;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_KEY_4 = 24;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_VIP = 30;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_STARTER_PACK = 41;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_GET_MORE_COINS_PACK = 42;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_30_DAYS_COIN_PACK = 43; // Not release in production

const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_FREE_TO_PLAY_1 = 51;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_FREE_TO_PLAY_2 = 52;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_PAY_TO_PLAY_1 = 61;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_PAY_TO_PLAY_2 = 62;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_PAY_TO_PLAY_3 = 63;

const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_CROWN_1 = 71;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_CROWN_2 = 72;
const int LobbyConstant::FACEBOOK_PRODUCT_TYPE_CROWN_3 = 73;


/* Facebook payment result */
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_FAIL_FROM_MIGRATE = -1;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_UNKNOWN = 0;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_CHARGE_COMPLETED = 1;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_CHARGE_FAILED = 2;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_DISPUTE = 3;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_REFUND = 4;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_ERROR_INVALID_PRODUCT_ID = 6;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_INVALID_PRODUCT_TYPE = 8;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_INVALID_PAYMENT_DATA = 10;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_UNSUPPORTED_PRODUCT = 11;
const int LobbyConstant::FACEBOOK_PAYMENT_RESULT_PROXY_ERROR = 12;

/* Facebook callback json changed field */
const string LobbyConstant::FACEBOOK_CALLBACK_JSON_CHANGED_FIELD_ACTIONS = "actions";
const string LobbyConstant::FACEBOOK_CALLBACK_JSON_CHANGED_FIELD_DISPUTES = "disputes";

const string LobbyConstant::FACEBOOK_PAYMENT_DETAIL_ACTION_TYPE_CHARGE = "charge";
const string LobbyConstant::FACEBOOK_PAYMENT_DETAIL_ACTION_STATUS_COMPLETED = "completed";

/* Facebook payment test */
const int LobbyConstant::FACEBOOK_PAYMENT_IS_NOT_TEST = 0;
const int LobbyConstant::FACEBOOK_PAYMENT_IS_TEST = 1;

/* Apple package type */
const int LobbyConstant::APPLE_PRODUCT_TYPE_UNKNOWN = 0;

const int LobbyConstant::APPLE_PRODUCT_TYPE_COIN_1 = 11; // 400,000
const int LobbyConstant::APPLE_PRODUCT_TYPE_COIN_2 = 12; // 880,000
const int LobbyConstant::APPLE_PRODUCT_TYPE_COIN_3 = 13; // 2,400,000
const int LobbyConstant::APPLE_PRODUCT_TYPE_COIN_4 = 14; // 7,200,000
const int LobbyConstant::APPLE_PRODUCT_TYPE_COIN_5 = 15; // 24,000,000
const int LobbyConstant::APPLE_PRODUCT_TYPE_COIN_6 = 16; // 70,000,000
const int LobbyConstant::APPLE_PRODUCT_TYPE_COIN_7 = 17; // 200,000,000

const int LobbyConstant::APPLE_PRODUCT_TYPE_CROWN_1 = 71;
const int LobbyConstant::APPLE_PRODUCT_TYPE_CROWN_2 = 72;
const int LobbyConstant::APPLE_PRODUCT_TYPE_CROWN_3 = 73;
const int LobbyConstant::APPLE_PRODUCT_TYPE_MOBILE_SPECIAL_OFFER = 80;
const int LobbyConstant::APPLE_PRODUCT_TYPE_BOOSTER_1 = 91;
const int LobbyConstant::APPLE_PRODUCT_TYPE_BOOSTER_2 = 92;
const int LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_WHEEL_1 = 101;
const int LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_WHEEL_2 = 102;
const int LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_WHEEL_3 = 103;
const int LobbyConstant::APPLE_PRODUCT_TYPE_PIGGY_BANK_1 = 111;
const int LobbyConstant::APPLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_WIN = 121;
const int LobbyConstant::APPLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_10_PERCENT = 122;
const int LobbyConstant::APPLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_20_PERCENT = 123;
const int LobbyConstant::APPLE_PRODUCT_TYPE_MAGIC_ITEM_DOUBLE_EXP = 124;
const int LobbyConstant::APPLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SYMBOL = 125;
const int LobbyConstant::APPLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_BIG_WIN = 126;
const int LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_1 = 131;
const int LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_2 = 132;
const int LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_3 = 133;

/* Apple payment type */
const int LobbyConstant::APPLE_PAYMENT_RESULT_UNKNOWN = 0;
const int LobbyConstant::APPLE_PAYMENT_RESULT_CHARGE = 1;
const int LobbyConstant::APPLE_PAYMENT_RESULT_ERROR_VERIFY_GOOGLE_RECEIPT_FAIL = 2;
const int LobbyConstant::APPLE_PAYMENT_RESULT_ERROR_INVALID_APP_ID = 3;
const int LobbyConstant::APPLE_PAYMENT_RESULT_ERROR_CODE_FROM_APPLE_SERVER = 4;
const int LobbyConstant::APPLE_PAYMENT_RESULT_ERROR_PAYMENT_EXIST = 5;
const int LobbyConstant::APPLE_PAYMENT_RESULT_ERROR_INVALID_PRODUCT_ID = 6;
const int LobbyConstant::APPLE_PAYMENT_RESULT_ERROR_CAN_NOT_REWARD_USER = 7;
const int LobbyConstant::APPLE_PAYMENT_RESULT_INVALID_PRODUCT_TYPE = 8;
const int LobbyConstant::APPLE_PAYMENT_RESULT_INVALID_PAYMENT_API_VERSION = 9;
const int LobbyConstant::APPLE_PAYMENT_RESULT_INVALID_PAYMENT_DATA = 10;
const int LobbyConstant::APPLE_PAYMENT_RESULT_UNSUPPORTED_PRODUCT = 11;
const int LobbyConstant::APPLE_PAYMENT_RESULT_PROXY_ERROR = 12;

/* Google package type */
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_UNKNOWN = 0;

const int LobbyConstant::GOOGLE_PRODUCT_TYPE_COIN_1 = 11; // 400,000
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_COIN_2 = 12; // 880,000
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_COIN_3 = 13; // 2,400,000
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_COIN_4 = 14; // 7,200,000
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_COIN_5 = 15; // 24,000,000
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_COIN_6 = 16; // 70,000,000
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_COIN_7 = 17; // 200,000,000

const int LobbyConstant::GOOGLE_PRODUCT_TYPE_CROWN_1 = 71;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_CROWN_2 = 72;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_CROWN_3 = 73;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_MOBILE_SPECIAL_OFFER = 80;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_BOOSTER_1 = 91;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_BOOSTER_2 = 92;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_LUCKY_WHEEL_1 = 101;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_LUCKY_WHEEL_2 = 102;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_LUCKY_WHEEL_3 = 103;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_PIGGY_BANK_1 = 111;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_WIN = 121;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_10_PERCENT = 122;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SPIN_20_PERCENT = 123;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_DOUBLE_EXP = 124;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_LUCKY_SYMBOL = 125;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_MAGIC_ITEM_100_PERCENT_BIG_WIN = 126;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_1 = 131;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_2 = 132;
const int LobbyConstant::GOOGLE_PRODUCT_TYPE_LUCKY_BOX_DOUBLE_REWARD_3 = 133;

/* Google payment type */
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_UNKNOWN = 0;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_CHARGE = 1;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_ERROR_VERIFY_GOOGLE_RECEIPT_FAIL = 2;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_ERROR_INVALID_APP_ID = 3;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_ERROR_CODE_FROM_GOOGLE_SERVER = 4;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_ERROR_PAYMENT_EXIST = 5;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_ERROR_INVALID_PRODUCT_ID = 6;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_ERROR_CAN_NOT_REWARD_USER = 7;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_INVALID_PRODUCT_TYPE = 8;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_INVALID_PAYMENT_API_VERSION = 9;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_INVALID_PAYMENT_DATA = 10;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_UNSUPPORTED_PRODUCT = 11;
const int LobbyConstant::GOOGLE_PAYMENT_RESULT_PROXY_ERROR = 12;
/* -------------------------------------------------- Payment -------------------------------------------------- */

/* Package status */
const string LobbyConstant::PACKAGE_STATUS = "completed";

const string LobbyConstant::FB_PURCHASE_STATUS_COMPLETE = "completed";
const string LobbyConstant::GGPLAY_PURCHASE_STATUS_COMPLETE = "approved";

/* Payment log type */
const int LobbyConstant::PAYMENT_INVALID = -1;
const int LobbyConstant::PAYMENT_APPROVE = 0;
const int LobbyConstant::PAYMENT_CANCEL = 1;
const int LobbyConstant::PAYMENT_ERROR = 2;
const int LobbyConstant::PAYMENT_REFUND = 3;
const int LobbyConstant::PAYMENT_EXISTED = 4;
const int LobbyConstant::USER_CLICK_PAYMENT = 5;
const int LobbyConstant::APP_STORE_READY = 6;

/* Admin : filter list user */
const int LobbyConstant::FILTER_BY_NAME = 0;
const int LobbyConstant::FILTER_BY_FB_UID = 1;
const int LobbyConstant::FILTER_BY_LEVEL = 2;
const int LobbyConstant::FILTER_BY_EMAIL = 3;
const int LobbyConstant::FILTER_BY_RANK = 4;
const int LobbyConstant::FILTER_BY_COIN = 5;
const int LobbyConstant::FILTER_BY_ID = 6;
const int LobbyConstant::FILTER_BY_TS_CREATED = 7;
const int LobbyConstant::FILTER_BY_TS_LAST_MODIFIED = 8;
const int LobbyConstant::FILTER_BY_USER_TYPE = 9;
const int LobbyConstant::FILTER_BY_LOGIN_COUNT = 10;

const int LobbyConstant::FILTER_BY_FARMER_AMOUNT_SEND = 11;
const int LobbyConstant::FILTER_BY_FARMER_TOTAL_SEND_TIMES = 12;


/* Coin reward after level up */
const string LobbyConstant::COIN_REWARD_AFTER_LEVEL_UP = "COIN_REWARD_AFTER_LEVEL_UP";
const string LobbyConstant::CROWN_REWARD_AFTER_LEVEL_UP = "CROWN_REWARD_AFTER_LEVEL_UP";

/* Default locale */
const string LobbyConstant::DEFAULT_LOCALE_PP_LANGUAGE = "en-US";
const string LobbyConstant::DEFAULT_LOCALE_FB_LANGUAGE = "en_US";

const string LobbyConstant::DYNAMIC_PACK_STRING = "dynamic-pack";

// 2015-11-11: Toan
const int LobbyConstant::NOT_LOGIN_IN_A_DAY = 0;
const int LobbyConstant::LOGIN_MORE_THAN_ONCE_IN_A_DAY = 1;
const string LobbyConstant::LOGIN_IN_DAY = "login_in_day";
const double LobbyConstant::AMOUNT_BUY_GET_MORE_COIN = 6;

const int LobbyConstant::MIN_RANDOM_ID_FOR_NAME_OF_GUEST_USER = 168;
const int LobbyConstant::MAX_RANDOM_ID_FOR_NAME_OF_GUEST_USER = 888;

const int LobbyConstant::NAMING_STRATEGY_USING_WRAPPER = 0;
const int LobbyConstant::NAMING_STRATEGY_USING_PUBLIC_FOLDER = 1;

const string LobbyConstant::GRAPH_API = "https://graph.facebook.com/v2.8/";

const int LobbyConstant::PLATFORM_WEB = 0;
const int LobbyConstant::PLATFORM_MOBILE = 1;

// 2016-03-11: Phuoc: dùng trong các API phân biệt android/ios
const int LobbyConstant::PLATFORM_ANDROID = 1;
const int LobbyConstant::PLATFORM_IOS = 2;

const int LobbyConstant::DEFAULT_MEMCACHED_EXPIRED_TIME = 3600;

const int LobbyConstant::DEFAULT_ANDROID_VERSION_CODE = -1;

// 2016-1-13 : Toan
//DAT - Ko dung
//const string LobbyConstant::MOBILE_GAME_DEEP_BLUE_MOBILE_WITHOUT_PREFIX = "deepblue";
//const string LobbyConstant::MOBILE_GAME_GOLDEN_EGG_MOBILE_WITHOUT_PREFIX = "goldeneggs";
//const string LobbyConstant::MOBILE_GAME_NEZHA_MOBILE_WITHOUT_PREFIX = "nezha";
//const string LobbyConstant::MOBILE_GAME_PHARAOH_MOBILE_WITHOUT_PREFIX = "pharaoh";
//const string LobbyConstant::MOBILE_GAME_ROMAN_EMPIRE_MOBILE_WITHOUT_PREFIX = "romanempire";
//const string LobbyConstant::MOBILE_GAME_BOXING_MOBILE_WITHOUT_PREFIX = "boxing";
//
//const string LobbyConstant::MOBILE_GAME_BOXING_MOBILE_WITH_WRONG_PREFIX = "game_boxing";
//const string LobbyConstant::MOBILE_GAME_DEEP_BLUE_MOBILE_WITH_WRONG_PREFIX = "game_deepblue";
//const string LobbyConstant::MOBILE_GAME_GOLDEN_EGG_MOBILE_WITH_WRONG_PREFIX = "game_goldenegg";
//const string LobbyConstant::MOBILE_GAME_NEZHA_MOBILE_WITH_WRONG_PREFIX = "game_nezha";
//const string LobbyConstant::MOBILE_GAME_PHARAOH_MOBILE_WITH_WRONG_PREFIX = "game_pharaoh";
//const string LobbyConstant::MOBILE_GAME_ROMAN_EMPIRE_MOBILE_WITH_WRONG_PREFIX = "game_romanempire";
//
//const string LobbyConstant::MOBILE_GAME_BOXING_MOBILE_WITH_RIGHT_PREFIX = "mobile_boxing";
//const string LobbyConstant::MOBILE_GAME_DEEP_BLUE_MOBILE_WITH_RIGHT_PREFIX = "mobile_deepblue";
//const string LobbyConstant::MOBILE_GAME_GOLDEN_EGG_MOBILE_WITH_RIGHT_PREFIX = "mobile_goldenegg";
//const string LobbyConstant::MOBILE_GAME_NEZHA_MOBILE_WITH_RIGHT_PREFIX = "mobile_nezha";
//const string LobbyConstant::MOBILE_GAME_PHARAOH_MOBILE_WITH_RIGHT_PREFIX = "mobile_pharaoh";
//const string LobbyConstant::MOBILE_GAME_ROMAN_EMPIRE_MOBILE_WITH_RIGHT_PREFIX = "mobile_romanempire";


const double LobbyConstant::PRICE_OF_SPECIAL_OFFER_PACKAGE = 0.99;

const int LobbyConstant::VOUCHER_PLATFORM_WEB = 0;
const int LobbyConstant::VOUCHER_PLATFORM_MOBILE = 1;
const string LobbyConstant::VOUCHER_PICTURE_URL_MOBILE = "";
const string LobbyConstant::VOUCHER_CAPTION_MOBILE = "";

const int LobbyConstant::TRANSACTION_HISTORY_SOURCE_TYPE_DESKTOP = 0;
const int LobbyConstant::TRANSACTION_HISTORY_SOURCE_TYPE_MOBILE = 1;

const bool LobbyConstant::ACHIEVEMENT_FLAG_COMPLETE = true;
const bool LobbyConstant::ACHIEVEMENT_FLAG_NOT_COMPLETE = false;

const bool LobbyConstant::ACHIEVEMENT_FLAG_COLLECTED = true;
const bool LobbyConstant::ACHIEVEMENT_FLAG_NOT_COLLECTED = false;

const int LobbyConstant::ACHIEVEMENT_GROUP_TYPE_GENERAL = 0;
const int LobbyConstant::ACHIEVEMENT_GROUP_TYPE_GAME = 1;
const int LobbyConstant::ACHIEVEMENT_GROUP_TYPE_SOCIAL = 2;

const int LobbyConstant::ACHIEVEMENT_TYPE_COMPLETE_TUTORIAL = 0;
const int LobbyConstant::ACHIEVEMENT_TYPE_CONTINUOUSLY_LOGIN = 1;
const int LobbyConstant::ACHIEVEMENT_TYPE_LEVEL_ACHIEVED = 2;
const int LobbyConstant::ACHIEVEMENT_TYPE_SPIN_ON_SLOT = 3;
const int LobbyConstant::ACHIEVEMENT_TYPE_FIRST_TIME_DEPOSIT = 4;
const int LobbyConstant::ACHIEVEMENT_TYPE_ACHIEVEMENT_MILESTONE = 5;
const int LobbyConstant::ACHIEVEMENT_TYPE_SPIN_COMPLETED_MILESTONE = 6;
const int LobbyConstant::ACHIEVEMENT_TYPE_TOTAL_WIN_MILESTONE = 7;
const int LobbyConstant::ACHIEVEMENT_TYPE_TOTAL_BET_MILESTONE = 8;
const int LobbyConstant::ACHIEVEMENT_TYPE_SEND_INVITE_TO_FRIEND = 9;
const int LobbyConstant::ACHIEVEMENT_TYPE_SEND_GIFT_TO_FRIEND = 10;
const int LobbyConstant::ACHIEVEMENT_TYPE_RECEIVED_GIFT_FROM_FRIEND = 11;
const int LobbyConstant::ACHIEVEMENT_TYPE_LINK_ACCOUNT_TO_FACEBOOK = 12;

// 2016-02-26: Phuoc:
const int LobbyConstant::ACHIEVEMENT_CATEGORY_ID_PERSONAL_PROGRESSION = 0;
const int LobbyConstant::ACHIEVEMENT_CATEGORY_ID_SPIN_MANIA = 1;
const int LobbyConstant::ACHIEVEMENT_CATEGORY_ID_LOYALIST = 2;
const int LobbyConstant::ACHIEVEMENT_CATEGORY_ID_WINNINGS = 3;
const int LobbyConstant::ACHIEVEMENT_CATEGORY_ID_BETTING_MANIA = 4;
const int LobbyConstant::ACHIEVEMENT_CATEGORY_ID_FRIENDS_WITH_BENEFITS = 5;
const int LobbyConstant::ACHIEVEMENT_CATEGORY_ID_SOCIALLY_CONNECTED = 6;

const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_READY_TO_PLAY = 0; // Personal Progression - Completed Tutorial
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_LOYALTY = 1; // Personal Progression - Consecutive Login
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_JOURNEYMAN = 2; // Personal Progression - Level achieved (5 -> 15)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_EXPLORER = 3; // Personal Progression - Level achieved (20 -> 50)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_MASTER = 4; // Personal Progression - Level achieved (60 -> 80)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_SPIN_JUNIOR = 5; // Spin Mania - Spin xxx Times on Slot (50 -> 500)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_SPIN_SENIOR = 6; // Spin Mania - Spin xxx Times on Slot (1000 -> 5000)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_LOYAL_SUPPORTER = 7; // Loyalist - First time deposit
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_ACHIEVER = 8; // Loyalist - Achievement Points

const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_NOVICE = 9; // Winnings - Total Win (50,000 -> 250,000)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_APPRENTICE = 10; // Winnings - Total Win (500,000 -> 5,000,000)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_JUNIOR_ROLLER = 11; // Betting Mania - Total Bet (50,000 - 250,000)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_MASTER_ROLLER = 12; // Betting Mania - Total Bet (500,000 - 2,500,000)

const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_PARTY_ORGANISER = 13; // Friends with Benefits - Sent Invites to Friends (5 -> 15)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_GOOD_SAMARITAN = 14; // Friends with Benefits - Sent gifts to Friends (5 -> 20)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_SOCIALITE = 15; // Friends with Benefits - Received 5 gifts from friends (5 -> 20)
const int LobbyConstant::ACHIEVEMENT_SUB_CATEGORY_ID_LINK_ACCOUNT_TO_FACEBOOK = 16; // Socially Connected


const int LobbyConstant::INVALID_RESULT_UPDATE_SQL_COMMAND = -1;

const string LobbyConstant::STRING_CALCULATE_AVG_PLAY_TIME_SCHEDULER = "CALCULATE_AVG_PLAY_TIME_SCHEDULER";
const string LobbyConstant::STRING_GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY_SCHEDULER = "GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY_SCHEDULER";
const string LobbyConstant::STRING_GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY_SCHEDULER = "GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY_SCHEDULER";
const string LobbyConstant::STRING_UPDATE_USER_STARDOM_STATISTIC_SCHEDULER = "UPDATE_USER_STARDOM_STATISTIC_SCHEDULER";
const string LobbyConstant::STRING_CALCULATE_GAME_ACCESS_PROCESSED_LOG = "CALCULATE_GAME_ACCESS_PROCESSED_LOG";
const string LobbyConstant::STRING_CALCULATE_CCUS_EVERY_60_MINUTES_SCHEDULER = "CALCULATE_CCUS_EVERY_60_MINUTES_SCHEDULER";
const string LobbyConstant::STRING_CALCULATE_CCUS_EVERY_5_MINUTES_SCHEDULER = "CALCULATE_CCUS_EVERY_5_MINUTES_SCHEDULER";
const string LobbyConstant::STRING_DELETE_EXPIRED_USER_SCHEDULER = "DELETE_EXPIRED_USER_SCHEDULER";
const string LobbyConstant::STRING_CHECK_USER_REJECT_APP_FB_SCHEDULER = "CHECK_USER_REJECT_APP_FB_SCHEDULER";
const string LobbyConstant::STRING_CHECK_RESET_DAILY_CHALLENGE_SCHEDULER = "CHECK_RESET_DAILY_CHALLENGE_SCHEDULER";
const string LobbyConstant::STRING_CHECK_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER = "CHECK_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER";


const string LobbyConstant::TIME_TO_SHOW_OFFER = "TIME_TO_SHOW_OFFER";
const string LobbyConstant::COIN_FOR_SHOW_OFFER = "COIN_FOR_SHOW_OFFER";

const double LobbyConstant::DEFAULT_TOTAL_BET_MULTIPLIER_FOR_CALCULATING_EXP = 1;

const double LobbyConstant::TUTORIAL_REWARD = 150000;
const double LobbyConstant::GET_PRE_TUTORIAL_REWARD = 100000;

// 2016-04-04: Phuoc:
const int LobbyConstant::ADS_ERROR_LOG_TYPE_UNKNOWN = 0;
const int LobbyConstant::ADS_ERROR_LOG_TYPE_IP_INVALID = -1;

const string LobbyConstant::MESSAGE_UNITY_ADS_OK = "1";
// Toan: chuoi thanh cong nay anh Dat yeu cau phai tra ve la "vc_success"
const string LobbyConstant::MESSAGE_COLONY_ADS_OK = "vc_success";
const string LobbyConstant::MESSAGE_ERROR_IP_INVALID = "Invalid IP";
const string LobbyConstant::MESSAGE_ERROR_INTERNAL_SERVER_ERROR = "Internal Server Error";
const string LobbyConstant::MESSAGE_ERROR_INVALID_USER_ID = "vc_noreward";
const string LobbyConstant::MESSAGE_ERROR_FAIL_TO_CHECK_MD5 = "vc_noreward";
const string LobbyConstant::MESSAGE_ERROR_FAIL_TO_SAVE = "Fail to save to DB";
const string LobbyConstant::MESSAGE_ERROR_TRANSACTION_ID_EXIST = "vc_noreward";
const string LobbyConstant::MESSAGE_ERROR_WRONG_PLATFORM = "Wrong Platform";

// 2016-04-28: Toan
const bool LobbyConstant::DISABLE_ALLOW_GET_PRE_TUTORIAL_REWARD = false;

const bool LobbyConstant::DISABLE_RESET_PASSWORD_FOR_USER_ADMIN = false;
const bool LobbyConstant::ENABLE_RESET_PASSWORD_FOR_USER_ADMIN = true;

const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_UNKNOWN = 0;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_LAUNCH_APP = 1;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_CALL_LOGIN_API = 2;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP = 3;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP_SUCCESSFULLY = 4;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP_FAILED = 5;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_SIGN_UP_INIT_FAILED = 6;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_LOGIN_FAILED = 7;
const int LobbyConstant::USER_FACEBOOK_EVENT_LOG_TYPE_DEAUTHORIZE_APP = 8;

const int LobbyConstant::DEFAULT_NUMBER_OF_BITS_FOR_GENERATING_SECURE_RANDOM_STRING = 256;

const string LobbyConstant::API_COMBINATION_BEAN_NAME_GET_MY_PROFILE = "BeanMyProfile";
const string LobbyConstant::API_COMBINATION_BEAN_NAME_CHECK_COLLECT_COIN = "BeanCheckCollectCoin";
const string LobbyConstant::API_COMBINATION_BEAN_NAME_GET_SPECIAL_OFFER = "BeanSpecialOffer";
const string LobbyConstant::API_COMBINATION_BEAN_NAME_GET_ALL_CONFIG = "BeanAllConfig";
const string LobbyConstant::API_COMBINATION_BEAN_NAME_GET_LINK_GAME = "BeanLinkGame";
const string LobbyConstant::API_COMBINATION_BEAN_NAME_GET_LEVEL_CONFIG = "BeanLevelConfig";
const string LobbyConstant::API_COMBINATION_BEAN_NAME_GET_ALL_LIST_SLOT_GAME_INFO = "BeanAllListSlotGameInfo";
const string LobbyConstant::API_COMBINATION_BEAN_NAME_GET_LIST_BET_SIZE_RESTRICTION = "BeanListBetSizeRestriction";


const string LobbyConstant::API_FEATURE_BEAN_TYPE_DAILY_BONUS_STREAK = "BeanListDailyBonusStreakConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_FREE_COIN_GIFT = "BeanListFreeCoinGiftConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_UNLOCK_BY_LEVEL = "BeanListUnlockFeatureByLevelConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_WHEEL = "BeanListLuckyWheelConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_DAILY_CHALLENGE = "BeanListDailyChallengeConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_BOOSTER = "BeanListBoosterLevelUpBonusConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_MOBILE_SLOT_GAME_CONFIG = "BeanMobileSlotGameConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_MOBILE_SLOT_GAME_PAY_LINE_CONFIG = "BeanMobileSlotGamePaylineConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_CONFIG = "BeanListLuckyBoxConfig";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_MAGIC_ITEM_CONFIG = "BeanListMagicItemConfig";

const int LobbyConstant::PAYMENT_API_VERSION_UNKNOWN = 0;
const int LobbyConstant::PAYMENT_API_VERSION_FACEBOOK = 1;
const int LobbyConstant::PAYMENT_API_VERSION_UNITY = 2;
const int LobbyConstant::PAYMENT_API_VERSION_CORDOVA = 3;
const int LobbyConstant::PAYMENT_API_VERSION_COCOS = 4;

const int LobbyConstant::SPECIAL_OFFER_API_VERSION_UNITY = 0;
const int LobbyConstant::SPECIAL_OFFER_API_VERSION_CORDOVA = 1;

const int LobbyConstant::SCHEDULER_LOG_TYPE_CHECK_SCHEDULER_STATUS_SCHEDULER = 0;
const int LobbyConstant::SCHEDULER_LOG_TYPE_CALCULATE_AVG_PLAY_TIME_SCHEDULER = 1;
const int LobbyConstant::SCHEDULER_LOG_TYPE_GET_GAME_PLAY_HISTORY_DESKTOP_GAME_PLAY_SCHEDULER = 2;
const int LobbyConstant::SCHEDULER_LOG_TYPE_GET_GAME_PLAY_HISTORY_MOBILE_GAME_PLAY_SCHEDULER = 3;
const int LobbyConstant::SCHEDULER_LOG_TYPE_UPDATE_USER_STARDOM_STATISTIC_SCHEDULER = 4;
const int LobbyConstant::SCHEDULER_LOG_TYPE_CALCULATE_GAME_ACCESS_PROCESSED_LOG = 5;
const int LobbyConstant::SCHEDULER_LOG_TYPE_CALCULATE_CCUS_EVERY_60_MINUTES_SCHEDULER = 6;
const int LobbyConstant::SCHEDULER_LOG_TYPE_CALCULATE_CCUS_EVERY_5_MINUTES_SCHEDULER = 7;
const int LobbyConstant::SCHEDULER_LOG_TYPE_DELETE_EXPIRED_USER_SCHEDULER = 8;
const int LobbyConstant::SCHEDULER_LOG_TYPE_CHECK_USER_REJECT_APP_FB_SCHEDULER = 9;
const int LobbyConstant::SCHEDULER_LOG_TYPE_RESET_DAILY_CHALLENGE_SCHEDULER = 10;
const int LobbyConstant::SCHEDULER_LOG_TYPE_PROCESS_SPECIAL_EVENT_DATA_SCHEDULER = 11;

const int LobbyConstant::SCHEDULER_LOG_TYPE_GET_USER_TRANSACTION_LOG_FROM_PROXY_DATABASE_SCHEDULER = 100;
const int LobbyConstant::SCHEDULER_LOG_TYPE_GET_TRANSACTION_HISTORY_FROM_GAME_PLAY_DESKTOP_SCHEDULER = 101;
const int LobbyConstant::SCHEDULER_LOG_TYPE_PROCESS_DATA_MERCHANT_STATISTIC_IN_PROXY_DATABASE_SCHEDULER = 102;
const int LobbyConstant::SCHEDULER_LOG_TYPE_GET_TRANSACTION_HISTORY_FROM_GAME_PLAY_MOBILE_SCHEDULER = 103;
const int LobbyConstant::SCHEDULER_LOG_TYPE_CALCULATE_AND_SEND_EMAIL_STATISTIC_SCHEDULER = 104;
const int LobbyConstant::SCHEDULER_LOG_TYPE_CHECK_COMPANY_LOSS_SCHEDULER = 105;
const int LobbyConstant::SCHEDULER_LOG_TYPE_RESET_COMPANY_LOSS_EACH_QUARTER_SCHEDULER = 106;
const int LobbyConstant::SCHEDULER_LOG_TYPE_RECALCULATE_MERCHANT_STATISTIC = 107;

const int LobbyConstant::SCHEDULER_LOG_TYPE_SYNC_WALLET_PROXY_AND_THIRD_PARTY = 200;

const string LobbyConstant::TRANSACTION_HISTORY_CHANGE_TYPE_RESULT = "Result";
const string LobbyConstant::TRANSACTION_HISTORY_CHANGE_TYPE_FREE_SPIN = "Free Spin";
const string LobbyConstant::TRANSACTION_HISTORY_CHANGE_TYPE_BONUS = "Bonus";
const string LobbyConstant::TRANSACTION_HISTORY_CHANGE_TYPE_GAMBLE = "Gamble";

const int LobbyConstant::BONUS_RTP_RATIO_TYPE_COMEBACK_BONUS_MOBILE = 1;

const int LobbyConstant::MOBILE_GAME_PLAY_TRANSACTION_HISTORY_VERSION_DEFAULT = 0;
const int LobbyConstant::MOBILE_GAME_PLAY_TRANSACTION_HISTORY_VERSION_WITH_FEATURE_BONUS_RTP_RATIO = 1;

const int LobbyConstant::SPECIAL_OFFER_TYPE_LIMITED = 0;

const int LobbyConstant::FACEBOOK_ACTIVATE_TRUE = 1;
const int LobbyConstant::FACEBOOK_ACTIVATE_FALSE = 0;

const string LobbyConstant::ALGORITHM_NAME_IN_PAYLOAD_DATA_OF_DEAUTHORIZATION_FACEBOOK_CALLBACK = "HMAC-SHA256";
const string LobbyConstant::ALGORITHM_FOR_VALIDATE_PAYLOAD_DATA_OF_DEAUTHORIZATION_FACEBOOK_CALLBACK = "HmacSHA256";
const string LobbyConstant::ALGORITHM_FOR_VALIDATE_PAYLOAD_DATA_OF_TRIAL_PAY_CALLBACK = "HmacMD5";
const string LobbyConstant::ALGORITHM_FOR_VALIDATE_PAYLOAD_DATA_OF_ADS_COLONY = "MD5";

const string LobbyConstant::TRIAL_PAY_REQUEST_HEADER_FOR_HMAC_MD5 = "trialpay-hmac-md5";

const int LobbyConstant::ENCODE_METHOD_FOR_VALIDATING_TRIAL_PAY_PAYLOAD = 0;

const int LobbyConstant::ENCODE_METHOD_FOR_VALIDATING_FACEBOOK_SIGNED_REQUEST_PAYLOAD = 1;


// FEATURE CONFIG
const string LobbyConstant::FREE_COIN_GIFT_COIN_REWARD_PREFIX = "free_coin_gift_coin_reward_";
const string LobbyConstant::FREE_COIN_WAITING_TIME_PREFIX = "free_coin_gift_waiting_time_after_collecting_level_";
const string LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE = "unlock_feature_by_level_choose_pay_line";
const string LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE = "unlock_feature_by_level_daily_challenge";
const string LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK = "unlock_feature_by_level_piggy_bank";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_BOOSTER_FACTOR_1 = "booster_level_up_bonus_multiplication_factor1";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_BOOSTER_FACTOR_2 = "booster_level_up_bonus_multiplication_factor2";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_COINS_REWARD = "lucky_box_coin_reward_type1";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_CROWNS_REWARD = "lucky_box_crown_reward_type1";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_LUCKY_WHEELS_REWARD = "lucky_box_spin_of_lucky_wheel_reward_type1";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_PRICE = "lucky_box_buy_and_double_price_type1";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_COINS_REWARD = "lucky_box_coin_reward_type2";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_CROWNS_REWARD = "lucky_box_crown_reward_type2";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_LUCKY_WHEELS_REWARD = "lucky_box_spin_of_lucky_wheel_reward_type2";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_PRICE = "lucky_box_buy_and_double_price_type2";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_COINS_REWARD = "lucky_box_coin_reward_type3";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_CROWNS_REWARD = "lucky_box_crown_reward_type3";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_LUCKY_WHEELS_REWARD = "lucky_box_spin_of_lucky_wheel_reward_type3";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_PRICE = "lucky_box_buy_and_double_price_type3";
const string LobbyConstant::API_FEATURE_BEAN_TYPE_MIN_NUMBER_OF_CONSECUTIVE_VIDEO_VIEW_TO_RECEIVE_MAGIC_ITEM_REWARD = "min_number_of_consecutive_video_view_to_receive_magic_item_reward";

//ADDITIONAL INFO
const string LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_STREAK = "BeanDailyBonusStreak";
const string LobbyConstant::API_BONUS_BEAN_TYPE_FREE_COIN_GIFT = "BeanFreeCoinGift";
const string LobbyConstant::API_BONUS_BEAN_TYPE_REFERENCE_CODE = "BeanReferenceCode";
const string LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_LUCKY_SPIN = "BeanDailyBonusLuckySpin";
const string LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_WHEEL = "BeanDailyBonusWheel";
const string LobbyConstant::API_BONUS_BEAN_TYPE_LUCKY_WHEEL = "BeanLuckyWheel";
const string LobbyConstant::API_BONUS_BEAN_TYPE_LUCKY_BOX = "BeanLuckyBox";
const string LobbyConstant::API_BONUS_BEAN_TYPE_PIGGY_BANK = "BeanPiggyBank";
const string LobbyConstant::API_BONUS_BEAN_TYPE_BOOSTER = "BeanBooster";
const string LobbyConstant::API_BONUS_BEAN_TYPE_COMEBACK_BONUS = "BeanComebackBonusMobile";
const string LobbyConstant::API_BONUS_BEAN_TYPE_MAGIC_ITEM = "BeanMagicItem";
