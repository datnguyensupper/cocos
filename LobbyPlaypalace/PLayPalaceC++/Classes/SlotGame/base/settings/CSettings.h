#pragma once

#include "cocos2d.h"
namespace GameSlot {
	class CSettings {
	public:
		static float SCALE_VALUE_TO_1920;

		static int CANVAS_WIDTH;
		static int CANVAS_HEIGHT;

#pragma region Values need to set by game
		static int REEL_OFFSET_X;
		static int REEL_OFFSET_Y;

		static int NUM_REELS;
		static int NUM_ROWS;
		static int NUM_SYMBOLS;

		static int SCATTER_SYMBOL;
		static int WILD_SYMBOL;
		static int BONUS_3_SYMBOL;
		static int BONUS_4_SYMBOL;

		static int NUM_PAYLINES;
		static int SYMBOL_WIDTH;
		static int SYMBOL_HEIGHT;

		static int SPACE_WIDTH_BETWEEN_SYMBOLS;
		static int SPACE_HEIGHT_BETWEEN_SYMBOLS;

		static float MAX_FRAMES_REEL_EASE;
		static int MIN_REEL_LOOPS;
		static int REEL_DELAY;

		static int NUM_INFO_PAGES;

		static int ANIM_SYMBOL_FPS;

		static bool IS_SHOW_ANIMATION_FRAMEWIN;

		static float SCALE_SYMBOL_MAX;
		static float SCALE_SYMBOL_MIN;
		static float SCALE_SYMBOL;
		static float SCALE_SYMBOL_ANIM;

		static float SCALE_FRAME_WIN;

		static cocos2d::Vec2 AMOUNT_WIN_POSITION;
		static cocos2d::Vec2 FRAME_WIN_POSITION;

		static float TIMER_ANIM_ZOOM_UP;
		static float TIMER_ANIM_ZOOM_DOWN;

		static float TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL;
		static float TIMER_WAITING_TEXT_WIN_PANEL;
		static float TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST;
		static float TIMER_WAITING_TEXT_WIN_PANEL_FAST;

		static float TIMER_DELAY_BETWEEN_TWO_COL;

		static float TIMER_DELAY_UPDATE_REEL;

		static float TIMER_DELAY_SHOW_WIN_BONUS;
#pragma endregion
		static int WIDTH_REEL;
		static int HEIGHT_REEL;

		static int REEL_START_Y;
		static int REEL_ARRIVAL_Y;

		static float TIME_SHOW_ALL_WINS;
		static float TIME_SPIN_BUT_CHANGE;
		static float TIME_HOLD_AUTOSPIN;
	};
}