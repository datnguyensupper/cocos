#include "Tutorial.h"
#include "Util/UtilFunction.h"
#include "Constant/Defination.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PluginManager.h"
#include "Manager/ScaleManager.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Lobby/bottom/BottomLobbyLayout.h"
#include "Views/Popup/Achievement/AchievementPopup.h"
#include "Views/Popup/Shop/ShopPopup.h"
#include "Views/Popup/Shop/PurchaseItemNode.h"
#include "Views/Effects/AnimationCoinCrown.h"
#include "Scene/LobbyScene.h"
#include "Scene/LoginScene.h"
#include "SlotGame/base/game/CMainBase.h"
#include "SlotGame/base/game/CGameBase.h"
#include "SlotGame/base/interfaceUI/CInterfaceBase.h"
#include "SlotGame/base/interfaceUI/CFooter.h"
#include "Helper/Helper4Scene.h"
#include "Helper/Helper4Sprite.h"
#include "Custom/Common/LabelAutoSize.h"

USING_NS_CC;

#define WELCOME_REWARD_COIN 100000
#define FADE_TUTORIAL_DURATION 0.6f
bool Welcome::init()
{
	if (!Node::init()) return false;

	auto origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();

	auto oDarklayer = UtilFunction::createDarkLayer();

	auto oBG = Helper4Sprite::createOptimizeSprite(PNG_LOBBY_BACKGROUND);
	oBG->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	auto oModel = Helper4Sprite::createOptimizeSprite(PNG_BODY_GIRL_MODEL);
	oModel->setAnchorPoint(Vec2(0.5, 0));

	cocos2d::Vec2 moveRight =  oBG->getPosition();
	oModel->setScale(ScaleManager::getInstance()->getLookGoodScaleDownRatio());
	oModel->setPosition(origin.x + oModel->getContentSize().width*oModel->getScale() / 2 + 100 * scaleDownRatio, origin.y);
	if (scaleDownRatio < 0.8) {
		moveRight = Vec2(visibleSize.width - (visibleSize.width - (oModel->getPosition().x - origin.x + oModel->getContentSize().width*oModel->getScale() / 2-100 * scaleDownRatio)) / 2 + origin.x, oBG->getPosition().y);
	}
	



	auto oInfo = Label::createWithTTF(
		"Here is " + UtilFunction::FormatWithCommas(WELCOME_REWARD_COIN) + " bonus\n to get you started!", 
		FONT_PassionOne_Bold,
		50);
	oInfo->setHorizontalAlignment(TextHAlignment::CENTER);
	oInfo->setPosition(moveRight);

	lb_welcome = LabelAutoSize::createWithTTF("WELCOME, " +InfoManager::getInstance()->getUserInfo()->name+ "!",FONT_PassionOne_Bold,75);
	((LabelAutoSize*)lb_welcome)->setAutoFitType(LabelAutoFitType::TrimString);
	((LabelAutoSize*)lb_welcome)->setTextAreaSize(Size(800, 0));


	/*auto oTitle = Label::createWithTTF("WELCOME, " +UtilFunction::trimStringAndAdd3Dots(InfoManager::getInstance()->getUserInfo()->name, 13)+ "!",FONT_PassionOne_Bold,75);*/
	lb_welcome->setHorizontalAlignment(TextHAlignment::CENTER);
	lb_welcome->setTextColor(Color4B(255, 210, 77, 255));
	lb_welcome->setPosition(Vec2(0, 100) + moveRight);

	oClaimBtn = UtilFunction::createButtonWithText(PNG_FRAME_GREEN_LONG_POPUP_BUTTON,
		"", "", ui::Widget::TextureResType::PLIST,
		"Claim " + UtilFunction::FormatWithCommas(WELCOME_REWARD_COIN) + "!", 50);
	oClaimBtn->setPosition(oInfo->getPosition() - Vec2(0, 150));


	this->addChild(oBG);
	this->addChild(oDarklayer);
	this->addChild(oModel);
	this->addChild(lb_welcome);
	this->addChild(oInfo);
	this->addChild(oClaimBtn);

	return true;
}


void Welcome::updateWelcomeText() {

	UtilFunction::detectFontAndSetStringForLabel(lb_welcome, FONT_PassionOne_Regular, "WELCOME, " + InfoManager::getInstance()->getUserInfo()->name);
}

