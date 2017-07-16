#pragma once
/**
* creator: Kiet Duong
* date: 2017-02-06
* file: UtilFunction.h, UtilFunction.cpp
*/
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Constant/PPEnums.h"
#include "Constant/LobbyConstant.h"

#define SYSTEM_LABEL_TYPE 1
#define TTF_LABEL_TYPE 2
#define SYSTEM_FONT true
#define TTF_FONT false
using namespace std;

class MobilePaymentInfo;
class UtilFunction
{
public:
	/// <summary>
	/// check valid input email
	/// </summary>
	/// <param name="email"></param>
	/// <returns></returns>
	static bool checkValidEmail(const string &email);
	/// <summary>
	/// show popup with animation
	/// </summary>
	/// <param name="node"></param>
	static void showPopupWithEffect(cocos2d::Node* node);
	/// <summary>
	/// hide popup with animation
	/// </summary>
	/// <param name="node"></param>
	static void hidePopupWithEffect(cocos2d::Node* node);
	/**
	* 2017-02-15: Kiet: set center another node (is not parent of node)
	*/
	static void setCenterNode(cocos2d::Node* node, cocos2d::Node* anotherNode, bool isCenterX = true, bool isCenterY = true);
	
	/**
	* 2017-02-15: Kiet: check game slot with orderId param is available?
	* @param: orderId (see enum GameSlotOrderId in file BodyLobbyLayout.h for more infomation)
	*/
	static bool isAvailableGameSlot(ppEnum::GameSlotOrderId orderId);

	/**
	* 2017-02-20: Kiet: create circle mask
	* @param: r radius
	*/
	static cocos2d::ClippingNode* createCircleMask(float r);

	/**
	* create circle mask
	*/
	static cocos2d::Node* createDarkLayer(GLubyte alpha = 150,
		const std::function<bool (cocos2d::Touch* touch, cocos2d::Event* event)>& touchListener = nullptr);

	/// <summary>
	/// create button with text
	/// </summary>
	/// <param name="normalImage"></param>
	/// <param name="selectedImage"></param>
	/// <param name="disableImage"></param>
	/// <param name="textureType"></param>
	/// <param name="titleText"></param>
	/// <param name="fontSize"></param>
	/// <returns></returns>
	static cocos2d::ui::Button* createButtonWithText(
		const std::string& normalImage,
		const std::string& selectedImage = "",
		const std::string& disableImage = "",
		const cocos2d::ui::Widget::TextureResType& textureType = cocos2d::ui::Widget::TextureResType::LOCAL,
		const std::string& titleText = "",
		float fontSize = 60);

	/**
	* 2017-02-20: Kiet: format number split by comma 
	* example: 1000-> 1,000; 54956708->54,956,708
	*/
	static std::string FormatWithCommas(double value);

	/**
	* 2017-02-20: Kiet: format number by comma to double
	* example: 1,000-> 1000; 8,567,677->856677
	*/
	static double getDoubleByFormatWithCommas(std::string numberFormatWithCommas);

	/**
	* 2017-02-20: Kiet: trim string
	* @param target: target string
	* @para numberCharacter: max char for target full string 
	* @return: example: trimStringAndAdd3Dots("Nguyen Van A", 8) -> "Nguyen V..."
	*/
	static std::string trimStringAndAdd3Dots(std::string target, int numberCharacter);

	/**
	* 2017-02-27: Kiet: calculate crown bonus and coin bonus when level up
	*/
	static void calculateCrownAndCoinBonusWhenLevelUp(double &coinBonus, long &crownBonus, long previousLevel, long currentLevel);
	/**
	* 2017-03-01: Kiet: get font name from language
	*/
	static std::string getFontNameFromLanguage();

#pragma region Network

	/**
	* Return random boundary for upload multipart
	*/
	static std::string getRandomBoundary();
	/**
	* Parse map formData with boundary to string
	*/
	static std::string getPostString(const map<std::string, std::string>& postMap, const std::string& boundary);
	/**
	* Get formData for multipart as string
	*/
	static std::string getMultipartData(const std::string& fieldName, const char* data, size_t len, const std::string& boundary);

#pragma endregion

#pragma region Image

	/**
	* Resize Image
	*/
	static cocos2d::Image* fixAvatarImage(cocos2d::Image* img, int size, int orientation);

#pragma endregion
	/**
	* 2017-03-08: Kiet: format number to k, m, b. Example coin = 100000, return 100k; coin 1000000000, return 1b
	*/
	static std::string formatCoinNumber(double &coinNumber);

