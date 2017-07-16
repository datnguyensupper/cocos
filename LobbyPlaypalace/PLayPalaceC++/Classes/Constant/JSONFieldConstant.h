#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: JSONFieldConstant.h, JSONFieldConstant.cpp
*/
#include "cocos2d.h"
using namespace std;
class JSONFieldConstant
{
public:
	static const string RESULT_CODE;
	static const string BEAN_TYPE;
	static const string TS_CREATED;
	static const string TS_LAST_MODIFIED;
	static const string BEAN;
	static const string ID;
	static const string INFO;
	static const string NAME;
	static const string PARENT_ID;
	static const string OWNER_ID;
	static const string LIST_SIZE;
	static const string TOTAL_PAGE;
	static const string MEMBER;

	static const string RELOAD;
	static const string TIMESTAMP_RELOAD;

	static const string EXTRA_INFO;

	static const string STRING_NAME;
	static const string INT;
	static const string LONG;
	static const string DOUBLE;
	static const string BIG_INTEGER;

	static const string RTP;
	static const string BONUS_PROBABILITY;
	static const string WIN_IN_FREE_SPIN_PROBABILITY;
	static const string RATIO_RTP_DECREASE_NO_BONUS;
	static const string MAX_TOTAL_BET_MUL_BEYOND_LOSING;
	static const string DISTRIBUTION_INDEX;
	static const string EXPONENTIAL;


	static const string FB_UID;
	static const string FB_URL;
	static const string FB_Name;
	static const string FB_Token;
	static const string Access_Token;
	static const string From_FB_UID;
	static const string To_FB_UID;
	static const string CHECK_TIME_LEFT;
	static const string TOTAL_TIME_LEFT;
	static const string FREE_GIFT_TIME_LEFT;
	static const string GIFT_TIME_LEFT;

	static const string IP;
	static const string Email;
	static const string Type;
	static const string Multi;
	static const string Status;
	static const string Delay;
	static const string Amount;
	static const string Exp;
	static const string Exp_Bar;
	static const string Coin;
	static const string Rank;
	static const string Level;
	static const string Role;
	static const string FreeGift;
	static const string Gift;
	static const string HoldEm;
	static const string Slot;

	static const string SecretBox;
	static const string SecretKey;
	static const string SecretKeyToday;
	static const string SecretGreenStone;
	static const string SecretBlueStone;
	static const string SecretPurpleStone;
	static const string KEY_REQUIRE;
	static const string MAX_BOX;
	static const string MAX_BLUE_STONE;
	static const string MAX_GREEN_STONE;
	static const string MAX_PURPLE_STONE;


	static const string BENEFIT_TYPE;
	static const string VIP_TYPE;
	static const string VALUE;

	static const string LEVEL_ID;
	static const string FACTOR;
	static const string COIN_REWARD;
	static const string CROWN_REWARD;
	static const string LUCKY_WHEEL_REWARD;
	static const string KEY_REWARD;

	static const string GAME_TYPE;
	static const string GAME_NAME;
	static const string PLATFORM;
	static const string COUNT;
	static const string USER_ID;
	static const string USER_TYPE;

	static const string NUMBER_OF_KEY_PER_SECRET_GIFT;
	static const string COIN_REWARD_SECRET_BOX;
	static const string BLUE_STONE_REWARD_SECRET_BOX;
	static const string GREEN_STONE_REWARD_SECRET_BOX;
	static const string PURPLE_STONE_REWARD_SECRET_BOX;

	static const string BIGGEST_WIN;
	static const string NET_PROFIT;
	static const string NUMBER_OF_JACKPOT;
	static const string NUMBER_OF_BONUS;
	static const string NUMBER_OF_FREESPIN;
	static const string PERCENT_WIN;
	static const string TOTAL_SPIN;
	static const string WIN;

	static const string ORDER_ID;
	static const string GAME_ID;
	static const string MAX_LINE;
	static const string MIN_LINE;
	static const string PROMOTE_GAME;
	static const string JACKPOT;
	static const string MIN_LEVEL;

	static const string LEVEL_BONUS;
	static const string NUMBER_OF_FRIEND;
	static const string COIN_PER_FRIEND;
	static const string TOTAL_COIN;
	static const string BOX;
	static const string VIP_BENEFIT;

