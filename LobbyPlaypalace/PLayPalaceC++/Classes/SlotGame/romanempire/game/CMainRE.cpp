#include "CMainRE.h"
#include "CGameRE.h"

USING_NS_CC;
namespace GameSlot {
	// on "init" you need to initialize your instance
	bool CMainRE::init()
	{
		this->gameName = "RomanEmpire";
		//////////////////////////////
		// 1. super init first
		if (!CMainBase::init())
		{
			return false;
		}

		return true;
	}

	void CMainRE::initSettings()
	{
		CSettings::REEL_OFFSET_X = 388 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::REEL_OFFSET_Y = 870 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_SYMBOLS = 13;
		CSettings::SCATTER_SYMBOL = 11;
		CSettings::WILD_SYMBOL = 12;
		CSettings::NUM_PAYLINES = 30;
		CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS = 19 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS = 4 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_INFO_PAGES = 4;
		CSettings::IS_SHOW_ANIMATION_FRAMEWIN = true;
		CSettings::SCALE_SYMBOL = 1.0f;
		CSettings::SCALE_SYMBOL_ANIM = 1.0f;
		CSettings::SCALE_SYMBOL_MIN = 1.0f;
		CSettings::SCALE_SYMBOL_MAX = 1.5f;
		CSettings::TIMER_ANIM_ZOOM_DOWN = 0.5f;
		CSettings::AMOUNT_WIN_POSITION = Vec2(0, -115) * CSettings::SCALE_VALUE_TO_1920;
		CSettings::FRAME_WIN_POSITION = Vec2::ZERO;
		CSettings::SCALE_FRAME_WIN = 1.0f;

		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL = 2.5f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL = 2.0f;
		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST = 1.5f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST = 3.0f;

		CSettings::TIMER_DELAY_UPDATE_REEL = 0.0f;

		CSettings::TIMER_DELAY_SHOW_WIN_BONUS = 1.0f;

		CSettings::ANIM_SYMBOL_FPS = 20;

		CMainBase::initSettings();

		CSlotSettings::getInstance()->initSlotSettings(new int[CSettings::NUM_SYMBOLS]{
			30,
			30,
			30,
			30,
			30,
			30,
			30,
			30,
			30,
			30,
			30,
			30,
			30
		});
	}

