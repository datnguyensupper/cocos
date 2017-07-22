#include "GameSlotScene.h"

#include "Constant/Defination.h"
#include "Constant/PPEnums.h"

#include "SlotGame/nezha/game/CMainLN.h"
#include "SlotGame/deepblue/game/CMainDB.h"
#include "SlotGame/goldenegg/game/CMainGE.h"
#include "SlotGame/pharaoh/game/CMainPO.h"
#include "SlotGame/boxing/game/CMainBO.h"
#include "SlotGame/romanempire/game/CMainRE.h"

#include "SlotGame/base/game/CGameBase.h"

#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Popup/LevelUpPopup.h"
#include "Views/Popup/GameUnlockedPopup.h"
#include "Views/Popup/MissingPopup.h"

#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/NetworkManager.h"
#if IS_DEBUG
#include "Manager/Test/TestManager.h"
#endif

#include "Info/AdditionalInfo.h"

#include "Helper/Helper4Scene.h"

USING_NS_CC;
namespace GameSlot {

	static bool isReleased = true;
	GameSlotScene* GameSlotScene::showGame(long gameOrderID)
	{
		if (!isReleased) {
			return nullptr;
		}
		isReleased = false;

		CMainBase* oMain = nullptr;
		switch (gameOrderID)
		{
		case ppEnum::GameSlotOrderId::NEZHA:
			oMain = CMainLN::create();
			break;
		case ppEnum::GameSlotOrderId::GOLDEN_EGGS:
			oMain = CMainGE::create();
			break;
		case ppEnum::GameSlotOrderId::PHARAOH:
			oMain = CMainPO::create();
			break;
		case ppEnum::GameSlotOrderId::BOXING:
			oMain = CMainBO::create();
			break;
		case ppEnum::GameSlotOrderId::ROMAN_EMPIRE:
			oMain = CMainRE::create();
			break;
		case ppEnum::GameSlotOrderId::CANDYLICIOUS:
			break;
		case ppEnum::GameSlotOrderId::FRUITILICIOUS:
			break;
		case ppEnum::GameSlotOrderId::KPOP:
			break;
		case ppEnum::GameSlotOrderId::LITTLE_MONSTERS:
			break;
		case ppEnum::GameSlotOrderId::MAFIA:
			break;
		case ppEnum::GameSlotOrderId::SHERLOCK:
			break;
		case ppEnum::GameSlotOrderId::MAGIC_QUEST:
			break;
		case ppEnum::GameSlotOrderId::BIKINI_BEACH:
			break;
		case ppEnum::GameSlotOrderId::FOUR_BEAUTIES:
			break;
		case ppEnum::GameSlotOrderId::ZEUS:
			break;
		case ppEnum::GameSlotOrderId::DEEP_BLUE:
			oMain = CMainDB::create();
			break;
		default:
			break;
		}

		if (oMain) {
			GameSlotScene* oScene = new GameSlotScene();
			oScene->autorelease();
			oScene->initSceneWithGame(oMain);
			//go to init session scene
			Director::getInstance()->replaceScene(
				TransitionFade::create(
					Configs::TIME_TRANSITION_FADE_SCENE,
					oScene
					)
				);
			return oScene;
		}
		return nullptr;
	}

	void GameSlotScene::initSceneWithGame(CMainBase * oMainGame)
	{
        BaseScene::init();
		this->setTag(ppEnum::GameScene::GameSlot);

		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

		this->oMainGame = oMainGame;
		this->oMainGame->setScene(this);

		this->oHeader = PopupManager::getInstance()->getHeaderLobbyLayout();
		this->oHeader->setPosition(Vec2(70, visibleSize.height - 60));
		this->setHeaderVisible(false);

		this->addChild(oMainGame);
		if (this->oHeader->getParent())
		{
			this->oHeader->getParent()->removeChild(this->oHeader);
		}
		this->addChild(this->oHeader);
		this->oHeader->onChangeScene(ppEnum::GameScene::GameSlot);

		PopupManager::getInstance()->getLevelUpPopup()->setGame(this);


#if IS_DEBUG
		TestManager::getInstance()->createTestButton(this);
#endif
	}

