#include "CSettings.h"

USING_NS_CC;
namespace GameSlot {
	int CSettings::CANVAS_WIDTH = 1600;
	int CSettings::CANVAS_HEIGHT = 900;

	float CSettings::SCALE_VALUE_TO_1920 = CSettings::CANVAS_WIDTH / 1920.0f;

	int CSettings::REEL_OFFSET_X = 0;
	int CSettings::REEL_OFFSET_Y = 0;

	int CSettings::NUM_REELS = 5;
	int CSettings::NUM_ROWS = 3;
	int CSettings::NUM_SYMBOLS = 0;

	int CSettings::SCATTER_SYMBOL = 0;
	int CSettings::WILD_SYMBOL = 0;
	int CSettings::BONUS_3_SYMBOL = 0;
	int CSettings::BONUS_4_SYMBOL = 0;

	int CSettings::NUM_PAYLINES = 0;
	int CSettings::SYMBOL_WIDTH = 180;
	int CSettings::SYMBOL_HEIGHT = 172;

	int CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS = 0;
	int CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS = 0;

	float CSettings::MAX_FRAMES_REEL_EASE = 0.2f;
	int CSettings::MIN_REEL_LOOPS = 2;
	int CSettings::REEL_DELAY = 0;

	int CSettings::NUM_INFO_PAGES = 5;

	int CSettings::ANIM_SYMBOL_FPS = 15;

	bool CSettings::IS_SHOW_ANIMATION_FRAMEWIN = true;

	float CSettings::SCALE_SYMBOL_MAX = 1.5f;
	float CSettings::SCALE_SYMBOL_MIN = 1.0f;
	float CSettings::SCALE_SYMBOL = 1.0f;
	float CSettings::SCALE_SYMBOL_ANIM = 1.0f;

	float CSettings::SCALE_FRAME_WIN = 1.0f;

	Vec2 CSettings::AMOUNT_WIN_POSITION = Vec2::ZERO;
	Vec2 CSettings::FRAME_WIN_POSITION = Vec2::ZERO;

	float CSettings::TIMER_ANIM_ZOOM_UP = 1.0f;
	float CSettings::TIMER_ANIM_ZOOM_DOWN = 0.5f;

	float CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL = 0;
	float CSettings::TIMER_WAITING_TEXT_WIN_PANEL = 0;
	float CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST = 0;
	float CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST = 0;

	float CSettings::TIMER_DELAY_BETWEEN_TWO_COL = 0.1f;

	float CSettings::TIMER_DELAY_UPDATE_REEL = 0.0f;

	float CSettings::TIMER_DELAY_SHOW_WIN_BONUS = 2.0f;

	int CSettings::WIDTH_REEL = 0;
	int CSettings::HEIGHT_REEL = 0;

	int CSettings::REEL_START_Y = 0;
	int CSettings::REEL_ARRIVAL_Y = 0;

	float CSettings::TIME_SHOW_ALL_WINS = 1.0f;
	float CSettings::TIME_SPIN_BUT_CHANGE = 1.0f;
	float CSettings::TIME_HOLD_AUTOSPIN = 1.0f;
}
