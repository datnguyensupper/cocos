#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: NetworkManager.h, NetworkManager.cpp
*/
#include "cocos2d.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "json/writer.h"
#include "json/document.h"

using namespace rapidjson;


struct NetworkFailProcessInfo {
	int core_result_code = 0;
	bool isReload = false;
	std::string errorMessage = "";
	int64_t ts_reload = 0;

};

class NetworkManager
{
private:
	static NetworkManager* s_instance;
	std::string loginToken = "";
	std::string session = "";
	std::vector<cocos2d::network::HttpRequest* > requestQueue;
#pragma region core methods
	/// <summary>
	/// send next request in queue
	/// </summary>
	void sendRequestInQueue();
	/**
	* 2017-02-06: Kiet: post method.
	*
	* @param data (example: data = "username=kiet@gmail.com&password=12345678" for login_web)
	* @param callback callback after get response and passed handleSpecialErrorResultCode
	*/
	void post(
		const std::string &url,
		std::string &data,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr,
		float timeoutIn = 10000.0f,
		bool isAddLoginToken = true
	);

	/**
	* 2017-02-06: Kiet: post method.
	*
	* @param data (example: data = "username=kiet@gmail.com&password=12345678" for login_web)
	* @param callback callback after get response and passed handleSpecialErrorResultCode
	*/
	void post(
		const std::string &url,
		std::string &data,
		std::function<void(int coreResultCode, bool isSuccess, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		float timeoutIn = 10000.0f,
		bool isAddLoginToken = true
	);
	/**
	* post multipart method.
	*
	* @param formData (map data - formData["loginToken"] = 1234125 )
	* @param dataFieldName: field name of "data need to send" on server side
	* @param dataBinary: data need to send
	* @param callback callback after get response and passed handleSpecialErrorResultCode
	*/
	void postMultipart(
		const std::string &url,
		const std::map<std::string, std::string> &formData,
		const std::string &dataFieldName, const char* dataBinary, size_t dataLen,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr,
		float timeoutIn = 10000.0f
	);
	/**
	* 2017-02-06: Kiet: get method.
	*
	* @param data (example: data = "?username=kiet@gmail.com&password=12345678" for login_web)
	* @param callback callback after get response and passed handleSpecialErrorResultCode
	*/
	void get(
		const std::string &url,
		std::string &data,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr,
		float timeoutIn = 10000.0f,
		bool isAddLoginToken = true
	);
	/**
	* 2017-02-06: Kiet: method called after post or get completed
	* method parse response to Document and call callbacks
	*/
	void onHttpRequestCompleted(
		cocos2d::network::HttpClient* sender,
		cocos2d::network::HttpResponse* response,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-02-09: Kiet: get session
	*/
	void getSession(cocos2d::network::HttpResponse* response);
	/**
	* 2017-02-06: Kiet: handle error when request
	* @param errorCode error code receive after request example 400, 404, 500,...
	*/
	void handleErrorRequest(
		cocos2d::network::HttpResponse* response,
		const std::function<void(std::string result)> callbackError,
		const std::function<void(std::string result)> callbackTimeOut
	);
	/**
	* 2017-02-06: Kiet:handle spceial error result code from server ( not onLoginTouched, onLoginTouched in another local, ... )
	*/
	bool handleSpecialErrorResultCode(
		int coreResultCode
	);

	/**
	* 2017-02-06: Kiet:redirect to google play store or app store to update game
	*/
	void gotoPlayStore2UpdateGame();
#pragma endregion
public:
#pragma region init signleton
	/**
	* 2017-02-06: Kiet: get instance class
	*/
	static NetworkManager* getInstance();
	/**
	* 2017-02-27: Kiet: destructor
	*/
	~NetworkManager();

	/**
	* 2017-02-09: Kiet: set login token ( call after apis login )
	*/
	void setLoginToken(const std::string &tsLogin)
	{
		this->loginToken = tsLogin;
	}
#pragma endregion

#pragma region Requests
	/**
	* 2017-02-06: Kiet: get redirect url of facebook picture
	*/
	void getRedirectFBPicture(
		const std::string &rootUrl,
		std::function<void(std::string redirectUrl)> callback
	);

#pragma region LoginScene
	/**
	* 2017-02-06: Kiet: call API /user/login to login Facebook Account
	*/
	void loginFB(
		const std::string &accessToken,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-02-06: Kiet: call API /user/login_web to login PP acount
	*/
	void loginPPAcount(
		const std::string &username,
		const std::string &password,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-02-13: Kiet: call API user/authorize to authorize PP acount after login
	*/
	void authorizePPAccount(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* 2017-02-08: Kiet: call API user/sign_up to signup pp account
	*/
	void signUpPlayPalaceAccount(
		const std::string &username,
		const std::string &password,
		const std::string &referenceCode,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* 2017-02-08: Kiet: call API user/local/onSignUpTouched to generate Guess acount
	*/
	void generateGuessAcount(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* 2017-02-08: Kiet: call API user/local/onLoginTouched to login Guess acount
	*/
	void loginGuessAcount(
		const std::string &usernameLocal,
		const std::string &passwordLocal,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* 2017-02-08: Kiet: call API user/requestResetPassword to request reset pass
	*/
	void resetPassword(
		const std::string &username,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

#pragma endregion

#pragma region InitSessionScene
	/**
	* 2017-02-13: Kiet: call API user/getAllData to get all data ( like server configs, list game slot, ... )
	*/
	void getAllData(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/// <summary>
	/// Dat : call api /user/featureConfig/getAll get Info:
	/// DAILY_BONUS_STREAK, FREE_COIN_GIFT, UNLOCK_BY_LEVEL, LUCKY_WHEEL, 
	/// DAILY_CHALLENGE, BOOSTER, MOBILE_SLOT_GAME_CONFIG, SLOT_GAME_PAY_LINE_CONFIG, 
	/// LUCKY_BOX_CONFIG, 
	/// </summary>
	/// <param name="callback"></param>
	/// <param name="callbackError"></param>
	/// <param name="callbackTimeOut"></param>
	void getAllFeatureConfig(
		std::function<void(int coreResultCode, bool isSuccess, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback
	);
	/// <summary>
	/// Dat : call api /user/freeCoinGift/collect 
	/// to collect freecoin gift
	/// </summary>
	/// <param name="callback"></param>
	/// <param name="callbackError"></param>
	/// <param name="callbackTimeOut"></param>
	void collectFreeCoinGift(
		std::function<void(int coreResultCode, bool isSuccess, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback
	);
	/**
	* 2017-02-13: Kiet: call API user/getAllData to get all data ( like server configs, list game slot, ... )
	*/
	void getAdditionalInfo(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-02-20: Kiet: call API user/getAdditionalInfo to get all user data
	*/
	void getUserInfo(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-02-13: Kiet: call API user/me/game/slot/listAll to get all data slot game
	*/
	void getGameSlotList(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

#pragma endregion

#pragma region SettingPopup
	/**
	* 2017-02-09: Kiet: call API user/logout to get leaderboard
	*/
	void logout(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

#pragma endregion

#pragma region Friend + Leaderboard + Inbox popup
	/**
	* 2017-02-09: Kiet: call API user/gift/getAll to get leaderboard
	*/
	void getAllGift(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-02-09: Kiet: call API user/gift/accept to accept gift with gift id
	*/
	void acceptGift(
		long giftId,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-02-09: Kiet: call API user/gift/acceptAll to accept all gift
	*/
	void acceptGiftAll(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-03-10: Kiet: call API user/friendList to get friend list
	*/
	void getFriendList(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-03-10: Kiet: call API user/gift/sendToUserList to ask server send gift for user list
	*/
	void sendGiftToUserList(
		std::vector<std::string> ids,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* 2017-03-10: Kiet: call API user/me/inviteFriends to ask server send gift for user list
	*/
	void sendInviteFriend(
		std::vector<std::string> facebookUIDs,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	
	/**
	* 2017-02-09: Kiet: call API user/me/getLeaderboard to get leaderboard
	*/
	void getLeaderboard(
		int type,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Purchase
	/**
	* 2017-03-01: Kiet: call API user/payment/android/verify to verify android IAP
	*/
	void verifyAndroidPayment(
		const std::string &receipt,
		const std::string &receiptCipheredPayload,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
    
    /**
     *  Dat: call API user/payment/ios/verify to verify android IAP
     */
    void verifyIOSPayment(
      const std::string &receipt,
      const std::string &appStoreReceipt,
      std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
      std::function<void(std::string result)> callbackError = nullptr,
      std::function<void(std::string result)> callbackTimeOut = nullptr
      );
#pragma endregion

#pragma region User
	/**
	* call API user/updateAvatar to upload avatar
	*/
	void uploadAvatar(
		const char* data, size_t len,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* call API user/updateName to update Name
	*/
	void updateName(
		const std::string& newName,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* call API user/inputReferenceCode to upload reference code
	*/
	void submitReferenceCode(
		const std::string& referenceCode,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Achievement
	/**
	* Get achievement list
	* @param callback
	*/
	void getAchievementList(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* Collect specific achievement
	* @param achievementId id of achievement
	* @param callback success
	*/
	void collectAchievement(
		int id,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Daily Bonus Wheel
	/**
	* Collect daily bosnus wheel
	*/
	void collectDailyBonusWheel(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Comeback Bonus Mobile
	/**
	* 2017-04-12: Kiet: call API /user/comebackBonusMobile/collect to collect comeback bonus mobile
	*/
	void collectComebackBonusMobile(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Tutorial
	/**
	* Redeem pre tutorial reward
	* @param callback
	*/
	void redeemPreTutorialReward(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* Redeem tutorial reward
	* @param callback
	*/
	void redeemTutorialReward(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);

	/**
	* Finish tutorial request
	* @param callback
	*/
	void finishTutorial(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Daily Bonus Streak
	/**
	* Collect daily bosnus wheel
	*/
	void collectDailyBonusStreak(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Lucky Wheel
	/**
	* Spin lucky wheel
	* @param callback
	*/
	void spinLuckyWheel(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* Buy lucky wheel using crown
	* @param packageType: package type
	* @param callback
	*/
	void buyLuckyWheelUsingCrow(
		const std::string& packageType,
		const std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)>& callback,
		const std::function<void(std::string result)>& callbackError = nullptr,
		const std::function<void(std::string result)>& callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Lucky Daily Spin
	/**
	* Collect daily bonus lucky spin
	* @param callback
	*/
	void collectDailyBonusLuckySpin(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Daily Challenge
	/**
	* get Daily Challenge Info
	* @param callback function
	*/
	void getDailyChallengeInfo(
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
	/**
	* Collect daily challenge
	* @param callback
	*/
	void collectDailyChallenge(
		const std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)>& callback,
		const std::function<void(std::string result)>& callbackError = nullptr,
		const std::function<void(std::string result)>& callbackTimeOut = nullptr
	);
#pragma endregion

#pragma region Shop
	/**
	* 2017-04-12: Kiet: call API /user/magicItem/activate to activate magic item
	*/
	void activateMagicItem(
		int magicItemType,
		std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback,
		std::function<void(std::string result)> callbackError = nullptr,
		std::function<void(std::string result)> callbackTimeOut = nullptr
	);
#pragma endregion

#pragma endregion

};
