#include "CMainBase.h"
#include "CGameBase.h"
#include "../utils/GameUtils.h"
#include "Manager/FileManager/DownloadFileManager.h"

USING_NS_CC;
namespace GameSlot {
	// on "init" you need to initialize your instance
	bool CMainBase::init()
	{
		/*auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

		this->setScale(visibleSize.width / CSettings::CANVAS_WIDTH);*/
		//this->setAnchorPoint(Vec2::ZERO);
		//////////////////////////////
		// 1. super init first
		if (!Node::init()) return false;

		this->initSettings();
		this->initMapStringValue();

		Manager4Network::getInstance()->setGame(this);
		if (GameConstant::getInstance()->getAccount().isFunMode) {
			Manager4Network::getInstance()->callFunPlay();
		}
		else {
			Manager4Network::getInstance()->callRealPlay();
		}

		this->initResources();
		Manager4Sound::getInstance()->setGame(this, GameConstant::getInstance()->getResources().sound);

		vector<string> loader;
		for (auto res : GameConstant::getInstance()->getResources().loader) {
			loader.push_back(res.second);
		}

		this->oLoadingUI = new CLoadingUI(this);
		this->addChild(this->oLoadingUI, ORDER_LOADING);

		CLoader::getInstance()->startLoadingResources(
			loader,
			[this]() {
			this->oLoadingUI->init();
			this->oLoadingUI->preload(aResources, CC_CALLBACK_0(CMainBase::allResourcesLoaded, this));
			CLoader::getInstance()->startLoadingResources(
				this->aResourcesExtend,
				[this]() {
				this->bReadyToSpin = true;
				if (this->bGotoGame) {
					this->oGame->getReel()->initLines();
				}
			}, nullptr);

			this->scheduleUpdate();
		}, nullptr);

		return true;
	}

	void CMainBase::initMapStringValue()
	{
		if (this->mapStringValues.size() > 0) {
			return;
		}
		this->mapStringValues["multiply"] = AttributeName::multiply;
		this->mapStringValues["multiplier"] = AttributeName::multiplier;
		this->mapStringValues["wheel"] = AttributeName::wheel;
		this->mapStringValues["lottoball"] = AttributeName::lottoball;
		this->mapStringValues["tid"] = AttributeName::tid;
		this->mapStringValues["val"] = AttributeName::val;
		this->mapStringValues["type"] = AttributeName::type;
		this->mapStringValues["bet"] = AttributeName::bet;
		this->mapStringValues["lines"] = AttributeName::lines;
		this->mapStringValues["totalbet"] = AttributeName::totalbet;
		this->mapStringValues["wild"] = AttributeName::wild;
		this->mapStringValues["scatter"] = AttributeName::scatter;
		this->mapStringValues["ts"] = AttributeName::ts;
		this->mapStringValues["width"] = AttributeName::width;
		this->mapStringValues["height"] = AttributeName::height;
		this->mapStringValues["win"] = AttributeName::win;
		this->mapStringValues["numberOfLuckySymbolWin"] = AttributeName::numberOfLuckySymbolWin;
		this->mapStringValues["luckySymbolPosition"] = AttributeName::luckySymbolPosition;
		this->mapStringValues["remainingSpin"] = AttributeName::remainingSpin;
		this->mapStringValues["remainingTime"] = AttributeName::remainingTime;
	}

	void CMainBase::initSettings()
	{
		CSettings::WIDTH_REEL = (CSettings::SYMBOL_WIDTH + CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS) * (CSettings::NUM_REELS) - CSettings::SPACE_WIDTH_BETWEEN_SYMBOLS;
		CSettings::HEIGHT_REEL = (CSettings::SYMBOL_HEIGHT + CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS) * (CSettings::NUM_ROWS) - CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS;

		CSettings::REEL_START_Y = CSettings::REEL_OFFSET_Y + CSettings::HEIGHT_REEL + CSettings::SPACE_HEIGHT_BETWEEN_SYMBOLS;
		CSettings::REEL_ARRIVAL_Y = CSettings::REEL_OFFSET_Y - CSettings::HEIGHT_REEL;
	}

