#include "SlotsGameDownloadFileManager.h"
#include "Constant/Defination.h"
#include "Configs.h"
#include "Helper/Helper4String.h"
#include "Manager/DeviceManager.h"

#define CC_CALLBACK_4(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, ##__VA_ARGS__)

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

#pragma region init singleton
SlotsGameDownloadFileManager* SlotsGameDownloadFileManager::s_instance = nullptr;

SlotsGameDownloadFileManager* SlotsGameDownloadFileManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new SlotsGameDownloadFileManager();
	}
	return s_instance;
}
#pragma endregion

SlotsGameDownloadFileManager::SlotsGameDownloadFileManager()
{
	std::vector<std::string> arrayGameSlot =
	{ GAME_SLOT_ID_BOXING,GAME_SLOT_ID_DEEPBLUE,GAME_SLOT_ID_GOLDENEGG,GAME_SLOT_ID_NEZHA,GAME_SLOT_ID_PHARAOH,GAME_SLOT_ID_ROMANEMPIRE};

	for (int i = 0; i < arrayGameSlot.size(); i++) {
		UserDefault::getInstance()->setBoolForKey((STORING_KEY_SHOULD_DONWLOAD_GAME_SLOT + arrayGameSlot[i]).c_str(), false);
	//	bool shouldDownloadSlotGame = UserDefault::getInstance()->getBoolForKey((STORING_KEY_SHOULD_DONWLOAD_GAME_SLOT + arrayGameSlot[i]).c_str(), false);
	//	if (shouldDownloadSlotGame) {
	//		if (!isGameInCache(arrayGameSlot[i])) {
	//			SlotGameDonwloadInfo *slotGameDownloadInfo = new SlotGameDonwloadInfo();;
	//			slotGameDownloadInfo->gameId = arrayGameSlot[i];
	//			slotGameDownloadInfo->gameShouldDownloadInMainThread = true;
	//			queueSlotGameForDownloading.push_back(slotGameDownloadInfo);				
	//		}
	//		else {
	//			/*UserDefault::getInstance()->setBoolForKey((STORING_KEY_SHOULD_DONWLOAD_GAME_SLOT + arrayGameSlot[i]).c_str(), false);
	//			UserDefault::getInstance()->flush();*/
	//		}
	//	}
	}
	UserDefault::getInstance()->flush();
}

std::string SlotsGameDownloadFileManager::getSlotGameDownloadURL(std::string gameId, std::string version) {
	std::string suffixes = "";
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || IS_DEBUG)
	if (DeviceManager::getInstance()->isLowRamDevice()) suffixes = "80Percent";
#endif    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 && IS_DEBUG)
	std::string url = Configs::downloadGameSlotPathTest + version + "/" + gameId + suffixes + ".zip";
#else
	std::string url = Configs::downloadGameSlotPath + version + "/" + gameId + suffixes + ".zip";
#endif
    
	return url;
}

std::string SlotsGameDownloadFileManager::getLocalPathToSaveDownloadedSlotGame(std::string url) {
	std::string fileName = Helper4String::getFileNameFromPath(url);
	std::string localPath = getGameSlotDirectoryGame("");
	std::string filePath = localPath + fileName;
	return filePath;
}

bool SlotsGameDownloadFileManager::isGameInCache(std::string gameId) {
	if (gameId == GAME_SLOT_ID_NEZHA) return true;

	std::string versionGameFilePath = getGameSlotDirectoryGame(gameId);
	versionGameFilePath.append("version.txt");
	return isFileExist(versionGameFilePath);
}

bool SlotsGameDownloadFileManager::isGameDownloading(std::string gameId) {
	if (gameId == GAME_SLOT_ID_NEZHA) return false;

	bool shouldDownloadSlotGame = UserDefault::getInstance()->getBoolForKey ((STORING_KEY_SHOULD_DONWLOAD_GAME_SLOT +gameId).c_str(), false);
	return shouldDownloadSlotGame;
}

