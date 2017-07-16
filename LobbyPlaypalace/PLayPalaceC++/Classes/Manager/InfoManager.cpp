#include "InfoManager.h"
#include "PromotionsManager.h"
#include "Util/UtilFunction.h"
#include "Constant/ResultCodeConstant.h"
#include "Manager/NetworkManager.h"
#include "Helper/Helper4ParseJSON.h"
#include "Helper/Helper4Scene.h"
#include "Constant/Defination.h"
#include "Constant/LobbyConstant.h"
#include "Helper/Helper4String.h"
#include "cocos2d.h"
#include "Info/AdditionalInfo.h"

#pragma region init singleton
InfoManager* InfoManager::s_instance = nullptr;

InfoManager* InfoManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new InfoManager();
	}
	return s_instance;
}
#pragma endregion


InfoManager::InfoManager()
{
	this->serverConfigsInfo = new ServerConfigsInfo();
	this->userInfo = new UserInfo();
	this->userBonusCheck = new UserBonusCheck();
	this->additionalInfo = new AdditionalInfo();
	this->facebookFriendInfo = new FacebookFriendInfo();
	this->achievementInfo = new AchievementInfo();
	this->flipCardInfo = new FlipCardUserInfo();

	this->listDailyBonuStreakConfig.clear();
	this->magicItemConfig = new MagicItemConfig();
	this->dailyChallengeInfo = new DailyChallengeInfo();
	this->flipCardConfig = new FlipCardConfig();
}

InfoManager::~InfoManager()
{
	CC_SAFE_DELETE(this->serverConfigsInfo);
	CC_SAFE_DELETE(this->magicItemConfig);
	CC_SAFE_DELETE(this->userInfo);
	CC_SAFE_DELETE(this->userBonusCheck);
	CC_SAFE_DELETE(this->facebookFriendInfo);
	CC_SAFE_DELETE(this->additionalInfo);
	CC_SAFE_DELETE(this->achievementInfo);
	CC_SAFE_DELETE(this->dailyChallengeInfo);
	CC_SAFE_DELETE(this->flipCardInfo);


	CC_SAFE_DELETE(this->flipCardConfig);
	this->ClearStdMap(this->betSlotGameInfoMap);
	this->ClearStdMap(this->serverSlotGameInfoMap);
	this->ClearStdMap(this->levelInfoMap);

	this->ClearStdVector(this->giftInfoList);
	this->ClearStdVector(this->listDailyBonuStreakConfig);

	listDailyBonuStreakConfig.clear();
	listLuckyWheelRewardConfig.clear();
	mapFreeCoinGiftConfig.clear();
	mapDailyChallengeConfig.clear();

	CC_SAFE_DELETE(s_instance);
}

