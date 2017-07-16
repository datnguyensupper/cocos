#include "Manager/LanguageManager.h"
#include "Constant/Defination.h"
#include "Views/IUpdateLanguage.h"
#include "Helper/Helper4Scene.h"
#include "Util/UtilFunction.h"

using namespace std;
USING_NS_CC;
#pragma region init singleton
LanguageManager* LanguageManager::s_instance = nullptr;

LanguageManager* LanguageManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new LanguageManager();
	}
	auto runningScene = Helper4Scene::getRunningScene();
	if (s_instance->currentScene != runningScene) {
		s_instance->currentScene = runningScene;
		s_instance->reset();
	}
	return s_instance;
}
#pragma endregion

LanguageManager::LanguageManager() 
{
    isGetMainLanguageSuccess = false;
    initData();
    
    //load default language
    isGetDefaultLanguageSuccess = false;
    setLanguage4ParseLanguageFail();
}

void LanguageManager::initData(){
    
	int currentIdLanguage = CCUserDefault::getInstance()->getIntegerForKey(STORING_KEY_CURRENT_LANGUAGE);
	SupportLanguage currentLanguage = static_cast<SupportLanguage>(currentIdLanguage);
	this->setCurrentLanguage(currentLanguage);
}

LanguageManager::~LanguageManager()
{
	CC_SAFE_DELETE(s_instance);
}

void LanguageManager::reset()
{
	this->listObjectWillBeClearUpdateLanguage = this->listObjectWillBeClearUpdateLanguageTemp;
	this->listObjectWillBeClearUpdateLanguageTemp.clear();
}

string LanguageManager::getStringForKeys(cocos2d::Label * label, std::string key, std::string key2){
	UtilFunction::setLabelFontByLanguage(label);
    
    
    setLanguage4ParseLanguageFail();
    bool isGetStringFail = false;
    if(isGetMainLanguageSuccess){
        if(document.HasMember(key.c_str()) && document[key.c_str()].HasMember(key2.c_str())){
            return document[key.c_str()][key2.c_str()].GetString();
        }
    }else{
        if(documentDefault.HasMember(key.c_str()) && documentDefault[key.c_str()].HasMember(key2.c_str())){
            return documentDefault[key.c_str()][key2.c_str()].GetString();
        }
    }
    // reload language
    initData();
    return "";
    
}

void LanguageManager::updateCurrentLanguageToCache(SupportLanguage language) {

	this->currentLanguage = language;
	CCUserDefault::getInstance()->setIntegerForKey(STORING_KEY_CURRENT_LANGUAGE, this->currentLanguage);
	cocos2d::CCUserDefault::getInstance()->flush();
}

void LanguageManager::parseLanguageFromJsonString(std::string languageJson) {
    log("start parse language");
    document.Parse<0>("");
    document.Parse<0>(languageJson.c_str());
    log("finish parse language");
    
    if (document.HasParseError()){
        CCLOG("Language file parsing error %i",document.GetParseError());
    }
}

bool LanguageManager::setCurrentLanguage(SupportLanguage language)
{
#if IS_DEBUG
	language = indo;
#endif
	string fileName = "language/en.json";
	switch (language){
	case en:
		fileName = "language/en.json";
		break;
	case cn:
		fileName = "language/cn.json";
		break;
	case tran_cn:
		fileName = "language/cn_tran.json";
		break;
	case vn:
		fileName = "language/vn.json";
		break;
	case my:
		fileName = "language/my.json";
		break;
	case indo:
		fileName = "language/indo.json";
		break;
	default:
		return false;
	}
	this->numberTimeChangeLanguage ++;
	// below we open, read and parse language data file with rapidjson library
	ssize_t nSize = 0;
	const char* buf = (const char*)CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "r", &nSize);
	string content(buf);
	string clearContent = content.substr(0, content.rfind('}') + 1);
	parseLanguageFromJsonString(clearContent);

	if (document.HasParseError()){
        isGetMainLanguageSuccess = false;
        updateCurrentLanguageToCache(SupportLanguage::en);
		setLanguage4ParseLanguageFail();
		return false;
    }else{
        updateCurrentLanguageToCache(language);
        isGetMainLanguageSuccess = true;
        return true;
    }
}

