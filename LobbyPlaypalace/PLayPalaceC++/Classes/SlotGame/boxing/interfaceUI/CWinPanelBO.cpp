#include "CWinPanelBO.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CWinPanelBO::CWinPanelBO(CGameBase * oGame):CWinPanelBase(oGame)
	{
	}
	CWinPanelBO::~CWinPanelBO()
	{
	}
	bool CWinPanelBO::init()
	{
		if (!CWinPanelBase::init()) return false;

		this->oTitle->setPositionY(125);
		this->oTitle->setTextColor(Color4B::WHITE);
		this->oTitle->enableOutline(Color4B::BLACK);

		this->oMessage->setPositionY(0);
		this->oMessage->setAlignment(TextHAlignment::CENTER);
		this->oMessage->setTextColor(Color4B(255, 250, 0, 255));
		this->oTitle->enableOutline(Color4B::BLACK);

		this->oMessage2 = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["win_panel_title"], "FREE SPINS");
		this->oMessage2->setPositionY(-45);
		this->oMessage2->setTextColor(Color4B::WHITE);
		this->oMessage2->enableOutline(Color4B::BLACK);

		this->addChild(this->oMessage2);

		return true;
	}
	void CWinPanelBO::showFreeSpinWinPanel(int iTotFreeSpin, int iTotMulty, const std::function<void()> cb)
	{
		this->show();

		this->oTitle->setPositionY(125);
		this->oMessage->setPositionY(45);

		this->oMessage2->setVisible(true);

		this->oTitle->setString("YOU WON");
		this->oMessage->setString(ToString(iTotFreeSpin));

		this->runAction(Sequence::createWithTwoActions(
			DelayTime::create(CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST),
			CallFunc::create([this, iTotFreeSpin, iTotMulty, cb] {
			if (cb != nullptr) {
				cb();
			}
			this->hide();
		})));
	}
	void CWinPanelBO::show()
	{
		CWinPanelBase::show();
		this->oTitle->setPositionY(125);
		this->oMessage->setPositionY(0);
		this->oMessage2->setVisible(false);
	}
}
