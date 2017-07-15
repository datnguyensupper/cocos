#pragma once

#include "cocos2d.h"
namespace GameSlot {
	class CJellyFishDB : public cocos2d::Sprite
	{
	private:
		cocos2d::Vec2 moveDirection;
		float speed = 2;
		bool isMoving = false;
		void calculateDirection();
	public:
		CJellyFishDB();
		~CJellyFishDB();

		void start();

		void update(float dt);
	};
}