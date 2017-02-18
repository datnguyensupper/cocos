#include "Helper4Array.h"
using namespace std;
USING_NS_CC;
#pragma region init singleton
Helper4Array* Helper4Array::s_instance = nullptr;

Helper4Array* Helper4Array::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new Helper4Array();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

Helper4Array::Helper4Array()
{

	
}


cocos2d::Color3B Helper4Array::removeRandomItemFromVector(std::vector<cocos2d::Color3B> &vector) {
	
	int indexRandom = cocos2d::random(0, static_cast<int>(vector.size()-1));
	Color3B item = vector[indexRandom];
	vector.erase(vector.begin() + indexRandom);
	return item;

}
