#pragma once

#include "cocos2d.h"
#include "Util/PoolSystem.h"

namespace GameSlot {
	class CReel;
	class CEaglePO : public PoolObject
	{
	private:
		cocos2d::Sprite* oEagle;
	public:
		CEaglePO();

		void init(CReel* oGame);

		void fly(const cocos2d::Vec2& pos);
	};
}