	void CMainBase::initResources()
	{
		this->aResources.clear();
		this->aResourcesExtend.clear();
		//Add Resources mega win - big win
		this->aResourcesExtend.push_back("popup/mega-big-win/win_effect.plist");
		this->aResourcesExtend.push_back("popup/mega-big-win/effect_win_font.png");
		this->aResourcesExtend.push_back("sound/megaBigWin.mp3");
	}

	void CMainBase::allResourcesLoaded()
	{
		this->bAllResourcesLoaded = true;
		this->gotoGame();
	}

	void CMainBase::gotoGame()
	{
		this->bGotoGame = true;
		if (this->oGame && this->oGame->init()) {
			this->addChild(this->oGame, ORDER_GAME);

			this->oGame->checkLastState();
			//if we go to bonus or double up, they will call hideLoading themself
			if (this->oGame->getCurrentType() == GAME_TYPE::MAIN_GAME ||
				this->oGame->getCurrentType() == GAME_TYPE::FREE_SPIN) {
				this->oLoadingUI->hideLoading([this]() {
					this->oScene->onBeginGame();
				});
			}
		}
	}

	void CMainBase::update(float dt)
	{
		if (this->oGame) {
			this->oGame->update(dt);
		}
	}

	std::string CMainBase::getSlotGameLocationPrefix(){
#if IS_DEBUG
		/*test: play game with local png*/
		//return "slotgame/" + DownloadFileManager::getInstance()->getGameNameFromID(getGameOrderID()) + "/";
#endif
		std::string filePath = DownloadFileManager::getInstance()->getGameSlotDirectoryGame(getGameOrderID());
		return filePath;
	}

	void CMainBase::onGetRealPlayKeyReceived(const string& szKey)
	{
		this->bRealPlay = true;
		this->szRealPlayKey = szKey;
		Manager4Network::getInstance()->callGetBalance(this->szRealPlayKey);
	}

	void CMainBase::onBalanceReceived(float szCredit)
	{
		this->iCredit = szCredit;

		if (!this->szRealPlayKey.empty()) {
			Manager4Network::getInstance()->callGetBet(this->szRealPlayKey);
		}
		else {
			Manager4Network::getInstance()->callGetBet(this->szFunPlayKey);
		}
	}

	void CMainBase::onBetsReceived(tinyxml2::XMLDocument* oXmlDoc)
	{
		string szVal = "";
		string szWheel = "";
		string szLottoBall = "";
		string szTid = "";
		auto betXML = oXmlDoc->FirstChildElement("bets");

		for (auto i = betXML->FirstAttribute();
			i != NULL; i = i->Next()) {
			switch (this->mapStringValues[i->Name()]) {
			case AttributeName::multiply:
			{
				this->iMultiply = i->IntValue();
				break;
			}
			case AttributeName::wheel:
			{
				szWheel = i->Value();
				break;
			}
			case AttributeName::lottoball:
			{
				szLottoBall = i->Value();
				break;
			}
			case AttributeName::tid:
			{
				szTid = i->Value();
				break;
			}
			case AttributeName::val:
			{
				szVal = i->Value();
				break;
			}
			}
		}
		//Set first bet of Game to be the current Bet
		auto aVals = GameUtils::splitString(szVal, ',');
		this->iBet = stof(aVals[0]);

		//Get array bet of Game
		for (int i = 0; i < aVals.size(); i++) {
			this->aBets.push_back(stoi(aVals[i]) * this->iMultiply);
		}

		this->iLines = CSettings::NUM_PAYLINES;

		this->iTotBet = this->iBet * this->iLines;
		//This will check if User still on Bonus last time, if so we will set the bet from last game to be the current bet
		auto bonus = betXML->FirstChildElement("bonus");
		if (bonus && bonus->FirstChildElement("last") &&
			!bonus->FirstChildElement("last")->NoChildren()) {
			if (betXML->Attribute("bet")) {
				this->iBet = atof(betXML->Attribute("bet"));
			}
			if (betXML->Attribute("lines")) {
				this->iLines = atof(betXML->Attribute("lines"));
			}

			if (this->oGame && 
				this->oGame->getInterface() && 
				this->oGame->getInterface()->getFooter()) {
				this->oGame->getInterface()->getFooter()->reloadBet(this->iBet);
				this->oGame->getInterface()->getFooter()->reloadPayline(this->iLines);
			}
		}

		//Get the starting wheel
		if (!szWheel.empty()) {
			this->aStartingWheel = GameUtils::splitString(szWheel, ',');
		}
		//This is virtual function -> should be override to check last bonus that User hasn't finished yet
		this->onCheckLastBonus(oXmlDoc);

		//this._bFinishAPI == false which means this is called when loading game
		if (!this->bFinishAPI) {
			this->bFinishAPI = true;
			this->gotoGame();
		}
		else {
			//this.oGame.refreshBet();
		}
	}