	static const string FACEBOOK_PRODUCT_ID;
	static const string ENABLE;
	static const string FACEBOOK_PRODUCT_LINK;
	static const string BASE_COIN;
	static const string ADDITIONAL_PERCENT;
	static const string PRICE;
	static const string CURRENCY;

	static const string NUMBER_OF_WIN;
	static const string NUMBER_OF_PLAY;
	static const string MAX_WIN_IN_A_ROW;
	static const string SPECIAL_FIELD;

	static const string BLACKJACK;
	static const string IS_LOCAL;

	static const string URL_FULL_AVATAR;
	static const string USER_NAME;
	static const string IS_ACTIVATED;
	static const string TEST_USER;

	static const string SERVER_START_TIMESTAMP;

	static const string FACEBOOK_UID;
	static const string COIN_BONUS;
	static const string CURRENT_WALLET;
	static const string TIMESTAMP_LAST_QUERY;

	static const string DISPLAY_NAME;
	static const string IS_RESET_PASSWORD;

	static const string TIME_LEFT_SEND_FREE_GIFT;
	static const string TIME_LEFT_SEND_COIN;
	static const string TIME_LEFT_REQUEST_SECRET_KEY;

	static const string VERSION;

	static const string PURCHASE_INFO_LIST;
	static const string PURCHASE_AMOUNT;

	static const string USER_INFO;

	static const string TOKEN;
	static const string TIMESTAMP_FIRST_REDEMPTION;
	static const string LINK_WEB;
	static const string LINK_FB;
	static const string EXPIRED_AFTER;

	static const string WALLET_TRANSACTION_ID;

	static const string TIMESTAMP_START_TIME;

	static const string SUCCESS;
	static const string WALLET_RESULT_CODE;
	static const string MER_USER_ID;

	static const string PREFER_LANGUAGE;
	static const string WEB_BACKGROUND;

	static const string PICTURE_URL;
	static const string CAPTION;

	static const string TS_LAST_START;
	static const string TS_LAST_END;
	static const string TS_CURRENT_START;

	static const string PACKAGE_TYPE;
	static const string PAYMENT_TYPE;

	static const string LOGIN_TOKEN;

	static const string LOGIN_COUNT;

	static const string JACKPOT_VALUE;

	static const string PAYMENT_ID;
	static const string ACTIONS;
	static const string DISPUTES;

	static const string FB_LANGUAGE;
	static const string PP_LANGUAGE;

	static const string COIN_BEFORE_COLLECTION;
	static const string COIN_AFTER_COLLECTION;
	static const string BONUS_COIN;
	static const string BONUS_PERCENT;
	static const string TIMESTAMP_LAST_LOGIN;
	static const string NUMBER_OF_INACTIVE_DAY;
	static const string BONUS_COIN_PER_DAY;

	static const string COMEBACK_BONUS_GIFT;


	//29-10-2015:Toan
	static const string PRODUCT;
	static const string PRODUCT_TITLE;
	static const string PRODUCT_DESCRIPTION;
	static const string PLURAL_TITLE;
	static const string PRODUCT_CURRENCY;
	static const string PRODUCT_AMOUNT;
	static const string EXPIRED_TIME;
	static const string AMOUNT_BONUS;
	static const string KEY_BONUS;
	static const string DIAMOND_BONUS;
	static const string CROWN_BONUS;
	static const string TIME_TO_SHOW_OFFER;
	static const string OFFER_TYPE;

	//30-10-2015:Toan
	static const string VIP_SHOP;
	static const string BONUS_COINS_PER_DAY;
	static const string BONUS_INVITATION_GIFT_PER_FRIEND;
	static const string VIP_BADGE_ON_PROFILE;
	static const string DAILY_SECRET_KEY_GIFT_KEY;
	static const string DAILY_SECRET_KEY_GIFT_BOX;
	static const string HOURLY_TIMER_BONUS_REDUCTION;
	static const string FAN_PAGE_REWARDS;
	static const string XP_BOOSTER;
	static const string ACCUMULATED_TOTAL_PRICE;
	static const string INSTANT_BONUS_COINS;

	static const string BLUE_STONE;
	static const string GREEN_STONE;
	static const string PURPLE_STONE;
	static const string KEY;

