#pragma once
#include "cocos2d.h"
#include "SlotGame/base/utils/CSpriteButton.h"

namespace LuckyWheel {
	class AnimationUIBase : public cocos2d::Node {
	public:
		virtual void startAnimation() {};
		virtual void stopAnimation() {};
	};

	class StarFlare : public AnimationUIBase {
	private:
		std::vector<cocos2d::Sprite*> aSprite;
	public:
		/// <summary>
		/// create star flare animation
		/// </summary>
		/// <param name="aPos"></param>
		/// <param name="aScale"></param>
		/// <returns></returns>
		static StarFlare* create(const std::vector<cocos2d::Vec2>& aPos, const std::vector<float>& aScale);

		virtual bool init(const std::vector<cocos2d::Vec2>& aPos, const std::vector<float>& aScale);
		/// <summary>
		/// base animation
		/// </summary>
		virtual void startAnimation();
		virtual void stopAnimation();
	};

	class ShinyBackground : public AnimationUIBase {
	private:
		cocos2d::Sprite* shiny_1;
		cocos2d::Sprite* shiny_2;
		cocos2d::Sprite* shiny_3;
	public:
		/// <summary>
		/// init UI
		/// </summary>
		/// <returns>is init success</returns>
		virtual bool init();
		/// <summary>
		/// animation for shine background
		/// </summary>
		virtual void startAnimation();
		virtual void stopAnimation();

		/// <summary>
		/// define create function
		/// </summary>
		/// <param name="">name of class</param>
		/// <returns>return class object</returns>
		CREATE_FUNC(ShinyBackground);
	};

	class CircleBound : public AnimationUIBase {
	private:
		cocos2d::Sprite* bg;

		cocos2d::Sprite* line_1;
		cocos2d::Sprite* line_2;
	public:
		/// <summary>
		/// init UI
		/// </summary>
		/// <returns>is init success</returns>
		virtual bool init();
		/// <summary>
		/// animation for circle bound
		/// </summary>
		virtual void startAnimation();
		virtual void stopAnimation();

		/// <summary>
		/// define create function
		/// </summary>
		/// <param name="">name of class</param>
		/// <returns>return class object</returns>
		CREATE_FUNC(CircleBound);
	};

	class SlotHover : public AnimationUIBase {
	private:
		cocos2d::Sprite* bg;
		bool isBlue;
	public:
		/// <summary>
		/// init UI
		/// </summary>
		/// <returns>is init success</returns>
		virtual bool init();

		/// <summary>
		/// animation for hover slots
		/// </summary>
		virtual void startAnimation();
		virtual void startAnimation(bool isBlue) { this->isBlue = isBlue; this->startAnimation(); }
		virtual void stopAnimation();

		/// <summary>
		/// define create function
		/// </summary>
		/// <param name="">name of class</param>
		/// <returns>return class object</returns>
		CREATE_FUNC(SlotHover);
	};

	class ButtonSpin : public AnimationUIBase {
	private:
		GameSlot::CSpriteButton* btn;

		cocos2d::Sprite* flashAnim;
		cocos2d::Sprite* innerAnim;
		cocos2d::Sprite* outerAnim;
		StarFlare* starFlare;
	public:
		/// <summary>
		/// init UI
		/// </summary>
		/// <returns>is init success</returns>
		virtual bool init();
		/// <summary>
		/// start animation when click to spin button
		/// </summary>
		void startFlashAnimation();
		void startInnerAnimation();
		void startOuterAnimation();
		/// <summary>
		/// get spin button
		/// </summary>
		/// <returns></returns>
		GameSlot::CSpriteButton* getButton() { return this->btn; }
		/// <summary>
		/// stop animation spin button
		/// </summary>
		void stopAnimation();
		/// <summary>
		/// handle click on spin button
		/// </summary>
		/// <param name="onTouched"></param>
		void setOnTouched(std::function<void()> onTouched) { this->btn->setOnTouchUp(onTouched); }

		/// <summary>
		/// define create function
		/// </summary>
		/// <param name="">name of class</param>
		/// <returns>return class object</returns>
		CREATE_FUNC(ButtonSpin);
	};

	class CircleFlashLight : public AnimationUIBase {
	private:
		cocos2d::Sprite* bg;
	public:
		/// <summary>
		/// init UI
		/// </summary>
		/// <returns>is init success</returns>
		virtual bool init();

		/// <summary>
		/// ajust rotation for spin animation
		/// </summary>
		virtual void startAnimation();
		/// <summary>
		/// start circle spin animation
		/// </summary>
		virtual void startSpinAnimation();
		virtual void stopAnimation();

		/// <summary>
		/// define create function
		/// </summary>
		/// <param name="">name of class</param>
		/// <returns>return class object</returns>
		CREATE_FUNC(CircleFlashLight);
	};

	class SlotCoinEffect : public AnimationUIBase {
	private:
		std::vector<cocos2d::Sprite*> aCoin;

		float startPosY;
	public:
		/// <summary>
		/// init UI
		/// </summary>
		/// <returns>is init success</returns>
		virtual bool init();
		/// <summary>
		/// start slot coin effect animation
		/// </summary>
		virtual void startAnimation();
		virtual void stopAnimation();

		/// <summary>
		/// define create function
		/// </summary>
		/// <param name="">name of class</param>
		/// <returns>return class object</returns>
		CREATE_FUNC(SlotCoinEffect);
	};

	class WheelSting : public AnimationUIBase {
	private:
		cocos2d::Sprite* bg;
		cocos2d::Sprite* flashAnim;
		StarFlare* starFlare;
	public:
		/// <summary>
		/// init UI
		/// </summary>
		/// <returns>is init success</returns>
		virtual bool init();
		/// <summary>
		/// stat wheel sting animation
		/// </summary>
		virtual void startAnimation();
		/// <summary>
		/// stop wheelsting animation
		/// </summary>
		virtual void stopAnimation();

		/// <summary>
		/// define create function
		/// </summary>
		/// <param name="">name of class</param>
		/// <returns>return class object</returns>
		CREATE_FUNC(WheelSting);
	};
}