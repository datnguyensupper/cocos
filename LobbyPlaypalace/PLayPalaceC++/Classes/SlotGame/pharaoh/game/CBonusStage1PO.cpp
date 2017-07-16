#include "CBonusStage1PO.h"
#include "../game/CGamePO.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CBonusStage1PO::CBonusStage1PO(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iBonusType = BONUS_TYPE::BONUS_TYPE_3;

		for (auto res : GameConstant::getInstance()->getResources().bonus1) {
			this->aResources.push_back(res.second);
		}

	}
	CBonusStage1PO::~CBonusStage1PO()
	{
	}
	bool CBonusStage1PO::init()
	{
		if (!CBonusBase::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		auto bg = Helper4Sprite::createOptimizeSprite(res.bonus1["bg"]);
		GameUtils::centerNode(bg);
		this->addChild(bg);

		this->oLeftDoor = Sprite::createWithSpriteFrameName("bonus_1_door-left");
		this->oLeftDoor->setPosition(700, CSettings::CANVAS_HEIGHT / 2 - 62);
		this->addChild(this->oLeftDoor);

		this->oRightDoor = Sprite::createWithSpriteFrameName("bonus_1_door-right");
		this->oRightDoor->setPosition(this->oLeftDoor->getPosition() + Vec2(this->oLeftDoor->getContentSize().width - 25, 0));
		this->addChild(this->oRightDoor);

		auto oDoorBG = Sprite::createWithSpriteFrameName("bonus_1_bg_door");
		oDoorBG->setPosition(CSettings::CANVAS_WIDTH / 2, -33);
		oDoorBG->setAnchorPoint(Vec2(0.5f, 0));
		this->addChild(oDoorBG);

		this->aBtn.resize(8);

		for (int i = 0, size = this->aBtn.size(); i < size; ++i) {
			this->createDoorButton(i);
		}

		this->aHeaderSymbols.resize(3);
		for (int i = 1; i < 4; ++i) {
			auto oSymbol = Sprite::createWithSpriteFrameName("bonus_1_symbol_1");
			oSymbol->setVisible(false);
			oSymbol->setScale(0.7f);
			this->addChild(oSymbol);

			this->aHeaderSymbols[i - 1] = oSymbol;
		}
		this->aHeaderSymbols[0]->setPosition(CSettings::CANVAS_WIDTH / 2 - 212, 750);
		this->aHeaderSymbols[1]->setPosition(CSettings::CANVAS_WIDTH / 2, 750);
		this->aHeaderSymbols[2]->setPosition(CSettings::CANVAS_WIDTH / 2 + 200, 750);

		this->oRule = Sprite::createWithSpriteFrameName("bonus_1_instruction");
		this->oRule->setPosition(CSettings::CANVAS_WIDTH / 2, 85);
		this->addChild(this->oRule);

		return true;
	}

	void CBonusStage1PO::onBonusEntered()
	{
		CBonusBase::onBonusEntered();
		this->bWinBonusStage2 = true;
		this->iCurHeaderSymbol = 0;
	}

	void CBonusStage1PO::createDoorButton(int index)
	{
		auto parent = Node::create();
		parent->setCascadeOpacityEnabled(true);

		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			"bonus_1_symbol_1",
			nullptr,
			[this, index](){
			this->btnGamblingClicked(index + 1);
		}
		);
		oBtn->setPosition(
			Vec2(
				855 + (index % 2) * 210 + (index % 2 == 0 ? -1 : 1)* floor(index / 2.0f) * 5,
				675 - floor(index / 2.0f) * 143
			) * CSettings::SCALE_VALUE_TO_1920);
		oBtn->setOpacity(0);
		parent->addChild(oBtn);

		auto oText = Label::createWithTTF(GameConstant::getInstance()->getResources().fontConfigs["bonus_3"], "0");
		oText->setPosition(oBtn->getPosition() - Vec2(0,55));
		oText->setVisible(false);
		oText->setTextColor(Color4B(232, 201, 46, 255));
		oText->enableOutline(Color4B(133, 71, 3, 255));
		parent->addChild(oText);

		this->addChild(parent);

		this->aBtn[index] = oBtn;
	}

	void CBonusStage1PO::showSymbolBtnInfo(int index, int symbolPrize, int symbolWin, bool isWin)
	{
		auto oBtn = this->aBtn[index];
		auto oText = (Label*)oBtn->getParent()->getChildren().at(1);
		oBtn->setSpriteFrame("bonus_1_symbol_" + ToString(symbolPrize));
		oBtn->setOpacity(255);
		oText->setString(UtilFunction::FormatWithCommas(symbolWin));
		oText->setVisible(true);
		if (!isWin) {
			oBtn->setOpacity(175);
			oText->setTextColor(Color4B(153, 153, 153, 255));
			oText->enableOutline(Color4B::BLACK);
		}
	}

	void CBonusStage1PO::showResult(bool bFinish, const std::vector<ObjectBonus>& aWheels, int iIndex, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, aWheels, iIndex, bFromRestore);
		
		auto iSelect = aWheels[iIndex].select - 1;
		if (iSelect < 0) {
			iSelect = aWheels[2].select - 1;
			iIndex = 2;
		}
		auto iPrize = aWheels[iIndex].type;
		auto iWin = aWheels[iIndex].win;
		//if this prize is greater than 3 then we cant open the door and go to bonus game 2
		if (iPrize > 3) {
			this->bWinBonusStage2 = false;
		}

		this->oRule->setVisible(false);
		//if this prize is smaller than 3 then we show the symbol on top of the door
		if (iPrize <= 3) {
			auto oSymbol = this->aHeaderSymbols[this->iCurHeaderSymbol++];
			oSymbol->setSpriteFrame("bonus_1_symbol_" + ToString(iPrize));
			oSymbol->setVisible(true);
		}
		//show this butotn's score
		this->showSymbolBtnInfo(iSelect, iPrize, iWin, true);

		this->aBtn[iSelect]->setTouchEnabled(false);

		if (bFinish) {
			this->disableAllBtn();

			//Show others symbol, play open door animation and then exit this bonus
			std::vector<ObjectBonus> fakeWheel = aWheels;
			if (aWheels.size() < 4) {
				fakeWheel = createFakeWheel(aWheels);
			}
			for (int i = 3, size = this->aBtn.size(); i < size; ++i) {
				auto item = fakeWheel[i];
				auto index = -item.select - 1;
				this->showSymbolBtnInfo(index, item.type, item.win, false);
			}
			fakeWheel.clear();

			if (this->bWinBonusStage2) {
				this->readyForBonusStage2(aWheels);
			}
			else {
				//afakeWheel =  
				for (auto wheel : aWheels) {
					this->iTotWin += wheel.win;
				}
				this->scheduleOnce(schedule_selector(CBonusStage1PO::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
			}
		}
	}


	std::vector<ObjectBonus> CBonusStage1PO::createFakeWheel(std::vector<ObjectBonus> awheel) {

		for (int i = 0; i < awheel.size(); i++) {
			ObjectBonus objectBonus = awheel[i];
			if (objectBonus.select > 0) {
				objectBonus.select = -objectBonus.select;
				awheel[i] = objectBonus;
			}
		}
		std::vector<ObjectBonus> aFakeWheel;
		ObjectBonus objectBonus;

		objectBonus.select = awheel[0].select;
		objectBonus.win = 600;
		objectBonus.type = awheel[0].type;
		aFakeWheel.push_back(objectBonus);

		objectBonus.select = awheel[1].select;
		objectBonus.win = 800;
		objectBonus.type = awheel[1].type;
		aFakeWheel.push_back(objectBonus);

		objectBonus.select = awheel[2].select;
		objectBonus.win = 800;
		objectBonus.type = awheel[2].type;
		aFakeWheel.push_back(objectBonus);

		objectBonus.select = -4;
		objectBonus.win = 3000;
		objectBonus.type = 4;
		aFakeWheel.push_back(objectBonus);

		objectBonus.select = -5;
		objectBonus.win = 1000;
		objectBonus.type = 5;
		aFakeWheel.push_back(objectBonus);

		objectBonus.select = -6;
		objectBonus.win = 1800;
		objectBonus.type = 6;
		aFakeWheel.push_back(objectBonus);

		objectBonus.select = -7;
		objectBonus.win = 3000;
		objectBonus.type = 7;
		aFakeWheel.push_back(objectBonus);

		objectBonus.select = -8;
		objectBonus.win = 1200;
		objectBonus.type = 8;
		aFakeWheel.push_back(objectBonus);

		for (int i = 3; i < aFakeWheel.size(); i++) {
			ObjectBonus objectBonus = aFakeWheel[i];
			for (int j = 0; j < 3; j++) {
				if (objectBonus.select == awheel[0].select) {
					objectBonus.select = -1;
				}else if (objectBonus.select == awheel[1].select) {
					objectBonus.select = -2;
				}else if (objectBonus.select == awheel[2].select) {
					objectBonus.select = -3;
				}

				if (objectBonus.type == awheel[0].type) {
					objectBonus.type = 1;
				}else if (objectBonus.type == awheel[1].type) {
					objectBonus.type = 2;
				}else if (objectBonus.type == awheel[2].type) {
					objectBonus.type = 3;
				}
			}
			aFakeWheel[i] = objectBonus;
		}

		return aFakeWheel;
	}

	void CBonusStage1PO::readyForBonusStage2(const std::vector<ObjectBonus>& aWheels)
	{
		
		for (int i = 0, size = this->aBtn.size(); i < size; ++i) {
			if (i == 0) {
				this->aBtn[i]->getParent()->runAction(Sequence::create(
					DelayTime::create(1.0f),
					FadeOut::create(3.0f),
					CallFunc::create([this]() {

					for (auto btn : this->aBtn) {
						btn->setVisible(false);
					}

					Manager4Sound::getInstance()->playEffect(GameConstant::getInstance()->getResources().sound["bonus_3_gate_open"]);

					this->oLeftDoor->runAction(Sequence::create(
						MoveTo::create(5.0f, Vec2(this->oLeftDoor->getPosition() - Vec2(180, 0))),
						DelayTime::create(1.0f),
						CallFunc::create([this]() {
						this->exitFromBonus();
					}), NULL));

					this->oRightDoor->runAction(MoveTo::create(5.0f, Vec2(this->oRightDoor->getPosition() + Vec2(180, 0))));

				}), NULL));
			}
			else {
				this->aBtn[i]->getParent()->runAction(Sequence::createWithTwoActions(
					DelayTime::create(1.0f),
					FadeOut::create(3.0f)));
			}
		}
	}

	void CBonusStage1PO::exitFromBonus()
	{
		this->oGame->setVisible(true);

		this->bGoToBonus = false;

		this->setVisible(false);

		((CGamePO*)this->oGame)->exitFromBonusStage1(this->iTotWin, this->bWinBonusStage2);

		this->resetBonus();
	}

	void CBonusStage1PO::resetBonus()
	{
		CBonusBase::resetBonus();
		this->oRule->setVisible(true);
		this->oLeftDoor->setPositionX(700);
		this->oRightDoor->setPositionX(this->oLeftDoor->getPositionX() + this->oLeftDoor->getContentSize().width - 25);
		for (auto btn : this->aBtn) {
			btn->setVisible(true);
			btn->setOpacity(0);
			btn->getParent()->setOpacity(255);
			auto oText = (Label*)btn->getParent()->getChildren().at(1);
			oText->setTextColor(Color4B(232, 201, 46, 255));
			oText->enableOutline(Color4B(133, 71, 3, 255));
			oText->setVisible(false);
		}

		for (auto headerSymbol : this->aHeaderSymbols) {
			headerSymbol->setVisible(false);
		}
	}
}
