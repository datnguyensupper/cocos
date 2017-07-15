#pragma once
#include "BaseItemInfo.h"
#include "Constant/LobbyConstant.h"
#include "Constant/Defination.h"
#include "Util/UtilFunction.h"
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: UserInfo.h
*/

using namespace rapidjson;
using namespace std;
struct BeanComebackBonusGift
{
	long userId;
	double coinBeforeCollection;
	double coinAfterCollection;
	double bonusCoin;
	long timestampLastLogin;
	int status;
	long numberOfInactiveDay;
	double bonusCoinPerDay;

	void updateDataFromValue(rapidjson::Value &beanData)
	{
		if (beanData.IsNull()) return;

		if (beanData.HasMember(JSONFieldConstant::USER_ID.c_str()))
		{
			this->userId = beanData[JSONFieldConstant::USER_ID.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::COIN_BEFORE_COLLECTION.c_str()))
		{
			this->coinBeforeCollection = beanData[JSONFieldConstant::COIN_BEFORE_COLLECTION.c_str()].GetDouble();
		}
		if (beanData.HasMember(JSONFieldConstant::COIN_AFTER_COLLECTION.c_str()))
		{
			this->coinAfterCollection = beanData[JSONFieldConstant::COIN_AFTER_COLLECTION.c_str()].GetDouble();
		}
		if (beanData.HasMember(JSONFieldConstant::BONUS_COIN.c_str()))
		{
			this->bonusCoin = beanData[JSONFieldConstant::BONUS_COIN.c_str()].GetDouble();
		}
		if (beanData.HasMember(JSONFieldConstant::TIMESTAMP_LAST_LOGIN.c_str()))
		{
			this->timestampLastLogin = beanData[JSONFieldConstant::TIMESTAMP_LAST_LOGIN.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::Status.c_str()))
		{
			this->timestampLastLogin = beanData[JSONFieldConstant::Status.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::NUMBER_OF_INACTIVE_DAY.c_str()))
		{
			this->timestampLastLogin = beanData[JSONFieldConstant::NUMBER_OF_INACTIVE_DAY.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::BONUS_COIN_PER_DAY.c_str()))
		{
			this->timestampLastLogin = beanData[JSONFieldConstant::BONUS_COIN_PER_DAY.c_str()].GetDouble();
		}
	}
};
struct Slot {
	double biggestWin;
	double netProfit;
	int numOfBonus;
	int numOfFreeSpin;
	int numOfJackpot;
	float percentWin;
	int totalSpin;
	int win;

	void updateDataFromValue(rapidjson::Value &beanData)
	{
		if (beanData.IsNull()) return;

		if (beanData.HasMember(JSONFieldConstant::BIGGEST_WIN.c_str()))
		{
			this->biggestWin = beanData[JSONFieldConstant::BIGGEST_WIN.c_str()].GetDouble();
		}
		if (beanData.HasMember(JSONFieldConstant::NET_PROFIT.c_str()))
		{
			this->netProfit = beanData[JSONFieldConstant::NET_PROFIT.c_str()].GetDouble();
		}
		if (beanData.HasMember(JSONFieldConstant::NUMBER_OF_BONUS.c_str()))
		{
			this->numOfBonus = beanData[JSONFieldConstant::NUMBER_OF_BONUS.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::NUMBER_OF_FREESPIN.c_str()))
		{
			this->numOfFreeSpin = beanData[JSONFieldConstant::NUMBER_OF_FREESPIN.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::NUMBER_OF_JACKPOT.c_str()))
		{
			this->numOfJackpot = beanData[JSONFieldConstant::NUMBER_OF_JACKPOT.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::PERCENT_WIN.c_str()))
		{
			this->percentWin = beanData[JSONFieldConstant::PERCENT_WIN.c_str()].GetFloat();
		}
		if (beanData.HasMember(JSONFieldConstant::TOTAL_SPIN.c_str()))
		{
			this->totalSpin = beanData[JSONFieldConstant::TOTAL_SPIN.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::WIN.c_str()))
		{
			this->win = beanData[JSONFieldConstant::WIN.c_str()].GetInt();
		}
	}
};
class UserInfo : public BaseItemInfo
{
public:
#pragma region fields

	ppEnum::LoginAndInitSSFrom loginFrom;
	string facebookUID;
	string accessToken;
	double coin;
	double exp;
	double exp_bar;
	long rank;
	long level;
	int role;
	int status;
	int allowSendFreeGift;
	int allowGift;
	bool local;
	int vip;
	string urlFullAvatar;
	long serverStartTimestamp;

	long timeLeftSendFreeGift;
	long timeLeftSendCoin;
	long timeLeftRequestSecretKey;
	string userName;
	bool validateActivated;

	string email;

	bool testUser;
	long preferLanguage;

	int webBackground;

	// 2016-02-16: Phuoc:
	long crown;
	long achievementPoint;

	double purchaseAmount;
	string loginToken;

	string extraInfo;

