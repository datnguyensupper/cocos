#include "CWinPanelBase.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CWinPanelBase::CWinPanelBase(CGameBase* oGame):
		oGame(oGame),
		oTitle(nullptr),
		oMessage(nullptr)
	{
		this->autorelease();
	}
	CWinPanelBase::~CWinPanelBase()
	{
	}
	bool CWinPanelBase::init()
	{
		if (!Node::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		this->oBG = CSpriteButton::createButtonWithFile(res.mainGame["total_winning"], nullptr, nullptr);
		((CSpriteButton*)this->oBG)->setIsBlock(true);

		this->oTitle = Label::createWithTTF(res.fontConfigs["win_panel_title"], "YOU WON");

		this->oMessage = Label::createWithTTF(res.fontConfigs["win_panel_message"], "0");


		this->addChild(this->oBG, 0);
		this->addChild(this->oTitle, 5);
		this->addChild(this->oMessage, 5);

		GameUtils::centerNode(this);

		this->setVisible(false);

		this->oGame->getMain()->addChild(this, ORDER_WIN_PANEL);

		return true;
	}
	void CWinPanelBase::showWinPanel(const std::string & title, double iTotWin, const std::function<void()> cb)
	{
		this->show();

		this->oTitle->setString(title);

		if (iTotWin == 0) {
			this->oMessage->setString("0");
			this->runAction(Sequence::createWithTwoActions(
				DelayTime::create(CSettings::TIMER_WAITING_TEXT_WIN_PANEL),
				CallFunc::create([this, iTotWin, cb] {
				if (cb != nullptr) {
					cb();
				}
				this->hide();
			})));
			return;
		}

		this->runAction(Sequence::create(ActionFloat::create(
			CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL, 0, iTotWin, [this](float value) {
			this->oMessage->setString(UtilFunction::FormatWithCommas(value));
		}), CallFunc::create([this, iTotWin, cb] {
			this->oMessage->setString(UtilFunction::FormatWithCommas(iTotWin));
		}),
			DelayTime::create(CSettings::TIMER_WAITING_TEXT_WIN_PANEL),
			CallFunc::create([this, iTotWin, cb]{
			this->oMessage->setString(UtilFunction::FormatWithCommas(iTotWin));
			if (cb != nullptr) {
				cb();
			}
			this->hide();
		}),
			NULL));
	}
	void CWinPanelBase::showFreeSpinAdditionWinPanel(int iTotFreeSpinconst, std::function<void()> cb)
	{
		this->show();

		this->oTitle->setString("YOU WON");

		this->oMessage->setString(ToString(iTotFreeSpinconst) + " FREE SPINS");
		this->runAction(Sequence::createWithTwoActions(
			DelayTime::create(CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST),
			CallFunc::create([this, cb] {
			if (cb != nullptr) {
				cb();
			}
			this->hide();
		})));
	}
	void CWinPanelBase::showFreeSpinWinPanel(int iTotFreeSpin, int iTotMulty, const std::function<void()> cb)
	{
		if (cb != nullptr) {
			cb();
		}
	}
	void CWinPanelBase::show()
	{
		this->setVisible(true);
		Manager4Sound::getInstance()->turnOffAllSound();
		Manager4Sound::getInstance()->playTotalWin();
	}
	void CWinPanelBase::hide()
	{
		this->setVisible(false);
		Manager4Sound::getInstance()->stopTotalWin();
	}
}