void SlotsGameDownloadFileManager::finishDownload1GameSlotCallBack(SlotGameDonwloadInfo *slotGameDownloadInfo, bool isFinish, bool isFail) {

		//reset current object download info
	if ((*slotGameDownloadInfo).callback != nullptr) {
		(*slotGameDownloadInfo).callback(1, isFinish, isFail);

	}
	if (!isFail) {
		// no need download game anymore
		UserDefault::getInstance()->setBoolForKey((STORING_KEY_SHOULD_DONWLOAD_GAME_SLOT + (*slotGameDownloadInfo).gameId).c_str(), false);
		UserDefault::getInstance()->flush();
	}
	removeGameSlotWithGameIdInDownloadingQueue((*slotGameDownloadInfo).gameId);
	(*slotGameDownloadInfo).gameId = "";
	(*slotGameDownloadInfo).gameVersion = "";
	(*slotGameDownloadInfo).callback = nullptr;
	if ((*slotGameDownloadInfo).downloader != nullptr) {
		CC_SAFE_DELETE((*slotGameDownloadInfo).downloader);
	}
		
	(*slotGameDownloadInfo).downloader = nullptr;
	(*slotGameDownloadInfo).gameShouldDownloadInMainThread = false;
	if (slotGameDownloadInfo == currentGameSlotDownloadInfo) {
		currentGameSlotDownloadInfo = nullptr;
	}
	else {
		currentGameSlotDownloadInBGThreadBK = nullptr;
	}
	slotGameDownloadInfo->release();
}
	
void SlotsGameDownloadFileManager::callbackEventForDownloadingFile(std::string gameID, float progress, bool isFinish, bool isFail) {
	
	SlotGameDonwloadInfo *checkGameSlotInfo = currentGameSlotDownloadInfo;
	if (currentGameSlotDownloadInBGThreadBK != nullptr && (*currentGameSlotDownloadInBGThreadBK).gameId.compare(gameID) == 0) {
		checkGameSlotInfo = currentGameSlotDownloadInBGThreadBK;
	}


	if (isFinish) {
		finishDownload1GameSlotCallBack(checkGameSlotInfo, isFinish, isFail);
		// check to download next game in queue
		downloadNextSlotGameInQueue();
	}
	else {
		if ((*checkGameSlotInfo).callback != nullptr) {
			(*checkGameSlotInfo).callback(progress, isFinish, isFail);
		}
	}
}

void SlotsGameDownloadFileManager::getNextGameSlotDonwloadInfoInDownloadingQueue(std::function<void(bool success, SlotGameDonwloadInfo &slotGameInfo)> callback) {
	// get game slot info run in main ui
	for (int i = 0; i < queueSlotGameForDownloading.size(); i++) {
		if ((*queueSlotGameForDownloading[i]).gameShouldDownloadInMainThread) {
			if (callback != nullptr) {
				callback(true, *queueSlotGameForDownloading[i]);
			}
			return;
		}
	}

	if (queueSlotGameForDownloading.size() > 0) {
		if (callback != nullptr) {
			callback(true, *queueSlotGameForDownloading[0]);
		}
		return;
	}

	SlotGameDonwloadInfo nullResult;
	if (callback != nullptr) {
		callback(false, nullResult);
	}

}

void SlotsGameDownloadFileManager::getGameSlotWithGameIdInDownloadingQueue(std::string gameID, std::function<void(bool success, SlotGameDonwloadInfo *slotGameInfo)> callback) {
	// get game slot info with game id
	for (int i = 0; i < queueSlotGameForDownloading.size(); i++) {
		if ((*queueSlotGameForDownloading[i]).gameId.compare(gameID) == 0){
			if (callback != nullptr) {
				callback(true, queueSlotGameForDownloading[i]);
			}
			return;
		}
	}
	if (callback != nullptr) {
		callback(false, nullptr);
	}

}

bool SlotsGameDownloadFileManager::fileIsExpireByVersion(std::string gameID, std::string newestVersion) {
	std::string url = getSlotGameDownloadURL(gameID,newestVersion);
	std::string filePath = getLocalPathToSaveDownloadedSlotGame(url);
	std::string gameSlotPath = DownloadFileManager::getInstance()->getGameSlotDirectoryGame(gameID);
	gameSlotPath.append("version.txt");
	
	string fileContent = readFileFromPath(gameSlotPath);
	if (fileContent.compare(newestVersion) < 0) {
		return true;
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || IS_DEBUG)
	std::string is80PercentPath = DownloadFileManager::getInstance()->getGameSlotDirectoryGame(gameID) + "is80Percent.txt";
	bool is80PercentFileExist = isFileExist(is80PercentPath);
	if ((is80PercentFileExist && !DeviceManager::getInstance()->isLowRamDevice()) ||
		(!is80PercentFileExist && DeviceManager::getInstance()->isLowRamDevice()))
		return true;
#endif

	return false;
}