	void CMainBase::onSpinReceived(tinyxml2::XMLDocument* oXmlDoc)
	{
		string szWild = "";
		string szScatter = "";

		auto spinXML = oXmlDoc->FirstChildElement("spin");

		for (auto i = spinXML->FirstAttribute();
			i != NULL; i = i->Next()) {
			switch (this->mapStringValues[i->Name()]) {
			case AttributeName::type:
			{
				break;
			}
			case AttributeName::bet:
			{
				this->iBet = i->FloatValue();
				break;
			}
			case AttributeName::lines:
			{
				this->iLines = i->IntValue();
				break;
			}
			case AttributeName::tid:
			{
				break;
			}
			case AttributeName::multiplier:
			{
				this->iMultiply = i->IntValue();
				break;
			}
			case AttributeName::totalbet:
			{
				this->iTotBet = i->DoubleValue();
				break;
			}
			case AttributeName::wild:
			{
				szWild = i->Value();
				break;
			}
			case AttributeName::scatter:
			{
				szScatter = i->Value();
				break;
			}
			case AttributeName::ts:
			{
				// this.iTimeStamp = oXmlDoc.getElementsByTagName('spin')[0].attributes[i].value;
				break;
			}

			}
		}
		//Get the current win for this spin
		this->iCurWin = atof(spinXML->FirstChildElement("win")->FirstChild()->Value());
		//Get User's current balance (credit)
		this->iCredit = atof(spinXML->FirstChildElement("balance")->FirstChild()->Value());

		//GET WHEEL INFO
		//type='normal' width='5' height='3' val='10,6,0,6,2,8,5,3,4,3,6,4,6,7,1'/>
		int iWidth, iHeight;
		string szWheel;
		for (auto i = spinXML->FirstChildElement("wheels")->FirstAttribute();
			i != NULL; i = i->Next()) {
			switch (this->mapStringValues[i->Name()]) {
			case AttributeName::type:
			{
				break;
			}
			case AttributeName::width:
			{
				iWidth = i->IntValue();
				break;
			}
			case AttributeName::height:
			{
				iHeight = i->IntValue();
				break;
			}
			case AttributeName::val:
			{
				szWheel = i->Value();
				break;
			}
			}
		}


		//If szWheel is null which means we dont received any wheel spin info from server -> generate loosing wheel
		if (szWheel.empty()) {
			//this->oGame->generateLosingWheel();
			return;
		}
		int** aWheels = new int*[iHeight];
		vector<string> aTmp = GameUtils::splitString(szWheel, ',');
		for (int i = 0; i < iHeight; i++) {
			aWheels[i] = new int[iWidth];
			for (int j = 0; j < iWidth; j++) {
				aWheels[i][j] = std::stoi(aTmp[(j * iHeight) + i]);
			}
		}
#pragma region Magic Item
		int** aLuckySymbolWheels = new int*[iHeight];
		for (int i = 0; i < iHeight; i++) {
			aLuckySymbolWheels[i] = new int[iWidth];
			for (int j = 0; j < iWidth; j++) {
				aLuckySymbolWheels[i][j] = 0;
			}
		}

		int typeMagicItem = LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DEFAULT;
		double winMagicItem = 0;
		int numberOfLuckySymbolWin = 0;
		std::string luckySymbolPos = "";
		int remainingSpin = 0;
		long remainingTime = 0;
		if (spinXML->FirstChildElement("magicitem"))
		{
			for (auto i = spinXML->FirstChildElement("magicitem")->FirstAttribute();
				i != NULL; i = i->Next()) {
				switch (this->mapStringValues[i->Name()]) {
				case AttributeName::type:
				{
					typeMagicItem = i->IntValue();
					break;
				}
				case AttributeName::win:
				{
					winMagicItem = atof(i->Value());
					break;
				}
				case AttributeName::numberOfLuckySymbolWin:
				{
					numberOfLuckySymbolWin = i->IntValue();
					break;
				}
				case AttributeName::luckySymbolPosition:
				{
					luckySymbolPos = i->Value();
					break;
				}
				case AttributeName::remainingSpin:
				{
					remainingSpin = i->IntValue();
					break;
				}
				case AttributeName::remainingTime:
				{
					remainingTime = (long)atof(i->Value());
					break;
				}
				}
			}

			UtilFunction::handleMagicItemAfterSpinRecieve(
				typeMagicItem,
				winMagicItem,
				numberOfLuckySymbolWin,
				luckySymbolPos,
				remainingSpin,
				remainingTime,
				aLuckySymbolWheels
			);
		}
		ObjectMagicItemReceiveAfterSpin *objectMagicItem = new ObjectMagicItemReceiveAfterSpin();
		objectMagicItem->magicItemType = typeMagicItem;
		objectMagicItem->aLuckySymbolWheels = aLuckySymbolWheels;
#pragma endregion

		vector<ObjectWinPosition> aWinPosition;
		//Get Win Info (Line? Win? Multiple? Pos?) of Normal Spin
		if (!spinXML->FirstChildElement("winposition")->NoChildren()) {
			for (auto i = spinXML->FirstChildElement("winposition")->FirstChild();
				i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					aWinPosition.push_back(
						ObjectWinPosition(
							element->IntAttribute("line"),
							element->DoubleAttribute("win"),
							element->IntAttribute("mul"),
							element->GetText(),
							false)
					);
				}
			}
		}
		//Table win currently is deprecated
		vector<ObjectTableWin> aTableWin;
		for (auto i = spinXML->FirstChildElement("tablewin")->FirstChild();
			i != NULL;
			i = i->NextSibling()) {
			auto element = i->ToElement();
			if (element) {
				aTableWin.push_back(
					ObjectTableWin(
						element->IntAttribute("card"),
						element->IntAttribute("count"),
						element->IntAttribute("wild")
					));
				//trace("aTableWin["+k+"]: card"+aTableWin[k].card+" #count:"+aTableWin[k].count+" #wild: "+aTableWin[k].wild);
			}
		}
		//This will get the bonus ID that User won and Total Free Spins (if exist)
		this->iCurBonus = -1;
		auto countFreeSpin = 0;
		if (spinXML->FirstChildElement("bonus")->FirstAttribute() != NULL) {
			this->iCurBonus = atoi(spinXML->FirstChildElement("bonus")->Attribute("id"));
			this->szBonusKey = spinXML->FirstChildElement("bonus")->FirstChild()->Value();
			if (this->iCurBonus == 2 &&
				spinXML->FirstChildElement("bonus")->Attribute("count") != NULL) {
				countFreeSpin = atoi(spinXML->FirstChildElement("bonus")->Attribute("count"));
			}
		}

		
		//Get Win Info (Line? Win? Multiple? Pos?) of Bonus
		for (auto i = spinXML->FirstChildElement("bonusposition")->FirstChild();
			i != NULL; i = i->NextSibling()) {
			auto element = i->ToElement();
			if (element) {
				auto winPos = ObjectWinPosition(
					element->IntAttribute("line"),
					element->DoubleAttribute("win"),
					element->IntAttribute("mul"),
					element->GetText(),
					this->iCurBonus > 1);

				for (auto j = 0; j < aWinPosition.size(); ++j) {
					if (aWinPosition[j].id == winPos.id) {
						aWinPosition.erase(aWinPosition.begin() + j);
						break;
					}
				}
				aWinPosition.push_back(winPos);
			}
		}

