#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-09
* file: LanguageManager.h, LanguageManager.cpp
*/

#include "cocos2d.h"
#include "json/document.h"
#include "json/writer.h"

using namespace rapidjson;

#define ENGLISH_TEXT "English"
#define TIENG_VIET_TEXT "Tiếng Việt"
#define CN_TEXT "简体"
#define TAIWAN_TEXT "繁體"
#define MALAY_TEXT "B-Malay"
#define INDO_TEXT "B-Indonesia"
#define DEFAULT_FONT "Helvetica"

enum SupportLanguage
{
	en = 0,
	cn = 2,
	tran_cn = 3,
	vn = 4,
	my = 5,
	indo = 6
};
class IUpdateLanguage;
class LanguageManager
{
private:
    void initData();
    Document document; // current document with language data
    bool isGetMainLanguageSuccess = false;
    Document documentDefault; // current document with language data
    bool isGetDefaultLanguageSuccess = false;
	LanguageManager(); // constructor is private
	SupportLanguage currentLanguage;

	std::vector<IUpdateLanguage*> listRetainObjectUpdateLanguage; //contain object like: popup setting, popup achievement,.. (object retain and only init 1 time)
	std::vector<IUpdateLanguage*> listObjectWillBeClearUpdateLanguage; //contain object like: button game slot,.. (object will be remove if run another scene, and objects in this list will be clear in reset fuction)
	std::vector<IUpdateLanguage*> listObjectWillBeClearUpdateLanguageTemp;// temp listObjectWillBeClearUpdateLanguage

	int numberTimeChangeLanguage = 0; //set all system font base on this varible
	static LanguageManager* s_instance;
	cocos2d::Scene* currentScene = nullptr;
public:
	/**
	* 2017-02-09: Kiet: get instance class
	*/
	static LanguageManager* getInstance();
	/**
	* 2017-02-27: Kiet: destructor
	*/
	~LanguageManager();
	/**
	* 2017-03-02: Kiet: reset language manager
	*/
	void reset();
	/**
	* 2017-02-09: Kiet: get string for key
	*/
    std::string getStringForKeys(cocos2d::Label * label, std::string key, std::string key2 = "text");
	/**
	* 2017-02-09: Kiet: get current language
	*/
	SupportLanguage getCurrentLanguage() { return currentLanguage; }

	/// <summary>
	/// update current language to cache
	/// </summary>
	/// <param name="language"></param>
	void updateCurrentLanguageToCache(SupportLanguage language);
	/// <summary>
	/// parse language from string format json
	/// </summary>
	/// <param name="languageJson"></param>
	void parseLanguageFromJsonString(std::string languageJson);
	/**
	* 2017-02-09: Kiet: set current language
	*/
	bool setCurrentLanguage(SupportLanguage language);
	/**
	* 2017-02-22: Kiet: add IUpdateLanguage to list need update when click change language button
	*/
	void pushBackToUpdateLanguageList(IUpdateLanguage* iUpdate, bool isRetainObject = true);
	/**
	* 2017-02-22: Kiet: update all list language base on current language
	*/
	void updateLanguageForApp();
	/**
	* 2017-02-22: Kiet: get name of current language ( use for setting popup )
	*/
	std::string getCurrentLanguageName();
	/**
	* Dat: set for fail parse language
	*/
	bool setLanguage4ParseLanguageFail();
	/**
	* 2017-02-22: Kiet: get number time change language
	*/
	int getNumberChangeLanguage() {
		return this->numberTimeChangeLanguage;
	};
};
