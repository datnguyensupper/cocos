#pragma once
/**
* creator: Dat
* date: 2017-02-06
* file: GameSlotTestScene.h, GameSlotTestScene.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Scene/BaseScene.h"

class GameSlotTestScene : public BaseScene
{
private:
    
	/// <summary>
	/// create game slot UI
	/// </summary>
	void createGameSlotUI();
	/// <summary>
	/// create particle snow
	/// </summary>
	void createParticalSnow();

	/// <summary>
	/// test button for download in lobby
	/// </summary>
	/// <param name="position"></param>
	/// <param name="gameId"></param>
	/// <param name="gameImgPath"></param>
	void createGameSlotUIBtn(cocos2d::Vec2 position, std::string gameId, std::string gameImgPath);

	/// <summary>
	/// test button for download in background
	/// </summary>
	/// <param name="position"></param>
	/// <param name="gameId"></param>
	/// <param name="gameImgPath"></param>
	void createGameSlotUIBtnBackgroundThread(cocos2d::Vec2 position, std::string gameId, std::string gameImgPath);
public:
	static cocos2d::Scene* createScene();

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	// implement the "static create()" method manually
	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(GameSlotTestScene);
};
