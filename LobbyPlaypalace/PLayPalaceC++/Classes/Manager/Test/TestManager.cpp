#include "TestManager.h"
#include "extensions/cocos-ext.h"
#include "Helper/Helper4String.h"
#include "Helper/Helper4Scene.h"
#include "Manager/PopupManager.h"
#include "Manager/InfoManager.h"
#include "Manager/ScaleManager.h"
#include "Info/AdditionalInfo.h"
#include "Views/Popup/FBDailySpinPopup/DailyBonusWheelPopup.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LuckyBoxPopup.h"
#include "Views/Popup/GameUnlockedPopup.h"
#include "Views/Popup/DailyBonusStreakPopup.h"
#include "Views/Popup/LevelUpPopup.h"
#include "Views/Popup/ComebackBonusMobilePopup.h"
#include "Views/Popup/Achievement/AchievementPopup.h"
#include "Views/Login/MainLoginLayer.h"
#include "Scene/LobbyScene.h"
#include "Scene/LoginScene.h"
#include "SlotGame/GameSlotScene.h"

#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
#include "unzip.h"

#else
#include "unzip/unzip.h"

#endif
#endif

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

using namespace std;
USING_NS_CC;
#pragma region init singleton
TestManager* TestManager::s_instance = nullptr;

TestManager* TestManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new TestManager();
	}
	return s_instance;
}
#pragma endregion

TestManager::TestManager()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	scaleDownRatio = ScaleManager::getInstance()->getExactlyScaleDownRatio();
}



void TestManager::printOutListSlotGameInfo(std::map<int, ServerSlotGameInfo*> listSlotGameInfo) {
//format
	/*ServerSlotGameInfo * serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 40;
	serverSlotGameInfoTest->gameId = "mobile_nezha";
	serverSlotGameInfoTest->minLevel = 0;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 40;
	serverSlotGameInfoTest->timestampOfCreated = 0;
	serverSlotGameInfoTest->timestampOfLastModified = 0;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Nezha";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));*/

	int i = -1;
	for (auto &slotGameInfo : listSlotGameInfo)
	{
		cocos2d::log("");
		ServerSlotGameInfo * info = slotGameInfo.second;
		i++;
		if (i == 0) {
		cocos2d::log("ServerSlotGameInfo * serverSlotGameInfoTest = new ServerSlotGameInfo();");

		}
		else {
		cocos2d::log("serverSlotGameInfoTest = new ServerSlotGameInfo();");
		}
		cocos2d::log("serverSlotGameInfoTest->orderId = %i;", info->orderId);
		cocos2d::log("serverSlotGameInfoTest->gameId = \"%s\";", info->gameId.c_str());
		cocos2d::log("serverSlotGameInfoTest->gameIdLocal = \"%s\";", info->gameIdLocal.c_str());
		cocos2d::log("serverSlotGameInfoTest->newestVersion = \"%s\";", info->newestVersion.c_str());
		cocos2d::log("serverSlotGameInfoTest->minLevel = %i;",info->minLevel);
		cocos2d::log("serverSlotGameInfoTest->platform = %i;",info->platform);
		cocos2d::log("serverSlotGameInfoTest->premiumType = %i;",info->premiumType);
		cocos2d::log("serverSlotGameInfoTest->minCrown = %i;",info->minCrown);
		cocos2d::log("serverSlotGameInfoTest->available = %s;",info->available?"true":"false");
		cocos2d::log("serverSlotGameInfoTest->id = %i;",info->id);
		cocos2d::log("serverSlotGameInfoTest->timestampOfCreated = %i;",info->timestampOfCreated);
		cocos2d::log("serverSlotGameInfoTest->timestampOfLastModified = %i;",info->timestampOfLastModified);
		cocos2d::log("serverSlotGameInfoTest->info = \"%s\";",info->info.c_str());
		cocos2d::log("serverSlotGameInfoTest->name = \"%s\";",info->name.c_str());
		cocos2d::log("listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));");
	}
}

