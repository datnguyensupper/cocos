#include "SpritePath.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool SpritePath::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    return true;
}