void Welcome::addOnClaimListener(const std::function<void(cocos2d::Ref*sender, cocos2d::ui::Widget::TouchEventType type)>& claimCallBack)
{
	oClaimBtn->addTouchEventListener(claimCallBack);
}


static Tutorial* s_instance = nullptr;

Tutorial* Tutorial::getInstance()
{
	if (!s_instance) {
		s_instance = new Tutorial();
	}
	return s_instance;
}

Tutorial::Tutorial():Node(),
userInfo(nullptr),
oHeaderUI(nullptr),
oWelcome(nullptr),
bActive(false),
bInited(false){
	updateReference();
}

Tutorial::~Tutorial()
{
}

bool Tutorial::init()
{
	updateReference();
	if (this->bInited) return false;

	this->oTutorial = Node::create();
	this->addChild(oTutorial);

	this->setCascadeOpacityEnabled(true);
	this->oTutorial->setCascadeOpacityEnabled(true);

	origin = Director::getInstance()->getVisibleOrigin();
	visibleSize = Director::getInstance()->getVisibleSize();
	scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();

	this->oStencil = DrawNode::create();

	//init farklayer and circle mask
	ClippingNode* clipper = ClippingNode::create();
	clipper->setCascadeOpacityEnabled(true);
	clipper->setInverted(true);
	clipper->setStencil(this->oStencil);

	auto darkLayer = UtilFunction::createDarkLayer(200, CC_CALLBACK_2(Tutorial::onTouched, this));
	clipper->addChild(darkLayer);

	//int model
	this->oModel = Helper4Sprite::createOptimizeSprite(PNG_BODY_GIRL_MODEL);
	oModel->setPositionY(origin.y);
	oModel->setScale(ScaleManager::getInstance()->getLookGoodScaleDownRatio());
	oModel->setAnchorPoint(Vec2(0.5, 0));
	//oModel
	//int arrow
	this->oArrow = Node::create();

	auto sprtArrow = Helper4Sprite::createOptimizeSprite(PNG_TUTORIAL_ARROW);
	//sprtArrow->setScale(0.8f);

	this->oArrow->addChild(sprtArrow);
	this->oArrow->setContentSize(sprtArrow->getContentSize());

	//int intruction text
	this->oText = Label::createWithTTF("", FONT_PassionOne_Regular, 50);
	this->oText->setAnchorPoint(Vec2(0, 1));

	this->oTutorial->addChild(clipper);
	this->oTutorial->addChild(this->oModel);
	this->oTutorial->addChild(this->oArrow);
	this->oTutorial->addChild(this->oText);

	this->aPos = std::vector<Vec2>{
		Vec2(),
		Vec2(520*scaleDownRatio+origin.x, visibleSize.height/2+170*scaleDownRatio), //Select Game
		Vec2(visibleSize.width/2+ 215 * scaleDownRatio + origin.x, 60), //Change Bet
		Vec2(70 * scaleDownRatio + origin.x, visibleSize.height-60*scaleDownRatio), //Customize
		Vec2(1490 - origin.x, 445), //Spin
		Vec2(1362 * scaleDownRatio + origin.x, visibleSize.height - 60 * scaleDownRatio), //Return Lobby
		Vec2(100 * scaleDownRatio + origin.x ,10), //Show Achievement
		Vec2(510 * scaleDownRatio + origin.x, visibleSize.height - 60 * scaleDownRatio), //Show Shop
		Vec2(visibleSize.width/2-470 * ScaleManager::getInstance()->getLookGoodScaleDownRatio() + origin.x, visibleSize.height/2-110* ScaleManager::getInstance()->getLookGoodScaleDownRatio()), //Watch Vid
		Vec2()
	};

	this->aSize = std::vector<float>{
		0,
		150*scaleDownRatio, //Select Game
		90 * scaleDownRatio, //Change Bet
		60 * scaleDownRatio, //Customize
		150, //Spin
		50 * scaleDownRatio, //Return Lobby
		130 * scaleDownRatio, //Show Achievement
		50 * scaleDownRatio, //Show Shop
		240 * ScaleManager::getInstance()->getLookGoodScaleDownRatio(), //Watch Vid
		0
	};

	this->bInited = true;

	this->oTutorial->setVisible(false);

	this->retain();

	return true;
}

