#include "CWinPanelRE.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CWinPanelRE::CWinPanelRE(CGameBase * oGame):CWinPanelBase(oGame)
	{
	}
	CWinPanelRE::~CWinPanelRE()
	{
	}
	bool CWinPanelRE::init()
	{
		if (!CWinPanelBase::init()) return false;

		this->oBG->setScaleX(2);

		this->oTitle->setPositionY(80);
		this->oTitle->setLineSpacing(-10);
		this->oTitle->setHorizontalAlignment(TextHAlignment::CENTER);
		this->oTitle->setTextColor(Color4B(255, 254, 197, 255));
		this->oTitle->enableOutline(Color4B(135, 72, 41, 255));

		this->oMessage->setPositionY(0);
		this->oMessage->setLineSpacing(-10);
		this->oMessage->setHorizontalAlignment(TextHAlignment::CENTER);
		this->oMessage->setAlignment(TextHAlignment::CENTER);
		this->oMessage->setTextColor(Color4B(255, 254, 197, 255));
		this->oMessage->enableOutline(Color4B(135, 72, 41, 255));

		this->oMessage2 = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["win_panel_message"], "YOU WON\n0");
		this->oMessage2->setHorizontalAlignment(TextHAlignment::CENTER);
		this->oMessage2->setLineSpacing(-20);
		this->oMessage2->setPositionY(-50);
		this->oMessage2->setTextColor(Color4B(255, 254, 197, 255));
		this->oMessage2->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oMessage2);

		return true;
	}
	void CWinPanelRE::showBonusWinPanel(double iTotWin, int iTotMulty, const std::function<void()> cb)
	{
		this->show();

		this->oMessage2->setVisible(true);

		this->oTitle->setScale(0.7f);
		this->oTitle->setPosition(-210, 90);
		this->oMessage->setScale(0.7f);
		this->oMessage->setPosition(210, 90);

		this->oTitle->setString("TOTAL BET\n" + UtilFunction::FormatWithCommas(iTotWin / iTotMulty));
		this->oMessage->setString("MULTIPLIER\n" + UtilFunction::FormatWithCommas(iTotMulty));
		this->oMessage2->setString("YOU WON\n0");

		this->runAction(Sequence::create(ActionFloat::create(
			CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL, 0, iTotWin, [this](float value) {
			this->oMessage2->setString("YOU WON\n" + UtilFunction::FormatWithCommas((int)value));
		}), CallFunc::create([this, iTotWin, cb] {
			this->oMessage2->setString("YOU WON\n" + UtilFunction::FormatWithCommas(iTotWin));
		}),
			DelayTime::create(CSettings::TIMER_WAITING_TEXT_WIN_PANEL),
			CallFunc::create([this, iTotWin, cb] {
			this->oMessage2->setString("YOU WON\n" + UtilFunction::FormatWithCommas(iTotWin));
			if (cb != nullptr) {
				cb();
			}
			this->hide();
		}),
			NULL));
	}
	void CWinPanelRE::show()
	{
		CWinPanelBase::show();
		this->oTitle->setPosition(0, 85);
		this->oTitle->setScale(1.0f);
		this->oMessage->setPosition(Vec2::ZERO);
		this->oMessage->setScale(1.0f);
		this->oMessage2->setVisible(false);
	}
}
