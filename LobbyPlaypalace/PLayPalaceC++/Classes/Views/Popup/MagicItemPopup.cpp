#include "MagicItemPopup.h"
#include "Manager/InfoManager.h"
#include "Info/AdditionalInfo.h"
#include "Util/UtilFunction.h"
#include "Views/Lobby/header/HeaderMagicItemBtn.h"
#include "Configs.h"
USING_NS_CC;
using namespace std;
#define TAIL_MAGIC_ITEM_REMAINING " left"

bool MagicItemPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	auto bg = Sprite::create(PNG_NOTIFICATION_POPUP_BACKGROUND);
	bg->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	bg->setCascadeOpacityEnabled(true);
	this->addChild(bg);

	this->magicItemIcon = HeaderMagicItemBtn::create();
	this->magicItemIcon->setCascadeOpacityEnabled(true);
	this->magicItemIcon->setPosition(bg->getContentSize() / 2 + Size(0, 50));
	bg->addChild(this->magicItemIcon);

	this->leftSpinOfTimeLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 56),
		"3 spin left",
		TextHAlignment::CENTER
	);
	this->leftSpinOfTimeLabel->setPosition(bg->getContentSize() / 2 + Size(0, -80));
	bg->addChild(this->leftSpinOfTimeLabel);

	//CLOSE BUTTON
	auto exitButton = BasePopup::createCloseButton();
	exitButton->setPosition(Vec2(
		origin.x + visibleSize.width / 2 + bg->getContentSize().width / 2.1f,
		origin.y + visibleSize.height / 2 + bg->getContentSize().height / 2.3f
	));
	this->addChild(exitButton);

	return true;
}

void MagicItemPopup::prepareAndShow(cocos2d::Node * parent)
{
	auto magicItemInfo = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo;
	std::string remainingString = "";
	switch (magicItemInfo->activeMagicItemType)
	{
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN:
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItem100PercentBigWin)
			+ (magicItemInfo->remainingSpinOfMagicItem100PercentBigWin > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN:
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItem100PercentMegaWin)
			+ (magicItemInfo->remainingSpinOfMagicItem100PercentMegaWin > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1:
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItemLuckySpinType1)
			+ (magicItemInfo->remainingSpinOfMagicItemLuckySpinType1 > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2:
		remainingString = ToString(magicItemInfo->remainingSpinOfMagicItemLuckySpinType2)
			+ (magicItemInfo->remainingSpinOfMagicItemLuckySpinType2 > 1 ? " spins " : " spin ")
			+ TAIL_MAGIC_ITEM_REMAINING;
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DOUBLE_EXP:
		remainingString = UtilFunction::timeStampToSimpleString(magicItemInfo->remainingTimeOfMagicItemDoubleExp) + TAIL_MAGIC_ITEM_REMAINING;
		break;
	case LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_LUCKY_SYMBOL:
		remainingString = UtilFunction::timeStampToSimpleString(magicItemInfo->remainingTimeOfMagicItemLuckySymbol) + TAIL_MAGIC_ITEM_REMAINING;
		break;
	default:
		return;
	}
	BasePopup::showWithQueue(parent);
	this->magicItemIcon->changeItemType(static_cast<LobbyConstant::MagicItemType>(magicItemInfo->activeMagicItemType));
	this->leftSpinOfTimeLabel->setString(remainingString);
}

