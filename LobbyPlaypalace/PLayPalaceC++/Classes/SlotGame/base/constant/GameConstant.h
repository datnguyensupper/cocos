#pragma once

#include "cocos2d.h"

namespace GameSlot {
#define ORDER_LOADING 100
#define ORDER_HEADER 50
#define ORDER_GAME 0
#define ORDER_BONUS 1
#define ORDER_WIN_PANEL 2
#define ORDER_BG 0

#define ORDER_REEL 1
#define ORDER_REEL_BG 0
#define ORDER_REEL_SYMBOLS 1
#define ORDER_REEL_LINES 2
#define ORDER_REEL_FRAMEWIN 3
#define ORDER_REEL_WINANIM 50

#define ORDER_CHARACTER 2

#define ORDER_INTERFACE 3

#define ToString(num) cocos2d::StringUtils::toString(num)

#define stoi(str) atoi(str.c_str())
#define stof(str) atof(str.c_str())
#define stol(str) atol(str.c_str())

	struct _gameService {
		std::string authorization;
		std::string getBalance;
		std::string getBet;
		std::string spin;
		std::string bonusGame;
	};
	struct _DomainName {
		_gameService gameService;
	};
	struct _Account {
		bool isFunMode = false;
	};
	struct _ResourcesGame {
		std::map<std::string, std::string> loader;
		std::map<std::string, std::string> mainGame;
		std::map<std::string, std::string> symbolAnims;
		std::map<std::string, std::string> lines;
		std::map<std::string, std::string> doubleUp;
		std::map<std::string, std::string> bonus1;
		std::map<std::string, std::string> bonus2;

		std::map<std::string, std::string> sound;

		std::map<std::string, cocos2d::TTFConfig> fontConfigs;
	};
	class GameConstant
	{
	private:
		_DomainName DomainName;
		_Account Account;
		_ResourcesGame Resources;
	public:
		static GameConstant* getInstance();

		_DomainName getDomainName() const { return this->DomainName; }
		_Account getAccount() const { return this->Account; }
		_ResourcesGame getResources() const { return this->Resources; }

		void initResources(_ResourcesGame& resourcesGame) { this->Resources = resourcesGame; }

		void setGame(const std::string& game);
		void release();
	};


	enum GAME_TYPE
	{
		MAIN_GAME,
		DOUBLE_UP,
		FREE_SPIN,
		BONUS
	};

	enum BONUS_TYPE {
		BONUS_DOUBLE_UP = 1,
		BONUS_FREESPIN = 2,
		BONUS_TYPE_3 = 3,
		BONUS_TYPE_4 = 4
	};

	enum GAME_STATE {
		GAME_IDLE,
		GAME_SPINING,
		GAME_SHOW_WIN,
		GAME_SHOW_ALL_WIN,
		GAME_BONUS
	};

	enum REEL_STATE {
		REEL_START,
		REEL_MOVING,
		REEL_STOP
	};

	enum SPIN_STATE {
		SPIN_TYPE_SPIN,
		SPIN_TYPE_STOP,
		SPIN_TYPE_AUTO_SPIN,
		SPIN_TYPE_SKIP,
		SPIN_TYPE_FREE_SPIN,
		SPIN_TYPE_BONUS
	};


	enum ERROR_CODE {
		WRONG_STEP = 14,
		WRONG_PARAM = 5,
		SPIN_TOO_FAST = 26,
		SERVER_MAINTENANCE = 20,
		LOGGED_SOMEWHERE_ELSE = 18,
		NOT_ENOUGH_MONEY = 10,
		COMMON_ERROR = 0,
	};
}