std::map<int, ServerSlotGameInfo*> TestManager::createListGameSlotInfoTest() {
	std::map<int, ServerSlotGameInfo*> listSlotGameInfo;

	ServerSlotGameInfo * serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 40;
	serverSlotGameInfoTest->gameId = "mobile_nezha";
	serverSlotGameInfoTest->gameIdLocal = "legendofnezha";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 0;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 40;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 211695532;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Nezha";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 41;
	serverSlotGameInfoTest->gameId = "mobile_goldenegg";
	serverSlotGameInfoTest->gameIdLocal = "goldenegg";
	serverSlotGameInfoTest->newestVersion = "2016-09-06-01";
	serverSlotGameInfoTest->minLevel = 8;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 41;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259876109;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Golden Eggs";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 42;
	serverSlotGameInfoTest->gameId = "mobile_pharaoh";
	serverSlotGameInfoTest->gameIdLocal = "pharaoh";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 12;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 42;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259889909;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Pharaoh";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 43;
	serverSlotGameInfoTest->gameId = "mobile_boxing";
	serverSlotGameInfoTest->gameIdLocal = "boxing";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 17;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 43;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259911056;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Boxing";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 44;
	serverSlotGameInfoTest->gameId = "mobile_romanempire";
	serverSlotGameInfoTest->gameIdLocal = "romanempire";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 25;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 44;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259926353;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Roman Empire";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 45;
	serverSlotGameInfoTest->gameId = "mobile_candylicious";
	serverSlotGameInfoTest->gameIdLocal = "mobile_candylicious";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 13;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 45;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = -1692927663;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Candylicious";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 46;
	serverSlotGameInfoTest->gameId = "mobile_fruitilicious";
	serverSlotGameInfoTest->gameIdLocal = "mobile_fruitilicious";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 15;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 46;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = -1692927663;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Fruitilicious";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 47;
	serverSlotGameInfoTest->gameId = "mobile_kpop";
	serverSlotGameInfoTest->gameIdLocal = "mobile_kpop";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 36;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 47;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259978200;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "K-Pop";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 48;
	serverSlotGameInfoTest->gameId = "mobile_littlemonsters";
	serverSlotGameInfoTest->gameIdLocal = "mobile_littlemonsters";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 20;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 48;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = -1692927663;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Little Monster";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 49;
	serverSlotGameInfoTest->gameId = "mobile_mafia";
	serverSlotGameInfoTest->gameIdLocal = "mobile_mafia";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 22;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 49;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = -1692927663;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Mafia";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 50;
	serverSlotGameInfoTest->gameId = "mobile_sherlock";
	serverSlotGameInfoTest->gameIdLocal = "mobile_sherlock";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 25;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 50;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = -1692927663;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Sherlock";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 51;
	serverSlotGameInfoTest->gameId = "mobile_magicquest";
	serverSlotGameInfoTest->gameIdLocal = "mobile_magicquest";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 0;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 1;
	serverSlotGameInfoTest->minCrown = 30;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 51;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = -1692927663;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Magic Quest";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 52;
	serverSlotGameInfoTest->gameId = "mobile_bikinibeach";
	serverSlotGameInfoTest->gameIdLocal = "mobile_bikinibeach";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 45;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 1;
	serverSlotGameInfoTest->minCrown = 40;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 52;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1260172897;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Bikini Beach";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 53;
	serverSlotGameInfoTest->gameId = "mobile_4beauties";
	serverSlotGameInfoTest->gameIdLocal = "mobile_4beauties";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 40;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 1;
	serverSlotGameInfoTest->minCrown = 40;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 53;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1260155897;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Four Beauties";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 54;
	serverSlotGameInfoTest->gameId = "mobile_zeus";
	serverSlotGameInfoTest->gameIdLocal = "mobile_zeus";
	serverSlotGameInfoTest->newestVersion = "";
	serverSlotGameInfoTest->minLevel = 0;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 1;
	serverSlotGameInfoTest->minCrown = 100;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 54;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = -33918259;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Zeus";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 55;
	serverSlotGameInfoTest->gameId = "mobile_deepblue";
	serverSlotGameInfoTest->gameIdLocal = "deepblue";
	serverSlotGameInfoTest->newestVersion = "2017-01-11-01";
	serverSlotGameInfoTest->minLevel = 3;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 55;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259858908;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Deep Blue";
	listSlotGameInfo.insert(std::pair<int, ServerSlotGameInfo*>(serverSlotGameInfoTest->orderId, serverSlotGameInfoTest));

	return listSlotGameInfo;
}