void SlotsGameDownloadFileManager::removeGameSlotWithGameIdInDownloadingQueue(std::string gameID) {
	// get game slot info with game id
	vector<SlotGameDonwloadInfo*>::iterator it2;
	for (it2 = queueSlotGameForDownloading.begin(); it2 != queueSlotGameForDownloading.end();++it2)
	{
		if ((*(*it2)).gameId.compare(gameID) == 0) {
			queueSlotGameForDownloading.erase(it2);
			return;
		}
	}

}
/// <summary>
/// By Dat if game can cancel download it will cancel download
/// </summary>
/// <param name="gameID"></param>
/// <returns></returns>
void SlotsGameDownloadFileManager::removeGameSlotWithGameId(std::string gameID) {
	if (isGameInCache(gameID)) {
		std::string versionGameFilePath = getGameSlotDirectoryGame(gameID);
		_fileUtils->removeDirectory(versionGameFilePath);
	}
}

bool SlotsGameDownloadFileManager::cancelGameSlotWithGameIdInDownloadingQueue(std::string gameID) {
	if (isGameCanCancelDownload(gameID)) {
		removeGameSlotWithGameIdInDownloadingQueue(gameID);
		return true;
	}
	return false;
}

bool SlotsGameDownloadFileManager::isGameCanCancelDownload(std::string gameID) {
	if (
		currentGameSlotDownloadInfo != nullptr &&
		currentGameSlotDownloadInfo->gameId.compare(gameID) == 0 &&
		currentGameSlotDownloadInfo->gameShouldDownloadInMainThread) {
		return false;
	}
	return true;
}

void SlotsGameDownloadFileManager::downloadNextSlotGameInQueue() {

	bool shouldDownloadNextSlotGame = false;

	if (currentGameSlotDownloadInfo == nullptr) {
		// current dont have any game download
		getNextGameSlotDonwloadInfoInDownloadingQueue([=](bool success, SlotGameDonwloadInfo &slotGameInfo) {
			if (success) {

				// still have game need to download in queue, so we download it
				if (slotGameInfo.gameShouldDownloadInMainThread) {
					// create new thread to download game
					currentGameSlotDownloadInfo = &slotGameInfo;
					(*currentGameSlotDownloadInfo).downloader = nullptr;
				}
				else {
					if (currentGameSlotDownloadInBGThreadBK == nullptr) {
						// no download game slot BK in background thread, so we download it

						currentGameSlotDownloadInfo = &slotGameInfo;
						(*currentGameSlotDownloadInfo).downloader = nullptr;

					}
				}
			}
		});
	}
	else if (currentGameSlotDownloadInfo != nullptr && !(*currentGameSlotDownloadInfo).gameShouldDownloadInMainThread) {
		// current have 1 download game in background thread, so we check have any new game need 2 download in UI thread
		getNextGameSlotDonwloadInfoInDownloadingQueue([=](bool success, SlotGameDonwloadInfo &slotGameInfo) {
			if (success && slotGameInfo.gameShouldDownloadInMainThread) {
				// still have game need to download in UI queue, so we stop current download background and download it

				// keep reference downloading game slot in bg thread
				currentGameSlotDownloadInBGThreadBK = currentGameSlotDownloadInfo;

				currentGameSlotDownloadInfo = &slotGameInfo;
				(*currentGameSlotDownloadInfo).downloader = nullptr;
				

			}
		});
	}

	if (currentGameSlotDownloadInfo != nullptr) {
		if ((*currentGameSlotDownloadInfo).downloader == nullptr) {
			if (!isGameInCache((*currentGameSlotDownloadInfo).gameId)) {

				std::string url = getSlotGameDownloadURL((*currentGameSlotDownloadInfo).gameId, (*currentGameSlotDownloadInfo).gameVersion);
				(*currentGameSlotDownloadInfo).downloader = downloadFileWithURLAndSave2Device(
					(*currentGameSlotDownloadInfo).gameId, true, nullptr, url, getLocalPathToSaveDownloadedSlotGame(url), true,
					CC_CALLBACK_4(SlotsGameDownloadFileManager::callbackEventForDownloadingFile, this)
				);
			}
			else {
				finishDownload1GameSlotCallBack(currentGameSlotDownloadInfo, true, false);
				downloadNextSlotGameInQueue();
			}
		}
	}
}


