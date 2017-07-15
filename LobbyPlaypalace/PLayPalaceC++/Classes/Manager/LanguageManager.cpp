#include "Manager/LanguageManager.h"
#include "Constant/Defination.h"
#include "Views/IUpdateLanguage.h"
#include "Helper/Helper4Scene.h"
#include "Util/UtilFunction.h"

using namespace std;
USING_NS_CC;
#pragma region init singleton
LanguageManager* LanguageManager::s_instance = nullptr;

LanguageManager* LanguageManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new LanguageManager();
	}
	auto runningScene = Helper4Scene::getRunningScene();
	if (s_instance->currentScene != runningScene) {
		s_instance->currentScene = runningScene;
		s_instance->reset();
	}
	return s_instance;
}
#pragma endregion

LanguageManager::LanguageManager() 
{
	int currentIdLanguage = CCUserDefault::getInstance()->getIntegerForKey(STORING_KEY_CURRENT_LANGUAGE);
	SupportLanguage currentLanguage = static_cast<SupportLanguage>(currentIdLanguage);
	this->setCurrentLanguage(currentLanguage);
}

LanguageManager::~LanguageManager()
{
	CC_SAFE_DELETE(s_instance);
}

void LanguageManager::reset()
{
	this->listObjectWillBeClearUpdateLanguage = this->listObjectWillBeClearUpdateLanguageTemp;
	this->listObjectWillBeClearUpdateLanguageTemp.clear();
}

string LanguageManager::getStringForKeys(cocos2d::Label * label, std::string key, std::string key2){
	UtilFunction::setLabelFontByLanguage(label);
	return document[key.c_str()][key2.c_str()].GetString();
}

void LanguageManager::setCurrentLanguage(SupportLanguage language)
{
	string fileName = "language/en.json";
	switch (language)
	{
	case en:
		fileName = "language/en.json";
		break;
	case cn:
		fileName = "language/cn.json";
		break;
	case tran_cn:
		fileName = "language/cn_tran.json";
		break;
	case vn:
		fileName = "language/vn.json";
		break;
	case my:
		fileName = "language/my.json";
		break;
	case indo:
		fileName = "language/indo.json";
		break;
	default:
		return;
	}
	this->numberTimeChangeLanguage ++;
	this->currentLanguage = language; 
	CCUserDefault::getInstance()->setIntegerForKey(STORING_KEY_CURRENT_LANGUAGE, this->currentLanguage);
	cocos2d::CCUserDefault::getInstance()->flush();
	// below we open, read and parse language data file with rapidjson library
	ssize_t nSize = 0;
	const char* buf = (const char*)CCFileUtils::sharedFileUtils()->getFileData(fileName.c_str(), "r", &nSize);
	string content(buf);
	string clearContent = content.substr(0, content.rfind('}') + 1);

	document.Parse<0>(clearContent.c_str());

	if (document.HasParseError())
	{
		CCLOG("Language file parsing error!");
		return;
	}
}

void LanguageManager::pushBackToUpdateLanguageList(IUpdateLanguage* iUpdate, bool isRetainObject)
{
	if (isRetainObject)
	{
		this->listRetainObjectUpdateLanguage.push_back(iUpdate);
	}
	else
	{
		this->listObjectWillBeClearUpdateLanguageTemp.push_back(iUpdate);
	}
}

void LanguageManager::updateLanguageForApp()
{
	for (auto& iUpdate : this->listRetainObjectUpdateLanguage)
	{
		if (iUpdate != nullptr)
		{
			iUpdate->updateAfterChangeLanguage();
		}
	}
	for (auto& iUpdate : this->listObjectWillBeClearUpdateLanguage)
	{
		if (iUpdate != nullptr)
		{
			iUpdate->updateAfterChangeLanguage();
		}
	}
}

std::string LanguageManager::getCurrentLanguageName()
{
	switch (this->currentLanguage)
	{
	case en:
		return ENGLISH_TEXT;
	case cn:
		return CN_TEXT;
	case tran_cn:
		return TAIWAN_TEXT;
	case vn:
		return TIENG_VIET_TEXT;
	case my:
		return MALAY_TEXT;
	case indo:
		return INDO_TEXT;
	default:
		return ENGLISH_TEXT;
	}
}
