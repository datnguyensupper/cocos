#include "CDoubleUpDB.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/constant/GameConstant.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CDoubleUpDB::CDoubleUpDB(CGameBase* oGame):CBonusBase(oGame)
	{
		this->iGameType = GAME_TYPE::DOUBLE_UP;
		this->iBonusType = BONUS_TYPE::BONUS_DOUBLE_UP;

		for (auto res : GameConstant::getInstance()->getResources().doubleUp) {
			this->aResources.push_back(res.second);
		}
	}
	CDoubleUpDB::~CDoubleUpDB()
	{

	}
	bool CDoubleUpDB::init()
	{
		if (!CBonusBase::init()) return false;

		auto res = GameConstant::getInstance()->getResources();

		auto oBg = Helper4Sprite::createOptimizeSprite(res.doubleUp["bg"]);
		GameUtils::centerNode(oBg);
		this->addChild(oBg);

		this->aBtn.resize(3);

		auto oFooter = Sprite::createWithSpriteFrameName("doubleup_bottom-bar");
		oFooter->setPosition(CSettings::CANVAS_WIDTH / 2, 115);
		this->addChild(oFooter);

		this->initAnimaton();

		createButton(0, "doubleup_btn_collect", Vec2(463, 249) * CSettings::SCALE_VALUE_TO_1920);
		createButton(1, "doubleup_btn_escape", Vec2(765, 115) * CSettings::SCALE_VALUE_TO_1920);
		createButton(2, "doubleup_btn_capture", Vec2(1119, 115) * CSettings::SCALE_VALUE_TO_1920);

		oCurrentWinBg = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("doubleup_bottom_bg_win_amount");
		oCurrentWinBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		auto capInsets = oCurrentWinBg->getCapInsets();
		capInsets.origin.x = capInsets.size.width / 2 - 2;
		capInsets.size.width = 4;
		oCurrentWinBg->setCapInsets(capInsets);
		oCurrentWinBgOriginalSize = oCurrentWinBg->getContentSize();
		this->addChild(oCurrentWinBg);

		this->oCurrentWinTxt = Label::createWithTTF(res.fontConfigs["double_up"], "0");
		this->oCurrentWinTxt->setPosition(this->aBtn[0]->getPosition() - Vec2(0, 50));
		this->oCurrentWinTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oCurrentWinTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oCurrentWinTxt);
		oCurrentWinBg->setPosition(this->oCurrentWinTxt->getPosition() - Vec2(5, 2));


		oPotentialWinBg = cocos2d::ui::Scale9Sprite::createWithSpriteFrameName("doubleup_bottom_bg_win_amount");
		oPotentialWinBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		oPotentialWinBg->setCapInsets(capInsets);
		oPotentialWinBgOriginalSize = oPotentialWinBg->getContentSize();
		this->addChild(oPotentialWinBg);

		this->oPotentialWinTxt = Label::createWithTTF(res.fontConfigs["double_up"], "0");
		this->oPotentialWinTxt->setPosition(CSettings::CANVAS_WIDTH - this->oCurrentWinTxt->getPositionX() - 10, this->oCurrentWinTxt->getPositionY());
		this->oPotentialWinTxt->setTextColor(Color4B(255, 254, 197, 255));
		this->oPotentialWinTxt->enableOutline(Color4B(135, 72, 41, 255));
		this->addChild(this->oPotentialWinTxt);
		oPotentialWinBg->setPosition(this->oPotentialWinTxt->getPosition() - Vec2(5, 2));

		return true;
	}
	void CDoubleUpDB::onBonusEntered()
	{
		CBonusBase::onBonusEntered();

		auto res = GameConstant::getInstance()->getResources().doubleUp;

		this->oAnglerFishLeft->stopAllActions();
		this->oAnglerFishRight->stopAllActions();
		this->oBlueFish->stopAllActions();

		this->oAnglerFishLeft->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			res["fish_plist"],
			"doubleup_angler_fish_doubleup_anglerfish_%i",
			1,
			24,
			30,
			-1
			));

		this->oAnglerFishRight->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			res["fish_plist"],
			"doubleup_angler_fish_doubleup_anglerfish_%i",
			1,
			24,
			30,
			-1
			));

		this->oBlueFish->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			res["fish_plist"],
			"doubleup_blue_fish_bluefish_%i",
			1,
			24,
			30,
			-1
			));

		this->updateTotalWinText();
	}
	void CDoubleUpDB::initAnimaton()
	{
		auto res = GameConstant::getInstance()->getResources().doubleUp;

		this->oFishContainer = Node::create();
		auto createFish = [this, &res](const std::string& frameFormat, const Vec2& pos, float scale) {
			auto fish = Sprite::createWithSpriteFrameName(StringUtils::format(frameFormat.c_str(), 1));
			fish->setPosition(pos);
			fish->setScale(scale);
			this->oFishContainer->addChild(fish);
			return fish;
		};

		this->oAnglerFishLeft = createFish("doubleup_angler_fish_doubleup_anglerfish_%i",
			Vec2(CSettings::CANVAS_WIDTH / 2 - 290, CSettings::CANVAS_HEIGHT / 2 + 85),
			2.5f);

		this->oAnglerFishRight = createFish("doubleup_angler_fish_doubleup_anglerfish_%i",
			Vec2(CSettings::CANVAS_WIDTH / 2 + 290, CSettings::CANVAS_HEIGHT / 2 + 85),
			2.5f);
		this->oAnglerFishRight->setScaleX(-2.5f);

		this->oBlueFish = createFish("doubleup_blue_fish_bluefish_%i",
			Vec2(CSettings::CANVAS_WIDTH / 2, CSettings::CANVAS_HEIGHT / 2),
			1.25f);

		this->oResult = Helper4Sprite::createOptimizeSprite();
		this->oResult->setVisible(false);
		this->oResult->setScale(2.5f);
		GameUtils::centerNode(this->oResult);

		this->addChild(this->oResult);
		this->addChild(this->oFishContainer);
	}
	void CDoubleUpDB::restore()
	{
		this->oGame->getMain()->removeBonusHistory();
	}
	void CDoubleUpDB::createButton(int index, const std::string & frameName, const cocos2d::Vec2 & pos)
	{
		auto oBtn = CSpriteButton::createButtonWithSpriteFrameName(
			frameName,
			nullptr,
			[this, index]() {
			this->btnGamblingClicked(index);
		}
		);
		oBtn->setScaleEvent(0.9f, 1.0f);
		oBtn->setPosition(pos);
		this->addChild(oBtn);

		this->aBtn[index] = oBtn;
	}
	void CDoubleUpDB::playResultAnimation(bool isEscape)
	{
		auto plist = GameConstant::getInstance()->getResources().doubleUp["capture_plist"];
		auto frameFormat = "doubleup_capture_doubleup_capture_%i";
		if (isEscape) {
			plist = GameConstant::getInstance()->getResources().doubleUp["escape_plist"];
			frameFormat = "doubleup_escape_doubleup_escape_%i";
		}
		auto animation = AnimationHelper::getInstance()->createAnimationByFrameName(
			plist,
			frameFormat,
			1,
			24,
			30,
			1
			);

		this->oResult->runAction(Sequence::createWithTwoActions(
			animation,
			CallFunc::create([this]() {
			this->oFishContainer->setVisible(true);
			this->oResult->setVisible(false);
			
			if (this->bFinish) {
				this->scheduleOnce(schedule_selector(CDoubleUpDB::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
			}
			else {
				this->enableAllBtn();
			}
		})
			));

		this->oFishContainer->setVisible(false);
		this->oResult->setVisible(true);
	}
	void CDoubleUpDB::updateTotalWinText()
	{
		if (this->iTotWin > 0) {
			//this->iTotWin = 10000000000000000000;
			this->oCurrentWinTxt->setString(UtilFunction::FormatWithCommas(this->iTotWin));
			oCurrentWinBg->setContentSize(Size(MAX(oCurrentWinBgOriginalSize.width,MIN(oCurrentWinTxt->getContentSize().width+60, oCurrentWinBgOriginalSize.width*2)),oCurrentWinBgOriginalSize.height));
			this->oPotentialWinTxt->setString(UtilFunction::FormatWithCommas(this->iTotWin * 2));
			oPotentialWinBg->setContentSize(Size(MAX(oPotentialWinBgOriginalSize.width, MIN(oPotentialWinTxt->getContentSize().width + 60, oPotentialWinBgOriginalSize.width * 2)), oPotentialWinBgOriginalSize.height));

			this->oCurrentWinTxt->runAction(Sequence::createWithTwoActions(
				EaseBounceOut::create(ScaleTo::create(0.1f, 1.5f)),
				EaseCubicActionIn::create(ScaleTo::create(0.1f, 1.0f))));

			this->oPotentialWinTxt->runAction(Sequence::createWithTwoActions(
				EaseBounceOut::create(ScaleTo::create(0.1f, 1.5f)),
				EaseCubicActionIn::create(ScaleTo::create(0.1f, 1.0f))));
		}
	}
	void CDoubleUpDB::showResult(bool bFinish, int iResult, double iTotWin, bool bFromRestore)
	{
		CBonusBase::showResult(bFinish, iResult, iTotWin);
		this->disableAllBtn();

		if (iResult != 0) {
			Manager4Sound::getInstance()->setVolumeBackgroundMusic(0.0f);

			Director::getInstance()->getScheduler()->schedule([this](float dt) {
				Manager4Sound::getInstance()->setVolumeBackgroundMusic(1.0f);
			}, this, 0, 0, 0.8f, false, "CDoubleUpDB_result");

			if (!this->bFinish) {
				//user win
				Manager4Sound::getInstance()->playDoubleUpWin();
			}
			else {
				//user lose
				Manager4Sound::getInstance()->playDoubleUpLose();
			}
		}
		if (iResult == 1) {
			this->playResultAnimation(true);
		}
		else if (iResult == 2) {
			this->playResultAnimation(false);
		}
		else if (bFinish) {
			this->scheduleOnce(schedule_selector(CDoubleUpDB::showFinalWin), CSettings::TIMER_DELAY_SHOW_WIN_BONUS);
		}


		this->updateTotalWinText();
	}
	void CDoubleUpDB::resetBonus()
	{
		CBonusBase::resetBonus();
		this->oFishContainer->setVisible(true);
		this->oAnglerFishLeft->stopAllActions();
		this->oAnglerFishRight->stopAllActions();
		this->oBlueFish->stopAllActions();
		this->oResult->setVisible(false);
		this->oResult->stopAllActions();
	}
}
