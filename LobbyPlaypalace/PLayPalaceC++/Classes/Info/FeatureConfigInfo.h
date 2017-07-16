#pragma once
#include "BaseItemInfo.h"
#include "Helper/Helper4ParseJSON.h"
#include "Constant/LobbyConstant.h"

/**
* creator: Dat
* date: 2017-02-13
* file: ServerConfigsInfo.h
*/

struct StreakConfig
{
	std::string name;
	double info; // coin reward

	/// <summary>
	/// Dat: update unlock feature by level info from values
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateStreakInfoByValue(rapidjson::Value &data) {

		name = data[JSONFieldConstant::NAME.c_str()].GetString();
		info = atof(static_cast<std::string>(data[JSONFieldConstant::VALUE.c_str()].GetString()).c_str());
	}
};

struct FreeCoinGiftConfig {
	int coinReward = 0;
	int waitingTime = 0;

};

class UnlockFeatureByLevelConfig {
public:
	int choosePayLine = 0;
	int dailyChallenge = 0;
	int piggyBank = 0;

	/**
	* Dat: update unlock feature by level info from values
	*/
	void updateUnlockFeatureByLevelInfoByValue(rapidjson::Value &data) {
//		if (data == NULL) {
//			return;
//		}
		auto dataArray = Helper4ParseJSON::getMember(data);
		auto length = dataArray.Size();
		for (int index = 0; index < length; index++)
		{
			std::string name = dataArray[index][JSONFieldConstant::NAME.c_str()].GetString();
			if (name == LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE)
				choosePayLine = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE)
				dailyChallenge = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK)
				piggyBank = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));

		}

	}
};

class LuckyWheelRewardConfig {
public:
	std::string name;
	std::string info;
	int reward = 0;

	/**
	* Dat: update lucky wheel reward info from values
	*/
	void updateLuckyWheelRewardInfoByValue(rapidjson::Value &data) {

		name = data[JSONFieldConstant::NAME.c_str()].GetString();
		info = data[JSONFieldConstant::VALUE.c_str()].GetString();
		reward = stoi(info);

	}

};

class DailyChallengeConfig {
public:
	int id = 0;
	std::string name;
	std::string info;
	bool is_activated = 0;
	int type = 0;
	int goal = 0;

	/**
	* Dat: update daily challenge info from values
	*/
	void updateDailyChallengeInfoByValue(rapidjson::Value &data) {
		name = data[JSONFieldConstant::NAME.c_str()].GetString();
		info = data[JSONFieldConstant::INFO.c_str()].GetString();
		is_activated = data[JSONFieldConstant::IS_ACTIVATED.c_str()].GetBool();
		type = data[JSONFieldConstant::DAILY_CHALLENGE_TASK_TYPE.c_str()].GetInt();
		goal = data[JSONFieldConstant::DAILY_CHALLENGE_TASK_GOAL.c_str()].GetInt();

	}
};

class BoosterConfig {
public:
	int multiFactor1 = 0;
	int multiFactor2 = 0;

	/**
	* Dat: update booster info from values
	*/
	void updateBoosterInfoByValue(rapidjson::Value &data) {

//		if (data == NULL) {
//			return;
//		}
		auto dataArray = Helper4ParseJSON::getMember(data);
		auto length = dataArray.Size();
		for (int index = 0; index < length; index++)
		{
			std::string name = dataArray[index][JSONFieldConstant::NAME.c_str()].GetString();

			if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_BOOSTER_FACTOR_1)
				multiFactor1 = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_BOOSTER_FACTOR_2)
				multiFactor2 = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
		}

	}
};

class PayLineConfig {
public:
	int maxPayLine = 0;
	float maxBetPerLine = 0;
	int level = 0;

	/**
	* Dat: update payline config info from values
	*/
	void updatePayLineConfigByValue(rapidjson::Value &data) {
		maxPayLine = data[JSONFieldConstant::MAX_PAYLINE.c_str()].GetInt();
		maxBetPerLine = data[JSONFieldConstant::MAX_BET_PER_LINE.c_str()].GetFloat();
		level = data[JSONFieldConstant::LEVEL_ID.c_str()].GetInt();
	}
};

struct LuckyBox {
	int coins = 0;
	int crowns = 0;
	int luckyWheels = 0;
	float price = 0;
};


