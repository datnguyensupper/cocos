#include "CWinPanelLN.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CWinPanelLN::CWinPanelLN(CGameBase * oGame):CWinPanelBase(oGame)
	{
	}
	CWinPanelLN::~CWinPanelLN()
	{
	}
	bool CWinPanelLN::init()
	{
		if (!CWinPanelBase::init()) return false;

		this->oTitle->setPositionY(160);
		this->oTitle->setTextColor(Color4B(255, 254, 197, 255));
		this->oTitle->enableOutline(Color4B(135, 72, 41, 255));

		this->oMessage->setTextColor(Color4B(255, 238, 62, 255));
		this->oMessage->enableOutline(Color4B(255, 0, 0, 255));

		this->oExplosion = Sprite::createWithSpriteFrameName("Bonus-01-weaponExplodeEffects_1");
		this->oExplosion->setScale(2);
		this->addChild(this->oExplosion, 10);

		return true;
	}
	void CWinPanelLN::show()
	{
		CWinPanelBase::show();

		auto posX = RandomHelper::random_real(0.2f, 0.8f) * CSettings::CANVAS_WIDTH;
		auto posY = RandomHelper::random_real(0.2f, 0.8f) * CSettings::CANVAS_HEIGHT;
		this->oExplosion->setPosition(posX - CSettings::CANVAS_WIDTH / 2, posY - CSettings::CANVAS_HEIGHT / 2);
		this->oExplosion->runAction(RepeatForever::create(Sequence::createWithTwoActions(
			AnimationHelper::getInstance()->createAnimationByFrameName(
			GameConstant::getInstance()->getResources().mainGame["explosion_plist"],
			"Bonus-01-weaponExplodeEffects_%i",
			1,
			15,
			15,
			1),
			CallFunc::create([this]() {
			auto posX = RandomHelper::random_real(0.2f, 0.8f) * CSettings::CANVAS_WIDTH;
			auto posY = RandomHelper::random_real(0.2f, 0.8f) * CSettings::CANVAS_HEIGHT;
			this->oExplosion->setPosition(posX - CSettings::CANVAS_WIDTH / 2, posY - CSettings::CANVAS_HEIGHT / 2);
		})
			)));
	}
	void CWinPanelLN::hide()
	{
		CWinPanelBase::hide();
		this->oExplosion->stopAllActions();
	}
}
