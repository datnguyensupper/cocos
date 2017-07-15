#include "CMainPO.h"
#include "CGamePO.h"

USING_NS_CC;
namespace GameSlot {
	// on "init" you need to initialize your instance
	bool CMainPO::init()
	{
		this->gameName = "Pharaoh";
		//////////////////////////////
		// 1. super init first
		if (!CMainBase::init())
		{
			return false;
		}

		return true;
	}

	void CMainPO::initSettings()
	{
		CSettings::REEL_OFFSET_X = 383 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::REEL_OFFSET_Y = 878 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_SYMBOLS = 13;
		CSettings::SCATTER_SYMBOL = 10;
		CSettings::WILD_SYMBOL = 11;
		CSettings::NUM_PAYLINES = 20;
		CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS = 20 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS = 5 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_INFO_PAGES = 7;
		CSettings::IS_SHOW_ANIMATION_FRAMEWIN = true;
		CSettings::SCALE_SYMBOL = 1.0;
		CSettings::SCALE_SYMBOL_ANIM = 1.0f;
		CSettings::SCALE_SYMBOL_MIN = 1.0f;
		CSettings::SCALE_SYMBOL_MAX = 1.0f;
		CSettings::TIMER_ANIM_ZOOM_DOWN = 0.1f;
		CSettings::AMOUNT_WIN_POSITION = Vec2(0, -85);
		CSettings::FRAME_WIN_POSITION = Vec2::ZERO;
		CSettings::SCALE_FRAME_WIN = 1.0f;

		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL = 4.5f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL = 2.0f;
		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST = 1.5f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST = 6.0f;

		CSettings::TIMER_DELAY_UPDATE_REEL = 0.02f;

		CSettings::TIMER_DELAY_SHOW_WIN_BONUS = 2.0f;

		CSettings::ANIM_SYMBOL_FPS = 24;

		CMainBase::initSettings();

		CSlotSettings::getInstance()->initSlotSettings(nullptr);
	}

