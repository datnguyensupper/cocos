#include "CMainGE.h"
#include "CGameGE.h"

USING_NS_CC;
namespace GameSlot {
	// on "init" you need to initialize your instance
	bool CMainGE::init()
	{
		this->gameName = "GoldenEggs";
		//////////////////////////////
		// 1. super init first
		if (!CMainBase::init())
		{
			return false;
		}

		return true;
	}

	void CMainGE::initSettings()
	{
		CSettings::REEL_OFFSET_X = 376 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::REEL_OFFSET_Y = 865 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_SYMBOLS = 13;
		CSettings::SCATTER_SYMBOL = 11;
		CSettings::WILD_SYMBOL = 12;
		CSettings::NUM_PAYLINES = 25;
		CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS = 21 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS = 2 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_INFO_PAGES = 5;
		CSettings::IS_SHOW_ANIMATION_FRAMEWIN = true;
		CSettings::SCALE_SYMBOL = 1.0f;
		CSettings::SCALE_SYMBOL_ANIM = 1.0f;
		CSettings::SCALE_SYMBOL_MIN = 1.0f;
		CSettings::SCALE_SYMBOL_MAX = 1.6f;
		CSettings::TIMER_ANIM_ZOOM_DOWN = 0.5f;
		CSettings::AMOUNT_WIN_POSITION = Vec2(0, -100) * CSettings::SCALE_VALUE_TO_1920;
		CSettings::FRAME_WIN_POSITION = Vec2::ZERO;
		CSettings::SCALE_FRAME_WIN = 1.0f;

		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL = 5.0f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL = 3.0f;
		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST = 1.0f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST = 7.0f;

		CSettings::TIMER_DELAY_UPDATE_REEL = 0.0f;

		CSettings::TIMER_DELAY_SHOW_WIN_BONUS = 2.0f;

		CSettings::ANIM_SYMBOL_FPS = 15;

		CMainBase::initSettings();

		CSlotSettings::getInstance()->initSlotSettings(new int[CSettings::NUM_SYMBOLS]{
			25,
			25,
			25,
			25,
			25,
			25,
			25,
			25,
			25,
			25,
			25,
			25,
			25
		});
	}

