#pragma once

#include "cocos2d.h"

class SplashScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
private:
	void GoToGameScene(float dt);
	void loadRS();
	void UpdateTimer(float dt);

	
	cocos2d::Sprite * btn_play;
};