	// 2015-11-11: Toan
	static const string CHECK_LOGGED_IN_IN_DAY;

	static const string FIRST_LOGIN;

	static const string PAYMENT_SOURCE_ID;

	static const string CROWN;
	static const string COIN_PURCHASE_BONUS;

	// 2016-2-17: Ty
	static const string NOTIFICATION_EMAIL_ADDRESS;
	static const string NOTIFICATION_EMAIL_TYPE;


	static const string PREMIUM_TYPE;
	static const string MIN_CROWN;
	static const string IS_UNLOCKED;
	static const string AVAILABLE;


	// 2016-2-18 : Toan
	static const string GROUP_TYPE;
	static const string ACHIEVEMENT_TYPE;
	static const string ACHIEVEMENT_POINT_REWARD;
	static const string ACHIEVEMENT_GOAL;

	static const string ACHIEVEMENT_POINT;
	static const string ACHIEVEMENT_ID;

	// 2016-2-20 : Ty
	static const string MAINTENANCE_SCHEDULER_MESSAGE;
	static const string MAINTENANCE_SCHEDULER_LIST_EMAIL;
	static const string MAINTENANCE_SCHEDULER_TITLE;
	static const string MAINTENANCE_SCHEDULER_IS_SENT;
	static const string MAINTENANCE_SCHEDULER_EXTRA_INFO;
	static const string MAINTENANCE_SCHEDULER_TIME;
	static const string MAINTENANCE_SCHEDULER_TIME_TO;

	//2016-03-05: Ty
	static const string TIME_CHANGE_NAME;

	static const string REAL_TIME_ACHIEVEMENT_LIST;

	static const string CURRENT_STATUS;
	static const string IS_COMPLETE;
	static const string IS_COLLECTED;

	static const string CATEGORY_ID;
	static const string CATEGORY_NAME;
	static const string SUB_CATEGORY_ID;
	static const string SUB_CATEGORY_NAME;
	static const string STAR;

	static const string ALLOW_PLAY_TUTORIAL;
	static const string ALLOW_GET_TUTORIAL_SPIN_REWARD;
	static const string ALLOW_GET_PRE_TUTORIAL_REWARD;

	static const string REMAINING_EXP;

	static const string IS_ONLY_ONE_ACHIEVEMENT;


	// 2016-04-26: Toan
	static const string BET_SIZE;
	static const string BET_SIZE_PER_LINE;
	static const string PAYLINE;
	static const string LEVEL_RESTRICTION;

	static const string FIRST_NAME;
	static const string LAST_NAME;
	static const string FULL_NAME;

	static const string EMAIL_ID;
	static const string TEMPLATE_ID;

	static const string API_TOKEN;

	static const string DAILY_STREAK;
	static const string CAN_COLLECT;
	static const string WAITING_TIME;

	static const string NEXT_COIN_REWARD;

	static const string PACKAGE_PRICE;

	static const string STRATEGY_TYPE;

	static const string MESSAGE;
	static const string MESSAGE_EN;
	static const string MESSAGE_VN;
	static const string MESSAGE_CN;
	static const string MESSAGE_TW;
	static const string MESSAGE_MY;
	static const string MESSAGE_INDO;
	static const string FROM_USER_ID;
	static const string TO_USER_ID;

	static const string REFERENCE_CODE;
	static const string NUMBER_OF_TIME_REFERENCE_CODE_IS_USED;
	static const string REFEREE_REFERENCE_CODE;

	static const string REEL_VALUES;

	static const string REMAINING_SPIN;

	static const string SPIN_OF_LUCKY_WHEEL_REWARD;
	static const string REMAINING_LUCKY_BOX_TYPE1;
	static const string REMAINING_LUCKY_BOX_TYPE2;
	static const string REMAINING_LUCKY_BOX_TYPE3;

	static const string BOOSTER_LEVEL_UP_BONUS_DURATION_TIME_REWARD;

	static const string REMAINING_TIME_OF_BOOSTER_LEVEL_UP_BONUS;

	static const string PRODUCT_TYPE;

	static const string PIGGY_BANK_LIMIT;

	static const string PIGGY_BANK_COIN;

	static const string NUMBER_OF_TIMES_COLLECT_FREE_COIN_GIFT;

