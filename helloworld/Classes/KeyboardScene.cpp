#include "KeyboardScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* KeyboardScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = KeyboardScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool KeyboardScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	//auto sprite = Sprite::create("HelloWorld.png");
	//sprite->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));

	//this->addChild(sprite,0);

	//// Add a "touch" event listener to our sprite
	//auto eventListener = EventListenerKeyboard::create();
	//eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)->bool {
	//	
	//	Vec2 loc = event->getCurrentTarget()->getPosition();
	//	switch (keyCode)
	//	{
	//	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	//	case EventKeyboard::KeyCode::KEY_A:
	//		event->getCurrentTarget()->setPosition(--loc.x,loc.y);
	//		break;
	//	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	//	case EventKeyboard::KeyCode::KEY_D:
	//		event->getCurrentTarget()->setPosition(++loc.x, loc.y);
	//		break;
	//	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	//	case EventKeyboard::KeyCode::KEY_W:
	//		event->getCurrentTarget()->setPosition(loc.x, ++loc.y);
	//		break;
	//	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	//	case EventKeyboard::KeyCode::KEY_S:
	//		event->getCurrentTarget()->setPosition(loc.x, --loc.y);
	//		break;
	//	default:
	//		break;
	//	}

		//return true;
	//};

	//touchListener->onTouchBegan = CC_CALLBACK_2(TouchScene::onTouchBegan, this);
	//touchListener->onTouchEnded = CC_CALLBACK_2(TouchScene::onTouchEnded, this);
	//touchListener->onTouchEnded = CC_CALLBACK_2(TouchScene::onTouchMoved, this);
	//touchListener->onTouchCancelled = CC_CALLBACK_2(TouchScene::onTouchCancelled, this);
	//   
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, sprite);

	label = cocos2d::Label::createWithSystemFont("Press the CTRL Key", "Arial", 32);
	label->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMidY());
	addChild(label);

	auto eventListerner = EventListenerKeyboard::create();

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
	eventListerner->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		// If a key already exists, do nothing as it will already have a time stamp
		// Otherwise, set's the timestamp to now
		if (keys.find(keyCode) == keys.end()) {
			keys[keyCode] = std::chrono::high_resolution_clock::now();
		}
	};
	eventListerner->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event * event) {
		// remove the key. std::map.erase() doesn't care if the key doesnt exist
		keys.erase(keyCode);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListerner, this);

	// Let cocos know we have an update function to be called
	// No worries, ill cover this in more detail later on
	this->scheduleUpdate();
    return true;
}


bool KeyboardScene::isKeyPressed(cocos2d::EventKeyboard::KeyCode code) {
	// Check if the key is currently pressed by seeing it it's in the std::map keys
	// In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
	if (keys.find(code) != keys.end()) {
		return true;
	}
	return false;
}

double KeyboardScene::keyPressedDuration(cocos2d::EventKeyboard::KeyCode code) {
	if (!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
		return 0; // Not pressed, so no duration obviously

	// Return the amount of time that has elapsed between now and when the user
	// first started holding down the key in milliseconds
	// Obviously the start time is the value we hold in our std::map keys
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-keys[code]).count();
}

void KeyboardScene::update(float delta) {
	// Register an update function that checks to see if the CTRL key is pressed
	// and if it is displays how long, otherwise tell the user to press it
	Node::update(delta);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL)) {
		std::stringstream ss;
		ss << "Control key has been pressed for " << keyPressedDuration(EventKeyboard::KeyCode::KEY_CTRL) << " ms";
		label->setString(ss.str().c_str());
	}
	else
		label->setString("Press the CTRL Key");
}

//Because cocos2d-x requires createScene to be static, we need to make other non_pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> KeyboardScene::keys;
