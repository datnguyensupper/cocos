#include "DailyBonusWheelPopup.h"
#include "DailyBonusWheelResultPopup.h"
#include "DailyBonusWheelSpinPopup.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Info/AdditionalInfo.h"
#include "Helper/Helper4Scene.h"

USING_NS_CC;

bool DailyBonusWheelPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}
	

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("popup/dailyBonusWheel/dailyBonusWheel.plist");

	this->wheelPopup = DailyBonusWheelSpinPopup::create(this);
	this->wheelPopup->retain();
	//this->wheelPopup->setVisible(true);
	//this->wheelPopup->setOpacity(1);
	//this->addChild(this->wheelPopup);


	this->resultPopup = DailyBonusWheelResultPopup::create(this);
	this->resultPopup->retain();
	//this->resultPopup->setVisible(true);
	//this->resultPopup->setOpacity(1);
	//this->addChild(this->resultPopup);
	return true;
}

void DailyBonusWheelPopup::reset()
{
	BasePopup::reset();
	this->wheelPopup->reset();
	this->resultPopup->reset();
}

void DailyBonusWheelPopup::show()
{
	BasePopup::show();
	this->wheelPopup->prepareAndShow();
}

void DailyBonusWheelPopup::processAfterSpin()
{
	this->resultPopup->prepareAndShow();
}

void DailyBonusWheelPopup::collectCoin(Vec2 worldBtnPos)
{
	auto coinIncrease = InfoManager::getInstance()->getAdditionalInfo()->dailyBonusWheelInfo->totalCoin;
	PopupManager::getInstance()->getHeaderLobbyLayout()->increaseCoin(coinIncrease);
	AnimationCoinCrown::create(
		Helper4Scene::getRunningScene(),
		worldBtnPos,
		coinIncrease
	);
	this->hide();
}

void DailyBonusWheelPopup::prepareAndShow(cocos2d::Node * parent)
{
	////DEBUG VALUES
	//auto dailyBonusWheelInfo = InfoManager::getInstance()->getAdditionalInfo()->dailyBonusWheelInfo;
	//dailyBonusWheelInfo->canCollect = false;
	//dailyBonusWheelInfo->box = 1;
	//dailyBonusWheelInfo->coin = 50;
	//dailyBonusWheelInfo->coinPerFriend = 700;
	//dailyBonusWheelInfo->factor = 4;
	//dailyBonusWheelInfo->levelBonus = 34000;
	//dailyBonusWheelInfo->numberOfFriend = 8;
	//dailyBonusWheelInfo->totalCoin = 40920;
	//dailyBonusWheelInfo->vipBenefit = 1.2f;

	BasePopup::showWithQueue(parent);
	if (this->darkLayer)
	{
		this->darkLayer->setOpacity(0);
	}
}