std::deque<ServerSlotGameInfo*> TestManager::createUnlockedListGameSlotInfoTest() {
	std::deque<ServerSlotGameInfo*> listSlotGameInfo; 

	ServerSlotGameInfo * serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 40;
	serverSlotGameInfoTest->gameId = "mobile_nezha";
	serverSlotGameInfoTest->gameIdLocal = "legendofnezha";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 0;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 40;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 211695532;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Nezha";
	listSlotGameInfo.push_back( serverSlotGameInfoTest);

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 41;
	serverSlotGameInfoTest->gameId = "mobile_goldenegg";
	serverSlotGameInfoTest->gameIdLocal = "goldenegg";
	serverSlotGameInfoTest->newestVersion = "2016-09-06-01";
	serverSlotGameInfoTest->minLevel = 8;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 41;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259876109;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Golden Eggs";
	listSlotGameInfo.push_back(serverSlotGameInfoTest);

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 42;
	serverSlotGameInfoTest->gameId = "mobile_pharaoh";
	serverSlotGameInfoTest->gameIdLocal = "pharaoh";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 12;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 42;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259889909;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Pharaoh";
	listSlotGameInfo.push_back( serverSlotGameInfoTest);

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 43;
	serverSlotGameInfoTest->gameId = "mobile_boxing";
	serverSlotGameInfoTest->gameIdLocal = "boxing";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 17;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 43;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259911056;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Boxing";
	listSlotGameInfo.push_back( serverSlotGameInfoTest);

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 44;
	serverSlotGameInfoTest->gameId = "mobile_romanempire";
	serverSlotGameInfoTest->gameIdLocal = "romanempire";
	serverSlotGameInfoTest->newestVersion = "2016-08-15-01";
	serverSlotGameInfoTest->minLevel = 25;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 44;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259926353;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Roman Empire";
	listSlotGameInfo.push_back( serverSlotGameInfoTest);

	serverSlotGameInfoTest = new ServerSlotGameInfo();
	serverSlotGameInfoTest->orderId = 55;
	serverSlotGameInfoTest->gameId = "mobile_deepblue";
	serverSlotGameInfoTest->gameIdLocal = "deepblue";
	serverSlotGameInfoTest->newestVersion = "2017-01-11-01";
	serverSlotGameInfoTest->minLevel = 3;
	serverSlotGameInfoTest->platform = 1;
	serverSlotGameInfoTest->premiumType = 0;
	serverSlotGameInfoTest->minCrown = 0;
	serverSlotGameInfoTest->available = true;
	serverSlotGameInfoTest->id = 55;
	serverSlotGameInfoTest->timestampOfCreated = 1895736148;
	serverSlotGameInfoTest->timestampOfLastModified = 1259858908;
	serverSlotGameInfoTest->info = "";
	serverSlotGameInfoTest->name = "Deep Blue";
	listSlotGameInfo.push_back(serverSlotGameInfoTest);

	return listSlotGameInfo;
}

void TestManager::getFakeRespone(
	std::string url, std::function<void(rapidjson::Value &responseAsDocument)> callback) {
	string result = "";
	if (Helper4String::isStringContain(url, "/user/dailyBonusWheel/collect")) {
		result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1491901331024,'bean':{'bean_type':'BeanDailyBonusWheel','id':0,'ts_created':1491901331599,'ts_last_modified':1491901331599,'name':'','info':'','can_collect':false,'factor':3,'coin':100,'level_bonus':5000,'number_of_friend':13,'coin_per_friend':700,'total_coin':18950,'box':2,'vip_benefit':1.5,'scratch_card_reward':0,'current_scratch_card_info':'3, 5, 3, 4, 3, 0, 1'},'extra_info':null}";

	}

	std::replace(result.begin(), result.end(), '\'', '"'); // replace all 'x' to 'y'
	Document responseAsDocument;
	responseAsDocument.Parse(result.c_str());
	rapidjson::Value beanResponseAsDocument;
	beanResponseAsDocument = responseAsDocument[JSONFieldConstant::BEAN.c_str()];
	beanResponseAsDocument[JSONFieldConstant::ID.c_str()];

	callback(beanResponseAsDocument);
}