void InfoManager::updateServerConfigsInfo(rapidjson::Value &data)
{
//	if (data == NULL) {
//		return;
//	}
	auto dataArray = data[JSONFieldConstant::MEMBER.c_str()].GetArray();
	auto length = dataArray.Size();
	for (int index = 0; index < length; index++)
	{
		std::string name = dataArray[index][JSONFieldConstant::NAME.c_str()].GetString();
		if (name == "operator_code")
		{
		}
		else if (name == "reload_real_time_notification_interval")
		{
			this->serverConfigsInfo->deltaTimeCallRealTimeNotification = std::atoi(dataArray[index][JSONFieldConstant::INFO.c_str()].GetString());
		}
		else if (name == "reload_server_notification_interval")
		{
		}
		else if (name == "friend_update_frequency")
		{
			this->serverConfigsInfo->deltaTimeCallUpdateFriend = std::atoi(dataArray[index][JSONFieldConstant::INFO.c_str()].GetString());
		}
		else if (name == "bot_avatar_link_list")
		{
		}
		else if (name == "COIN_REWARD_AFTER_LEVEL_UP")
		{
			this->serverConfigsInfo->coinRewardAfterUpLevel = std::atoi(dataArray[index][JSONFieldConstant::INFO.c_str()].GetString());
		}
		else if (name == "CROWN_REWARD_AFTER_LEVEL_UP")
		{
			this->serverConfigsInfo->crownRewardAfterUpLevel = std::atoi(dataArray[index][JSONFieldConstant::INFO.c_str()].GetString());
		}
		else if (name == "TIME_TO_SHOW_OFFER")
		{
		}
		else if (name == "COIN_FOR_SHOW_OFFER")
		{
		}
		else if (name == "sample_wheel_mega_win_in_tutorial")
		{
			this->serverConfigsInfo->sampleResponseSpinInTutorial = dataArray[index][JSONFieldConstant::INFO.c_str()].GetString();
		}
	}
}
void InfoManager::updateUserInfo(rapidjson::Value &data)
{
	this->userInfo->updateUserInfoByValue(data);
}
void InfoManager::reloadUserInfo(std::function<void(bool isSuccess, UserInfo* result)> callback)
{
	auto callbackFromServer = [this, callback](
		int coreResultCode,
		rapidjson::Value &doc,
		string responseAsString) {
		if (coreResultCode == RESULT_CODE_VALID)
		{
			updateUserInfo(doc);

			PromotionsManager::getInstance()->checkRepeatedPromotions();
		}
		callback(coreResultCode == RESULT_CODE_VALID, this->getUserInfo());
	};
	NetworkManager::getInstance()->getUserInfo(
       true,
       [callbackFromServer](int coreResultCode,
		rapidjson::Value &doc,string responseAsString) {
        cocos2d::log("User Info\n %s\n",responseAsString.c_str());
		callbackFromServer(coreResultCode, doc, responseAsString);
	}, [callback, this](std::string result) {
		callback(false, this->getUserInfo());
	}, [callback, this](std::string result) {
		callback(false, this->getUserInfo());
	});
}
void InfoManager::updateUserBonusCheck(rapidjson::Value &data)
{
	this->userBonusCheck->updateInfoByValue(data);
}
void InfoManager::reloadAchievementInfo(std::function<void(bool isSuccess, AchievementInfo*result)> callback)
{

	if (isGettingListAchievementsFromSV) {
		callback(true, this->achievementInfo);
		return;
	}
	isGettingListAchievementsFromSV = true;

	const std::function<void(std::string)>& fail = [this, callback](std::string error) {
		callback(false, this->achievementInfo);
		isGettingListAchievementsFromSV = false;
	};


	NetworkManager::getInstance()->getAchievementList([this, callback](int coreResultCode,
		rapidjson::Value &doc,
		string responseAsString) {
		isGettingListAchievementsFromSV = false;
		this->achievementInfo->updateAchievementInfo(doc);
		if (callback) {
			callback(coreResultCode == RESULT_CODE_VALID, this->achievementInfo);
		}
	}, fail, fail);
}
void InfoManager::reloadDailyChallengeInfo(std::function<void(bool isSuccess, DailyChallengeInfo*result)> callback)
{
	const std::function<void(std::string)>& fail = [this, callback](std::string error) {
		callback(false, this->dailyChallengeInfo);
	};

	NetworkManager::getInstance()->getDailyChallengeInfo([this, callback, fail](int coreResultCode,
		rapidjson::Value &doc,
		string responseAsString) {
		if (coreResultCode == RESULT_CODE_VALID) {
			this->dailyChallengeInfo->updateInfoByValue(doc);
			if (callback) {
				callback(true , this->dailyChallengeInfo);
			}
		}
		else {
			fail(responseAsString);
		}
	}, fail, fail);
}
void InfoManager::reloadFlipCardUserInfo(std::function<void(bool isSuccess, FlipCardUserInfo*result)> callback)
{
	const std::function<void(std::string)>& fail = [this, callback](std::string error) {
		if (callback) {
			callback(false, this->flipCardInfo);
		}
	};

	NetworkManager::getInstance()->getFlipCardInfo([this, callback, fail](int coreResultCode,
		rapidjson::Value &doc,
		string responseAsString) {
		if (coreResultCode == RESULT_CODE_VALID) {
			this->flipCardInfo->updateInfoByValue(doc);
			if (callback) {
				callback(true, this->flipCardInfo);
			}
		}
		else {
			fail(responseAsString);
		}
	}, fail, fail);
}
void InfoManager::reloadAdditionalInfo(std::function<void(bool isSuccess, AdditionalInfo*result)> callback)
{
	NetworkManager::getInstance()->getAdditionalInfo([callback, this](
		int coreResultCode,
		rapidjson::Value &responseAsDocument,
		std::string responseAsString)
	{
		if (coreResultCode == RESULT_CODE_VALID)
		{
			//reset some feature
			this->additionalInfo->dailyBonusWheelInfo->canCollect = false;
			//getdata
			auto listSize = Helper4ParseJSON::getListSize(responseAsDocument);
			auto members = Helper4ParseJSON::getMember(responseAsDocument);
			for (auto i = 0; i < listSize; i++) {

				rapidjson::Value &beanData = Helper4ParseJSON::getBeanData(members[i]);

				std::string beanType = Helper4ParseJSON::getBeanType(beanData);
				if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_STREAK)
					this->additionalInfo->dailyBonusStreakInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_FREE_COIN_GIFT)
					this->additionalInfo->freeCoinGiftInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_REFERENCE_CODE)
					this->additionalInfo->referenceCodeInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_LUCKY_SPIN)
					this->additionalInfo->dailyBonusLuckySpinInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_DAILY_BONUS_WHEEL)
					this->additionalInfo->dailyBonusWheelInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_LUCKY_WHEEL)
					this->additionalInfo->luckyWheelInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_LUCKY_BOX)
					this->additionalInfo->luckyBoxInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_PIGGY_BANK)
					this->additionalInfo->piggyBankInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_BOOSTER)
					this->additionalInfo->boosterInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_COMEBACK_BONUS)
					this->additionalInfo->comebackBonusMobileInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_MAGIC_ITEM)
					this->additionalInfo->magicItemInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_SCRATCH_CARD_INFO)
					this->additionalInfo->scratchCardInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_FEEDBACK)
					this->additionalInfo->feedbackInfo->updateInfoByValue(beanData);
				else if (beanType == LobbyConstant::API_BONUS_BEAN_TYPE_FLIP_CARD_INFO)
					this->additionalInfo->flipCardInfo->updateInfoByValue(beanData);
			}
		}
		if (callback)
		{
			callback(coreResultCode == RESULT_CODE_VALID, this->additionalInfo);
		}
	});
}
void InfoManager::reloadFriendListOnly(std::function<void(bool isSuccess, FacebookFriendInfo*newFbFriendInfo)> callback)
{
	NetworkManager::getInstance()->getFriendList(
		[callback, this](int coreResultCode,
			rapidjson::Value &response,
			std::string responseAsString)
	{
		if (coreResultCode == RESULT_CODE_VALID)
		{
			this->getFacebookFriendInfo()->updateFriendList(response);
		}
		if (callback)
		{
			callback(coreResultCode == RESULT_CODE_VALID, this->getFacebookFriendInfo());
		}
	}
	);
}
void InfoManager::reloadGiftInfoList(std::function<void(bool isSuccess, std::vector<GiftInfo*>result)> callback)
{
	if (isGettingListGiftsFromSV) {
		callback(true, this->giftInfoList);
		return;
	}
	isGettingListGiftsFromSV = true;

	const std::function<void(std::string)>& fail = [this,callback](std::string error) {
		callback(false, this->giftInfoList);
		isGettingListGiftsFromSV = false;
	};
	NetworkManager::getInstance()->getAllGift(
		[this, callback](
			int coreResultCode,
			rapidjson::Value &response,
			std::string responseAsString){

		isGettingListGiftsFromSV = false;
		if (coreResultCode == RESULT_CODE_VALID){
			for (auto &child : this->giftInfoList){
				if (child){
					CC_SAFE_DELETE(child);
				}
			}
			this->giftInfoList.clear();
			this->giftInfoList.shrink_to_fit();

			//parse data
			auto members = Helper4ParseJSON::getMember(response);
			auto listSize = Helper4ParseJSON::getListSize(response);
			//for (int i = listSize - 1; i >= 0; i--)
			for (int i = 0; i < listSize; i++){
				GiftInfo *giftInfo = new GiftInfo();
				giftInfo->updateInfoByValue(members[i]);

				this->giftInfoList.push_back(giftInfo);
			}
		}
		if (callback){
			callback(coreResultCode == RESULT_CODE_VALID, this->giftInfoList);
		}
	}, fail, fail);
}

