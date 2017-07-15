#include "Scene/InitSessionScene.h"
#include "LoginScene.h"
#include "LobbyScene.h"

#include "json/writer.h"
#include "json/document.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/JSONFieldConstant.h"
#include "Constant/LobbyConstant.h"
#include "Constant/PPEnums.h"

#include "Info/AdditionalInfo.h"

#include "Manager/InfoManager.h"
#include "Manager/LanguageManager.h"
#include "Manager/PopupManager.h"
#include "Manager/PluginManager.h"
#include "Util/UtilFunction.h"

#include "Helper/Helper4ParseJSON.h"
#include "Helper/Helper4Sprite.h"

#define DURATION_PROGRESS_TIMER_ANIMATION 0.5f
#define CANNOT_CONNECT_TO_SERVER  "Can not connect to server! Please try again later ..."
#define SERVER_MAINTENANCE  "Server maintenance. Please check back later ..."
#define LOGGED_SOMEWHERE_ELSE  "Your account has been logged in from another location. Please reload the game"

#define LOADING_SCENE_CALL_API_MESSAGE_1  "Connecting Server"
#define LOADING_SCENE_CALL_API_MESSAGE_2  "Get Data From Server"
#define LOADING_SCENE_CALL_API_MESSAGE_3  "Get Config From Server"
#define LOADING_SCENE_CALL_API_MESSAGE_4  "Get Strategy From Server"
#define LOADING_SCENE_CALL_API_MESSAGE_5  "Loading the lobby"
//#define LOADING_SCENE_MESSAGE_2  "Loading slot game"
USING_NS_CC;
using namespace rapidjson;
Scene* InitSessionScene::createScene(ppEnum::LoginAndInitSSFrom _loginFrom)
{
	// 'scene' is an autorelease object
	auto scene = InitSessionScene::create();
	scene->setTag(ppEnum::GameScene::InitSession);
	InfoManager::getInstance()->getUserInfo()->loginFrom = _loginFrom;

	scene->loginFrom = _loginFrom;

	// return the scene
	return scene;
}

void InitSessionScene::onEnter()
{
    BaseScene::onEnter();
    //play bg music
	processAfterInit();
}

// on "init" you need to initialize your instance
bool InitSessionScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!BaseScene::init())
	{
		return false;
	}

	//init language
	LanguageManager::getInstance();
	//init popup
	PopupManager::getInstance()->initAllPopupLobbyScene();

	

	//BACKGROUND
	auto background = Helper4Sprite::createOptimizeSprite(PNG_LOADING_BACKGROUND);
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);

#if IS_DEBUG
	/*test:know what is your scene*/
	/*auto label = Label::createWithSystemFont("Init Session", "Arial", 96);
	label->setColor(Color3B::BLACK);
	label->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(label, 1);*/

	/*test:*/
	//this->scheduleOnce(schedule_selector(InitSessionScene::gotoLoadingLobbyScene), 0.5);
#endif

	//LOADING PROGRESS TIMER
	auto bgLoadingBar = Helper4Sprite::createOptimizeSprite(PNG_LOADING_BAR_BACKGROUND);
	bgLoadingBar->setPosition(Vec2(
		background->getPosition().x,
		background->getPosition().y - 180));
	this->addChild(bgLoadingBar);

	this->loadingProgessTimer = CCProgressTimer::create(CCSprite::create(PNG_LOADING_BAR_FILL));
	if (this->loadingProgessTimer != NULL)
	{
		this->loadingProgessTimer->setType(kCCProgressTimerTypeBar);
		this->loadingProgessTimer->setMidpoint(ccp(0, 0));
		this->loadingProgessTimer->setBarChangeRate(ccp(1, 0));
		this->loadingProgessTimer->setPercentage(0);
		this->loadingProgessTimer->setPosition(ccp(bgLoadingBar->getContentSize().width / 2, bgLoadingBar->getContentSize().height / 2));
		bgLoadingBar->addChild(this->loadingProgessTimer);
	}

	//LOADING LABEL
	this->loadingLabel = Label::createWithTTF(TTFConfig(FONT_PassionOne_Regular,35),LOADING_SCENE_CALL_API_MESSAGE_1);
	this->loadingLabel->setPosition(Vec2(
		bgLoadingBar->getPosition().x,
		bgLoadingBar->getPosition().y - 120
	));
	this->addChild(loadingLabel);
    
    // turn on schedule to run function gotoLoginSceneAfterDelay
//    this->scheduleUpdate();
	return true;
}

