#pragma once
#include "BaseItemInfo.h"
#include "Helper/Helper4ParseJSON.h"
#include "Constant/LobbyConstant.h"
#include "Manager/InfoManager.h"
/**
* creator: Kiet Duong
* date: 2017-02-27
* file: AdditionalInfo.h
*/
struct DailyBonusStreakInfo : public BaseItemInfo
{
	bool canCollect;
	int dailyStreak;
	double coinReward;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		canCollect = data[JSONFieldConstant::CAN_COLLECT.c_str()].GetBool();
		dailyStreak = data[JSONFieldConstant::DAILY_STREAK.c_str()].GetInt();
		coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
	}
};

struct FreeCoinGiftInfo : public BaseItemInfo
{
	bool canCollect;
	double coinReward;
	double nextCoinReward;
	int waitingTime;
	int numberOfTimeCollectFreeCoin;
	/// <summary>
	/// get waiting time base on coin reward
	/// </summary>
	/// <param name="coin">coin reward</param>
	/// <returns></returns>
	int getCoinInfoCollectWaitingTime(double coin) {
		std::map<int, FreeCoinGiftConfig> &mapFreeCoinGiftConfig = InfoManager::getInstance()->mapFreeCoinGiftConfig;
		
		std::map<int, FreeCoinGiftConfig>::iterator it;

		for (it = mapFreeCoinGiftConfig.begin(); it != mapFreeCoinGiftConfig.end(); it++)
		{
			FreeCoinGiftConfig freeCoinGiftConfig = it->second;
			if (freeCoinGiftConfig.coinReward == coin) {
				return freeCoinGiftConfig.waitingTime;
			}
		}
		return 0;
	}

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		if (data.HasMember(JSONFieldConstant::CAN_COLLECT.c_str()))
			canCollect = data[JSONFieldConstant::CAN_COLLECT.c_str()].GetBool();
		else canCollect = false;
		
		if(data.HasMember(JSONFieldConstant::COIN_REWARD.c_str()))
		{
			coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
			nextCoinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		}

		if (data.HasMember(JSONFieldConstant::NEXT_COIN_REWARD.c_str()))
		{
			nextCoinReward = data[JSONFieldConstant::NEXT_COIN_REWARD.c_str()].GetDouble();
		}

		if (data.HasMember(JSONFieldConstant::WAITING_TIME.c_str()))
			waitingTime = data[JSONFieldConstant::WAITING_TIME.c_str()].GetInt();
		else
			waitingTime = getCoinInfoCollectWaitingTime(data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble());

		numberOfTimeCollectFreeCoin = data[JSONFieldConstant::NUMBER_OF_TIMES_COLLECT_FREE_COIN_GIFT.c_str()].GetInt();
	}
};

struct BoosterInfo : public BaseItemInfo
{
	long remainingTimeOfBoosterLevelUpBonus;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		remainingTimeOfBoosterLevelUpBonus = data[JSONFieldConstant::REMAINING_TIME_OF_BOOSTER_LEVEL_UP_BONUS.c_str()].GetInt64();
	}
};

struct ReferenceCodeInfo : public BaseItemInfo
{
	std::string referenceCode;
	int numberOfTimesReferenceCodeIsUsed;
	std::string refereeReferenceCode;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		referenceCode = data[JSONFieldConstant::REFERENCE_CODE.c_str()].GetString();
		numberOfTimesReferenceCodeIsUsed = data[JSONFieldConstant::NUMBER_OF_TIME_REFERENCE_CODE_IS_USED.c_str()].GetInt();
		refereeReferenceCode = data[JSONFieldConstant::REFEREE_REFERENCE_CODE.c_str()].GetString();
	}
};

struct DailyBonusLuckySpinInfo : public BaseItemInfo
{
	bool canCollect;
	double coinReward;
	int crownReward;
	std::string reelValues;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		canCollect = data[JSONFieldConstant::CAN_COLLECT.c_str()].GetBool();
		coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetInt();
		reelValues = data[JSONFieldConstant::REEL_VALUES.c_str()].GetString();
	}
};

struct DailyBonusWheelInfo : public BaseItemInfo
{
	bool canCollect;

