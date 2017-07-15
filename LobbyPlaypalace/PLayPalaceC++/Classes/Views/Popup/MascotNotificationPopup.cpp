#include "MascotNotificationPopup.h"
#include "Constant/Defination.h"
#include "Manager/SoundManager.h"


USING_NS_CC;

bool MascotNotificationPopup::init()
{
	if (!Node::init()) return false;

	this->bg = Sprite::create(PNG_MASCOT_NOTI_BG);
	this->bg->setScale(1.25f);
	this->addChild(this->bg);

	this->txtMessage = Label::createWithTTF("", FONT_PassionOne_Regular, 40);
	this->txtMessage->setDimensions(this->bg->getContentSize().width * this->bg->getScale() * 4 / 5.0f, this->bg->getContentSize().height);
	this->txtMessage->setPosition(0, this->bg->getContentSize().height / 8);
	this->txtMessage->setHorizontalAlignment(TextHAlignment::CENTER);
	this->txtMessage->setVerticalAlignment(TextVAlignment::CENTER);
	this->addChild(this->txtMessage);

	this->setCascadeOpacityEnabled(true);
	this->setVisible(false);

	return true;
}

void MascotNotificationPopup::show(cocos2d::Node* parent, const std::string& message, cocos2d::Vec2 pos)
{
	if (pos == Vec2::ZERO) {
		pos = Director::getInstance()->getVisibleOrigin() + Vec2(Director::getInstance()->getVisibleSize().width / 4,
			Director::getInstance()->getVisibleSize().height * 4 / 5.0f);
	}
	this->setPosition(pos);
	if (this->getParent() != parent) {
		this->removeFromParent();
		parent->addChild(this);
	}

	this->txtMessage->setString(message);

	this->setOpacity(0);
	this->txtMessage->setOpacity(0);
	this->setScale(1);
	this->txtMessage->setScale(1);

	this->stopAllActions();
	this->txtMessage->stopAllActions();

	this->runAction(FadeIn::create(0.2f));
	this->runAction(Sequence::create(
		ScaleTo::create(0.05f, 1.5f),
		ScaleTo::create(0.05f, 0.8f),
		ScaleTo::create(0.05f, 1.3f),
		ScaleTo::create(0.05f, 0.9f),
		ScaleTo::create(0.05f, 1.1f),
		ScaleTo::create(0.05f, 1),
		CallFunc::create([this]() {
		this->txtMessage->runAction(FadeIn::create(0.1f));
		this->txtMessage->runAction(Sequence::create(
			ScaleTo::create(0.15f, 1.3f),
			ScaleTo::create(0.15f, 1.0f),
			DelayTime::create(0.5f),
			CallFunc::create([this]() {
			this->runAction(Sequence::createWithTwoActions(
				FadeOut::create(0.2f), 
				CallFunc::create([this]() { 
				this->setVisible(false); 
			})));
		}), NULL));
	}), NULL));

	SoundManager::getInstance()->stopSound(soundEffect);
	soundEffect = SoundManager::getInstance()->playSoundEffectMascotNoti();
	this->setVisible(true);
}
