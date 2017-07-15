#include "CMainBO.h"
#include "CGameBO.h"
#include "CDoubleUpBO.h"

USING_NS_CC;
namespace GameSlot {
	// on "init" you need to initialize your instance
	bool CMainBO::init()
	{
		this->gameName = "Boxing";
		//////////////////////////////
		// 1. super init first
		if (!CMainBase::init())
		{
			return false;
		}

		return true;
	}

	void CMainBO::initSettings()
	{
		CSettings::REEL_OFFSET_X = 387 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::REEL_OFFSET_Y = 858 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_SYMBOLS = 13;
		CSettings::SCATTER_SYMBOL = 11;
		CSettings::WILD_SYMBOL = 12;
		CSettings::NUM_PAYLINES = 15;
		CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS = 19 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS = 4 * CSettings::SCALE_VALUE_TO_1920;
		CSettings::NUM_INFO_PAGES = 5;
		CSettings::IS_SHOW_ANIMATION_FRAMEWIN = true;
		CSettings::SCALE_SYMBOL = 1.0f;
		CSettings::SCALE_SYMBOL_ANIM = 1.0f;
		CSettings::SCALE_SYMBOL_MIN = 0.9f;
		CSettings::SCALE_SYMBOL_MAX = 1.5f;
		CSettings::TIMER_ANIM_ZOOM_DOWN = 0.5f;
		CSettings::AMOUNT_WIN_POSITION = Vec2(0, -115) * CSettings::SCALE_VALUE_TO_1920;
		CSettings::FRAME_WIN_POSITION = Vec2(5, 0);
		CSettings::SCALE_FRAME_WIN = 1.3f;

		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL = 2.5f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL = 2.0f;
		CSettings::TIMER_RUN_ANIMATION_TEXT_WIN_PANNEL_FAST = 1.5f;
		CSettings::TIMER_WAITING_TEXT_WIN_PANEL_FAST = 3.0f;

		CSettings::TIMER_DELAY_UPDATE_REEL = 0.0f;

		CSettings::TIMER_DELAY_SHOW_WIN_BONUS = 2.0f;

		CSettings::ANIM_SYMBOL_FPS = 24;

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

	void CMainBO::initResources()
	{
		CMainBase::initResources();

		_ResourcesGame resourceGame;
		std::string gamePrefix = getSlotGameLocationPrefix();
		//gamePrefix = "slotgame/boxing/";

		//Loader Res
		resourceGame.loader["bg"] = gamePrefix + "sprites/bg-loading.png";
		resourceGame.loader["icon"] = gamePrefix + "sprites/preloader_anim.png";
		//Font
		auto fontPath = gamePrefix + "AMERICAN-CAPTAIN.ttf";

		resourceGame.fontConfigs["win_anim"] = TTFConfig(fontPath, 45);
		resourceGame.fontConfigs["win_panel_title"] = TTFConfig(fontPath, 85);
		resourceGame.fontConfigs["win_panel_title"].outlineSize = 4;
		resourceGame.fontConfigs["win_panel_message"] = TTFConfig(fontPath, 100);
		resourceGame.fontConfigs["win_panel_message"].outlineSize = 4;
		resourceGame.fontConfigs["freespin"] = TTFConfig(fontPath, 30);
		resourceGame.fontConfigs["freespin"].bold = true;
		resourceGame.fontConfigs["double_up_win"] = TTFConfig(fontPath, 25);
		resourceGame.fontConfigs["double_up_win"].outlineSize = 4;
		resourceGame.fontConfigs["double_up_label"] = TTFConfig(fontPath, 35);
		resourceGame.fontConfigs["double_up_label"].outlineSize = 4;
		//Main Game Res
		resourceGame.mainGame["bg"] = gamePrefix + "sprites/game-bg.png";
		resourceGame.mainGame["model"] = gamePrefix + "sprites/avatar.png";
		resourceGame.mainGame["total_winning"] = gamePrefix + "sprites/totalwinning.png";
		resourceGame.mainGame["info_page_1"] = gamePrefix + "sprites/info_1.png";
		resourceGame.mainGame["info_page_2"] = gamePrefix + "sprites/info_2.png";
		resourceGame.mainGame["info_page_3"] = gamePrefix + "sprites/info_3.png";
		resourceGame.mainGame["info_page_4"] = gamePrefix + "sprites/info_4.png";
		resourceGame.mainGame["info_page_5"] = gamePrefix + "sprites/info_5.png";
		resourceGame.mainGame["symbols_plist"] = gamePrefix + "sprites/symbols.plist";
		resourceGame.mainGame["but_spin_plist"] = gamePrefix + "sprites/but_spin.plist";

		resourceGame.mainGame["double_up_loading"] = gamePrefix + "sprites/doubleup-loading.png";
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
		resourceGame.lines["8"] = gamePrefix + "sprites/lines/line_8.png";
		resourceGame.lines["9"] = gamePrefix + "sprites/lines/line_9.png";
		resourceGame.lines["10"] = gamePrefix + "sprites/lines/line_10_13.png";
		resourceGame.lines["11"] = gamePrefix + "sprites/lines/line_11_12.png";
		resourceGame.lines["12"] = gamePrefix + "sprites/lines/line_11_12.png";
		resourceGame.lines["13"] = gamePrefix + "sprites/lines/line_10_13.png";
		resourceGame.lines["14"] = gamePrefix + "sprites/lines/line_7_14.png";
		resourceGame.lines["15"] = gamePrefix + "sprites/lines/line_6_15.png";
		//Double Up Res
		resourceGame.doubleUp["bg"] = gamePrefix + "sprites/doubleUp/bg.png";
		resourceGame.doubleUp["double_up_plist"] = gamePrefix + "sprites/doubleUp/double_up_plist.plist";
		//Bonus Res
		
		//Sound Res
		resourceGame.sound["main_game"] = gamePrefix + "sounds/Main-BGM.mp3";
		resourceGame.sound["free_spin"] = gamePrefix + "sounds/FreeSpins-BGM.mp3";
		resourceGame.sound["double_up"] = gamePrefix + "sounds/DoubleUp-BGM.mp3";

		resourceGame.sound["double_up_card_selected"] = gamePrefix + "sounds/Select-Card.mp3";
		resourceGame.sound["double_up_win"] = gamePrefix + "sounds/Player-Win.mp3";
		resourceGame.sound["double_up_lose"] = gamePrefix + "sounds/Player-Lose.mp3";

		resourceGame.sound["spin"] = gamePrefix + "sounds/Spin.mp3";
		resourceGame.sound["reel_stop"] = gamePrefix + "sounds/Reels_stop.mp3";
		resourceGame.sound["scatter_stop"] = gamePrefix + "sounds/Scatter_Stop.mp3";

		resourceGame.sound["symbol_0"] = gamePrefix + "sounds/Symbol_0.mp3";
		resourceGame.sound["symbol_1"] = gamePrefix + "sounds/Symbol_1_2_3.mp3";
		resourceGame.sound["symbol_2"] = gamePrefix + "sounds/symbol_1_2_3.mp3";
		resourceGame.sound["symbol_3"] = gamePrefix + "sounds/symbol_1_2_3.mp3";
		resourceGame.sound["symbol_4"] = gamePrefix + "sounds/Symbol_4_5.mp3";
		resourceGame.sound["symbol_5"] = gamePrefix + "sounds/Symbol_4_5.mp3";
		resourceGame.sound["symbol_6"] = gamePrefix + "sounds/Symbol_6_7.mp3";
		resourceGame.sound["symbol_7"] = gamePrefix + "sounds/Symbol_6_7.mp3";
		resourceGame.sound["symbol_8"] = gamePrefix + "sounds/Symbol_8.mp3";
		resourceGame.sound["symbol_9"] = gamePrefix + "sounds/Symbol_9_10.mp3";
		resourceGame.sound["symbol_10"] = gamePrefix + "sounds/Symbol_9_10.mp3";
		resourceGame.sound["symbol_11"] = gamePrefix + "sounds/Symbol_11.mp3";
		resourceGame.sound["symbol_12"] = gamePrefix + "sounds/Symbol_12.mp3";

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

	void CMainBO::gotoGame()
	{
		if (this->bAllResourcesLoaded && this->bFinishAPI) {
			this->oGame = new CGameBO(this);
			CMainBase::gotoGame();
		}
	}

	void CMainBO::initLastBonusInfo(tinyxml2::XMLElement* bonusXML)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_DOUBLE_UP:
		{
			this->oBonusToRestore->finish = 0;
			this->oBonusToRestore->history.clear();

			auto data = bonusXML->FirstChildElement("data");

			this->oBonusToRestore->win = atof(data->Attribute("gamewin"));

			int iCurStep = 0;

			if (data->FirstChildElement("step")) {
				iCurStep = atoi(data->FirstChildElement("step")->GetText());
			}
			auto wheels = data->FirstChildElement("wheels");
			if (iCurStep == 1) {
				this->oBonusToRestore->win = wheels->DoubleAttribute("bank");

				std::vector<ObjectBonus> aInfo;
				ObjectAdditionInfo* card = nullptr;

				this->oBonusToRestore->finish = atoi(wheels->Attribute("finish"));

				auto element = wheels->ToElement();
				if (element) {
					double iBet = element->DoubleAttribute("bet");
					double iBank = element->DoubleAttribute("bank");
					int iSelect = element->IntAttribute("sel");

					std::string name;
					if (iSelect == 1)
						name = "half";
					else if (iSelect == 2)
						name = "double";

					double iWinPot = element->DoubleAttribute(name.c_str());

					aInfo.push_back(ObjectBonus(iSelect, iBank, iBet, iWinPot, 0));
					auto cardElement = wheels->FirstChildElement("item")->ToElement();
					if (cardElement) {
						card = new ObjectCardDoubleUpBO(
							cardElement->IntAttribute("id"),
							cardElement->IntAttribute("suit"),
							atoi(cardElement->GetText())
							);
					}
				}
				this->oBonusToRestore->history = aInfo;
				this->oBonusToRestore->oInfo = card;
			}

			break;
		}
		case BONUS_TYPE::BONUS_FREESPIN:
		{
			if (this->oBonusToRestore->bonus_step > 0) {
				this->oBonusToRestore->counter = atoi(bonusXML->Attribute("counter"));
				//Check for some game doesn't have multy in free spin
				auto multy = bonusXML->Attribute("mp");
				if (multy != NULL) {
					this->oBonusToRestore->multiplier = atoi(bonusXML->Attribute("mp"));
				}
			}
			else {
				this->oBonusToRestore->counter = -1;
			}
			break;
		}
		}
	}

