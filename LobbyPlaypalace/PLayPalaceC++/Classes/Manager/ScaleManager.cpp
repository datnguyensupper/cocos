#include "ScaleManager.h"

using namespace std;
USING_NS_CC;
#pragma region init singleton
ScaleManager* ScaleManager::s_instance = nullptr;

ScaleManager* ScaleManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new ScaleManager();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

ScaleManager::ScaleManager()
{

}

void ScaleManager::init(cocos2d::Size visibleSize, cocos2d::Vec2 original) {
	if (original.x > 0)
		ratio = visibleSize.width*1.0 / (visibleSize.width + original.x * 2);
	else if (original.y > 0)
		ratio = visibleSize.height*1.0 / (visibleSize.height + original.y * 2);
	else
		ratio = visibleSize.width*1.0 / (visibleSize.width + original.x * 2);
}

float ScaleManager::getScaleUpRatio() {
	return 1.0 / ratio;
}

float ScaleManager::getExactlyScaleDownRatio() {
	return ratio;
}


float ScaleManager::getLookGoodScaleDownRatio() {
	return ratio + (1-ratio)/2;
}