	int factor;
	double coin;
	double levelBonus;
	int numberOfFriend;
	double coinPerFriend;
	double totalCoin;
	int box;
	double vipBenefit;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		canCollect = data[JSONFieldConstant::CAN_COLLECT.c_str()].GetBool();
		factor = data[JSONFieldConstant::FACTOR.c_str()].GetInt();
		coin = data[JSONFieldConstant::Coin.c_str()].GetDouble();
		levelBonus = data[JSONFieldConstant::LEVEL_BONUS.c_str()].GetDouble();
		numberOfFriend = data[JSONFieldConstant::NUMBER_OF_FRIEND.c_str()].GetInt();
		coinPerFriend = data[JSONFieldConstant::COIN_PER_FRIEND.c_str()].GetDouble();
		totalCoin = data[JSONFieldConstant::TOTAL_COIN.c_str()].GetDouble();
		box = data[JSONFieldConstant::BOX.c_str()].GetInt();
		vipBenefit = data[JSONFieldConstant::VIP_BENEFIT.c_str()].GetDouble();
	}
};

struct LuckyWheelInfo : public BaseItemInfo
{
	double coinReward;
	int crownReward;
	int remainingSpin;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetInt();
		remainingSpin = data[JSONFieldConstant::REMAINING_SPIN.c_str()].GetInt();
	}
};

struct LuckyBoxInfo : public BaseItemInfo
{
	double coinReward;
	int crownReward;
	int spinOfLuckyWheelReward;

	int remainingLuckyBoxType1;
	int remainingLuckyBoxType2;
	int remainingLuckyBoxType3;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetInt();
		spinOfLuckyWheelReward = data[JSONFieldConstant::SPIN_OF_LUCKY_WHEEL_REWARD.c_str()].GetInt();

		remainingLuckyBoxType1 = data[JSONFieldConstant::REMAINING_LUCKY_BOX_TYPE1.c_str()].GetInt();
		remainingLuckyBoxType2 = data[JSONFieldConstant::REMAINING_LUCKY_BOX_TYPE2.c_str()].GetInt();
		remainingLuckyBoxType3 = data[JSONFieldConstant::REMAINING_LUCKY_BOX_TYPE3.c_str()].GetInt();
	}
};
struct PiggyBankInfo : public BaseItemInfo
{
	double piggyBankCoin;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		piggyBankCoin = data[JSONFieldConstant::PIGGY_BANK_COIN.c_str()].GetDouble();
	}
};

struct ComebackBonusMobileInfo : public BaseItemInfo
{
	bool canCollect;
	int numberOfComebackTimes;
	double coinReward;
	int increasedPercentageOfExp;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		canCollect = data[JSONFieldConstant::CAN_COLLECT.c_str()].GetBool();
		numberOfComebackTimes = data[JSONFieldConstant::NUMBER_OF_COME_BACK_TIME.c_str()].GetInt();
		coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		increasedPercentageOfExp = data[JSONFieldConstant::INCREASED_PERCENTAGE_OF_EXP.c_str()].GetInt();
	}
};

struct MagicItemInfo : public BaseItemInfo
{
	int activeMagicItemType;

	int remainingPackageOfMagicItem100PercentBigWin;
	int remainingSpinOfMagicItem100PercentBigWin;

	int remainingPackageOfMagicItem100PercentMegaWin;
	int remainingSpinOfMagicItem100PercentMegaWin;

	int remainingPackageOfMagicItemLuckySpinType1;
	int remainingSpinOfMagicItemLuckySpinType1;

	int remainingPackageOfMagicItemLuckySpinType2;
	int remainingSpinOfMagicItemLuckySpinType2;

	int remainingPackageOfMagicItemDoubleExp;
	long remainingTimeOfMagicItemDoubleExp;

	int remainingPackageOfMagicItemLuckySymbol;
	long remainingTimeOfMagicItemLuckySymbol;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		activeMagicItemType = data[JSONFieldConstant::ACTIVE_MAGIC_ITEM_TYPE.c_str()].GetInt();
		
		remainingPackageOfMagicItem100PercentBigWin = data[JSONFieldConstant::REMAINING_PACKAGE_OF_MAGIC_ITEM_100_PERCENT_BIG_WIN.c_str()].GetInt();
		remainingSpinOfMagicItem100PercentBigWin = data[JSONFieldConstant::REMAINING_SPIN_OF_MAGIC_ITEM_100_PERCENT_BIG_WIN.c_str()].GetInt();
		
