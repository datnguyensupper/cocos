#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: InitSession.h, InitSession.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
class ButtonDownloadGameSlot : public cocos2d::ui::Button {
private:
	void firstSetUp();
public:

	std::string _gameId;
	std::string _gameVersion;

	//bool init() override;

	ButtonDownloadGameSlot();

	static ButtonDownloadGameSlot* create();
	/// <summary>
	/// create button for game slot
	/// </summary>
	/// <param name="gameId"></param>
	/// <param name="gameVersion"></param>
	/// <param name="normalImage"></param>
	/// <param name="selectedImage"></param>
	/// <param name="disableImage"></param>
	/// <param name="texType">texture type : file or plist</param>
	/// <returns></returns>
	static ButtonDownloadGameSlot* create(
		const std::string &gameId,
		const std::string &gameVersion,
		const std::string &normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		TextureResType texType = TextureResType::LOCAL);
};
