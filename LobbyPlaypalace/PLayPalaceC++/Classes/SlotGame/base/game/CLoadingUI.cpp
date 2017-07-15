#include "CLoadingUI.h"
#include "CMainBase.h"
#include "../settings/CSettings.h"
#include "../utils/CSpriteButton.h"
#include "Util/CLoader.h"
#include "../utils/GameUtils.h"
#include "../constant/GameConstant.h"
#include "Constant/Defination.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
namespace GameSlot {
	CLoadingUI::CLoadingUI(CMainBase * oMain): Node(),
		oMain(oMain)
	{
		this->autorelease();
	}
	// on "init" you need to initialize your instance
	bool CLoadingUI::init()
	{
		//////////////////////////////
		// 1. super init first
		if (!Node::init())
		{
			return false;
		}
		this->loaderGroup = Node::create();
		this->loaderGroup->setCascadeOpacityEnabled(true);
		GameUtils::centerNode(this->loaderGroup);

		auto resLoader = GameConstant::getInstance()->getResources().loader;

		this->bg = CSpriteButton::createButtonWithFile(resLoader["bg"], nullptr, nullptr);
		((CSpriteButton*)this->bg)->setIsBlock(true);

		this->loaderIcon = Helper4Sprite::createOptimizeSprite(resLoader["icon"]);
		this->loaderIcon->setScale(3);
		this->loaderIcon->setPositionY(-CSettings::CANVAS_HEIGHT / 2.4f);

		this->label = Label::createWithTTF("1%", FONT_PassionOne_Regular, 40);
		this->label->setPositionY(this->loaderIcon->getPositionY());

		this->loaderGroup->addChild(this->bg);
		this->loaderGroup->addChild(this->loaderIcon);
		this->loaderGroup->addChild(this->label);

		this->addChild(this->loaderGroup, ORDER_LOADING);

		return true;
	}

	void CLoadingUI::showLoading(int progress)
	{
		auto scene = this->oMain->getScene();
		if (scene) {
			scene->setHeaderVisible(false);
		}
		this->loaderGroup->setOpacity(255);
		this->loaderGroup->setVisible(true);

		this->label->setString(ToString(min(progress, 99)) + "%");
		if (this->loaderIcon->getNumberOfRunningActions() == 0) {
			this->loaderIcon->stopAllActions();
			this->loaderIcon->runAction(RepeatForever::create(RotateBy::create(0.1f, 60)));
		}
	}

	void CLoadingUI::hideLoading(const std::function<void()>& callback)
	{
		this->loaderGroup->runAction(Sequence::create(
			DelayTime::create(0.5f),
			CallFunc::create([this]() {
			this->label->setString("100%");
		}),
			FadeOut::create(0.5f),
			CallFunc::create([this, callback](){
			if (callback != nullptr) {
				callback();
			}
			auto scene = this->oMain->getScene();
			if (scene) {
				scene->setHeaderVisible(true);
			}
			this->loaderIcon->stopAllActions();
			this->loaderGroup->setVisible(false);
		}), NULL));
	}

	void CLoadingUI::startLoading(float dt)
	{
		auto scene = this->oMain->getScene();
		if (scene) {
			scene->setHeaderVisible(false);
		}
		CLoader::getInstance()->startLoadingResources(
			this->aResources,
			this->callbackComplete,
			[this](float progress) {
			this->label->setString(ToString((int)(progress * 100)) + "%");
		}, bLoadMainThread);
	}

	void CLoadingUI::setBackgroundLoading(const std::string& fileName)
	{
		if (this->bg) {
			if (fileName.empty() || TextureCache::getInstance()->getTextureForKey(fileName) == nullptr) return;
			this->bg->setTexture(fileName);
		}
	}

	void CLoadingUI::preload(const vector<std::string>& aResources, const std::function<void()>& callbackComplete, bool bLoadMainThread) {
		this->showLoading(1);
		this->aResources = aResources;
		this->callbackComplete = callbackComplete;
		this->bLoadMainThread = bLoadMainThread;
		if (this->aResources.empty()) {
            callbackComplete();
			return;
		}
		this->scheduleOnce(schedule_selector(CLoadingUI::startLoading), 0.25f);
	}
}