	bool allowGetLoginCount;
	long timestampLastLogin;
	long loginCount;

	int blueStone;
	int greenStone;
	int purpleStone;
	int secretKey;
	int box;

	int checkLoginInDay;
	BeanComebackBonusGift beanComebackBonusGift;
	Slot slot;

	bool firstLogin;
	bool allowGetFirstLogin;

	int timeChangeName;

	bool allowPlayTutorial;
	bool allowGetTutorialSpinReward;
	bool allowGetPreTutorialReward;

	long remainingExp;

	bool allowGetTimestampLastLogin;

#pragma endregion

	/**
	* 2017-02-13: Kiet: update user info from values from PP Server
	*/
	void updateUserInfoByValue(rapidjson::Value &beanData)
	{
//		if (beanData == NULL)
//		{
//			return;
//		}

		this->updateBaseItemInfoByValue(beanData);
		if (beanData.HasMember(JSONFieldConstant::Slot.c_str()))
		{
			this->slot.updateDataFromValue(beanData[JSONFieldConstant::Slot.c_str()]);
		}
		if (beanData.HasMember(JSONFieldConstant::FB_UID.c_str()))
		{
			this->facebookUID = beanData[JSONFieldConstant::FB_UID.c_str()].GetString();
		}
		if (beanData.HasMember(JSONFieldConstant::Access_Token.c_str()))
		{
			this->accessToken = beanData[JSONFieldConstant::Access_Token.c_str()].GetString();
		}
		if (beanData.HasMember(JSONFieldConstant::Level.c_str()))
		{
			this->level = beanData[JSONFieldConstant::Level.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::Coin.c_str()))
		{
			this->coin = beanData[JSONFieldConstant::Coin.c_str()].GetDouble();
		}
		if (beanData.HasMember(JSONFieldConstant::Rank.c_str()))
		{
			this->rank = beanData[JSONFieldConstant::Rank.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::Exp_Bar.c_str()))
		{
			this->exp_bar = beanData[JSONFieldConstant::Exp_Bar.c_str()].GetDouble();
		}
		if (beanData.HasMember(JSONFieldConstant::Role.c_str()))
		{
			this->role = beanData[JSONFieldConstant::Role.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::Status.c_str()))
		{
			this->status = beanData[JSONFieldConstant::Status.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::FreeGift.c_str()))
		{
			this->allowSendFreeGift = beanData[JSONFieldConstant::FreeGift.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::Gift.c_str()))
		{
			this->allowGift = beanData[JSONFieldConstant::Gift.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::Type.c_str()))
		{
			this->vip = beanData[JSONFieldConstant::Type.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::URL_FULL_AVATAR.c_str()))
		{
			this->urlFullAvatar = beanData[JSONFieldConstant::URL_FULL_AVATAR.c_str()].GetString();
		}
		if (beanData.HasMember(JSONFieldConstant::USER_NAME.c_str()))
		{
			this->userName = beanData[JSONFieldConstant::USER_NAME.c_str()].GetString();
		}
		if (beanData.HasMember(JSONFieldConstant::IS_ACTIVATED.c_str()))
		{
			this->validateActivated = beanData[JSONFieldConstant::IS_ACTIVATED.c_str()].GetBool();
		}
		if (beanData.HasMember(JSONFieldConstant::TEST_USER.c_str()))
		{
			this->testUser = beanData[JSONFieldConstant::TEST_USER.c_str()].GetBool();
		}
		if (beanData.HasMember(JSONFieldConstant::Email.c_str()))
		{
			this->email = beanData[JSONFieldConstant::Email.c_str()].GetString();
		}
		if (beanData.HasMember(JSONFieldConstant::PREFER_LANGUAGE.c_str()))
		{
			this->preferLanguage = beanData[JSONFieldConstant::PREFER_LANGUAGE.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::WEB_BACKGROUND.c_str()))
		{
			this->webBackground = beanData[JSONFieldConstant::WEB_BACKGROUND.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::SERVER_START_TIMESTAMP.c_str()))
		{
			this->serverStartTimestamp = beanData[JSONFieldConstant::SERVER_START_TIMESTAMP.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::LOGIN_TOKEN.c_str()))
		{
			this->loginToken = beanData[JSONFieldConstant::LOGIN_TOKEN.c_str()].GetString();
		}
		if (beanData.HasMember(JSONFieldConstant::TIME_LEFT_SEND_FREE_GIFT.c_str()))
		{
			this->timeLeftSendFreeGift = beanData[JSONFieldConstant::TIME_LEFT_SEND_FREE_GIFT.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::TIME_LEFT_SEND_COIN.c_str()))
		{
			this->timeLeftSendCoin = beanData[JSONFieldConstant::TIME_LEFT_SEND_COIN.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::TIME_LEFT_REQUEST_SECRET_KEY.c_str()))
		{
			this->timeLeftRequestSecretKey = beanData[JSONFieldConstant::TIME_LEFT_REQUEST_SECRET_KEY.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::PURCHASE_AMOUNT.c_str()))
		{
			this->purchaseAmount = beanData[JSONFieldConstant::PURCHASE_AMOUNT.c_str()].GetDouble();
		}
		/*if (beanData.HasMember(JSONFieldConstant::EXTRA_INFO.c_str()))
		{
			this->extraInfo = beanData[JSONFieldConstant::EXTRA_INFO.c_str()].GetString();
		}*/
		if (beanData.HasMember(JSONFieldConstant::LOGIN_COUNT.c_str()))
		{
			this->loginCount = beanData[JSONFieldConstant::LOGIN_COUNT.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::COMEBACK_BONUS_GIFT.c_str()))
		{
			this->beanComebackBonusGift.updateDataFromValue(beanData[JSONFieldConstant::COMEBACK_BONUS_GIFT.c_str()]);
		}
		if (beanData.HasMember(JSONFieldConstant::BLUE_STONE.c_str()))
		{
			this->blueStone = beanData[JSONFieldConstant::BLUE_STONE.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::GREEN_STONE.c_str()))
		{
			this->greenStone = beanData[JSONFieldConstant::GREEN_STONE.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::PURPLE_STONE.c_str()))
		{
			this->purpleStone = beanData[JSONFieldConstant::PURPLE_STONE.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::KEY.c_str()))
		{
			this->secretKey = beanData[JSONFieldConstant::KEY.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::BOX.c_str()))
		{
			this->box = beanData[JSONFieldConstant::BOX.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::CHECK_LOGGED_IN_IN_DAY.c_str()))
		{
			this->checkLoginInDay = beanData[JSONFieldConstant::CHECK_LOGGED_IN_IN_DAY.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::FIRST_LOGIN.c_str()))
		{
			this->firstLogin = beanData[JSONFieldConstant::FIRST_LOGIN.c_str()].GetBool();
			if (this->firstLogin) {
				cocos2d::UserDefault::getInstance()->setBoolForKey((STORING_KEY_TUTORIAL_FIRST_LOGIN + ToString(id)).c_str(), firstLogin);
				cocos2d::UserDefault::getInstance()->flush();
			}
		}
		if (beanData.HasMember(JSONFieldConstant::CROWN.c_str()))
		{
			this->crown = beanData[JSONFieldConstant::CROWN.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::ACHIEVEMENT_POINT.c_str()))
		{
			this->achievementPoint = beanData[JSONFieldConstant::ACHIEVEMENT_POINT.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::TIME_CHANGE_NAME.c_str()))
		{
			this->timeChangeName = beanData[JSONFieldConstant::TIME_CHANGE_NAME.c_str()].GetInt();
		}
		if (beanData.HasMember(JSONFieldConstant::ALLOW_PLAY_TUTORIAL.c_str()))
		{
			this->allowPlayTutorial = beanData[JSONFieldConstant::ALLOW_PLAY_TUTORIAL.c_str()].GetBool();
		}
		if (beanData.HasMember(JSONFieldConstant::ALLOW_GET_TUTORIAL_SPIN_REWARD.c_str()))
		{
			this->allowGetTutorialSpinReward = beanData[JSONFieldConstant::ALLOW_GET_TUTORIAL_SPIN_REWARD.c_str()].GetBool();
		}
		if (beanData.HasMember(JSONFieldConstant::ALLOW_GET_PRE_TUTORIAL_REWARD.c_str()))
		{
			this->allowGetPreTutorialReward = beanData[JSONFieldConstant::ALLOW_GET_PRE_TUTORIAL_REWARD.c_str()].GetBool();
		}
		if (beanData.HasMember(JSONFieldConstant::REMAINING_EXP.c_str()))
		{
			this->remainingExp = beanData[JSONFieldConstant::REMAINING_EXP.c_str()].GetInt64();
		}
		if (beanData.HasMember(JSONFieldConstant::TIMESTAMP_LAST_LOGIN.c_str()))
		{
			this->timestampLastLogin = beanData[JSONFieldConstant::TIMESTAMP_LAST_LOGIN.c_str()].GetInt64();
		}
	}
	/// <summary>
	/// get avatar URL
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <returns></returns>
	std::string getAvatarURL(int width = 320, int height = 320) const {
		return UtilFunction::getAvatarUrl(
				static_cast<USER_ROLE>(this->role),
				this->facebookUID,
				this->urlFullAvatar,
				width,
				height
		);
	}
};

struct LevelUpInfo {
	long currentLevel;
	long newLevel;

	int64_t coinReward;
	int64_t crownReward;
	/// <summary>
	/// init level up info
	/// </summary>
	/// <param name="currentLevel"></param>
	/// <param name="newLevel"></param>
	/// <param name="coinReward"></param>
	/// <param name="crownReward"></param>
	LevelUpInfo(long currentLevel,
		long newLevel,
		int64_t coinReward,
		int64_t crownReward) {
		this->currentLevel = currentLevel;
		this->newLevel = newLevel;
		this->coinReward = coinReward;
		this->crownReward = crownReward;
	}
};
