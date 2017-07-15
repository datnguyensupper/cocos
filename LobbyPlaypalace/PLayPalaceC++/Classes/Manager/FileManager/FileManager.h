#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: FileManager.h, FileManager.cpp
*/

#include "cocos2d.h"

class FileManager
{
private:
	static FileManager* s_instance;

	cocos2d::Scheduler* _scheduler;
	std::mutex _schedulerMutex;
public:
	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static FileManager* getInstance();

	/// <summary>
	/// get directory of all game slot resource
	/// </summary>
	/// <returns></returns>
	std::string getDirectoryGame();
	/// <summary>
	/// get directory of game slot resource
	/// </summary>
	/// <param name="gameName"></param>
	/// <returns></returns>
	std::string getGameSlotDirectoryGame(std::string gameName);
	/// <summary>
	/// get directory of game slot resource
	/// </summary>
	/// <param name="gameID"></param>
	/// <returns></returns>
	std::string getGameSlotDirectoryGame(int gameID);
	/// <summary>
	/// get game name from id
	/// </summary>
	/// <param name="gameID"></param>
	/// <returns></returns>
	std::string getGameNameFromID(int gameID);
protected:
	//! Reference to the global file utils
	cocos2d::FileUtils *_fileUtils;

	FileManager();
	/// <summary>
	/// remove file
	/// </summary>
	/// <param name="filePath"></param>
	void removeFile(std::string filePath);
	/// <summary>
	/// check file is exist
	/// </summary>
	/// <param name="filePath"></param>
	/// <returns></returns>
	bool isFileExist(std::string filePath);
	/// <summary>
	/// function to call uncompress thead alone
	/// </summary>
	/// <param name="zip"></param>
	/// <param name="callback"></param>
	void uncompressInBGThread(const std::string &zip, std::function<void(bool isSuccess)> callback);
	/// <summary>
	/// uncompress zip file in background thread
	/// </summary>
	/// <param name="zip"></param>
	/// <param name="callback"></param>
	void uncompressThreadAlone(const std::string &zip, std::function<void(bool isSuccess)> callback);
	/// <summary>
	/// uncompress zip file
	/// </summary>
	/// <param name="zip"></param>
	/// <returns></returns>
	bool uncompress(const std::string &zip);
	/// <summary>
	/// get base name of file from path
	/// </summary>
	/// <param name="path"></param>
	/// <returns></returns>
	std::string basename(const std::string& path) const;
	/// <summary>
	/// read txt file from path
	/// </summary>
	/// <param name="pFileName"></param>
	/// <returns></returns>
	std::string readFileFromPath(std::string pFileName);
};