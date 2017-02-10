#include "KeyTabletScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* KeyTabletScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = KeyTabletScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool KeyTabletScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Create a text field
	TextFieldTTF * textField = cocos2d::TextFieldTTF::textFieldWithPlaceHolder("Click here to type", cocos2d::Size(400,200), TextHAlignment::LEFT, "Arial", 42.0);
	textField->setPosition(this->getBoundingBox().getMidX(), this->getBoundingBox().getMaxX()-20);
	textField->setColorSpaceHolder(Color3B::GREEN);
	textField->setDelegate(this);

	this->addChild(textField);

	// Add a touch handler to our textfield that will show a keyboard when touched
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [](cocos2d::Touch*touch, cocos2d::Event *event)->bool {
		try {
			// Show me on screen keyboard
			auto textField = dynamic_cast<TextFieldTTF *>(event->getCurrentTarget());
			textField->attachWithIME();
			return true;
		}
		catch (std::bad_cast & err) { return true; }
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, textField);

    return true;
}

KeyTabletScene::~KeyTabletScene() {}


bool KeyTabletScene::onTextFieldAttachWithIME(cocos2d::TextFieldTTF * sender) {
	return TextFieldDelegate::onTextFieldAttachWithIME(sender);
}

bool KeyTabletScene::onTextFieldDetachWithIME(cocos2d::TextFieldTTF * sender) {
	return TextFieldDelegate::onTextFieldDetachWithIME(sender);
}

bool KeyTabletScene::onTextFieldInsertText(cocos2d::TextFieldTTF * sender, const char *text, size_t nLen) {
	return TextFieldDelegate::onTextFieldInsertText(sender,text,nLen);

}

bool KeyTabletScene::onTextFieldDeleteBackward(cocos2d::TextFieldTTF * sender, const char *delText, size_t nLen) {
	return TextFieldDelegate::onTextFieldDeleteBackward(sender,delText,nLen);

}

bool KeyTabletScene::onVisit(cocos2d::TextFieldTTF * sender, cocos2d::Renderer * renderer, cocos2d::Mat4 const &transform, uint32_t flags) {
	return TextFieldDelegate::onVisit(sender,renderer,transform,flags);

}

