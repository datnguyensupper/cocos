#include "MultiTouch.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MultiTouch::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MultiTouch::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MultiTouch::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	// Create an array of Labels to display touch locations and add them to this node, defaulted to invisible
	for (int i = 0; i < MAX_TOUCHES; ++i) {
		labelTouchLocations[i] = Label::createWithSystemFont("", "Arial", 42);
		labelTouchLocations[i]->setVisible(false);
		this->addChild(labelTouchLocations[i]);
	}

	auto eventListener = EventListenerTouchAllAtOnce::create();

	//create an eventListener to handle multiple touches, using a lambda, cause baby, it's C++11
	eventListener->onTouchesBegan = [=](const std::vector<Touch*>&touches, Event*event) {
		// Clear all visible touches just in case there are less fingers touching than last time
		std::for_each(labelTouchLocations, labelTouchLocations + MAX_TOUCHES, [](Label* touchLabel) {
			touchLabel->setVisible(false);
		});

		// For each touch in the touches vector, set a Label to display at it's location and make it visible
		for (int i = 0; i < touches.size(); ++i) {
			labelTouchLocations[i]->setPosition(touches[i]->getLocation());
			labelTouchLocations[i]->setVisible(true);
			labelTouchLocations[i]->setString("Touched");
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);


    return true;
}
