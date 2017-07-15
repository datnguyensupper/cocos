#include "CWinPanelGE.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CWinPanelGE::CWinPanelGE(CGameBase * oGame):CWinPanelBase(oGame)
	{

	}
	CWinPanelGE::~CWinPanelGE()
	{
	}
	bool CWinPanelGE::init()
	{
		if (!CWinPanelBase::init()) return false;

		this->oTitle->setPositionY(105);
		this->oTitle->setTextColor(Color4B(255, 254, 197, 255));
		this->oTitle->enableOutline(Color4B(135, 72, 41, 255));

		this->oMessage->setPositionY(20);
		this->oMessage->setAlignment(TextHAlignment::CENTER);
		this->oMessage->setTextColor(Color4B(255, 254, 197, 255));
		this->oMessage->enableOutline(Color4B(135, 72, 41, 255));

		return true;
	}
	void CWinPanelGE::showFreeSpinWinPanel(int iTotFreeSpin, int iTotMulty, const std::function<void()> cb)
	{

		this->show();

		float quotient = iTotFreeSpin * 1.0 / iTotMulty;

		this->oTitle->setString("YOU WON");
		this->oMessage->setString("0 FREE SPINS\n0x MULTIPLIER");

		this->runAction(Sequence::create(ActionFloat::create(
			CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST, 0, iTotFreeSpin, [this, quotient](float value) {
			this->oMessage->setString(
				ToString((int)value) + " FREE SPINS" + "\n" +
				ToString((int)(value / quotient)) + "x MULTIPLIER");
		}),
			DelayTime::create(CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST),
			CallFunc::create([this, iTotFreeSpin, iTotMulty, cb] {
			if (cb != nullptr) {
				cb();
			}
			this->hide();
		}),
			NULL));
	}
}