const std::deque<ServerSlotGameInfo*> InfoManager::updateServerSlotGameInfoList(rapidjson::Value &listSlotGameInfo)
{
	auto dataArray = listSlotGameInfo.GetArray();
	std::deque<ServerSlotGameInfo*> listNewGameUnlocked;
	for (int i = 0; i < dataArray.Size(); i++)
	{
		auto &child = dataArray[i];
		int orderId = child[JSONFieldConstant::ORDER_ID.c_str()].GetInt64();
		ServerSlotGameInfo* slotGameInfo = nullptr;
		if (this->serverSlotGameInfoMap.find(orderId) != this->serverSlotGameInfoMap.end()) {
			slotGameInfo = this->serverSlotGameInfoMap.at(orderId);
		}
		else {
			slotGameInfo = new ServerSlotGameInfo();

			this->serverSlotGameInfoMap.insert(std::pair<int, ServerSlotGameInfo*>(orderId, slotGameInfo));
		}
		bool previousUnlcokedInfo = slotGameInfo->bUnlocked;
		slotGameInfo->updateInfoByValue(child);
		if (!previousUnlcokedInfo && slotGameInfo->bUnlocked) {
			listNewGameUnlocked.push_back(slotGameInfo);
		}
	}

	std::sort(
		listNewGameUnlocked.begin(),
		listNewGameUnlocked.end(),
		[](ServerSlotGameInfo* game1, ServerSlotGameInfo* game2){ return game1->minLevel < game2->minLevel; });

	return listNewGameUnlocked;
}
void InfoManager::reloadServerSlotGameInfoList(std::function<void(const std::deque<ServerSlotGameInfo*>& listNewGameUnlocked)> callback)
{
	auto callbackFromServer = [this, callback](
		int coreResultCode,
		rapidjson::Value &doc,
		string responseAsString) {
		if (coreResultCode == RESULT_CODE_VALID && callback)
		{
			callback(updateServerSlotGameInfoList(doc[JSONFieldConstant::MEMBER.c_str()]));
		}
	};
	NetworkManager::getInstance()->getGameSlotList(callbackFromServer);
}
void InfoManager::updateBetSlotGameInfoList(rapidjson::Value &data)
{
	auto dataArray = data[JSONFieldConstant::MEMBER.c_str()].GetArray();

	for (int i = 0; i < dataArray.Size(); i++)
	{
		auto &child = dataArray[i];
		int id = child[JSONFieldConstant::ID.c_str()].GetInt64();
		BetSlotGameInfo* betSlotGameInfo = nullptr;
		if (this->betSlotGameInfoMap.find(id) != this->betSlotGameInfoMap.end())
		{
			betSlotGameInfo = this->betSlotGameInfoMap[id];
		}
		else 
		{
			betSlotGameInfo = new BetSlotGameInfo();

			this->betSlotGameInfoMap.insert(std::pair<int, BetSlotGameInfo*>(id, betSlotGameInfo));
		}
		betSlotGameInfo->updateInfoByValue(dataArray[i]);
	}
}
void InfoManager::updateLevelInfoList(rapidjson::Value &data)
{
	auto dataArray = data[JSONFieldConstant::MEMBER.c_str()].GetArray();

	for (int i = 0; i < dataArray.Size(); i++)
	{
		auto &child = dataArray[i];
		int levelId = child[JSONFieldConstant::LEVEL_ID.c_str()].GetInt();
		LevelInfo* level = nullptr;
		if (this->levelInfoMap.find(levelId) != this->levelInfoMap.end())
		{
			level = this->levelInfoMap[levelId];
		}
		else
		{
			level = new LevelInfo();

			this->levelInfoMap.insert(std::pair<int, LevelInfo*>(levelId, level));
		}
		level->updateInfoByValue(dataArray[i]);
	}
}

