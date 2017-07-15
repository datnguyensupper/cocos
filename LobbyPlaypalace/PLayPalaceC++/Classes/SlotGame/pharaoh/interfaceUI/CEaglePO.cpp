#include "CEaglePO.h"
#include "SlotGame/base/interfaceUI/CReel.h"
#include "Helper/AnimationHelper.h"

USING_NS_CC;
namespace GameSlot {
	CEaglePO::CEaglePO()
	{
	}
	void CEaglePO::init(CReel* oReel)
	{
		this->oEagle = Sprite::createWithSpriteFrameName("eagle_animation0");
		this->oEagle->setVisible(false);

		oReel->addChild(this->oEagle, ORDER_REEL_WINANIM);
	}
	void CEaglePO::fly(const cocos2d::Vec2 & pos)
	{
		this->oEagle->setPosition(pos);
		this->oEagle->setVisible(true);
		this->oEagle->setScale(1.35f);
		this->oEagle->runAction(Sequence::create(
			AnimationHelper::getInstance()->createAnimationByFrameName(
				GameConstant::getInstance()->getResources().mainGame["freespin_eagle_plist"],
				"eagle_animation%i",
				0,
				27,
				25,
				1),
			CallFunc::create([this, pos]() {
			this->oEagle->setSpriteFrame("symbol_11-0-5");
			this->oEagle->setScale(1);
			this->oEagle->setPosition(pos + Vec2(CSettings::SYMBOL_WIDTH / 2, - CSettings::SYMBOL_HEIGHT / 2));
		}),
			DelayTime::create(1.0f),
			CallFunc::create([this]() {
			this->oEagle->setScale(1.3f);
			this->oEagle->setSpriteFrame("eagle_animation0");
			this->oEagle->setVisible(false);
			this->system->destroy(this);
		}), NULL));
	}
}