		this->oGame->onSpinReceived(aWheels, objectMagicItem, aWinPosition, aTableWin, this->iCurBonus, countFreeSpin);
	}


	void CMainBase::onBonusReceived(tinyxml2::XMLDocument* oXmlDoc)
	{
	}

	void CMainBase::onCheckLastBonus(tinyxml2::XMLDocument* oXmlDoc)
	{
		auto betXML = oXmlDoc->FirstChildElement("bets");
		//CHECK IF THERE IS AN OPEN BONUS
		if (betXML->FirstChildElement("bonus") != NULL) {
			if (!this->oBonusToRestore) {
				this->oBonusToRestore = new ObjectBonusRestore();
			}
			this->oBonusToRestore->bonus_id = this->iCurBonus = atoi(betXML->FirstChildElement("bonus")->Attribute("id"));
			auto bonusStep = betXML->FirstChildElement("bonus")->Attribute("step");
			if (bonusStep == NULL) {
				this->removeBonusHistory();
			}
			else {
				this->oBonusToRestore->bonus_step = atoi(bonusStep);
				this->szBonusKey = betXML->FirstChildElement("bonus")->Attribute("key");

				auto lastXML = betXML->FirstChildElement("bonus")->FirstChildElement("last");
				//Check if we has some last bonus data, if we dont (which means bonus step = 0) -> dont need to init last bonus info
				if (lastXML != NULL) {
					auto bonusXML = lastXML->FirstChildElement("bonus");
					if (bonusXML != NULL) {
						this->initLastBonusInfo(bonusXML);
					}
				}

			}
		}
	}

	void CMainBase::initLastBonusInfo(tinyxml2::XMLElement* bonusXML) {
	}

	void CMainBase::onDoubleUpReceive(tinyxml2::XMLDocument* oXmlDoc)
	{
		auto doubleUpXML = oXmlDoc->FirstChildElement("bonus");

		auto iStep = this->oGame->getStepBonus();

		this->iCredit = atof(doubleUpXML->FirstChildElement("balance")->FirstChild()->Value());
		double iTotWin = 0;

		auto dataXML = doubleUpXML->FirstChildElement("data");

		if (iStep == 0) {
			iTotWin = atof(dataXML->Attribute("gamewin"));
			this->oGame->onDoubleUpStep0Received(iTotWin);
		}
		else {
			auto iFinish = atoi(dataXML->FirstChildElement("wheels")->Attribute("finish"));
			auto iResult = 0;
			iTotWin = 0;

			for (auto i = dataXML->FirstChildElement("history")->FirstChild();
				i != NULL; i = i->NextSibling()) {
				auto element = i->ToElement();
				if (element) {
					iResult = element->IntAttribute("result");
					iTotWin = element->DoubleAttribute("value");
				}
			}

			if (iResult == 0 && iTotWin == 0) {
				iTotWin = atof(dataXML->Attribute("gamewin"));
			}
			this->oGame->onDoubleUpStep1Received(iFinish, iResult, iTotWin);
		}
	}

	void CMainBase::onBonusFreeSpinWithRetriggerReceived(tinyxml2::XMLDocument* oXmlDoc)
	{
		auto bonusXML = oXmlDoc->FirstChildElement("bonus");

		this->iCredit = atof(bonusXML->FirstChildElement("balance")->FirstChild()->Value());
		//<bonus type='fs' tid='481373' counter='3' mp='1' gamewin='0.00' all='4' ts='1429198225'>
		auto iRemainingFreeSpin = atoi(bonusXML->Attribute("counter"));
		auto iMultyFS = atoi(bonusXML->Attribute("mp"));

		this->iCurWin = atof(bonusXML->FirstChildElement("win")->FirstChild()->Value());

		auto dataXML = bonusXML->FirstChildElement("data");
		auto spinXML = dataXML->FirstChildElement("spin");

		vector<ObjectWinPosition> aWinPosition;
		for (auto i = spinXML->FirstChildElement("winposition")->FirstChild();
			i != NULL; i = i->NextSibling()) {
			auto element = i->ToElement();
			if (element) {
				aWinPosition.push_back(
					ObjectWinPosition(
						element->IntAttribute("line"),
						element->DoubleAttribute("win"),
						element->IntAttribute("mul"),
						element->GetText(),
						false
						)
					);
			}
		}

		std::string szRow = spinXML->FirstChildElement("wheels")->Attribute("val");
		auto iHeight = atoi(spinXML->FirstChildElement("wheels")->Attribute("height"));
		auto iWidth = atoi(spinXML->FirstChildElement("wheels")->Attribute("width"));

		auto aWheels = new int*[iHeight];
		vector<string> aTmp = GameUtils::splitString(szRow, ',');
		for (int i = 0; i < iHeight; i++) {
			aWheels[i] = new int[iWidth];
			for (int j = 0; j < iWidth; j++) {
				aWheels[i][j] = stoi(aTmp[(j * iHeight) + i]);
			}
		}

		vector<ObjectTableWin> aTableWin;
		for (auto i = spinXML->FirstChildElement("tablewin")->FirstChild();
			i != NULL;
			i = i->NextSibling()) {
			auto element = i->ToElement();
			if (element) {
				aTableWin.push_back(
					ObjectTableWin(
						element->IntAttribute("card"),
						element->IntAttribute("count"),
						element->IntAttribute("wild")
					));
				//trace("aTableWin["+k+"]: card"+aTableWin[k].card+" #count:"+aTableWin[k].count+" #wild: "+aTableWin[k].wild);
			}
		}

		auto iTotWin = dataXML->FirstAttribute()->DoubleValue();

		this->oGame->onBonusFreeSpinStepReceived(iRemainingFreeSpin, iMultyFS, aWinPosition, aWheels, aTableWin, iTotWin);
	}

	int CMainBase::getGameOrderID() {
		return 0;
	}

	void CMainBase::onExit()
	{
		this->unscheduleUpdate();

		Node::onExit();

		CLoader::getInstance()->stopAll();

		auto resources = GameConstant::getInstance()->getResources();

		for (auto res : resources.mainGame) {
			UtilFunction::releaseCache(res.second);
		}
		for (auto res : resources.symbolAnims) {
			UtilFunction::releaseCache(res.second);
		}
		for (auto res : resources.lines) {
			UtilFunction::releaseCache(res.second);
		}
		for (auto res : resources.doubleUp) {
			UtilFunction::releaseCache(res.second);
		}
		for (auto res : resources.bonus1) {
			UtilFunction::releaseCache(res.second);
		}
		for (auto res : resources.bonus2) {
			UtilFunction::releaseCache(res.second);
		}
		for (auto res : resources.loader) {
			UtilFunction::releaseCache(res.second);
		}

		this->removeBonusHistory();
	}
}