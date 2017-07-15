#pragma once

#include "cocos2d.h"
#include "SlotGame/base/interfaceUI/ICharacter.h"

namespace GameSlot {
	class CCharacterGE : public ICharacter
	{
	private:
		cocos2d::Sprite* sprite;
	public:
		CCharacterGE();
		~CCharacterGE();

		void create(CGameBase* _oGame);
		void playIdle();
		void playFreeSpin();
		void playWin();
	};
}