void SlotsGameDownloadFileManager::forceDownloadInMainUI(
	std::string gameID,
	std::string gameVersion,
	std::function<void(float progress, bool isFinish, bool isFail)> callback) {
	std::string url = getSlotGameDownloadURL(gameID,gameVersion);
	downloadFileWithURLAndSave2Device(
		(*currentGameSlotDownloadInfo).gameId, true, nullptr, url, getLocalPathToSaveDownloadedSlotGame(url), true,
		[=](std::string fileID, float progress, bool isFinish, bool isFail) {
		if (callback != nullptr) {
			callback(progress, isFinish, isFail);
		}
	}
	);

}

void SlotsGameDownloadFileManager::downloadSlotGameInMainUI(
	std::string gameID, std::string gameVersion,
	std::function<void(float progress, bool isFinish, bool isFail)> callback) {


	UserDefault::getInstance()->setBoolForKey((STORING_KEY_SHOULD_DONWLOAD_GAME_SLOT + gameID).c_str(), true);
	cocos2d::UserDefault::getInstance()->flush();

	// current downloading game is gameID
	if (currentGameSlotDownloadInfo != nullptr && (*currentGameSlotDownloadInfo).gameId.compare(gameID) == 0) {
		// change current download game from background thread to main thread and show progress in UI
		if ((*currentGameSlotDownloadInfo).gameShouldDownloadInMainThread == false) {
			(*currentGameSlotDownloadInfo).gameShouldDownloadInMainThread = true;
			if ((*currentGameSlotDownloadInfo).callback != nullptr) {
				(*currentGameSlotDownloadInfo).callback(1, true, false);
			}
			(*currentGameSlotDownloadInfo).callback = callback;

			// update callback for download slot game
			std::string url = getSlotGameDownloadURL(gameID,gameVersion);
			downloadFileWithURLAndSave2Device(
				gameID,false, (*currentGameSlotDownloadInfo).downloader, 
				url, getLocalPathToSaveDownloadedSlotGame(url), true,
				CC_CALLBACK_4(SlotsGameDownloadFileManager::callbackEventForDownloadingFile, this)
			);
		}
		else {// game is download and update UI so we do nothing
			(*currentGameSlotDownloadInfo).callback = callback;
		}
	}
	else {
		//check game is in queue
		getGameSlotWithGameIdInDownloadingQueue(gameID,[=](bool success, SlotGameDonwloadInfo *slotGameInfo) {
			if (!success) {
				slotGameInfo = new SlotGameDonwloadInfo();
				(*slotGameInfo).gameId = gameID;
				(*slotGameInfo).gameVersion = gameVersion;
				queueSlotGameForDownloading.push_back(slotGameInfo);
			}
			else if(!(*slotGameInfo).gameShouldDownloadInMainThread && (*slotGameInfo).callback != nullptr) {
				(*slotGameInfo).callback(1, true, false);
			}

			if (callback != nullptr) {
				callback(0, false, false);
			}
			(*slotGameInfo).gameShouldDownloadInMainThread = true;
			(*slotGameInfo).callback = callback;
			//callback(0,false,false);
			downloadNextSlotGameInQueue();
		});
	}

}

void SlotsGameDownloadFileManager::downloadSlotGameInBackgroundUI(
	std::string gameID, std::string gameVersion,
	std::function<void(float progress, bool isFinish, bool isFail)> callback) {

	// current downloading game is gameID
	if (currentGameSlotDownloadInfo != nullptr && (*currentGameSlotDownloadInfo).gameId.compare(gameID) == 0) {
		if ((*currentGameSlotDownloadInfo).gameShouldDownloadInMainThread && callback != nullptr) {
			callback(1, true, false);
		}
		// if current game slot doesnt download anything, we continue download it
		if ((*currentGameSlotDownloadInfo).downloader == nullptr) {
			downloadNextSlotGameInQueue();
		}
		
	}
	else {
		//check game is in queue
		getGameSlotWithGameIdInDownloadingQueue(gameID, [=](bool success, SlotGameDonwloadInfo *slotGameInfo) {
			if (!success) {
				slotGameInfo = new SlotGameDonwloadInfo();
				(*slotGameInfo).gameId = gameID;
				(*slotGameInfo).gameVersion = gameVersion;
				queueSlotGameForDownloading.push_back(slotGameInfo);
				(*slotGameInfo).gameShouldDownloadInMainThread = false;
			}

			if ((*slotGameInfo).gameShouldDownloadInMainThread) {
				if (callback != nullptr) {
					callback(1, true, false);
				}
			}
			else {
				(*slotGameInfo).callback = callback;
				//callback(0, false, false);
			}
			downloadNextSlotGameInQueue();
		});
	}

	
}
