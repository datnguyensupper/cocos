#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: InfoManager.h, InfoManager.cpp
*/
#include "cocos2d.h"
#include "Info/BetSlotGameInfo.h"
#include "Info/LevelInfo.h"
#include "Info/ServerConfigsInfo.h"
#include "Info/ServerSlotGameInfo.h"
#include "Info/UserBonusCheckInfo.h"
#include "Info/UserInfo.h"
#include "Info/FeatureConfigInfo.h"
#include "Info/FacebookFriendInfo.h"
#include "Info/AchievementInfo.h"
#include "Info/GiftInfo.h"
#include "Info/LeaderboardInfo.h"
#include "Info/DailyChallengeInfo.h"

class AdditionalInfo;

class InfoManager
{
private:
	static InfoManager* s_instance;

	ServerConfigsInfo* serverConfigsInfo;
	UserInfo* userInfo;
	UserBonusCheck* userBonusCheck;
	AdditionalInfo* additionalInfo;
	FacebookFriendInfo *facebookFriendInfo;
	AchievementInfo* achievementInfo;
	DailyChallengeInfo* dailyChallengeInfo;

	bool isGettingListAchievementsFromSV = false;
	std::vector<GiftInfo*> giftInfoList;
	bool isGettingListGiftsFromSV = false;
	std::map<int, BetSlotGameInfo*> betSlotGameInfoMap;
	std::map<int, ServerSlotGameInfo*> serverSlotGameInfoMap; //key = orderId
	std::map<int, LevelInfo*> levelInfoMap; //key = levelId

	//Feature config
	std::vector<StreakConfig*> listDailyBonuStreakConfig;
	std::vector<LuckyWheelRewardConfig> listLuckyWheelRewardConfig;
	std::map<int, DailyChallengeConfig> mapDailyChallengeConfig; //key = freecoingift turn id
	UnlockFeatureByLevelConfig unlockFeatureByLevelConfig; //key = freecoingift turn id
	BoosterConfig boosterConfig; //key = freecoingift turn id
	std::map<std::string, int> mapSlotGameConfig;
	std::map<int, std::vector<PayLineConfig>> mapListPayLineConfig; //key = freecoingift turn id
	LuckyBoxConfig luckyBoxConfig; //key = freecoingift turn id
	MagicItemConfig* magicItemConfig;
public:
	/**
	* 2017-02-13: Kiet: get instance class
	*/
	static InfoManager* getInstance();

	/**
	* 2017-02-13: Kiet: contructor
	*/
	InfoManager();
	/**
	* 2017-02-13: Kiet: destructor 
	*/
	~InfoManager();
	/// <summary>
	/// updateServerConfigsInfo
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateServerConfigsInfo(rapidjson::Value &data);
	ServerConfigsInfo* getServerConfigsInfo() {
		return this->serverConfigsInfo;
	}
	/// <summary>
	/// updateUserInfo
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateUserInfo(rapidjson::Value &data);
	UserInfo* getUserInfo() {
		return this->userInfo;
	}
	void reloadUserInfo(std::function<void(bool isSuccess, UserInfo* result)> callback);
	/// <summary>
	/// updateUserBonusCheck
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateUserBonusCheck(rapidjson::Value &data);
	UserBonusCheck* getUserBonusCheck() {
		return this->userBonusCheck;
	}

	AdditionalInfo* getAdditionalInfo() {
		return this->additionalInfo;
	}
	/// <summary>
	/// reloadAdditionalInfo
	/// </summary>
	/// <param name="callback"></param>
	void reloadAdditionalInfo(std::function<void(bool isSuccess, AdditionalInfo* result)> callback);

	FacebookFriendInfo* getFacebookFriendInfo() {
		return this->facebookFriendInfo;
	}
	void reloadFriendListOnly(std::function<void(bool isSuccess, FacebookFriendInfo* newFbFriendInfo)> callback);
	/// <summary>
	/// reloadAchievementInfo
	/// </summary>
	/// <param name="callback"></param>
	void reloadAchievementInfo(std::function<void(bool isSuccess, AchievementInfo* result)> callback);
	AchievementInfo* getAchievementInfo() {
		return this->achievementInfo;
	}
	/// <summary>
	/// reloadDailyChallengeInfo
	/// </summary>
	/// <param name="callback"></param>
	void reloadDailyChallengeInfo(std::function<void(bool isSuccess, DailyChallengeInfo* result)> callback);
	DailyChallengeInfo* getDailyChallengeInfo() {
		return this->dailyChallengeInfo;
	}

