#pragma once

#include "Manager/LanguageManager.h"
#include "Configs.h"
#include <algorithm>

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define CALL_NATIVE_CROP_AVATAR 1
#else
#define CALL_NATIVE_CROP_AVATAR 0
#endif

/**
* creator: Kiet Duong
* date: 2017-02-08
* file: Defination.h
*/
#pragma region Font Resources
#define FONT_CHINA "fonts/helveticaneue.ttf"
//#define FONT_CHINA "Arial"
#define FONT_VIETNAME "fonts/helveticaneue.ttf"
#define FONT_HelveticaNeue_Thin "fonts/HelveticaNeue-Thin.otf"
#define FONT_HelveticaNeue_Light "fonts/Helvetica-Light.otf"
#define FONT_PassionOne_Black "fonts/PassionOne-Black.ttf"
#define FONT_PassionOne_Bold "fonts/PassionOne-Bold.ttf"
#define FONT_PassionOne_Regular "fonts/PassionOne-Regular.ttf"

#define FONT_BITMAP_LEVELUP "popup/levelup/popup-levelup-font.fnt"
#define FONT_BITMAP_ACTIVED_MAGIC_ITEM_SHOP "popup/shop/activated_shop_font-export.fnt"
#define FONT_BITMAP_COMEBACK_BONUS_MOBILE "popup/comback-bonus/comback_bonus_font-export.fnt"
#define FONT_BITMAP_DAILY_CHALLENGE "popup/daily_challenge/dailychallenge_text-export.fnt"
#define FONT_BITMAP_PIGGY_BANK "popup/piggy_bank/piggy_bank_font.fnt"

#pragma endregion

#pragma region Animation
#define PNG_STAR_EFFECT_SPIN "animation/star_effect_spin.png"
#define PNG_STAR_EFFECT_SPIN_PARTICLE "animation/star_effect_spin.plist"
#pragma endregion

#pragma region Loading Animation
#define PNG_LOADNING_ANIMATION_LOGIN "loading animation/loading_login.png"
#define PLIST_LOADNING_ANIMATION_LOGIN "loading animation/loading_login.plist"

#define PNG_LOADNING_ANIMATION_LOBBY "loading animation/loading-icon.png"
#define PLIST_LOADNING_ANIMATION_LOBBY "loading animation/loading-icon.plist"
#pragma endregion

#pragma region Login Scene Resouces
#define PNG_FRAME_LOGIN_BACKGROUND "login_background"
#define PNG_FRAME_LOGIN_BACK "login_back"
#define PNG_FRAME_LOGIN_BOTTOM_TEXT "login_bottom_text"
#define PNG_FRAME_LOGIN_BUTTON_LOGIN_PP "login_btn_login_pp"
#define PNG_FRAME_LOGIN_GUESS_ICON "login_guess_icon"
#define PNG_FRAME_LOGIN_LOGIN_WITH_FB "login_with_fb"
#define PNG_FRAME_LOGIN_LOGIN_WITH_PP "login_with_pp"
#define PNG_FRAME_LOGIN_LOGO "login_logo"
#define PNG_FRAME_LOGIN_OR "login_or"
#define PNG_FRAME_LOGIN_NOTIFICATION_BG "login_notif_popup"
#define PNG_FRAME_LOGIN_CLOSE_POPUP "login_close_popup"
#pragma endregion

#pragma region Lobby Scene Resouces

#define PNG_CIRCLE_MASK "circleMask.png"

#pragma region Header

#define PNG_HEADER_AVATAR_ICON "header/avatar.png"

#define PLIST_HEADER "header/header.plist"

#define PNG_FRAME_HEADER_START_LEVEL_ICON "header_star_for_level_and_vip_header"
#define PNG_FRAME_HEADER_LEVEL_PROGESS_BAR "header_level"
#define PNG_FRAME_HEADER_LEVEL_MASK_PROGESS_BAR "header_level_mask"

#define PNG_FRAME_HEADER_BUY_COIN_BG "header_bg-buy-coin"
#define PNG_FRAME_HEADER_BUY_CROWN_BG "header_bg-buy-crown"
#define PNG_FRAME_HEADER_FRIEND_BUTTON_HEADER "header_friend"
#define PNG_FRAME_HEADER_HOME_BUTTON_HEADER "header_home"
#define PNG_FRAME_HEADER_SETTINGS_BUTTON_HEADER "header_setting"
#define PNG_FRAME_HEADER_INFO_BUTTON_HEADER "header_info"

#pragma endregion

#pragma region Body

//Slot game info Start **********************
#define PNG_LOADING_BACKGROUND "loading screen/loading_background.png"
#define PNG_LOADING_BAR_BACKGROUND "loading screen/loading-bar-ready.png"
#define PNG_LOADING_BAR_FILL "loading screen/loading-bar-done.png"

#define PNG_LOBBY_BACKGROUND "body/background_high.png"
#define PNG_BODY_GIRL_MODEL "body/model.png"
#define PNG_BODY_DOT_ICON "body/dot.png"
#define PNG_DOWNLOAD_ICON "body/slotGameIcon/btn_download.png"
#define PNG_LOCK_ICON "body/slotGameIcon/btn_lock.png"
#define PNG_PROGRESS_DOWNLOAD_SLOT_TEXT_BG "body/slotGameIcon/progress_bg.png"
#define PNG_PROGRESS_DOWNLOAD_SLOT_BG "body/slotGameIcon/slider_bar_bg.png"
#define PNG_PROGRESS_DOWNLOAD_SLOT "body/slotGameIcon/slider_bar.png"

