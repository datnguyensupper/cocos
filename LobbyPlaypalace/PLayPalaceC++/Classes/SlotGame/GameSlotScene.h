#pragma once

#include "cocos2d.h"
#include "Scene/BaseScene.h"

class HeaderLobbyLayout;
struct LevelUpInfo;
namespace GameSlot {
	enum GameEventListenerType {
		BeginGame,
		BeginSpin,
		BeginBonus,
		FinishSpin,
		FinishBonus,
		FinishGame,
	};
	class CMainBase;
	class GameSlotScene : public BaseScene{
	private:
		HeaderLobbyLayout* oHeader;
		CMainBase* oMainGame;

		bool isLevelUp = false;

		void onReloadData(const std::function<void()>& cb, bool isSuccess, LevelUpInfo* levelUpInfo);

		std::vector<std::function<void(GameSlotScene*, GameEventListenerType)>> _aEventListener;
	public:
		CMainBase* getMain() { return this->oMainGame; };
		HeaderLobbyLayout* getHeader() { return this->oHeader; };
		/*
		* static function called to show game slot
		* @param gameOrderID: order id of game
		*/
		static GameSlotScene* showGame(long gameOrderID);
		/*
		* create game scene
		* @param oMainGame: CMain of game
		*/
		void initSceneWithGame(CMainBase* oMainGame);
		/*
		* set header's visibility
		* @param isVisible
		*/
		void setHeaderVisible(bool isVisible);
		/*
		* check user can spin - call to check when user click spin button
		*/
		bool checkCanSpin();
		/*
		* cb after collected LevelUp
		*/
		void onLevelUpCollected(double coinReward, double crownReward);
		/*
		* function called when begin game
		*/
		void onBeginGame();
		/*
		* function called when finish game
		*/
		void onFinishGame();
		/*
		* function called when begin spin
		*/
		void onBeginSpin();
		/*
		* function called after the reel stop
		*/
		void onFinishSpin(const std::function<void()>& cb);

		/*
		* function called when begin bonus game - doubleup
		*/
		void onBeginBonus();
		/*
		* function called after exit from bonus - doubleup
		*/
		void onFinishBonus(const std::function<void()>& cb);

		/**
		* Add Game Event Listener
		*/
		void addGameEventListener(const std::function<void(GameSlotScene*, GameEventListenerType)>& func);

		bool isInGame();

		virtual void menuCloseCallback(cocos2d::Ref* pSender);
		virtual void onExit();
	};
}
