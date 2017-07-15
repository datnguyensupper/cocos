#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"

namespace GameSlot {
	class CGameBase;
	class CWinPanelBase : public cocos2d::Node{
	protected:
		CGameBase* oGame;

		cocos2d::Sprite* oBG;
		cocos2d::Label* oTitle;
		cocos2d::Label* oMessage;
		/**
		* Show Panel
		*/
		virtual void show();
		/**
		* Hide Panel
		*/
		virtual void hide();
	public:
		CWinPanelBase(CGameBase* oGame);
		virtual ~CWinPanelBase();
		/**
		* init Panel
		*/
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
		/**
		* Show Win Panel Function
		* @param title: Title Text
		* @param iTotWin: Total Win
		* @param cb: callback after show
		*/
		virtual void showWinPanel(const std::string& title, double iTotWin, const std::function<void()> cb);
		/**
		* Show Free Spin Win Panel
		* @param iTotFreeSpin: total FreeSpin won
		* @param iTotMulty: total Multiplier won
		* @param cb: callback after show
		*/
		virtual void showFreeSpinWinPanel(int iTotFreeSpin, int iTotMulty, const std::function<void()> cb);
		/**
		* Show Free Spin Win Panel
		* @param iTotFreeSpin: total FreeSpin won
		* @param iTotMulty: total Multiplier won
		* @param cb: callback after show
		* @param isAdditionWin: is this is Addition FreeSpin
		*/
		virtual void showFreeSpinAdditionWinPanel(int iTotFreeSpinconst, std::function<void()> cb);
	};
}
