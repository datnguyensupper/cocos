#pragma once

#include "cocos2d.h"

namespace GameSlot {
	class CSpriteButton : public cocos2d::Sprite{
	protected:
		cocos2d::EventListenerTouchOneByOne* listener;
		std::function<void()> onLongTouch;
		std::function<void()> onDown;
		std::function<void()> onUp;
		cocos2d::Rect touchRect;

		float longTouchTime;
		float longTouchDuration;

		float scaleDown;
		float scaleUp;

		std::string frameNormal;
		std::string frameTouching;
		std::string frameDisable;

		bool isTouchBegin = false;
		bool isTouching = false;

		bool isBlock;
		/**
		* add touch events
		*/
		void addEvents();

		bool isButtonVisible();

		/**
		* on Down Event
		*/
		virtual void onDownEvent();
		/**
		* on Down Event
		*/
		virtual void onUpEvent();

		bool checkCanRunListener(cocos2d::Touch* touch);
		void longTouchUpdate(float dt);
		void normalState();
		void pressedState();
	public:
		CSpriteButton();
		virtual ~CSpriteButton();


		/**
		* static function create a sprite button
		* @param fileName: texture file's name
		* @param onDown: on touch down callback (optional)
		* @param onUp: on touch up callback (optional)
		*/
		static CSpriteButton* createButtonWithFile(
			const std::string& fileName,
			const std::function<void()>& onDown,
			const std::function<void()>& onUp);
		/**
		* static function create a sprite button
		* @param spriteName: sprite frame's name
		* @param onDown: on touch down callback (optional)
		* @param onUp: on touch up callback (optional)
		*/
		static CSpriteButton* createButtonWithSpriteFrameName(
			const std::string& spriteName,
			const std::function<void()>& onDown,
			const std::function<void()>& onUp);
		/**
		* static function create a invisible button
		* @param rect: rectangle received touch input
		* @param onDown: on touch down callback (optional)
		* @param onUp: on touch up callback (optional)
		*/
		static CSpriteButton* createInvisibleButton(
			const cocos2d::Rect& rect,
			const std::function<void()>& onDown,
			const std::function<void()>& onUp);
		/**
		* set on touch down callback
		* @param onDown:  on touch down callback
		*/
		void setOnTouchDown(const std::function<void()>& onDown);
		/**
		* set on touch up callback
		* @param onUp:  on touch up callback
		*/
		void setOnTouchUp(const std::function<void()>& onUp);
		/**
		* set on touch up callback
		* @param duration:  long touch duration (second)
		* @param onLongTouch:  on long touch callback
		*/
		void setLongTouch(float duration, const std::function<void()>& onLongTouch);
		/**
		* set touch enabled
		* @param isEnabled
		*/
		void setTouchEnabled(bool isEnabled);
		/**
		* Set scale button when touched
		* @param isEnabled
		*/
		void setScaleEvent(float scaleDown, float scaleUp = 1.0f) { this->scaleDown = scaleDown; this->scaleUp = scaleUp; }
		/**
		* Set change button image on different state
		* @param isEnabled
		*/
		void setImageEvent(const std::string& frameTouching,
			const std::string& frameDisable = "") { this->frameTouching = frameTouching; this->frameDisable = frameDisable; }
		/**
		* Set custom zone received touch event - this is relative rect (default: rect(0,0,width,height))
		* @param isEnabled
		*/
		void setCustomTouchZone(const cocos2d::Rect& touchRect) { this->touchRect = touchRect; }
		/**
		* Set this button is only for blocking touches from user
		* @param isEnabled
		*/
		void setIsBlock(bool isBlock) { this->isBlock = isBlock; }
		/**
		* Just Change Sprite Frame To Normal - Not Change Button State
		*/
		void changeSpriteFrameToNormal();
		/**
		* Just Change Sprite Frame To Touching - Not Change Button State
		*/
		void changeSpriteFrameToTouching();
		/**
		* Just Change Sprite Frame To Disable - Not Change Button State
		*/
		void changeSpriteFrameToDisable();
	};
}