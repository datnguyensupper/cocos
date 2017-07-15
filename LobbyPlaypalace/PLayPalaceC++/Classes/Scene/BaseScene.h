#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: InitSession.h, InitSession.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Constant/PPEnums.h"
namespace GameSlot {
    class GameSlotScene;
}
class BaseScene : public cocos2d::Scene
{
protected:
    /// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
    virtual void update(float dt);
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    float scaleDownRatio;
private:
    
    static BaseScene* currentScene;
    std::string messageGoToLoginScene;
    std::string titleGoToLoginScene;
    bool isGoingToLoginScene = false;
public:
    static BaseScene* getCurrentScene();
	/// <summary>
	/// go to login scene, show or dont show popup with title and message
	/// </summary>
	/// <param name="title">title popup</param>
	/// <param name="message">message popup</param>
    void gotoLoginScene(std::string title = "", std::string message = "");
	/// <summary>
	/// go to login scene and show popup server maintainance
	/// </summary>
    void gotoLoginSceneServerMaintenance();
	/// <summary>
	/// go to login scene and show popup connection error
	/// </summary>
    void gotoLoginSceneLostConnection();
	/// <summary>
	/// go to login scene and show popup login in another place
	/// </summary>
    void gotoLoginSceneLoginAnotherPlace();
	/// <summary>
	/// go to login scene and show popup something wrong
	/// </summary>
    void gotoLoginSceneSomethingWrong();
	/// <summary>
	/// go to login scene with delay
	/// </summary>
	/// <param name="delay">delay in second</param>
    void gotoLoginSceneWithDelay(float delay);
//    void forceGotoLoginScene(std::string message);
	/// <summary>
	/// go to lobby scene
	/// </summary>
	/// <param name="dt"></param>
    void gotoLobbyScene(float dt);
	/// <summary>
	/// go to lucky wheel scene
	/// </summary>
	/// <param name="dt"></param>
    void gotoLuckyWheelScene(float dt);
	/// <summary>
	/// go to test game scene
	/// </summary>
	/// <param name="dt"></param>
    void gotoGameTestScene(float dt);
	/// <summary>
	/// go to game slot scene
	/// </summary>
	/// <param name="gameId">game slot id</param>
	/// <returns></returns>
    GameSlot::GameSlotScene* gotoGameSlotScene(int gameId);
	/// <summary>
	/// go to init session scene
	/// </summary>
	/// <param name="dt">delay by second</param>
	/// <param name="loginFrom">type of user login</param>
    void gotoInitSessionScene(float dt, ppEnum::LoginAndInitSSFrom loginFrom);
	/// <summary>
	/// go to init session scene after delay
	/// </summary>
	/// <param name="dt">delay by second</param>
    void gotoInitSessionScene(float dt);
    
    
    virtual void onEnter() override;
    
    // implement the "static create()" method manually
    /// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(BaseScene);
};
