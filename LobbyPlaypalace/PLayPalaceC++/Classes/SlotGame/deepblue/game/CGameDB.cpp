#include "CGameDB.h"
#include "CBonusFreeSpinDB.h"
#include "CDoubleUpDB.h"
#include "../interfaceUI/CInterfaceDB.h"
#include "../interfaceUI/CWinPanelDB.h"
#include "../interfaceUI/CJellyFishDB.h"

USING_NS_CC;
namespace GameSlot {
	CGameDB::CGameDB(CMainBase * _oMain):
		CGameBase(_oMain),
		oBonusFreeSpin(nullptr)
	{
	}
	CGameDB::~CGameDB()
	{

	}
	bool CGameDB::init()
	{
		if (!CGameBase::init()) return false;

		this->oDoubleUp = new CDoubleUpDB(this);
		this->oBonusFreeSpin = new CBonusFreeSpinDB(this);

		return true;
	}
	void CGameDB::initBackground()
	{
		CGameBase::initBackground();

		for (int i = 0; i < 3; ++i) {
			auto fish = new CJellyFishDB();
			this->aJellyFish.pushBack(fish);
			this->addChild(fish, ORDER_BG);

			fish->start();
		}
	}
	void CGameDB::initInterface()
	{
		this->oInterface = new CInterfaceDB(this);
		this->oInterface->init();
	}
	void CGameDB::initWinPanel()
	{
		this->oWinPanel = new CWinPanelDB(this);
		CGameBase::initWinPanel();
	}
	void CGameDB::initReels()
	{
		this->oReel = new CReel(this);
		CGameBase::initReels();
		this->oReel->setPosition(Vec2(0, 0));
	}
	bool CGameDB::checkLastState()
	{
		if (CGameBase::checkLastState()) {
			auto bonusHistory = this->oMain->getBonusHistory();
			switch (this->iBonusActive)
			{
			case BONUS_TYPE::BONUS_FREESPIN:
				this->changeToFreeSpinState(
					bonusHistory->counter,
					bonusHistory->multiplier
					);
				break;
			case BONUS_TYPE::BONUS_TYPE_3:
				if (this->iStepBonus == 0) {
					Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);
				}
				this->oBonusFreeSpin->show(
					bonusHistory->counter,
					bonusHistory->multiplier);
				break;
			case BONUS_TYPE::BONUS_DOUBLE_UP:
				this->oDoubleUp->show(bonusHistory->win);
				break;
			default:
				break;
			}
			return true;
		}
		return false;
	}
	void CGameDB::onSpinReceived(
		int ** aWheels,
		ObjectMagicItemReceiveAfterSpin *oMagicItemAfterSpin,
		const vector<ObjectWinPosition>& aWinPosition, 
		const vector<ObjectTableWin>& aTableWin,
		int iBonus, 
		int countFreeSpin)
	{
		CGameBase::onSpinReceived(aWheels, oMagicItemAfterSpin, aWinPosition, aTableWin, iBonus, countFreeSpin);

		//We change bonus id
		//Because in this game, FreeSpin id is 3 and Bonus id is 2 (which is different from others)
		//So we change it to be content with the inheritance
		this->iBonusActive =
			this->iBonusActive == BONUS_TYPE::BONUS_TYPE_3 ?
			BONUS_TYPE::BONUS_FREESPIN :
			(this->iBonusActive == BONUS_TYPE::BONUS_FREESPIN ? BONUS_TYPE::BONUS_TYPE_3 : this->iBonusActive);
	}
	void CGameDB::startBonus()
	{
		CGameBase::startBonus();
		this->oBonusFreeSpin->show();
	}
	void CGameDB::onBonusFreeSpinStep0Received(int totalFreeSpins, int totalMulty)
	{
		this->oBonusFreeSpin->show(totalFreeSpins, totalMulty);
		this->iStepBonus++;
	}
	void CGameDB::onBonusFreeSpinStep1Received(bool iFinish, int totalFreeSpins, int totalMulty, const std::vector<ObjectBonus>& aWheels)
	{
		this->iStepBonus++;
		this->oBonusFreeSpin->showResult(iFinish, totalFreeSpins, totalMulty, aWheels, aWheels.size() - 1);
	}
}