	void GameSlotScene::setHeaderVisible(bool isVisible)
	{
		this->oHeader->setVisible(isVisible);
	}
	bool GameSlotScene::checkCanSpin()
	{
        
		if (this->isLevelUp) return false;

#if IS_RUN_WITHOUT_NW
        return true;
#endif

        
		//auto missingCoin = this->oMainGame->getTotalBet() - InfoManager::getInstance()->getUserInfo()->coin;
		auto missingCoin = this->oMainGame->getTotalBet() - PopupManager::getInstance()->getHeaderLobbyLayout()->getCoinInHeaderUI();
		if (missingCoin > 0) {
			//Show Popup Missing Coin
			//PopupManager::getInstance()->getNotificationPopup()->showPopupMissingCoin(this, missingCoin);
			PopupManager::getInstance()->getMissingPopup()->prepareAndShow(this, ppEnum::PPCurrency::COIN_CURRENCY, missingCoin);
			this->oMainGame->getGame()->setAutoSpin(false);
			this->oMainGame->getGame()->resetReel();
			this->oMainGame->getGame()->setState(GAME_STATE::GAME_IDLE);
			this->oMainGame->getGame()->getInterface()->setFooterEnabled(true);
			return false;
		}
		return true;
	}
	void GameSlotScene::onLevelUpCollected(double coinReward, double crownReward)
	{
		this->isLevelUp = false;

		//update user info coin + crown 
		InfoManager::getInstance()->getUserInfo()->coin += coinReward;
		InfoManager::getInstance()->getUserInfo()->crown += crownReward;

		this->oHeader->increaseCoin(coinReward);
		this->oHeader->increaseCrown(crownReward);


		auto oGame = this->oMainGame->getGame();

		if (oGame->isAutoSpin() && 
			!oGame->isBonus() && 
			oGame->getCurrentType() == GAME_TYPE::MAIN_GAME &&
			oGame->getCurrentState() != GAME_STATE::GAME_SHOW_WIN) {
			oGame->onAutoSpin(0);
		}
	}
	void GameSlotScene::onBeginGame()
	{
		for (auto listener : _aEventListener) {
			listener(this, GameEventListenerType::BeginGame);
		}
	}
	void GameSlotScene::onFinishGame()
	{
		for (auto listener : _aEventListener) {
			listener(this, GameEventListenerType::FinishGame);
		}
	}
	void GameSlotScene::onBeginSpin()
	{
		this->oHeader->decreaseCoin(this->oMainGame->getTotalBet(), true);
		for (auto listener : _aEventListener) {
			listener(this, GameEventListenerType::BeginSpin);
		}
	}
	void GameSlotScene::onFinishSpin(const std::function<void()>& cb)
	{
		this->oMainGame->setUpdateUserInfo(false);

		this->oHeader->reloadUIHeaderAndCheckShowPopupLevelUp([this, cb](bool isSuccess, LevelUpInfo* levelUpInfo) {
			if (Helper4Scene::getRunningScene()->getTag() != ppEnum::GameScene::GameSlot) return;
			this->onReloadData(cb, isSuccess, levelUpInfo);

			for (auto listener : _aEventListener) {
				listener(this, GameEventListenerType::FinishSpin);
			}
		});
	}
	void GameSlotScene::onBeginBonus()
	{
		for (auto listener : _aEventListener) {
			listener(this, GameEventListenerType::BeginBonus);
		}
	}
	void GameSlotScene::onFinishBonus(const std::function<void()>& cb)
	{
		this->oHeader->reloadUIHeaderAndCheckShowPopupLevelUp([this, cb](bool isSuccess, LevelUpInfo* levelUpInfo) {
			if (Helper4Scene::getRunningScene()->getTag() != ppEnum::GameScene::GameSlot) return;
			this->onReloadData(cb, isSuccess, levelUpInfo);

			for (auto listener : _aEventListener) {
				listener(this, GameEventListenerType::FinishBonus);
			}
		});
	}

