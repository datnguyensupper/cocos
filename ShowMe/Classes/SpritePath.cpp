#include "SpritePath.h"
#include "PhysicBodyAdjustRotation.h"
#include "Helper4Calculate.h"
#include "Helper4Sprite.h"

USING_NS_CC;


SpritePath * SpritePath::create(cocos2d::Sprite * player) {

	SpritePath *pRet = new(std::nothrow) SpritePath();
	if (pRet && pRet->init()){
		pRet->setPlayer(player);
		pRet->autorelease();
		return pRet;
	}else{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

void SpritePath::setPlayer(cocos2d::Sprite * _player) {
	player = _player;
}

SpritePath::~SpritePath(){
    arrayOfTexPath.clear();
}

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

    
//    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("light.png");
//    cocos2d::Texture2D::TexParams tp ;
//    tp.minFilter =GL_LINEAR;
//    tp.magFilter =GL_LINEAR;
//    tp.wrapS =GL_REPEAT;
//    tp.wrapT =GL_REPEAT;
//    texture->setTexParameters(&tp);
//    spriteBG = CCSprite::createWithTexture(texture, CCRectMake(0, 0, 135, 174));
    
    spriteBG = Sprite::create("light.png");
    
    int yPosition = 0;
    for(int i = 0; i < 15; i++){
        auto spriteTex = Sprite::create("light_texture.png");
        spriteTex->setAnchorPoint(Vec2(0, 0));
        Helper4Sprite::setBlendModeAdd(spriteTex);
        spriteBG->addChild(spriteTex);
        arrayOfTexPath.push_back(spriteTex);
    }
//    cocos2d::ui::Scale9Sprite::create("light.png", cocos2d::Rect::ZERO, Rect(10, 10, 20, 20));
//	spriteBG->setScale9Enabled(true);
	spriteBG->setContentSize(Size(spriteBG->getContentSize().width, 0));
	spriteBG->setPosition(firstPoint);
	spriteBG->setAnchorPoint(Vec2(0.5, 0));
	
	addChild(spriteBG);

    return true;
}

void SpritePath::adjustFirstPoint() {
	float distance2Player = firstPoint.distance(player->getPosition());
	if (distance2Player <= player->getContentSize().width + spriteBG->getContentSize().width) {
		firstPoint.x = player->getPosition().x+ player->getContentSize().width + spriteBG->getContentSize().width;
	}
}

void SpritePath::adjustSecondPoint() {
	//return;
	float pathAngle = Helper4Calculate::getInstance()->angle(firstPoint, secondPoint);
	float playerAngle = Helper4Calculate::getInstance()->angle(firstPoint, player->getPosition());
	float delta = abs(pathAngle - playerAngle);
	if (delta > 180) {
		delta = 360 -delta;
	}
	//log("delta : %f", delta);
	//return;
	if (delta < 10) {
		Point newPoint2 = player->getPosition();
		newPoint2.x = player->getPosition().x + player->getContentSize().width + spriteBG->getContentSize().width;

		float oldDistance = firstPoint.distance(secondPoint);
		float newDistance = firstPoint.distance(newPoint2);
		float ratio = oldDistance*1.0 / newDistance;
		secondPoint = (newPoint2 - firstPoint)*ratio+firstPoint;
	}
}

void SpritePath::adjustSprite(cocos2d::Point _firstPoint, cocos2d::Point _secondPoint) {
	firstPoint = _firstPoint;
	adjustFirstPoint();
	delayForSetSecondPoint = 0;
	adjustSprite(_secondPoint);
}

void SpritePath::adjustSprite(cocos2d::Point _secondPoint) {
	if (delayForSetSecondPoint > 0) {
		delayForSetSecondPoint--;
		return;
	}
	delayForSetSecondPoint = 2;

	secondPoint = _secondPoint;
	adjustSecondPoint();
	adjustSprite(true);
}

void SpritePath::adjustSpriteWithoutPhysic(cocos2d::Point _secondPoint) {
	secondPoint = _secondPoint;
	adjustSecondPoint();
	adjustSprite(false);
}

void SpritePath::adjustSprite(bool havePhysic) {
	float distance = firstPoint.distance(secondPoint);

    distance = min(distance, arrayOfTexPath.size()*arrayOfTexPath[0]->getContentSize().height);
	spriteBG->setContentSize(Size(50, distance ));
    float yPosition = 0;
    int count = 0;
    log(distance);
    for(; count < arrayOfTexPath.size(); count++){
        Sprite* texPath = arrayOfTexPath[count];
        texPath->setVisible(true);
        texPath->setPositionY(yPosition);
        yPosition += texPath->getContentSize().height;
        if(yPosition > distance) break;
    }
    for(; count < arrayOfTexPath.size(); count++){
        Sprite* texPath = arrayOfTexPath[count];
        texPath->setVisible(false);
    }
    
//    spriteBG->setContentSize(Size(spriteBG->getContentSize().width, distance ));

	spriteBG->setRotation(Helper4Calculate::getInstance()->angle(firstPoint,secondPoint));
	spriteBG->setPosition(firstPoint);
	if(havePhysic) updatePhysic();
	else spriteBG->setOpacity(255 * 0.5);

}

void SpritePath::updatePhysic() {
	removePhysic();

	spriteBG->setOpacity(255);
	physicBody = PhysicBodyAdjustRotation::createBox(Size(spriteBG->getContentSize().width, spriteBG->getContentSize().height),
		PhysicsMaterial(0.0f, 0.0f, 0.0f));
	physicBody->setRotationOffset(spriteBG->getRotation());
	//set the body isn't affected by the physics world's gravitational force
	physicBody->setRotationEnable(true);
	physicBody->setGravityEnable(false);
	physicBody->setDynamic(false);
	physicBody->setCollisionBitmask(BOUND_COLLISION_BITMASK);
	physicBody->setContactTestBitmask(true);
	spriteBG->setPhysicsBody(physicBody);
	//playerRed->addComponent(playerBodyRed);
}

void SpritePath::removePhysic() {
	if (physicBody == nullptr) return;
	physicBody->removeFromWorld();
	physicBody = nullptr;
}
