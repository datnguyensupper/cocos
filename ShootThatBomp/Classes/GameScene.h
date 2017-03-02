#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::PhysicsWorld * physicWorld;
public:
    static cocos2d::Scene* createScene();

	void setPhysicWorld(cocos2d::PhysicsWorld *_physicWorld) {
		physicWorld = _physicWorld;
	};
    virtual bool init();
	void createWorldBounds(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