	void GameSlotScene::onReloadData(const std::function<void()>& cb, bool isSuccess, LevelUpInfo * levelUpInfo)
	{
		if (!this->isInGame()) return;
		if (isSuccess) {
			if (levelUpInfo) {
				this->isLevelUp = true;

				PopupManager::getInstance()->getLevelUpPopup()->prepareAndShow(
					levelUpInfo->currentLevel + 1,
					levelUpInfo->newLevel + 1,
					levelUpInfo->coinReward,
					levelUpInfo->crownReward,
					InfoManager::getInstance()->getAdditionalInfo()->boosterInfo->remainingTimeOfBoosterLevelUpBonus > 0,
					((levelUpInfo->newLevel + 1) % 10) == 0
					);

				int currentLevel = levelUpInfo->newLevel + 1;
				int oldLevel = levelUpInfo->currentLevel + 1;
				InfoManager::getInstance()->reloadServerSlotGameInfoList([this, cb, currentLevel, oldLevel](const std::deque<ServerSlotGameInfo*>& listNewGameUnlocked) {
					if (listNewGameUnlocked.size() > 0) {
						PopupManager::getInstance()->getGameUnlockedPopup()->prepareAndShow(listNewGameUnlocked, this);
					}

					auto checkFeatureAlreadyUnlocked = [currentLevel, oldLevel](std::string featureName)
					{
						auto levelToUnlock = 0;
						if (featureName == LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE) {
							levelToUnlock = InfoManager::getInstance()->getUnlockFeatureByLevelConfig().choosePayLine;
						}
						else if (featureName == LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE) {
							levelToUnlock = InfoManager::getInstance()->getUnlockFeatureByLevelConfig().dailyChallenge;
						}
						else if (featureName == LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK) {
							levelToUnlock = InfoManager::getInstance()->getUnlockFeatureByLevelConfig().piggyBank;
						}
						else
						{
							return false;
						}
						return currentLevel >= levelToUnlock && oldLevel < levelToUnlock;
					};
					std::deque<std::string> listNewFeatureByLevel;
					if (checkFeatureAlreadyUnlocked(LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE))
					{
						listNewFeatureByLevel.push_back(LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE);
					}
					if (checkFeatureAlreadyUnlocked(LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE))
					{
						listNewFeatureByLevel.push_back(LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE);
					}
					if (checkFeatureAlreadyUnlocked(LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK))
					{
						listNewFeatureByLevel.push_back(LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK);
					}
					std::sort(
						listNewFeatureByLevel.begin(),
						listNewFeatureByLevel.end(),
						[](std::string feature1, std::string feature2) 
					{ 
						auto getLevelToUnlockByFeatureName = [](std::string featureName)
						{
							if (featureName == LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE) {
								return InfoManager::getInstance()->getUnlockFeatureByLevelConfig().choosePayLine;
							}
							else if (featureName == LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE) {
								return InfoManager::getInstance()->getUnlockFeatureByLevelConfig().dailyChallenge;
							}
							else if (featureName == LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK) {
								return InfoManager::getInstance()->getUnlockFeatureByLevelConfig().piggyBank;
							}
							return 0;
						};
						return getLevelToUnlockByFeatureName(feature1) < getLevelToUnlockByFeatureName(feature1);
					});

					PopupManager::getInstance()->getGameUnlockedPopup()->prepareAndShow(listNewFeatureByLevel, this);
				});
			}


			this->oMainGame->setUpdateUserInfo(true);
			if (cb) {
				cb();
			}
		}
	}

	void GameSlotScene::onExit()
	{
		this->onFinishGame();

		AnimationHelper::getInstance()->release();
		Scene::onExit();
		Manager4Network::getInstance()->release();
		Manager4Sound::getInstance()->release();
		GameConstant::getInstance()->release();
		CSlotSettings::getInstance()->release();

		isReleased = true;
	}
	void GameSlotScene::addGameEventListener(const std::function<void(GameSlotScene*, GameEventListenerType)>& listener)
	{
		if (listener) {
			_aEventListener.push_back(listener);
		}
	}
	bool GameSlotScene::isInGame()
	{
		return Helper4Scene::getRunningScene()->getTag() == ppEnum::GameScene::GameSlot;
	}
	void GameSlotScene::menuCloseCallback(Ref* pSender)
	{
		//Close the cocos2d-x game scene and quit the application
		Director::getInstance()->end();
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
		
		/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
		
		//EventCustom customEndEvent("game_scene_close_event");
		//_eventDispatcher->dispatchEvent(&customEndEvent);
	}
}