void InfoManager::updateListDailyBonusStreakConfig(rapidjson::Value &data) {
	listDailyBonuStreakConfig.clear();

//	if (data == NULL) {
//		return;
//	}
	auto dataArray = Helper4ParseJSON::getMember(data);
	auto length = dataArray.Size();
	for (int index = 0; index < length; index++)
	{
		StreakConfig* streakInfo = new StreakConfig();
		streakInfo->updateStreakInfoByValue(dataArray[index]);
		listDailyBonuStreakConfig.push_back(streakInfo);
	}
}

void InfoManager::updateFreecoinGiftConfig(rapidjson::Value &data) {
	mapFreeCoinGiftConfig.clear();

//	if (data == NULL) {
//		return;
//	}
	auto dataArray = Helper4ParseJSON::getMember(data);
	auto length = dataArray.Size();
	for (int index = 0; index < length; index++)
	{
		std::string name = dataArray[index][JSONFieldConstant::NAME.c_str()].GetString();
		int id = 0;
		int waitingTime = 0;
		int coinReward = 0;
		if (Helper4String::isStringContain(name, LobbyConstant::FREE_COIN_GIFT_COIN_REWARD_PREFIX)) {
			coinReward = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			id = stoi(Helper4String::splitString(name, LobbyConstant::FREE_COIN_GIFT_COIN_REWARD_PREFIX)[1]);
		}
		else if (Helper4String::isStringContain(name, LobbyConstant::FREE_COIN_WAITING_TIME_PREFIX)) {
			waitingTime = stoi(static_cast<std::string>(dataArray[index][JSONFieldConstant::VALUE.c_str()].GetString()));
			id = stoi(Helper4String::splitString(name, LobbyConstant::FREE_COIN_WAITING_TIME_PREFIX)[1]);

		}

		FreeCoinGiftConfig giftInfo = mapFreeCoinGiftConfig[id];
		if (waitingTime != 0) giftInfo.waitingTime = waitingTime;
		if (coinReward != 0)  giftInfo.coinReward = coinReward;
		mapFreeCoinGiftConfig[id] = giftInfo;
	
	}

}