	static const string SLOT_TOTAL_BET;

	static const string DAILY_CHALLENGE_TASK_GOAL;
	static const string DAILY_CHALLENGE_TASK_TYPE;

	static const string DAILY_CHALLENGE_TASK_CONFIG_ID;
	static const string CURRENT_PROGRESS;

	static const string DAILY_CHALLENGE_TASK_LIST;


	static const string NUMBER_OF_COME_BACK_TIME;
	static const string INCREASED_PERCENTAGE_OF_EXP;
	static const string SPECIAL_RTP_RATIO;
	static const string NUMBER_OF_SPIN_RECEIVE_BENEFIT;

	static const string MAX_BET_PER_LINE;
	static const string MAX_PAYLINE;

	static const string MAGIC_ITEM_100_PERCENT_MEGA_WIN_REWARD;
	static const string MAGIC_ITEM_LUCKY_SPIN_TYPE_1_REWARD;
	static const string MAGIC_ITEM_LUCKY_SPIN_TYPE_2_REWARD;
	static const string MAGIC_ITEM_DOUBLE_EXP_DURATION_TIME_REWARD;
	static const string MAGIC_ITEM_LUCKY_SYMBOL_DURATION_TIME_REWARD;

	static const string RTP_RATIO_GUEST_ACCOUNT;
	static const string RTP_RATIO_PLAYPALACE_ACCOUNT;
	static const string RTP_RATIO_FACEBOOK_ACCOUNT;

	static const string ACTIVE_MAGIC_ITEM_TYPE;

	static const string REMAINING_PACKAGE_OF_MAGIC_ITEM_100_PERCENT_BIG_WIN;
	static const string REMAINING_SPIN_OF_MAGIC_ITEM_100_PERCENT_BIG_WIN;
	static const string REMAINING_PACKAGE_OF_MAGIC_ITEM_100_PERCENT_MEGA_WIN;
	static const string REMAINING_SPIN_OF_MAGIC_ITEM_100_PERCENT_MEGA_WIN;

	static const string REMAINING_PACKAGE_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_1;
	static const string REMAINING_SPIN_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_1;

	static const string REMAINING_PACKAGE_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_2;
	static const string REMAINING_SPIN_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_2;

	static const string REMAINING_PACKAGE_OF_MAGIC_ITEM_DOUBLE_EXP;
	static const string REMAINING_TIME_OF_MAGIC_ITEM_DOUBLE_EXP;
	static const string TIMESTAMP_START_MAGIC_ITEM_DOUBLE_EXP;
	static const string MAGIC_ITEM_DOUBLE_EXP_DURATION_TIME;

	static const string REMAINING_PACKAGE_OF_MAGIC_ITEM_LUCKY_SYMBOL;
	static const string REMAINING_TIME_OF_MAGIC_ITEM_LUCKY_SYMBOL;
	static const string TIMESTAMP_START_MAGIC_ITEM_LUCKY_SYMBOL;
	static const string MAGIC_ITEM_LUCKY_SYMBOL_DURATION_TIME;


	static const string REMAINING_AMOUNT;
	static const string REMAINING_TIME;

	static const string RANGE_OF_LOGIN_COUNT;
	static const string LOGIN_COUNT_WEB;

	static const string REMAINING_QUANTITY;

	static const string REMAINING_SCRATCH_CARD;
	static const string CURRENT_SCRATCH_CARD_INFO;
	static const string NEXT_SCRATCH_CARD_INFO;
	static const string SCRATCH_CARD_REWARD;

	static const string CARD_TYPE;
	static const string CARD_LEVEL;
	static const string LEAF_REWARD;
	static const string LEAF_UPGRADE_REQUIREMENT;

	static const string FLIP_CARD_VALUE;
	static const string REMAINING_WAITING_TIME;
	static const string SHOW_FLIP_CARD_DETAIL;
	static const string CAN_REDEEM_FLIP_CARD_REWARD;
	static const string LEAF;

	static const string FEEDBACK_STATUS;

	static const string PASSWORD;

	static const string ENABLE_TOURNAMENT;

	static const string TOURNAMENT_ID;
	static const string TOTAL_WIN;

	static const string SLOT_GAME_INFO_ID;
};