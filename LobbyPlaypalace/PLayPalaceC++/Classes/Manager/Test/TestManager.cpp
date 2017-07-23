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

void TestManager::getFakeXMLRespone(std::string url,std::function<void(bool isSuccess, tinyxml2::XMLDocument* response)> callback) {
    
    string result = "";
    
    if (Helper4String::isStringContain(url, "/gameplay/authorizationByToken")) {
        result = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><string>7855a823eb41bbb784634083d3ad941224ae15b87c96d220f7691467aada3f,2,104</string>";
    }
    else if (Helper4String::isStringContain(url, "/gameplay/getBalance")) {
        result = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><BALANCE CUR='USD'>3845500.00</BALANCE>";
    }
    else if (Helper4String::isStringContain(url, "getBet")) {
        result = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><bets bet='300.0' jackpot='0' lines='30' mp='1' multiply='1' promoFreeSpinLeft='0' tid='448' val='300,1500,8000,40000,80000,150000' wheel='6,1,0,1,10,0,1,8,0,5,7,6,6,9,9' cjackpot='0'/>";
    }
    else if (Helper4String::isStringContain(url, "spin")) {
        result = "<?xml version='1.0' encoding='UTF-8' standalone='yes'?><spin bet='300.0' lines='15' multiplier='1' promoFreeSpinLeft='0' scatter='0' tid='1812324' ts='1500737375' totalbet='4500.0' type='s' wild='0'><balance>265500.0</balance><bonus/><bonusposition/><jackpot/><tablewin/><wheels height='3' type='normal' val='4,7,4,4,6,4,5,3,6,3,6,1,6,2,9' width='5'/><win jackpot='0.0'>0.0</win><winposition/></spin>";
    }
    
    auto doc = new tinyxml2::XMLDocument();
    doc->Parse(result.c_str());
    callback(true, doc);
}

