#pragma once

#include "SlotGame/base/interfaceUI/CReel.h"

namespace GameSlot {
	class CGameBase;
	class CReelRE : public CReel {
	private:
	public:
		CReelRE(CGameBase* oGame);
		/**
		* init columns
		*/
		virtual void initCols(int* aStartingWheel);
	};
	class CReelColumnRE : public CReelColumn {
	private:
	public:
		CReelColumnRE(CReel* oReel);
		/**
		* Set array symbol for column
		* @param aSymbols: array of 3 symbols
		* @param startIndex
		*/
		void setSymbol(int* aSymbols = nullptr, int startIndex = 0) override;
	};
}