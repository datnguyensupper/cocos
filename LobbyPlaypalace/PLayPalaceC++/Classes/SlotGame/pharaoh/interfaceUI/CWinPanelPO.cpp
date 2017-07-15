#include "CWinPanelPO.h"
#include "SlotGame/base/game/CGameBase.h"
#include "Custom/Common/LabelAutoSize.h"

USING_NS_CC;
namespace GameSlot {
	CWinPanelPO::CWinPanelPO(CGameBase * oGame):CWinPanelBase(oGame)
	{
	}
	CWinPanelPO::~CWinPanelPO()
	{
	}
	bool CWinPanelPO::init()
	{
		if (!CWinPanelBase::init()) return false;

		this->oTitle->setPositionY(0);
		this->oTitle->setLineSpacing(-10);
		this->oTitle->setHorizontalAlignment(TextHAlignment::CENTER);
		this->oTitle->setTextColor(Color4B(255, 254, 197, 255));
		this->oTitle->enableOutline(Color4B(135, 72, 41, 255));

		this->oMessage->setPositionY(-85);
		this->oMessage->setLineSpacing(-10);
		this->oMessage->setHorizontalAlignment(TextHAlignment::CENTER);
		this->oMessage->setAlignment(TextHAlignment::CENTER);
		this->oMessage->setTextColor(Color4B(255, 254, 197, 255));
		this->oMessage->enableOutline(Color4B(135, 72, 41, 255));

		this->oMessage2 = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["win_panel_message"], "YOU WON\n0");
		//((LabelAutoSize*)this->oMessage2)->setTextAreaSize(Size(600, 200));
		this->oMessage2->setScale(0.7f);
		this->oMessage2->setPositionY(-70);
		this->oMessage2->setHorizontalAlignment(TextHAlignment::CENTER);
		this->oMessage2->setLineSpacing(-20);
		this->oMessage2->setTextColor(Color4B(255, 254, 197, 255));
		this->oMessage2->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oMessage2);

		return true;
	}
	void CWinPanelPO::showFreeSpinWinPanel(int iTotFreeSpin, int iTotMulty, const std::function<void()> cb)
	{
		this->show();

		this->oTitle->setVisible(false);

		this->oMessage->setScale(0.7f);
		this->oMessage->setPositionY(-45);

		this->oMessage->setString("YOU WON\n" + ToString(iTotFreeSpin) + "\nFREE SPINS");

		this->runAction(Sequence::createWithTwoActions(
			DelayTime::create(CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST),
			CallFunc::create([this, iTotFreeSpin, iTotMulty, cb] {
			if (cb != nullptr) {
				cb();
			}
			this->hide();
		})));
	}
	void CWinPanelPO::showBonusWinPanel(double iTotWin1, double iTotWin2, const std::function<void()> cb)
	{
		this->show();

		this->oMessage2->setVisible(true);

		this->oMessage->setScale(0.56f);
		this->oTitle->setScale(0.56f);

		this->oTitle->setPosition(-215, 12);
		this->oMessage->setPosition(215, 12);

		auto iTotWin = iTotWin1 + iTotWin2;

		float quotientWin1 = iTotWin1 * 1.0f / iTotWin;
		float quotientWin2 = iTotWin2 * 1.0f / iTotWin;

		this->runAction(Sequence::create(ActionFloat::create(
			CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST, 0, iTotWin, [this, quotientWin1, quotientWin2](float value) {
			this->oTitle->setString("BONUS 1 WON\n" + UtilFunction::FormatWithCommas(value* quotientWin1));
			this->oMessage->setString("BONUS 2 WON\n" + UtilFunction::FormatWithCommas(value* quotientWin2));
			this->oMessage2->setString("TOTAL WON " + UtilFunction::FormatWithCommas(value));
		}),
			CallFunc::create([this, iTotWin, iTotWin1, iTotWin2, cb] {
			this->oTitle->setString("BONUS 1 WON\n" + UtilFunction::FormatWithCommas(iTotWin1));
			this->oMessage->setString("BONUS 2 WON\n" + UtilFunction::FormatWithCommas(iTotWin2));
			this->oMessage2->setString("TOTAL WON " + UtilFunction::FormatWithCommas(iTotWin));
		}),
			DelayTime::create(CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST),
			CallFunc::create([this, iTotWin, iTotWin1, iTotWin2, cb] {
			if (cb != nullptr) {
				cb();
			}
			this->hide();
		}),
			NULL));
	}
	void CWinPanelPO::show()
	{
		CWinPanelBase::show();
		this->oTitle->setScale(1.0f);
		this->oTitle->setPosition(Vec2::ZERO);
		this->oTitle->setVisible(true);
		this->oMessage->setScale(1.0f);
		this->oMessage->setPosition(0, -85);
		this->oMessage2->setVisible(false);
	}
}
