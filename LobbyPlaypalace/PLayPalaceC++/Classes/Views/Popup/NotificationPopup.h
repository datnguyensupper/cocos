#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-18
* file: NotificationPopup.h, NotificationPopup.cpp
*/
#include "BasePopup.h"
#include "Manager/LanguageManager.h"
#include "Constant/LanguageConstant.h"

class NotificationPopup : public BasePopup
{
private:
	cocos2d::Label* titleLabel;
	cocos2d::Label* bodyLabel;
	cocos2d::Label* infoLabel; //info addition at bottom
	cocos2d::Sprite* infoIconSprite;

	cocos2d::ui::Button* okButton;
	cocos2d::ui::Button* cancelButton;

	std::function <void(void)> callbackOK; //when click button ok
	std::function <void(void)> callbackCancel; //when click close popup or cancel button

	/// <summary>
	/// 2017-02-18: Kiet: process after click OK Button
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void okButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);

	/// <summary>
	/// 2017-02-18: Kiet: process after click Close Popup or Cancel Button
	/// </summary>
	/// <param name="sender">button info</param>
	/// <param name="type">type of touched</param>
	void closePopupButtonTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
	/**
	* show missing popup
	* //DEPRECATED: USING MissingPopup Instead
	*/
	void showPopupMissing(
		cocos2d::Node* parent,
		const int64_t& iValue,
		bool isCrown = false
	);
public:
	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

	/// <summary>
	/// 2017-02-18: Kiet: prepare and show popup
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="title"></param>
	/// <param name="body"></param>
	/// <param name="okText"></param>
	/// <param name="cancelText"></param>
	/// <param name="info"></param>
	/// <param name="callbackOK"></param>
	/// <param name="callbackCancel"></param>
	void prepareAndShow(
		cocos2d::Node* parent,
		const std::string &title,
		const std::string &body,
		const std::string &okText = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
		const std::string &cancelText = LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::CANCEL),
		const std::string &info = "",
		const std::function <void(void)> callbackOK = nullptr,
		const std::function <void(void)> callbackCancel = nullptr
	);

	/// <summary>
	/// show unfinish popup
	/// </summary>
	/// <param name="parent">parent of popup</param>
	void showUnfinishJobPopup(
		cocos2d::Node* parent
                              );
    
    /// <summary>
    /// show unfinish popup
    /// </summary>
    /// <param name="parent">parent of popup</param>
    void showDisconnect2PurchaseStore(cocos2d::Node* parent);

	/// <summary>
	/// show not support popup
	/// </summary>
	/// <param name="parent">parent of popup</param>
	void showDontSupportPopup(
		cocos2d::Node* parent
	);

	/**
	* show missing coin or crown popup
	* //DEPRECATED: USING MissingPopup Instead
	*/
	void showPopupMissingCoin(
		cocos2d::Node* parent,
		const int64_t& iCoinMissing
	);
	/**
	* show missing coin or crown popup
	* //DEPRECATED: USING MissingPopup Instead
	*/
	void showPopupMissingCrown(
		cocos2d::Node* parent,
		const int64_t& iCrownMissing
	);


	/// <summary>
	/// show missing coin or crown popup
	/// </summary>
	/// <param name="parent">parent popup</param>
	/// <param name="funcReload">reload function after reveive coins</param>
	/// <param name="forceToCloseOpeningPopup">close parent popup</param>
	/// <param name="callbackOK"></param>
	/// <param name="callbackCancel"></param>
	void showServerErrorPopup(
		cocos2d::Node* parent,
		const std::function<void()> funcReload = nullptr,
		bool forceToCloseOpeningPopup = true,
		const std::function <void(void)> callbackOK = nullptr,
		const std::function <void(void)> callbackCancel = nullptr
	);

	/// <summary>
	/// return OK button position
	/// </summary>
	/// <returns></returns>
	cocos2d::Vec2 getOkButtonPosition() {
		return okButton->getPosition();
	}

	/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(NotificationPopup);
};
