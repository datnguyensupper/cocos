#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-13
* file: BaseItemInfo.h
*/
#include "BaseItemInfo.h"
#include "Constant/Defination.h"


struct DailyChallengeTask : public BaseItemInfo {
	int configID;
	double currentProgress;

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		configID = data[JSONFieldConstant::DAILY_CHALLENGE_TASK_CONFIG_ID.c_str()].GetInt();
		currentProgress = data[JSONFieldConstant::CURRENT_PROGRESS.c_str()].GetDouble();
	}
};

struct DailyChallengeInfo : public BaseItemInfo
{
	bool canCollect;
	double coinReward;
	double crownReward;

	std::vector<DailyChallengeTask*> listTask;

	~DailyChallengeInfo() {
		SAFE_DELETE_VECTOR(listTask);
	}

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		canCollect = data[JSONFieldConstant::CAN_COLLECT.c_str()].GetBool();
		coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetDouble();

		auto dataArray = data[JSONFieldConstant::DAILY_CHALLENGE_TASK_LIST.c_str()][JSONFieldConstant::MEMBER.c_str()].GetArray();

		SAFE_DELETE_VECTOR(listTask);

		for (int i = 0, size = dataArray.Size(); i < size; i++)
		{
			DailyChallengeTask* task = new DailyChallengeTask();
			task->updateInfoByValue(dataArray[i]);
			listTask.push_back(task);
		}
	}
};