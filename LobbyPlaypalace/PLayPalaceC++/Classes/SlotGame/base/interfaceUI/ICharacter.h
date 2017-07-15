#pragma once
#include "Manager/ScaleManager.h"

namespace GameSlot {
	class CGameBase;
	class ICharacter
	{
	protected:
		cocos2d::Size visibleSize;
		cocos2d::Vec2 origin;
		float scaleDownRatio;
	public:
		void init() {
			visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
			origin = cocos2d::Director::getInstance()->getVisibleOrigin();
			scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
		};
		virtual ~ICharacter() {};
		virtual void create(CGameBase* _oGame) = 0;
		virtual void playIdle() = 0;
		virtual void playFreeSpin() = 0;
		virtual void playWin() = 0;
	};
}