#include "CGameBO.h"
#include "CDoubleUpBO.h"
#include "../interfaceUI/CInterfaceBO.h"
#include "../interfaceUI/CWinPanelBO.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CGameBO::CGameBO(CMainBase * _oMain):
		CGameBase(_oMain)
	{
	}
	CGameBO::~CGameBO()
	{

	}
	bool CGameBO::init()
	{
		if (!CGameBase::init()) return false;

		this->oDoubleUp = new CDoubleUpBO(this);

		return true;
	}
	void CGameBO::initInterface()
	{
		this->oInterface = new CInterfaceBO(this);
		this->oInterface->init();
	}
	void CGameBO::initWinPanel()
	{
		this->oWinPanel = new CWinPanelBO(this);
		CGameBase::initWinPanel();
	}
	void CGameBO::initReels()
	{
		this->oReel = new CReel(this);
		CGameBase::initReels();
		this->oReel->getWinAnim()->setTextColor(Color4B::WHITE);

		auto oModel = Helper4Sprite::createOptimizeSprite(GameConstant::getInstance()->getResources().mainGame["model"]);
		oModel->setAnchorPoint(Vec2(0.5f, 0));
		oModel->setPosition(CSettings::CANVAS_WIDTH / 2, 0);
		this->oReel->addChild(oModel, ORDER_REEL_FRAMEWIN + 1);
	}
	bool CGameBO::checkLastState()
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
	void CGameBO::launchBonus()
	{
		CGameBase::launchBonus();
		//Cause Boxing only has Free Spin and Double Up never call to this function
		//so we'll show free spin win panel without checking bonus ID
		this->oWinPanel->showFreeSpinWinPanel(15, 0, nullptr);
	}

	void CGameBO::onDoubleUpStep1Received(bool bFinish, const std::vector<ObjectBonus>& aInfo, const ObjectCardDoubleUpBO & cardDealer)
	{
		((CDoubleUpBO*)this->oDoubleUp)->showCardToPick(bFinish, aInfo, cardDealer);

		this->iStepBonus++;
	}
	void CGameBO::onDoubleUpStep2Received(bool bFinish, const std::vector<ObjectCardDoubleUpBO>& aCard, double iBank, int iSelect, double iTotWin)
	{
		this->iStepBonus = 1;

		((CDoubleUpBO*)this->oDoubleUp)->showResult(bFinish, aCard, iBank, iSelect, iTotWin);
	}
}