void LanguageManager::pushBackToUpdateLanguageList(IUpdateLanguage* iUpdate, bool isRetainObject)
{
	if (isRetainObject)
	{
		this->listRetainObjectUpdateLanguage.push_back(iUpdate);
	}
	else
	{
		this->listObjectWillBeClearUpdateLanguageTemp.push_back(iUpdate);
	}
}

void LanguageManager::updateLanguageForApp()
{
	for (auto& iUpdate : this->listRetainObjectUpdateLanguage)
	{
		if (iUpdate != nullptr)
		{
			iUpdate->updateAfterChangeLanguage();
		}
	}
	for (auto& iUpdate : this->listObjectWillBeClearUpdateLanguage)
	{
		if (iUpdate != nullptr)
		{
			iUpdate->updateAfterChangeLanguage();
		}
	}
}

std::string LanguageManager::getCurrentLanguageName()
{
	switch (this->currentLanguage)
	{
	case en:
		return ENGLISH_TEXT;
	case cn:
		return CN_TEXT;
	case tran_cn:
		return TAIWAN_TEXT;
	case vn:
		return TIENG_VIET_TEXT;
	case my:
		return MALAY_TEXT;
	case indo:
		return INDO_TEXT;
	default:
		return ENGLISH_TEXT;
	}
}