bool Tutorial::checkAndShow(cocos2d::Node* parent)
{
	//load info from local
	this->loadLocal();


	//if user not complete tutorial or is allow to play according to Server -> init and show tutorial
	if (!this->info.isComplete || this->userInfo->allowPlayTutorial) {

		if (this->info.isComplete && this->userInfo->allowPlayTutorial) {
			this->info.isComplete = false;
			this->info.iCurStep = this->userInfo->allowGetPreTutorialReward || this->info.isFirstLogin ? TutorialStep::StepWelcome : TutorialStep::StepSelectGame;
			this->saveLocal();
		}

		this->init();
		this->bActive = true;

		this->start();

		if (this->getParent()) {
			this->removeFromParent();
		}
		parent->addChild(this, INT_MAX);
		return true;
	}
	else {
		this->finish();
		return false;
	}
}

void Tutorial::updateReference() {

	this->userInfo = InfoManager::getInstance()->getUserInfo();
	this->oHeaderUI = PopupManager::getInstance()->getHeaderLobbyLayout();
}

void Tutorial::loadToSlotGame()
{
	this->oTutorial->setVisible(false);
	auto gameSlotScene = ((LobbyScene*)Helper4Scene::getRunningScene())->gotoGameSlotScene(ppEnum::GameSlotOrderId::NEZHA);
	//Add some game event listener to trigger when on tutorial
	gameSlotScene->addGameEventListener([this, gameSlotScene](GameSlot::GameSlotScene* ref, GameSlot::GameEventListenerType type) {
		switch (type)
		{
		case GameSlot::BeginGame:
		{
			if (this->info.isFirstLogin) {
				this->oHeaderUI->setCoin(100000);
			}
			if (this->getParent()) {
				this->removeFromParent();
			}

			gameSlotScene->addChild(this, INT_MAX);
			gameSlotScene->getMain()->getGame()->getInterface()->getGameEffect()->getSpinEffect()->setUpdateExpLocal(false);

			if (this->info.iCurStep < TutorialStep::StepSpin) {
				auto oFooter = gameSlotScene->getMain()->
					getGame()->getInterface()->getFooter();
				oFooter->setEnableBtn((GameSlot::CSpriteButton*)oFooter->getChildByName("bet")->getChildByName("btnAdd"), true);
			}

			this->showStep(this->info.iCurStep);
			break;
		}
		case GameSlot::BeginSpin:
			this->oTutorial->setVisible(false);
			break;
		case GameSlot::FinishSpin:
			//Show mega win
			gameSlotScene->getMain()->getGame()->getInterface()->getGameEffect()->getWinEffect()->showWinEffect(gameSlotScene->getMain()->getWin(), true);
			//Delay 5s to go to Return Lobby Step
			this->oTutorial->runAction(Sequence::createWithTwoActions(DelayTime::create(5.0f), CallFunc::create([this]() {
				this->showStep(TutorialStep::StepReturnLobby);
			})));
			break;
		}
	});
}

