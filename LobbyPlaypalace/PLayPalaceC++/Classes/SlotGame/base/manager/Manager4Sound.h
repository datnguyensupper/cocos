#pragma once

#include "cocos2d.h"
#include "../constant/GameConstant.h"

namespace GameSlot {
	class CMainBase;
	class Manager4Sound
	{
	private:
		CMainBase* oMain;
		std::map<std::string, std::string> resSound;

		int backGroundID;
		int animationID;
		int totalWinID;
		int reelSpinID;

		bool bSoundEnabled;
	public:
		/** Returns the shared instance of the Manager4Sound.
		* @return The instance of the Manager4Sound.
		*/
		static Manager4Sound* getInstance();
		Manager4Sound();
		~Manager4Sound();

		/*
		* Set current res - need to be called when init CMain
		*/
		void setGame(CMainBase* oMain, const std::map<std::string, std::string>& res);
		/*
		* Reset
		*/
		void reset();
		/*
		* Set state
		*/
		void setState(bool bEnabled);
		/**
		* Play current background Sound
		*/
		int playBackgroundMusic();
		/**
		* Set volumn for BG Sound
		* @param volume: number of volume
		*/
		void setVolumeBackgroundMusic(float volume);
		/**
		* Play Spin Sound
		*/
		int playSpin();
		/**
		* Play Reel Spin Sound
		*/
		int playReelSpin();
		/**
		* Stop Reel Spin Sound
		*/
		void stopReelSpin();
		/**
		* Play Reel Stop Sound
		*/
		int playReelStop();
		/**
		* Play Reel Stop Sound
		*/
		int playScatterStop();

		/**
		* Play Wild Stop Sound
		*/
		int playWildStop();

		/**
		* Play Bonus Stop Sound
		*/
		int playBonusStop(int bonusID);
		/**
		* Play symbol Animation Sound
		* @param iSymbol: symbol value
		*/
		int playSymbolAnimation(int iSymbol);
		/**
		* Stop Total Win Sound
		*/
		void stopSymolAnimation();
		/**
		* Play Total Win Sound
		*/
		int playTotalWin();
		/**
		* Stop Total Win Sound
		*/
		void stopTotalWin();
		/**
		* Play Button Clicked in Double Up
		*/
		int playBtnDoubleUpClicked();
		/**
		* Play Button Clicked in Bonus 3
		*/
		int playBtnBonusType3Clicked();
		/**
		* Play Button Clicked in Bonus 4
		*/
		int playBtnBonusType4Clicked();

		/**
		* Play Double Up Win
		*/
		int playDoubleUpWin();
		/**
		* Play Double Up Lose
		*/
		int playDoubleUpLose();

		/**
		* Play Win Effect
		*/
		int playWinEffectSound();

		int playEffect(const std::string& file, bool isLoop = false);
		void stopEffect(int id);

		void turnOffAllSound();

		void release();
	};
}