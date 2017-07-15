#include "CGamePO.h"
#include "CBonusStage1PO.h"
#include "CBonusStage2PO.h"
#include "../interfaceUI/CInterfacePO.h"
#include "../interfaceUI/CWinPanelPO.h"
#include "../interfaceUI/CReelPO.h"
#include "../interfaceUI/CEaglePO.h"

USING_NS_CC;
namespace GameSlot {
	CGamePO::CGamePO(CMainBase * _oMain):
		CGameBase(_oMain)
	{
	}
	CGamePO::~CGamePO()
	{

	}
	bool CGamePO::init()
	{
		if (!CGameBase::init()) return false;

		this->oBonusStage1 = new CBonusStage1PO(this);
		this->oBonusStage2 = new CBonusStage2PO(this);

		return true;
	}
	int * CGamePO::generateRandSymbols()
	{
		auto aRandSymbols = new int[3];
		auto s_aRandSymbols = CSlotSettings::getInstance()->getSymbolsOccurence();
		for (int i = 0; i < CSettings::NUM_ROWS; ++i) {
			if ((i - 1) % 3 == 0) {
				aRandSymbols[i] = 12;
			}
			else {
				int iRandIndex = RandomHelper::random_int(0, (int)s_aRandSymbols.size() - 1);
				aRandSymbols[i] = s_aRandSymbols[iRandIndex];
			}
		}
		return aRandSymbols;
	}
	void CGamePO::initBackground()
	{
		CGameBase::initBackground();

		auto oModel = Sprite::createWithSpriteFrameName("avatar");
		oModel->setAnchorPoint(Vec2::ZERO);
		oModel->setPosition(origin.x, 0);
		this->addChild(oModel, ORDER_CHARACTER);
	}
	void CGamePO::initInterface()
	{
		this->oInterface = new CInterfacePO(this);
		this->oInterface->init();
	}
	void CGamePO::initWinPanel()
	{
		this->oWinPanel = new CWinPanelPO(this);
		CGameBase::initWinPanel();
	}
	void CGamePO::initReels()
	{
		this->oReel = new CReelPO(this);
		CGameBase::initReels();

		this->poolSystemEagle = CPoolManager::getInstance()->createSystem("eagle_po", [this]() {
			auto oEagle = new CEaglePO();
			oEagle->init(this->oReel);
			return oEagle;
		}, 1);
	}

	int CGamePO::fixColToShowAnimation(const vector<ObjectCell>& aCellList, int col)
	{
		int column = col;
		auto row = (col < aCellList.size()) ? aCellList[col].row : -1;
		if (this->aCurWheel[row][aCellList[col].col] == CSettings::WILD_SYMBOL) {
			for (auto cell : aCellList) {
				if ((this->aCurWheel[cell.row][cell.col] != CSettings::WILD_SYMBOL)) {
					return cell.col;
				}
			}
		}
		return column;
	}
	bool CGamePO::checkLastState()
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
					this->oBonusStage1->show();
				}
				else if (this->iStepBonus < 4) {
					this->oBonusStage1->show();
				} 
				else if (this->iStepBonus == 4) {
					Manager4Network::getInstance()->callBonus(this->iStepBonus, 1);
					this->oBonusStage2->show(0);
				}
				else {
					this->oBonusStage2->show(bonusHistory->counter);
				}
				break;
			default:
				break;
			}
			return true;
		}
		return false;
	}

	void CGamePO::onBonusFreeSpinStepReceived(
		int iRemainingFreeSpin, 
		int iMultyFS, 
		const vector<ObjectWinPosition>& aWinPosition, 
		int ** aWheels, 
		const vector<ObjectTableWin>& aTableWin,
		double iTotWin)
	{
		bool bPlayFlyingEagle = false;
		if (this->aCurWheel && this->iStepBonus > 1) {
			for (auto i = 1; i < 3; i++) {
				for (auto j = 0; j < 3; j++) {
					//if this is Wild Symbol -> play flying eagle animation right there
					if (this->aCurWheel[j][i] == CSettings::WILD_SYMBOL) {
						bPlayFlyingEagle = true;
						auto oEagle = (CEaglePO*)this->poolSystemEagle->spawn();
						oEagle->fly(Vec2(
							CSettings::REEL_OFFSET_X + (CSettings::SYMBOL_WIDTH + CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS) * (i + 1),
							CSettings::REEL_OFFSET_Y - (CSettings::SYMBOL_HEIGHT + CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS) * j
							));
					}
				}
			}
		}
		if (bPlayFlyingEagle) {
			Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["eagle"]);
		}
		CGameBase::onBonusFreeSpinStepReceived(iRemainingFreeSpin, iMultyFS, aWinPosition, aWheels, aTableWin, iTotWin);
	}

	void CGamePO::launchBonus()
	{
		CGameBase::launchBonus();
		if (this->iBonusActive == BONUS_TYPE::BONUS_FREESPIN) {
			this->oWinPanel->showFreeSpinWinPanel(this->iTotFreeSpin, 0, nullptr);
		}
	}

	void CGamePO::startBonus()
	{
		CGameBase::startBonus();
		switch (this->iBonusActive)
		{
		case BONUS_TYPE::BONUS_TYPE_3:
			this->oBonusStage1->show();
			break;
		default:
			break;
		}
	}
	void CGamePO::onBonusStage1Step0Received()
	{
		this->oBonusStage1->show();
		this->iStepBonus++;
	}
	void CGamePO::onBonusStage1Step1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels)
	{
		this->iStepBonus++;
		this->oBonusStage1->showResult(bFinish, aWheels, aWheels.size() - 1);
	}
	void CGamePO::onBonusStage2Step0Received(int iMode)
	{
		this->oBonusStage2->show(iMode);
		this->iStepBonus++;
	}
	void CGamePO::onBonusStage2Step1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels)
	{
		this->iStepBonus++;
		this->oBonusStage2->showResult(bFinish, aWheels, aWheels.size() - 1);
	}
	void CGamePO::exitFromBonusStage1(const double& iWin, bool bWinBonusStage2)
	{
		if (bWinBonusStage2) {
			this->iBonusActive = BONUS_TYPE::BONUS_TYPE_4;
			Manager4Network::getInstance()->callBonus(this->iStepBonus, 1);
			this->oBonusStage2->show(0);
		}
		else {
			this->exitFromBonus(iWin);
		}
	}
	void CGamePO::onExit()
	{
		CPoolManager::getInstance()->releaseSystem("eagle_po");
		Node::onExit();
	}
}
