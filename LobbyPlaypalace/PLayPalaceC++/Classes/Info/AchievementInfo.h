#pragma once
#include "Helper/Helper4ParseJSON.h"
#include "Constant/JSONFieldConstant.h"

using namespace rapidjson;
using namespace std;

enum AchievementGroupType {
	GENERAL = 0,
	GAME = 1,
	SOCIAL = 2
};

struct AchievementItem {
	int id;
	int type;
	string name;

	double status;
	double goal;

	int star;

	double coinReward;
	double crownReward;

	double pointReward;

	int sub_category_id;
	string sub_category_name;

	bool isComplete;
	bool isCollected;
	bool isOnTimeAchieved;

	bool isCollectable() { return this->isComplete && !this->isCollected; }

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="id">achievement id</param>
	/// <param name="data">data from PP Server</param>
	AchievementItem(int id, const rapidjson::Value &data) {
		this->id = id;

		this->type = data[JSONFieldConstant::ACHIEVEMENT_TYPE.c_str()].GetInt();
		this->name = data[JSONFieldConstant::NAME.c_str()].GetString();

		this->status = data[JSONFieldConstant::CURRENT_STATUS.c_str()].GetDouble();
		this->goal = data[JSONFieldConstant::ACHIEVEMENT_GOAL.c_str()].GetDouble();

		this->star = data[JSONFieldConstant::STAR.c_str()].GetInt();

		this->coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		this->crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetDouble();

		this->pointReward = data[JSONFieldConstant::ACHIEVEMENT_POINT_REWARD.c_str()].GetDouble();

		this->sub_category_id = data[JSONFieldConstant::SUB_CATEGORY_ID.c_str()].GetInt();
		this->sub_category_name = data[JSONFieldConstant::SUB_CATEGORY_NAME.c_str()].GetString();

		this->isComplete = data[JSONFieldConstant::IS_COMPLETE.c_str()].GetBool();
		this->isCollected = data[JSONFieldConstant::IS_COLLECTED.c_str()].GetBool();
		this->isOnTimeAchieved = data[JSONFieldConstant::IS_ONLY_ONE_ACHIEVEMENT.c_str()].GetBool();
	}
};
struct AchievementCategory {
	int id;
	string name;
	map<int, AchievementItem*> mItems;
	~AchievementCategory() {
		for (auto item : mItems) {
			CC_SAFE_DELETE(item.second);
		}
		mItems.clear();
	}

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="id">achievement category id</param>
	/// <param name="data">data from PP Server</param>
	void update(int id, const rapidjson::Value &data) {
		this->id = id;
		this->name = data[JSONFieldConstant::CATEGORY_NAME.c_str()].GetString();

		int itemID = data[JSONFieldConstant::ACHIEVEMENT_ID.c_str()].GetInt();

		auto item = new AchievementItem(itemID, data);

		mItems[itemID] = item;
	}
};
struct AchievementGroup {
	AchievementGroupType type;
	map<int, AchievementCategory*> mCategories;
	int iTotalCollectableAchievement = 0;

	~AchievementGroup() {
		for (auto cat : mCategories) {
			CC_SAFE_DELETE(cat.second);
		}
		mCategories.clear();
	}

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="id">achievement group id</param>
	/// <param name="data">data from PP Server</param>
	void update(AchievementGroupType type, const rapidjson::Value &data) {
		this->type = type;

		int categoryID = data[JSONFieldConstant::CATEGORY_ID.c_str()].GetInt();

		if (data[JSONFieldConstant::IS_COMPLETE.c_str()].GetBool() && !data[JSONFieldConstant::IS_COLLECTED.c_str()].GetBool()) {
			iTotalCollectableAchievement++;
		}

		AchievementCategory* category = nullptr;
		if (mCategories.find(categoryID) == mCategories.end()) {
			category = new AchievementCategory();
			mCategories[categoryID] = category;
		}
		else {
			category = mCategories[categoryID];
		}
		category->update(categoryID, data);
	}
};

class AchievementInfo
{
private:
	int iTotalCollectableAchievement;
	map<AchievementGroupType, AchievementGroup*> mGroups;
public:
	map<AchievementGroupType, AchievementGroup*> getAllGroups() const { return this->mGroups; }
	AchievementGroup* getGroup(AchievementGroupType type) { return this->mGroups[type]; }

	int getTotalCollectableAchievement() { return iTotalCollectableAchievement; }

	/// <summary>
	/// update info from values from PP Server
	/// </summary>
	/// <param name="data">data from PP Server</param>
	void updateAchievementInfo(const rapidjson::Value &data) {
		this->reset();

		auto aAchievementInfo = data[JSONFieldConstant::MEMBER.c_str()].GetArray();

		for (int i = 0; i < aAchievementInfo.Size(); i++)
		{
			auto& info = aAchievementInfo[i];
			AchievementGroupType type = (AchievementGroupType)info[JSONFieldConstant::GROUP_TYPE.c_str()].GetInt();

			AchievementGroup* group = nullptr;
			if (mGroups.find(type) == mGroups.end()) {
				group = new AchievementGroup();
				mGroups[type] = group;
			}
			else {
				group = mGroups[type];
			}
			group->update(type, info);

		}
		for (auto group : mGroups)
		{
			iTotalCollectableAchievement += group.second->iTotalCollectableAchievement;
		}
	}

	void reset() {
		iTotalCollectableAchievement = 0;
		for (auto group : mGroups) {
			CC_SAFE_DELETE(group.second);
		}
		mGroups.clear();
	}
};