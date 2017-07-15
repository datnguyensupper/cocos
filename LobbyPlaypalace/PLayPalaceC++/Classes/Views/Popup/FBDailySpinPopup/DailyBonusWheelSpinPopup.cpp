#include "DailyBonusWheelSpinPopup.h"
#include "DailyBonusWheelPopup.h"
#include "Constant/Defination.h"
#include "Manager/InfoManager.h"
#include "Manager/SoundManager.h"
#include "Info/AdditionalInfo.h"
#include "Helper/Helper4Sprite.h"


USING_NS_CC;
#define SPIN_TIME 4 //5second
#define AUTO_SPIN_AFTER 3 //3second
#define DELAY_TIME_SHOW_RESULT 3

void DailyBonusWheelSpinPopup::spin()
{
	this->spinButton->setEnabled(false);
	SoundManager::getInstance()->playSoundEffectDailyWheelBonusSpin();
	auto dailyBonusWheelInfo = InfoManager::getInstance()->getAdditionalInfo()->dailyBonusWheelInfo;
	double coinValue = dailyBonusWheelInfo->coin;
	int factor = dailyBonusWheelInfo->factor;

	int angleWheelBG = this->factorsWithAnglePosWheel[factor];
	int angleInnerWheel = this->coinValuesWithAnglePosInnerWheel[coinValue];

	//wheel bg spin
	int rotateWheelBGValue = 360 - angleWheelBG + 360 * 2;
	auto actionWheelBG = EaseQuadraticActionOut::create(RotateBy::create(SPIN_TIME, rotateWheelBGValue));
	auto actionFinish = CallFunc::create([this]()
	{
		this->_parent->processAfterSpin();
	});
	this->wheelBG->runAction(Sequence::create(
		actionWheelBG, 
		CallFunc::create([this]()
		{
			this->light->setVisible(true);
			for (auto lensflare : this->light->getChildren())
			{
				float time1 = RandomHelper::random_real(0.3f, 0.8f);
				float time2 = RandomHelper::random_real(0.3f, 0.8f);
				lensflare->runAction(
					RepeatForever::create(
						Sequence::create(
							Spawn::create(
								ScaleTo::create(time1, .5f),
								RotateBy::create(time1, 90),
								nullptr
							),
							Spawn::create(
								ScaleTo::create(time2, 0.0f),
								RotateBy::create(time2, 90),
								nullptr
							),
							DelayTime::create(0.2f),
							nullptr
						)
					)
				);
			}
		}),
		DelayTime::create(DELAY_TIME_SHOW_RESULT), 
		actionFinish,
		nullptr));

	//inner wheel bg spin
	int rotateInnerWheelValue = -angleInnerWheel - 360 * 2;
	this->wheelInner->runAction(EaseQuadraticActionOut::create(RotateBy::create(SPIN_TIME, rotateInnerWheelValue)));

	//gear
	float durationGearRotateAction = 0.3f;
	auto sequenceAction = Sequence::createWithTwoActions(
		RotateTo::create(durationGearRotateAction, -30),
		RotateTo::create(durationGearRotateAction, 0)
	);
	this->gear->runAction(Repeat::create(sequenceAction, SPIN_TIME / (2 * durationGearRotateAction) + 1));

	//particals
	this->particalCircleForSpinBtn->start();
	this->particalCircleForWheelBG->start();
}

DailyBonusWheelSpinPopup * DailyBonusWheelSpinPopup::create(DailyBonusWheelPopup * parent)
{
	DailyBonusWheelSpinPopup* spinPopup = new (std::nothrow) DailyBonusWheelSpinPopup();
	spinPopup->_parent = parent;
	if (spinPopup && spinPopup->init())
	{
		spinPopup->autorelease();
		return spinPopup;
	}
	CC_SAFE_DELETE(spinPopup);
	return nullptr;
}

bool DailyBonusWheelSpinPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//WHEEL BG
	this->wheelBG = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_BACKGROUND);
	this->wheelBG->setPosition(origin + visibleSize / 2);
	this->addChild(wheelBG);

	//WHEEL INNER
	this->wheelInner = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_INNER);
	this->wheelInner->setPosition(this->wheelBG->getPosition());
	this->addChild(this->wheelInner);

	//GEAR
	this->gear = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_GEAR);
	this->gear->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	this->gear->setPosition(this->wheelBG->getPosition() + Vec2(0, this->wheelBG->getContentSize().height / 2 - 30));
	this->addChild(gear);

	//SPIN BUTTON
	this->spinButton = ui::Button::create(PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_BTN_SPIN, "", PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_BTN_SPIN,ui::Widget::TextureResType::PLIST);
	this->spinButton->setPosition(this->wheelBG->getPosition());
	this->spinButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->spin();
	});
	this->addChild(this->spinButton);

	//LIGHT
	this->light = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_DAILY_BONUS_WHEEL_SPIN_POPUP_LIGHT);
	this->light->setPosition(this->wheelBG->getPosition() + Vec2(0, this->light->getContentSize().height / 2 + this->spinButton->getContentSize().height / 2 - 20));
	this->light->setVisible(false);
	this->addChild(light);

	//ANIMATION FOR LIGHT
	Vec2 animationArr[16] = {
		Vec2(13, 19),
		Vec2(35, 16),
		Vec2(79, 11),
		Vec2(106, 13),
		Vec2(135, 18),
		Vec2(145, 44),
		Vec2(135, 85),
		Vec2(115, 145),
		Vec2(107, 186),
		Vec2(100, 207),
		Vec2(81, 202),
		Vec2(62, 207),
		Vec2(17, 37),
		Vec2(26, 86),
		Vec2(39, 129),
		Vec2(50, 167)
	};
	for (int i = 0; i < 16; i++)
	{
		Vec2 animationPos = animationArr[i];
		animationPos = (Vec2(animationPos.x * 2, light->getContentSize().height * Director::getInstance()->getContentScaleFactor()) - animationPos) / Director::getInstance()->getContentScaleFactor();
		auto lensflareAnim = Helper4Sprite::createWithSpriteFrameName(
			(RandomHelper::random_int(0, 10) > 5 ?
				PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_WHITE : PNG_FRAME_DAILY_BONUS_WHEEL_RESULT_POPUP_START_YELLOW));
		lensflareAnim->setBlendFunc(BlendFunc::ADDITIVE);
		lensflareAnim->setPosition(animationPos);
		lensflareAnim->setScale(0);
		this->light->addChild(lensflareAnim);
	}

	//PARTICALS
	this->particalCircleForWheelBG = ParticleSystemQuad::create("animation/partical_circle_spin_popup.plist");
	//this->particalCircleForWheelBG->setScale(3);
	this->particalCircleForWheelBG->setStartSize(600);
	this->particalCircleForWheelBG->setEndSize(1000);
	this->particalCircleForWheelBG->setPosition(this->wheelBG->getPosition());
	this->particalCircleForWheelBG->stop();
	this->addChild(this->particalCircleForWheelBG);

	this->particalCircleForSpinBtn = ParticleSystemQuad::create("animation/partical_circle_spin_popup.plist");
	this->particalCircleForSpinBtn->setPosition(this->wheelBG->getPosition());
	this->particalCircleForSpinBtn->stop();
	this->addChild(this->particalCircleForSpinBtn);

	//init maps
	this->factorsWithAnglePosWheel[1] = 0;
	this->factorsWithAnglePosWheel[2] = 330;
	this->factorsWithAnglePosWheel[3] = 90;
	this->factorsWithAnglePosWheel[4] = 60;
	this->factorsWithAnglePosWheel[5] = 30;
	this->factorsWithAnglePosWheel[6] = 210;

	this->coinValuesWithAnglePosInnerWheel[50] = 270;
	this->coinValuesWithAnglePosInnerWheel[100] = 210;
	this->coinValuesWithAnglePosInnerWheel[200] = 240;
	this->coinValuesWithAnglePosInnerWheel[300] = 0;
	this->coinValuesWithAnglePosInnerWheel[500] = 300;
	this->coinValuesWithAnglePosInnerWheel[600] = 150;
	this->coinValuesWithAnglePosInnerWheel[800] = 90;
	this->coinValuesWithAnglePosInnerWheel[1000] = 30;
	this->coinValuesWithAnglePosInnerWheel[2000] = 120;
	this->coinValuesWithAnglePosInnerWheel[5000] = 60;
	this->coinValuesWithAnglePosInnerWheel[10000] = 180;
	this->coinValuesWithAnglePosInnerWheel[50000] = 330;

	return true;
}

void DailyBonusWheelSpinPopup::reset()
{
	BasePopup::reset();
	this->wheelBG->stopAllActions();
	this->wheelBG->setRotation(0);

	this->wheelInner->stopAllActions();
	this->wheelInner->setRotation(0);

	this->particalCircleForWheelBG->stop();

	this->particalCircleForSpinBtn->stop();

	this->spinButton->setEnabled(true);

	this->light->setVisible(false);

	this->gear->stopAllActions();
	this->gear->setRotation(0);
}

void DailyBonusWheelSpinPopup::prepareAndShow()
{
	this->reset();
	BasePopup::show(_parent);
	/*this->_parent->addChild(this);
	this->setVisible(true);
	this->setOpacity(1);*/
	this->scheduleOnce([this](float dt)
	{
		if (this->wheelBG->getNumberOfRunningActions() > 0) {
			return;
		}
		this->spin();
	}, AUTO_SPIN_AFTER, "schedule_auto_spin");
}
