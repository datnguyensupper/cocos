#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-22
* file: SettingPopup.h, SettingPopup.cpp
*/
#include "BasePopup.h"
#include "Views/IUpdateLanguage.h"

class ToggleButton;
class SettingPopup : public BasePopup, public IUpdateLanguage
{
private:
	cocos2d::Label* loggedViaLabel;
	cocos2d::Label* nameLabel;
	cocos2d::Label* accountUIDLabel;
	cocos2d::ui::ScrollView* accountUIDScrollView;

	ToggleButton* toggleBGMusicItem;
	ToggleButton* toggleSoundEffectsItem;
	
	cocos2d::ui::Button* languageButton;
	cocos2d::Label* currentLanguageLabel;
	cocos2d::Node* languageComboBox;

	cocos2d::Label* myCodeLabel;
	cocos2d::Label* myRefCodeLabel;

	cocos2d::ui::Button* copyButton;
	cocos2d::ui::Button* addButton;

#pragma region USING FOR CHANGE LANGUAGE
	cocos2d::ui::Button* logoutButton;
	cocos2d::ui::Button* termsOfServiceButton;
	cocos2d::ui::Button* privacyPolicyButton;

	cocos2d::Label* gameOptionTitleLabel;
	cocos2d::Label* bgMusicTitleLabel;
	cocos2d::Label* soundEffectsTitleLabel;
	cocos2d::Label* languageTitleLabel;
	cocos2d::Label* myReferenceCodeTitleLabel;
	cocos2d::Label* myCodeTitleLabel;
	cocos2d::Label* myRefCodeTitleLabel;
	cocos2d::Label* versionLabel;
	cocos2d::CCMenu* menuVersionLabel;
#pragma endregion

	int numberLabelVersionTextTouched = 0;

	/// <summary>
	/// 2017-02-22: Kiet: on change language touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onChangeLanguageTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-22: Kiet: on logout touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onLogoutTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-22: Kiet: on copy my code touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onCopyMyCodeTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-22: Kiet: on add reference code touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onAddRefCodeTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-22: Kiet: on toggle bg music touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onToggleBGMusicTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-22: Kiet: on toggle sound effect touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onToggleSoundEffectTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-22: Kiet: on terms of service touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onTermsOfServiceTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-22: Kiet: on privacy policy touched
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void onPrivacyPolicyTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* 2017-02-22: Kiet: perpare data
	*/
	void prepareData();
    
    
    /**
     By Dat : enable btn copy in
     @param enable is enable
     */
    void enableBtnCopy(bool enable);
    
    /**
     By Dat : enable btn add
     @param enable is enable
     */
    void enableBtnAdd(bool enable);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/**
	* 2017-02-22: Kiet: update ui after change language
	*/
	void updateAfterChangeLanguage() override;

	/// <summary>
	/// 2017-02-22: Kiet: prepare and show
	/// </summary>
	/// <param name="parent">parent of popup</param>
	void prepareAndShow(cocos2d::Node* parent);

	/// <summary>
	/// By Dat:
	/// update referee code from additional info
	/// </summary>
	void updateRefereeCode();

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(SettingPopup);
};
