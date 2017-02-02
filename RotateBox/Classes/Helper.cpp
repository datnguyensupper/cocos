#include "Helper.h"
#include "Definitions.h"

USING_NS_CC;

static Helper* helper = nullptr;

Helper::Helper()
{
}

Helper* Helper::getInstance()
{
	if (!helper) {
		helper = new (std::nothrow)Helper();
	}
	return helper;
}

float Helper::randomDirectionOneDimention() {
	float randomX = CCRANDOM_MINUS1_1();
	if (randomX < 0) {
		randomX = -1;
	}
	else {
		randomX = 1;
	}
	return randomX;
}

cocos2d::Vec2 Helper::randomDirection() {
	auto randomX = CCRANDOM_MINUS1_1();
	if (randomX < 0) {
		randomX = -1;
	}
	else {
		randomX = 1;
	}
	auto randomY = CCRANDOM_MINUS1_1();
	if (randomY < 0) {
		randomY = -1;
	}
	else {
		randomY = 1;
	}
	return Vec2(randomX, randomY);
}

cocos2d::Vec2 Helper::normalizeDirection(cocos2d::Vec2 direction) {
	auto randomX = direction.x;
	if (randomX < 0) {
		randomX = -1;
	}
	else {
		randomX = 1;
	}
	auto randomY = direction.y;
	if (randomY < 0) {
		randomY = -1;
	}
	else {
		randomY = 1;
	}
	return Vec2(randomX, randomY);
}