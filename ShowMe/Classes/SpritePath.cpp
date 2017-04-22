#include "SpritePath.h"
#include "PhysicBodyAdjustRotation.h"

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
	firstPoint = Point::ZERO;
	secondPoint = Point::ZERO;

	spriteBG = cocos2d::ui::Scale9Sprite::create("CloseNormal.png", cocos2d::Rect::ZERO, Rect(10, 10, 20, 20));
	spriteBG->setScale9Enabled(true);
	spriteBG->setContentSize(Size(spriteBG->getContentSize().width, 0));
	spriteBG->setPosition(firstPoint);
	spriteBG->setAnchorPoint(Vec2(0.5, 0));
	
	addChild(spriteBG);

    return true;
}

void SpritePath::adjustSprite(cocos2d::Point _firstPoint, cocos2d::Point _secondPoint) {
	firstPoint = _firstPoint;
	secondPoint = _secondPoint;
	adjustSprite();
}

void SpritePath::adjustSprite(cocos2d::Point _secondPoint) {
	secondPoint = _secondPoint;
	adjustSprite();
}

void SpritePath::adjustSprite() {
	float distance = firstPoint.distance(secondPoint);
	Vec2 vectorDirection = secondPoint - firstPoint;
	float angle = vectorDirection.getAngle();
	log("direction: x=%f y=%f angle: %f",vectorDirection.x,vectorDirection.y,angle* (180.0 / 3.14));
	spriteBG->setContentSize(Size(spriteBG->getContentSize().width, distance ));

	spriteBG->setRotation(-angle * (180.0 / 3.14)+90);
	spriteBG->setPosition(firstPoint);
	updatePhysic();
}

void SpritePath::updatePhysic() {
	removePhysic();


	physicBody = PhysicBodyAdjustRotation::createBox(Size(spriteBG->getContentSize().width, spriteBG->getContentSize().height),
		PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicBody->setRotationOffset(spriteBG->getRotation());
	//set the body isn't affected by the physics world's gravitational force
	physicBody->setRotationEnable(true);
	physicBody->setGravityEnable(false);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(PLAYER_COLLISION_BITMASK_RED);
	physicBody->setContactTestBitmask(true);
	spriteBG->setPhysicsBody(physicBody);
	//playerRed->addComponent(playerBodyRed);
}

void SpritePath::removePhysic() {
	if (physicBody == nullptr) return;
	physicBody->removeFromWorld();
	physicBody = nullptr;
}