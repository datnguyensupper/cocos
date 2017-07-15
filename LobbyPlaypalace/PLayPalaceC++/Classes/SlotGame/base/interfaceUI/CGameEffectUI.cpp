#include "CGameEffectUI.h"
#include "../game/CMainBase.h"
#include "../utils/GameUtils.h"
#include "../utils/CSpriteButton.h"
#include "../manager/Manager4Sound.h"
#include "../constant/GameConstant.h"
#include "../settings/CSettings.h"
#include "Manager/PopupManager.h"
#include "Manager/ScaleManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Util/UtilFunction.h"
#include "Constant/Defination.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
#define DELAY_ANIMATION 0.15f
	CWinEffectUI::CWinEffectUI(): Node()
	{
		this->setCascadeOpacityEnabled(true);
	}
	bool CWinEffectUI::init()
	{
		if(!Node::init()) return false;

		this->setPositionY(85);

		//GameUtils::centerNode(this);
		auto darkLayer = LayerColor::create(ccc4(0, 0, 0, 150));
		darkLayer->setContentSize(Size(CSettings::CANVAS_WIDTH, CSettings::CANVAS_HEIGHT));
		darkLayer->setPosition(Vec2(darkLayer->getContentSize() / -2) - Vec2(0, 85));
		this->addChild(darkLayer);

		auto block = CSpriteButton::createInvisibleButton(Rect(darkLayer->getContentSize() / -2, darkLayer->getContentSize()), nullptr, nullptr);
		block->setIsBlock(true);
		this->addChild(block);

		this->oStars = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_LVUP_STARS);
		this->addChild(this->oStars);

		this->oBigWin = Node::create();
		this->oBigWin->setCascadeOpacityEnabled(true);
		this->addChild(this->oBigWin);
		this->oMegaWin = Node::create();
		this->oMegaWin->setCascadeOpacityEnabled(true);
		this->addChild(this->oMegaWin);

		//Init stars for big win
		auto firstPos = Vec2(-175, 50);
		auto xDis = 30;
		auto yDis = 70;

		std::vector<Vec2>aPos = {
			Vec2(firstPos + Vec2(-xDis - 10, - yDis + 10)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(xDis + 330, - yDis + 10)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(-2 * xDis, -2 * yDis)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(xDis + 320, 0)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(2 * xDis + 320, -2 * yDis)) * CSettings::SCALE_VALUE_TO_1920,
			firstPos * CSettings::SCALE_VALUE_TO_1920,
		};

		std::vector<Vec2>aAnchor = {
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(1, 0),
			Vec2(0, 0),
			Vec2(0, 0),
			Vec2(1, 0),
		};

		this->aBigWinStars.resize(6);

		for (int i = 0, size = this->aBigWinStars.size(); i < size; ++i) {
			auto bigStar = Sprite::createWithSpriteFrameName("win_effect_big_star_" + ToString(i + 1));
			bigStar->setAnchorPoint(aAnchor[i]);
			auto starSize = bigStar->getContentSize();
			bigStar->setPosition(aPos[i] - starSize / 2 + Vec2(starSize.width * aAnchor[i].x, starSize.height * aAnchor[i].y));
			this->oBigWin->addChild(bigStar);
			this->aBigWinStars[i] = bigStar;
		}

		//Init upper stars for mega win
		firstPos = Vec2(-185, 50);

		aPos = {
			firstPos * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(390, 0)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(-25, -86)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(-58 + 390, 48)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(25 + 390, -86)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(58, 48)) * CSettings::SCALE_VALUE_TO_1920
		};

		this->aMegaWinUpStars.resize(6);

		for (int i = 0, size = this->aMegaWinUpStars.size(); i < size; ++i) {
			auto upStar = Sprite::createWithSpriteFrameName("win_effect_mega_star_up_" + ToString(i + 1));
			upStar->setAnchorPoint(aAnchor[i]);
			auto starSize = upStar->getContentSize();
			upStar->setPosition(aPos[i] - starSize / 2 + Vec2(starSize.width * aAnchor[i].x, starSize.height * aAnchor[i].y));
			this->oMegaWin->addChild(upStar);
			this->aMegaWinUpStars[i] = upStar;
		}

		//Init down stars for mega win
		firstPos = Vec2(-155, -50);
		xDis = 58;
		yDis = 27;

		aPos = {
			firstPos * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(320, 0)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(xDis - 50 + 320, yDis + 42)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(xDis, -yDis)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(-xDis + 320, -yDis)) * CSettings::SCALE_VALUE_TO_1920,
			Vec2(firstPos + Vec2(-xDis + 50, yDis + 42)) * CSettings::SCALE_VALUE_TO_1920
		};
		aAnchor = {
			Vec2(1, 1),
			Vec2(0, 1),
			Vec2(0, 1),
			Vec2(1, 1),
			Vec2(0, 1),
			Vec2(1, 1),
		};

		this->aMegaWinDownStars.resize(6);

		for (int i = 0, size = this->aMegaWinDownStars.size(); i < size; ++i) {
			auto downStar = Sprite::createWithSpriteFrameName("win_effect_mega_star_down_" + ToString(i + 1));
			downStar->setAnchorPoint(aAnchor[i]);
			auto starSize = downStar->getContentSize();
			downStar->setPosition(aPos[i] - starSize / 2 + Vec2(starSize.width * aAnchor[i].x, starSize.height * aAnchor[i].y));
			this->oMegaWin->addChild(downStar);
			this->aMegaWinDownStars[i] = downStar;
		}

		this->oTitleBigWin = Sprite::createWithSpriteFrameName("win_effect_bigwin");
		this->oBigWin->addChild(this->oTitleBigWin);

		this->oTitleMega = Sprite::createWithSpriteFrameName("win_effect_mega_mega");
		this->oTitleMega->setPositionY(50);
		this->oMegaWin->addChild(this->oTitleMega);

		this->oTitleWin = Sprite::createWithSpriteFrameName("win_effect_mega_win");
		this->oTitleWin->setPositionY(-50);
		this->oMegaWin->addChild(this->oTitleWin);

		this->oWinText = Label::createWithBMFont("popup/mega-big-win/effect_win_font.fnt", "0");
		this->oWinText->setPositionY(-250);
		this->addChild(this->oWinText);

		this->reset();

		return true;
	}
	void CWinEffectUI::showWinEffect(const double & iWin, bool isMegaWin, std::string titleBigWinPath)
	{
		this->reset();
		this->setVisible(true);

		float totalDuration = isMegaWin ? 3.75f : 1.5f;

		this->oWinText->setScale(0);
		this->oWinText->setString("0");
		this->oWinText->runAction(Sequence::create(
			DelayTime::create(0.35f),
			EaseBackOut::create(ScaleTo::create(0.25f, 0.6f)),
			ActionFloat::create(totalDuration - 0.75f, 0, iWin, [this](float value) {
			this->oWinText->setString(UtilFunction::FormatWithCommas(value));
		}), CallFunc::create([this, iWin] {
			this->oWinText->setString(UtilFunction::FormatWithCommas(iWin));
		}), NULL));

		this->runAction(Sequence::create(
			DelayTime::create(totalDuration + 1.0f),
			FadeOut::create(0.5f),
			CallFunc::create([this] {
			this->setVisible(false);
		}), NULL));

		this->playBigWin(isMegaWin, titleBigWinPath);
	}
	void CWinEffectUI::checkAndShowWinEffect(const double & iWin, const double & totalBet, ObjectMagicItemReceiveAfterSpin *oMagicItemAfterSpin)
	{
		if (oMagicItemAfterSpin
			&& oMagicItemAfterSpin->magicItemType != LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DEFAULT
			&& oMagicItemAfterSpin->magicItemType != LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DOUBLE_EXP
			&& oMagicItemAfterSpin->magicItemType != LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SYMBOL)
		{
			std::string titleBigWinPath = PNG_FRAME_MAGIC_ITEM_100_WIN_TITLE;
			if (oMagicItemAfterSpin->magicItemType == LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1)
			{
				titleBigWinPath = PNG_FRAME_MAGIC_ITEM_LUCKY_10_TITLE;
			}
			else if (oMagicItemAfterSpin->magicItemType == LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2)
			{
				titleBigWinPath = PNG_FRAME_MAGIC_ITEM_LUCKY_20_TITLE;
			}
			this->showWinEffect(iWin, false, titleBigWinPath);
		}
		else
		{
			if (iWin >= totalBet * 10) {
				this->showWinEffect(iWin, true);
			}
			else if (iWin >= totalBet * 5) {
				this->showWinEffect(iWin, false);
			}
		}
	}
	void CWinEffectUI::playShootingStar(const std::vector<cocos2d::Sprite*>& aStars, 
		float delayToShootStar,
		const std::vector<float>& delayBetweenStar,
		bool bPlayExplodeStar)
	{
		if (bPlayExplodeStar) {
			this->oStars->setScale(0);
			this->oStars->stopAllActions();
			this->oStars->setOpacity(255);

			this->oStars->runAction(Sequence::createWithTwoActions(
				DelayTime::create(0.25f),
				EaseBackOut::create(ScaleTo::create(0.5f, 2.0f))));
			this->oStars->runAction(Sequence::createWithTwoActions(
				DelayTime::create(0.25f),
				FadeOut::create(0.8f)));
		}

		for (int i = 0, size = aStars.size(); i < size; ++i) {
			aStars[i]->runAction(
				Sequence::createWithTwoActions(
					DelayTime::create(delayToShootStar + delayBetweenStar[i]),
					EaseBackOut::create(ScaleTo::create(0.12f, 1.0f))));
		}
	}
	void CWinEffectUI::playBigWin(bool isMegaWin, std::string titleBigWinPath)
	{
		this->oBigWin->setVisible(true);
		this->playShootingStar(this->aBigWinStars, 
			2 * DELAY_ANIMATION, 
			std::vector<float>{ 0, 0, DELAY_ANIMATION, 2 * DELAY_ANIMATION, DELAY_ANIMATION, 2 * DELAY_ANIMATION });

		//if (titleBigWinPath == "win_effect_bigwin")
		//{
			this->oTitleBigWin->initWithSpriteFrameName(titleBigWinPath);
		//}
	/*	else
		{
			this->oTitleBigWin->initWithFile(titleBigWinPath);
		}*/
		this->oTitleBigWin->runAction(EaseBackOut::create(ScaleTo::create(0.25f, 1.0f)));

		Action* action = nullptr;
		if (isMegaWin) {
			this->oBigWin->runAction(Sequence::create(
				DelayTime::create(2.0f),
				FadeOut::create(0.5f),
				CallFunc::create([this]() {
				this->oBigWin->setVisible(false);
				this->playMegaWin();
			}), NULL));
		}

		Manager4Sound::getInstance()->playWinEffectSound();
	}
	void CWinEffectUI::playMegaWin()
	{
		this->oMegaWin->setVisible(true);

		this->oTitleMega->runAction(EaseBackOut::create(ScaleTo::create(0.25f, 1.0f)));
		this->oTitleWin->runAction(Sequence::createWithTwoActions(
			DelayTime::create(DELAY_ANIMATION * 2), EaseBackOut::create(ScaleTo::create(0.25f, 1.0f))));

		this->playShootingStar(this->aMegaWinUpStars,
			3 * DELAY_ANIMATION,
			std::vector<float>{ 0, 0, DELAY_ANIMATION, 2 * DELAY_ANIMATION, DELAY_ANIMATION, 2 * DELAY_ANIMATION }, true);
		this->playShootingStar(this->aMegaWinDownStars,
			3 * DELAY_ANIMATION,
			std::vector<float>{ 0, 0, 2 * DELAY_ANIMATION, DELAY_ANIMATION, DELAY_ANIMATION, 2 * DELAY_ANIMATION }, false);

		Manager4Sound::getInstance()->playWinEffectSound();
	}
	void CWinEffectUI::reset()
	{
		this->setVisible(false);
		this->stopAllActions();


		this->oBigWin->setOpacity(255);
		this->oBigWin->setVisible(false);
		this->oBigWin->stopAllActions();

		this->oMegaWin->setVisible(false);

		this->setOpacity(255);

		this->oTitleBigWin->setScale(0);
		this->oTitleBigWin->stopAllActions();
		this->oTitleMega->setScale(0);
		this->oTitleMega->stopAllActions();
		this->oTitleWin->setScale(0);
		this->oTitleWin->stopAllActions();

		for (auto star : this->aBigWinStars) {
			star->stopAllActions();
			star->setScale(0);
		}
		for (auto star : this->aMegaWinDownStars) {
			star->stopAllActions();
			star->setScale(0);
		}
		for (auto star : this->aMegaWinUpStars) {
			star->stopAllActions();
			star->setScale(0);
		}
	}


	CSpinEffect::CSpinEffect(CMainBase* oMain) : Node(),
		oMain(oMain),
		bUpdateExpLocal(true)
	{
	}
	CSpinEffect::~CSpinEffect()
	{
	}
	bool CSpinEffect::init()
	{
		if (!Node::create()) return false;
		this->setCascadeOpacityEnabled(true);

		this->oParticle = ParticleSystemQuad::create(PNG_STAR_EFFECT_SPIN_PARTICLE);
		this->oParticle->setPositionType(ParticleSystem::PositionType::FREE);

		this->oParticle->stop();
		this->addChild(this->oParticle);



		this->oStar = Helper4Sprite::createOptimizeSprite(PNG_STAR_EFFECT_SPIN);
		this->oStar->setScale(0.9f*ScaleManager::getInstance()->getExactlyScaleDownRatio());
		this->addChild(this->oStar);

		this->setVisible(false);

		return true;
	}
	void CSpinEffect::playFlyingStarAnimation(const cocos2d::Vec2& startPos, const cocos2d::Vec2& endPos)
	{
		this->setPosition(startPos);
		this->setOpacity(255);

		this->stopAllActions();
		this->oParticle->stop();

		this->oStar->stopAllActions();
		this->oStar->setRotation(0);

		if (config.endPosition == Vec2::ZERO) {
			config.controlPoint_1 = Vec2(startPos.x, startPos.y + CSettings::CANVAS_HEIGHT * 0.8f);
			config.controlPoint_2 = Vec2(endPos.x + abs(startPos.x - endPos.x) / 3, endPos.y - CSettings::CANVAS_HEIGHT / 4);
			config.endPosition = Vec2(endPos);
		}

		this->setVisible(true);
		this->runAction(Sequence::create(
			BezierTo::create(1.5f, config), 
			CallFunc::create([this]() { 
			if (this->oMain && bUpdateExpLocal) {
				PopupManager::getInstance()->getHeaderLobbyLayout()->hightLightExpBar(oMain->getTotalBet());
			}
			this->oParticle->stop();
		}), 
			FadeOut::create(0.25f), 
			CallFunc::create([this]() {
			this->setVisible(false);
			this->oStar->stopAllActions();
		}), NULL));

		this->oStar->runAction(RotateTo::create(2.0f, 1080));


		this->oParticle->start();
	}

	CGameEffectUI::CGameEffectUI(CMainBase* oMain): Node()
	{
		this->autorelease();
		this->oWinEffect = new CWinEffectUI();
		this->oWinEffect->init();

		this->oSpinEffect = new CSpinEffect(oMain);
		this->oSpinEffect->init();

		this->setPosition(Director::getInstance()->getVisibleOrigin() + Director::getInstance()->getVisibleSize() / 2);

		this->addChild(this->oWinEffect);
		this->addChild(this->oSpinEffect);

		oMain->getScene()->addChild(this);
	}
	CGameEffectUI::~CGameEffectUI()
	{
	}
}