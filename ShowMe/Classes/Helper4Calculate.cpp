#include "Helper4Calculate.h"
using namespace std;
USING_NS_CC;
#pragma region init singleton
Helper4Calculate* Helper4Calculate::s_instance = nullptr;

Helper4Calculate* Helper4Calculate::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new Helper4Calculate();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

Helper4Calculate::Helper4Calculate()
{

	
}

float Helper4Calculate::distance(cocos2d::Vec2 firstPoint, cocos2d::Vec2 secondPoint) {
	return firstPoint.distance(secondPoint);
}

float Helper4Calculate::angle(cocos2d::Vec2 firstPoint, cocos2d::Vec2 secondPoint) {

	Vec2 vectorDirection = secondPoint - firstPoint;
	float angle = vectorDirection.getAngle();
	//log("direction: x=%f y=%f angle: %f", vectorDirection.x, vectorDirection.y, angle* (180.0 / 3.14));
	float angleResult = -angle * (180.0 / 3.14) + 90;
	
	if (angleResult < 0) angleResult += 360;
	return angleResult;
}