#define PNG_MASCOT_NOTI_BG "body/mascot_noti_bg.png"
//Slot game info end *************************

#define PLIST_SLOT_GAME_ICONS "body/slotGameIcon/WebGame/gameIcon.plist"

#define PNG_NEZHA_GAME_ICON "body_slotGameIcon_WebGame_40"
#define PNG_GOLDENEGG_GAME_ICON "body_slotGameIcon_WebGame_41"
#define PNG_PHARAOH_GAME_ICON "body_slotGameIcon_WebGame_42"
#define PNG_BOXING_GAME_ICON "body_slotGameIcon_WebGame_43"
#define PNG_ROMANEMPIRE_GAME_ICON "body_slotGameIcon_WebGame_44"
#define PNG_CANDYLICIOUS_GAME_ICON "body_slotGameIcon_WebGame_45"
#define PNG_FRUITILICIOUS_GAME_ICON "body_slotGameIcon_WebGame_46"
#define PNG_KPOP_GAME_ICON "body_slotGameIcon_WebGame_47"
#define PNG_LITTLEMONSTERS_GAME_ICON "body_slotGameIcon_WebGame_48"
#define PNG_MAFIA_GAME_ICON "body_slotGameIcon_WebGame_49"
#define PNG_SHERLOCK_GAME_ICON "body_slotGameIcon_WebGame_50"
#define PNG_MAGICQUEST_GAME_ICON "body_slotGameIcon_WebGame_51"
#define PNG_BIKINIBEACH_GAME_ICON "body_slotGameIcon_WebGame_52"
#define PNG_4BEAUTIES_GAME_ICON "body_slotGameIcon_WebGame_53"
#define PNG_DEEPBLUE_GAME_ICON "body_slotGameIcon_WebGame_54"
#pragma endregion

#pragma region Bottom

#define PNG_BOTTOM_PLIST "bottom/footer.plist"
#define PNG_BOTTOM_NOTI_GREEN "bottom/bt-notification.png"

#define FRAME_BOTTOM_BG "footer_footer-bg"
#define FRAME_BOTTOM_BG_MASK "footer_footer-bg-mask"
#define FRAME_BOTTOM_ICON_BG "footer_footer-icon-bg"
#define FRAME_BOTTOM_LOCK "footer_footer_lock_S"
#define FRAME_BOTTOM_LOCK_MASK "footer_footer_lock_S_mask"

#define FRAME_BOTTOM_FCG_PROGRESS_BG "free_coin_footer-progress-bg"
#define FRAME_BOTTOM_FCG_PROGRESS_BAR "free_coin_footer-progress-bar"
#define FRAME_BOTTOM_FCG_PROGRESS_DIVIDE "free_coin_footer-progress-divide"
#define PARTICLE_FCG "bottom/particle_free_coin_gift.plist"

#define FRAME_BOTTOM_LW_ANIM_FORMAT "lucky_wheel__lucky wheel_1-2%.4i"
#define FRAME_BOTTOM_LS_ANIM_FORMAT "daily_spin_daily_spin%.4i"
#define FRAME_BOTTOM_LB_ANIM_FORMAT "lucky_box__lucky box%.4i"
#define FRAME_BOTTOM_DC_ANIM_FORMAT "daily_challenge____challenge%.4i"
#define FRAME_BOTTOM_PB_ANIM_FORMAT "piggy_bank___piggy%.4i"

#define FRAME_BOTTOM_LW_TEXT "text_footer_lucky_wheel_text"
#define FRAME_BOTTOM_LS_TEXT "text_footer_daily_bonus_spin_text"
#define FRAME_BOTTOM_LB_TEXT "text_footer_lucky_box_text"
#define FRAME_BOTTOM_DC_TEXT "text_footer_daily_challenge_text"
#define FRAME_BOTTOM_PB_TEXT "text_footer_piggy_bank_text"

#pragma endregion

#pragma region Icon

#define PNG_GENERAL_ICON_PLIST "general icon/general_icon.plist"

#define PNG_FRAME_CROWN_SLOT_ICON "general_icon_crown-Slot"
#define PNG_FRAME_INPUT_FIELD_BG "general_icon_input_field_bg"
#define PNG_FRAME_RED_NOTIFICATION "general_icon_red_notification"
#define PNG_FRAME_GOLD_STARDOM "general_icon_stardom-gold"
#define PNG_FRAME_SLIVER_STARDOM "general_icon_stardom-sliver"
#define PNG_FRAME_BRONZE_STARDOM "general_icon_stardom-bronze"
#pragma endregion

#pragma endregion

#pragma region Popup Resources

#define PNG_POPUP_BUTTON_PLIST "popup_button/popup_button.plist"

#define PNG_FRAME_CLOSE_POPUP_BUTTON "popup_button_btn_close"
#define PNG_FRAME_BLUE_POPUP_BUTTON "popup_button_btn_blue"
#define PNG_FRAME_GREEN_POPUP_BUTTON_NEW "popup_button_btn_green_new"
#define PNG_FRAME_GREEN_POPUP_BUTTON "popup_button_btn_green"
#define PNG_FRAME_GREEN_LONG_POPUP_BUTTON "popup_button_btn_green_long"
#define PNG_FRAME_PURPLE_POPUP_BUTTON "popup_button_btn_purple"
#define PNG_FRAME_ADDITION_BUTTON "popup_button_addButton"
#define PNG_FRAME_MINUS_BUTTON "popup_button_minusButton"
#define PNG_FRAME_SWITCH_TAB_BUTTON_ON "popup_button_switch_tab_button_on"
#define PNG_FRAME_SWITCH_TAB_BUTTON_OFF "popup_button_switch_tab_button_off"
#define PNG_FRAME_YELLOW_POPUP_BUTTON "popup_button_btn_yellow"


