#pragma once

#include "cocos2d.h"

class MultiTouch : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MultiTouch);
private:
	const static int MAX_TOUCHES = 5;
protected:
	cocos2d::Label * labelTouchLocations[MAX_TOUCHES];
};