	std::vector<GiftInfo*> getGiftInfoList() {
		return this->giftInfoList;
	}
	/// <summary>
	/// reloadGiftInfoList
	/// </summary>
	/// <param name="callback"></param>
	void reloadGiftInfoList(std::function<void(bool isSuccess, std::vector<GiftInfo*> result)> callback);
	/// <summary>
	/// updateServerSlotGameInfoList
	/// </summary>
	/// <param name="data">data from pp sv</param>
	/// <returns></returns>
	const std::deque<ServerSlotGameInfo*> updateServerSlotGameInfoList(rapidjson::Value &data);
	std::map<int, ServerSlotGameInfo*> getServerSlotGameInfoMap() {
		return this->serverSlotGameInfoMap;
	}
	/// <summary>
	/// update slot game info from PP SV
	/// </summary>
	/// <param name="callback"></param>
	void reloadServerSlotGameInfoList(std::function<void(const std::deque<ServerSlotGameInfo*>& listNewGameUnlocked)> callback);
	/// <summary>
	/// updateBetSlotGameInfoList
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateBetSlotGameInfoList(rapidjson::Value &data);
	std::map<int, BetSlotGameInfo*> getBetSlotGameInfoMap() {
		return this->betSlotGameInfoMap;
	}
	/// <summary>
	/// updateLevelInfoList
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateLevelInfoList(rapidjson::Value &data);
	std::map<int, LevelInfo*> getLevelInfoMap() {
		return this->levelInfoMap;
	}

	//Feature config
	/// <summary>
	/// updateListDailyBonusStreakConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateListDailyBonusStreakConfig(rapidjson::Value &data);
	std::vector<StreakConfig*> getListDailyBonusStreakConfig() {
		return listDailyBonuStreakConfig;
	}

	std::map<int, FreeCoinGiftConfig> mapFreeCoinGiftConfig; //key = freecoingift turn id
	/// <summary>
	/// updateFreecoinGiftConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateFreecoinGiftConfig(rapidjson::Value &data);
	FreeCoinGiftConfig getFreeCoinGiftWithId(int id) {
		return mapFreeCoinGiftConfig[id];
	}
	/// <summary>
	/// updateUnlockFeatureByLevelConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateUnlockFeatureByLevelConfig(rapidjson::Value &data);
	UnlockFeatureByLevelConfig getUnlockFeatureByLevelConfig() {
		return unlockFeatureByLevelConfig;
	}
	/// <summary>
	/// updateListLuckyWheelRewardConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateListLuckyWheelRewardConfig(rapidjson::Value &data);
	std::vector<LuckyWheelRewardConfig> getListLuckyWheelRewardConfig(int id) {
		return listLuckyWheelRewardConfig;
	}
	/// <summary>
	/// updateDailyChallengeConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateDailyChallengeConfig(rapidjson::Value &data);
	std::map<int, DailyChallengeConfig> getDailyChallengeConfig() {
		return mapDailyChallengeConfig;
	}
	/// <summary>
	/// updateBoosterConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateBoosterConfig(rapidjson::Value &data);
	BoosterConfig getBoosterConfig() {
		return boosterConfig;
	}
	/// <summary>
	/// updateSlotGameConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateSlotGameConfig(rapidjson::Value &data);
	int getGameIDByName(const std::string& gameName) const;

	/// <summary>
	/// updatePayLineConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updatePayLineConfig(rapidjson::Value &data);
	std::map<int, std::vector<PayLineConfig>> getMapListPaylineConfig() {
		return mapListPayLineConfig;
	}

	/// <summary>
	/// updateLuckyBoxConfig
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateLuckyBoxConfig(rapidjson::Value &data);
	LuckyBoxConfig getLuckyBoxConfig() {
		return luckyBoxConfig;
	}

	/// <summary>
	/// update magic item config
	/// </summary>
	/// <param name="data">data from pp sv</param>
	void updateMagicItemConfig(rapidjson::Value &data);
	MagicItemConfig * getMagicItemConfig() {
		return magicItemConfig;
	}

	/**
	* 2017-02-18: Kiet: clear map with value is pointer
	*/
	template <typename Key, typename Value>
	void ClearStdMap(std::map<Key, Value*> map);
	/// <summary>
	/// clear vector
	/// </summary>
	template <typename Value>
	void ClearStdVector(std::vector<Value*>& vector);
};
