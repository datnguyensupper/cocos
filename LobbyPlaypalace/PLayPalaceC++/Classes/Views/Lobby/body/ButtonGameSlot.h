#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-15
* file: ButtonGameSlot.h, ButtonGameSlot.cpp
*/
#include "cocos2d.h"
#include "Views/IUpdateLanguage.h"
#include "ui/CocosGUI.h"
#include "Custom/Common/ButtonScaleChild.h"


class ButtonScaleChild;
class ServerSlotGameInfo;
class LobbyScene;
enum ButtonGameSlotState
{
	Unzipping,
	CanPlay,
	Locked,
	ComingSoon,
	Download, //show icon download
	Downloading //show status downloading
};
class ButtonGameSlot : public ButtonScaleChild, public IUpdateLanguage
{
private:
	cocos2d::Label *statusLabel;
	cocos2d::DrawNode *backgroundStatusLabel;
	cocos2d::Sprite *lockSprite;
	cocos2d::Sprite *downloadSprite;
	cocos2d::Node *downloadingProgressGroup;
	cocos2d::CCProgressTimer* downloadingProgress;
	int downloadingProgressMaskWidth = 60;

	LobbyScene* lobbyScene;

	ServerSlotGameInfo* gameInfo;
	ButtonGameSlotState currentState;

	/// <summary>
	/// 2017-02-15: Kiet: init function
	/// </summary>
	/// <param name="normalImage">normal image for button</param>
	/// <param name="selectedImage">selected image for button</param>
	/// <param name="disableImage">disable image for button</param>
	/// <param name="texType">texture type</param>
	/// <returns></returns>
	bool init(const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::PLIST) override;

	/// <summary>
	/// Update Download Progress By Dat
	/// </summary>
	/// <param name="progress">from 0->1</param>
	/// <param name="isFinish">is finish downloading</param>
	/// <param name="isFail">is download fail when finish</param>
	void updateDownloadProgress(float progress, bool isFinish, bool isFail);
public:
	/// <summary>
	/// Dat use to detect long press from outside
	/// </summary>
	float minimumPressDuration = 0.7f;
	bool isLongPress;
	/// <summary>
	/// create button game slots
	/// </summary>
	/// <param name="lobbyScene">lobby scene</param>
	/// <param name="gameInfo">game info</param>
	/// <param name="normalImage">normal image for button</param>
	/// <param name="selectedImage">selected image for button</param>
	/// <param name="disableImage">disable image for button</param>
	/// <param name="texType">texture type</param>
	/// <returns></returns>
	static ButtonGameSlot* create(
		LobbyScene* lobbyScene,
		const std::string& normalImage,
		ServerSlotGameInfo* gameInfo,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::PLIST);

	/// <summary>
	/// remove callback for downloading game slot avoid crash problem
	/// </summary>
	~ButtonGameSlot();

	/// <summary>
	/// By Dat
	/// start download game slot in User's UI
	/// </summary>
	void startDownloadGameSlotInGameBG();

	/// <summary>
	/// By Dat
	/// remove callback when downloading in slot game
	/// </summary>
	void removeCallback4Downloading();

	/**
	* Dat: check previous download game slot before goto game slot scene
	*/
	void checkPreviousDownload();

	/**
	* 2017-02-15: Kiet: check state for button base on game info and
	* local data ( ex: downloaded ) to change state and ui for this button
	*/
	void checkStateAndUpdateUI();

	/**
	* 2017-02-15: Kiet: get gameinfo of this button
	*/
	ServerSlotGameInfo* getGameInfo() {
		return this->gameInfo;
	}
	/**
	* 2017-02-15: Kiet: get current state
	*/
	ButtonGameSlotState getCurrentState() {
		return this->currentState;
	}

	/**
	* 2017-02-22: Kiet: update ui after change language
	*/
	void updateAfterChangeLanguage();
	/// <summary>
	/// By dat
	/// is game can cancel download
	/// </summary>
	/// <returns></returns>
	bool isGameCanCancelDownload();

	/// <summary>
	/// By dat
	/// cancel download game slot
	/// </summary>
	/// <returns></returns>
	void cancelDownloadGameSlot();

	/// <summary>
	/// By dat
	/// cancel download game slot
	/// </summary>
	/// <returns></returns>
	void removeGameSlot();

	/// <summary>
	/// By dat
	/// check file is expire by version
	/// </summary>
	/// <returns></returns>
	bool fileIsExpireByVersion();
};
