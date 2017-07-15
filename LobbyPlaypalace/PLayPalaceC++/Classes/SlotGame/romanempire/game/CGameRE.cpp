#include "CGameRE.h"
#include "CBonusRE.h"
#include "CDoubleUpRE.h"
#include "../interfaceUI/CWinPanelRE.h"
#include "../interfaceUI/CReelRE.h"

USING_NS_CC;
namespace GameSlot {
	CGameRE::CGameRE(CMainBase * _oMain):
		CGameBase(_oMain),
		oBonus(nullptr)
	{
	}
	CGameRE::~CGameRE()
	{

	}
	bool CGameRE::init()
	{
		if (!CGameBase::init()) return false;

		this->oDoubleUp = new CDoubleUpRE(this);
		this->oBonus = new CBonusRE(this);

		return true;
	}
	bool CGameRE::onSpin(tinyxml2::XMLDocument* doc)
	{
		if (CGameBase::onSpin()) {
			this->hideExpand();
		}
		return false;
	}
	void CGameRE::initBackground()
	{
		CGameBase::initBackground();

		auto oModel = Sprite::createWithSpriteFrameName("avatar");
		oModel->setPosition(origin / 2);
		oModel->setAnchorPoint(Vec2::ZERO);
		this->addChild(oModel, ORDER_CHARACTER);
	}
	void CGameRE::initInterface()
	{
		this->oInterface = new CInterfaceBase(this, true);
		this->oInterface->init();
	}
	void CGameRE::initWinPanel()
	{
		this->oWinPanel = new CWinPanelRE(this);
		CGameBase::initWinPanel();
	}
	void CGameRE::initReels()
	{
		this->oReel = new CReelRE(this);
		CGameBase::initReels();

		this->aExpand.resize(3);

		auto createExpand = [this](int iIndex) {
			auto sprite = Sprite::createWithSpriteFrameName("symbol-expand");
			sprite->setPosition(
				CSettings::REEL_OFFSET_X + (CSettings::SYMBOL_WIDTH + CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS) * iIndex + CSettings::SYMBOL_WIDTH / 2,
				CSettings::REEL_OFFSET_Y - CSettings::HEIGHT_REEL / 2 + 3.5f
				);
			sprite->setVisible(false);
			this->oReel->addChild(sprite, ORDER_REEL_FRAMEWIN + 1);
			return sprite;
		};
		this->aExpand[0] = createExpand(1);
		this->aExpand[1] = createExpand(2);
		this->aExpand[2] = createExpand(3);
	}
	void CGameRE::showExpand(int iCol)
	{
		if (this->aExpand[iCol - 1]->isVisible()) {
			return;
		}
		auto expand = this->aExpand[iCol - 1];
		expand->setOpacity(0);
		expand->setVisible(true);
		expand->runAction(FadeIn::create(0.15f));
	}
	void CGameRE::hideExpand()
	{
		for (auto expand : this->aExpand) {
			if (expand->isVisible()) {
				expand->runAction(Sequence::createWithTwoActions(FadeOut::create(0.15f), 
					CallFunc::create([this, expand]{
					expand->setVisible(false);
				})));
			}
		}
	}
	bool CGameRE::checkExpandColumn(int iCol)
	{
		return this->aCurWheel[0][iCol] == CSettings::WILD_SYMBOL &&
			this->aCurWheel[1][iCol] == CSettings::WILD_SYMBOL &&
			this->aCurWheel[2][iCol] == CSettings::WILD_SYMBOL;
	}
	int CGameRE::fixColToShowAnimation(const vector<ObjectCell>& aCellList, int col)
	{
		int column = col;
		while (this->checkExpandColumn(column)) {
			column--;
		}
		if (column < 0) column = 0;
		return column;
	}
	bool CGameRE::checkLastState()
	{
		if (CGameBase::checkLastState()) {
			auto bonusHistory = this->oMain->getBonusHistory();
			switch (this->iBonusActive)
			{
			case BONUS_TYPE::BONUS_TYPE_3:
				if (this->iStepBonus == 0) {
					Manager4Network::getInstance()->callBonus(this->iStepBonus, 0);
				}
				this->oBonus->show();
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
	int CGameRE::onStopOneReelColumn(int totalReelStop)
	{
		if (CGameBase::onStopOneReelColumn(totalReelStop) == CSettings::WILD_SYMBOL) {
			if (this->checkExpandColumn(totalReelStop - 1)) {
				this->showExpand(totalReelStop - 1);
			}
		}
		return 0;
	}
	void CGameRE::startBonus()
	{
		CGameBase::startBonus();
		this->oBonus->show();
	}
	void CGameRE::onBonusStep0Received()
	{
		this->oBonus->show();
		this->iStepBonus++;
	}
	void CGameRE::onBonusStep1Received(bool iFinish, int iTotMul, double iTotWin)
	{
		this->iStepBonus++;
		this->oBonus->showResult(iFinish, iTotMul, iTotWin);
	}
}
