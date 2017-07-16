#include "LoadingAnimation.h"
#include "Constant/Defination.h"
#include "Constant/PPEnums.h"
#include "Configs.h"
#include "Helper/AnimationHelper.h"
#include "Helper/Helper4Scene.h"

USING_NS_CC;
using namespace std;

bool LoadingAnimation::init()
{
	if (!BasePopup::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//LOADING SPRITE + PLISH TO CACHE
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_LOADNING_ANIMATION_LOGIN);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_LOADNING_ANIMATION_LOBBY);

	this->loadingAnimationLogin = Sprite::createWithSpriteFrameName("Layer 1");
	this->loadingAnimationLogin->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(this->loadingAnimationLogin);

	this->loadingAnimationLobby = Sprite::createWithSpriteFrameName("loading-icon_1");
	this->loadingAnimationLobby->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));
	this->addChild(this->loadingAnimationLobby);
	return true;
}
void LoadingAnimation::prepareAndShow(
	cocos2d::Node* parent
)
{
	if (!this || !parent) {
		return;
	}
	auto tagCurrentScene = Helper4Scene::getRunningScene()->getTag();
	switch (tagCurrentScene)
	{
		case ppEnum::GameScene::Login:
		{
			if (this->loadingAnimationLogin->getNumberOfRunningActions() <= 0)
			{
				auto actionLoadingLogin =
					AnimationHelper::getInstance()->createAnimationByFrameName(
						PLIST_LOADNING_ANIMATION_LOGIN, "Layer %i", 1, 20, 20, kRepeatForever);
				this->loadingAnimationLogin->runAction(actionLoadingLogin);
			}
			this->loadingAnimationLogin->setVisible(true);
			this->loadingAnimationLobby->setVisible(false);
			break;
		}
	default:
	{
		if (this->loadingAnimationLobby->getNumberOfRunningActions() <= 0)
		{
			auto actionLoadingLobby =
				AnimationHelper::getInstance()->createAnimationByFrameName(
					PLIST_LOADNING_ANIMATION_LOBBY, "loading-icon_%i", 1, 11, 20, kRepeatForever);
			this->loadingAnimationLobby->runAction(actionLoadingLobby);
		}
		this->loadingAnimationLogin->setVisible(false);
		this->loadingAnimationLobby->setVisible(true);
		break;
	}
	}
	this->setPosition(-parent->getPosition());
	BasePopup::show(parent, false);
	this->setLocalZOrder(INT_MAX);
}


void LoadingAnimation::showLoadingAnimationLogin(cocos2d::Node* parent){
    if (!this || !parent) {
        return;
    }
    if (this->loadingAnimationLogin->getNumberOfRunningActions() <= 0)
    {
        auto actionLoadingLogin =
        AnimationHelper::getInstance()->createAnimationByFrameName(
                                                                   PLIST_LOADNING_ANIMATION_LOGIN, "Layer %i", 1, 20, 20, kRepeatForever);
        this->loadingAnimationLogin->runAction(actionLoadingLogin);
    }
    this->loadingAnimationLogin->setVisible(true);
    this->loadingAnimationLobby->setVisible(false);
    this->setPosition(-parent->getPosition());
    BasePopup::show(parent, false);
    this->setLocalZOrder(INT_MAX);
}
