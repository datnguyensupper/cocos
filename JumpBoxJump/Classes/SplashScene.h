#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::Layer
{
private:
	void SplashScene::showBtnMove2NextScene(float dt);
	void GoToGameScene(float dt);

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScene);
};

#endif // __HELLOWORLD_SCENE_H__