void Tutorial::start()
{
	//this fuction call to start tutorial series
	switch (this->info.iCurStep)
	{
	case TutorialStep::StepWelcome:
	{
		//show welcome
		if (!oWelcome) {
			oWelcome = Welcome::create();

			if (this->info.isFirstLogin) {
				this->oHeaderUI->setCoin(0);
			}

			oWelcome->addOnClaimListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
				if (type != ui::Widget::TouchEventType::ENDED) return;

				if (this->info.isFirstLogin) {
					this->oHeaderUI->setCoin(0);
				}
				if (this->userInfo->allowGetPreTutorialReward) {
					NetworkManager::getInstance()->redeemPreTutorialReward([this, sender](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString) {
						if (coreResultCode == RESULT_CODE_VALID) {
							this->oHeaderUI->reloadUIHeaderAndCheckShowPopupLevelUp([this, sender](bool isSuccess, LevelUpInfo* lvUp) {
								AnimationCoinCrown::create(
									Helper4Scene::getRunningScene(),
									Vec2(((ui::Button*)sender)->getPosition()),
									100000
								);
								this->showStep(TutorialStep::StepSelectGame);
								oWelcome->setVisible(false);
							});
						}
						else {
							this->showStep(TutorialStep::StepSelectGame);
							oWelcome->setVisible(false);
						}
					}, CC_CALLBACK_1(Tutorial::onError, this), CC_CALLBACK_1(Tutorial::onError, this));
				}
				else {
					this->oHeaderUI->increaseCoin(WELCOME_REWARD_COIN);
					AnimationCoinCrown::create(
						Helper4Scene::getRunningScene(),
						Vec2(((ui::Button*)sender)->getPosition()),
						100000
					);
					this->showStep(TutorialStep::StepSelectGame);
					oWelcome->setVisible(false);
				}
			});
			this->addChild(oWelcome);
		}
		oWelcome->updateWelcomeText();
		break;
	}
	case TutorialStep::StepSelectGame:
		if (this->info.isFirstLogin) {
			this->oHeaderUI->setCoin(100000);
		}
		this->showStep(this->info.iCurStep);
		break;
	case TutorialStep::StepChangeBet:
	case TutorialStep::StepCustomizeIntro:
	case TutorialStep::StepSpin:
		if (this->info.isFirstLogin) {
			this->oHeaderUI->setCoin(100000);
		}
		//those step is on nezha game so we first must go to nezha game
		//need a little delay to avoid bugs
		this->runAction(Sequence::createWithTwoActions(DelayTime::create(0.5f), CallFunc::create([this](){
			this->loadToSlotGame();
		})));
		break;
	case TutorialStep::StepReturnLobby:
		//call complete tutorial when user not call this yet
		NetworkManager::getInstance()->finishTutorial(
		[this](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString) {
			if (coreResultCode == RESULT_CODE_VALID) {
				PopupManager::getInstance()->getBottomLobbyLayout()->updateNotificationAchievementsFromSV();
			}
			this->showStep(TutorialStep::StepShowAchivement);
		}, CC_CALLBACK_1(Tutorial::onError, this), CC_CALLBACK_1(Tutorial::onError, this));
		break;
	case TutorialStep::StepShowAchivement:
	case TutorialStep::StepShowShop:
		//show those steps on lobby scene
		this->showStep(this->info.iCurStep);
		break;
	}
}

bool Tutorial::onTouched(cocos2d::Touch * touch, cocos2d::Event * event)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("TUTORIAL DARK LAYER SWALLOW TOUCH");
	}

	cocos2d::Vec2 p = this->convertToNodeSpace(touch->getLocation());
	//rect that user can touch on screen
	cocos2d::Rect rect = Rect(
		this->aPos[this->info.iCurStep].x - this->aSize[this->info.iCurStep],
		this->aPos[this->info.iCurStep].y - this->aSize[this->info.iCurStep], 
		2 * this->aSize[this->info.iCurStep], 
		2 * this->aSize[this->info.iCurStep]);

	if (!this->isVisible()) return false;

	if (this->oTutorial->isVisible()) {
		if (rect.containsPoint(p))
		{
			this->oTutorial->setVisible(false);
			switch (this->info.iCurStep)
			{
			case TutorialStep::StepSelectGame:
				//change step and load to game
				this->info.iCurStep = TutorialStep::StepChangeBet;
				this->loadToSlotGame();
				break;
			case TutorialStep::StepChangeBet:
				//change game's bet and show next step
				((GameSlot::GameSlotScene*)this->getParent())->getMain()->
					getGame()->getInterface()->getFooter()->reloadPayline(15, true);
				((GameSlot::GameSlotScene*)this->getParent())->getMain()->
					getGame()->getInterface()->getFooter()->reloadBet(6000, true);
				this->showStep(TutorialStep::StepCustomizeIntro);
				break;
			case TutorialStep::StepCustomizeIntro:
				this->oTutorial->setVisible(true);
				//this step is received no input
				break;
			case TutorialStep::StepSpin:
			{
				//call spin
				if (!this->info.isFirstLogin) {
					NetworkManager::getInstance()->redeemTutorialReward(
						[this](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString) {
						tinyxml2::XMLDocument doc;
						doc.Parse(InfoManager::getInstance()->getServerConfigsInfo()->sampleResponseSpinInTutorial.c_str());
						((GameSlot::GameSlotScene*)this->getParent())->getMain()->
							getGame()->onSpin(&doc);
					}, CC_CALLBACK_1(Tutorial::onError, this), CC_CALLBACK_1(Tutorial::onError, this));
				}
				else {
					tinyxml2::XMLDocument doc;
					doc.Parse(InfoManager::getInstance()->getServerConfigsInfo()->sampleResponseSpinInTutorial.c_str());
					((GameSlot::GameSlotScene*)this->getParent())->getMain()->
						getGame()->onSpin(&doc);
				}
				break;
			}
			case TutorialStep::StepReturnLobby:
				//call complete tutorial and return to lobby when user click home button
				NetworkManager::getInstance()->finishTutorial(
					[this](int coreResultCode, rapidjson::Value&responseAsDocument, std::string responseAsString) {
					this->oHeaderUI->gotoLobbyScene();
					//If collect success -> up to next step
					//else remain in this step and when return to lobby scene, it will call collect again
					if (coreResultCode == RESULT_CODE_VALID) {
						this->info.iCurStep = TutorialStep::StepShowAchivement;
					}
					else {
						this->info.iCurStep = TutorialStep::StepReturnLobby;
					}
					this->saveLocal();
				}, CC_CALLBACK_1(Tutorial::onError, this), CC_CALLBACK_1(Tutorial::onError, this));
				break;
			case TutorialStep::StepShowAchivement:
			{
				//show popup achievement
				auto achievementPopup = PopupManager::getInstance()->getAchievementPopup();
				achievementPopup->addPopupEventListener([this](BasePopup* popup, PopupStateType type) {
					if (type == PopupStateType::Popup_State_Close) {
						this->setVisible(true);
						this->showStep(TutorialStep::StepShowShop);
					}
				});
				achievementPopup->prepareAndShow(this->getParent());
				this->setVisible(false);
				break;
			}
			case TutorialStep::StepShowShop:
				//show popup shop
				PopupManager::getInstance()->getShopPopup()->prepareAndShow(this->getParent(), ShopType::CoinShop);
				this->showStep(TutorialStep::StepWatchVideo);
				break;
			case TutorialStep::StepWatchVideo:

				this->oTutorial->setVisible(true);
				//watch video
                this->finish();
                    
				PopupManager::getInstance()->getShopPopup()->selecteItem(PurchaseItemType::FREE_COINS);
                    
				break;
			}
			return true;
		}else if(this->info.iCurStep == TutorialStep::StepWatchVideo) {
			//user touch outside the circle zone on the last step
			this->finish();
		}
	}
	return true;
}


