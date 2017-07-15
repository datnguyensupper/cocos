#pragma once

#include "cocos2d.h"

#include "../constant/GameConstant.h"
#include "network/HttpClient.h"
#include "tinyxml2/tinyxml2.h"

namespace GameSlot {
	class CMainBase;
	typedef const std::function<void(bool, tinyxml2::XMLDocument*)>& APIGameCallback;
	class Manager4Network
	{
	private:
		cocos2d::network::HttpRequest* curRequest = nullptr;
		CMainBase* _oMain;
		tinyxml2::XMLDocument* curDoc;
		long long _lTs;
		/*
		* Function callback after request
		* @param sender
		* @param response
		*/

		void onHttpRequestCompleted(
			cocos2d::network::HttpClient *sender,
			cocos2d::network::HttpResponse *response);
		/*
		* Function callback after after parse DOCXML
		* @param cb
		*/
		void onReceivedXML(const APIGameCallback& cb);
		/*
		* Function handle error for xmlDoc
		* @param doc: document need to check
		* @return: bool (true - error | false: normal)
		*/
		bool handleError(tinyxml2::XMLDocument* doc, const APIGameCallback& cb);

		/*
		* Function called after detecting access token was invalid
		*/
		void alertInvalidAccessToken();
	public:
		/** Returns the shared instance of the Manager4Network.
		* @return The instance of the Manager4Network.
		*/
		static Manager4Network* getInstance();
		~Manager4Network();
#pragma region Core Methods
		/*
		* HTTP Get Method
		* @param url: url to call
		* @param params: parameters as string
		* @param cb: callback
		*/
		void get(const std::string& url,
			const std::string& params,
			APIGameCallback cb);
		/*
		* HTTP Post Method
		* @param url: url to call
		* @param params: parameters as string
		* @param cb: callback
		*/
		void post(const std::string& url,
			const std::string& params,
			APIGameCallback cb);
#pragma endregion

		/*
		* Set current game - need to be called when init CMain
		*/
		void setGame(CMainBase* _oMain);

#pragma region Game API Functions
		/*
		* Authorize account for fun user - deprecated
		*/
		void callFunPlay();
		/*
		* Authorize account for current user
		*/
		void callRealPlay();
		/**
		* Request User's balance
		* @param szKey: play key
		*/
		void callGetBalance(const std::string& szKey);
		/**
		* Request get bets info
		* @param szKey: play key
		*/
		void callGetBet(const std::string& szKey);
		/**
		* Request get Spin info
		* @param cb(optional): callback after get spin info
		*/
		void callGetSpin(const std::function<void()>& cb = nullptr);
		/**
		* Request get Bonus info
		* @param iStep: bonus's step
		* @param iParam: bonus's param
		*/
		void callBonus(int iStep, int iParam);
#pragma endregion
		void release();
	};
}
