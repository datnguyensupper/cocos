#include "LuckyWheelScene.h"
#include "ui/CocosGUI.h"
#include "Configs.h"
#include "Manager/SoundManager.h"
#include "Constant/PPEnums.h"
#include "Util/UtilFunction.h"
#include "Views/LuckyWheel/LuckyWheelLayout.h"
USING_NS_CC;
Scene* LuckyWheelScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = LuckyWheelScene::create();
	scene->setTag(ppEnum::GameScene::LuckyWheel);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LuckyWheelScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!BaseScene::init())
	{
		return false;
	}

	auto luckyWheelLayout = LuckyWheel::LuckyWheelLayout::create();
	this->addChild(luckyWheelLayout);

	return true;
}