void TestManager::testBonusWheel(cocos2d::Node * parent) {

	/*test:test bonus wheel*/
	TestManager::getInstance()->getFakeRespone("/user/dailyBonusWheel/collect", [parent](rapidjson::Value &responseAsDocument) {

		auto infoMNG = InfoManager::getInstance();
		infoMNG->getAdditionalInfo()->dailyBonusWheelInfo->updateInfoByValue(responseAsDocument);
		PopupManager::getInstance()->getDailyBonusWheelPopup()->prepareAndShow(parent);

	});

}
void TestManager::testLuckyBox(cocos2d::Node * parent) {
	GiftInfo * giftInfo = new GiftInfo();
	giftInfo->type = LobbyConstant::LUCKY_BOX_SILVER_CHEST;
	//giftInfo->type = LobbyConstant::LUCKY_BOX_GOLD_CHEST;
	//giftInfo->type = LobbyConstant::LUCKY_BOX_RED_CHEST;
	giftInfo->coinReward = 100000000;
	giftInfo->crownReward = 100000000;
	giftInfo->luckyWheelReward = 100000000;
	PopupManager::getInstance()->getLuckyBoxPopup()->prepareAndShow(parent,giftInfo,/*number of box*/3,/*isCollectAll*/false,nullptr);
}

void TestManager::testLuckyWheel(cocos2d::Node * parent) {
	parent->scheduleOnce(
		[](float dt) {
		((BaseScene*)Helper4Scene::getRunningScene())->gotoLuckyWheelScene(0);
	}, 1.0, "TestManager::testLuckyWheel");
}

void TestManager::testCombackBonus(cocos2d::Node * parent) {
	parent->scheduleOnce(
		[parent](float dt) {
		PopupManager::getInstance()->getComebackBonusMobilePopup()->prepareAndShow(parent);
	}, 1.0, "TestManager::testLuckyWheel");
}

void TestManager::prepareTestLuckyWheel(cocos2d::Node * parent) {
	shouldAutoTestLuckyWheel = true;
	autoLogin(parent);
}

void TestManager::testUnlockPopup(cocos2d::Node * parent) {
	PopupManager::getInstance()->getGameUnlockedPopup()->prepareAndShow(createUnlockedListGameSlotInfoTest(), parent);
}

void TestManager::testUnlockFeature(cocos2d::Node * parent) {
	std::deque<std::string> listNewFeatureByLevel;
	listNewFeatureByLevel.push_back(LobbyConstant::API_BONUS_NAME_UFBL_CHOOSE_PAY_LINE);
	listNewFeatureByLevel.push_back(LobbyConstant::API_BONUS_NAME_UFBL_DAILY_CHANLLENGE);
	listNewFeatureByLevel.push_back(LobbyConstant::API_BONUS_NAME_UFBL_PIGGY_BANK);
	
	PopupManager::getInstance()->getGameUnlockedPopup()->prepareAndShow(listNewFeatureByLevel, parent);
}

void TestManager::testGameSlot(cocos2d::Node * parent) {
	
		parent->scheduleOnce(
			[](float dt) {
		//((BaseScene*)Helper4Scene::getRunningScene())->gotoGameSlotScene(ppEnum::GameSlotOrderId::NEZHA);
		//((BaseScene*)Helper4Scene::getRunningScene())->gotoGameSlotScene(ppEnum::GameSlotOrderId::DEEP_BLUE);
		//((BaseScene*)Helper4Scene::getRunningScene())->gotoGameSlotScene(ppEnum::GameSlotOrderId::GOLDEN_EGGS);
		//((BaseScene*)Helper4Scene::getRunningScene())->gotoGameSlotScene(ppEnum::GameSlotOrderId::PHARAOH);
		//((BaseScene*)Helper4Scene::getRunningScene())->gotoGameSlotScene(ppEnum::GameSlotOrderId::BOXING);
		((BaseScene*)Helper4Scene::getRunningScene())->gotoGameSlotScene(ppEnum::GameSlotOrderId::ROMAN_EMPIRE);
		}, 1.0, "TestManager::testGameSlot");
	
}

