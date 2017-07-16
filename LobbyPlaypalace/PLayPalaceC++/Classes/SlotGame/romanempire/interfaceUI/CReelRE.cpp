#include "CReelRE.h"
#include "SlotGame/base/game/CGameBase.h"

USING_NS_CC;
namespace GameSlot {
	CReelRE::CReelRE(CGameBase* oGame):CReel(oGame)
	{
	}
	void CReelRE::initCols(int * aStartingWheel)
	{
		auto iXPos = CSettings::REEL_OFFSET_X;
		auto iYPos = CSettings::REEL_OFFSET_Y;

		int iCont = 0;
		int* aSymbols = new int[3];

		for (int i = 0; i < CSettings::NUM_REELS; i++) {
			aSymbols[0] = aStartingWheel[iCont];
			aSymbols[1] = aStartingWheel[iCont + 1];
			aSymbols[2] = aStartingWheel[iCont + 2];

			auto column = new CReelColumnRE(this);
			column->init(
				i,
				Vec2(iXPos, iYPos),
				aSymbols,
				this->oAttachSymbols,
				this->oAttachWinFrame);

			this->aMovingColumns.pushBack(column);

			iXPos += CSettings::SYMBOL_WIDTH + CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS;
			iCont += 3;

		}
		CC_SAFE_DELETE_ARRAY(aSymbols);
	}

	CReelColumnRE::CReelColumnRE(CReel * oReel): CReelColumn(oReel)
	{
	}

	void CReelColumnRE::setSymbol(int * aSymbols, int startIndex)
	{
		if (this->bReadyToStop && aSymbols &&
			aSymbols[0] == CSettings::WILD_SYMBOL &&
			aSymbols[1] == CSettings::WILD_SYMBOL &&
			aSymbols[2] == CSettings::WILD_SYMBOL) {
			auto type = RandomHelper::random_int(1, 3);
			auto maxSymbol = CSettings::SCATTER_SYMBOL - 1;
			switch (type)
			{
			case 1:
				aSymbols[0] = RandomHelper::random_int(0, maxSymbol);
				aSymbols[1] = RandomHelper::random_int(0, maxSymbol);
				break;
			case 2:
				aSymbols[0] = RandomHelper::random_int(0, maxSymbol);
				aSymbols[2] = RandomHelper::random_int(0, maxSymbol);
				break;
			case 3:
				aSymbols[1] = RandomHelper::random_int(0, maxSymbol);
				aSymbols[2] = RandomHelper::random_int(0, maxSymbol);
				break;
			default:
				break;
			}
		}
		CReelColumn::setSymbol(aSymbols, startIndex);
	}
}
