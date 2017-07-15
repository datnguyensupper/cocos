#include "CJellyFishDB.h"
#include "../game/CGameDB.h"
USING_NS_CC;
namespace GameSlot {
	CJellyFishDB::CJellyFishDB() : Sprite()
	{
		this->autorelease();
	}
	CJellyFishDB::~CJellyFishDB()
	{

	}
	void CJellyFishDB::start()
	{
		this->initWithSpriteFrameName("jellyfish_small_0010");
		this->setPosition(RandomHelper::random_int((int)(CSettings::CANVAS_WIDTH * 0.25f), CSettings::CANVAS_WIDTH),
			RandomHelper::random_int((int)(CSettings::CANVAS_HEIGHT * 0.25f), CSettings::CANVAS_HEIGHT));
		this->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().mainGame["jelly_fish_plist"],
			"jellyfish_small_00%i",
			10,
			48,
			30,
			-1
			));

		this->setRotation(RandomHelper::random_int(0, 360));
		this->calculateDirection();
		this->scheduleUpdate();
	}
	void CJellyFishDB::calculateDirection()
	{
		auto angle = MATH_DEG_TO_RAD(this->getRotationSkewX() - 90);
		this->moveDirection = Vec2(cos(angle), -sin(angle));
	}
	void CJellyFishDB::update(float dt)
	{
		bool isChangedX = false;
		float angle = this->getRotationSkewX();
		if (this->_position.x <= -50) {
			angle = RandomHelper::random_int(30, 150);
			isChangedX = true;
		}
		else if (this->_position.x >= CSettings::CANVAS_WIDTH + 50) {
			angle = -RandomHelper::random_int(30, 150);
			isChangedX = true;
		}
		if (this->_position.y >= CSettings::CANVAS_HEIGHT + 50) {
			angle = isChangedX ? angle + 180 : -RandomHelper::random_int(120, 240);
		}
		else if (this->_position.y <= -50) {
			angle = isChangedX ? angle + 180 : -RandomHelper::random_int(-60, 60);
		}
		if (angle != this->getRotationSkewX()) {
			this->setRotation(angle);
			this->calculateDirection();
		}
		this->setPosition(this->getPosition() + moveDirection * speed);
	}
}