	void CMainGE::initResources()
	{
		CMainBase::initResources();

		_ResourcesGame resourceGame;
		std::string gamePrefix = getSlotGameLocationPrefix();
		//gamePrefix = "slotgame/goldenegg/";

		//Loader Res
		resourceGame.loader["bg"] = gamePrefix + "sprites/bg-loading.png";
		resourceGame.loader["icon"] = gamePrefix + "sprites/preloader_anim.png";
		//Font
		auto fontPath = gamePrefix + "Skater Girls Rock.ttf";

		resourceGame.fontConfigs["win_anim"] = TTFConfig(fontPath, 30);
		resourceGame.fontConfigs["win_anim"].outlineSize = 2;
		resourceGame.fontConfigs["win_panel_title"] = TTFConfig(fontPath, 48);
		resourceGame.fontConfigs["win_panel_title"].outlineSize = 4;
		resourceGame.fontConfigs["win_panel_message"] = resourceGame.fontConfigs["win_panel_title"];
		resourceGame.fontConfigs["freespin"] = TTFConfig(fontPath, 45);
		resourceGame.fontConfigs["freespin"].bold = true;
		resourceGame.fontConfigs["bonus_freespin"] = TTFConfig(fontPath, 45);
		resourceGame.fontConfigs["bonus_freespin"].outlineSize = 5;
		resourceGame.fontConfigs["bonus_freespin_egg"] = TTFConfig(fontPath, 40);
		resourceGame.fontConfigs["double_up"] = TTFConfig(fontPath, 35);
		resourceGame.fontConfigs["double_up"].outlineSize = 4;
		//Main Game Res
		resourceGame.mainGame["bg"] = gamePrefix + "sprites/game-bg.png";
		resourceGame.mainGame["bg_freespin"] = gamePrefix + "sprites/bg-freespins.png";
		resourceGame.mainGame["total_winning"] = gamePrefix + "sprites/totalwinning.png";
		resourceGame.mainGame["info_page_1"] = gamePrefix + "sprites/info_1.png";
		resourceGame.mainGame["info_page_2"] = gamePrefix + "sprites/info_2.png";
		resourceGame.mainGame["info_page_3"] = gamePrefix + "sprites/info_3.png";
		resourceGame.mainGame["info_page_4"] = gamePrefix + "sprites/info_4.png";
		resourceGame.mainGame["info_page_5"] = gamePrefix + "sprites/info_5.png";
		resourceGame.mainGame["symbols_plist"] = gamePrefix + "sprites/symbols.plist";
		resourceGame.mainGame["but_spin_plist"] = gamePrefix + "sprites/but_spin.plist";

		resourceGame.mainGame["farmer_plist"] = gamePrefix + "sprites/animation/farmer.plist";
		resourceGame.mainGame["lady_plist"] = gamePrefix + "sprites/animation/lady.plist";

		resourceGame.mainGame["double_up_loading"] = gamePrefix + "sprites/doubleup-loading.png";
		resourceGame.mainGame["bonus_loading"] = gamePrefix + "sprites/bonus-loading.png";
		//Animation Symbol And Res
		resourceGame.symbolAnims["symbol_0_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_0.plist";
		resourceGame.symbolAnims["symbol_1_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_1.plist";
		resourceGame.symbolAnims["symbol_2_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_2.plist";
		resourceGame.symbolAnims["symbol_3_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_3.plist";
		resourceGame.symbolAnims["symbol_4_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_4.plist";
		resourceGame.symbolAnims["symbol_5_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_5.plist";
		resourceGame.symbolAnims["symbol_6_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_6.plist";
		resourceGame.symbolAnims["symbol_7_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_7.plist";
		resourceGame.symbolAnims["symbol_8_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_8.plist";
		resourceGame.symbolAnims["symbol_9_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_9.plist";
		resourceGame.symbolAnims["symbol_10_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_10.plist";
		resourceGame.symbolAnims["symbol_11_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_11.plist";
		resourceGame.symbolAnims["symbol_12_plist"] = gamePrefix + "sprites/anim_symbol/anim_symbol_12.plist";
		//Line Res
		resourceGame.lines["1"] = gamePrefix + "sprites/lines/line_1_2_3.png";
		resourceGame.lines["2"] = gamePrefix + "sprites/lines/line_1_2_3.png";
		resourceGame.lines["3"] = gamePrefix + "sprites/lines/line_1_2_3.png";
		resourceGame.lines["4"] = gamePrefix + "sprites/lines/line_4.png";
		resourceGame.lines["5"] = gamePrefix + "sprites/lines/line_5.png";
		resourceGame.lines["6"] = gamePrefix + "sprites/lines/line_6_15.png";
		resourceGame.lines["7"] = gamePrefix + "sprites/lines/line_7_14.png";
		resourceGame.lines["8"] = gamePrefix + "sprites/lines/line_8_16.png";
		resourceGame.lines["9"] = gamePrefix + "sprites/lines/line_9_17.png";
		resourceGame.lines["10"] = gamePrefix + "sprites/lines/line_10_13.png";
		resourceGame.lines["11"] = gamePrefix + "sprites/lines/line_11_12.png";
		resourceGame.lines["12"] = gamePrefix + "sprites/lines/line_11_12.png";
		resourceGame.lines["13"] = gamePrefix + "sprites/lines/line_10_13.png";
		resourceGame.lines["14"] = gamePrefix + "sprites/lines/line_7_14.png";
		resourceGame.lines["15"] = gamePrefix + "sprites/lines/line_6_15.png";
		resourceGame.lines["16"] = gamePrefix + "sprites/lines/line_8_16.png";
		resourceGame.lines["17"] = gamePrefix + "sprites/lines/line_9_17.png";
		resourceGame.lines["18"] = gamePrefix + "sprites/lines/line_18.png";
		resourceGame.lines["19"] = gamePrefix + "sprites/lines/line_19.png";
		resourceGame.lines["20"] = gamePrefix + "sprites/lines/line_20.png";
		resourceGame.lines["21"] = gamePrefix + "sprites/lines/line_21.png";
		resourceGame.lines["22"] = gamePrefix + "sprites/lines/line_22.png";
		resourceGame.lines["23"] = gamePrefix + "sprites/lines/line_23.png";
		resourceGame.lines["24"] = gamePrefix + "sprites/lines/line_24.png";
		resourceGame.lines["25"] = gamePrefix + "sprites/lines/line_25.png";
		//Double Up Res
		resourceGame.doubleUp["bg"] = gamePrefix + "sprites/doubleUp/bg.png";
		resourceGame.doubleUp["symbols_plist"] = gamePrefix + "sprites/doubleUp/double_up.plist";

		//Bonus Res
		resourceGame.bonus1["bonus_symbols"] = gamePrefix + "sprites/bonus_freespin/bonus_symbols.plist";
		resourceGame.bonus1["bonus_anim_side"] = gamePrefix + "sprites/bonus_freespin/bonus_anim_side.plist";
		resourceGame.bonus1["bonus_anim_front"] = gamePrefix + "sprites/bonus_freespin/bonus_anim_front.plist";
		
		//Sound Res
		resourceGame.sound["main_game"] = gamePrefix + "sounds/Main-BG-music.mp3";
		resourceGame.sound["free_spin"] = gamePrefix + "sounds/Free Spins-BG-music.mp3";
		resourceGame.sound["double_up"] = gamePrefix + "sounds/Bonus ,DoubleUp-BG-music.mp3";
		resourceGame.sound["bonus_3"] = gamePrefix + "sounds/GE-Bonus BGM.mp3";

		resourceGame.sound["double_up_clicked"] = gamePrefix + "sounds/Bonus, Double up -selection.mp3";
		resourceGame.sound["double_up_collect"] = gamePrefix + "sounds/Bonus, Double up -collect.mp3";
		resourceGame.sound["double_up_win"] = gamePrefix + "sounds/Double Up- Win.mp3";
		resourceGame.sound["double_up_lose"] = gamePrefix + "sounds/Double Up-lose.mp3";
		resourceGame.sound["bonus_3_clicked"] = gamePrefix + "sounds/Bonus, Double up -selection.mp3";
		resourceGame.sound["bonus_3_reward"] = gamePrefix + "sounds/Reward reveal-Bonus.mp3";

		resourceGame.sound["spin"] = gamePrefix + "sounds/spin.mp3";
		resourceGame.sound["reel_spin"] = gamePrefix + "sounds/ReelSpin.mp3";
		resourceGame.sound["reel_stop"] = gamePrefix + "sounds/reelstop.mp3";
		resourceGame.sound["scatter_stop"] = gamePrefix + "sounds/scatterstop.mp3";

		resourceGame.sound["symbol_0"] = gamePrefix + "sounds/symbol_0.mp3";
		resourceGame.sound["symbol_1"] = gamePrefix + "sounds/symbol_1_2_3.mp3";
		resourceGame.sound["symbol_2"] = gamePrefix + "sounds/symbol_1_2_3.mp3";
		resourceGame.sound["symbol_3"] = gamePrefix + "sounds/symbol_1_2_3.mp3";
		resourceGame.sound["symbol_4"] = gamePrefix + "sounds/symbol_4_5.mp3";
		resourceGame.sound["symbol_5"] = gamePrefix + "sounds/symbol_4_5.mp3";
		resourceGame.sound["symbol_6"] = gamePrefix + "sounds/symbol_6_7.mp3";
		resourceGame.sound["symbol_7"] = gamePrefix + "sounds/symbol_6_7.mp3";
		resourceGame.sound["symbol_8"] = gamePrefix + "sounds/symbol_8.mp3";
		resourceGame.sound["symbol_9"] = gamePrefix + "sounds/symbol_9.mp3";
		resourceGame.sound["symbol_10"] = gamePrefix + "sounds/symbol_10.mp3";
		resourceGame.sound["symbol_11"] = gamePrefix + "sounds/symbol_11.mp3";
		resourceGame.sound["symbol_12"] = gamePrefix + "sounds/symbol_12.mp3";

		resourceGame.sound["total_winning"] = gamePrefix + "sounds/Free Spins-totalwinning.mp3";

		for (auto res : resourceGame.mainGame) {
			this->aResources.push_back(res.second);
		}
		for (auto res : resourceGame.sound) {
			this->aResources.push_back(res.second);
		}

		for (auto res : resourceGame.symbolAnims) {
			this->aResourcesExtend.push_back(res.second);
		}
		for (auto res : resourceGame.lines) {
			this->aResourcesExtend.push_back(res.second);
		}

		GameConstant::getInstance()->initResources(resourceGame);
	}

	void CMainGE::gotoGame()
	{
		if (this->bAllResourcesLoaded && this->bFinishAPI) {
			this->oGame = new CGameGE(this);
			CMainBase::gotoGame();
		}
	}
}