#pragma once
#include "cocos2d.h"
class CSpinWheel;
class HeaderLobbyLayout;
class LuckyWheelInfo;
namespace LuckyWheel {
	class ShinyBackground;
	class CircleBound;
	class SlotHover;
	class ButtonSpin;
	class CircleFlashLight;
	class SlotCoinEffect;
	class WheelSting;
	class LuckyWheelShopPopup;
	class LuckyWheelLayout : public cocos2d::Node
	{
	private:
		std::vector<std::string> aRes;
		LuckyWheelInfo* info;

		cocos2d::Node* oLoadingGroup;
		cocos2d::ProgressTimer* oLoadingProgessTimer;
		cocos2d::Label* oLoadingLabel;

		HeaderLobbyLayout* oHeader;
		LuckyWheelShopPopup* oPopupShop;

		cocos2d::Node* oLuckyWheelGroup;
		ShinyBackground* shinyBackgroud;
		CircleBound* circleBound;
		SlotHover* slotHover;
		ButtonSpin* btnSpin;
		CircleFlashLight* cirlceFlashLight;
		SlotCoinEffect* slotCoinEffect;
		WheelSting* wheelSting;

		CSpinWheel* spinWheel;

		cocos2d::Label* txtRemainingSpin;

		double winValue;
		/**
		* init loading ui
		*/
		void initLoading();
		/**
		* start loading resources
		*/
		void loadingRes();
		/**
		* callback when 1 file has loaded
		*/
		void onFileLoaded(float progress);
		/**
		* callback when all files has loaded
		*/
		void finishLoadingRes();

		/**
		* init lucky wheel resources
		*/
		void initLuckyWheel();

		/**
		* play idle animation
		*/
		void playIdleAnimation();
		/**
		* play spin animation
		*/
		void playSpinAnimation();
		/**
		* play win animation
		*/
		void playWinAnimation();
		/// <summary>
		/// stop winning animation
		/// </summary>
		void stopWinAnimation();
		/**
		* init function
		*/
		void openLuckyWheelShopPopup();
		/// <summary>
		/// reload remaining spins
		/// </summary>
		void reloadRemaining();
	public:
		/**
		* init function
		*/
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

		/**
		* init function
		*/
		void onSpin();

		/**
		* onEnter
		*/
		virtual void onEnter();
		/**
		* callback when exit lucky wheel
		*/
		virtual void onExit();

		/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LuckyWheelLayout);
	};
}