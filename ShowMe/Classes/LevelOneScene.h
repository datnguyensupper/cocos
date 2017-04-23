#pragma once

#include "BaseScene.h"
#include "EnemyController.h"

class SpritePath;
class LevelOneScene : public BaseScene{
private:
	bool isDied = false;
	float deadSpace = false;
	float delayTime = 0;
    cocos2d::Sprite * player;
    cocos2d::Vec2 playerFirstPosition;
	cocos2d::Label * label;
	SpritePath * spritePath;
	float speed;
	EnemyController enemyController;
public:
	static cocos2d::Scene* createScene();

    virtual bool init();
    void handlePhysicEvent();
    void update(float delta);
    void spawnEnemy(float delta);
	void createPlayer();
	void handleTouchInput();
	void doDead();

	bool onContactBegin(cocos2d::PhysicsContact & contact);
	void onContactSeparate(cocos2d::PhysicsContact & contact);

	// implement the "static create()" method manually
	CREATE_FUNC(LevelOneScene);
    
};

