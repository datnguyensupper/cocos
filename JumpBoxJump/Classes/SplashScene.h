#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Layer
{
private:
	void GoToGameScene(float dt);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif // __HELLOWORLD_SCENE_H__
