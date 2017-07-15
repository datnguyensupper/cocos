#pragma once

#include "SlotGame/deepblue/game/CMainDB.h"

namespace GameSlot {
	class CMainGE : public CMainDB
	{
	private:
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/*
		* Function init settings
		*/
		virtual void initSettings();
		/*
		* Function init resources
		*/
		virtual void initResources();
		/**
		* CREATE CGAME OBJECT
		*/
		void gotoGame() override;
	public:
		// implement the "static create()" method manually
		/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(CMainGE);
	protected:
		virtual int getGameOrderID() {
			return ppEnum::GameSlotOrderId::GOLDEN_EGGS;
		}
	};
}
