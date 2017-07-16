#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-18
* file: BasePopup.h, BasePopup.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"

enum PopupStateType {
	Popup_State_Open,
	Popup_State_Close,
};

class ButtonScaleChild;
class BasePopup : public cocos2d::Layer
{
protected:
	cocos2d::CCLayerColor *darkLayer = nullptr; 
	std::vector<std::function<void(BasePopup*, PopupStateType)>> _aEventListener;
	cocos2d::CCLayerColor *layerDisableClickOnHide = nullptr;
	bool _isShowing = false;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float scaleDownRatio;
    float scaleDownLookGoodRatio;

	/**
	* 2017-02-18: Kiet: create close button
	*/
	virtual cocos2d::ui::Button* createCloseButton();
	/**
	* create label of button
	*/
	virtual cocos2d::ui::Button* createLabelButton(ButtonScaleChild* btn, bool isMutilpleLanguage, std::string titleText = "", float fontSize = 60);
	/**
	* create button base on sprite name
	*/
	virtual cocos2d::ui::Button* createButton(const std::string& fileName, bool isMutilpleLanguage, std::string titleText = "", float fontSize = 60);
	/**
	* create button base on frame name
	*/
	virtual cocos2d::ui::Button* createButtonWithFrameName(const std::string& frameName, bool isMutilpleLanguage, std::string titleText = "", float fontSize = 60);
	/**
	* create blue button
	*/
	virtual cocos2d::ui::Button* createBlueButton(bool isMutilpleLanguage, std::string titleText = "", float fontSize = 60);
	/**
	* 2017-02-18: Kiet: create green button
	*/
	virtual cocos2d::ui::Button* createGreenButton(bool isMutilpleLanguage, std::string titleText = "", float fontSize = 60);
	/**
	* 2017-02-18: Kiet: create purple button
	*/
	virtual cocos2d::ui::Button* createPurpleButton(bool isMutilpleLanguage, std::string titleText = "", float fontSize = 60);
	/**
	* 2017-02-22: Kiet: create list animation for show popup
	* override this to JUST custom ONLY animation for show popup ( don't need call visible true after run animation )
	*/
	virtual std::vector<cocos2d::Action*> animationShowPopup();
	/**
	* 2017-02-22: Kiet: create list animation for hide popup
	* override this to JUST custom ONLY animation for hide popup ( don't need call visible false after run animation )
	*/
	virtual std::vector<cocos2d::Action*> animationHidePopup();
	/**
	* 2017-03-14: Kiet: sound open popup effect
	* override this to JUST custom sound open popup effect
	*/
	virtual void playSoundOpenPopup();
	/**
	* 2017-03-14: Kiet: sound close popup effect
	* override this to JUST custom sound close popup effect
	*/
	virtual void playSoundClosePopup();

	/// <summary>
	/// Dat: get min ratio popup for scale from animation
	/// </summary>
	/// <returns></returns>
	virtual float getMinRatioPopup();

	/// <summary>
	/// Dat: get real ratio popup show on multiple device
	/// </summary>
	/// <returns></returns>
	virtual float getMaxRatioPopup();

	/// <summary>
	/// rotate ray animation for unlock popup, lucky box popup
	/// </summary>
	/// <returns></returns>
	cocos2d::Action* createActionRotateLightRay();

	cocos2d::Sprite * createLightRayBG(cocos2d::Vec2 position);

	/// <summary>
	/// call back if click to dark layer of popup
	/// </summary>
	virtual void callback4Click2DarkLayer();

public:
	BasePopup();

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/**
	* 2017-02-27: Kiet: reset popup by set visible to false and ishowing to false
	*/
	virtual void reset();
	/**
	* 2017-02-18: Kiet: show popup directly with current info and UI (old popup were init before)
	* @param isCleanUp isCleanUp in parent remove child
	*/
	virtual void show(cocos2d::Node* parent, bool isCleanUp = true);
	/**
	* show popup directly with current info and UI (old popup were init before) without change parent
	*/
	virtual void show();

	/// <summary>
	/// 2017-02-18: Kiet: add to queue before check and show
	/// </summary>
	/// <param name="parent"></param>
	/// <param name="forceShowAfterReleaseScene">is show popup after change scene</param>
	virtual void showWithQueue(cocos2d::Node* parent, bool forceShowAfterReleaseScene = false);
	/**
	* 2017-02-18: Kiet: hide popup with animation
	*/
	virtual void hide();
	/**
	* 2017-02-27: Kiet: get is showing
	*/
	bool isShowing() {
		return this->_isShowing;
	}
	/**
	* Add Game Event Listener
	*/
	void addPopupEventListener(const std::function<void(BasePopup*, PopupStateType)>& func);
	/**
	* dat: update ui after change language
	*/
	virtual void updateAfterChangeLanguage();
};
