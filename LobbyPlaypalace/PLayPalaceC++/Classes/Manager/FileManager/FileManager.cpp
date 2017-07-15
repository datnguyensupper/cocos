#include "FileManager.h"
#include "extensions/cocos-ext.h"
#ifdef MINIZIP_FROM_SYSTEM
#include <minizip/unzip.h>
#else // from our embedded sources
#include "unzip.h"
#endif

#include "Constant/PPEnums.h"
#include "Constant/Defination.h"

#define BUFFER_SIZE    8192
#define MAX_FILENAME   512

using namespace std;
USING_NS_CC;
#pragma region init singleton
FileManager* FileManager::s_instance = nullptr;

FileManager* FileManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new FileManager();
	}
	return s_instance;
}
#pragma endregion

FileManager::FileManager()
{
	_fileUtils = CCFileUtils::sharedFileUtils();
	_scheduler = Director::getInstance()->getScheduler();
}

std::string FileManager::getDirectoryGame() {

	std::string str = _fileUtils->getWritablePath();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

	//str.append("/");

	#endif

	return str;
}


std::string FileManager::getGameSlotDirectoryGame(std::string gameName) {
	std::string directory = getDirectoryGame();
	directory.append("slotgame/");
	if (gameName.compare("") != 0) {
		directory.append(gameName);
		directory.append("/");
    }else{
        
    }
//    CCLOG("directory :%s", directory.c_str());
    if(!_fileUtils->isDirectoryExist(directory)){
        _fileUtils->createDirectory(directory);
    }
//    bool isDirectoryExist =_fileUtils->isDirectoryExist(directory);
	return directory;
}

std::string FileManager::getGameSlotDirectoryGame(int gameID) {
	return getGameSlotDirectoryGame(getGameNameFromID(gameID));
}

std::string FileManager::getGameNameFromID(int gameID) {

	switch (gameID)
	{
	case ppEnum::GameSlotOrderId::NEZHA:
		return GAME_SLOT_ID_NEZHA;
	case ppEnum::GameSlotOrderId::GOLDEN_EGGS:
		return GAME_SLOT_ID_GOLDENEGG;
	case ppEnum::GameSlotOrderId::PHARAOH:
		return GAME_SLOT_ID_PHARAOH;
	case ppEnum::GameSlotOrderId::BOXING:
		return GAME_SLOT_ID_BOXING;
	case ppEnum::GameSlotOrderId::ROMAN_EMPIRE:
		return GAME_SLOT_ID_ROMANEMPIRE;
	case ppEnum::GameSlotOrderId::DEEP_BLUE:
		return GAME_SLOT_ID_DEEPBLUE;
	default:
		break;
	}

	return "";
}

void FileManager::removeFile(std::string filePath) {

	_fileUtils->removeFile(filePath);

}


bool FileManager::isFileExist(std::string filePath) {
	return _fileUtils->isFileExist(filePath);
}

std::string FileManager::basename(const std::string& path) const
{
	size_t found = path.find_last_of("/\\");

	if (std::string::npos != found)
	{
		return path.substr(0, found);
	}
	else
	{
		return path;
	}
}


void FileManager::uncompressInBGThread(const std::string &zip, std::function<void(bool isSuccess)> callback) {

	auto t = std::thread(&FileManager::uncompressThreadAlone, this, zip,callback);
	t.detach();
}

void FileManager::uncompressThreadAlone(const std::string &zip, std::function<void(bool isSuccess)> callback) {

	_schedulerMutex.lock();
	bool isSuccess = uncompress(zip);
	_scheduler->performFunctionInCocosThread([=]() {
		callback(isSuccess);
	});
	_schedulerMutex.unlock();
}