#pragma region Notification
#define PNG_NOTIFICATION_POPUP_BACKGROUND "popup/notification/background.png"
#define PNG_NOTIFICATIO_POPUP_INFO_ICON "popup/notification/info_icon.png"
#pragma endregion

#pragma region Setting

#define PNG_SETTINGS_POPUP_PLIST "popup/settings/settings.plist"

#define PNG_FRAME_SETTING_POPUP_BACKGROUND "settings_background-option"
#define PNG_FRAME_SETTING_BTN_ON_OFF_ON "settings_btn-on-off_01"
#define PNG_FRAME_SETTING_BTN_ON_OFF_OFF "settings_btn-on-off_02"
#define PNG_FRAME_SETTING_BTN_LOGOUT "settings_logout_button"
#define PNG_FRAME_SETTING_BTN_PINK "settings_pink_button"
#define PNG_FRAME_SETTING_BTN_PRIVACY_POLICY "settings_privacy_policy_background"
#define PNG_FRAME_SETTING_BTN_TERM_OF_SERVICE "settings_term_of_service_background"
#define PNG_FRAME_SETTING_BTN_ISSUE_TYPE "settings_issue_type"
#pragma endregion

#pragma region Shop

#define PNG_SHOP_POPUP_PLIST "popup/shop/shop.plist"

#define PNG_FRAME_SHOP_POPUP_BACKGROUND "shop_background"

#define PNG_FRAME_SHOP_MASK_TOGGLE "shop_maskToggle"

#define PNG_FRAME_SHOP_PANEL_ITEM_COIN "shop_panel_item_coin"
#define PNG_FRAME_SHOP_PANEL_ITEM_CROWN "shop_panel_item_crown"
#define PNG_FRAME_SHOP_PANEL_ITEM_MAGIC_ITEM "shop_panel_item_magic_item"
#define PNG_FRAME_SHOP_PANEL_ITEM_BOOSTER "shop_panel_item_booster"

#define PNG_FRAME_SHOP_WATCH_VIDEO_ICON "shop_watch_video_icon"
#define PNG_FRAME_SHOP_COINS_1 "shop_coins_1"
#define PNG_FRAME_SHOP_COINS_2 "shop_coins_2"
#define PNG_FRAME_SHOP_COINS_3 "shop_coins_3"
#define PNG_FRAME_SHOP_CROWNS_1 "shop_crowns_1"
#define PNG_FRAME_SHOP_CROWNS_2 "shop_crowns_2"
#define PNG_FRAME_SHOP_CROWNS_3 "shop_crowns_3"
#define PNG_FRAME_SHOP_MAGIC_100_BIG_WIN "shop_magic_100_big_win"
#define PNG_FRAME_SHOP_MAGIC_100_BIG_WIN_1 "shop_magic_100_big_win_1"
#define PNG_FRAME_SHOP_MAGIC_100_MEGA_WIN "shop_magic_100_mega_win"
#define PNG_FRAME_SHOP_MAGIC_100_MEGA_WIN_1 "shop_magic_100_mega_win_1"
#define PNG_FRAME_SHOP_MAGIC_DOUBLE_EXP "shop_magic_double_exp"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL "shop_magic_lucky_symbol"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL_1 "shop_magic_lucky_symbol_1"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_SYMBOL_2 "shop_magic_lucky_symbol_2"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_10 "shop_magic_lucky10"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_10_1 "shop_magic_lucky10_1"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_10_2 "shop_magic_lucky10_2"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_20 "shop_magic_lucky20"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_20_1 "shop_magic_lucky20_1"
#define PNG_FRAME_SHOP_MAGIC_LUCKY_20_2 "shop_magic_lucky20_2"
#define PNG_FRAME_SHOP_BOOSTERS "shop_boosters_1"

#define PNG_FRAME_SHOP_BOOSTERS_BTN "shop_bg_btn_buy_shop_booster"
#define PNG_FRAME_SHOP_INFO_BTN "shop_btn_info"
#define PNG_FRAME_SHOP_COIN_BTN "shop_bg_btn_buy_shop_coin"
#define PNG_FRAME_SHOP_MAGIC_ITEM_FREE_BTN "shop_bg_btn_buy_shop_magic_free"
#define PNG_FRAME_SHOP_MAGIC_ITEM_FREE_BTN_SEPARATOR "shop_divisor"
#define PNG_FRAME_SHOP_BOOSTER_ACTIVATED_BOTTOM "shop_booster_activated_bottom"
#define PNG_FRAME_SHOP_BOOSTER_INFO_BG "shop_booster_info_bg"
#define PNG_FRAME_SHOP_MAGIC_ACTIVATED_BOTTOM "shop_magic_activated_bottom"
#define PNG_FRAME_SHOP_MAGIC_INFO_BG "shop_magic_info_bg"