void Tutorial::setTutorialString(std::string tutorialString) {
	UtilFunction::detectFontAndSetStringForLabel(this->oText, FONT_PassionOne_Regular, tutorialString);
}

void Tutorial::showStep(TutorialStep step)
{

	this->info.iCurStep = step;

	this->oStencil->clear();

	switch (this->info.iCurStep)
	{
		//StepSelectGame
	case TutorialStep::StepSelectGame:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(-50);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x + this->aSize[this->info.iCurStep] * 1.4f,
			this->aPos[this->info.iCurStep].y - this->aSize[this->info.iCurStep] * 1.3f);

		/*UtilFunction::detectFontAndSetStringForLabel(this->oText, FONT_PassionOne_Regular, "Hello "+ UtilFunction::trimStringAndAdd3Dots(this->userInfo->name, 16) + "!"+ "\nTap the icon to start!");*/
		setTutorialString("Hello " + UtilFunction::trimStringAndAdd3Dots(this->userInfo->name, 16) + "!" + "\nTap the icon to start!");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(60, -55));

		this->oModel->setPositionX(this->oModel->getContentSize().width / 2 + 10 + origin.x);
		break;
		//StepChangeBet
	case TutorialStep::StepChangeBet:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(150);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x - this->aSize[this->info.iCurStep] * 1.3f,
			this->aPos[this->info.iCurStep].y + this->aSize[this->info.iCurStep] * 2.3f);

		//this->oText->setString("Tap to change bet.");
		setTutorialString("Tap to change bet.");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(-200, 160));

		this->oModel->setPositionX(this->oModel->getContentSize().width / 2 + 10+origin.x);
		break;
		//StepCustomizeIntro
	case TutorialStep::StepCustomizeIntro:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(-45);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x + this->aSize[this->info.iCurStep] * 2.8f,
			this->aPos[this->info.iCurStep].y - this->aSize[this->info.iCurStep] * 2.8f);

		//UtilFunction::detectFontAndSetStringForLabel(this->oText, FONT_PassionOne_Regular, "This is you, \n"+ UtilFunction::trimStringAndAdd3Dots(this->userInfo->name, 16) +".\nCustomize by logging in.");
		setTutorialString("This is you, \n" + UtilFunction::trimStringAndAdd3Dots(this->userInfo->name, 16) + ".\nCustomize by logging in.");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(80, -80));

		this->oModel->setPositionX(this->oModel->getContentSize().width*scaleDownRatio / 2 + 1300*scaleDownRatio+origin.x/2);

		//Delay 3s to go to Spin step
		this->oTutorial->runAction(Sequence::createWithTwoActions(DelayTime::create(3.0f), CallFunc::create([this]() {
			this->showStep(this->userInfo->allowGetTutorialSpinReward ? TutorialStep::StepSpin : TutorialStep::StepReturnLobby);
#if IS_DEBUG
			/*test: show spin step in tutorial*/
			//this->showStep( TutorialStep::StepSpin );
#endif

		})));
		//change game's bet and show next step
		((GameSlot::GameSlotScene*)this->getParent())->getMain()->
			getGame()->getInterface()->getFooter()->reloadPayline(15, true);
		((GameSlot::GameSlotScene*)this->getParent())->getMain()->
			getGame()->getInterface()->getFooter()->reloadBet(6000, true);
		break;
		//StepSpin
	case TutorialStep::StepSpin:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(90);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x - this->aSize[this->info.iCurStep] * 1.8f,
			this->aPos[this->info.iCurStep].y);

		setTutorialString("Tap to spin!");
		//this->oText->setString("Tap to spin!");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(-300, 10));

		this->oModel->setPositionX(this->oModel->getContentSize().width / 2 + 10+origin.x);
		//change game's bet and show next step
		((GameSlot::GameSlotScene*)this->getParent())->getMain()->
			getGame()->getInterface()->getFooter()->reloadPayline(15, true);
		((GameSlot::GameSlotScene*)this->getParent())->getMain()->
			getGame()->getInterface()->getFooter()->reloadBet(6000, true);
		break;
		//StepReturnLobby
	case TutorialStep::StepReturnLobby:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(45);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x - this->aSize[this->info.iCurStep] * 2.8f,
			this->aPos[this->info.iCurStep].y - this->aSize[this->info.iCurStep] * 2.8f);

		setTutorialString("This takes you back \nto the lobby.");
		//this->oText->setString("This takes you back \nto the lobby.");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(-250, -110));

		this->oModel->setPositionX(this->oModel->getContentSize().width / 2 + 10+origin.x);

		this->info.isFirstLogin = false;
		break;
		//StepShowAchivement
	case TutorialStep::StepShowAchivement:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(-145);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x + this->aSize[this->info.iCurStep],
			this->aPos[this->info.iCurStep].y + this->aSize[this->info.iCurStep] * 2.0f);
		setTutorialString("Tutorial completed! \nClaim your rewards now\nand spin away.");
		//this->oText->setString("Tutorial completed! \nClaim your rewards now\nand spin away.");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(100, 160));

		this->oModel->setPositionX(this->oModel->getContentSize().width / 2 + 1300*scaleDownRatio);
		break;
		//StepShowShop
	case TutorialStep::StepShowShop:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(-35);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x + this->aSize[this->info.iCurStep] * 1.8f,
			this->aPos[this->info.iCurStep].y - this->aSize[this->info.iCurStep] * 3.0f);
		setTutorialString("One more thing...");
		//this->oText->setString("One more thing...");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(60, -90));

		this->oModel->setPositionX(this->oModel->getContentSize().width / 2 + 1300 * scaleDownRatio);
		break;
		//StepWatchVideo
	case TutorialStep::StepWatchVideo:
		this->oStencil->drawSolidCircle(Vec2(this->aPos[this->info.iCurStep]), this->aSize[this->info.iCurStep], 0.0f, 64.0f, Color4F::WHITE);

		this->oArrow->setRotation(-130);
		this->oArrow->setPosition(this->aPos[this->info.iCurStep].x + this->aSize[this->info.iCurStep] * 1.3f,
			this->aPos[this->info.iCurStep].y + this->aSize[this->info.iCurStep]);
		setTutorialString("You can always get more\nfree coins by watching a video.");
		//this->oText->setString("You can always get more\nfree coins by watching a video.");
		this->oText->setPosition(this->oArrow->getPosition() + Vec2(100, 120+(1-ScaleManager::
getInstance()->getLookGoodScaleDownRatio())*oModel->getContentSize().height));

		this->oModel->setPositionX(this->oModel->getContentSize().width / 2 + 1300 * scaleDownRatio);
		break;
	}

	auto sprtArrow = this->oArrow->getChildren().at(0);
	sprtArrow->stopAllActions();
	sprtArrow->setPosition(Vec2::ZERO);
	sprtArrow->setContentSize(this->oArrow->getContentSize());
	sprtArrow->runAction(RepeatForever::create(Sequence::createWithTwoActions(MoveBy::create(0.4f, Vec2(0, 50)), MoveBy::create(0.4f, Vec2(0, -50)))));
	sprtArrow->runAction(RepeatForever::create(Sequence::createWithTwoActions(
		ResizeBy::create(0.4f, Size(0, -sprtArrow->getContentSize().height * 0.3f)),
		ResizeBy::create(0.4f, Size(0, sprtArrow->getContentSize().height * 0.3f)))));

	this->oTutorial->setOpacity(0);
	this->oTutorial->setVisible(true);
	this->oTutorial->runAction(FadeIn::create(FADE_TUTORIAL_DURATION));

	if (step != TutorialStep::StepWatchVideo) {
		this->saveLocal();
	}
}