bool LanguageManager::setLanguage4ParseLanguageFail() {
    if(isGetDefaultLanguageSuccess) return true;
	std::string languageJson = "{'popup_need_level_to_play_game':{'text1':'You need to reach level ','text2':' to play this game.'},'setting_language_lable':{'text':'English'},'setting_logged_with_lable':{'text':'Logged in via : '},'setting_logout_lable':{'text':'Logout'},'setting_login_lable':{'text':'Login'},'setting_game_option_lable':{'text':'Game Options'},'setting_back_ground_music_lable':{'text':'Background Music'},'setting_back_sound_effect_lable':{'text':'Sound Effects'},'setting_language':{'text':'Language'},'setting_ref_lable':{'text':'Reference Code'},'setting_mycode_lable':{'text':'My Code'},'setting_myrefcode_lable':{'text':'My RefCode'},'setting_friend_request_lable':{'text':'Friend Request'},'setting_btn_tearm_lable':{'text':'Terms of Service'},'setting_btn_privacy_lable':{'text':'Privacy Policy'},'setting_version_lable':{'text':'Version'},'setting_languages':{'eng':'English','cn':'简体','taiwan':'繁體','vn':'Tiếng Việt','malay':'B-Malay','indo':'B-Indonesia'},'footer_collect_lable':{'text':'Collect'},'footer_collect_time_bonus_in_lable':{'text':'Time bonus in'},'footer_achievement_lable':{'text':'Achievements'},'popup_profile_to_level_up_lable':{'text':' XP\\nto level up'},'footer_gift_lable':{'text':'Gifts'},'header_profile_tooltip':{'text':'Profile'},'header_invite_tooltip':{'text':'Invite friends'},'header_sendgift_tooltip':{'text':'Send gift'},'header_shop_tooltip':{'text':'Shop'},'header_stardom_tooltip':{'text':'Stardom'},'header_Level':{'text':'Lv.'},'header_recent_winner_text':{'text1':'Recent','text2':'Winner'},'popup_shop_transaction_cancelled':{'text':'Transaction Cancelled'},'popup_achievement_title':{'text':'ACHIEVEMENTS'},'popup_achievement_total_achievement_point':{'text':'ACHIEVEMENT POINTS'},'popup_achievement_group_title_general':{'text':'General'},'popup_achievement_group_title_game':{'text':'Game'},'popup_achievement_group_title_social':{'text':'Social'},'popup_profile_logo':{'text':'Profile'},'popup_profile_level':{'text':'Level'},'popup_profile_rank':{'text':'Rank'},'popup_profile_MaximumCoins':{'text':'Maximum Coins'},'popup_profile_PlayedSince':{'text':'Played Since'},'popup_profile_btn_SendFreeGift':{'text':'Send Free Gift'},'popup_profile_btn_SendCoins':{'text':'Send Coins'},'popup_profile_Slot_NumberofJackpot':{'text':'Number of Jackpot'},'popup_profile_Slot_Win':{'text':'WIN: '},'popup_profile_Slot_BiggestWin':{'text':'Biggest Win'},'popup_profile_Slot_TotalSpin':{'text':'Total Spin'},'popup_profile_Slot_NetProfit':{'text':'Net Profit'},'popup_profile_Blackjack_NumberofBlackjack':{'text':'Number of Blackjack'},'popup_profile_Blackjack_PlayedHand':{'text':'Played Hand'},'popup_profile_Blackjack_BiggestWin':{'text':'Biggest Win'},'popup_profile_Blackjack_Win':{'text':'Win'},'popup_profile_Blackjack_NetProfit':{'text':'Net Profit'},'popup_profile_Change_Avatar':{'title':'Change Avatar','success':'Change Avatar Successfully!','fail':'Change Avatar Failed!'},'popup_profile_Blackjack_MaxWinInaRow':{'text':'Max Win In a Row'},'popup_gift_leaderboard':{'text':'Leaderboard'},'popup_gift_friends':{'text':'Friends'},'popup_gift_inbox':{'text':'Inbox'},'popup_gift_inbox_empty':{'text':'Your inbox is empty!'},'popup_gift_error_oop':{'text':'Warning'},'popup_gift_error_message':{'text':'Please login with your facebook account!'},'popup_gift_select':{'text':'Please choose at least one friend!'},'popup_gift_success':{'text':'Success'},'popup_gift_send_free_gift_success':{'text':'Send free gift successfully!'},'popup_gift_invite_success':{'text':'Invite successfully!'},'popup_gift_info':{'text':' You can get 100,000 coins'},'popup_gift_warning':{'text':'Warning'},'popup_gift_warning_message':{'text':' Please try again later'},'popup_gift_accept_success':{'text':'Accepted gift successfully!'},'popup_gift_anonymous':{'text':'Anonymous'},'popup_edit_name':{'title':'Change name','fail':'Please type name','success':'Change name successfully!','reachLimit':'Maximum change name reached'},'popup_reference':{'title':'My Reference Code','title_noti':'Reference Code','already_send':'Already sent gift from reference code','not_exist':'Reference code not exists!','max':'Reference code reached max time!','own_code':'Can not enter your own reference code!','success':'Reference code updated!','confirm':'Confirm'},'popup_change_language':{'fail':'Fail!','success':'Successfully!'},'popup_invite_description':{'text':'If you send invitation to your friend, you can get $700 per friend'},'popup_invite_tab_FriendtoSendGift':{'text':'Friends to Send Gift'},'popup_invite_tab_AllFriends':{'text':'All Friends'},'popup_invite_FriendsSelected':{'text':'Friends selected'},'popup_invite_btn_UnSelectAll':{'text':'Un select All'},'popup_invite_btn_SelectAll':{'text':'Select All'},'popup_invite_btn_SendGift':{'text':'SEND GIFT'},'popup_invite_btn_Invite':{'text':'INVITE'},'popup_invite_error_non_select':{'text':'Please choose at least one friend!'},'popup_invite_tab_GameFriend':{'text':'Game Friends'},'popup_askfriend_description':{'text':'You Can Receive Up To 3 Keys Per Day'},'popup_askfriend_btn_label':{'text':'Ask Friend'},'popup_SendGift_Description':{'text':'If you send a gift to your friend, you can get $700'},'popup_shop_btn_BuyNow':{'text':'BUY NOW'},'popup_stardom_level':{'text':'Level'},'popup_stardom_BankRoll':{'text':'Bankroll'},'popup_stardom_BiggestWin':{'text':'Biggest Win'},'popup_stardom_JackPot':{'text':'Jackpot'},'popup_stardom_label_Player':{'text':'PLAYER'},'popup_stardom_player_AllPlayers':{'text':'All Players'},'popup_stardom_player_Friends':{'text':'Friends'},'popup_stardom_player_BankRoll':{'text':'Bankroll'},'popup_stardom_player_NetProfit':{'text':'Net Profit'},'popup_stardom_player_BiggestWin':{'text':'Biggest Win'},'popup_stardom_player_Jackpot':{'text':'Jackpot'},'popup_stardom_player_Ranking':{'text':'Ranking'},'popup_stardom_player_Players':{'text':'Players'},'popup_stardom_player_Coins':{'text':'Coins'},'popup_stardom_player_PlayTogether':{'text':'Play Together'},'popup_stardom_player_Game':{'text':'Game'},'popup_secretgift_description':{'text1':'*WARNING!','text2':' Keys purchased from key Shop Will Never Expire'},'popup_smallbox_description':{'text':'3 Keys Are Required to Open the Box'},'popup_inbox_btn_Accept':{'text':'ACCEPT'},'popup_inbox_btn_Accept_SendGift':{'text':'ACCEPT & SEND GIFT'},'popup_inbox_btn_SendKey':{'text':'Send key'},'popup_inbox_btn_Accept_SendGift_All':{'text':'Accept & Send gift All'},'popup_inbox_Message_Gift':{'text1':'I send ','text2':' coins to you! Good luck!'},'popup_inbox_message_free_magic_item_watching_video':{'text1':'Congratulation! You have received a free magic item for watching ','text2':' videos'},'popup_inbox_message_default_gift':{'text':'Congratulation! You have received a gift'},'popup_inbox_Message_FreeGift':{'text1':'I send a gift up to ','text2':' coins to you! Good luck!'},'popup_inbox_Message_SystemGift':{'text1':'You have received ','text2':' coins. Good luck!'},'popup_inbox_Message_Requestkey':{'text':'Dear, Send Me One Key, Please!'},'popup_inbox_Message_Promote':{'text1':'Promotion bonus for inviting friend (','text2':') coins'},'popup_inbox_Message_Vip':{'text1':'Congratulation! You have received VIP gift. Your reward is ','text2':' coins'},'popup_inbox_Friend_Benefit':{'text1':'Congratulation! You have received ','text2':' coins for inviting your friend'},'popup_inbox_Reference_Code':{'text1':'Congratulation! You have received reference gift. Your reward is ','text2':' coins'},'popup_inbox_Top_Player_Gift':{'text1':'Congratulation! You are top player. Your reward is ','text2':' coins'},'popup_inbox_Message_Vip_Up':{'text':'Congratulate to Vip Up!'},'popup_shop_Vip':{'text':'Vip'},'popup_shop_Standard':{'text':'Standard'},'popup_shop_Mobile':{'text':'Mobile'},'menu_setting_Label':{'text':'SETTINGS'},'menu_setting_GraphicQuality':{'text':'Graphic Quality'},'menu_setting_Music':{'text':'Music'},'menu_setting_Sound':{'text':'Sound'},'menu_setting_Language':{'text':'Language'},'popup_voucher_description':{'text1':'You have been awarded ','text2':' coins'},'popup_warning_switch_to_app_fb':{'text':'Please switch to facebook app to purchase!'},'popup_warning_switch_to_app_fb_to_invite':{'text':'Please switch to facebook app to invite!'},'popup_warning_switch_to_app_fb_to_send_gift':{'text':'Please switch to facebook app to send gift!'},'popup_warning_switch_to_app_fb_to_share':{'text':'Please switch to facebook app to share!'},'share_facebook_levelup':{'name':'Level Up','caption':'New Level Achieved in PlayPalace!','info':'has successfully leveled up to Level'},'share_facebook_game_unlock':{'name':'Game Unlock','caption':'New Games Unlocked in PlayPalace!','info':'has successfully unlocked new games in PlayPalace!'},'popup_user_level_up':{'text1':'Level ','text2':' Achieved','text3':'Here is ','text4':' Free Coins For You'},'popup_user_game_unlock':{'text1':'Level ','text2':' Achieved','text3':' is now unlocked & available','text4':'Unlock','text5':'Crowns','text6':'Unlock By Crown','text7':'Unlock this game with ','text8':' crowns?','text9':' Booster Level Times','text10':' Lucky Spin'},'footer_collect_coin':{'text':'Collect'},'footer_time_bonus':{'text':'Time bonus in'},'main_menu_not_support_region':{'text':'Your region is currently not supported'},'body_slot_game_coming_soon':{'text':'Coming soon'},'popup_inbox_button_accept_all':{'text':'Accept All'},'ok':{'text':'OK'},'pay':{'text':'Pay'},'copy':{'text_copy':'Copy','text_copied':'Copied'},'add':{'text_add':'Add','text_added':'Added'},'loginFacebook':{'text':'Login Facebook'},'collect':{'text':'Collect'},'collectAndShare':{'text':'Collect & Share'},'cancel':{'text':'Cancel'},'buyNow':{'text':'Buy now'},'goToLobby':{'text':'GO TO LOBBY'},'send':{'text':'Send'},'voucher_has_expired':{'text':'Voucher has expired'},'voucher_has_already_been_redeemed':{'text':'Voucher has already been redeemed'},'you_have_unlocked_a_new_game':{'text':'You have unlocked a new game'},'crown_purchase_successfully':{'text':'Crown purchase successfully. Please wait for our game server to process this payment'},'coin_purchase_successfully':{'text':'Coin purchase successfully. Please wait for our game server to process this payment'},'new_game_tile':{'text':'New content coming soon'},'new_game_description':{'text':'We are working hard to bring you new content'},'cant_get_image':{'text':'You can not get this image!'},'download_remove':{'message_download':' will start downloading shortly. Meanwhile you can play other available games. A Wi-Fi connection is recommended to download the slot, 3G/LTE charges may apply.','info_remove':'Remove a game anytime by pressing and holding it down','download':'DOWNLOAD','remove':'REMOVE','stop':'STOP','continue':'CONTINUE','wait_to_download':'Please wait while game data is downloaded. ','download_soon':' will be downloaded soon!','downloading':'Downloading resources for ','cancle_download':'. Do you want to cancel this download?','update':'UPDATE','message_update':'The resource of this game needs to be updated. Do you want to update now?','message_remove':'Game will start deleting shortly.','delete_failed':'Delete game failed.'},'exit_game':{'title':'Exit confirm','message':'Do you want to stop playing?'},'not_enough_space':{'text':'Your device does not have enough storage space.'},'login_some_where':{'text':'Your account has been logged in from another device.\\nClick ok to reload.'},'cant_get_data_FB':{'text':'Cannot get data from facebook.\\nPlease try again later.'},'FB_token_expired':{'text':'Your facebook token has been expired.\\nPlease reload app.'},'purchased':{'approved':'Purchase approved!','reward':'Your reward is: ','payment_accepted':'Your payment is accepted!','support':'If you do not receive coins, please contact admin for support!','not_available':'Product is not available right now!'},'free_coin':{'received':'Received','play_fail':'You cannot play video at this time. Please try again later.','title':'Free coin'}}";


    std::replace(languageJson.begin(),languageJson.end(),'\'','"');

    documentDefault.Parse<0>(languageJson.c_str());
    if (documentDefault.HasParseError()){
//        updateCurrentLanguageToCache(SupportLanguage::en);
		CCLOG("setLanguage4ParseLanguageFail!");
		return false;
	}else {
        //		updateCurrentLanguageToCache(SupportLanguage::en);
        CCLOG("setLanguage4ParseLanguageSuccess!");
        isGetDefaultLanguageSuccess = true;
        return true;
	}
}