#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_FREE "shop_coins_text_free"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_$0_99 "shop_coins_text_$0_99"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_$1_99 "shop_coins_text_$1_99"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_$4_99 "shop_coins_text_$4_99"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_$9_99 "shop_coins_text_$9_99"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_$19_99 "shop_coins_text_$19_99"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_$49_99 "shop_coins_text_$49_99"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_$99_99 "shop_coins_text_$99_99"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_FREE_COINS "shop_coins_text_free_coins"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_400K "shop_coins_text_400,000"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_880K "shop_coins_text_880,000"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_2M4 "shop_coins_text_2,400,000"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_7M2 "shop_coins_text_7,200,000"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_24M "shop_coins_text_24,000,000"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_70M "shop_coins_text_70,000,000"
#define PNG_FRAME_SHOP_TEXT_COINS_TEXT_200M "shop_coins_text_200,000,000"
#define PNG_FRAME_SHOP_TEXT_CROWNS_TEXT_10_CROWNS "shop_crowns_text_10_crowns"
#define PNG_FRAME_SHOP_TEXT_CROWNS_TEXT_55_CROWNS "shop_crowns_text_55_crowns"
#define PNG_FRAME_SHOP_TEXT_CROWNS_TEXT_120_CROWNS "shop_crowns_text_120_crowns"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_1_HOUR_$4_99 "shop_magic_text_1_hour_$4_99"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_1_SPIN_$0_99 "shop_magic_text_1_spin_$0_99"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_1_SPIN_$1_99 "shop_magic_text_1_spin_$1_99"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_10_SPINS_$1_99 "shop_magic_text_10_spins_$1_99"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_3_SPINS_$0_99 "shop_magic_text_3_spins_$0_99"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_100_BIG_WIN "shop_magic_text_100_big_win"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_100_MEGA_WIN "shop_magic_text_100_mega_win"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_DOUBLE_EXP "shop_magic_text_double_exp"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_LUCKY_SYMBOL "shop_magic_text_lucky_symbol"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_LUCKY_10 "shop_magic_text_lucky10"
#define PNG_FRAME_SHOP_TEXT_MAGIC_TEXT_LUCKY_20 "shop_magic_text_lucky20"
#define PNG_FRAME_SHOP_TEXT_BOOSTERS_TEXT_3_DAYS_$2_99 "shop_boosters_text_3_days_$2_99"
#define PNG_FRAME_SHOP_TEXT_BOOSTERS_TEXT_7_DAYS_$3_99 "shop_boosters_text_7_days_$3_99"
#define PNG_FRAME_SHOP_TEXT_BOOSTERS_TEXT_BOOSTERS "shop_boosters_text_boosters"

#define PNG_SHOP_COIN_ICON "popup/shop/shop_coin_icon.png"
#define PNG_SHOP_CROWN_ICON "popup/shop/shop_crown_icon.png"
#pragma endregion

#pragma region Level Up
#define PNG_LVUP_POPUP_PLIST "popup/levelup/levelup.plist"

#define PNG_FRAME_LVUP_POPUP_BACKGROUND "levelup_LevelUpBG"
#define PNG_FRAME_LVUP_POPUP_TITLE "levelup_LevelUpTitle"
#define PNG_FRAME_LVUP_LIGHTRAY "levelup_lightray"
#define PNG_FRAME_LVUP_STARS "levelup_stars"
#define PNG_FRAME_LVUP_BOOSTER_ICON "levelup_booster_package_icon"
#define PNG_FRAME_LVUP_BOOSTER_ICON_BG "levelup_booster_package_icon_bg"
#define PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_LARGE_BG "levelup_booster_package_multiplier_large_background"
#define PNG_FRAME_LVUP_BOOSTER_MULTIPLIER_SMALL_BG "levelup_booster_package_multiplier_small_background"
#pragma endregion

#pragma region Lucky Box

#define PNG_LUCKY_BOX_PLIST "popup/lucky_box/asset_luckybox.plist"

#define FRAME_LUCKY_BOX_BG "luckybox_background"
#define FRAME_LUCKY_BOX_BUY_AND_DOUBLE_BG "luckybox_buy_and_double_background"
#define FRAME_LUCKY_BOX_CHEST_SILVER "luckybox_silver_chest"
#define FRAME_LUCKY_BOX_CHEST_GOLD "luckybox_gold_chest"
#define FRAME_LUCKY_BOX_CHEST_RED "luckybox_red_chest"
#define FRAME_LUCKY_BOX_LENS_FLARE "luckybox_lens_flare"
#define FRAME_LUCKY_BOX_STAR "luckybox_star"
#define FRAME_LUCKY_BOX_LIGHT_RAY "luckybox_light_ray"
#define FRAME_LUCKY_BOX_STAR_FLARE_GOLD "luckybox_star_flare_gold"
#define FRAME_LUCKY_BOX_STAR_FLARE_WHITE "luckybox_star_flare_white"


#pragma endregion

#pragma region Promotions

#define PNG_PROMOTIONS_PLIST "popup/promotions/promotion_popups.plist"

#define FRAME_STARTER_PACK_BG "starter_pack"
#define FRAME_GET_MORE_COINS_BG "get_more_coins"
#define FRAME_FREE_TO_PLAY_BG "free_to_play"
#define FRAME_PAY_TO_PLAY_BG "pay_to_play"
#define FRAME_SPECIAL_OFFER_BG "special_offer"

#pragma endregion

#pragma region GameSlot-Info
#define PLIST_INFO "popup/info/info_popup.plist"

