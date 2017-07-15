#pragma once
#include "AchievementPopup.h"

struct AchievementCategory;
struct AchievementItem;

class AchievementItemCell : public cocos2d::Node
{
private:

public:
	virtual bool init(AchievementItem* itemInfo);
};

class AchievementCategoryCell : public cocos2d::ui::Layout
{
private:

public:
	virtual bool init(AchievementCategory* categoryInfo);
};