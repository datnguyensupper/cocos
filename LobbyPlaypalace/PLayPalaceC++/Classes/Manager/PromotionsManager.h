#pragma once

#include "cocos2d.h"

class PromotionsManager
{
private:
	bool isCheckStartup = false;

	bool isLobbyBegin = false;

	bool bF2PShowedInGame = false;
	bool bF2PShowedInLobby = false;

	int getMoreCoinTotalShowed = 0;

	PromotionsManager();
public:
	/**
	* get instance class
	*/
	static PromotionsManager* getInstance();

	void checkStartupPromotions(const std::function<void(bool isHavePromotion)> cb = nullptr);
	void checkRepeatedPromotions(const std::function<void(bool isHavePromotion)> cb = nullptr);

	void checkSpecialOffer(const std::function<void(bool isHavePromotion)> cb);
	bool checkStarterPack();
	bool checkPayToPlay();
	bool checkFreeToPlay();
	bool checkGetMoreCoins();

	void reset();
};