	void CMainRE::initResources()
	{
		CMainBase::initResources();

		_ResourcesGame resourceGame;
		std::string gamePrefix = getSlotGameLocationPrefix();
		//gamePrefix = "slotgame/romanempire/";

		//Loader Res
		resourceGame.loader["bg"] = gamePrefix + "sprites/bg-loading.png";
		resourceGame.loader["icon"] = gamePrefix + "sprites/preloader_anim.png";
		//Font
		auto fontPath = gamePrefix + "DALEK_.TTF";

		resourceGame.fontConfigs["win_anim"] = TTFConfig(fontPath, 35);
		resourceGame.fontConfigs["win_panel_title"] = TTFConfig(fontPath, 70);
		resourceGame.fontConfigs["win_panel_title"].outlineSize = 4;
		resourceGame.fontConfigs["win_panel_message"] = TTFConfig(fontPath, 65);
		resourceGame.fontConfigs["win_panel_message"].outlineSize = 4;
		resourceGame.fontConfigs["double_up"] = TTFConfig(fontPath, 25);
		resourceGame.fontConfigs["double_up"].outlineSize = 4;
		//Main Game Res
		resourceGame.mainGame["bg"] = gamePrefix + "sprites/game-bg.png";
		resourceGame.mainGame["total_winning"] = gamePrefix + "sprites/totalwinning.png";
		resourceGame.mainGame["info_page_1"] = gamePrefix + "sprites/info_1.png";
		resourceGame.mainGame["info_page_2"] = gamePrefix + "sprites/info_2.png";
		resourceGame.mainGame["info_page_3"] = gamePrefix + "sprites/info_3.png";
		resourceGame.mainGame["info_page_4"] = gamePrefix + "sprites/info_4.png";
		resourceGame.mainGame["symbols_plist"] = gamePrefix + "sprites/symbols.plist";
		resourceGame.mainGame["but_spin_plist"] = gamePrefix + "sprites/but_spin.plist";

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
		resourceGame.lines["26"] = gamePrefix + "sprites/lines/line_26.png";
		resourceGame.lines["27"] = gamePrefix + "sprites/lines/line_27.png";
		resourceGame.lines["28"] = gamePrefix + "sprites/lines/line_28.png";
		resourceGame.lines["29"] = gamePrefix + "sprites/lines/line_29.png";
		resourceGame.lines["30"] = gamePrefix + "sprites/lines/line_30.png";
		//Double Up Res
		resourceGame.doubleUp["double_up"] = gamePrefix + "sprites/doubleUp/double_up.plist";

		for (int i = 1; i <= 36; ++i) {
			resourceGame.doubleUp["result_" + ToString(i)] = 
				gamePrefix + StringUtils::format("sprites/doubleUp/animation/result_%i.png", i);
		}
		for (int i = 1; i <= 10; ++i) {
			resourceGame.doubleUp["result_head_" + ToString(i)] =
				gamePrefix + StringUtils::format("sprites/doubleUp/animation/head/result_head_%i.png", i);

			resourceGame.doubleUp["result_tail_" + ToString(i)] =
				gamePrefix + StringUtils::format("sprites/doubleUp/animation/tail/result_tail_%i.png", i);

		}

		//Bonus Res
		resourceGame.bonus1["bg"] = gamePrefix + "sprites/bonus/bg_bonus_freespin.png";
		resourceGame.bonus1["bonus_symbols"] = gamePrefix + "sprites/bonus/bonus_symbols.plist";
		
		//Sound Res
		resourceGame.sound["main_game"] = gamePrefix + "sounds/RomanEmpire-Main BGM.mp3";
		resourceGame.sound["double_up"] = gamePrefix + "sounds/RomanEmpire-DoubleUP-BGM.mp3";
		resourceGame.sound["bonus_3"] = gamePrefix + "sounds/RomanEmpire-Bonus-BGM.mp3";

		resourceGame.sound["double_up_clicked"] = gamePrefix + "sounds/Spin.mp3";
		resourceGame.sound["double_up_win"] = gamePrefix + "sounds/SelectCoin_Win.mp3";
		resourceGame.sound["double_up_lose"] = gamePrefix + "sounds/SelectCoin_Lose.mp3";
		resourceGame.sound["double_up_coin"] = gamePrefix + "sounds/Coin.mp3";

		resourceGame.sound["bonus_3_clicked"] = gamePrefix + "sounds/Spin.mp3";
		resourceGame.sound["bonus_3_wheel"] = gamePrefix + "sounds/WheelOfFortune.mp3";

		resourceGame.sound["spin"] = gamePrefix + "sounds/Spin.mp3";
		resourceGame.sound["reel_stop"] = gamePrefix + "sounds/Reel-stop.mp3";
		resourceGame.sound["scatter_stop"] = gamePrefix + "sounds/reel_stop_Bonus1.mp3";
		resourceGame.sound["wild_stop"] = gamePrefix + "sounds/Reel_stop-Wild.mp3";

		resourceGame.sound["symbol_0"] = gamePrefix + "sounds/Symbol_0_1_Colloseum_Jar.mp3";
		resourceGame.sound["symbol_1"] = gamePrefix + "sounds/Symbol_0_1_Colloseum_Jar.mp3";
		resourceGame.sound["symbol_2"] = gamePrefix + "sounds/Symbol_2_3_Sword_MaceSpike.mp3";
		resourceGame.sound["symbol_3"] = gamePrefix + "sounds/Symbol_2_3_Sword_MaceSpike.mp3";
		resourceGame.sound["symbol_4"] = gamePrefix + "sounds/Symbol_4_5_Helmet_Shield.mp3";
		resourceGame.sound["symbol_5"] = gamePrefix + "sounds/Symbol_4_5_Helmet_Shield.mp3";
		resourceGame.sound["symbol_6"] = gamePrefix + "sounds/Symbol_6_7_Necklace_ArenaBalcony.mp3";
		resourceGame.sound["symbol_7"] = gamePrefix + "sounds/Symbol_6_7_Necklace_ArenaBalcony.mp3";
		resourceGame.sound["symbol_8"] = gamePrefix + "sounds/Symbol_8_Helena.mp3";
		resourceGame.sound["symbol_9"] = gamePrefix + "sounds/Symbol_9_Gladiator.mp3";
		resourceGame.sound["symbol_10"] = gamePrefix + "sounds/Symbol_10_RomanSoldier.mp3";
		resourceGame.sound["symbol_11"] = gamePrefix + "sounds/Symbol_11_RomanCoins.mp3";

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

	void CMainRE::gotoGame()
	{
		if (this->bAllResourcesLoaded && this->bFinishAPI) {
			this->oGame = new CGameRE(this);
			CMainBase::gotoGame();
		}
	}

	void CMainRE::initLastBonusInfo(tinyxml2::XMLElement* bonusXML)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_DOUBLE_UP:
		{
			this->oBonusToRestore->finish = 0;
			this->oBonusToRestore->history.clear();

			this->oBonusToRestore->win = atof(bonusXML->FirstChildElement("data")->Attribute("gamewin"));

			if (bonusXML->FirstChildElement("wheels") != NULL) {
				for (auto i = bonusXML->FirstChildElement("wheels")->FirstChild();
				i != NULL; i = i->NextSibling()) {
					auto element = i->ToElement();
					if (element) {
						this->oBonusToRestore->win = atof(element->GetText());
					}
				}
				this->oBonusToRestore->finish = atoi(bonusXML->FirstChildElement("wheels")->Attribute("finish"));
			}
			break;
		}
		case BONUS_TYPE::BONUS_TYPE_3:
		{
			auto dataXML = bonusXML->FirstChildElement("data");

			this->oBonusToRestore->finish = 0;
			this->oBonusToRestore->history.clear();

			if (dataXML && dataXML->FirstChildElement("wheels") != NULL) {
				
				auto element = dataXML->FirstChildElement("wheels")->FirstChild()->ToElement();

				this->oBonusToRestore->finish = atoi(dataXML->FirstChildElement("wheels")->Attribute("finish"));
				this->oBonusToRestore->win = atof(element->GetText());
				this->oBonusToRestore->multiplier = element->IntAttribute("mul");
			}
			break;
		}
		}
	}

	void CMainRE::onBonusReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_DOUBLE_UP:
			this->onDoubleUpReceive(oXmlDoc);
			break;
		case BONUS_TYPE::BONUS_TYPE_3:
			this->onBonusFreeSpinReceived(oXmlDoc);
			break;
		}
	}
	void CMainRE::onBonusFreeSpinReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		auto iStep = this->oGame->getStepBonus();

		auto bonusXML = oXmlDoc->FirstChildElement("bonus");

		this->iCredit = atof(bonusXML->FirstChildElement("balance")->FirstChild()->Value());

		auto wheelXML = bonusXML->FirstChildElement("data")->FirstChildElement("wheels");

		if (iStep == 0) {
			((CGameRE*)this->oGame)->onBonusStep0Received();
		}
		else {
			auto iFinish = atoi(wheelXML->Attribute("finish"));
			int iMul = 0;
			double iWin = 0;

			for (auto i = wheelXML->FirstChild();
			i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					iMul = element->IntAttribute("mul");
					iWin = atof(element->GetText());
				}
			}

			((CGameRE*)this->oGame)->onBonusStep1Received(iFinish, iMul, iWin);
		}
	}
}