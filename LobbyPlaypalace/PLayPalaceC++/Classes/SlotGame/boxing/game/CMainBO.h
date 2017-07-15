#pragma once

#include "SlotGame/base/game/CMainBase.h"
#include "Constant/PPEnums.h"

namespace GameSlot {
	class CMainBO : public CMainBase
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
		/**
		* Function called to check if there is bonus in the last game
		* @param betXML
		*/
		void initLastBonusInfo(tinyxml2::XMLElement* bonusXML) override;
		/**
		* Function called when received Bonus Info after request
		* @param oXmlDoc: XML Document received
		*/
		void onBonusReceived(tinyxml2::XMLDocument* oXmlDoc) override;
		/**
		* Function called when received Double Up after request
		*/
		void onDoubleUpReceive(tinyxml2::XMLDocument* oXmlDoc) override;
	public:
		// implement the "static create()" method manually
		/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(CMainBO);
	protected:
		virtual int getGameOrderID() {
			return ppEnum::GameSlotOrderId::BOXING;
		}
	};
}