		remainingPackageOfMagicItem100PercentMegaWin = data[JSONFieldConstant::REMAINING_PACKAGE_OF_MAGIC_ITEM_100_PERCENT_MEGA_WIN.c_str()].GetInt();
		remainingSpinOfMagicItem100PercentMegaWin = data[JSONFieldConstant::REMAINING_SPIN_OF_MAGIC_ITEM_100_PERCENT_MEGA_WIN.c_str()].GetInt();

		remainingPackageOfMagicItemLuckySpinType1 = data[JSONFieldConstant::REMAINING_PACKAGE_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_1.c_str()].GetInt();
		remainingSpinOfMagicItemLuckySpinType1 = data[JSONFieldConstant::REMAINING_SPIN_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_1.c_str()].GetInt();
		
		remainingPackageOfMagicItemLuckySpinType2 = data[JSONFieldConstant::REMAINING_PACKAGE_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_2.c_str()].GetInt();
		remainingSpinOfMagicItemLuckySpinType2 = data[JSONFieldConstant::REMAINING_SPIN_OF_MAGIC_ITEM_LUCKY_SPIN_TYPE_2.c_str()].GetInt();

		remainingPackageOfMagicItemDoubleExp = data[JSONFieldConstant::REMAINING_PACKAGE_OF_MAGIC_ITEM_DOUBLE_EXP.c_str()].GetInt();
		remainingTimeOfMagicItemDoubleExp = data[JSONFieldConstant::REMAINING_TIME_OF_MAGIC_ITEM_DOUBLE_EXP.c_str()].GetInt64();

		remainingPackageOfMagicItemLuckySymbol = data[JSONFieldConstant::REMAINING_PACKAGE_OF_MAGIC_ITEM_LUCKY_SYMBOL.c_str()].GetInt();
		remainingTimeOfMagicItemLuckySymbol = data[JSONFieldConstant::REMAINING_TIME_OF_MAGIC_ITEM_LUCKY_SYMBOL.c_str()].GetInt64();
	}
};

class AdditionalInfo
{
public:
	DailyBonusStreakInfo* dailyBonusStreakInfo;
	FreeCoinGiftInfo* freeCoinGiftInfo;
	BoosterInfo* boosterInfo;
	ReferenceCodeInfo* referenceCodeInfo;
	DailyBonusLuckySpinInfo* dailyBonusLuckySpinInfo;
	DailyBonusWheelInfo* dailyBonusWheelInfo;
	LuckyWheelInfo* luckyWheelInfo;
	LuckyBoxInfo* luckyBoxInfo;
	PiggyBankInfo* piggyBankInfo;
	ComebackBonusMobileInfo* comebackBonusMobileInfo;
	MagicItemInfo* magicItemInfo;

	AdditionalInfo()
	{
		this->dailyBonusStreakInfo = new DailyBonusStreakInfo();
		this->freeCoinGiftInfo = new FreeCoinGiftInfo();
		this->boosterInfo = new BoosterInfo();
		this->referenceCodeInfo = new ReferenceCodeInfo();
		this->dailyBonusLuckySpinInfo = new DailyBonusLuckySpinInfo();
		this->dailyBonusWheelInfo = new DailyBonusWheelInfo();
		this->luckyWheelInfo = new LuckyWheelInfo();
		this->luckyBoxInfo = new LuckyBoxInfo();
		this->piggyBankInfo = new PiggyBankInfo();
		this->comebackBonusMobileInfo = new ComebackBonusMobileInfo();
		this->magicItemInfo = new MagicItemInfo();

	}

	~AdditionalInfo()
	{
		CC_SAFE_DELETE(this->dailyBonusStreakInfo);
		CC_SAFE_DELETE(this->freeCoinGiftInfo);
		CC_SAFE_DELETE(this->boosterInfo);
		CC_SAFE_DELETE(this->referenceCodeInfo);
		CC_SAFE_DELETE(this->dailyBonusLuckySpinInfo);
		CC_SAFE_DELETE(this->dailyBonusWheelInfo);
		CC_SAFE_DELETE(this->luckyWheelInfo);
		CC_SAFE_DELETE(this->luckyBoxInfo);
		CC_SAFE_DELETE(this->piggyBankInfo);
		CC_SAFE_DELETE(this->comebackBonusMobileInfo);
		CC_SAFE_DELETE(this->magicItemInfo);
	}
};
