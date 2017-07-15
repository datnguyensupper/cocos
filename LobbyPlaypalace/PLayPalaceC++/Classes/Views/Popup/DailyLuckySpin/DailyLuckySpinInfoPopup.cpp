#include "DailyLuckySpinInfoPopup.h"
#include "Constant/Defination.h"
#include "Constant/LanguageConstant.h"

USING_NS_CC;
using namespace std;

bool DailyLuckySpinInfoPopup::init()
{
	if (!BasePopup::init()) return false;

	auto bg = Sprite::createWithSpriteFrameName(FRAME_DAILY_LUCKY_SPIN_BG);
	bg->setPosition(origin + visibleSize / 2);
	bg->setContentSize(Size(bg->getContentSize().width * 1.1f, bg->getContentSize().height * 1.3f));
	this->addChild(bg);

	auto title = Sprite::createWithSpriteFrameName(FRAME_DAILY_LUCKY_SPIN_INFO_TITLE);
	title->setPosition(bg->getPosition() + Vec2(0, bg->getContentSize().height * 0.44f));
	this->addChild(title);

	string strInfo = "-Coin payout = (Sum value of three columns) x 3000.\n-Crown reward: If three columns have same value, you will receive 1 crown.\n-Example:";

	auto infoText = Label::createWithTTF(strInfo, FONT_PassionOne_Regular, 42);
	infoText->setPosition(bg->getPosition() + Vec2(0, bg->getContentSize().height / 4.5f));
	infoText->setDimensions(bg->getContentSize().width * 5 / 6.0f, 0);
	this->addChild(infoText);

	auto tableBG = Sprite::createWithSpriteFrameName(FRAME_DAILY_LUCKY_SPIN_INFO_TABLE);
	tableBG->setPosition(bg->getPosition() - Vec2(0, bg->getContentSize().height / 9));
	tableBG->setCascadeOpacityEnabled(true);
	this->addChild(tableBG);

	std::vector<std::vector<string>> data = { 
		{"Spin Result", "7 - 7 - 7", "7 - 8 - 9"},
		{ "Coin Reward", "63,000", "72,000" },
		{ "Crown Reward", "1", "0" }
	};

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			auto text = Label::createWithTTF(strInfo, FONT_PassionOne_Regular, 42);
			text->setString(data[i][j]);
			text->setPosition(tableBG->getContentSize().width / 6 + i * tableBG->getContentSize().width / 3,
				tableBG->getContentSize().height * 5 / 6 - j * tableBG->getContentSize().height / 3);
			tableBG->addChild(text);
		}
	}

	auto btnOK = this->createButtonWithFrameName(PNG_FRAME_GREEN_POPUP_BUTTON_NEW, Language(nullptr, LanguageConstant::OK));
	btnOK->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->hide();
	});
	btnOK->setPosition(bg->getPosition() - Vec2(0, bg->getContentSize().height * 0.35f));
	this->addChild(btnOK);

	return true;
}

void DailyLuckySpinInfoPopup::prepareAndShow(cocos2d::Node * parent)
{
	BasePopup::show(parent);
}
