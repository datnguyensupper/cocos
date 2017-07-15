#include "CLoader.h"
#include "Helper/Helper4Sprite.h"
#include "Manager/SoundManager.h"

USING_NS_CC;

CLoader* CLoader::getInstance()
{
	auto poolSystem = CPoolManager::getInstance()->getSystem("CLoader");
	if (!poolSystem) {
		poolSystem = CPoolManager::getInstance()->createSystem("CLoader", []() {
			auto loader = new CLoader();
			return loader;
		});
	}
	return (CLoader*)poolSystem->spawn();
}

CLoader::~CLoader()
{
}

void CLoader::_loadImage(const string& image) {
	if (this->bStop) {
		return;
	}

	if (this->bLoadMainThread) {
		TextureCache::getInstance()->addImage(image);
		this->onFileLoaded();
	}
	else {
//        if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS){
//            TextureCache::getInstance()->addImage(image);
//            this->onFileLoaded();
//        }else{
			Helper4Sprite::addOptimizeImageAsync(image, [this](Texture2D* tex) {
                this->onFileLoaded();
            });
            
//        }
	}
}
void CLoader::_loadPlist(const string& plist) {
	if (this->bStop) {
		return;
	}
	if (this->bLoadMainThread
//        &&
//        CC_TARGET_PLATFORM != CC_PLATFORM_IOS
        ) {
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist);
		this->onFileLoaded();
	}
	else {
		auto texturePath = plist;
		// remove .xxx
		size_t startPos = texturePath.find_last_of(".");
		texturePath = texturePath.erase(startPos);

		auto pngPath = texturePath; pngPath.append(".png");
		auto jpgPath = texturePath; jpgPath.append(".jpg");

		auto fileUtils = FileUtils::getInstance();
        string imagePath = "";
        if (fileUtils->isFileExist(pngPath)) {
            imagePath = pngPath;
        }
        else if (fileUtils->isFileExist(jpgPath)) {
            imagePath = jpgPath;
		}
        
        if(imagePath.compare("") != 0){
//            if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS){
//                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, TextureCache::getInstance()->addImage(imagePath));
//                this->onFileLoaded();
//            }else{
				Helper4Sprite::addOptimizeImageAsync(imagePath, [this, plist](Texture2D* tex) {
                    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist, tex);
                    this->onFileLoaded();
                });
//            }
        }
        else {
            this->onFileLoaded();
        }
    }
}
void CLoader::_loadSound(const string & sound)
{
	if (this->bStop) {
		return;
	}

	SoundManager::getInstance()->preload(sound, [this, sound](bool isSuccess) {
		this->onFileLoaded(true);
	});
}
void CLoader::onFileLoaded(bool isFromSound) {
	if (this->bStop) {
		return;
	}
	this->currentFiles = MIN(this->currentFiles + 1, this->totalFiles);
	if (this->callbackFileLoaded) {
		this->callbackFileLoaded(this->currentFiles * 1.0f / this->totalFiles);
	}

	this->bLoadNextFile = true;
	if (!this->bLoadMainThread) {
		this->loadNextFile();
	}
	else if (isFromSound) {
		this->bLoadNextFile = false;
		this->loadNextFile();
	}
}

void CLoader::resetLoading() {
	this->totalFiles = 0;
	this->currentFiles = 0;
	this->resources.clear();
	this->callbackComplete = nullptr;
	this->callbackFileLoaded = nullptr;

	this->bStop = false;
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
	if (this->bStop) {
		return;
	}

	this->bLoadNextFile = false;

	if (this->currentFiles < this->totalFiles) {
		auto filePath = resources[this->currentFiles];

		log("loading File... %s", filePath.c_str());

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
	const function<void(float progress)>& callbackFileLoaded,
	bool bLoadMainThread) {
	this->bLoadMainThread = bLoadMainThread;
	this->bLoadNextFile = true;

	if (this->bLoadMainThread) {
		Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	}
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

void CLoader::stop()
{
	if (this->bStop) {
		return;
	}
	this->bStop = true;
	this->system->destroy(this);
}

void CLoader::stopAll()
{
	for (auto loader : system->getAll()) {
		if (loader) {
			((CLoader*)loader)->stop();
		}
	}
}

void CLoader::active()
{
	this->resetLoading();
}

void CLoader::deactive()
{
	this->bStop = true;

	Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void CLoader::update(float dt)
{
	if (this->bStop) return;
	if (this->bLoadMainThread) {
		if (this->bLoadNextFile) {
			this->loadNextFile();
		}
	}
}

