#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: LobbyScene.h, LobbyScene.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Configs.h"
#include "SlotGame/GameSlotScene.h"

#include "Constant/Defination.h"
#include "Constant/JSONFieldConstant.h"
#include "Constant/LanguageConstant.h"
#include "Constant/LobbyConstant.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/PPEnums.h"
#include "BaseScene.h"


class BodyLobbyLayout;
class HeaderLobbyLayout;
class BottomLobbyLayout;
class LobbyScene : public BaseScene
{
private:
    
	cocos2d::CCLayerColor *layerSwallowTouched = nullptr;

	BodyLobbyLayout* bodyLayout;
	HeaderLobbyLayout* headerLayout;
	BottomLobbyLayout* bottomLayout;

	/// <summary>
	/// check and show strategy popups
	/// </summary>
	void checkAndShowStrategyPopups();
	bool isShowLoading = false;
	/// <summary>
	/// first enter scene
	/// </summary>
	void onBegin();
public:
	static cocos2d::Scene* createScene(ppEnum::GameScene lastScene);

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// enter UI for scene
	/// </summary>
	virtual void onEnter() override;
	/// <summary>
	/// Exit scene
	/// </summary>
	virtual void onExit() override;

	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LobbyScene);
};
