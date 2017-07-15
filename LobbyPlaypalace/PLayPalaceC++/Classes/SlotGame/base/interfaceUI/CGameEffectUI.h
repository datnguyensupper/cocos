#pragma once

#include "cocos2d.h"

namespace GameSlot {
	class CMainBase;
	class ObjectMagicItemReceiveAfterSpin;
	class CWinEffectUI : public cocos2d::Node {
	private:
		cocos2d::Node* oBigWin;
		cocos2d::Node* oMegaWin;

		cocos2d::Label* oWinText;

		cocos2d::Sprite* oStars;

		cocos2d::Sprite* oTitleBigWin;

		cocos2d::Sprite* oTitleMega;
		cocos2d::Sprite* oTitleWin;

		std::vector<cocos2d::Sprite*> aBigWinStars;

		std::vector<cocos2d::Sprite*> aMegaWinUpStars;
		std::vector<cocos2d::Sprite*> aMegaWinDownStars;
		/**
		* show shooting stars for popup megawin and bigwin
		* @param aStars: array image key
		* @param delayToShootStar: delay to start show shooting star
		* @param delayBetweenStar : array delay between stars
		* @param iScaleValue
		*/
		void playShootingStar(
			const std::vector<cocos2d::Sprite*>& aStars,
			float delayToShootStar, 
			const std::vector<float>& delayBetweenStar,
			bool bPlayExplodeStar = true
			);
		/**
		* play animaton big win
		*/
		void playBigWin(bool isMegaWin, std::string titleBigWinPath = "win_effect_bigwin");
		/**
		* play animaton mega win
		*/
		void playMegaWin();
		/**
		* reset after play animation
		*/
		void reset();
	public:
		CWinEffectUI();

		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/**
		* show win effect (mega - big)
		* @param iWin: total win
		* @param isMegaWin: true if this's mega win
		*/
		void showWinEffect(const double& iWin, bool isMegaWin, std::string titleBigWinPath = "win_effect_bigwin");
		/**
		* Kiet: 2017-04-25: check and show win effect
		*/
		void checkAndShowWinEffect(
			const double& iWin,
			const double& totalBet,
			ObjectMagicItemReceiveAfterSpin *oMagicItemAfterSpin);
	};

	class CSpinEffect : public cocos2d::Node {
	protected:
		CMainBase* oMain;
		cocos2d::Sprite* oStar;
		cocos2d::ParticleSystemQuad* oParticle;

		cocos2d::ccBezierConfig config;

		bool bUpdateExpLocal;
	public:
		CSpinEffect(CMainBase* oMain);
		virtual ~CSpinEffect();

		bool init() override;
		/**
		* Playing Flying Star from Button Spin To EXP BAR
		* @param startPos: Button Spin's pos
		* @param startPos: EXP BAR's pos
		*/
		void playFlyingStarAnimation(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos);

		void setUpdateExpLocal(bool bUpdateExpLocal) { this->bUpdateExpLocal = bUpdateExpLocal; }
	};

	class CMainBase;
	class CGameEffectUI : public cocos2d::Node {
	private:
		CWinEffectUI* oWinEffect;
		CSpinEffect* oSpinEffect;
	public:
		CGameEffectUI(CMainBase* oMain);
		~CGameEffectUI();
		CWinEffectUI* getWinEffect() { return oWinEffect; }
		CSpinEffect* getSpinEffect() { return oSpinEffect; }
	};
}