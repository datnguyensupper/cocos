#include "CGameLN.h"
#include "CBonusPalaceLN.h"
#include "CBonusBattleLN.h"
#include "../interfaceUI/CCharacterLN.h"
#include "../interfaceUI/CInterfaceLN.h"
#include "../interfaceUI/CWinPanelLN.h"

USING_NS_CC;
namespace GameSlot {
	CGameLN::CGameLN(CMainBase * _oMain):
		CGameBase(_oMain),
		iColDragon(0)
	{
	}
	CGameLN::~CGameLN()
	{

	}
	bool CGameLN::init()
	{
		if (!CGameBase::init()) return false;

		this->oBonusPalace = new CBonusPalaceLN(this);
		this->oBonusBattle = new CBonusBattleLN(this);

		return true;
	}
	void CGameLN::initBackground()
	{
		CGameBase::initBackground();
		auto resGame = GameConstant::getInstance()->getResources().mainGame;

		auto animation = AnimationHelper::getInstance()->createAnimationByFrameName(
			resGame["sea_animation_plist_0"],
			"BG_HD_%i",
			0,
			12,
			20,
			-1);

		auto sea = Sprite::createWithSpriteFrameName("BG_HD_0");
		sea->setScale(1.95f);
		sea->setAnchorPoint(Vec2(0.5, 1));
		sea->runAction(animation);

		GameUtils::centerNode(sea);

		this->addChild(sea, 1);
	}
	void CGameLN::initCharacter()
	{
		this->oCharacter = new CCharacterLN();
		this->oCharacter->create(this);
		CGameBase::initCharacter();
	}
	void CGameLN::initInterface()
	{
		this->oInterface = new CInterfaceLN(this);
		this->oInterface->init();
	}
	void CGameLN::initWinPanel()
	{
		this->oWinPanel = new CWinPanelLN(this);
		CGameBase::initWinPanel();
	}
	void CGameLN::initReels()
	{
		this->oReel = new CReel(this);
		CGameBase::initReels();
		this->oReel->setPosition(Vec2(-4, 21));

		auto oAmountText = this->oReel->getWinAnim()->getText();
		oAmountText->enableGlow(Color4B(255, 129, 0, 255));
		oAmountText->setPositionY(oAmountText->getPositionY() + 3);
	}

	int CGameLN::fixColToShowAnimation(const vector<ObjectCell>& aCellList, int col)
	{
		int column = col;
		if (this->iTotFreeSpin > 0 || this->bEndFreeSpin) {
			if (column == this->iColDragon) {
				column--;
			}
		}
		return column;
	}
	bool CGameLN::checkLastState()
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
				this->oBonusPalace->show();
				break;
			case BONUS_TYPE::BONUS_TYPE_4:
				if (this->iStepBonus == 0) {
					Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);
				}
				this->oBonusBattle->show();
				break;
			default:
				break;
			}
			return true;
		}
		return false;
	}

	void CGameLN::onBonusFreeSpinStepReceived(
		int iRemainingFreeSpin, 
		int iMultyFS, 
		const vector<ObjectWinPosition>& aWinPosition, 
		int ** aWheels, 
		const vector<ObjectTableWin>& aTableWin,
		double iTotWin)
	{
		auto index = iRemainingFreeSpin % 4;
		this->iColDragon = (index == 0 ? 1 : 4 - index);

		((CFreeSpinIndicatorLN*)this->oInterface->getFreeSpinIndicator())->showDragon(this->iColDragon);

		CGameBase::onBonusFreeSpinStepReceived(iRemainingFreeSpin, iMultyFS, aWinPosition, aWheels, aTableWin, iTotWin);
	}

	void CGameLN::startBonus()
	{
		CGameBase::startBonus();
		switch (this->iBonusActive)
		{
		case BONUS_TYPE::BONUS_TYPE_3:
			this->oBonusPalace->show();
			break;
		case BONUS_TYPE::BONUS_TYPE_4:
			this->oBonusBattle->show();
			break;
		default:
			break;
		}
	}
	void CGameLN::onBonusPalaceStep0Received()
	{
		this->oBonusPalace->show();
		this->iStepBonus++;
	}
	void CGameLN::onBonusPalaceStep1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels)
	{
		this->iStepBonus++;
		this->oBonusPalace->showResult(bFinish, aWheels, aWheels.size() - 1);
	}
	void CGameLN::onBonusBattleStep0Received()
	{
		this->oBonusBattle->show();
		this->iStepBonus++;
	}
	void CGameLN::onBonusBattleStep1Received(bool bFinish, const std::vector<ObjectBonus>& aWheels)
	{
		this->iStepBonus++;
		this->oBonusBattle->showResult(bFinish, aWheels, aWheels.size() - 1);
	}
}