// server request step1
void InitSessionScene::processAfterInit(){
	this->updateProgressTimerLoading(0, false, LOADING_SCENE_CALL_API_MESSAGE_1);
	this->updateProgressTimerLoading(RandomHelper::random_real(0.7f, 1.0f));

	switch (loginFrom)
	{
	case ppEnum::Facebook:{
		std::string accessTokenFacebook = PluginManager::getInstance()->getFacebookController()->getAccessToken();
		if (Configs::printConsoleLog) CCLOG("GET ACCESS TOKEN FROM FB: %s", accessTokenFacebook.c_str());
		
		NetworkManager::getInstance()->loginFB(accessTokenFacebook,
			[this](int coreResultCode,rapidjson::Value &response,std::string responseAsString){
			if (coreResultCode == RESULT_CODE_VALID){
				InfoManager::getInstance()->updateUserInfo(response);
				NetworkManager::getInstance()->setLoginToken(response[JSONFieldConstant::LOGIN_TOKEN.c_str()].GetString());
				this->getDataFromServer();
			}else{
				this->gotoLoginSceneSomethingWrong();
			}
		});
		break;
	}
	case ppEnum::PPAccount:{
		auto callbackAuthorizeSession = [this](int coreResultCode,rapidjson::Value &response,std::string responseAsString){
			if (coreResultCode == RESULT_CODE_VALID)
				this->getDataFromServer();
			else 
				this->gotoLoginSceneSomethingWrong();
		};
		NetworkManager::getInstance()->authorizePPAccount(callbackAuthorizeSession);
		break;
	}
	case ppEnum::Guess:
		this->getDataFromServer();
		break;
	default:
		break;
	}
}

//server request step2
void InitSessionScene::getDataFromServer()
{
	this->updateProgressTimerLoading(0, false, LOADING_SCENE_CALL_API_MESSAGE_2);
	this->updateProgressTimerLoading(RandomHelper::random_real(0.7f, 1.0f));

	NetworkManager::getInstance()->getAllData(
		[this](
			int coreResultCode,
			rapidjson::Value &responseAsDocument,
			std::string responseAsString) {

		if (coreResultCode == RESULT_CODE_VALID)
		{
			this->updateProgressTimerLoading(1.0f, false);
			auto listSize = responseAsDocument[JSONFieldConstant::LIST_SIZE.c_str()].GetInt();
			auto members = responseAsDocument[JSONFieldConstant::MEMBER.c_str()].GetArray();
			for (auto i = 0; i < listSize; i++) {
				std::string beanType = members[i][JSONFieldConstant::BEAN_TYPE.c_str()].GetString();
				if (members[i][JSONFieldConstant::RESULT_CODE.c_str()].GetInt64() != RESULT_CODE_VALID)
					continue;
				if (beanType == LobbyConstant::API_COMBINATION_BEAN_NAME_GET_MY_PROFILE)
					InfoManager::getInstance()->updateUserInfo(members[i][JSONFieldConstant::BEAN.c_str()]);
				else if (beanType == LobbyConstant::API_COMBINATION_BEAN_NAME_CHECK_COLLECT_COIN)
					InfoManager::getInstance()->updateUserBonusCheck(members[i][JSONFieldConstant::BEAN.c_str()]);
				else if (beanType == LobbyConstant::API_COMBINATION_BEAN_NAME_GET_ALL_CONFIG)
					InfoManager::getInstance()->updateServerConfigsInfo(members[i][JSONFieldConstant::BEAN.c_str()]);
				/*todo:them update product sau*/
				else if (beanType == LobbyConstant::API_COMBINATION_BEAN_NAME_GET_LINK_GAME) {}
				else if (beanType == LobbyConstant::API_COMBINATION_BEAN_NAME_GET_LEVEL_CONFIG)
					InfoManager::getInstance()->updateLevelInfoList(members[i][JSONFieldConstant::BEAN.c_str()]);
				else if (beanType == LobbyConstant::API_COMBINATION_BEAN_NAME_GET_ALL_LIST_SLOT_GAME_INFO)
					InfoManager::getInstance()->updateServerSlotGameInfoList((members[i][JSONFieldConstant::BEAN.c_str()])[JSONFieldConstant::MEMBER.c_str()]);
				else if (beanType == LobbyConstant::API_COMBINATION_BEAN_NAME_GET_LIST_BET_SIZE_RESTRICTION)
					//auto dataArray = data[JSONFieldConstant::MEMBER.c_str()].GetArray();
					InfoManager::getInstance()->updateBetSlotGameInfoList(members[i][JSONFieldConstant::BEAN.c_str()]);
			}
			getFeatureConfigInfoAndCollectDataInfo(CC_CALLBACK_0(InitSessionScene::getAdditionalInfo, this));
		}
		else {
			if (Configs::printConsoleLog) CCLOG("ERROR AT GET ALL CONFIGS");
			this->gotoLoginSceneSomethingWrong();
		}
	});
}