#define PNG_FRAME_BET_BACKGROUND "info_backgroundChangeBet"
#define PNG_FRAME_INFO_POPUP_BACKGROUND "info_background-info-gameslots"
#define PNG_FRAME_INFO_TOGGLE_OFF "info_ToggleOff"
#define PNG_FRAME_INFO_TOGGLE_ON "info_ToggleOn"
#pragma endregion

#pragma region GameSlot-Unlocked
#define PNG_UNLOCKED_ICON "popup/game-unlocked/popup_UnlockGame_lock.png"
#define PNG_UNLCOKED_POPUP_TITLE "popup/game-unlocked/popup_UnlockGame_title.png"
#pragma endregion
#pragma region Feature-Unlocked

#define PLIST_FEATURE_UNLOCKED "popup/feature-unlocked/feature_unlocked.plist"

#define PNG_FRAME_UFBL_PIGGY_BANK "feature_unlocked_info-piggy-bank"
#define PNG_FRAME_UFBL_PAYLINE "feature_unlocked_info-pay-line"
#define PNG_FRAME_UFBL_DAILY_CHALLENGE "feature_unlocked_info-daily-challenge"
#pragma endregion

#pragma region Profile

#define PLIST_PROFILE "popup/profile/profile.plist"

#define PNG_FRAME_PROFILE_POPUP_BACKGROUND "profile_background"
#define PNG_FRAME_PROFILE_BTN_NAME "profile_btn_username"
#define PNG_FRAME_PROFILE_BTN_AVATAR "profile_btn_ava"
#define PNG_FRAME_PROFILE_FACEBOOK_ICON "profile_facebook_icon"

#pragma endregion

#pragma region Friend-Inbox-Leaderboard

#define PNG_FRIEND_POPUP_BACKGROUND "popup/friend/background.png"
#define PNG_FRIEND_POPUP_FRAME_FOR_CELLS "popup/friend/frame_for_cells.png"

#define PNG_INBOX_ICONS "popup/friend/inbox/inbox_icons.png"
#define PLIST_INBOX_ICONS "popup/friend/inbox/inbox_icons.plist"

#define PNG_FRIEND_TOGGLE_ON "popup/friend/friend/toggle-on-friend.png"
#define PNG_FRIEND_TOGGLE_OFF "popup/friend/friend/toggle-off-friend.png"

#define PNG_LEADERBOARD_TOGGLE_LEFT "popup/friend/leaderboard/leaderboard-switch-button-left.png"
#define PNG_LEADERBOARD_TOGGLE_RIGHT "popup/friend/leaderboard/leaderboard-switch-button-right.png"
#pragma endregion

#pragma region Achievement

#define PNG_ACHIEVEMENT_PLIST "popup/achievement/achievement_plist.plist"

#define PNG_ACHIEVEMENT_POPUP_BACKGROUND "popup/friend/background.png"
#define FRAME_ACHIEVEMENT_CATEGORY_BG "achievement_BGType"
#define FRAME_ACHIEVEMENT_PROGRESS_BG "achievement_achievement_bar"
#define FRAME_ACHIEVEMENT_PROGRESS_BAR "achievement_achievement_bar_filter"
#define FRAME_ACHIEVEMENT_POINT_BG "achievement_point"
#define FRAME_ACHIEVEMENT_FB_ICON "achievement_facebookAvatar"
#define FRAME_ACHIEVEMENT_ICON_FRAME "achievement_BGAvatarAchievement"
#define FRAME_ACHIEVEMENT_STAR_ON "achievement_starcolor"
#define FRAME_ACHIEVEMENT_STAR_OFF "achievement_starNoColor"
#define FRAME_ACHIEVEMENT_BUTTON "achievement_buttonCollectAchievement"
#define FRAME_ACHIEVEMENT_POINT_FRAME "achievement_achievement_BGAchievementPoint"

#pragma endregion

#pragma region ComebackBonusMobile
	
#define PNG_COMEBACK_BONUS_MOBILE_BACKGROUND "popup/comback-bonus/background_comback_bonus.png"
	
#pragma endregion

#pragma region DailyBonusWheel ( Spin Popup )
#define PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_BACKGROUND "dailyBonusWheel_bg-wheel"
#define PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_INNER "dailyBonusWheel_wheel_round_inner"
#define PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_LIGHT "dailyBonusWheel_spin_active_v_light"
#define PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_GEAR "dailyBonusWheel_spin_icon_gear"
#define PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_BTN_SPIN "dailyBonusWheel_btn_spin"

#define PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_BACKGROUND "dailyBonusWheel_bg-result"
#define PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_YELLOW "dailyBonusWheel_star1"
#define PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_WHITE "dailyBonusWheel_starWhileLens"

#pragma endregion

#pragma region DailyBonusStreak

#define PLIST_DAILY_BONUS_STREAK "popup/daily-bonus-streak/daily_streak.plist"
#define PARTICLE_DAILY_BONUS_STREAK "popup/daily-bonus-streak/star_bonus_streak.plist"

#define FRAME_DAILY_BONUS_BG "daily_streak_bg"
#define FRAME_DAILY_BONUS_LOGO "daily_streak_logo"
#define FRAME_DAILY_BONUS_DAY "daily_streak_day"
#define FRAME_DAILY_BONUS_DAY_STREAK "daily_streak_day_streak"
#define FRAME_DAILY_BONUS_DAY_NEXT "daily_streak_day_next"
#define FRAME_DAILY_BONUS_DAY_CHECK "daily_streak_day_check"
#define FRAME_DAILY_BONUS_DAY_SHINY "daily_streak_day_shiny"