	void CMainBO::onBonusReceived(tinyxml2::XMLDocument * oXmlDoc)
	{
		switch (this->iCurBonus) {
		case BONUS_TYPE::BONUS_DOUBLE_UP:
			this->onDoubleUpReceive(oXmlDoc);
			break;
		case BONUS_TYPE::BONUS_FREESPIN:
			this->onBonusFreeSpinWithRetriggerReceived(oXmlDoc);
			break;
		}
	}
	void CMainBO::onDoubleUpReceive(tinyxml2::XMLDocument * oXmlDoc)
	{
		auto iStep = this->oGame->getStepBonus();

		auto doubleUpXML = oXmlDoc->FirstChildElement("bonus");

		this->iCredit = atof(doubleUpXML->FirstChildElement("balance")->FirstChild()->Value());
		double iTotWin = 0;

		auto dataXML = doubleUpXML->FirstChildElement("data");

		if (iStep == 0) {
			iTotWin = atof(dataXML->Attribute("gamewin"));
			this->oGame->onDoubleUpStep0Received(iTotWin);
		}
		else if (iStep == 1) {
			std::vector<ObjectBonus> aInfo;
			ObjectCardDoubleUpBO card_dealer;

			auto iFinish = atoi(dataXML->FirstChildElement("wheels")->Attribute("finish"));
			if (!iFinish) {

				auto element = dataXML->FirstChildElement("wheels")->ToElement();
				if (element) {
					double iBet = element->DoubleAttribute("bet");
					double iBank = element->DoubleAttribute("bank");
					int iSelect = element->IntAttribute("sel");

					std::string name;
					if (iSelect == 1)
						name = "half";
					else if (iSelect == 2)
						name = "double";

					double iWinPot = element->DoubleAttribute(name.c_str());

					aInfo.push_back(ObjectBonus(iSelect, iBank, iBet, iWinPot, 0));
					auto cardElement = dataXML->FirstChildElement("wheels")->FirstChildElement("item")->ToElement();
					if (cardElement) {
						card_dealer = ObjectCardDoubleUpBO(
							cardElement->IntAttribute("id"),
							cardElement->IntAttribute("suit"),
							atoi(cardElement->GetText())
							);
					}
				}
			}
			((CGameBO*)this->oGame)->onDoubleUpStep1Received(iFinish, aInfo, card_dealer);
		}
		else {
			auto iFinish = atoi(dataXML->FirstChildElement("wheels")->Attribute("finish"));

			std::vector<ObjectCardDoubleUpBO> aCard;
			double iWin = 0;
			double iBank = 0;
			int iSelect = 0;

			auto element = dataXML->FirstChildElement("wheels")->ToElement();
			if (element) {
				iSelect = element->IntAttribute("selected");
				iBank = element->DoubleAttribute("bank");
				iWin = element->DoubleAttribute("win");
			}

			for (auto i = dataXML->FirstChildElement("wheels")->FirstChildElement("item");
			i != NULL; i = i->NextSiblingElement()) {
				if (i) {
					aCard.push_back(ObjectCardDoubleUpBO(
						i->IntAttribute("id"),
						i->IntAttribute("suit"),
						atoi(i->GetText())
						));
				}
			}
			((CGameBO*)this->oGame)->onDoubleUpStep2Received(iFinish, aCard, iBank, iSelect, iWin);
		}
	}
}