class LuckyBoxConfig {
public:
	LuckyBox box1;
	LuckyBox box2;
	LuckyBox box3;

	/**
	* Dat: update kucky box config info from values
	*/
	void updateLuckBoxConfigInfoByValue(rapidjson::Value &data) {
//		if (data == NULL) {
//			return;
//		}
		auto dataArray = Helper4ParseJSON::getMember(data);
		auto length = dataArray.Size();
		for (int index = 0; index < length; index++)
		{

			std::string name = dataArray[index][JSONFieldConstant::NAME.c_str()].GetString();
			if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_COINS_REWARD)
				box1.coins = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_CROWNS_REWARD)
				box1.crowns = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_LUCKY_WHEELS_REWARD)
				box1.luckyWheels = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_1_PRICE)
				box1.price = stof(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_COINS_REWARD)
				box2.coins = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_CROWNS_REWARD)
				box2.crowns = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_LUCKY_WHEELS_REWARD)
				box2.luckyWheels = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_2_PRICE)
				box2.price = stof(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_COINS_REWARD)
				box3.coins = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_CROWNS_REWARD)
				box3.crowns = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_LUCKY_WHEELS_REWARD)
				box3.luckyWheels = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			else if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_3_PRICE)
				box3.price = stof(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
		}
		//cocos2d::log("");
	}
};

class MagicItemConfig {
public:
	int minNumberOfConsecutiveVideoViewToReceiveMagicItemReward = 0;

	/**
	* Dat: update magic item config from values
	*/
	void updateMagicItemConfigInfoByValue(rapidjson::Value &data) {

		auto dataArray = Helper4ParseJSON::getMember(data);
		auto length = dataArray.Size();
		for (int index = 0; index < length; index++)
		{
			std::string name = dataArray[index][JSONFieldConstant::NAME.c_str()].GetString();

			if (name == LobbyConstant::API_FEATURE_BEAN_TYPE_MIN_NUMBER_OF_CONSECUTIVE_VIDEO_VIEW_TO_RECEIVE_MAGIC_ITEM_REWARD)
				minNumberOfConsecutiveVideoViewToReceiveMagicItemReward = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
		}

	}
};

struct FlipCardConfig {
public:
	struct LevelConfig {
		int level;
		double coin_reward;
		double crown_reward;
		int leaf_reward;
		int leaf_upgrade_requirement;

		void updateInfo(const rapidjson::Value &data) {
			level = data[JSONFieldConstant::CARD_LEVEL.c_str()].GetInt();
			coin_reward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
			crown_reward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetDouble();
			leaf_reward = data[JSONFieldConstant::LEAF_REWARD.c_str()].GetInt();
			leaf_upgrade_requirement = data[JSONFieldConstant::LEAF_UPGRADE_REQUIREMENT.c_str()].GetInt();
		}
	};
	std::map<LobbyConstant::FlipCardType, std::map<int, LevelConfig*>> configs;
	double waitingTime;

	~FlipCardConfig() {
		for (auto levelConfig : configs) {
			for (auto child : levelConfig.second) {
				CC_SAFE_DELETE(child.second);
			}
		}
		configs.clear();
	}

	/**
	* update Flip Card Config from values
	*/
	void updateConfigInfoByValue(rapidjson::Value &data) {

		auto dataArray = Helper4ParseJSON::getMember(data);
		if (dataArray.Size() < 2) return;

		waitingTime = atoll(dataArray[0][JSONFieldConstant::VALUE.c_str()].GetString());

		configs.clear();

		auto aCardConfigs = Helper4ParseJSON::getMember(dataArray[1]);

		for (int index = 0, length = aCardConfigs.Size(); index < length; index++)
		{
			std::map<int, LevelConfig*> mapLevelConfig;
			LobbyConstant::FlipCardType cardType = 
				(LobbyConstant::FlipCardType)aCardConfigs[index][JSONFieldConstant::CARD_TYPE.c_str()].GetInt();
			if (configs.find(cardType) != configs.end()) {
				mapLevelConfig = configs[cardType];
			}

			auto levelConfig = new LevelConfig();
			levelConfig->updateInfo(aCardConfigs[index]);
			mapLevelConfig[levelConfig->level] = levelConfig;

			configs[cardType] = mapLevelConfig;
		}

	}
};