#define FRAME_DAILY_BONUS_COIN_1 "daily_streak_coin_1"
#define FRAME_DAILY_BONUS_COIN_2 "daily_streak_coin_2"
#define FRAME_DAILY_BONUS_COIN_3_4 "daily_streak_coin_3_4"
#define FRAME_DAILY_BONUS_COIN_5_6 "daily_streak_coin_5_6"
#define FRAME_DAILY_BONUS_COIN_7 "daily_streak_coin_7"
#define PNG_DAILY_BONUS_MG_ITEM_7 "popup/daily-bonus-streak/day_item_magic_item.png"

#define FRAME_DAILY_BONUS_COIN_NEXT_1 "daily_streak_coin_next_1"
#define FRAME_DAILY_BONUS_COIN_NEXT_2 "daily_streak_coin_next_2"
#define FRAME_DAILY_BONUS_COIN_NEXT_3_4 "daily_streak_coin_next_3_4"
#define FRAME_DAILY_BONUS_COIN_NEXT_5_6 "daily_streak_coin_next_5_6"
#define FRAME_DAILY_BONUS_COIN_NEXT_7 "daily_streak_coin_next_7"
#define PNG_DAILY_BONUS_MG_ITEM_NEXT_7 "popup/daily-bonus-streak/day_item_magic_item_not_pass.png"

#pragma endregion

#pragma region Daily Lucky Spin

#define PLIST_DAILY_LUCKY_SPIN "popup/daily_lucky_spin/daily_lucky_spin.plist"
#define FRAME_DAILY_LUCKY_SPIN_BG "daily_lucky_spin_bg"
#define FRAME_DAILY_LUCKY_SPIN_MASK_REEL "daily_lucky_spin_mask_reel"
#define FRAME_DAILY_LUCKY_SPIN_BG_REEL "daily_lucky_spin_bg_reel"
#define FRAME_DAILY_LUCKY_SPIN_TITLE "daily_lucky_spin_title"

#define FRAME_DAILY_LUCKY_SPIN_INFO_TABLE "daily_lucky_spin_popup_info_table"
#define FRAME_DAILY_LUCKY_SPIN_INFO_TITLE "daily_lucky_spin_popup_info_title"
#define FRAME_DAILY_LUCKY_SPIN_BUTTON_FORMAT "daily_lucky_spin_button_%.2i"

#pragma endregion

#pragma region Daily Challenge

#define PLIST_DAILY_CHALLENGE "popup/daily_challenge/daily_challenge.plist"

#define FRAME_DAILY_CHALLENGE_BG "daily_challenge_bg"
#define FRAME_DAILY_CHALLENGE_ROW_BG "daily_challenge_row_bg"
#define FRAME_DAILY_CHALLENGE_DROP_DOWN "daily_challenge_drop_down"

#define FRAME_DAILY_CHALLENGE_TOTAL_PROGRESS_BG "daily_challenge_progress_bg"
#define FRAME_DAILY_CHALLENGE_TOTAL_PROGRESS_BAR "daily_challenge_progress_full"
#define FRAME_DAILY_CHALLENGE_PROGRESS_BG "daily_challenge_progress_bar_bg"
#define FRAME_DAILY_CHALLENGE_PROGRESS_BAR "daily_challenge_progress_bar"

#define FRAME_DAILY_CHALLENGE_ICON_BIG_WIN "daily_challenge_icon_big_win"
#define FRAME_DAILY_CHALLENGE_ICON_COLLECT "daily_challenge_icon_collect"
#define FRAME_DAILY_CHALLENGE_ICON_LEVEL_UP "daily_challenge_icon_level_up"
#define FRAME_DAILY_CHALLENGE_ICON_MAX_BET "daily_challenge_icon_max_bet"
#define FRAME_DAILY_CHALLENGE_ICON_MEGA_WIN "daily_challenge_icon_mega_win"
#define FRAME_DAILY_CHALLENGE_ICON_RECEIVE_GIFT "daily_challenge_icon_receive_gift"
#define FRAME_DAILY_CHALLENGE_ICON_SEND_GIFT "daily_challenge_icon_send_gift"
#define FRAME_DAILY_CHALLENGE_ICON_SPIN "daily_challenge_icon_spin"
#define FRAME_DAILY_CHALLENGE_ICON_TOTAL_BET "daily_challenge_icon_total_bet"
#define FRAME_DAILY_CHALLENGE_ICON_TOTAL_WIN "daily_challenge_icon_total_win"

#define FRAME_DAILY_CHALLENGE_COLLECT_BUTTON_FORMAT "daily_challenge_collect_%.2i"
#pragma endregion

#pragma region Piggy Bank

#define PLIST_PIGGY_BANK "popup/piggy_bank/piggy_bank.plist"

#define FRAME_PIGGY_BANK_PIG_GLOW "piggy_bank_pig_glow"
#define FRAME_PIGGY_BANK_PIG "piggy_bank_pig"
#define FRAME_PIGGY_BANK_PIG_MASK_BEHIND "piggy_bank_pig_mask_behind"
#define FRAME_PIGGY_BANK_PIG_TAIL "piggy_bank_pig_tail"
#define FRAME_PIGGY_BANK_PIG_COIN_LIGHT_RAY "piggy_bank_light_coin"
#define FRAME_PIGGY_BANK_HAMMER "piggy_bank_hammer"

