#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: DownloadFileManager.h, DownloadFileManager.cpp
*/

#include "cocos2d.h"
#include "FileManager.h"
#include "extensions/cocos-ext.h"

class DownloadFileManager : public FileManager
{
protected:
	DownloadFileManager();
private:
	static DownloadFileManager* s_instance;
public:

	/*cocos2d::extension::AssetsManagerEx* _am;
	cocos2d::extension::EventListenerAssetsManagerEx* _amListener;
	cocos2d::network::Downloader *downloader;*/

	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static DownloadFileManager* getInstance();

	/// <summary>
	/// download file with url
	/// </summary>
	/// <param name="fileUrl">download url</param>
	/// <param name="callback">return image after download</param>
	/// <param name="shouldReleaseImageAfterDownload">should remove image after download</param>
	void downloadFileWithURL(std::string fileUrl, std::function<void(cocos2d::Image*)> callback, bool shouldReleaseImageAfterDownload);

	/// <summary>
	/// download file, decompress file and save file to local
	/// </summary>
	/// <param name="isStartDownload">should start it download</param>
	/// <param name="downloader">downloader to download file via http request</param>
	/// <param name="url">url of file</param>
	/// <param name="filePath">local path to store file</param>
	/// <param name="shouldDecompress">should decompress file</param>
	/// <param name="callback">call back to update ui progress</param>
	cocos2d::network::Downloader* downloadFileWithURLAndSave2Device(
		std::string fileID,
		bool isStartDownload,
		cocos2d::network::Downloader *downloader,
		std::string url,
		std::string filePath,
		bool shouldDecompress,
		std::function<void(std::string fileID, float progress, bool isFinish, bool isFail)> callback);

	/// <summary>
	/// download game slot with asset manager
	/// </summary>
	/// <param name="prefix">prefix of file</param>
	/// <param name="callback">update progress when download</param>
	cocos2d::extension::AssetsManagerEx * downloadFileWithAssetManager(
		std::string fileID,
		bool isStartDownload,
		cocos2d::extension::AssetsManagerEx * _am,
		std::string url,
		std::string filePath,
		bool shouldDecompress,
		std::function<void(std::string fileID, float progress, bool isFinish, bool isFail)> callback);

	//void releasAssetManagerEvent();

};