bool FileManager::uncompress(const std::string &zip)
{
	// Find root path for zip file
	size_t pos = zip.find_last_of("/\\");
	if (pos == std::string::npos)
	{
		CCLOG("AssetsManagerEx : no root path specified for zip file %s\n", zip.c_str());
		return false;
	}
	const std::string rootPath = zip.substr(0, pos + 1);

	// Open the zip file
	unzFile zipfile = unzOpen(FileUtils::getInstance()->getSuitableFOpen(zip).c_str());
	if (!zipfile)
	{
		CCLOG("AssetsManagerEx : can not open downloaded zip file %s\n", zip.c_str());
		return false;
	}

	// Get info about the zip file
	unz_global_info global_info;
	if (unzGetGlobalInfo(zipfile, &global_info) != UNZ_OK)
	{
		CCLOG("AssetsManagerEx : can not read file global info of %s\n", zip.c_str());
		unzClose(zipfile);
		return false;
	}

	// Buffer to hold data read from the zip file
	char readBuffer[BUFFER_SIZE];
	// Loop to extract all files.
	uLong i;
	for (i = 0; i < global_info.number_entry; ++i)
	{
		// Get info about current file.
		unz_file_info fileInfo;
		char fileName[MAX_FILENAME];
		if (unzGetCurrentFileInfo(zipfile,
			&fileInfo,
			fileName,
			MAX_FILENAME,
			NULL,
			0,
			NULL,
			0) != UNZ_OK)
		{
			CCLOG("AssetsManagerEx : can not read compressed file info\n");
			unzClose(zipfile);
			return false;
		}
		const std::string fullPath = rootPath + fileName;

		// Check if this entry is a directory or a file.
		const size_t filenameLength = strlen(fileName);
		if (fileName[filenameLength - 1] == '/')
		{
			//There are not directory entry in some case.
			//So we need to create directory when decompressing file entry
			if (!_fileUtils->createDirectory(basename(fullPath)))
			{
				// Failed to create directory
				CCLOG("AssetsManagerEx : can not create directory %s\n", fullPath.c_str());
				unzClose(zipfile);
				return false;
			}
		}
		else
		{
			// Create all directories in advance to avoid issue
			std::string dir = basename(fullPath);
			if (!_fileUtils->isDirectoryExist(dir)) {
				if (!_fileUtils->createDirectory(dir)) {
					// Failed to create directory
					CCLOG("AssetsManagerEx : can not create directory %s\n", fullPath.c_str());
					unzClose(zipfile);
					return false;
				}
			}
			// Entry is a file, so extract it.
			// Open current file.
			if (unzOpenCurrentFile(zipfile) != UNZ_OK)
			{
				CCLOG("AssetsManagerEx : can not extract file %s\n", fileName);
				unzClose(zipfile);
				return false;
			}

			// Create a file to store current file.
			FILE *out = fopen(FileUtils::getInstance()->getSuitableFOpen(fullPath).c_str(), "wb");
			if (!out)
			{
				CCLOG("AssetsManagerEx : can not create decompress destination file %s (errno: %d)\n", fullPath.c_str(), errno);
				unzCloseCurrentFile(zipfile);
				unzClose(zipfile);
				return false;
			}

			// Write current file content to destinate file.
			int error = UNZ_OK;
			do
			{
				error = unzReadCurrentFile(zipfile, readBuffer, BUFFER_SIZE);
				if (error < 0)
				{
					CCLOG("AssetsManagerEx : can not read zip file %s, error code is %d\n", fileName, error);
					fclose(out);
					unzCloseCurrentFile(zipfile);
					unzClose(zipfile);
					return false;
				}

				if (error > 0)
				{
					fwrite(readBuffer, error, 1, out);
				}
			} while (error > 0);

			fclose(out);
		}

		unzCloseCurrentFile(zipfile);

		// Goto next entry listed in the zip file.
		if ((i + 1) < global_info.number_entry)
		{
			if (unzGoToNextFile(zipfile) != UNZ_OK)
			{
				CCLOG("AssetsManagerEx : can not read next file for decompressing\n");
				unzClose(zipfile);
				return false;
			}
		}
	}

	unzClose(zipfile);
	return true;
}

string FileManager::readFileFromPath(string pFileName) {
	
	std::string fileContents;
	fileContents = CCFileUtils::sharedFileUtils()->getStringFromFile(pFileName);

	return fileContents;

}
