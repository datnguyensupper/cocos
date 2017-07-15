#pragma once
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"
#include "SlotGame/GameSlotScene.h"

class ServerSlotGameInfo;
enum GameUnlockedPopupType {
	UNLOCK_GAME,
	UNLOCK_FEATURE
};
class GameUnlockedPopup : public BasePopup
{
private:
	std::deque<ServerSlotGameInfo*> listNewGameUnlocked;
	std::deque<std::string> listNewFeatureByLevel;

	cocos2d::Label* oText;
	cocos2d::Sprite* oLightRay;
	cocos2d::Sprite* oGameIcon;

	cocos2d::ui::Button* btn;

	/// <summary>
	/// prepare info for current unlocked game
	/// </summary>
	/// <param name="info"></param>
	void prepareInfo(ServerSlotGameInfo* info);
	/// <summary>
	/// prepare info of current feature
	/// </summary>
	/// <param name="info"></param>
	void prepareInfo(std::string &info);
	GameUnlockedPopupType currentType;
	std::string currentUFBL;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset popup UI
	/// </summary>
	void reset() override;
	/// <summary>
	/// update popup by chosend language
	/// </summary>
	void updateAfterChangeLanguage();
	/// <summary>
	/// prepare and show unlocked games
	/// </summary>
	/// <param name="listNewGameUnlocked"></param>
	/// <param name="parent"></param>
	void prepareAndShow(const std::deque<ServerSlotGameInfo*>& listNewGameUnlocked, cocos2d::Node* parent);
	/// <summary>
	/// preparent and show list unlocked features
	/// </summary>
	/// <param name="listNewFeatureByLevel"></param>
	/// <param name="parent"></param>
	void prepareAndShow(const std::deque<std::string>& listNewFeatureByLevel, cocos2d::Node* parent);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(GameUnlockedPopup);
};