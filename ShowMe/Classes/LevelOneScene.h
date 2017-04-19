#pragma once

#include "BaseScene.h"

class LevelOneScene : public BaseScene{
public:
	static cocos2d::Scene* createScene();

    virtual bool init();
	void createPlayer();

	// implement the "static create()" method manually
	CREATE_FUNC(LevelOneScene);
    
};

