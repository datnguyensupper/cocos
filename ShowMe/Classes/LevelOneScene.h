#pragma once

#include "BaseScene.h"

class SpritePath;
class LevelOneScene : public BaseScene{
private:
    cocos2d::Sprite * player;
    cocos2d::Vec2 playerFirstPosition;
	cocos2d::Label * label;
	SpritePath * spritePath;
	float speed;
public:
	static cocos2d::Scene* createScene();

    virtual bool init();
    void update(float delta);
	void createPlayer();
	void handleTouchInput();

	// implement the "static create()" method manually
	CREATE_FUNC(LevelOneScene);
    
};

