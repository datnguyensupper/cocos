#include "PhysicBodyAdjustRotation.h"
using namespace std;
USING_NS_CC;

PhysicBodyAdjustRotation::PhysicBodyAdjustRotation()
{

	
}

PhysicBodyAdjustRotation* PhysicBodyAdjustRotation::createBox(const cocos2d::Size& size, const cocos2d::PhysicsMaterial& material, const cocos2d::Vec2& offset)
{
	PhysicBodyAdjustRotation* body = new (std::nothrow) PhysicBodyAdjustRotation();
	if (body && body->init())
	{
		body->addShape(PhysicsShapeBox::create(size, material, offset));
		body->autorelease();
		return body;
	}

	CC_SAFE_DELETE(body);
	return nullptr;
}

void PhysicBodyAdjustRotation::onAdd() {
	PhysicsBody::onAdd();
	setRotationOffset(0);
}