/// <summary>
/// server request step3
/// Dat: call API /user/featureConfig/getAll
/// </summary>
void InitSessionScene::getFeatureConfigInfoAndCollectDataInfo(std::function<void()> callbackAfterGet){

	this->updateProgressTimerLoading(0, false, LOADING_SCENE_CALL_API_MESSAGE_3);
	this->updateProgressTimerLoading(RandomHelper::random_real(0.7f, 1.0f));

	NetworkManager::getInstance()->getAllFeatureConfig([this, callbackAfterGet](
		int coreResultCode,
		bool isSuccess,
		rapidjson::Value &responseAsDocument,
		std::string responseAsString) {
		log("NetworkManager::getInstance()->getAllFeatureConfig DONE");
		if (isSuccess){
			auto listSize = Helper4ParseJSON::getListSize(responseAsDocument);
			auto members = Helper4ParseJSON::getMember(responseAsDocument);
			for (auto i = 0; i < listSize; i++) {
				std::string beanType = Helper4ParseJSON::getBeanType(members[i]);
				if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_DAILY_BONUS_STREAK)
					InfoManager::getInstance()->updateListDailyBonusStreakConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_FREE_COIN_GIFT)
					InfoManager::getInstance()->updateFreecoinGiftConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_UNLOCK_BY_LEVEL)
					InfoManager::getInstance()->updateUnlockFeatureByLevelConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_WHEEL)
					InfoManager::getInstance()->updateListLuckyWheelRewardConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_DAILY_CHALLENGE)
					InfoManager::getInstance()->updateDailyChallengeConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_BOOSTER)
					InfoManager::getInstance()->updateBoosterConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_MOBILE_SLOT_GAME_CONFIG)
					InfoManager::getInstance()->updateSlotGameConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_MOBILE_SLOT_GAME_PAY_LINE_CONFIG)
					InfoManager::getInstance()->updatePayLineConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_LUCKY_BOX_CONFIG)
					InfoManager::getInstance()->updateLuckyBoxConfig(members[i]);
				else if (beanType == LobbyConstant::API_FEATURE_BEAN_TYPE_MAGIC_ITEM_CONFIG)
					InfoManager::getInstance()->updateMagicItemConfig(members[i]);
			}
			this->updateProgressTimerLoading(1.0f, false);
			if (callbackAfterGet)callbackAfterGet();
		}
		else
		{
			if (Configs::printConsoleLog) CCLOG("ERROR AT GET FEATURE CONFIG");	
			this->gotoLoginSceneSomethingWrong();
		}
	});
}

//server request step4
void InitSessionScene::getAdditionalInfo()
{
	this->updateProgressTimerLoading(0, false, LOADING_SCENE_CALL_API_MESSAGE_4);
	this->updateProgressTimerLoading(RandomHelper::random_real(0.7f, 1.0f));
	InfoManager::getInstance()->reloadAdditionalInfo([this](bool isSuccess, AdditionalInfo *result) {


		log("InfoManager::getInstance()->reloadAdditionalInfo DONE");
		//Kiet: get friend list -> invitable friend list if login from facebook
		//(get in new thread)
		auto infoMNG = InfoManager::getInstance();
		long currentUserId = infoMNG->getUserInfo()->id;
		if (isSuccess
			&& this->loginFrom == ppEnum::LoginAndInitSSFrom::Facebook
			&& infoMNG->getFacebookFriendInfo()->getUserIdCurrentFriendList() != currentUserId){
			PluginManager::getInstance()->getFacebookController()->getInvitableFriends(
				[infoMNG, currentUserId](std::vector < InvitableFriendInfo*>& friends){
				CCLOG("callback get invitable friends");
				if (currentUserId == infoMNG->getUserInfo()->id){
					CCLOG("callback get invitable friends OK CONDITION");
					infoMNG->getFacebookFriendInfo()->updateInvitableFriendList(friends);
					CCLOG("infoMNG->reloadFriendListOnly");
					infoMNG->reloadFriendListOnly(nullptr);
					CCLOG("infoMNG->getFacebookFriendInfo()->setUserIdCurrentFriendList(");
					infoMNG->getFacebookFriendInfo()->setUserIdCurrentFriendList(currentUserId);
				}else{
					CCLOG("CC_SAFE_DELETE(child);");
					for (auto child : friends){
						CC_SAFE_DELETE(child);
					}
					friends.clear();
				}
			});
		}
		checkAndGoToNextScene(isSuccess);
	});
}

//server request step5
void InitSessionScene::checkAndGoToNextScene(bool isSuccess) {

	this->updateProgressTimerLoading(0, false, LOADING_SCENE_CALL_API_MESSAGE_5);
	this->updateProgressTimerLoading(RandomHelper::random_real(0.7f, 1.0f));

	//this->updateProgressTimerLoading(1.0f, false);
	if (isSuccess) this->gotoLobbyScene(0);
	else this->gotoLoginSceneSomethingWrong();
}

void InitSessionScene::updateProgressTimerLoading(float percent, bool isRunAnimation,std::string loadingLabel)
{
	this->loadingProgessTimer->stopAllActions();
	if (isRunAnimation) 
	{
		this->loadingProgessTimer->runAction(
			ProgressFromTo::create(RandomHelper::random_real(DURATION_PROGRESS_TIMER_ANIMATION - 0.2f, DURATION_PROGRESS_TIMER_ANIMATION + 0.2f),
				this->loadingProgessTimer->getPercentage(),
				percent * 100));
	}
	else
	{
		this->loadingProgessTimer->setPercentage(percent * 100);
	}
	if (!loadingLabel.empty())
	{
		this->loadingLabel->setString(loadingLabel);
	}
}

void InitSessionScene::update(float delta){
    /*doesnt work right now*/
    BaseScene::update(delta);
}
