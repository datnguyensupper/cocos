/**
* creator: Kiet Duong
* date: 2017-04-03
* file: DailyBonusWheelResultPopup.h, DailyBonusWheelResultPopup.cpp
*/
#pragma once
#include "Views/Popup/BasePopup.h"

class TitleValueLabel : public cocos2d::Node
{
private:
	cocos2d::Label *titleLabel;
	cocos2d::Label *valueLabel;
	cocos2d::ParticleSystemQuad *particalAnimation;//
	int xDistance;
public:
	/// <summary>
	/// create popup result UI
	/// </summary>
	/// <param name="_titleLabel"></param>
	/// <param name="_valueLabel"></param>
	/// <param name="_xDistance">distance between label and info</param>
	/// <returns></returns>
	static TitleValueLabel *create(cocos2d::Label *_titleLabel, cocos2d::Label *_valueLabel, int _xDistance) {

		TitleValueLabel* label = new (std::nothrow) TitleValueLabel();
		label->titleLabel = _titleLabel;
		label->titleLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
		label->titleLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);

		label->valueLabel = _valueLabel;
		label->valueLabel->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
		label->valueLabel->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);

		label->xDistance = _xDistance;

		if (label && label->init())
		{
			label->setCascadeOpacityEnabled(true);
			label->addChild(_titleLabel);
			label->addChild(_valueLabel);
			label->particalAnimation = cocos2d::ParticleSystemQuad::create("animation/particle_dailybonuswheel_show_text.plist");
			label->particalAnimation->stop();
			label->addChild(label->particalAnimation);
			label->resetPosTitleAndValueLabel();
			label->autorelease();
			return label;
		}
		CC_SAFE_DELETE(label);
		return nullptr;
	}
	cocos2d::Label *getTitleLabel() {
		return this->titleLabel;
	}
	cocos2d::Label *getValueLabel() {
		return this->valueLabel;
	}
	void resetPosTitleAndValueLabel() {
		this->titleLabel->setPosition(cocos2d::Vec2(
			-getContentSize().width / 2,
			this->titleLabel->getPositionY()
		));
		this->valueLabel->setPosition(cocos2d::Vec2(
			this->titleLabel->getPositionX() + this->titleLabel->getContentSize().width + xDistance,
			this->valueLabel->getPositionY()
		));
		this->particalAnimation->setPosVar(
			cocos2d::Vec2(this->getContentSize().width * 0.5f, this->particalAnimation->getPosVar().y / 2)
		);
		this->particalAnimation->setGravity(cocos2d::Vec2(50, 50));
		this->particalAnimation->setStartSize(40);
		this->particalAnimation->setEndSize(10);
		this->particalAnimation->setEmissionRate(1200);
		this->particalAnimation->setPosition(0, 0);
	}
	virtual cocos2d::Size getContentSize() {
		return cocos2d::Size(this->titleLabel->getContentSize().width + this->valueLabel->getContentSize().width + xDistance,
			this->titleLabel->getContentSize().height);
	}
	/// <summary>
	/// animation show info
	/// </summary>
	void resetPosAndShowWithPartical() {
		this->resetPosTitleAndValueLabel();
		this->setVisible(true);
		this->titleLabel->runAction(cocos2d::FadeIn::create(0.1f));
		this->valueLabel->runAction(cocos2d::FadeIn::create(0.1f));
		this->particalAnimation->start();
	}
	void setOpacityForLabels(float opacity) {
		this->titleLabel->setOpacity(opacity);
		this->valueLabel->setOpacity(opacity);
	}
};
class DailyBonusWheelPopup;
class DailyBonusWheelResultPopup : public BasePopup
{
private:
	TitleValueLabel *wheelBonusLabel;
	TitleValueLabel *levelBonusLabel;
	TitleValueLabel *friendBonusLabel;
	TitleValueLabel *vipLabel;

	cocos2d::Sprite *coinSprite;
	cocos2d::Label *totalCoinLabel;

	cocos2d::Node *lensFlareYellowGroup;
	cocos2d::Node *lensFlareWhiteGroup;

	cocos2d::ui::Button *collectButton;

	DailyBonusWheelPopup *_parent;
public:
	/// <summary>
	/// create popup with parent UI
	/// </summary>
	/// <param name="parent"></param>
	/// <returns></returns>
	static DailyBonusWheelResultPopup* create(DailyBonusWheelPopup *parent);

	/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();
	/// <summary>
	/// reset UI
	/// </summary>
	virtual void reset() override;

	/**
	* 2017-03-04: Kiet: prepare and show popup with parent
	*/
	void prepareAndShow();
};