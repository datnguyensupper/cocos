#include "CLoader.h"
#include "SimpleAudioEngine.h"
#include "AudioEngine.h"

USING_NS_CC;

CLoader* CLoader::getInstance()
{
	auto poolSystem = CPoolManager::getInstance()->getSystem("CLoader");
	if (!poolSystem) {
		poolSystem = CPoolManager::getInstance()->createSystem("CLoader", []() {
			return new CLoader();
		});
	}
	return (CLoader*)poolSystem->spawn();
}

CLoader::~CLoader()
{
}

void CLoader::_loadImage(const string& image) {
	TextureCache::getInstance()->addImageAsync(image, [this](Texture2D* tex) {
		this->onFileLoaded();
	});
}
void CLoader::_loadPlist(const string& plist) {
	auto texturePath = plist;
	// remove .xxx
	size_t startPos = texturePath.find_last_of(".");
	texturePath = texturePath.erase(startPos);

	auto pngPath = texturePath; pngPath.append(".png");
	auto jpgPath = texturePath; jpgPath.append(".jpg");

	auto fileUtils = FileUtils::getInstance();
	if (fileUtils->isFileExist(pngPath)) {
		TextureCache::getInstance()->addImageAsync(pngPath, [this, plist](Texture2D* tex) {
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, tex);
			this->onFileLoaded();
		});
	}
	else if (fileUtils->isFileExist(jpgPath)) {
		TextureCache::getInstance()->addImageAsync(jpgPath, [this, plist](Texture2D* tex) {
			SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, tex);
			this->onFileLoaded();
		});
	}
	else {
		this->onFileLoaded();
	}
}
void CLoader::_loadSound(const string & sound)
{
	experimental::AudioEngine::preload(sound, [this, sound](bool isSuccess) {
		this->onFileLoaded();
	});
}
void CLoader::onFileLoaded() {
	this->currentFiles = MIN(this->currentFiles + 1, this->totalFiles);
	if (this->callbackFileLoaded) {
		this->callbackFileLoaded(this->currentFiles * 1.0f / this->totalFiles);
	}
	this->loadNextFile();
}

void CLoader::resetLoading() {
	this->totalFiles = 0;
	this->currentFiles = 0;
	this->resources.clear();
	this->callbackComplete = nullptr;
	this->callbackFileLoaded = nullptr;
}

void CLoader::completeLoading()
{
	if (this->callbackComplete) {
		this->callbackComplete();
	}
	this->resetLoading();
	this->system->destroy(this);
}

void CLoader::loadNextFile() {
	if (this->currentFiles < this->totalFiles) {
		auto filePath = resources[this->currentFiles];

		auto extension = filePath;
		// remove .xxx
		size_t startPos = extension.find_last_of(".");
		extension = extension.erase(0, startPos);

		if (extension.compare(".plist") == 0) {
			this->_loadPlist(filePath);
		}else if (extension.compare(".mp3") == 0 ||
			extension.compare(".wav") == 0) {
			this->_loadSound(filePath);
		}else {
			this->_loadImage(filePath);
		}
	}
	else {
		this->completeLoading();
	}
}

void CLoader::startLoadingResources(
	const vector<string>& resources,
	const function<void()>& callbackComplete,
	const function<void(float progress)>& callbackFileLoaded) {
	this->currentFiles = this->totalFiles = 0;
	if (resources.size() > 0) {
		this->resources = resources;
		this->totalFiles = resources.size();
	}
	else {
		this->system->destroy(this);
		return;
	}
	this->callbackComplete = callbackComplete;
	this->callbackFileLoaded = callbackFileLoaded;

	this->loadNextFile();
}

void CLoader::active()
{
	this->resetLoading();
}

