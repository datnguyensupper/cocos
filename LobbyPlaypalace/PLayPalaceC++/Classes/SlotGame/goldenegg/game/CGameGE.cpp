#include "CGameGE.h"
#include "CBonusFreeSpinGE.h"
#include "CDoubleUpGE.h"
#include "../interfaceUI/CInterfaceGE.h"
#include "../interfaceUI/CWinPanelGE.h"
#include "../interfaceUI/CCharacterGE.h"

USING_NS_CC;
namespace GameSlot {
	CGameGE::CGameGE(CMainBase * _oMain):
		CGameDB(_oMain)
	{
	}
	CGameGE::~CGameGE()
	{

	}
	bool CGameGE::init()
	{
		if (!CGameBase::init()) return false;

		this->oDoubleUp = new CDoubleUpGE(this);
		this->oBonusFreeSpin = new CBonusFreeSpinGE(this);

		return true;
	}
	void CGameGE::initBackground()
	{
		CGameBase::initBackground();
	}
	void CGameGE::initCharacter()
	{
		this->oCharacter = new CCharacterGE();
		this->oCharacter->create(this);
		CGameBase::initCharacter();
	}
	void CGameGE::initInterface()
	{
		this->oInterface = new CInterfaceGE(this);
		this->oInterface->init();
	}
	void CGameGE::initWinPanel()
	{
		this->oWinPanel = new CWinPanelGE(this);
		CGameBase::initWinPanel();
	}
	void CGameGE::initReels()
	{
		this->oReel = new CReel(this);
		CGameBase::initReels();
		this->oReel->getWinAnim()->setTextColor(Color4B(255, 254, 197, 255), Color4B(135, 72, 41, 255));
	}
}