void TestManager::testDailyBonusStreak(cocos2d::Node * parent) {
	PopupManager::getInstance()->getDailyBonusStreakPopup()->prepareAndShow(this);
}

void TestManager::testLevelUpPopup(cocos2d::Node * parent) {
	PopupManager::getInstance()->getLevelUpPopup()->setGame((GameSlot::GameSlotScene*)BaseScene::getCurrentScene());
	PopupManager::getInstance()->getLevelUpPopup()->prepareAndShow(
		5,6,25000,200,/*isBoosterPackage*/true,/*isx10*/false
	);
}

void TestManager::testAchievementPopup(cocos2d::Node * parent) {
	parent->scheduleOnce(
		[parent](float dt) {
		PopupManager::getInstance()->getAchievementPopup()->prepareAndShow(parent);
	}, 1.0, "TestManager::testAchievementPopup");
}

void TestManager::prepareTestAchievementPopup(cocos2d::Node * parent) {
	shouldAutoTestAchievement = true;
	autoLogin(parent);
}

void TestManager::prepareTestCombackBonus(cocos2d::Node * parent) {
	shouldAutoEnterCombackBonus = true;
	autoLogin(parent);
}

void TestManager::prepareTestGameSlot(cocos2d::Node * parent) {
	shouldAutoEnterGameSlots = true;
	autoLogin(parent);
}


void TestManager::autoLogin(cocos2d::Node * parent) {

#if IS_DEBUG
	((LoginScene*)BaseScene::getCurrentScene())->getMainLoginLayer()->forceCallBtnLoginGuest(nullptr, ui::Widget::TouchEventType::ENDED);
#endif
}

void TestManager::check4AutoTest(cocos2d::Node * parent) {

	if (shouldAutoEnterGameSlots)
		testGameSlot(parent);
	shouldAutoEnterGameSlots = false;
	if (shouldAutoTestLuckyWheel)
		testLuckyWheel(parent);
	shouldAutoTestLuckyWheel = false;
	if (shouldAutoTestAchievement)
		testAchievementPopup(parent);
	shouldAutoTestAchievement = false;
	if (shouldAutoEnterCombackBonus)
		testCombackBonus(parent);
	shouldAutoEnterCombackBonus = false;
}

void TestManager::createTestButton(cocos2d::Node * parent) {


	PopupManager::getInstance()->initAllPopupLobbyScene();
	cocos2d::ui::Button* testButton = BasePopup::createGreenButton("Test", 50);;
	testButton->setPosition(Vec2(
		origin.x + 100 ,
		origin.y + visibleSize.height/2
	));
	//parent->scheduleOnce([=](float dt) {prepareTestGameSlot(parent);}, 2.0, "TestManager::prepareTestGameSlot");
	testButton->addTouchEventListener([=](cocos2d::Ref* sender, ui::Widget::TouchEventType touchEvent) {
		if (touchEvent != ui::Widget::TouchEventType::ENDED) return;

		//PopupManager::getInstance()->getNotificationPopup()->showUnfinishJobPopup(parent);
		//testLuckyBox(parent);
		//testUnlockPopup(parent);
		//testBonusWheel(parent);
		//prepareTestGameSlot(parent);
		//prepareTestCombackBonus(parent);
		//prepareTestLuckyWheel(parent);
		testLevelUpPopup(parent);
		//prepareTestAchievementPopup(parent);
		//testUnlockPopup(parent);
//		testUnlockFeature(parent);
	
	});
	parent->addChild(testButton);
}