	void CMainPO::initResources()
	{
		CMainBase::initResources();

		_ResourcesGame resourceGame;
		std::string gamePrefix = getSlotGameLocationPrefix();
		//gamePrefix = "slotgame/pharaoh/";

		//Loader Res
		resourceGame.loader["bg"] = gamePrefix + "sprites/bg-loading.png";
		resourceGame.loader["icon"] = gamePrefix + "sprites/preloader_anim.png";
		//Font
		auto fontPath = gamePrefix + "ADONAIS.ttf";

		resourceGame.fontConfigs["win_anim"] = TTFConfig(fontPath, 35);
		resourceGame.fontConfigs["win_panel_title"] = TTFConfig(fontPath, 70);
		resourceGame.fontConfigs["win_panel_title"].outlineSize = 4;
		resourceGame.fontConfigs["win_panel_message"] = resourceGame.fontConfigs["win_panel_title"];
		resourceGame.fontConfigs["freespin"] = TTFConfig(fontPath, 45);
		resourceGame.fontConfigs["freespin"].bold = true;
		resourceGame.fontConfigs["bonus_3"] = TTFConfig(fontPath, 35);
		resourceGame.fontConfigs["bonus_3"].outlineSize = 4;
		resourceGame.fontConfigs["bonus_4"] = TTFConfig(fontPath, 45);
		resourceGame.fontConfigs["bonus_4"].outlineSize = 5;
		//Main Game Res
		resourceGame.mainGame["bg"] = gamePrefix + "sprites/game-bg.png";
		resourceGame.mainGame["bg_freespin"] = gamePrefix + "sprites/bg-freespins.png";
		resourceGame.mainGame["total_winning"] = gamePrefix + "sprites/totalwinning.png";
		resourceGame.mainGame["info_page_1"] = gamePrefix + "sprites/info_1.png";
		resourceGame.mainGame["info_page_2"] = gamePrefix + "sprites/info_2.png";
		resourceGame.mainGame["info_page_3"] = gamePrefix + "sprites/info_3.png";
		resourceGame.mainGame["info_page_4"] = gamePrefix + "sprites/info_4.png";
		resourceGame.mainGame["info_page_5"] = gamePrefix + "sprites/info_5.png";
		resourceGame.mainGame["info_page_6"] = gamePrefix + "sprites/info_6.png";
		resourceGame.mainGame["info_page_7"] = gamePrefix + "sprites/info_7.png";
		resourceGame.mainGame["symbols_plist"] = gamePrefix + "sprites/symbols.plist";
		resourceGame.mainGame["frame_win_plist"] = gamePrefix + "sprites/animation/frame_win.plist";
		resourceGame.mainGame["freespin_eagle_plist"] = gamePrefix + "sprites/animation/freespin_eagle.plist";
		resourceGame.mainGame["but_spin_plist"] = gamePrefix + "sprites/but_spin.plist";
		//Animation Symbol And Res
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
		//Bonus Palace Res
		resourceGame.bonus1["bg"] = gamePrefix + "sprites/bonusstage1/bg.png";
		resourceGame.bonus1["bonus_plist"] = gamePrefix + "sprites/bonusstage1/bonus_stage1_symbols.plist";
		//Bonus Battle Res
		resourceGame.bonus2["bg"] = gamePrefix + "sprites/bonusstage2/bg.png";
		resourceGame.bonus2["bonus_plist"] = gamePrefix + "sprites/bonusstage2/bonus_stage2_symbols.plist";
		//Sound Res
		resourceGame.sound["main_game"] = gamePrefix + "sounds/Main-BGM.mp3";
		resourceGame.sound["free_spin"] = gamePrefix + "sounds/FreeSpins -BGM.mp3";
		resourceGame.sound["bonus_3"] = gamePrefix + "sounds/Bonus1-BGM.mp3";
		resourceGame.sound["bonus_4"] = gamePrefix + "sounds/Bonus2-BGM.mp3";

		resourceGame.sound["spin"] = gamePrefix + "sounds/Spin.mp3";
		resourceGame.sound["reel_stop"] = gamePrefix + "sounds/ReelStop.mp3";

		resourceGame.sound["bonus_3_clicked"] = gamePrefix + "sounds/Bonus1-selection.mp3";
		resourceGame.sound["bonus_4_clicked"] = gamePrefix + "sounds/Bonus1-selection.mp3";

		resourceGame.sound["eagle"] = gamePrefix + "sounds/TravellingWild.mp3";
		resourceGame.sound["bonus_3_gate_open"] = gamePrefix + "sounds/BonusGateOpen.mp3";
		resourceGame.sound["bonus_4_wheel_spin"] = gamePrefix + "sounds/Bonus2-WheelSpin.mp3";
		resourceGame.sound["bonus_4_wheel_stop"] = gamePrefix + "sounds/Bonus2-WheelStop.mp3";

		resourceGame.sound["symbol_0"] = gamePrefix + "sounds/Symbol_0_1_2_3.mp3";
		resourceGame.sound["symbol_1"] = gamePrefix + "sounds/Symbol_0_1_2_3.mp3";
		resourceGame.sound["symbol_2"] = gamePrefix + "sounds/Symbol_0_1_2_3.mp3";
		resourceGame.sound["symbol_3"] = gamePrefix + "sounds/Symbol_0_1_2_3.mp3";
		resourceGame.sound["symbol_4"] = gamePrefix + "sounds/Symbol_4_5_6_7.mp3";
		resourceGame.sound["symbol_5"] = gamePrefix + "sounds/Symbol_4_5_6_7.mp3";
		resourceGame.sound["symbol_6"] = gamePrefix + "sounds/Symbol_4_5_6_7.mp3";
		resourceGame.sound["symbol_7"] = gamePrefix + "sounds/Symbol_4_5_6_7.mp3";
		resourceGame.sound["symbol_8"] = gamePrefix + "sounds/symbol_8.mp3";
		resourceGame.sound["symbol_9"] = gamePrefix + "sounds/symbol_9.mp3";
		resourceGame.sound["symbol_10"] = gamePrefix + "sounds/symbol_10.mp3";

		resourceGame.sound["total_winning"] = gamePrefix + "sounds/TotalWin.mp3";

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

	void CMainPO::gotoGame()
	{
		if (this->bAllResourcesLoaded && this->bFinishAPI) {
			this->oGame = new CGamePO(this);
			CMainBase::gotoGame();
		}
	}

	void CMainPO::initLastBonusInfo(tinyxml2::XMLElement* bonusXML)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_TYPE_3:
		{
			this->oBonusToRestore->finish = 0;
			this->oBonusToRestore->history.clear();

			if (this->oBonusToRestore->bonus_step > 1 && this->oBonusToRestore->bonus_step != 4) {
				if (this->oBonusToRestore->bonus_step < 4) {
					auto stage = bonusXML->FirstChildElement("data")->FirstChildElement("wheels")->FirstChildElement("stage");

					std::vector<ObjectBonus> aWheels;

					for (auto i = stage->FirstChild();
					i != NULL; i = i->NextSibling()) {
						auto element = i->ToElement();
						if (element) {
							aWheels.push_back(ObjectBonus(
								element->IntAttribute("selected"),
								atof(element->GetText()),
								element->IntAttribute("prize")
								));
						}
					}

					this->oBonusToRestore->finish = atoi(stage->Attribute("finish"));
					this->oBonusToRestore->history = aWheels;

				}
				else if (this->oBonusToRestore->bonus_step == 5) {
					this->oBonusToRestore->counter = atoi(bonusXML->FirstChildElement("data")->FirstChildElement("count")->Attribute("mode"));
				}
				else {
					auto stage = bonusXML->FirstChildElement("data")->FirstChildElement("wheels")->FirstChildElement("stage");

					this->oBonusToRestore->counter = atoi(stage->Attribute("mode"));
					std::vector<ObjectBonus> aWheels;

					auto iWin = atof(stage->Attribute("win"));

					for (auto i = stage->FirstChild();
					i != NULL; i = i->NextSibling()) {
						auto element = i->ToElement();
						if (element) {
							aWheels.push_back(ObjectBonus(
								1,
								iWin,
								element->IntAttribute("prize")
								));
						}
					}

					this->oBonusToRestore->finish = atoi(stage->Attribute("finish"));
					this->oBonusToRestore->history = aWheels;
				}
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
		}
	}

	void CMainPO::onBonusReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_TYPE_3:
		{
			this->onBonusStageReceived(oXmlDoc);
			break;
		}
		case BONUS_TYPE::BONUS_FREESPIN:
		{
			this->onBonusFreeSpinWithRetriggerReceived(oXmlDoc);
			break;
		}
		}
	}

	void CMainPO::onBonusStageReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		auto iStep = this->oGame->getStepBonus();

		auto bonusXML = oXmlDoc->FirstChildElement("bonus");

		this->iCredit = atof(bonusXML->FirstChildElement("balance")->FirstChild()->Value());


		auto data = bonusXML->FirstChildElement("data");

		if (iStep == 0) {
			((CGamePO*)this->oGame)->onBonusStage1Step0Received();
		}
		else if(iStep < 4) {
			auto stage = data->FirstChildElement("wheels")->FirstChildElement("stage");

			auto iFinish = atoi(stage->Attribute("finish"));

			std::vector<ObjectBonus> aWheels;

			for (auto i = stage->FirstChild();
			i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					aWheels.push_back(ObjectBonus(
						element->IntAttribute("selected"),
						atof(element->GetText()),
						element->IntAttribute("prize")
						));
				}
			}

			((CGamePO*)this->oGame)->onBonusStage1Step1Received(iFinish, aWheels);
		}
		else if (iStep == 4) {
			auto iMode = atoi(data->FirstChildElement("count")->Attribute("mode"));
			((CGamePO*)this->oGame)->onBonusStage2Step0Received(iMode);
		}
		else if (iStep < 7) {
			auto stage = data->FirstChildElement("wheels")->FirstChildElement("stage");

			auto iFinish = atoi(stage->Attribute("finish"));

			auto iWin = atof(stage->Attribute("win"));

			std::vector<ObjectBonus> aWheels;

			for (auto i = stage->FirstChild();
			i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					aWheels.push_back(ObjectBonus(
						element->IntAttribute("selected"),
						iWin,
						element->IntAttribute("prize")
						));
				}
			}

			((CGamePO*)this->oGame)->onBonusStage2Step1Received(iFinish, aWheels);
		}
		else {
			auto stage = data->FirstChildElement("wheels")->FirstChildElement("stage");

			auto iFinish = atoi(stage->NextSiblingElement()->Attribute("finish"));

			auto iWin1 = atof(stage->Attribute("win"));
			auto iWin2 = atof(stage->NextSiblingElement()->Attribute("win"));

			std::vector<ObjectBonus> aWheels;

			for (auto i = stage->NextSibling()->FirstChild();
			i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					aWheels.push_back(ObjectBonus(
						element->IntAttribute("selected"),
						iWin1,
						0,
						iWin2,
						element->IntAttribute("prize")
						));
				}
			}
			((CGamePO*)this->oGame)->onBonusStage2Step1Received(iFinish, aWheels);
		}
	}
}