	/// <summary>
	/// 2017-03-10: Kiet: get avatar url
	/// </summary>
	/// <param name="role">role of user</param>
	/// <param name="facebookUI">facebook udid</param>
	/// <param name="userFullAvatarUrl">avatar url</param>
	/// <param name="width">avatar width</param>
	/// <param name="height">avatar height</param>
	/// <returns></returns>
	static std::string getAvatarUrl(
		USER_ROLE role,
		std::string facebookUI, 
		std::string userFullAvatarUrl,
		int width = 100, 
		int height = 100);

	/**
	* 2017-03-20: Kiet: utf8 substr
	*/
	static std::string utf8_substr(const std::string& str, unsigned int start, unsigned int leng);

	/**
	* 2017-04-18: Kiet: time stamp to simple string
	*/
	static std::string timeStampToSimpleString(long timestamp);

	/*
	* Release texture cache, spite frame cache
	* @param name: texture file name or sprite frame name
	*/
	static void releaseCache(const std::string& name);
	/// <summary>
	/// handle and show UI result of magic item after spin
	/// </summary>
	/// <param name="typeMagicItem">magic item type</param>
	/// <param name="winMagicItem">win amount</param>
	/// <param name="numberOfLuckySymbolWin">number of lucky symbol</param>
	/// <param name="luckySymbolPos">lucky symbol position</param>
	/// <param name="remainingSpin">remaining spin</param>
	/// <param name="remainingTime">remaining time</param>
	/// <param name="luckySymbolWheelsOutput">parse luckysymbol position from luckySymbolPos and save to luckySymbolWheelsOutput </param>
	static void handleMagicItemAfterSpinRecieve(
		int typeMagicItem,
		double winMagicItem,
		int numberOfLuckySymbolWin,
		std::string luckySymbolPos,
		int remainingSpin,
		long remainingTime,
		int **luckySymbolWheelsOutput
	);
	/// <summary>
	/// get font size from label
	/// </summary>
	/// <param name="label"></param>
	/// <returns></returns>
	static float getFontSizeFromLabel(cocos2d::Label * label);
	/// <summary>
	/// get label type
	/// </summary>
	/// <param name="label"></param>
	/// <returns>is system font or customize font</returns>
	static int getLabelType(cocos2d::Label * label);
	/// <summary>
	/// set font for label by chosen languag
	/// </summary>
	/// <param name="label">lalel</param>
	/// <param name="fontName">customize font name</param>
	/// <param name="fontSize"></param>
	/// <param name="isSystemFont">is use system font</param>
	static void setFontForLabel(cocos2d::Label * label, string fontName, float fontSize, bool isSystemFont);
	/// <summary>
	/// set font for label by chosen language
	/// </summary>
	/// <param name="label"></param>
	static void setLabelFontByLanguage(cocos2d::Label * label);
	/// <summary>
	/// set label font by current language
	/// </summary>
	/// <param name="label"></param>
	/// <param name="customizeFont">customize font in case not use system font</param>
	/// <param name="fontSize"></param>
	static void setLabelFontByLanguage(cocos2d::Label * label,std::string customizeFont,int fontSize = 0);

	/**
	*  @brief Whether the character is a Vietnamese/Chinese/Japanese/Korean character.
	*  @param ch    The unicode character.
	*  @returns     Whether the character is a Chinese character.
	*
	*/
	static bool isVietnameseUnicode(char16_t ch);
	/**
	*  detect if this label string contains Vietnamese/Chinese/Japanese/Korean character,
	* if so, we will using system font, if not we use it's font.
	*  @param label  label
	*  @param font  customize font for label in case not system font
	*  @param text   text of label
	*
	*/
	static void detectFontAndSetStringForLabel(cocos2d::Label * label, const std::string & font, const std::string& text);

	/**
	*  purchase item in a convenient way
	*  @param itemID
	*  @param cb
	*  @param cbError
	*
	*/
	static void purchaseItem(
		const std::string& itemID, 
		bool bHideLoadingAfterFinishPurchase = true,
		const std::function<void(int, MobilePaymentInfo*)> cb = nullptr, 
		const std::function<void()> cbError = nullptr,
		const std::function<void()> cbCancle = nullptr);
};
