#include "TouchScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* TouchScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TouchScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TouchScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	// Add a "touch" event listener to our sprite
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](Touch* touch, Event* event)->bool {
		auto bounds = event->getCurrentTarget()->getBoundingBox();

		if (bounds.containsPoint(touch->getLocation())) {
			std::stringstream touchDetails;
			touchDetails << "Touched at OpenGL coorinates: " << 
				touch->getLocation().x << "," << "," << touch->getLocation().y << std::endl << 
				"Touched at UI coordinate: " << 
				touch->getLocationInView().x << "," << touch->getLocationInView().y << std::endl << 
				"Touched at local coordinate:" << 
				event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).x << "," << 
				event->getCurrentTarget()->convertToNodeSpace(touch->getLocation()).y << std::endl << 
				"Touch moved by:" << touch->getDelta().x << "," << touch->getDelta().y;

			MessageBox(touchDetails.str().c_str(), "Touched");
		}
		return true;
	};

	//touchListener->onTouchBegan = CC_CALLBACK_2(TouchScene::onTouchBegan, this);
	//touchListener->onTouchEnded = CC_CALLBACK_2(TouchScene::onTouchEnded, this);
	//touchListener->onTouchEnded = CC_CALLBACK_2(TouchScene::onTouchMoved, this);
	//touchListener->onTouchCancelled = CC_CALLBACK_2(TouchScene::onTouchCancelled, this);
 //   
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, sprite);
	this->addChild(sprite,0);

    return true;
}


bool TouchScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	
	labelTouchInfo->setPosition(touch->getLocation());
	labelTouchInfo->setString("You Touched Here");

	return true;
}

void TouchScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
	cocos2d::log("touch ended");
}

void TouchScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	cocos2d::log("touch moved");

}

void TouchScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
	cocos2d::log("touch cancelled");

}