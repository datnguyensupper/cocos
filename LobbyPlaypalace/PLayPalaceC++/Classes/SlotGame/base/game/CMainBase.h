#pragma once

#include "SlotGame/GameSlotScene.h"
#include "CLoadingUI.h"
#include "Util/CLoader.h"
#include "Util/UtilFunction.h"
#include "../settings/CSettings.h"
#include "../settings/CSlotSettings.h"
#include "../manager/Manager4Network.h"
#include "../manager/Manager4Sound.h"
#include "../utils/GameUtils.h"
#include "Helper/AnimationHelper.h"
#include "../constant/GameConstant.h"
#include "Configs.h"
#include "../object/InfoObject.h"

namespace GameSlot {
	class CGameBase;
	class CMainBase : public cocos2d::Node
	{
		enum AttributeName {
			none,
			multiply,
			multiplier,
			wheel,
			lottoball,
			tid,
			val,
			type,
			bet,
			lines,
			totalbet,
			wild,
			scatter,
			ts,
			width,
			height,
			win,
			numberOfLuckySymbolWin,
			luckySymbolPosition,
			remainingSpin,
			remainingTime
		};
	protected:
		std::map<std::string, AttributeName> mapStringValues;
		void initMapStringValue();

		bool bRealPlay = true;
		string szFunPlayKey;
		string szRealPlayKey;
		int iMultiply = 0;
		unsigned iBet = 0;
		std::vector<int> aBets;
		int iLines = 0;
		double iTotBet = 0;
		std::vector<string> aStartingWheel;
		CGameBase* oGame = nullptr;
		ObjectBonusRestore* oBonusToRestore = nullptr;
		int iCurBonus = 0;
		string szBonusKey;
		double iCurWin = 0;
		double iCredit = 0;

		bool bAllResourcesLoaded = false;
		bool bFinishAPI = false;
		bool bReadyToSpin = false;
		bool bReceivedBonusData = false;
		bool bUpdatedUserInfo = false;
		bool bGotoGame = false;

		std::string gameName;

		CLoadingUI* oLoadingUI = nullptr;
		GameSlotScene* oScene = nullptr;

		vector<std::string> aResources;
		vector<std::string> aResourcesExtend;
		

		/*
		* Function init settings
		*/
		virtual void initSettings();
		/*
		* Function init resources
		*/
		virtual void initResources();
		/*
		* Function called after all resources've been loaded
		*/
		virtual void allResourcesLoaded();
		/**
		* CREATE CGAME OBJECT
		*/
		virtual void gotoGame();
		/**
		* update function
		*/
		void update(float dt);
		/**
		* Function called to check if there is bonus in the last game
		* @param oXmlDoc
		*/
		void onCheckLastBonus(tinyxml2::XMLDocument* oXmlDoc);
		/**
		* Function called to set last bonus's info
		* @param betXML
		*/
		virtual void initLastBonusInfo(tinyxml2::XMLElement* bonusXML);
		/**
		* Function called when received Double Up after request
		*/
		virtual void onDoubleUpReceive(tinyxml2::XMLDocument* oXmlDoc);
		/**
		* Function called when received Free Spin with Retrigger after request
		* @param oXmlDoc: XML Document received
		*/
		virtual void onBonusFreeSpinWithRetriggerReceived(tinyxml2::XMLDocument* oXmlDoc);
	public:

		std::string getSlotGameLocationPrefix();

		virtual int getGameOrderID();
		virtual void onExit();
#pragma region Setter
		/**
		* Set current Bonus Index
		* @param currentBonus: bonus index
		*/
		void setCurrentBonus(int currentBonus) { this->iCurBonus = currentBonus; }
		void setReceivedBonus(bool isReceived) { this->bReceivedBonusData = isReceived; }
		void setUpdateUserInfo(bool isUpdated) { this->bUpdatedUserInfo = isUpdated; }
		void setStartingWheel(vector<std::string>& aStartingWheel) { this->aStartingWheel = aStartingWheel; }
		void removeBonusHistory() { CC_SAFE_DELETE(this->oBonusToRestore); }

		void setBet(unsigned iBet) { this->iBet = iBet; }
		void setTotalBet(double iTotBet) { this->iTotBet = iTotBet; }
		void setLine(int iLine) { this->iLines = iLine; }

		void setScene(GameSlotScene* oScene) { this->oScene = oScene; }
#pragma endregion
#pragma region Getter
		std::string getGameName() const { return this->gameName; }
		unsigned getBet() const { return this->iBet; }
		int getLine() const { return this->iLines; }
		int getMul() const { return this->iMultiply; }
		double getWin() const { return this->iCurWin; }
		double getTotalBet() const { return this->iTotBet; }
		bool isReceivedBonus() const { return this->bReceivedBonusData; }
		bool isUpdateUserInfo() const { return this->bUpdatedUserInfo; }
		bool isReadyToSpin() const { return this->bReadyToSpin; }
		string getRealPlayKey() const { return this->szRealPlayKey; }
		string getBonusKey() const { return this->szBonusKey; }
		ObjectBonusRestore* getBonusHistory() const { return this->oBonusToRestore; }
		vector<std::string> getStartingWheel() const { return this->aStartingWheel; }
		CLoadingUI* getLoadingUI() { return this->oLoadingUI; }
		GameSlotScene* getScene() { return this->oScene; }
		CGameBase* getGame() { return this->oGame; }
#pragma endregion

#pragma region API - Core Functions
		/**
		* Function called when receiving user's key for slot game after request
		* @param szKey: play key
		*/
		void onGetRealPlayKeyReceived(const string& szKey);
		/**
		* Function called when received user's balance after request
		* @param szCredit: user's credit (balance)
		*/
		void onBalanceReceived(float szCredit);
		/**
		* Function called when received Bets Info after request
		* @param oXmlDoc: XML Document received
		*/
		void onBetsReceived(tinyxml2::XMLDocument* oXmlDoc);
		/**
		* Function called when received Spin Info after request
		* @param oXmlDoc: XML Document received
		*/
		void onSpinReceived(tinyxml2::XMLDocument* oXmlDoc);
		/**
		* Function called when received Bonus Info after request
		* @param oXmlDoc: XML Document received
		*/
		virtual void onBonusReceived(tinyxml2::XMLDocument* oXmlDoc);
#pragma endregion

		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	};
}