void InfoManager::updateUnlockFeatureByLevelConfig(rapidjson::Value &data) {
	unlockFeatureByLevelConfig.updateUnlockFeatureByLevelInfoByValue(data);
}

void InfoManager::updateListLuckyWheelRewardConfig(rapidjson::Value &data) {

	listLuckyWheelRewardConfig.clear();

//	if (data == NULL) {
//		return;
//	}
	auto dataArray = Helper4ParseJSON::getMember(data);
	auto length = dataArray.Size();
	for (int index = 0; index < length; index++)
	{
		LuckyWheelRewardConfig luckyWheelInfo;
		luckyWheelInfo.updateLuckyWheelRewardInfoByValue(dataArray[index]);
		listLuckyWheelRewardConfig.push_back(luckyWheelInfo);
	}

}

void InfoManager::updateDailyChallengeConfig(rapidjson::Value &data) {

	mapDailyChallengeConfig.clear();

//	if (data == NULL) {
//		return;
//	}
	auto dataArray = Helper4ParseJSON::getMember(data);
	auto length = dataArray.Size();
	for (int index = 0; index < length; index++)
	{

		int id = dataArray[index][JSONFieldConstant::ID.c_str()].GetInt();
		DailyChallengeConfig dailyInfo = mapDailyChallengeConfig[id];
		dailyInfo.id = id;
		dailyInfo.updateDailyChallengeInfoByValue(dataArray[index]);

		mapDailyChallengeConfig[id] = dailyInfo;

	}
}

void InfoManager::updateBoosterConfig(rapidjson::Value &data) {
	boosterConfig.updateBoosterInfoByValue(data);
}

void InfoManager::updateSlotGameConfig(rapidjson::Value & data)
{
//	if (data == NULL) {
//		return;
//	}
	auto dataArray = Helper4ParseJSON::getMember(data);
	this->mapSlotGameConfig.clear();
	for (int i = 0, length = dataArray.Size(); i < length; ++i)
	{
		auto gameName = dataArray[i][JSONFieldConstant::NAME.c_str()].GetString();
		auto gameId = dataArray[i][JSONFieldConstant::ID.c_str()].GetInt();

		this->mapSlotGameConfig[gameName] = gameId;
	}
}

int InfoManager::getGameIDByName(const std::string & gameName) const
{
	if (this->mapSlotGameConfig.find(gameName) != this->mapSlotGameConfig.end()) {
		return this->mapSlotGameConfig.at(gameName);
	}
	return -1;
}

void InfoManager::updatePayLineConfig(rapidjson::Value &data) {
//	if (data == NULL) {
//		return;
//	}
	auto dataArray = Helper4ParseJSON::getMember(data);
	auto length = dataArray.Size();
	mapListPayLineConfig.clear();
	for (int index = 0; index < length; index++)
	{
		int gameID = dataArray[index][JSONFieldConstant::GAME_ID.c_str()].GetInt();
		std::vector<PayLineConfig> listPayLineConfig = mapListPayLineConfig[gameID];

		PayLineConfig payLineConfig;
		payLineConfig.updatePayLineConfigByValue(dataArray[index]);

		int i = 0;
		for (i; i < listPayLineConfig.size(); i++) {
			if (payLineConfig.level < listPayLineConfig[i].level) {
				break;
			}
		}
		if (i < listPayLineConfig.size())
			listPayLineConfig.insert(listPayLineConfig.begin() + i, payLineConfig);
		else
			listPayLineConfig.push_back(payLineConfig);
		mapListPayLineConfig[gameID] = listPayLineConfig;
	}
}

void InfoManager::updateLuckyBoxConfig(rapidjson::Value &data) {
	luckyBoxConfig.updateLuckBoxConfigInfoByValue(data);
}

void InfoManager::updateMagicItemConfig(rapidjson::Value &data) {
	magicItemConfig->updateMagicItemConfigInfoByValue(data);
}

void InfoManager::updateFlipCardConfig(rapidjson::Value & data)
{
	this->flipCardConfig->updateConfigInfoByValue(data);
}

template <typename Key, typename Value>
void InfoManager::ClearStdMap(std::map<Key, Value*> map)
{
	for (auto &child : map) {
		if (child.second) {
			CC_SAFE_DELETE(child.second);
		}
	}
	map.clear();
}

template<typename Value>
void InfoManager::ClearStdVector(std::vector<Value*>& vector)
{
	for (auto &child : vector) {
		if (child) {
			CC_SAFE_DELETE(child);
		}
	}
	vector.clear();
}
