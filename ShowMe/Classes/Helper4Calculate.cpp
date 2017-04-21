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