#define FRAME_PIGGY_BANK_BREAK_PIG_GLOW "piggy_bank_break_pig_glow"
#define FRAME_PIGGY_BANK_BREAK_PIG_HEAD "piggy_bank_break_pig_head"
#define FRAME_PIGGY_BANK_BREAK_PIG_BODY_BEHIND "piggy_bank_break_pig_body_behind"
#define FRAME_PIGGY_BANK_BREAK_PIG_BODY_FRONT_1 "piggy_bank_break_pig_body_front_1"
#define FRAME_PIGGY_BANK_BREAK_PIG_BODY_FRONT_2 "piggy_bank_break_pig_body_front_2"
#define FRAME_PIGGY_BANK_BREAK_FLASH "piggy_bank_break_breaking_flash"
#define FRAME_PIGGY_BANK_BREAK_LIGHT "piggy_bank_break_breaking_light"
#define FRAME_PIGGY_BANK_BREAK_MARK "piggy_bank_break_breaking_mark"
#define FRAME_PIGGY_BANK_BREAK_COIN_BEHIND "piggy_bank_break_coins_behind"
#define FRAME_PIGGY_BANK_BREAK_COIN_FRONT "piggy_bank_break_coins_front"
#pragma endregion

#pragma region Strategy Resources

#pragma region Magic Item Resources

#define PLIST_MAGIC_ITEM "strategy/magic_item/magic_item.plist"

#define PNG_FRAME_MAGIC_ITEM_PINK_BG "magic_item_bg_noti_magic_item_pink"
#define PNG_FRAME_MAGIC_ITEM_YELLOW_BG "magic_item_bg_noti_magic_item_yellow"
#define PNG_FRAME_MAGIC_ITEM_100_WIN_TITLE "magic_item_100_win_noti_text"
#define PNG_FRAME_MAGIC_ITEM_LUCKY_10_TITLE "magic_item_lucky_spin_10_noti_text"
#define PNG_FRAME_MAGIC_ITEM_LUCKY_20_TITLE "magic_item_lucky_spin_20_noti_text"
#define PNG_FRAME_MAGIC_ITEM_LUCKY_SYMBOL_FULL_ICON "magic_item_lucky_symbol_full_icon"
#define PNG_FRAME_MAGIC_ITEM_BG_DOUBLE_EXP_BAR "magic_item_bg_double_exp_bar"
#define PNG_FRAME_MAGIC_ITEM_FLARE_DOUBLE_EXP_BAR "magic_item_flare_double_exp_bar"

#pragma endregion

#pragma endregion

#pragma region Tutorial

#define PNG_TUTORIAL_ARROW "tutorial/arrow.png"

#pragma endregion

#pragma region Storing Key
#define STORING_KEY_USER_NAME_GUESS "user_name_guess"
#define STORING_KEY_PASSWORD_GUESS "password_guess"
#define STORING_KEY_USER_NAME_PLAYPALACE "user_name_pp"
#define STORING_KEY_LOGIN_TOKEN "storing_key_login_token"
#define STORING_KEY_JSESSIONID "storing_key_jsessionid"
#define STORING_KEY_CURRENT_LANGUAGE "current_language"
#define STORING_KEY_CAN_PLAY_BACKGROUND_MUSIC "can_play_background_music"
#define STORING_KEY_CAN_PLAY_SOUND_EFFECT "can_play_sound_effect"
#define STORING_KEY_SHOULD_DONWLOAD_GAME_SLOT "should_download_game_slot_"
#define STORING_KEY_PREVIOUS_CUSTOM_ID_ADCOLONY "previous_custom_id_adcolony"


#define STORING_KEY_TUTORIAL_FIRST_LOGIN "tutorial_first_login"
#define STORING_KEY_TUTORIAL_STEP "tutorial_step"
#define STORING_KEY_TUTORIAL_IS_COMPLETED "tutorial_is_completed"
#pragma endregion

#pragma region Game slots info
#define GAME_SLOT_ID_DEEPBLUE "deepblue"
#define GAME_SLOT_ID_GOLDENEGG "goldenegg"
#define GAME_SLOT_ID_BOXING "boxing"
#define GAME_SLOT_ID_PHARAOH "pharaoh"
#define GAME_SLOT_ID_NEZHA "legendofnezha"
#define GAME_SLOT_ID_ROMANEMPIRE "romanempire"

#define GAME_SLOT_RS_VERSION_DEEPBLUE "2017-05-27-01"
#define GAME_SLOT_RS_VERSION_GOLDENEGG "2017-04-27-01"
#define GAME_SLOT_RS_VERSION_BOXING "2017-04-27-01"
#define GAME_SLOT_RS_VERSION_PHARAOH "2017-04-27-01"
#define GAME_SLOT_RS_VERSION_NEZHA "2017-04-27-01"
#define GAME_SLOT_RS_VERSION_ROMANEMPIRE "2017-04-27-01"
#define GAME_SLOT_RS_VERSION_DEFAULT "2017-04-27-01"

#pragma endregion

#pragma region IAP Keys
#define IAP_COINS_400K "400kcoin"
#define IAP_COINS_800K "800kcoin"
#define IAP_COINS_2M "2mcoin"
#define IAP_COINS_4M "4mcoin"
#define IAP_COINS_8M "8mcoin"
#define IAP_COINS_20M "20mcoin"
#define IAP_COINS_40M "40mcoin"

#define IAP_CROWNS_10 "10crowns"
#define IAP_CROWNS_55 "55crowns"
#define IAP_CROWNS_120 "120crowns"

