#pragma once

#include "BaseScene.h"
#include "ui/CocosGUI.h"

class SplashScene : public BaseScene
{
public:
    static cocos2d::Scene* createScene();
	cocos2d::ui::Button* tutorialBtn;

    virtual bool init();
	void createTutorialView();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

