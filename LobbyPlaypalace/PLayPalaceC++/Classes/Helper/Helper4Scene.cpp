#include "Helper4Scene.h"
#include "Scene/BaseScene.h"

USING_NS_CC;

cocos2d::Scene* Helper4Scene::getRunningScene(){
    Scene * runningScene = Director::getInstance()->getRunningScene();
    if(runningScene == nullptr ||
       runningScene->getTag() < 0){
        return BaseScene::getCurrentScene();
        
    }
    return runningScene;
}


bool Helper4Scene::isUnexpectedProblemWithCurrentScene(){
    Scene * runningScene = Director::getInstance()->getRunningScene();
    return (runningScene == nullptr ||
            runningScene->getTag() < 0);
}