#define IAP_MAGIC_ITEM_100_BIG_WIN "magic_item_lucky_100_big_win"
#define IAP_MAGIC_ITEM_100_MEGA_WIN "magic_item_lucky_100_mega_win"
#define IAP_MAGIC_ITEM_LUCKY_10 "magic_item_lucky_10"
#define IAP_MAGIC_ITEM_LUCKY_20 "magic_item_lucky_20"
#define IAP_MAGIC_ITEM_DOUBLE_EXP "magic_item_double_exp"
#define IAP_MAGIC_ITEM_LUCKY_SYMBOL "magic_item_lucky_symbol"

#define IAP_BOOSTER_1 "booster1"
#define IAP_BOOSTER_2 "booster2"

#define IAP_LUCKY_BOX_X2_COMMONER "lucky_box_x2_commoner"
#define IAP_LUCKY_BOX_X2_NOBLE "lucky_box_x2_noble"
#define IAP_LUCKY_BOX_X2_KING "lucky_box_x2_king"


#define IAP_LUCKY_WHEEL_P1 "lucky_wheel_1"
#define IAP_LUCKY_WHEEL_P2 "lucky_wheel_2"
#define IAP_LUCKY_WHEEL_P3 "lucky_wheel_3"

#define IAP_PIGGY_BANK_P1 "piggy_bank_1"

#define IAP_SPECIAL_OFFER "specialoffer"
#define IAP_STARTER_PACK "starter_pack"
#define IAP_GET_MORE_COINS "get_more_coins"
#define IAP_FREE_TO_PLAY_P1 "free_to_play_1"
#define IAP_FREE_TO_PLAY_P2 "free_to_play_2"
#define IAP_PAY_TO_PLAY_P1 "pay_to_play_1"
#define IAP_PAY_TO_PLAY_P2 "pay_to_play_2"
#define IAP_PAY_TO_PLAY_P3 "pay_to_play_3"

#pragma endregion

#pragma region Sounds

#define SOUND_BG_LOBBY "sound/background.mp3"
#define SOUND_BG_LUCKY_WHEEL "sound/lucky_wheel_bg.mp3"

#define SOUND_INCREASE_COIN "sound/TotalWin.mp3"
#define SOUND_DECREASE_COIN "sound/failedCoin.mp3"
#define SOUND_OPEN_SHOP "sound/coinCrownPurchase.mp3"
#define SOUND_OPEN_OR_CLOSE_POPUP "sound/popup.mp3"

#define SOUND_COIN_DROP "sound/coin-drop.mp3"
#define SOUND_RECEIVE_COIN "sound/animationCoinReceive.mp3"
#define SOUND_INCLUDE_COIN "sound/Cartoon_sound_effects_pop.mp3"

#define SOUND_DAILY_WHEEL_BONUS_SPIN "sound/spin-sound.mp3"


#define SOUND_LUCKY_WHEEL_START "sound/lucky_wheel/start_lucky_wheel_spin.mp3"
#define SOUND_LUCKY_WHEEL_SPIN "sound/lucky_wheel/spinning_lucky_wheel_v2.mp3"
#define SOUND_LUCKY_WHEEL_STOP "sound/lucky_wheel/stop_lucky_wheel_spin.mp3"

#define SOUND_LUCKY_SPIN_REEL_STOP "sound/lucky_spin/end_reel.mp3"
#define SOUND_LUCKY_SPIN_STOP "sound/lucky_spin/end.mp3"

#define SOUND_LUCKY_BOX_BOUNCE "sound/lucky_box/chest_bounce.mp3"
#define SOUND_LUCKY_BOX_OPEN "sound/lucky_box/chest_open.mp3"
#define SOUND_LUCKY_BOX_SHAKE "sound/lucky_box/chest_shake.mp3"

#define SOUND_MASCOT_NOTIFICATION "sound/mascot_noti.mp3"

#define SOUND_PIGGY_BANK_BREAK_PIG "sound/piggy_bank/break_pig.mp3"
#define SOUND_PIGGY_BANK_BREAK_PIG_2 "sound/piggy_bank/break_pig_2.mp3"
#define SOUNG_PIGGY_BANK_COIN_SHAKE "sound/piggy_bank/coin_shake.mp3"
#define SOUND_PIGGY_BANK_CRACK_PIG "sound/piggy_bank/crack_pig.mp3"
#define SOUND_PIGGY_BANK_FINISH "sound/piggy_bank/finish_piggy_bank.mp3"
#pragma endregion


#pragma region Debug

//#define IS_DEBUG true
#define IS_DEBUG false

#pragma endregion


#pragma region Helper

#define PNG_FRAME_TRANSPARENT "popup_button_transparent"

#pragma endregion

#pragma region Other

#define APLHA_DARK_LAYER 150

#pragma endregion


#define CALLBACK_4(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)

#define ToString(num) cocos2d::StringUtils::toString(num)

#define Language(label, key) LanguageManager::getInstance()->getStringForKeys(label, key)
#define LanguageText(label, key, textKey) LanguageManager::getInstance()->getStringForKeys(label, key, textKey)

#define ToUpper(str) std::transform(str.begin(), str.end(), str.begin(), ::toupper);

#define stoi(str) atoi(str.c_str())
#define stof(str) atof(str.c_str())
#define stol(str) atol(str.c_str())
#define stoll(str) atoll(str.c_str())

#define SAFE_DELETE_VECTOR(vector) { for(auto child : vector) CC_SAFE_DELETE(child); vector.clear(); }
