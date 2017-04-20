#pragma once

#include "BaseScene.h"
#include "ui/CocosGUI.h"

class LevelOneScene : public BaseScene{
private:
    cocos2d::Sprite * player;
    cocos2d::ui::Scale9Sprite * ninePath;
public:
	static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float delta);
	void createPlayer();

	// implement the "static create()" method manually
	CREATE_FUNC(LevelOneScene);
    
};

