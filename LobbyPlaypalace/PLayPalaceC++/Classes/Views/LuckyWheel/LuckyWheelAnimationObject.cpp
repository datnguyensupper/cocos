#include "LuckyWheelAnimationObject.h"
#include "Helper/AnimationHelper.h"
#include "Constant/Defination.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
using namespace std;

namespace LuckyWheel {
	bool ShinyBackground::init()
	{
		if (!AnimationUIBase::init()) return false;

		this->shiny_1 = Sprite::createWithSpriteFrameName("lucky_wheel_shiny_bg_1");
		this->shiny_1->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });

		this->shiny_2 = Sprite::createWithSpriteFrameName("lucky_wheel_shiny_bg_1");
		this->shiny_2->setScaleX(-1);
		this->shiny_2->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });

		this->shiny_3 = Sprite::createWithSpriteFrameName("lucky_wheel_shiny_bg_2");
		this->shiny_3->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });

		this->addChild(this->shiny_1);
		this->addChild(this->shiny_2);
		this->addChild(this->shiny_3);

		this->stopAnimation();

		return true;
	}
	void ShinyBackground::startAnimation()
	{
		if (this->shiny_1->getNumberOfRunningActions() > 0) return;
		this->setVisible(true);
		this->shiny_1->setScale(1.0f);
		this->shiny_2->setScale(1.0f);
		this->shiny_3->setScale(1.0f);

		this->shiny_1->runAction(Sequence::create(
			ScaleTo::create(0.5f, 2.4f),
			ScaleTo::create(0.5f, 2.0f),
			ScaleTo::create(0.5f, 2.5f),
			ScaleTo::create(0.5f, 1),
			CallFunc::create([this]() {
			this->stopAnimation();
		}), NULL));

		this->shiny_2->runAction(Sequence::create(
			ScaleTo::create(0.5f, 2.4f),
			ScaleTo::create(0.5f, 2.0f),
			ScaleTo::create(0.5f, 2.5f),
			ScaleTo::create(0.5f, 1), NULL));
		this->shiny_3->runAction(Sequence::create(
			ScaleTo::create(0.5f, 2.4),
			ScaleTo::create(0.5f, 2.0f),
			ScaleTo::create(0.5f, 2.5f),
			ScaleTo::create(0.5f, 1), NULL));
	}
	void ShinyBackground::stopAnimation()
	{
		this->shiny_1->stopAllActions();
		this->shiny_2->stopAllActions();
		this->shiny_3->stopAllActions();

		this->setVisible(false);
	}

	bool CircleBound::init()
	{
		if (!AnimationUIBase::init()) return false;

		this->bg = Sprite::createWithSpriteFrameName("lucky_wheel_wheel_bound");
		this->addChild(this->bg);

		this->line_1 = Sprite::createWithSpriteFrameName("lucky_wheel_wheel_bound_light");
		this->line_1->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
		this->line_1->setAnchorPoint(Vec2(1, 0));
		this->addChild(this->line_1);

		this->line_2 = Sprite::createWithSpriteFrameName("lucky_wheel_wheel_bound_light");
		this->line_2->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
		this->line_2->setScaleX(-1);
		this->line_2->setAnchorPoint(Vec2(1, 0));
		this->addChild(this->line_2);

		this->stopAnimation();

		return true;
	}
	void CircleBound::startAnimation()
	{
		if (this->line_1->getNumberOfRunningActions() > 0) return;
		this->bg->setSpriteFrame("lucky_wheel_wheel_bound_light_bg");
		this->line_1->setRotation(0);
		this->line_2->setRotation(0);
		this->line_1->setVisible(true);
		this->line_2->setVisible(true);
		this->line_1->runAction(Sequence::createWithTwoActions(
			RotateBy::create(2.0f, 720),
			CallFunc::create([this]() {
			this->stopAnimation();
		})));
		this->line_2->runAction(RotateBy::create(2.0f, -720));
	}
	void CircleBound::stopAnimation()
	{
		this->bg->setSpriteFrame("lucky_wheel_wheel_bound");
		this->line_1->setVisible(false);
		this->line_2->setVisible(false);
		this->line_1->stopAllActions();
		this->line_2->stopAllActions();
	}

	bool SlotHover::init()
	{
		if (!AnimationUIBase::init()) return false;

		this->bg = Sprite::createWithSpriteFrameName("luckywheel_hover_blue_01");
		this->bg->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
		//this->bg->setScale(1.2f);
		this->bg->setPositionY(-60);
		this->bg->setAnchorPoint(Vec2(0.5, 0));

		this->addChild(this->bg);

		this->stopAnimation();

		return true;
	}
	void SlotHover::startAnimation()
	{
		if (this->bg->getNumberOfRunningActions() > 0) return;
		this->setVisible(true);
		string frameFormat = "luckywheel_hover_blue_%.2i";
		if (!this->isBlue) {
			frameFormat = "luckywheel_hover_purple_%.2i";
		}
		this->bg->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			"",
			frameFormat,
			1,
			31,
			24,
			kRepeatForever));
	}
	void SlotHover::stopAnimation()
	{
		this->bg->stopAllActions();
		this->setVisible(false);
	}

	bool ButtonSpin::init()
	{
		if (!Node::init()) return false;

		this->innerAnim = Sprite::createWithSpriteFrameName("luckywheel_button_inner_01");
		this->innerAnim->setScale(1.1f);
		this->innerAnim->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
		this->addChild(this->innerAnim);

		this->btn = GameSlot::CSpriteButton::createButtonWithSpriteFrameName("lucky_wheel_spin", nullptr, nullptr);
		this->btn->setScaleEvent(0.9f);
		this->addChild(this->btn);

		this->starFlare = StarFlare::create({ Vec2(-50, 40), Vec2(50, -20) }, { 0.7f, 0.3f });
		this->addChild(this->starFlare);

		this->flashAnim = Sprite::createWithSpriteFrameName("luckywheel_button_flash_01");
		this->flashAnim->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
		this->addChild(this->flashAnim);

		this->outerAnim = Sprite::createWithSpriteFrameName("luckywheel_button_anim_01");
		this->outerAnim->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
		this->outerAnim->setScale(1.3f);
		this->addChild(this->outerAnim);

		this->stopAnimation();

		return true;
	}
	void ButtonSpin::startFlashAnimation()
	{
		if (this->flashAnim->getNumberOfRunningActions() > 0) return;
		this->flashAnim->setVisible(true);
		this->flashAnim->runAction(Sequence::createWithTwoActions(
			AnimationHelper::getInstance()->createAnimationByFrameName(
			"",
			"luckywheel_button_flash_%.2i",
			1,
			12,
			15,
			1
		),
			CallFunc::create([this]() {
			this->flashAnim->setVisible(false);
		})));

		this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.5f), CallFunc::create([this]() {
			this->starFlare->startAnimation();
		})));
	}
	void ButtonSpin::startInnerAnimation()
	{
		if (this->innerAnim->getNumberOfRunningActions() > 0) return;
		this->innerAnim->setVisible(true);
		this->innerAnim->setOpacity(255);
		this->innerAnim->runAction(Sequence::create(
			AnimationHelper::getInstance()->createAnimationByFrameName(
				"",
				"luckywheel_button_inner_%.2i",
				1,
				39,
				60,
				1
			),
			FadeOut::create(0.5f),
			CallFunc::create([this]() {
			this->innerAnim->setVisible(false);
		}), NULL));
	}
	void ButtonSpin::startOuterAnimation()
	{
		if (this->outerAnim->getNumberOfRunningActions() > 0) return;
		this->outerAnim->setVisible(true);
		this->outerAnim->setOpacity(255);
		this->outerAnim->runAction(Sequence::create(
			AnimationHelper::getInstance()->createAnimationByFrameName(
				"",
				"luckywheel_button_anim_%.2i",
				1,
				28,
				24,
				1
			),
			FadeOut::create(0.25f),
			CallFunc::create([this]() {
			this->outerAnim->setVisible(false);
		}), NULL));
	}
	void ButtonSpin::stopAnimation()
	{
		this->flashAnim->stopAllActions();
		this->innerAnim->stopAllActions();
		this->outerAnim->stopAllActions();
		this->starFlare->stopAnimation();

		this->flashAnim->setVisible(false);
		this->innerAnim->setVisible(false);
		this->outerAnim->setVisible(false);
	}

	bool CircleFlashLight::init()
	{
		if (!AnimationUIBase::init()) return false;

		this->bg = Sprite::createWithSpriteFrameName("lucky_wheel_wheel_circle_light");
		this->addChild(this->bg);

		this->stopAnimation();

		return true;
	}
	void CircleFlashLight::startAnimation()
	{
		this->stopAnimation();
		this->bg->setRotation(0);
		this->bg->runAction(RepeatForever::create(
			Sequence::create(
				CallFunc::create([this]() {
			this->bg->setRotation(10);
		}), DelayTime::create(0.1f),
			CallFunc::create([this]() {
			this->bg->setRotation(0);
		}), DelayTime::create(0.1f), NULL)));
	}
	void CircleFlashLight::startSpinAnimation()
	{
		this->stopAnimation();
		this->runAction(EaseQuarticActionOut::create(RotateBy::create(2.0f, -360)));
	}
	void CircleFlashLight::stopAnimation()
	{
		this->bg->setRotation(0);
		this->bg->stopAllActions();
	}

	bool SlotCoinEffect::init()
	{
		if (!AnimationUIBase::init()) return false;

		std::vector<Vec2> aPos = {
			Vec2(-50, 240),
			Vec2(5, 220),
			Vec2(50, 230),
			Vec2(-40, 180),
			Vec2(30, 170),
		};

		for (auto pos : aPos) {
			auto coin = Sprite::createWithSpriteFrameName("luckywheel_coin_1");
			coin->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
			coin->setPosition(pos);
			this->addChild(coin);

			this->aCoin.push_back(coin);

			auto lightFlare = Sprite::createWithSpriteFrameName("lucky_wheel_light_flare_yellow");
			lightFlare->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
			lightFlare->setPosition(pos * 1.1f);
			this->addChild(lightFlare);

		}
		this->setCascadeOpacityEnabled(true);

		this->stopAnimation();

		return true;
	}
	void SlotCoinEffect::startAnimation()
	{
		if (this->getNumberOfRunningActions() > 0) return;
		for (auto coin : this->aCoin) {
			coin->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
				"",
				"luckywheel_coin_%i",
				1,
				20,
				RandomHelper::random_int(10, 20),
				kRepeatForever
			));
		}
		this->startPosY = this->getPositionY();
		this->setOpacity(0);
		this->setScale(1);
		this->setPositionY(startPosY + 20);

		this->runAction(MoveTo::create(0.4f, Vec2(this->getPositionX(), startPosY)));
		this->runAction(Sequence::create(
			FadeIn::create(0.4f),
			CallFunc::create([this]() {
			this->runAction(ScaleTo::create(0.5f, 1.5f));
			this->runAction(MoveTo::create(0.5f, Vec2(this->getPositionX(), startPosY - 100)));
			this->runAction(Sequence::createWithTwoActions(
				FadeOut::create(0.5f),
				CallFunc::create([this]() {
				this->stopAnimation();
			})));
		}), NULL));

		this->setVisible(true);
	}
	void SlotCoinEffect::stopAnimation()
	{
		this->setPositionY(startPosY);
		for (auto coin : this->aCoin) {
			coin->stopAllActions();
		}
		this->setVisible(false);
	}

	bool WheelSting::init()
	{
		if (!AnimationUIBase::init()) return false;

		this->bg = Sprite::createWithSpriteFrameName("lucky_wheel_wheel_sting");
		this->addChild(this->bg);

		this->starFlare = StarFlare::create({ Vec2(-20, 30), Vec2(20, -20) }, { 0.5f, 0.2f });
		this->addChild(this->starFlare);

		this->flashAnim = Sprite::createWithSpriteFrameName("luckywheel_sting_flash_01");
		this->flashAnim->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
		this->addChild(this->flashAnim);

		this->stopAnimation();

		return true;
	}
	void WheelSting::startAnimation()
	{
		if (this->flashAnim->getNumberOfRunningActions() > 0) return;
		this->flashAnim->setVisible(true);
		this->flashAnim->runAction(AnimationHelper::getInstance()->createAnimationByFrameName(
			"",
			"luckywheel_sting_flash_%.2i",
			1,
			18,
			30,
			3
		));
		this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.5f), CallFunc::create([this]() {
			this->starFlare->startAnimation();
		})));
	}
	void WheelSting::stopAnimation()
	{
		this->starFlare->stopAnimation();
		this->flashAnim->stopAllActions();
		this->flashAnim->setVisible(false);
	}

	StarFlare * StarFlare::create(const std::vector<cocos2d::Vec2>& aPos, const std::vector<float>& aScale)
	{
		auto starFlare = new StarFlare();
		if (starFlare->init(aPos, aScale)) {
			starFlare->autorelease();
			return starFlare;
		}
		CC_SAFE_RELEASE_NULL(starFlare);
		return nullptr;
	}
	bool StarFlare::init(const std::vector<cocos2d::Vec2>& aPos, const std::vector<float>& aScale)
	{
		if (!AnimationUIBase::init()) return false;

		int i = 0;
		for (auto pos : aPos) {
			auto star = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_WHITE);
			star->setBlendFunc({ GL_SRC_ALPHA, GL_ONE });
			star->setPosition(pos);
			star->setScale(aScale[i++]);
			this->addChild(star);

			aSprite.push_back(star);
		}
		this->setCascadeOpacityEnabled(true);
		this->stopAnimation();

		return true;
	}
	void StarFlare::startAnimation()
	{
		this->setVisible(true);
		for (auto star : this->aSprite) {
			star->runAction(RepeatForever::create(RotateBy::create(1.0f, 360)));
		}
		this->setOpacity(255);
		this->runAction(Sequence::createWithTwoActions(
			FadeOut::create(1.0f),
			CallFunc::create([this]() {
			this->stopAnimation();
		})));
	}
	void StarFlare::stopAnimation()
	{
		this->stopAllActions();
		for (auto star : this->aSprite) {
			star->stopAllActions();
		}
		this->setVisible(false);
	}
}