void Tutorial::onError(const std::string & mes)
{
	this->remove();
	Director::getInstance()->replaceScene(
		TransitionFade::create(
			Configs::TIME_TRANSITION_FADE_SCENE,
			LoginScene::createScene("","")
		)
	);
}

void Tutorial::finish()
{
	this->info.isFirstLogin = false;
	this->info.isComplete = true;
	this->saveLocal();

	UserDefault::getInstance()->deleteValueForKey((STORING_KEY_TUTORIAL_FIRST_LOGIN + ToString(userInfo->id)).c_str());
	UserDefault::getInstance()->deleteValueForKey((STORING_KEY_TUTORIAL_STEP + ToString(userInfo->id)).c_str());
	UserDefault::getInstance()->deleteValueForKey((STORING_KEY_TUTORIAL_IS_COMPLETED + ToString(userInfo->id)).c_str());
	cocos2d::UserDefault::getInstance()->flush();

	this->remove();
}

void Tutorial::remove()
{
	this->bActive = false;

	s_instance = nullptr;

	if (this->getParent()) {
		this->removeFromParent();
	}
	this->autorelease();

	if (this->finishCallback) {
		this->finishCallback();
		this->finishCallback = nullptr;
	}
}

void Tutorial::loadLocal()
{
	this->info.isFirstLogin = UserDefault::getInstance()->getBoolForKey((STORING_KEY_TUTORIAL_FIRST_LOGIN + ToString(userInfo->id)).c_str(), false);
	this->info.iCurStep = (TutorialStep)UserDefault::getInstance()->getIntegerForKey((STORING_KEY_TUTORIAL_STEP + ToString(userInfo->id)).c_str(), TutorialStep::StepWelcome);
	this->info.isComplete = UserDefault::getInstance()->getBoolForKey((STORING_KEY_TUTORIAL_IS_COMPLETED + ToString(userInfo->id)).c_str(), true);

	if (!bActive) {
#if IS_DEBUG
	/*test: force turn on tutorial*/
		//this->info.isFirstLogin = true;
		//this->info.iCurStep = TutorialStep::StepWelcome;
		////this->info.iCurStep = TutorialStep::StepShowShop;
		//this->info.isComplete = false;
		//this->userInfo->allowPlayTutorial = true;
#endif
	}
}

void Tutorial::saveLocal()
{
	UserDefault::getInstance()->setBoolForKey((STORING_KEY_TUTORIAL_FIRST_LOGIN + ToString(userInfo->id)).c_str(), this->info.isFirstLogin);
	UserDefault::getInstance()->setIntegerForKey((STORING_KEY_TUTORIAL_STEP + ToString(userInfo->id)).c_str(), (int)this->info.iCurStep);
	UserDefault::getInstance()->setBoolForKey((STORING_KEY_TUTORIAL_IS_COMPLETED + ToString(userInfo->id)).c_str(), this->info.isComplete);
	UserDefault::getInstance()->flush();
}
