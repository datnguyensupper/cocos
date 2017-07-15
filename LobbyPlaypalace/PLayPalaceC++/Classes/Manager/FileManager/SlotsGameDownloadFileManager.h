#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: SlotGameDonwloadInfo.h, SlotGameDonwloadInfo.cpp
*/

#include "cocos2d.h"
#include "DownloadFileManager.h"
#include "extensions/cocos-ext.h"

class SlotGameDonwloadInfo: public cocos2d::Ref {
public:
	std::string gameId = "";
	std::string gameVersion = "";
	bool gameShouldDownloadInMainThread = false;
	cocos2d::network::Downloader * downloader = nullptr;
	//cocos2d::extension::AssetsManagerEx * downloader = nullptr;
	std::function<void(float progress, bool isFinish, bool isFail)> callback = nullptr;
};

class SlotsGameDownloadFileManager : public DownloadFileManager
{
protected:
	SlotsGameDownloadFileManager();
private:
	static SlotsGameDownloadFileManager* s_instance;
	SlotGameDonwloadInfo *currentGameSlotDownloadInfo = nullptr;
	// we cant stop game is downloading so we accept 2 game download at same time, we cant do anything better than this
	SlotGameDonwloadInfo *currentGameSlotDownloadInBGThreadBK = nullptr;

	/// <summary>
	/// get game slot download URL
	/// </summary>
	/// <param name="gameId"></param>
	/// <param name="version"></param>
	/// <returns></returns>
	std::string getSlotGameDownloadURL(std::string gameId, std::string version);
	/// <summary>
	/// get local path to save game slot
	/// </summary>
	/// <param name="url"></param>
	/// <returns></returns>
	std::string getLocalPathToSaveDownloadedSlotGame(std::string url);
	/// <summary>
	/// get next game slot should download in queue
	/// </summary>
	/// <param name="callback"></param>
	void getNextGameSlotDonwloadInfoInDownloadingQueue(std::function<void(bool success, SlotGameDonwloadInfo &slotGameInfo)> callback);
	/// <summary>
	/// get game slot with id from queue
	/// </summary>
	void getGameSlotWithGameIdInDownloadingQueue(std::string gameID,std::function<void(bool success, SlotGameDonwloadInfo *slotGameInfo)> callback);
	/// <summary>
	/// remove game slot from queue
	/// </summary>
	/// <param name="gameID"></param>
	void removeGameSlotWithGameIdInDownloadingQueue(std::string gameID);
	/// <summary>
	/// download next slot game in queue
	/// </summary>
	void downloadNextSlotGameInQueue();
	/// <summary>
	/// call back when finish download game slot
	/// </summary>
	/// <param name="slotGameDownloadInfo"></param>
	/// <param name="isFinish"></param>
	/// <param name="isFail"></param>
	void finishDownload1GameSlotCallBack(SlotGameDonwloadInfo *slotGameDownloadInfo, bool isFinish, bool isFail);
public:
	/// <summary>
	/// check file is expire by version
	/// </summary>
	/// <param name="gameID"></param>
	/// <param name="newestVersion">newest version to comare with local version</param>
	/// <returns></returns>
	bool fileIsExpireByVersion(std::string gameID, std::string newestVersion);
	/// <summary>
	/// By Dat remove game in cache
	/// </summary>
	/// <param name="gameID"></param>
	/// <returns></returns>
	void removeGameSlotWithGameId(std::string gameID);
	/// <summary>
	/// By Dat if game can cancel download it will cancel download
	/// </summary>
	/// <param name="gameID"></param>
	/// <returns></returns>
	bool cancelGameSlotWithGameIdInDownloadingQueue(std::string gameID);
	/// <summary>
	/// By Dat check game can cancel download
	/// </summary>
	/// <param name="gameID"></param>
	/// <returns></returns>
	bool isGameCanCancelDownload(std::string gameID);
	std::vector<SlotGameDonwloadInfo*> queueSlotGameForDownloading = {};
	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static SlotsGameDownloadFileManager* getInstance();
	/// <summary>
	/// calback progress when dowloading file
	/// </summary>
	/// <param name="gameID"></param>
	/// <param name="progress"></param>
	/// <param name="isFinish"></param>
	/// <param name="isFail"></param>
	void callbackEventForDownloadingFile(std::string gameID, float progress, bool isFinish, bool isFail);
	/// <summary>
	/// check game is in cache
	/// </summary>
	/// <param name="gameId"></param>
	/// <returns></returns>
	bool isGameInCache(std::string gameId);
	/// <summary>
	/// check game is downloading check when user comback to lobby scene
	/// </summary>
	/// <param name="gameId"></param>
	/// <returns></returns>
	bool isGameDownloading(std::string gameId);
	/// <summary>
	/// download game and show progress on UI
	/// </summary>
	/// <param name="gameID"></param>
	/// <param name="gameVersion"></param>
	/// <param name="callback"></param>
	void downloadSlotGameInMainUI(
		std::string gameID,
		std::string gameVersion,
		std::function<void(float progress, bool isFinish, bool isFail)> callback);
	/// <summary>
	/// dowload game button down show progress on UI
	/// </summary>
	/// <param name="gameID"></param>
	/// <param name="gameVersion"></param>
	/// <param name="callback"></param>
	void forceDownloadInMainUI(
		std::string gameID, std::string gameVersion,
		std::function<void(float progress, bool isFinish, bool isFail)> callback);

	/// <summary>
	/// download ngam
	/// </summary>
	/// <param name="url"></param>
	/// <param name="filePath"></param>
	/// <param name="shouldDecompress"></param>
	/// <param name="callback"></param>
	void downloadSlotGameInBackgroundUI(
		std::string gameID, std::string gameVersion,
		std::function<void(float progress, bool isFinish, bool isFail)> callback);

};