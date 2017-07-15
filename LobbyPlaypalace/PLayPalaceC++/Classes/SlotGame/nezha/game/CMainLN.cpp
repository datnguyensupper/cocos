#include "CMainLN.h"
#include "CGameLN.h"

USING_NS_CC;
namespace GameSlot {
	// on "init" you need to initialize your instance
	bool CMainLN::init()
	{
		this->gameName = "Nezha";
		//////////////////////////////
		// 1. super init first
		if (!CMainBase::init())
		{
			return false;
		}

		return true;
	}

	void CMainLN::initSettings()
	{
		CSettings::REEL_OFFSET_X = CSettings::CANVAS_WIDTH * 0.199f + 1;
		CSettings::REEL_OFFSET_Y = CSettings::CANVAS_HEIGHT * 0.78f;
		CSettings::NUM_SYMBOLS = 11;
		CSettings::SCATTER_SYMBOL = 10;
		CSettings::WILD_SYMBOL = 12;
		CSettings::BONUS_3_SYMBOL = 8;
		CSettings::BONUS_4_SYMBOL = 9;
		CSettings::NUM_PAYLINES = 30;
		CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS = 16.5f;
		CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS = 3.5f;
		CSettings::NUM_INFO_PAGES = 5;
		CSettings::IS_SHOW_ANIMATION_FRAMEWIN = false;
		CSettings::SCALE_SYMBOL = 1.0;
		CSettings::SCALE_SYMBOL_ANIM = 1.15f;
		CSettings::SCALE_SYMBOL_MIN = 1.0f;
		CSettings::SCALE_SYMBOL_MAX = 1.3f;
		CSettings::TIMER_ANIM_ZOOM_DOWN = 0.5f;
		CSettings::AMOUNT_WIN_POSITION = Vec2(0, -76.5f);
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
			21,
			23,
			21,
			23,
			24,
			19,
			24,
			21,
			23,
			23,
			20
		},
			new Vec2[11]{
			Vec2(101 / 200.0f, 1 - 91 / 216.0f),
			Vec2(80 / 159.0f, 1 - 68 / 162.0f),
			Vec2(112 / 213.0f, 1 - 68 / 177.0f),
			Vec2(81 / 162.0f, 1 - 81 / 163.0f),
			Vec2(95 / 176.0f, 1 - 103 / 170.0f),
			Vec2(97 / 197.0f, 1 - 99 / 187.0f),
			Vec2(101 / 213.0f, 1 - 103 / 184.0f),
			Vec2(127 / 237.0f, 1 - 100 / 198.0f),
			Vec2(109 / 183.0f, 1 - 125 / 194.0f),
			Vec2(107 / 191.0f, 1 - 84 / 190.0f),
			Vec2(73 / 153.0f, 1 - 110 / 179.0f)
		}
			);
	}

	void CMainLN::initResources()
	{
		CMainBase::initResources();

		_ResourcesGame resourceGame;

		//Loader Res
		resourceGame.loader["bg"] = "slotgame/nezha/sprites/bg-loading.png";
		resourceGame.loader["icon"] = "slotgame/nezha/sprites/preloader_anim.png";
		//Font
		auto fontPath = "slotgame/nezha/copperplatessibold.ttf";

		resourceGame.fontConfigs["win_anim"] = TTFConfig(fontPath, 35);
		resourceGame.fontConfigs["win_panel_title"] = TTFConfig(fontPath, 85);
		resourceGame.fontConfigs["win_panel_title"].outlineSize = 4;
		resourceGame.fontConfigs["win_panel_message"] = resourceGame.fontConfigs["win_panel_title"];
		resourceGame.fontConfigs["freespin"] = TTFConfig(fontPath, 42);
		resourceGame.fontConfigs["freespin"].bold = true;
		resourceGame.fontConfigs["bonus_palace"] = TTFConfig(fontPath, 30);
		resourceGame.fontConfigs["bonus_palace"].bold = true;
		resourceGame.fontConfigs["bonus_battle"] = TTFConfig(fontPath, 25);
		resourceGame.fontConfigs["bonus_battle"].bold = true;
		resourceGame.fontConfigs["bonus_battle"].outlineSize = 4;
		//Main Game Res
		resourceGame.mainGame["bg"] = "slotgame/nezha/sprites/game-bg.png";
		resourceGame.mainGame["reel"] = "slotgame/nezha/sprites/reel.png";
		resourceGame.mainGame["total_winning"] = "slotgame/nezha/sprites/totalwinning.png";
		resourceGame.mainGame["info_page_1"] = "slotgame/nezha/sprites/info_1.png";
		resourceGame.mainGame["info_page_2"] = "slotgame/nezha/sprites/info_2.png";
		resourceGame.mainGame["info_page_3"] = "slotgame/nezha/sprites/info_3.png";
		resourceGame.mainGame["info_page_4"] = "slotgame/nezha/sprites/info_4.png";
		resourceGame.mainGame["info_page_5"] = "slotgame/nezha/sprites/info_5.png";
		resourceGame.mainGame["symbols_plist"] = "slotgame/nezha/sprites/symbols.plist";
		resourceGame.mainGame["sea_animation_plist"] = "slotgame/nezha/sprites/animation/background/sea_animation.plist";
		resourceGame.mainGame["nezha_idle_plist"] = "slotgame/nezha/sprites/animation/nezha/nezha_idle.plist";
		resourceGame.mainGame["nezha_freespin_plist"] = "slotgame/nezha/sprites/animation/nezha/nezha_freespin.plist";
		resourceGame.mainGame["but_spin_plist"] = "slotgame/nezha/sprites/but_spin.plist";
		resourceGame.mainGame["explosion_plist"] = "slotgame/nezha/sprites/animation/effect/explosion.plist";
		resourceGame.mainGame["free_spin_dragon_plist"] = "slotgame/nezha/sprites/freespin/dragon.plist";
		resourceGame.mainGame["free_spin_dragon_wild_plist"] = "slotgame/nezha/sprites/freespin/dragon_wild.plist";
		//Animation Symbol And Res
		resourceGame.symbolAnims["symbol_0_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_0.plist";
		resourceGame.symbolAnims["symbol_1_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_1.plist";
		resourceGame.symbolAnims["symbol_2_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_2.plist";
		resourceGame.symbolAnims["symbol_3_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_3.plist";
		resourceGame.symbolAnims["symbol_4_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_4.plist";
		resourceGame.symbolAnims["symbol_5_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_5.plist";
		resourceGame.symbolAnims["symbol_6_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_6.plist";
		resourceGame.symbolAnims["symbol_7_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_7.plist";
		resourceGame.symbolAnims["symbol_8_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_8.plist";
		resourceGame.symbolAnims["symbol_9_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_9.plist";
		resourceGame.symbolAnims["symbol_10_plist"] = "slotgame/nezha/sprites/anim_symbol/anim_symbol_10.plist";
		//Line Res
		resourceGame.lines["1"] = "slotgame/nezha/sprites/lines/line_1_2_3.png";
		resourceGame.lines["2"] = "slotgame/nezha/sprites/lines/line_1_2_3.png";
		resourceGame.lines["3"] = "slotgame/nezha/sprites/lines/line_1_2_3.png";
		resourceGame.lines["4"] = "slotgame/nezha/sprites/lines/line_4.png";
		resourceGame.lines["5"] = "slotgame/nezha/sprites/lines/line_5.png";
		resourceGame.lines["6"] = "slotgame/nezha/sprites/lines/line_6_15.png";
		resourceGame.lines["7"] = "slotgame/nezha/sprites/lines/line_7_14.png";
		resourceGame.lines["8"] = "slotgame/nezha/sprites/lines/line_8_16.png";
		resourceGame.lines["9"] = "slotgame/nezha/sprites/lines/line_9_17.png";
		resourceGame.lines["10"] = "slotgame/nezha/sprites/lines/line_10_13.png";
		resourceGame.lines["11"] = "slotgame/nezha/sprites/lines/line_11_12.png";
		resourceGame.lines["12"] = "slotgame/nezha/sprites/lines/line_11_12.png";
		resourceGame.lines["13"] = "slotgame/nezha/sprites/lines/line_10_13.png";
		resourceGame.lines["14"] = "slotgame/nezha/sprites/lines/line_7_14.png";
		resourceGame.lines["15"] = "slotgame/nezha/sprites/lines/line_6_15.png";
		resourceGame.lines["16"] = "slotgame/nezha/sprites/lines/line_8_16.png";
		resourceGame.lines["17"] = "slotgame/nezha/sprites/lines/line_9_17.png";
		resourceGame.lines["18"] = "slotgame/nezha/sprites/lines/line_18.png";
		resourceGame.lines["19"] = "slotgame/nezha/sprites/lines/line_19.png";
		resourceGame.lines["20"] = "slotgame/nezha/sprites/lines/line_20.png";
		resourceGame.lines["21"] = "slotgame/nezha/sprites/lines/line_21.png";
		resourceGame.lines["22"] = "slotgame/nezha/sprites/lines/line_22.png";
		resourceGame.lines["23"] = "slotgame/nezha/sprites/lines/line_23.png";
		resourceGame.lines["24"] = "slotgame/nezha/sprites/lines/line_24.png";
		resourceGame.lines["25"] = "slotgame/nezha/sprites/lines/line_25.png";
		resourceGame.lines["26"] = "slotgame/nezha/sprites/lines/line_26.png";
		resourceGame.lines["27"] = "slotgame/nezha/sprites/lines/line_27.png";
		resourceGame.lines["28"] = "slotgame/nezha/sprites/lines/line_28.png";
		resourceGame.lines["29"] = "slotgame/nezha/sprites/lines/line_29.png";
		resourceGame.lines["30"] = "slotgame/nezha/sprites/lines/line_30.png";
		//Bonus Palace Res
		resourceGame.bonus1["bonus_plist"] = "slotgame/nezha/sprites/bonuspalace/bonus_palace.plist";
		//Bonus Battle Res
		resourceGame.bonus2["bonus_plist_0"] = "slotgame/nezha/sprites/bonusbattle/bonus_battle_0.plist";
		resourceGame.bonus2["bonus_plist_1"] = "slotgame/nezha/sprites/bonusbattle/bonus_battle_1.plist";
		for (int i = 0; i < 17; ++i) {
			resourceGame.bonus2["bg_anim_" + ToString(i)] = "slotgame/nezha/sprites/bonusbattle/bg/Bonus-02-nezha_idle_" + ToString(i) + ".png";
		}
		//Sound Res
		resourceGame.sound["main_game"] = "slotgame/nezha/sounds/soundtrack.mp3";
		resourceGame.sound["free_spin"] = "slotgame/nezha/sounds/soundtrack_bonus_freespin.mp3";
		resourceGame.sound["bonus_3"] = "slotgame/nezha/sounds/soundtrack_bonus_freespin.mp3";
		resourceGame.sound["bonus_4"] = "slotgame/nezha/sounds/soundtrack_bonus_freespin.mp3";

		resourceGame.sound["spin"] = "slotgame/nezha/sounds/spin.mp3";
		resourceGame.sound["reel_stop"] = "slotgame/nezha/sounds/reelstop.mp3";
		resourceGame.sound["scatter_stop"] = "slotgame/nezha/sounds/scatterstop.mp3";
		resourceGame.sound["bonus_3_stop"] = "slotgame/nezha/sounds/bonusStopTaijiPalace.mp3";
		resourceGame.sound["bonus_4_stop"] = "slotgame/nezha/sounds/bonusStopBattle.mp3";

		resourceGame.sound["bonus_3_clicked"] = "slotgame/nezha/sounds/item_select_bonus_palace.mp3";
		resourceGame.sound["bonus_4_clicked"] = "slotgame/nezha/sounds/item_select_bonus_battle.mp3";

		resourceGame.sound["symbol_0"] = "slotgame/nezha/sounds/symbol_0_1_2.mp3";
		resourceGame.sound["symbol_1"] = "slotgame/nezha/sounds/symbol_0_1_2.mp3";
		resourceGame.sound["symbol_2"] = "slotgame/nezha/sounds/symbol_0_1_2.mp3";
		resourceGame.sound["symbol_3"] = "slotgame/nezha/sounds/symbol_3_4.mp3";
		resourceGame.sound["symbol_4"] = "slotgame/nezha/sounds/symbol_3_4.mp3";
		resourceGame.sound["symbol_5"] = "slotgame/nezha/sounds/symbol_5_6.mp3";
		resourceGame.sound["symbol_6"] = "slotgame/nezha/sounds/symbol_5_6.mp3";
		resourceGame.sound["symbol_7"] = "slotgame/nezha/sounds/symbol_7.mp3";
		resourceGame.sound["symbol_8"] = "slotgame/nezha/sounds/symbol_8.mp3";
		resourceGame.sound["symbol_9"] = "slotgame/nezha/sounds/symbol_9.mp3";
		resourceGame.sound["symbol_10"] = "slotgame/nezha/sounds/symbol_10.mp3";

		resourceGame.sound["total_winning"] = "slotgame/nezha/sounds/totalwinning.mp3";

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

	void CMainLN::gotoGame()
	{
		if (this->bAllResourcesLoaded && this->bFinishAPI) {
			this->oGame = new CGameLN(this);
			CMainBase::gotoGame();
		}
	}

	void CMainLN::initLastBonusInfo(tinyxml2::XMLElement* bonusXML)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_TYPE_3:
		{
			this->oBonusToRestore->finish = 0;
			this->oBonusToRestore->history.clear();

			if (bonusXML->FirstChildElement("wheels") != NULL) {
				auto totalFreeSpins = atoi(bonusXML->FirstChildElement("wheels")->Attribute("count"));
				auto totalMulty = atoi(bonusXML->FirstChildElement("wheels")->Attribute("m"));

				for (auto i = bonusXML->FirstChildElement("wheels")->FirstChild();
					i != NULL; i = i->NextSibling()) {
					auto element = i->ToElement();
					if (element) {
						this->oBonusToRestore->history.push_back(ObjectBonus(
							element->IntAttribute("id"),	//select
							atof(element->GetText()),		//win
							element->IntAttribute("t")		//type
						));
					}
				}
				this->oBonusToRestore->finish = atoi(bonusXML->FirstChildElement("wheels")->Attribute("finish"));
			}
			break;
		}
		case BONUS_TYPE::BONUS_FREESPIN:
		{
			if (this->oBonusToRestore->bonus_step > 0) {
				this->oBonusToRestore->counter = atoi(bonusXML->Attribute("counter"));
			}
			else {
				this->oBonusToRestore->counter = -1;
			}
			break;
		}
		case BONUS_TYPE::BONUS_TYPE_4:
		{
			auto dataXML = bonusXML->FirstChildElement("data");
			this->oBonusToRestore->finish = 0;
			this->oBonusToRestore->history.clear();
			if (dataXML->FirstChildElement("wheelsrestore") != NULL) {
				for (auto i = dataXML->FirstChildElement("wheelsrestore")->FirstChild();
					i != NULL; i = i->NextSibling()) {
					auto element = i->ToElement();
					if (element) {
						this->oBonusToRestore->history.push_back(ObjectBonus(
							element->IntAttribute("selected"),	//select
							atof(element->GetText()),		//win
							0		//type
						));
					}
				}
				this->oBonusToRestore->finish = atoi(dataXML->FirstChildElement("wheels")->Attribute("finish"));
			}
			break;
		}
		}
	}

	void CMainLN::onBonusReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_TYPE_3:
		{
			this->onBonusPalaceReceived(oXmlDoc);
			break;
		}
		case BONUS_TYPE::BONUS_FREESPIN:
		{
			this->onBonusFreeSpinWithRetriggerReceived(oXmlDoc);
			break;
		}
		case BONUS_TYPE::BONUS_TYPE_4:
		{
			this->onBonusBattleReceived(oXmlDoc);
			break;
		}
		}
	}

	void CMainLN::onBonusPalaceReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		auto iStep = this->oGame->getStepBonus();

		auto bonusXML = oXmlDoc->FirstChildElement("bonus");

		this->iCredit = atof(bonusXML->FirstChildElement("balance")->FirstChild()->Value());


		auto data = bonusXML->FirstChildElement("data");

		if (iStep == 0) {
			((CGameLN*)this->oGame)->onBonusPalaceStep0Received();
		}
		else {
			auto iFinish = atoi(data->FirstChildElement("wheels")->Attribute("finish"));

			std::vector<ObjectBonus> aWheels;

			for (auto i = data->FirstChildElement("wheels")->FirstChild();
			i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					aWheels.push_back(ObjectBonus(
						element->IntAttribute("selected"),
						atof(element->GetText()),
						0
						));
				}
			}

			((CGameLN*)this->oGame)->onBonusPalaceStep1Received(iFinish, aWheels);
		}
	}

	void CMainLN::onBonusBattleReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		auto iStep = this->oGame->getStepBonus();

		auto bonusXML = oXmlDoc->FirstChildElement("bonus");

		this->iCredit = atof(bonusXML->FirstChildElement("balance")->FirstChild()->Value());

		auto data = bonusXML->FirstChildElement("data");

		if (iStep == 0) {
			((CGameLN*)this->oGame)->onBonusBattleStep0Received();
		}
		else {
			auto iFinish = atoi(data->FirstChildElement("wheels")->Attribute("finish"));

			std::vector<ObjectBonus> aWheels;

			for (auto i = data->FirstChildElement("wheels")->FirstChild();
			i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					aWheels.push_back(ObjectBonus(
						element->IntAttribute("selected"),
						atof(element->GetText()),
						0
						));
				}
			}

			((CGameLN*)this->oGame)->onBonusBattleStep1Received(iFinish, aWheels);
		}
	}
}