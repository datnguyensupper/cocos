#pragma once
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"
#include "SlotGame/GameSlotScene.h"
#include "SlotGame/base/utils/CSpriteButton.h"
#include "Plugins/ImagePicker/ImagePicker.h"

class UserInfo;

class ProfilePopup;
class ImagePickerResult : public cocos2d::ImagePickerDelegate {
private:
	ProfilePopup* profile;

	std::string fileName;
public:
	ImagePickerResult(ProfilePopup* profile);
	void didFinishPickingWithResult(cocos2d::Image* image, int orientation) override;
};

class ProfilePopup : public BasePopup
{
private:
	ImagePickerResult* imagePickerResult;

	cocos2d::Node* oParent;

	cocos2d::Sprite* oVipSymbol;
	cocos2d::Sprite* oFacebookSymbol;

	cocos2d::Sprite* oAvatar;

	cocos2d::Label* oName;
	cocos2d::ui::RichText* oLevel;
	cocos2d::Label* oExp;
	cocos2d::Label* oWin;

	GameSlot::CSpriteButton* oNameBtn;
	GameSlot::CSpriteButton* oAvatarBtn;

	float firstPosX;
	float endPosX;
	/// <summary>
	/// touch button change name
	/// </summary>
	void onChangeNameTouched();
	/// <summary>
	/// touch button avatar
	/// </summary>
	void onChangeAvatarTouched();
	/// <summary>
	/// update user info ui
	/// </summary>
	/// <param name="isSuccess">is success get user info from server</param>
	/// <param name="userInfo">user info from server</param>
	void reloadInfo(bool isSuccess, UserInfo* userInfo);
	/**
	* create list animation for show popup
	* override this to JUST custom ONLY animation for show popup ( don't need call visible true after run animation )
	*/
	virtual std::vector<cocos2d::Action*> animationShowPopup() override;
	/**
	* create list animation for hide popup
	* override this to JUST custom ONLY animation for hide popup ( don't need call visible false after run animation )
	*/
	virtual std::vector<cocos2d::Action*> animationHidePopup() override;
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	
	/// <summary>
	/// prepare and show
	/// </summary>
	/// <param name="parent">parent of popup</param>
	void prepareAndShow(cocos2d::Node* parent);
	/**
	* update avatar
	* @param texture
	*/
	void updateAvatar(cocos2d::Texture2D* texture);
	/**
	* update avatar
	* @param texture
	*/
	void updateName(const std::string& newName);

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(ProfilePopup);
};