#pragma once

#include "cocos2d.h"

class PhysicScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

	bool onContactBegin(cocos2d::PhysicsContact & contact);

    // implement the "static create()" method manually
    CREATE_FUNC(PhysicScene);
};

