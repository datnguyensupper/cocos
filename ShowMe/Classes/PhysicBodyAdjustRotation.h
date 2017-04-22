#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: LanguageManager.h, LanguageManager.cpp
*/

#include "cocos2d.h"

class PhysicBodyAdjustRotation : public cocos2d::PhysicsBody{
protected:
	void onAdd();
public:
	PhysicBodyAdjustRotation();

	static PhysicBodyAdjustRotation* createBox(const cocos2d::Size& size, const cocos2d::PhysicsMaterial& material = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, const cocos2d::Vec2& offset = cocos2d::Vec2::ZERO);
};