#pragma once

#include "cocos2d.h"

#include "SlotGame/base/interfaceUI/ICharacter.h"

namespace GameSlot {
	class CCharacterLN : public ICharacter
	{
	private:
		cocos2d::Sprite* nezhaSprite;
	public:
		CCharacterLN();
		~CCharacterLN();

		void create(CGameBase* _oGame);
		void playIdle();
		void playFreeSpin();
		void playWin();
	};
}