void TestManager::getFakeRespone(
	std::string url, std::function<void(rapidjson::Value &responseAsDocument)> callback) {
	string result = "";
	if (Helper4String::isStringContain(url, "/user/dailyBonusWheel/collect")) {
		result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1491901331024,'bean':{'bean_type':'BeanDailyBonusWheel','id':0,'ts_created':1491901331599,'ts_last_modified':1491901331599,'name':'','info':'','can_collect':false,'factor':3,'coin':100,'level_bonus':5000,'number_of_friend':13,'coin_per_friend':700,'total_coin':18950,'box':2,'vip_benefit':1.5,'scratch_card_reward':0,'current_scratch_card_info':'3, 5, 3, 4, 3, 0, 1'},'extra_info':null}";

    } else if (Helper4String::isStringContain(url, "login")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500301616619,'bean':{'bean_type':'BeanItemInfoUser','id':5326,'ts_created':1500301581791,'ts_last_modified':1500301616804,'name':'Guest 35309','info':'','accessToken':'proxy@playpalace@ee89186c-1cfe-4695-8b75-b3cefbaaeae6','facebookUID':'','level':0,'coin':250000.0,'rank':0,'expBar':0.0,'role':3,'status':1,'freeGift':1,'gift':0,'type':0,'Slot':null,'blackjack':null,'url_full_avatar':'','user_name':'750aud25710mas0noakal2kimh','is_activated':false,'test_user':false,'email':'','prefer_language':0,'web_background':0,'rs':1499917511455,'ts_login':'1500301616619','time_left_send_free_gift':0,'time_left_send_coin':0,'time_left_request_secret_key':0,'purchase_info_list':null,'purchase_amount':0.0,'extra_info':null,'comeback_bonus_gift':{'bean_type':'BeanComebackBonusGift','id':0,'ts_created':1500301616620,'ts_last_modified':1500301616620,'name':'','info':'','user_id':0,'coin_before_collection':0.0,'coin_after_collection':0.0,'bonus_coin':0.0,'timestamp_last_login':0,'status':0,'number_of_inactive_day':0,'bonus_coin_per_day':0.0},'check_loggedin_in_day':0,'first_login':false,'crown':0,'achievement_point':0,'time_change_name':0,'allow_play_tutorial':true,'allow_get_tutorial_spin_reward':true,'allow_get_pre_tutorial_reward':false,'remaining_exp':300000,'timestamp_last_login':1500301582764},'extra_info':null}";
    } else if (Helper4String::isStringContain(url, "/user/getAllData")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500470577984,'bean':{'bean_type':'BeanList','list_size':8,'member':[{'bean_type':'BeanMyProfile','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577985,'bean':{'bean_type':'BeanErrorNotLogin','rs':1499917511455},'extra_info':null},{'bean_type':'BeanCheckCollectCoin','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577985,'bean':{'bean_type':'BeanErrorNotLogin','rs':1499917511455},'extra_info':null},{'bean_type':'BeanSpecialOffer','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577986,'bean':{'bean_type':'BeanBasic'},'extra_info':null},{'bean_type':'BeanAllConfig','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577988,'bean':{'bean_type':'BeanErrorNotLogin','rs':1499917511455},'extra_info':null},{'bean_type':'BeanLinkGame','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577988,'bean':{'bean_type':'BeanErrorNotLogin','rs':1499917511455},'extra_info':null},{'bean_type':'BeanLevelConfig','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577988,'bean':{'bean_type':'BeanErrorNotLogin','rs':1499917511455},'extra_info':null},{'bean_type':'BeanAllListSlotGameInfo','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577989,'bean':{'bean_type':'BeanBasic'},'extra_info':null},{'bean_type':'BeanListBetSizeRestriction','core_result_code':-1001,'total_page':0,'reload':false,'ts_reload':1500470577989,'bean':{'bean_type':'BeanErrorNotLogin','rs':1499917511455},'extra_info':null}]},'extra_info':null}";
    }else if (Helper4String::isStringContain(url, "/user/featureConfig/getAll")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475201792,'bean':{'bean_type':'BeanList','list_size':11,'member':[{'bean_type':'BeanListDailyBonusStreakConfig','list_size':7,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201792,'ts_last_modified':1500475201792,'name':'daily_bonus_streak_coin_reward_1','info':'','value':'10000.0','strategy_type':2},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201793,'ts_last_modified':1500475201793,'name':'daily_bonus_streak_coin_reward_2','info':'','value':'20000.0','strategy_type':2},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201793,'ts_last_modified':1500475201793,'name':'daily_bonus_streak_coin_reward_3','info':'','value':'30000.0','strategy_type':2},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201793,'ts_last_modified':1500475201793,'name':'daily_bonus_streak_coin_reward_4','info':'','value':'40000.0','strategy_type':2},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201794,'ts_last_modified':1500475201794,'name':'daily_bonus_streak_coin_reward_5','info':'','value':'50000.0','strategy_type':2},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201794,'ts_last_modified':1500475201794,'name':'daily_bonus_streak_coin_reward_6','info':'','value':'60000.0','strategy_type':2},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'daily_bonus_streak_coin_reward_7','info':'','value':'0.0','strategy_type':2}]},{'bean_type':'BeanListFreeCoinGiftConfig','list_size':6,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'free_coin_gift_coin_reward_1','info':'','value':'30000','strategy_type':5},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'free_coin_gift_waiting_time_after_collecting_level_1','info':'','value':'10000','strategy_type':5},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'free_coin_gift_coin_reward_2','info':'','value':'15000','strategy_type':5},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'free_coin_gift_waiting_time_after_collecting_level_2','info':'','value':'10000','strategy_type':5},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'free_coin_gift_coin_reward_3','info':'','value':'8000','strategy_type':5},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'free_coin_gift_waiting_time_after_collecting_level_3','info':'','value':'2000','strategy_type':5}]},{'bean_type':'BeanListBoosterLevelUpBonusConfig','list_size':2,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'booster_level_up_bonus_multiplication_factor1','info':'','value':'10','strategy_type':0},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201795,'ts_last_modified':1500475201795,'name':'booster_level_up_bonus_multiplication_factor2','info':'','value':'2','strategy_type':0}]},{'bean_type':'BeanListUnlockFeatureByLevelConfig','list_size':3,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'unlock_feature_by_level_daily_challenge','info':'','value':'5','strategy_type':0},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'unlock_feature_by_level_piggy_bank','info':'','value':'10','strategy_type':0},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'unlock_feature_by_level_choose_pay_line','info':'','value':'3','strategy_type':0}]},{'bean_type':'BeanListLuckyWheelConfig','list_size':6,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'lucky_wheel_coin_reward_type1','info':'','value':'200000','strategy_type':9},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'lucky_wheel_coin_reward_type2','info':'','value':'400000','strategy_type':9},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'lucky_wheel_coin_reward_type3','info':'','value':'600000','strategy_type':9},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'lucky_wheel_coin_reward_type4','info':'','value':'1000000','strategy_type':9},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'lucky_wheel_coin_reward_type5','info':'','value':'3000000','strategy_type':9},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201796,'ts_last_modified':1500475201796,'name':'lucky_wheel_crown_reward_type6','info':'','value':'5','strategy_type':9}]},{'bean_type':'BeanListDailyChallengeConfig','list_size':5,'member':[{'bean_type':'BeanDailyChallengeTaskConfig','id':1,'ts_created':1477452097035,'ts_last_modified':1478769736143,'name':'DAILY_CHALLENGE_TYPE_LEVEL_UP','info':'','daily_challenge_task_goal':1,'daily_challenge_task_type':1,'is_activated':true},{'bean_type':'BeanDailyChallengeTaskConfig','id':4,'ts_created':1477452097035,'ts_last_modified':1479869555792,'name':'DAILY_CHALLENGE_TYPE_COLLECT_FREE_COIN_GIFT','info':'','daily_challenge_task_goal':10,'daily_challenge_task_type':4,'is_activated':true},{'bean_type':'BeanDailyChallengeTaskConfig','id':6,'ts_created':1477452097035,'ts_last_modified':1489196758806,'name':'DAILY_CHALLENGE_TYPE_MAX_BET','info':'','daily_challenge_task_goal':20,'daily_challenge_task_type':6,'is_activated':true},{'bean_type':'BeanDailyChallengeTaskConfig','id':9,'ts_created':1477452097035,'ts_last_modified':1478590997848,'name':'DAILY_CHALLENGE_TYPE_TOTAL_BET','info':'','daily_challenge_task_goal':100000,'daily_challenge_task_type':9,'is_activated':true},{'bean_type':'BeanDailyChallengeTaskConfig','id':10,'ts_created':1477452097035,'ts_last_modified':1478591001897,'name':'DAILY_CHALLENGE_TYPE_TOTAL_WIN','info':'','daily_challenge_task_goal':100000,'daily_challenge_task_type':10,'is_activated':true}]},{'bean_type':'BeanMobileSlotGameConfig','list_size':6,'member':[{'bean_type':'BeanMobileSlotGameConfig','id':1,'ts_created':1477903519265,'ts_last_modified':1477903519265,'name':'DeepBlue','info':'','slot_game_info_id':55},{'bean_type':'BeanMobileSlotGameConfig','id':2,'ts_created':1477903519265,'ts_last_modified':1477903519265,'name':'GoldenEggs','info':'','slot_game_info_id':41},{'bean_type':'BeanMobileSlotGameConfig','id':3,'ts_created':1477903519265,'ts_last_modified':1477903519265,'name':'RomanEmpire','info':'','slot_game_info_id':44},{'bean_type':'BeanMobileSlotGameConfig','id':4,'ts_created':1477903519265,'ts_last_modified':1477903519265,'name':'Pharaoh','info':'','slot_game_info_id':42},{'bean_type':'BeanMobileSlotGameConfig','id':5,'ts_created':1477903519265,'ts_last_modified':1477903519265,'name':'Boxing','info':'','slot_game_info_id':43},{'bean_type':'BeanMobileSlotGameConfig','id':6,'ts_created':1477903519265,'ts_last_modified':1477903519265,'name':'Nezha','info':'','slot_game_info_id':40}]},{'bean_type':'BeanMobileSlotGamePaylineConfig','list_size':66,'member':[{'bean_type':'BeanMobileSlotGamePaylineConfig','id':1,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':1,'game_id':1,'max_bet_per_line':400.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':2,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':1,'game_id':2,'max_bet_per_line':400.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':3,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':1,'game_id':3,'max_bet_per_line':300.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':4,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':1,'game_id':4,'max_bet_per_line':300.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':5,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':1,'game_id':5,'max_bet_per_line':400.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':6,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':1,'game_id':6,'max_bet_per_line':300.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':7,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':3,'game_id':1,'max_bet_per_line':3000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':8,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':3,'game_id':2,'max_bet_per_line':3000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':9,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':3,'game_id':3,'max_bet_per_line':1500.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':10,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':3,'game_id':4,'max_bet_per_line':3000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':11,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':3,'game_id':5,'max_bet_per_line':3000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':12,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':3,'game_id':6,'max_bet_per_line':1500.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':13,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':8,'game_id':1,'max_bet_per_line':3000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':14,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':8,'game_id':2,'max_bet_per_line':3000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':15,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':8,'game_id':3,'max_bet_per_line':1500.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':16,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':8,'game_id':4,'max_bet_per_line':3000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':17,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':8,'game_id':5,'max_bet_per_line':3000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':18,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':8,'game_id':6,'max_bet_per_line':1500.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':19,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':12,'game_id':1,'max_bet_per_line':15000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':20,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':12,'game_id':2,'max_bet_per_line':15000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':21,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':12,'game_id':3,'max_bet_per_line':8000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':22,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':12,'game_id':4,'max_bet_per_line':10000.0,'max_payline':10},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':23,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':12,'game_id':5,'max_bet_per_line':15000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':24,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':12,'game_id':6,'max_bet_per_line':8000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':25,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':17,'game_id':1,'max_bet_per_line':15000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':26,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':17,'game_id':2,'max_bet_per_line':15000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':27,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':17,'game_id':3,'max_bet_per_line':8000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':28,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':17,'game_id':4,'max_bet_per_line':10000.0,'max_payline':20},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':29,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':17,'game_id':5,'max_bet_per_line':15000.0,'max_payline':10},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':30,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':17,'game_id':6,'max_bet_per_line':8000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':31,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':25,'game_id':1,'max_bet_per_line':25000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':32,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':25,'game_id':2,'max_bet_per_line':25000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':33,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':25,'game_id':3,'max_bet_per_line':40000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':34,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':25,'game_id':4,'max_bet_per_line':30000.0,'max_payline':20},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':35,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':25,'game_id':5,'max_bet_per_line':30000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':36,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':25,'game_id':6,'max_bet_per_line':40000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':37,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':30,'game_id':1,'max_bet_per_line':50000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':38,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':30,'game_id':2,'max_bet_per_line':50000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':39,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':30,'game_id':3,'max_bet_per_line':80000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':40,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':30,'game_id':4,'max_bet_per_line':50000.0,'max_payline':20},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':41,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':30,'game_id':5,'max_bet_per_line':100000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':42,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':30,'game_id':6,'max_bet_per_line':80000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':43,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':10,'game_id':1,'max_bet_per_line':15000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':44,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':10,'game_id':2,'max_bet_per_line':15000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':45,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':10,'game_id':3,'max_bet_per_line':8000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':46,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':10,'game_id':4,'max_bet_per_line':10000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':47,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':10,'game_id':5,'max_bet_per_line':15000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':48,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':10,'game_id':6,'max_bet_per_line':8000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':49,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':18,'game_id':1,'max_bet_per_line':25000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':50,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':18,'game_id':2,'max_bet_per_line':25000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':51,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':18,'game_id':3,'max_bet_per_line':40000.0,'max_payline':0},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':52,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':18,'game_id':4,'max_bet_per_line':30000.0,'max_payline':20},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':53,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':18,'game_id':5,'max_bet_per_line':30000.0,'max_payline':10},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':54,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':18,'game_id':6,'max_bet_per_line':40000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':55,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':28,'game_id':1,'max_bet_per_line':50000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':56,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':28,'game_id':2,'max_bet_per_line':50000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':57,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':28,'game_id':3,'max_bet_per_line':80000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':58,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':28,'game_id':4,'max_bet_per_line':50000.0,'max_payline':20},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':59,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':28,'game_id':5,'max_bet_per_line':100000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':60,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':28,'game_id':6,'max_bet_per_line':80000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':61,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':38,'game_id':1,'max_bet_per_line':120000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':62,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':38,'game_id':2,'max_bet_per_line':120000.0,'max_payline':25},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':63,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':38,'game_id':3,'max_bet_per_line':150000.0,'max_payline':30},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':64,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':38,'game_id':4,'max_bet_per_line':150000.0,'max_payline':20},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':65,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':38,'game_id':5,'max_bet_per_line':200000.0,'max_payline':15},{'bean_type':'BeanMobileSlotGamePaylineConfig','id':66,'ts_created':1477897084477,'ts_last_modified':1477897084477,'name':'','info':'','level_id':38,'game_id':6,'max_bet_per_line':150000.0,'max_payline':30}]},{'bean_type':'BeanListLuckyBoxConfig','list_size':17,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_coin_reward_type1','info':'','value':'400000','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_coin_reward_type2','info':'','value':'800000','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_coin_reward_type3','info':'','value':'2000000','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_crown_reward_type1','info':'','value':'5','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_crown_reward_type2','info':'','value':'10','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_crown_reward_type3','info':'','value':'20','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_spin_of_lucky_wheel_reward_type3','info':'','value':'2','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_coin_reward_type1','info':'','value':'900000','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_coin_reward_type2','info':'','value':'1700000','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_coin_reward_type3','info':'','value':'4500000','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_crown_reward_type1','info':'','value':'10','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_crown_reward_type2','info':'','value':'20','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_crown_reward_type3','info':'','value':'40','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_spin_of_lucky_wheel_reward_type3','info':'','value':'4','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_price_type1','info':'','value':'1','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_price_type2','info':'','value':'2','strategy_type':11},{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'lucky_box_buy_and_double_price_type3','info':'','value':'5','strategy_type':11}]},{'bean_type':'BeanListMagicItemConfig','list_size':1,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201797,'ts_last_modified':1500475201797,'name':'min_number_of_consecutive_video_view_to_receive_magic_item_reward','info':'','value':'2','strategy_type':15}]},{'bean_type':'BeanListFlipCardConfig','list_size':2,'member':[{'bean_type':'BeanStrategyConfig','id':0,'ts_created':1500475201798,'ts_last_modified':1500475201798,'name':'flip_card_waiting_time','info':'','value':'3600000','strategy_type':23},{'bean_type':'BeanList','list_size':28,'member':[{'bean_type':'BeanFlipCardConfig','id':1,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':1,'card_level':1,'coin_reward':5000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':2,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':2,'card_level':1,'coin_reward':5000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':3,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':3,'card_level':1,'coin_reward':5000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':4,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':4,'card_level':1,'coin_reward':5000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':5,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':5,'card_level':1,'coin_reward':5000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':6,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':6,'card_level':1,'coin_reward':10000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':7,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':7,'card_level':1,'coin_reward':12000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':8,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':8,'card_level':1,'coin_reward':0.0,'crown_reward':0,'leaf_reward':1,'leaf_upgrade_requirement':0},{'bean_type':'BeanFlipCardConfig','id':9,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':1,'card_level':2,'coin_reward':6000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':2},{'bean_type':'BeanFlipCardConfig','id':10,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':2,'card_level':2,'coin_reward':6000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':2},{'bean_type':'BeanFlipCardConfig','id':11,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':3,'card_level':2,'coin_reward':6000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':2},{'bean_type':'BeanFlipCardConfig','id':12,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':4,'card_level':2,'coin_reward':6000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':2},{'bean_type':'BeanFlipCardConfig','id':13,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':5,'card_level':2,'coin_reward':6000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':2},{'bean_type':'BeanFlipCardConfig','id':14,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':1,'card_level':3,'coin_reward':8000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':3},{'bean_type':'BeanFlipCardConfig','id':15,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':2,'card_level':3,'coin_reward':8000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':3},{'bean_type':'BeanFlipCardConfig','id':16,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':3,'card_level':3,'coin_reward':8000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':3},{'bean_type':'BeanFlipCardConfig','id':17,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':4,'card_level':3,'coin_reward':8000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':3},{'bean_type':'BeanFlipCardConfig','id':18,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':5,'card_level':3,'coin_reward':8000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':3},{'bean_type':'BeanFlipCardConfig','id':19,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':1,'card_level':4,'coin_reward':10000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':4},{'bean_type':'BeanFlipCardConfig','id':20,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':2,'card_level':4,'coin_reward':10000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':4},{'bean_type':'BeanFlipCardConfig','id':21,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':3,'card_level':4,'coin_reward':10000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':4},{'bean_type':'BeanFlipCardConfig','id':22,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':4,'card_level':4,'coin_reward':10000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':4},{'bean_type':'BeanFlipCardConfig','id':23,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':5,'card_level':4,'coin_reward':10000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':4},{'bean_type':'BeanFlipCardConfig','id':24,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':1,'card_level':5,'coin_reward':12000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':5},{'bean_type':'BeanFlipCardConfig','id':25,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':2,'card_level':5,'coin_reward':12000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':5},{'bean_type':'BeanFlipCardConfig','id':26,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':3,'card_level':5,'coin_reward':12000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':5},{'bean_type':'BeanFlipCardConfig','id':27,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':4,'card_level':5,'coin_reward':12000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':5},{'bean_type':'BeanFlipCardConfig','id':28,'ts_created':1494302894000,'ts_last_modified':1494302894000,'name':'','info':'','card_type':5,'card_level':5,'coin_reward':12000.0,'crown_reward':0,'leaf_reward':0,'leaf_upgrade_requirement':5}]}]}]},'extra_info':null}";
    }else if (Helper4String::isStringContain(url, "/user/profile")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475424678,'bean':{'bean_type':'BeanItemInfoUser','id':104,'ts_created':1439453961396,'ts_last_modified':1500475156528,'name':'quan2','info':'','accessToken':'proxy@playpalace@16b75064-6644-496e-8a51-f35b4d9c5958','facebookUID':'','level':37,'coin':3835500.0,'rank':55,'expBar':0.048699173553719007,'role':2,'status':1,'freeGift':1,'gift':1,'type':2,'Slot':{'numOfJackpot':0,'biggestWin':3.375E8,'numOfBonus':23,'totalSpin':1854,'percentWin':55.609492988133766,'numOfFreeSpin':44,'netProfit':1.6829069E9,'win':1031},'blackjack':{'biggestWin':0.0,'numberOfWin':0,'numberOfPlay':1,'maxWinInARow':0,'netProfit':-30000.0,'specialField':'0'},'url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-09/104-0-4b90bee29372d06950ccb3098cddaff9a853fd517288bd714eae32e4a481.jpeg','user_name':'quandm1993@gmail.com','is_activated':true,'test_user':false,'email':'','prefer_language':0,'web_background':0,'rs':1499917511455,'ts_login':'','time_left_send_free_gift':0,'time_left_send_coin':0,'time_left_request_secret_key':0,'purchase_info_list':null,'purchase_amount':0.0,'extra_info':null,'comeback_bonus_gift':{'bean_type':'BeanComebackBonusGift','id':0,'ts_created':1500475424680,'ts_last_modified':1500475424680,'name':'','info':'','user_id':0,'coin_before_collection':0.0,'coin_after_collection':0.0,'bonus_coin':0.0,'timestamp_last_login':0,'status':0,'number_of_inactive_day':0,'bonus_coin_per_day':0.0},'check_loggedin_in_day':0,'crown':156,'achievement_point':50,'time_change_name':2,'allow_play_tutorial':false,'allow_get_tutorial_spin_reward':false,'allow_get_pre_tutorial_reward':false,'remaining_exp':57553700,'timestamp_last_login':1500475156528},'extra_info':null}";
    }else if (Helper4String::isStringContain(url, "/user/getAdditionalInfo")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787078,'bean':{'bean_type':'BeanList','list_size':14,'member':[{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787079,'bean':{'bean_type':'BeanDailyBonusStreak','id':0,'ts_created':1500475787085,'ts_last_modified':1500475787085,'name':'','info':'','daily_streak':1,'can_collect':true,'coin_reward':10000.0,'magic_item_reward_quantity':0,'magic_item_reward_type':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787085,'bean':{'bean_type':'BeanFreeCoinGift','id':0,'ts_created':1500475787086,'ts_last_modified':1500475787086,'name':'','info':'','can_collect':true,'coin_reward':30000.0,'waiting_time':0,'number_of_times_collect_free_coin_gift':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787086,'bean':{'bean_type':'BeanBooster','id':0,'ts_created':1500475787086,'ts_last_modified':1500475787086,'name':'','info':'','remaining_time_of_booster_level_up_bonus':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787086,'bean':{'bean_type':'BeanReferenceCode','id':0,'ts_created':1500475787086,'ts_last_modified':1500475787086,'name':'','info':'','reference_code':'DuYsG8','number_of_times_reference_code_is_used':0,'referee_reference_code':''},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787086,'bean':{'bean_type':'BeanDailyBonusLuckySpin','id':0,'ts_created':1500475787086,'ts_last_modified':1500475787086,'name':'','info':'','can_collect':true,'coin_reward':0.0,'crown_reward':0,'reel_values':''},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':-60120,'total_page':0,'reload':false,'ts_reload':1500475787086,'bean':{'bean_type':'BeanBasic'},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787086,'bean':{'bean_type':'BeanLuckyWheel','id':0,'ts_created':1500475787086,'ts_last_modified':1500475787086,'name':'','info':'','coin_reward':0.0,'crown_reward':0,'remaining_spin':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787086,'bean':{'bean_type':'BeanLuckyBox','id':0,'ts_created':1500475787086,'ts_last_modified':1500475787086,'name':'','info':'','coin_reward':0.0,'crown_reward':0,'spin_of_lucky_wheel_reward':0,'remaining_lucky_box_type1':0,'remaining_lucky_box_type2':0,'remaining_lucky_box_type3':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787086,'bean':{'bean_type':'BeanPiggyBank','id':0,'ts_created':1500475787088,'ts_last_modified':1500475787088,'name':'','info':'','piggy_bank_coin':43140.0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787088,'bean':{'bean_type':'BeanComebackBonusMobile','id':0,'ts_created':1500475787107,'ts_last_modified':1500475787107,'name':'','info':'','can_collect':false,'number_of_comeback_times':0,'coin_reward':0.0,'increased_percentage_of_exp':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787107,'bean':{'bean_type':'BeanMagicItem','id':0,'ts_created':1500475787107,'ts_last_modified':1500475787107,'name':'','info':'','active_magic_item_type':0,'remaining_package_of_magic_item_100_percent_big_win':0,'remaining_spin_of_magic_item_100_percent_big_win':0,'remaining_package_of_magic_item_100_percent_mega_win':0,'remaining_spin_of_magic_item_100_percent_mega_win':0,'remaining_package_of_magic_item_lucky_spin_type_1':0,'remaining_spin_of_magic_item_lucky_spin_type_1':0,'remaining_package_of_magic_item_lucky_spin_type_2':0,'remaining_spin_of_magic_item_lucky_spin_type_2':0,'remaining_package_of_magic_item_double_exp':0,'remaining_time_of_magic_item_double_exp':0,'remaining_package_of_magic_item_lucky_symbol':0,'remaining_time_of_magic_item_lucky_symbol':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787107,'bean':{'bean_type':'BeanScratchCardInfo','id':0,'ts_created':1500475787108,'ts_last_modified':1500475787108,'name':'','info':'','remaining_scratch_card':0,'coin_reward':0.0,'current_scratch_card_info':'','next_scratch_card_info':''},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787108,'bean':{'bean_type':'BeanFeedback','id':0,'ts_created':1500475787108,'ts_last_modified':1500475787108,'name':'','info':'','feedback_status':0},'extra_info':null},{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500475787108,'bean':{'bean_type':'BeanFlipCardInfo','id':0,'ts_created':1500475787109,'ts_last_modified':1500475787109,'name':'','info':'','flip_card_value':'','remaining_waiting_time':0,'show_flip_card_detail':false,'can_redeem_flip_card_reward':false,'leaf':0},'extra_info':null}]},'extra_info':null}";
    }else if (Helper4String::isStringContain(url, "/user/gift/getAll")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500476874618,'bean':{'bean_type':'BeanList','list_size':0,'member':[]},'extra_info':null}";
    }else if (Helper4String::isStringContain(url, "/user/achievement/listAllOfCurrentUser")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500477001391,'bean':{'bean_type':'BeanList','list_size':13,'member':[{'bean_type':'BeanItemInfoUserAchievement','id':8724,'ts_created':1461295412953,'ts_last_modified':1461295412953,'name':'Completed Tutorial','info':'','group_type':0,'category_id':0,'category_name':'Personal Progression','sub_category_id':0,'sub_category_name':'Ready-to-Play','star':3,'achievement_type':0,'coin_reward':50000.0,'achievement_point_reward':5,'crown_reward':0,'achievement_goal':1,'user_id':104,'achievement_id':1,'current_status':1,'is_complete':true,'is_collected':false,'is_only_one_achievement':true},{'bean_type':'BeanItemInfoUserAchievement','id':8725,'ts_created':1461295413385,'ts_last_modified':1461295413385,'name':'Consecutive Login for 5 days','info':'','group_type':0,'category_id':0,'category_name':'Personal Progression','sub_category_id':1,'sub_category_name':'Loyalty','star':1,'achievement_type':1,'coin_reward':50000.0,'achievement_point_reward':5,'crown_reward':0,'achievement_goal':5,'user_id':104,'achievement_id':2,'current_status':1,'is_complete':false,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8730,'ts_created':1461295415467,'ts_last_modified':1461295415467,'name':'Level 15 Achieved','info':'','group_type':0,'category_id':0,'category_name':'Personal Progression','sub_category_id':2,'sub_category_name':'Journeyman','star':3,'achievement_type':2,'coin_reward':50000.0,'achievement_point_reward':10,'crown_reward':0,'achievement_goal':15,'user_id':104,'achievement_id':7,'current_status':15,'is_complete':true,'is_collected':true,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8733,'ts_created':1461295416716,'ts_last_modified':1461295416716,'name':'Level 50 Achieved','info':'','group_type':0,'category_id':0,'category_name':'Personal Progression','sub_category_id':3,'sub_category_name':'Explorer','star':3,'achievement_type':2,'coin_reward':100000.0,'achievement_point_reward':10,'crown_reward':0,'achievement_goal':50,'user_id':104,'achievement_id':10,'current_status':38,'is_complete':false,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8738,'ts_created':1461295418795,'ts_last_modified':1461295418795,'name':'Spin 200 Times on Slot','info':'','group_type':0,'category_id':1,'category_name':'Spin Mania','sub_category_id':5,'sub_category_name':'Spin Junior','star':2,'achievement_type':3,'coin_reward':25000.0,'achievement_point_reward':10,'crown_reward':0,'achievement_goal':200,'user_id':104,'achievement_id':15,'current_status':200,'is_complete':true,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8743,'ts_created':1461295420873,'ts_last_modified':1461295420873,'name':'First time deposit','info':'','group_type':0,'category_id':2,'category_name':'Loyalist','sub_category_id':7,'sub_category_name':'Loyal Supporter','star':3,'achievement_type':4,'coin_reward':80000.0,'achievement_point_reward':50,'crown_reward':0,'achievement_goal':1,'user_id':104,'achievement_id':20,'current_status':1,'is_complete':true,'is_collected':false,'is_only_one_achievement':true},{'bean_type':'BeanItemInfoUserAchievement','id':8744,'ts_created':1461295421290,'ts_last_modified':1461295421290,'name':'100 Achievement Points','info':'','group_type':0,'category_id':2,'category_name':'Loyalist','sub_category_id':8,'sub_category_name':'Achiever','star':1,'achievement_type':5,'coin_reward':0.0,'achievement_point_reward':0,'crown_reward':10,'achievement_goal':100,'user_id':104,'achievement_id':21,'current_status':50,'is_complete':false,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8747,'ts_created':1461295422538,'ts_last_modified':1461295422538,'name':'100,000 Total Win','info':'','group_type':1,'category_id':3,'category_name':'Winnings','sub_category_id':9,'sub_category_name':'Novice','star':1,'achievement_type':7,'coin_reward':20000.0,'achievement_point_reward':5,'crown_reward':0,'achievement_goal':100000,'user_id':104,'achievement_id':24,'current_status':100000,'is_complete':true,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8753,'ts_created':1461295425033,'ts_last_modified':1461295425033,'name':'50,000 Total Bet','info':'','group_type':1,'category_id':4,'category_name':'Betting Mania','sub_category_id':11,'sub_category_name':'Junior Roller','star':1,'achievement_type':8,'coin_reward':10000.0,'achievement_point_reward':5,'crown_reward':0,'achievement_goal':50000,'user_id':104,'achievement_id':30,'current_status':50000,'is_complete':true,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8759,'ts_created':1461295427530,'ts_last_modified':1461295427530,'name':'Sent Invites to 5 Friends','info':'','group_type':2,'category_id':5,'category_name':'Friends with Benefits','sub_category_id':13,'sub_category_name':'Party Organiser','star':1,'achievement_type':9,'coin_reward':20000.0,'achievement_point_reward':10,'crown_reward':0,'achievement_goal':5,'user_id':104,'achievement_id':36,'current_status':0,'is_complete':false,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8762,'ts_created':1461295428781,'ts_last_modified':1461295428781,'name':'Sent gifts to 5 Friends','info':'','group_type':2,'category_id':5,'category_name':'Friends with Benefits','sub_category_id':14,'sub_category_name':'Good Samaritan ','star':1,'achievement_type':10,'coin_reward':20000.0,'achievement_point_reward':5,'crown_reward':0,'achievement_goal':5,'user_id':104,'achievement_id':39,'current_status':0,'is_complete':false,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8765,'ts_created':1461295430026,'ts_last_modified':1461295430026,'name':'Received 5 gifts from friends','info':'','group_type':2,'category_id':5,'category_name':'Friends with Benefits','sub_category_id':15,'sub_category_name':'Socialite','star':1,'achievement_type':11,'coin_reward':10000.0,'achievement_point_reward':5,'crown_reward':0,'achievement_goal':5,'user_id':104,'achievement_id':42,'current_status':0,'is_complete':false,'is_collected':false,'is_only_one_achievement':false},{'bean_type':'BeanItemInfoUserAchievement','id':8768,'ts_created':1461295431275,'ts_last_modified':1461295431275,'name':'Linked Account to Facebook','info':'','group_type':2,'category_id':6,'category_name':'Socially Connected','sub_category_id':16,'sub_category_name':'Linked Account to Facebook','star':3,'achievement_type':12,'coin_reward':100000.0,'achievement_point_reward':20,'crown_reward':0,'achievement_goal':1,'user_id':104,'achievement_id':45,'current_status':0,'is_complete':false,'is_collected':false,'is_only_one_achievement':true}]},'extra_info':null}";
    }else if (Helper4String::isStringContain(url, "/user/me/checkSpecialOffer")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500477118027,'bean':{'bean_type':'BeanList','list_size':1,'member':[{'bean_type':'BeanSpecialOffer','id':1,'ts_created':1452478432607,'ts_last_modified':1452478432607,'name':'Limited time offer','info':'880,000 coins package','coin_reward':880000.0,'remaining_amount':99,'remaining_time':11926081968,'bonus_percent':120.0}]},'extra_info':null}";
    }
    else if (Helper4String::isStringContain(url, "/user/me/getLeaderboard")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500480323335,'bean':{'bean_type':'BeanList','list_size':100,'member':[{'bean_type':'BeanItemInfo','id':2313,'ts_created':1462597504393,'ts_last_modified':1463222775523,'name':'2313','info':'','level':29,'coin':9.999991323400205E13,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-05/2313-0-44d8ae94e8d9f9f9c09d26e476fc8fa1ecee7a77e1528fa08aa5dcd1d679fc6.png','vip_type':5},{'bean_type':'BeanItemInfo','id':1741,'ts_created':1456970705851,'ts_last_modified':1463450288252,'name':'ghju','info':'','level':16,'coin':9.999991336E11,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-04/1741-0-5ad5ddb1840d4f07f5e962b6767a04ca16271e377a3ac6d168a47458e5662a.jpeg','vip_type':0},{'bean_type':'BeanItemInfo','id':15,'ts_created':1434528229066,'ts_last_modified':1454035815354,'name':'Đây là cờ lone','info':'','level':38,'coin':9.963311531927E10,'slot_total_bet':0.0,'facebookUID':'105768529761247','url_full_avatar':'','vip_type':2},{'bean_type':'BeanItemInfo','id':34,'ts_created':1435725277376,'ts_last_modified':1466474027831,'name':'Leon Lim','info':'','level':10,'coin':1.302413750008E10,'slot_total_bet':0.0,'facebookUID':'10154079715339062','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2293,'ts_created':1461916799064,'ts_last_modified':1490072557785,'name':'TESTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT','info':'','level':57,'coin':9.9701604E9,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-03/2293-0-f64d132cc4fa5bc5bc974524b04d1a4edb46e3c9d3ebd39b8198ff7b387ce78.png','vip_type':0},{'bean_type':'BeanItemInfo','id':1669,'ts_created':1456201615883,'ts_last_modified':1497456237459,'name':'DUY','info':'','level':16,'coin':3.65544073E9,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-05/1669-0-3447e7ed88117bfc15b02cd0ee2e97439738579e91f241a6c994a9e53ad1a146.png','vip_type':5},{'bean_type':'BeanItemInfo','id':405,'ts_created':1466131609504,'ts_last_modified':1489142823757,'name':'Anthony','info':'','level':1,'coin':1.8749098E9,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-03/405-0-ed5b8a9f76ca28a9b78676f05eaadb123159ca39d72c15fc1a9f6e1ba68b9a6.png','vip_type':5},{'bean_type':'BeanItemInfo','id':356,'ts_created':1449722430794,'ts_last_modified':1491194320330,'name':'kiet3@gmail.com','info':'','level':5,'coin':1.111116111E9,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-06/356-0-b798aab1bcefad7e483934d5f10824a40495e2ec530a057bd3a975bff52b9b.jpeg','vip_type':0},{'bean_type':'BeanItemInfo','id':2291,'ts_created':1461915680533,'ts_last_modified':1489117161006,'name':'FDFDFASDASDEDASDASDASDASDASD','info':'','level':0,'coin':1.0008207E9,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':5},{'bean_type':'BeanItemInfo','id':109,'ts_created':1438579458088,'ts_last_modified':1455954832683,'name':'dominhquan.uit@gmail.com','info':'','level':101,'coin':1.0000658E9,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-02/109-0-e98822d84ad977bcbcf8f6e85638ae1cc755b7d0302896b0d91ef0edb741a.jpeg','vip_type':0},{'bean_type':'BeanItemInfo','id':2036,'ts_created':1459477390476,'ts_last_modified':1459483403511,'name':'thanh01@gmail.com','info':'','level':17,'coin':9.63637E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-04/2036-0-b311741d3fa1face5eef439975119530251b94102f42c3e77f33a7bc31f6.jpeg','vip_type':0},{'bean_type':'BeanItemInfo','id':355,'ts_created':1449722338274,'ts_last_modified':1493871927769,'name':'TranThiKimOanh TranThiKim','info':'','level':9,'coin':9.565543E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-03/355-0-1ff359ac9b25f273b727f379bb56f22bd3d4db9cfb9f15cfdbee608db5c7d5ed.png','vip_type':5},{'bean_type':'BeanItemInfo','id':53,'ts_created':1437209289067,'ts_last_modified':1452940376427,'name':'Hoang Anh','info':'','level':36,'coin':9.1818823524E8,'slot_total_bet':0.0,'facebookUID':'1433937303601318','url_full_avatar':'','vip_type':4},{'bean_type':'BeanItemInfo','id':7,'ts_created':1465003921737,'ts_last_modified':1495247554291,'name':'Thien Tien Trang','info':'','level':54,'coin':8.5125133E8,'slot_total_bet':0.0,'facebookUID':'1616043135279470','url_full_avatar':'','vip_type':1},{'bean_type':'BeanItemInfo','id':4796,'ts_created':1488960419805,'ts_last_modified':1497452840002,'name':'huy','info':'','level':50,'coin':8.404452E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-05/4796-0-839ba0ba1fc5a81df921d773d74e8ca8aa1c4bea8ab98978465d5f2f9a30c043.png','vip_type':2},{'bean_type':'BeanItemInfo','id':16,'ts_created':1434529436123,'ts_last_modified':1482141393632,'name':'Dino Nguyen','info':'','level':40,'coin':6.7503836735E8,'slot_total_bet':0.0,'facebookUID':'1503176979972718','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':354,'ts_created':1463993836453,'ts_last_modified':1493865515753,'name':'meomeo1@gmail.com','info':'','level':2,'coin':4.95987423E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-06/354-0-989b802c82c8a4bbd418a9396569b116faa3158a7ece93ad3639ec7f41728cd.png','vip_type':0},{'bean_type':'BeanItemInfo','id':2575,'ts_created':1462936951696,'ts_last_modified':1484125637403,'name':'meomeo','info':'','level':39,'coin':3.081185E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-12/2575-0-c7bbe21ba3b48329aa5ef8c4f1b5ba9abe27bd6b314470397c1c25fd8f7f8c.png','vip_type':0},{'bean_type':'BeanItemInfo','id':370,'ts_created':1449807241089,'ts_last_modified':1463224042757,'name':'Play Palace','info':'','level':27,'coin':2.57830925E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-05/370-0-13fe1a4bffdb44307db1d2851c2298fef5b7deb88f1258372d983b6d0874274.png','vip_type':0},{'bean_type':'BeanItemInfo','id':2201,'ts_created':1461059104642,'ts_last_modified':1500474183625,'name':'Cá','info':'','level':26,'coin':2.12327659E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-05/2201-0-a5a9faea65e7f6322890951d853ba7d56df3ed1b7342a13fae356dd8b53ba1.png','vip_type':5},{'bean_type':'BeanItemInfo','id':1905,'ts_created':1466506075211,'ts_last_modified':1496928157409,'name':'Lê Jobs','info':'','level':25,'coin':1.60710172E8,'slot_total_bet':0.0,'facebookUID':'116718895364350','url_full_avatar':'','vip_type':3},{'bean_type':'BeanItemInfo','id':2368,'ts_created':1462263254268,'ts_last_modified':1464864143049,'name':'Dino Cal','info':'','level':54,'coin':1.1660089999E8,'slot_total_bet':0.0,'facebookUID':'105559556527845','url_full_avatar':'','vip_type':3},{'bean_type':'BeanItemInfo','id':375,'ts_created':1449886428151,'ts_last_modified':1449914194775,'name':'Anonymous','info':'','level':0,'coin':1.065E8,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':408,'ts_created':1461983958387,'ts_last_modified':1464583764507,'name':'Trương Hà Mi','info':'','level':26,'coin':1.0047654E8,'slot_total_bet':0.0,'facebookUID':'470621349783675','url_full_avatar':'','vip_type':2},{'bean_type':'BeanItemInfo','id':3760,'ts_created':1478161484829,'ts_last_modified':1478162234483,'name':'Thùy Dương','info':'','level':30,'coin':1.0026795E8,'slot_total_bet':0.0,'facebookUID':'615831371915705-test-002','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':1219,'ts_created':1454061913375,'ts_last_modified':1463978956852,'name':'Hà Mi 2201','info':'','level':15,'coin':9.67279E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-05/1219-0-9151caa22934ae2ceda13761aa19e7c8c54e3b669308a391c7b6cf4c7ecdaf7.png','vip_type':0},{'bean_type':'BeanItemInfo','id':1832,'ts_created':1457684147592,'ts_last_modified':1457684163428,'name':'kiet333@gmail.com','info':'','level':7,'coin':9.6725E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2661,'ts_created':1466132812389,'ts_last_modified':1466584659678,'name':'Lotte','info':'','level':18,'coin':7.74885E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-06/2661-0-806327e34b84cc3b379f6a4ade3e2607d4af6f87b89c129388dbcdb41bec.png','vip_type':0},{'bean_type':'BeanItemInfo','id':3303,'ts_created':1473043891931,'ts_last_modified':1473733233414,'name':'Dd','info':'','level':15,'coin':7.40948E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-09/3303-0-8f28e37b5150689ce02f8df8f9f64c36b15794192b208c8e8fb619b561235eb5.png','vip_type':0},{'bean_type':'BeanItemInfo','id':3774,'ts_created':1478244434995,'ts_last_modified':1497241609971,'name':'aaa','info':'','level':42,'coin':7.027177E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-06/3774-0-42eeb2c6f8b2e256caebe89c7c226186bbfe372b806648ac59dfdbdf445ee6.png','vip_type':3},{'bean_type':'BeanItemInfo','id':2039,'ts_created':1459483644478,'ts_last_modified':1464685742429,'name':'Trương Hà Mi gmail','info':'','level':33,'coin':5.7929399E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-05/2039-0-9d8995fc6ff0a1242439dd7463292b594f2d412fdf444e27d7d5ddd9170c0.jpeg','vip_type':0},{'bean_type':'BeanItemInfo','id':39,'ts_created':1436170757974,'ts_last_modified':1469170759644,'name':'Thinh Tran','info':'','level':30,'coin':5.06782E7,'slot_total_bet':0.0,'facebookUID':'661059414038658','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':76,'ts_created':1438050641539,'ts_last_modified':1464841534748,'name':'Yang Chiang','info':'','level':100,'coin':4.34694268E7,'slot_total_bet':0.0,'facebookUID':'105481506468071','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2337,'ts_created':1463047170184,'ts_last_modified':1464833326343,'name':'           ','info':'','level':52,'coin':3.96751E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-05/2337-0-52f33ceb93167fb1db5b6a4d602f7b752fb74c286593ea1067818707cfe64.png','vip_type':0},{'bean_type':'BeanItemInfo','id':1768,'ts_created':1457004615385,'ts_last_modified':1461921972254,'name':'Mi Xù','info':'','level':33,'coin':3.83661E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-04/1768-0-30185f80ddf7e36a9298a65fefa319678dd2f4807b5ab563271dfadfb28aa5b.jpeg','vip_type':0},{'bean_type':'BeanItemInfo','id':2491,'ts_created':1464419965528,'ts_last_modified':1464419965528,'name':'qqq@qq.com','info':'','level':19,'coin':3.67927E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':679,'ts_created':1452061851184,'ts_last_modified':1452062507093,'name':'leon','info':'','level':5,'coin':3.5772E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':1531,'ts_created':1454653015553,'ts_last_modified':1464832276973,'name':'Xu Mi','info':'','level':35,'coin':3.281551249E7,'slot_total_bet':0.0,'facebookUID':'101434626904889','url_full_avatar':'','vip_type':1},{'bean_type':'BeanItemInfo','id':2687,'ts_created':1466674311511,'ts_last_modified':1473325220258,'name':'vitamin','info':'','level':14,'coin':3.231023E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-09/2687-0-ca3be7b75ec87e1cef3a6a59e1e146a8ab7e437176946a8c22daafb21e638.png','vip_type':0},{'bean_type':'BeanItemInfo','id':55,'ts_created':1437734175940,'ts_last_modified':1443757050654,'name':'CM Leon','info':'','level':345,'coin':2.7020985E7,'slot_total_bet':0.0,'facebookUID':'129616270710227','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':3920,'ts_created':1480326532108,'ts_last_modified':1488850014192,'name':'ezNormalBonus@gm.com','info':'','level':25,'coin':2.29725E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-12/3920-0-8ec95f4befb0735ea5be2c67f4f6388314fdb303dc2c6fd42ec2db18c539fa.png','vip_type':0},{'bean_type':'BeanItemInfo','id':776,'ts_created':1452326956415,'ts_last_modified':1452495344675,'name':'ricky','info':'','level':4,'coin':2.27967E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':906,'ts_created':1452927416654,'ts_last_modified':1452939869916,'name':'14520030@gm.uit.edu.vn','info':'','level':6,'coin':2.06948E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4238,'ts_created':1481949212000,'ts_last_modified':1492418109086,'name':'cxcxc','info':'','level':37,'coin':2.0364154E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-04/4238-0-1822b93bb4f6d1236f4c5bbf1965ed26ca1abdab07fa2cb37c597b5cdb69ad.png','vip_type':0},{'bean_type':'BeanItemInfo','id':3244,'ts_created':1472530920283,'ts_last_modified':1473671530697,'name':'Meomeo','info':'','level':28,'coin':1.73688E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-09/3244-0-2ac795774f6ee86554c5ce6725fe7fa5f14ec2b9c31e547be165c8a93b60a14d.png','vip_type':0},{'bean_type':'BeanItemInfo','id':54,'ts_created':1437731852623,'ts_last_modified':1439519094092,'name':'Wai Tan','info':'','level':19,'coin':1.4844475E7,'slot_total_bet':0.0,'facebookUID':'1429295800734106','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':28,'ts_created':1435129046303,'ts_last_modified':1486123487556,'name':'Chris Loo','info':'','level':40,'coin':1.337534391E7,'slot_total_bet':0.0,'facebookUID':'10154056130467575','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2766,'ts_created':1467858798355,'ts_last_modified':1473648650920,'name':'Duongkute','info':'','level':34,'coin':1.19423E7,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-09/2766-0-c5b2aa7e6729a7f65b1df592d22357c999bc99e21cd78eb93da2cc5f9.png','vip_type':0},{'bean_type':'BeanItemInfo','id':18,'ts_created':1434592924904,'ts_last_modified':1437723645244,'name':'Ychong Tan','info':'','level':660,'coin':9780000.14,'slot_total_bet':0.0,'facebookUID':'384728978387895','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4254,'ts_created':1482231968438,'ts_last_modified':1487581592064,'name':'buoi@gmail.com','info':'','level':10,'coin':9290000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-01/4254-0-8572575177267ee294d589128398dda2c891c0af76584d57b8fc93bd284cc46.png','vip_type':0},{'bean_type':'BeanItemInfo','id':10,'ts_created':1434524835116,'ts_last_modified':1494228189444,'name':'Nguyễn Đạt','info':'','level':1,'coin':8977901.48,'slot_total_bet':0.0,'facebookUID':'597067537062271','url_full_avatar':'','vip_type':3},{'bean_type':'BeanItemInfo','id':40,'ts_created':1461571335672,'ts_last_modified':1464604956211,'name':'Tranthikimoanh Tranthikimoanh','info':'','level':9,'coin':7389725.0,'slot_total_bet':0.0,'facebookUID':'100543560294537','url_full_avatar':'','vip_type':5},{'bean_type':'BeanItemInfo','id':4681,'ts_created':1486178799433,'ts_last_modified':1486178940757,'name':'Ggg','info':'','level':0,'coin':6940000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-02/4681-0-5c3a7b2b4532b53c5b0bba589ad9f4358f907626ee3ea6a6554c1663a65e36.png','vip_type':0},{'bean_type':'BeanItemInfo','id':4682,'ts_created':1486181941733,'ts_last_modified':1486181951903,'name':'Luckywheel@gmail.com','info':'','level':0,'coin':6540000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-02/4682-0-a59ac5cb98fda58ba86a692a885ccb14a0426a639e46936c23d1a568614a796.png','vip_type':0},{'bean_type':'BeanItemInfo','id':38,'ts_created':1448010346000,'ts_last_modified':1464577642714,'name':'Trần Kim Oanh','info':'','level':14,'coin':6418363.58,'slot_total_bet':0.0,'facebookUID':'497310980426418','url_full_avatar':'','vip_type':5},{'bean_type':'BeanItemInfo','id':651,'ts_created':1451968872207,'ts_last_modified':1452966743684,'name':'kiet19@gmail.com','info':'','level':1,'coin':6347200.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':74,'ts_created':1437999745485,'ts_last_modified':1481789450220,'name':'Cherie Vsgl','info':'','level':106,'coin':6133748.8,'slot_total_bet':0.0,'facebookUID':'1469519680031725','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':1791,'ts_created':1457146904808,'ts_last_modified':1463454046987,'name':'Yến Nhi','info':'','level':6,'coin':5952950.0,'slot_total_bet':0.0,'facebookUID':'200656020298741','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':77,'ts_created':1438051623375,'ts_last_modified':1438051842979,'name':'Ian Ho','info':'','level':15,'coin':5644417.0,'slot_total_bet':0.0,'facebookUID':'10155881629490331','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':650,'ts_created':1451968577093,'ts_last_modified':1451968590835,'name':'kiet18@gmail.com','info':'','level':0,'coin':5250000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4310,'ts_created':1482572108033,'ts_last_modified':1482718795804,'name':'1200fixpaid2@g.com','info':'','level':30,'coin':5040000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4391,'ts_created':1482894612851,'ts_last_modified':1482907355117,'name':'maxfixpaid4@g.com','info':'','level':29,'coin':4990000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2668,'ts_created':1466161254240,'ts_last_modified':1466476404279,'name':'test2','info':'','level':6,'coin':4825000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-06/2668-0-ddda94edf0978ac2131886cb381108082cd2e3ad336b38a203192256b7d3.png','vip_type':0},{'bean_type':'BeanItemInfo','id':1201,'ts_created':1454049276299,'ts_last_modified':1464598412024,'name':'hi','info':'','level':26,'coin':4662654.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-05/1201-0-77581c2c47275078452adff64ea7a93dfbb2aaa4a3efff6bf36f34f2ea0e3a0.png','vip_type':0},{'bean_type':'BeanItemInfo','id':4274,'ts_created':1482382837681,'ts_last_modified':1482392017051,'name':'maxfixpaid1@g.com','info':'','level':29,'coin':4590000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4311,'ts_created':1482717936810,'ts_last_modified':1482735127091,'name':'maxfixpaid2@g.com','info':'','level':30,'coin':4390000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4267,'ts_created':1482307027053,'ts_last_modified':1482542769242,'name':'625softstr5@g.com','info':'','level':29,'coin':4340000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4376,'ts_created':1482803798055,'ts_last_modified':1482822030177,'name':'625fixpaid2@g.com','info':'','level':32,'coin':4240000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':3926,'ts_created':1480411702346,'ts_last_modified':1480491536223,'name':'1200newfix1@g.com','info':'','level':29,'coin':4235000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4246,'ts_created':1482201906048,'ts_last_modified':1482369992228,'name':'maxsoftstr5@g.com','info':'','level':29,'coin':4090000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4292,'ts_created':1482465877840,'ts_last_modified':1482477656174,'name':'maxsoftpaid1@g.com','info':'','level':29,'coin':4090000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4410,'ts_created':1482995499447,'ts_last_modified':1482995509435,'name':'240fixnormal2@g.com','info':'','level':24,'coin':4060000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2865,'ts_created':1468808588780,'ts_last_modified':1482746553626,'name':'tocngan@gmail.com','info':'','level':8,'coin':4040200.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-07/2865-0-106dc991196dc6fb09e88cd47623215b3baa9806030e814f63f176514e557c.png','vip_type':0},{'bean_type':'BeanItemInfo','id':2521,'ts_created':1464770745414,'ts_last_modified':1496993788534,'name':'Đạt','info':'','level':29,'coin':3938285.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-06/2521-0-175ec63ead3b79f1b794db03894943ade1a76454aba8ca2e9f287557a75ee1.png','vip_type':2},{'bean_type':'BeanItemInfo','id':4247,'ts_created':1482207740886,'ts_last_modified':1482283123444,'name':'75softstr2@g.com','info':'','level':24,'coin':3910000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4295,'ts_created':1482469479934,'ts_last_modified':1482477770771,'name':'1200softpaid1@g.com','info':'','level':29,'coin':3840000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4372,'ts_created':1482745192735,'ts_last_modified':1482892123705,'name':'625softpaid2@g.com','info':'','level':29,'coin':3740000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4400,'ts_created':1482918697143,'ts_last_modified':1482974454307,'name':'maxfixpaid6@g.com','info':'','level':30,'coin':3690000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4249,'ts_created':1482218288903,'ts_last_modified':1482224150612,'name':'mediumsoftat2@g.com','info':'','level':24,'coin':3660000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4407,'ts_created':1482981344561,'ts_last_modified':1482981350470,'name':'mediumsoftnormal1@g.com','info':'','level':24,'coin':3510000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4396,'ts_created':1482899188045,'ts_last_modified':1482914740575,'name':'maxsoftnormal1@g.com','info':'','level':23,'coin':3410000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4258,'ts_created':1482285846700,'ts_last_modified':1482296594108,'name':'375softstr2@g.com','info':'','level':24,'coin':3410000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4385,'ts_created':1482829655277,'ts_last_modified':1482893132311,'name':'625fixpaid3@g.com','info':'','level':29,'coin':3390000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4402,'ts_created':1482974740169,'ts_last_modified':1483061867556,'name':'medsoftnormal1@g.com','info':'','level':24,'coin':3360000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4243,'ts_created':1482120337720,'ts_last_modified':1482197767299,'name':'medsoftstr2@g.com','info':'','level':24,'coin':3360000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4397,'ts_created':1482903627466,'ts_last_modified':1482976553203,'name':'1200softpaid','info':'','level':29,'coin':3240000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4237,'ts_created':1481946079690,'ts_last_modified':1481946090453,'name':'maxdbfixat1@g.com','info':'','level':30,'coin':3240000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4775,'ts_created':1488602367404,'ts_last_modified':1488612895057,'name':'Biggybank@gmail.com','info':'','level':0,'coin':3195000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2017-03/4775-0-4f956880252f641a14184451e0cc5036bf80bc9c76c4106849b91cb62ceed154.png','vip_type':0},{'bean_type':'BeanItemInfo','id':4403,'ts_created':1482976547192,'ts_last_modified':1483062890091,'name':'minnormal2@g.com','info':'','level':24,'coin':3160000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2066,'ts_created':1459588205817,'ts_last_modified':1483697042476,'name':'xyzz','info':'','level':422,'coin':3156700.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-09/2066-0-33ddfdcbe73ac040f22cc71c62fcd2d4f56b11e38fc716c6332e26d24e86cdac.png','vip_type':0},{'bean_type':'BeanItemInfo','id':377,'ts_created':1449890661573,'ts_last_modified':1452967857603,'name':'kiet16@gmail.com','info':'','level':14,'coin':3120800.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4242,'ts_created':1482117234411,'ts_last_modified':1482216584586,'name':'minntat1@g.com','info':'','level':24,'coin':3010000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4269,'ts_created':1482374073872,'ts_last_modified':1482374084572,'name':'mediumfixpaid1@g.com','info':'','level':29,'coin':2890000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':2752,'ts_created':1467085221887,'ts_last_modified':1477467602351,'name':'Gà Con','info':'','level':2,'coin':2827600.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'https://scmw-web.spiralworks-cloud.com/ppwebstatic/test/profile-pix/2016-07/2752-0-7c226b676ff916684aaf3e341ae2d3d6b15f9c3e812ab1b9df73cc8df31f17.png','vip_type':0},{'bean_type':'BeanItemInfo','id':4304,'ts_created':1482543081964,'ts_last_modified':1482715562245,'name':'maxsoftpaid3@g.com','info':'','level':29,'coin':2790000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4346,'ts_created':1482740023343,'ts_last_modified':1482892063555,'name':'625softpaid1@g.com','info':'','level':29,'coin':2790000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4408,'ts_created':1482984335693,'ts_last_modified':1482984352926,'name':'240fixnormal1@g.com','info':'','level':24,'coin':2760000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4393,'ts_created':1482897617983,'ts_last_modified':1482907326272,'name':'maxfixpaid5@g.com','info':'','level':29,'coin':2690000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4390,'ts_created':1482893295283,'ts_last_modified':1482893302883,'name':'625fixpaid5@g.com','info':'','level':29,'coin':2590000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0},{'bean_type':'BeanItemInfo','id':4239,'ts_created':1481956994241,'ts_last_modified':1481957010572,'name':'75dbfixat2@g.com','info':'','level':24,'coin':2510000.0,'slot_total_bet':0.0,'facebookUID':'','url_full_avatar':'','vip_type':0}]},'extra_info':null}";
    }
//    else if (Helper4String::isStringContain(url, "login")) {
//        result = "";
//    }else if (Helper4String::isStringContain(url, "login")) {
//        result = "";
//    }else if (Helper4String::isStringContain(url, "login")) {
//        result = "";
    else if (Helper4String::isStringContain(url, "/user/dailyBonusStreak/collect")) {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500479892891,'bean':{'bean_type':'BeanDailyBonusStreak','id':0,'ts_created':1500479893123,'ts_last_modified':1500479893123,'name':'','info':'','daily_streak':1,'can_collect':false,'coin_reward':10000.0,'magic_item_reward_quantity':0,'magic_item_reward_type':0},'extra_info':null}";
    }
    else {
        result = "{'bean_type':'BeanResultWithBeanBasic','core_result_code':0,'total_page':0,'reload':false,'ts_reload':1500479892891,'bean':{'bean_type':'BeanDailyBonusStreak','id':0,'ts_created':1500479893123,'ts_last_modified':1500479893123,'name':'','info':'','daily_streak':1,'can_collect':false,'coin_reward':10000.0,'magic_item_reward_quantity':0,'magic_item_reward_type':0},'extra_info':null}";
    }


	std::replace(result.begin(), result.end(), '\'', '"'); // replace all 'x' to 'y'
	Document responseAsDocument;
	responseAsDocument.Parse(result.c_str());
	rapidjson::Value beanResponseAsDocument;
	beanResponseAsDocument = responseAsDocument[JSONFieldConstant::BEAN.c_str()];
//	beanResponseAsDocument[JSONFieldConstant::ID.c_str()];

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

               
void TestManager::loginGuessAcount(std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callback){
    TestManager::getInstance()->getFakeRespone("loginguest", [callback](rapidjson::Value &responseAsDocument) {
        
        callback(0,responseAsDocument,"");
        
    });
    
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

    return;
	PopupManager::getInstance()->initAllPopupLobbyScene();
	cocos2d::ui::Button* testButton = BasePopup::createGreenButton(false, "Test", 50);;
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
		prepareTestLuckyWheel(parent);
//		testLevelUpPopup(parent);
		//prepareTestAchievementPopup(parent);
		//testUnlockPopup(parent);
//		testUnlockFeature(parent);
	
	});
	parent->addChild(testButton);
}
