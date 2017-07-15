#include "UtilFunction.h"
#include "json/writer.h"
#include "json/document.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/JSONFieldConstant.h"
#include "Helper/Helper4String.h"
#include "Info/AdditionalInfo.h"
#include "Manager/InfoManager.h"
#include "Manager/LanguageManager.h"
#include "Manager/DeviceManager.h"
#include "Views/Lobby/body/BodyLobbyLayout.h"
#include "Custom/Common/ButtonScaleChild.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Configs.h"


USING_NS_CC;

bool UtilFunction::checkValidEmail(const string &email)
{
	size_t at_index = email.find_first_of('@', 0);
	return at_index != std::string::npos
		&& email.find_first_of('.', at_index) != std::string::npos;
}

void UtilFunction::showPopupWithEffect(cocos2d::Node* node)
{
	float fadeIn = 0.2f;
	float scaleIn = 0.4f;

	node->setVisible(true);
	node->setOpacity(0);
	node->setCascadeOpacityEnabled(true);
	auto actionOpacity = FadeIn::create(fadeIn);
	auto actionScaleTo = ScaleTo::create(scaleIn, 1);
	auto ease_out_back = EaseBackOut::create(actionScaleTo);
	node->runAction(actionOpacity);
	node->runAction(ease_out_back);
}

void UtilFunction::hidePopupWithEffect(cocos2d::Node* node)
{
	float fadeIn = 0.2f;
	float scaleIn = 0.4f;

	node->setCascadeOpacityEnabled(true);
	auto actionOpacity = FadeOut::create(fadeIn);
	auto actionScaleTo = ScaleTo::create(scaleIn, 0.4f);
	auto ease_in_back = EaseBackIn::create(actionScaleTo);
	auto hideCallback = CallFunc::create([node]() {
		node->setVisible(false);
	});
	auto sequenseAction = Sequence::create(ease_in_back, hideCallback, nullptr);
	node->runAction(actionOpacity);
	node->runAction(sequenseAction);
}

void UtilFunction::setCenterNode(cocos2d::Node* node, cocos2d::Node* anotherNode, bool isCenterX, bool isCenterY)
{
	if (!node
		|| !anotherNode) {
		return;
	}
	float centerX = anotherNode->getPosition().x
		+ (0.5f - anotherNode->getAnchorPoint().x) * anotherNode->getContentSize().width
		+ (0.5f - node->getAnchorPoint().x) * node->getContentSize().width;
	float centerY = anotherNode->getPosition().y
		+ (0.5f - anotherNode->getAnchorPoint().y) * anotherNode->getContentSize().height
		+ (0.5f - node->getAnchorPoint().y) * node->getContentSize().height;
	Vec2 newPos = isCenterX ? Vec2(centerX, 0) : Vec2(node->getPosition().x, 0);
	newPos = isCenterY ? Vec2(newPos.x, centerY) : Vec2(newPos.x, node->getPosition().y);

	node->setPosition(newPos);
}
bool UtilFunction::isAvailableGameSlot(ppEnum::GameSlotOrderId orderId)
{
	switch (orderId)
	{
	case ppEnum::GameSlotOrderId::NEZHA:
	case ppEnum::GameSlotOrderId::GOLDEN_EGGS:
	case ppEnum::GameSlotOrderId::PHARAOH:
	case ppEnum::GameSlotOrderId::BOXING:
	case ppEnum::GameSlotOrderId::ROMAN_EMPIRE:
	case ppEnum::GameSlotOrderId::DEEP_BLUE:
		return true;
	default:
		return false;
	}
}
ClippingNode* UtilFunction::createCircleMask(float r)
{
	auto stencil = DrawNode::create();
	stencil->drawSolidCircle(Vec2(0, 0), r, 0.0f, 64.0f, Color4F::GREEN);

	// create the clipping node and set the stencil 
	auto clipper = ClippingNode::create();
	clipper->setStencil(stencil);
	return clipper;
}

cocos2d::Node* UtilFunction::createDarkLayer(GLubyte alpha,
	const std::function<bool (cocos2d::Touch* touch, cocos2d::Event* event)>& touchListener)
{
	//DARK LAYER
	auto darkLayer = CCLayerColor::create(ccc4(0, 0, 0, alpha));
	darkLayer->setScale(100);

	//swallow touch
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	if (touchListener) {
		listener->onTouchBegan = touchListener;
	}
	else {
		listener->onTouchBegan = [darkLayer](Touch* touch, Event* event) {
			if (Configs::printConsoleLog)
			{
				CCLOG("DARK LAYER SWALLOW TOUCH");
			}
			auto node = darkLayer->getParent();

			while (node) {
				if (!node->isVisible()) return false;
				node = node->getParent();
			}

			if (darkLayer->isVisible())
			{
				return true;
			}

			return false;
		};
	}

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, darkLayer);

	return darkLayer;
}

cocos2d::ui::Button * UtilFunction::createButtonWithText(
	const std::string& normalImage,
	const std::string& selectedImage,
	const std::string& disableImage,
	const cocos2d::ui::Widget::TextureResType & textureType,
	const std::string & titleText,
	float fontSize)
{
	std::string fontName = UtilFunction::getFontNameFromLanguage();
	auto button = ButtonScaleChild::create(normalImage, selectedImage, disableImage, textureType);
	button->setCascadeOpacityEnabled(true);
	button->setZoomScale(Configs::BUTTON_ZOOM_SCALE_VALUE);

	auto labelAutoScale = LabelAutoSize::createWithTTF(
		TTFConfig(fontName, fontSize),
		titleText
	);
	labelAutoScale->setTextColor(Color4B::WHITE);
	labelAutoScale->setCascadeOpacityEnabled(true);
	labelAutoScale->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
	labelAutoScale->setTextAreaSize(Size(button->getContentSize().width * button->getScaleX() - 20, button->getContentSize().height * button->getScaleY()));

	button->setTitleLabel(labelAutoScale);
	button->addScaleNode(labelAutoScale);
	return button;
}

std::string UtilFunction::FormatWithCommas(double value)
{
	/*long long valueAsLong = roundl(value);
	std::stringstream ss;
	ss.imbue(std::locale(""));
	ss << std::fixed << valueAsLong;
	return ss.str();*/

	long long valueAsLong = roundl(value);
	std::stringstream ss;
	ss << std::fixed << valueAsLong;
	string numWithCommas = ss.str();
	int insertPosition = numWithCommas.length() - 3;
	while (insertPosition > 0) {
		numWithCommas.insert(insertPosition, ",");
		insertPosition -= 3;
	}
	return numWithCommas;
}
double UtilFunction::getDoubleByFormatWithCommas(std::string numberFormatWithCommas)
{
	CCString::create(numberFormatWithCommas);
	auto newString 
		= Helper4String::replaceCCString(CCString::create(numberFormatWithCommas), CCString::create(","), CCString::create(""));
	return atof(newString->getCString());
}

std::string UtilFunction::trimStringAndAdd3Dots(std::string target, int numberCharacter)
{
	std::string newString;

	std::u16string string16;
	if (StringUtils::UTF8ToUTF16(target, string16)) {
		if (string16.size() <= numberCharacter) {
			return target;
		}
		StringUtils::UTF16ToUTF8(string16.substr(0, numberCharacter), newString);
	}
	else {
		if (target.size() <= numberCharacter) {
			return target;
		}
		newString = UtilFunction::utf8_substr(target, 0, numberCharacter);
	}
	newString += "...";
	return newString;
}

void UtilFunction::calculateCrownAndCoinBonusWhenLevelUp(double &coinBonus, long &crownBonus, long previousLevel, long currentLevel)
{
	long levelJump = currentLevel - previousLevel;
	long checkLevel;
	double calCoinsBonus = 0;
	long calCrownBonus = 0;
	long rewardBonusCoin = 0;
	long rewardBonusCrown = 0;
	if (levelJump > 0) {
		for (long i = 0; i < levelJump; i++) {
			checkLevel = previousLevel + i + 1;
			auto levelInfo = InfoManager::getInstance()->getLevelInfoMap()[checkLevel + 1];
			if (levelInfo){
				rewardBonusCoin = levelInfo->coinReward;
				rewardBonusCrown = levelInfo->crownReward;
			}else{
				rewardBonusCoin = InfoManager::getInstance()->getServerConfigsInfo()->coinRewardAfterUpLevel;
				rewardBonusCrown = InfoManager::getInstance()->getServerConfigsInfo()->crownRewardAfterUpLevel;
			}
			if (InfoManager::getInstance()->getAdditionalInfo()->boosterInfo->remainingTimeOfBoosterLevelUpBonus > 0){
				if ((checkLevel + 1) % 10 == 0) {
					calCoinsBonus += rewardBonusCoin *(InfoManager::getInstance()->getBoosterConfig().multiFactor1);
					calCrownBonus += rewardBonusCrown *(InfoManager::getInstance()->getBoosterConfig().multiFactor1);
				}else {
					calCoinsBonus += rewardBonusCoin *(InfoManager::getInstance()->getBoosterConfig().multiFactor2);
					calCrownBonus += rewardBonusCrown *(InfoManager::getInstance()->getBoosterConfig().multiFactor2);
				}
			}else{
				calCoinsBonus += rewardBonusCoin;
				calCrownBonus += rewardBonusCrown;
			}
		}
	}

	coinBonus = calCoinsBonus;
	crownBonus = calCrownBonus;
}

std::string UtilFunction::getFontNameFromLanguage()
{
	std::string fontName = FONT_PassionOne_Regular;
	switch (LanguageManager::getInstance()->getCurrentLanguage())
	{
	case cn:
	case tran_cn:
	{
		/*todo:comming soon*/
		fontName = FONT_CHINA;
		break;
	}
	case vn:
	{
		fontName = FONT_VIETNAME;
		break;
	}
	default:
		break;
	}
	//fontName = FONT_VIETNAME;
	return fontName;
}

std::string UtilFunction::getRandomBoundary()
{
	return ToString(RandomHelper::random_int(0, INT_MAX)) + ToString(RandomHelper::random_int(0, INT_MAX));
}

std::string UtilFunction::getPostString(const map<std::string, std::string>& postMap, const std::string & boundary)
{
	if (postMap.size() == 0) {
		return "";
	}
	std::string postString = "";
	postString += "\r\n--" + boundary;
	for (auto iter = postMap.begin(); iter != postMap.end(); ++iter) {
		postString += "\r\nContent-Disposition: form-data; name=\"" + iter->first + "\"";
		postString += "\r\n\r\n" + iter->second;
		if ((++iter)-- != postMap.end()) {
			postString += "\r\n--" + boundary;
		}
	}
	postString += "\r\n--" + boundary;
	return postString;
}

std::string UtilFunction::getMultipartData(const std::string& fieldName, const char* data, size_t len, const std::string & boundary)
{
	std::string binary = std::string(data, len);

	std::string body = "";
	body += "\r\n--" + boundary;

	body += "\r\nContent-disposition: form-data; name=\"" + fieldName + "\"; filename=\"blob\"";
	body += "\r\nContent-Type: application/octet-stream";
	body += "\r\n\r\n" + binary;

	body += "\r\n--" + boundary;

	return body;
}

cocos2d::Image * UtilFunction::fixAvatarImage(cocos2d::Image * img, int size, int orientation)
{
	auto inGameSize = size * Configs::SCALE_RESOUCE_VALUE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (DeviceManager::getInstance()->isLowRamDevice()) {
        inGameSize = size * Configs::SCALE_RESOUCE_VALUE_LOW_RAM_DEVICE;
    }
#endif
    
	Texture2D* texture = new Texture2D();
	texture->initWithImage(img);
	texture->autorelease();
	img->release();

	auto sprite = Sprite::createWithTexture(texture);

	auto spriteWidth = sprite->getContentSize().width;
	auto spriteHeight = sprite->getContentSize().height;

	int xOffset = 0, yOffset = 0;

	if (spriteWidth > spriteHeight) {
		xOffset = (spriteWidth - spriteHeight) / 2;
		spriteWidth = spriteHeight;
	}
	else if (spriteHeight > spriteWidth) {
		yOffset = (spriteHeight - spriteWidth) / 2;
		spriteHeight = spriteWidth;
	}
	sprite->setTextureRect(Rect(Vec2(xOffset, yOffset), Size(spriteWidth, spriteHeight)));

	sprite->setContentSize(Size(inGameSize, inGameSize));

	sprite->setPosition(inGameSize / 2.0f, inGameSize / 2.0f);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    switch (orientation) {
		case 1:
		case 2://ExifInterface.ORIENTATION_NORMAL:
			break;
		case 3:
		case 4://ExifInterface.ORIENTATION_ROTATE_180:
			sprite->setRotation(180);
			break;
		case 5:
		case 6://ExifInterface.ORIENTATION_TRANSPOSE:
			sprite->setRotation(90);
			break;
		case 7:
		case 8:
			sprite->setRotation(-90);
			break;
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    switch (orientation) {
        case 0:
        case 4://UP:
            break;
        case 1:
        case 5://DOWN:
            sprite->setRotation(180);
            break;
        case 2:
        case 6://LEFT:
            sprite->setRotation(-90);
            break;
        case 3:
        case 7://RIGHT:
            sprite->setRotation(90);
            break;
    }
#endif


	auto renderTexture = RenderTexture::create(inGameSize, inGameSize);
	
	renderTexture->beginWithClear(0, 0, 0, 0);
	sprite->visit();
	renderTexture->end();

	Director::getInstance()->getRenderer()->render();

	Image* newImg = renderTexture->newImage();

	return newImg;
}
std::string UtilFunction::formatCoinNumber(double & coinNumber)
{
	std::string result = "";
	bool isNegative = false;
	long long coinValue = coinNumber;//parseInt(coin, 10);
	if (coinValue < 0) {
		isNegative = true;
		coinValue = -coinValue;
	}
	if (coinValue < 1000) {
		result += coinValue;
	}
	else if (coinValue < 1000000) {
		long quotient = floor(coinValue / 1000);
		long wtf = coinValue - 1000 * quotient;
		wtf = floor(wtf / 100);
		if (wtf > 0) {
			result += ToString(quotient) + '.' + ToString(wtf) + 'K';
		}
		else {
			result += ToString(quotient) + 'K';
		}
	}
	else if (coinValue < 1000000000) {
		long quotient = floor(coinValue / 1000000);
		long wtf = coinValue - 1000000 * quotient;
		if (wtf > 0) {
			wtf = floor(wtf / 100000);
		}
		result += ToString(quotient) + '.' + ToString(wtf) + 'M';
	}
	else {
		long quotient = floor(coinValue / 1000000000);
		long wtf = coinValue - 1000000000 * quotient;
		wtf = floor(wtf / 100000000);
		result += ToString(quotient) + '.' + ToString(wtf) + 'B';
	}
	if (isNegative) {
		result = "-" + result;
	}
	return result;
}

std::string UtilFunction::getAvatarUrl(USER_ROLE role, std::string facebookUI, std::string userFullAvatarUrl, int width, int height)
{
	std::string urlAvatar = PNG_HEADER_AVATAR_ICON;
	if (role == USER_ROLE::FACEBOOK
		&& !facebookUI.empty())
	{
		urlAvatar = "https://graph.facebook.com/" + facebookUI +
			"/picture?type=normal&width=" + ToString(width) + "&height=" + ToString(height);
	}
	else if (role == USER_ROLE::PLAYPALACE
		&& !userFullAvatarUrl.empty())
	{
		urlAvatar = userFullAvatarUrl;
	}
	return urlAvatar;
}

std::string UtilFunction::utf8_substr(const std::string& str, unsigned int start, unsigned int leng)
{
	if (leng == 0) { return ""; }
	unsigned int c, i, ix, q, min = std::string::npos, max = std::string::npos;
	for (q = 0, i = 0, ix = str.length(); i < ix; i++, q++)
	{
		if (q == start) { min = i; }
		if (q <= start + leng || leng == std::string::npos) { max = i; }

		c = (unsigned char)str[i];
		if (
			//c>=0   &&
			c <= 127) i += 0;
		else if ((c & 0xE0) == 0xC0) i += 1;
		else if ((c & 0xF0) == 0xE0) i += 2;
		else if ((c & 0xF8) == 0xF0) i += 3;
		//else if (($c & 0xFC) == 0xF8) i+=4; // 111110bb //byte 5, unnecessary in 4 byte UTF-8
		//else if (($c & 0xFE) == 0xFC) i+=5; // 1111110b //byte 6, unnecessary in 4 byte UTF-8
		else return "";//invalid utf8
	}
	if (q <= start + leng || leng == std::string::npos) { max = i; }
	if (min == std::string::npos || max == std::string::npos) { return ""; }
	return str.substr(min, max);
}

std::string UtilFunction::timeStampToSimpleString(long timestamp)
{
	if (timestamp > (1000 * 60 * 60 * 24)) {
		timestamp = round(timestamp *1.0 / (1000 * 60 * 60 * 24));
		if (timestamp > 1) {
			return ToString(timestamp) + " days";
		}
		else {
			return ToString(timestamp) + " day";
		}
	}
	// 2017-22-03: Huy: if timestamp > 1h
	else if (timestamp > (1000 * 60 * 60)) {
		timestamp = round(timestamp *1.0 / (1000 * 60 * 60));
		if (timestamp > 1) {
			if (timestamp != 24) {
				return ToString(timestamp) + " hours";
			}
			else {
				return "1 day";
			}
		}
		else {
			return ToString(timestamp) + " hour";
		}
	}
	// 2017-22-03: Huy: if timestamp > 1m
	else if (timestamp > (1000 * 60)) {
		timestamp = round(timestamp *1.0 / (1000 * 60));
		if (timestamp > 1) {
			if (timestamp != 60) {
				return ToString(timestamp) + " minutes";
			}
			else {
				return "1 hour";
			}
		}
		else {
			return ToString(timestamp) + " minute";
		}
	}
	// 2017-22-03: Huy: if timestamp < 1m
	else {
		timestamp = round(timestamp *1.0 / 1000);
		if (timestamp > 1) {
			if (timestamp != 60) {
				return ToString(timestamp) + " seconds";
			}
			else {
				return "1 minute";
			}
		}
		else {
			return ToString(timestamp) + " second";
		}
	}
}

void UtilFunction::releaseCache(const std::string & fileName)
{
	auto textureCache = TextureCache::getInstance();
	auto spriteFrameCache = SpriteFrameCache::getInstance();

	auto lastChar = fileName.at(fileName.size() - 1);
	if (lastChar == 'g') {
		textureCache->removeTextureForKey(fileName);
	}
	else if (lastChar == 't') {
		auto texturePath = fileName;
		// remove .xxx
		size_t startPos = texturePath.find_last_of(".");
		texturePath = texturePath.erase(startPos);

		auto pngPath = texturePath; pngPath.append(".png");
		auto jpgPath = texturePath; jpgPath.append(".jpg");
		auto tex = textureCache->getTextureForKey(pngPath);
		if (!tex) { tex = textureCache->getTextureForKey(jpgPath); }

		spriteFrameCache->removeSpriteFramesFromFile(fileName);
		textureCache->removeTexture(tex);
	}
}

void UtilFunction::handleMagicItemAfterSpinRecieve(
	int typeMagicItem,
	double winMagicItem,
	int numberOfLuckySymbolWin,
	std::string luckySymbolPos,
	int remainingSpin,
	long remainingTime,
	int **luckySymbolWheelsOutput
)
{
	if (typeMagicItem == LobbyConstant::MagicItemType::MAGIC_ITEM_TYPE_DEFAULT) {
		return;
	}
	auto magicItemInfo = InfoManager::getInstance()->getAdditionalInfo()->magicItemInfo;
	switch (typeMagicItem)
	{
	case LobbyConstant::MAGIC_ITEM_TYPE_100_PERCENT_BIG_WIN:
		magicItemInfo->remainingSpinOfMagicItem100PercentBigWin = remainingSpin;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_100_PERCENT_MEGA_WIN:
		magicItemInfo->remainingSpinOfMagicItem100PercentMegaWin = remainingSpin;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_1:
		magicItemInfo->remainingSpinOfMagicItemLuckySpinType1 = remainingSpin;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SPIN_TYPE_2:
		magicItemInfo->remainingSpinOfMagicItemLuckySpinType2 = remainingSpin;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_DOUBLE_EXP:
		magicItemInfo->remainingTimeOfMagicItemDoubleExp = remainingTime;
		break;
	case LobbyConstant::MAGIC_ITEM_TYPE_LUCKY_SYMBOL:
		magicItemInfo->remainingTimeOfMagicItemLuckySymbol = remainingTime;
		if (numberOfLuckySymbolWin > 0)
		{
			auto aLuckySymbplPos = Helper4String::splitString(luckySymbolPos, ",");
			for (auto pos : aLuckySymbplPos)
			{
				int posAsInt = stoi(pos);
				if (posAsInt > 0)
				{
					int col = (posAsInt - 1) / 3;
					int row = (posAsInt - 1) % 3;
					//danh dau ngay vi tri nay co luckysymbol
					luckySymbolWheelsOutput[row][col] = 1;
				}
			}
		}
		break;
	default:
		break;
	}

}

float UtilFunction::getFontSizeFromLabel(cocos2d::Label * label)
{
	bool isTTFLabel = label->getTTFConfig().fontFilePath != "";
	if (isTTFLabel)
	{
		return label->getTTFConfig().fontSize;
	}
	return label->getSystemFontSize();
}

int UtilFunction::getLabelType(cocos2d::Label * label)
{
	if (label->getTTFConfig().fontFilePath == "")
	{
		return SYSTEM_LABEL_TYPE;
	}
	return TTF_LABEL_TYPE;
}

void UtilFunction::setFontForLabel(cocos2d::Label * label, string fontName, float fontSize, bool isSystemFont)
{
	Color4B oldColor = label->getTextColor();
	TextHAlignment oldHAligment = label->getHorizontalAlignment();
	TextVAlignment oldVAligment = label->getVerticalAlignment();
	Size oldDimensions = label->getDimensions();
	if (isSystemFont){
		label->setTTFConfig(TTFConfig());
		label->setSystemFontName(fontName);
		label->setSystemFontSize(fontSize);
	}else{
		label->setTTFConfig(TTFConfig(fontName, fontSize));
	}
	label->setTextColor(oldColor);
	label->setHorizontalAlignment(oldHAligment);
	label->setVerticalAlignment(oldVAligment);
	label->setDimensions(oldDimensions.width, oldDimensions.height);
}

void UtilFunction::setLabelFontByLanguage(cocos2d::Label * label){

	std::string fontName = UtilFunction::getFontNameFromLanguage();
	setLabelFontByLanguage(label,fontName);
}


void UtilFunction::setLabelFontByLanguage(cocos2d::Label * label, std::string customizeFont, int fontSize) {
	if (label == nullptr) return;
	std::string currentLanguageName = LanguageManager::getInstance()->getCurrentLanguageName();
	if (currentLanguageName == CN_TEXT || currentLanguageName == TAIWAN_TEXT){
		UtilFunction::setFontForLabel(label, "Arial", (fontSize!=0)? fontSize:UtilFunction::getFontSizeFromLabel(label), SYSTEM_FONT);
	}else{
		std::string fontName = UtilFunction::getFontNameFromLanguage();
		if (customizeFont == "") customizeFont = fontName;
		UtilFunction::setFontForLabel(label, customizeFont, (fontSize != 0) ? fontSize : UtilFunction::getFontSizeFromLabel(label), TTF_FONT);
	}

}

bool UtilFunction::isVietnameseUnicode(char16_t ch)
{
	return
		/*TODO:
		/* Belows symbols can be displayed by Passion font so we doest need to check;
		*/
		//(ch >= 0x00C0 && ch <= 0x00C3) || 	//A`, A', A^, A~
		//(ch >= 0x00C8 && ch <= 0x00CA) || 	//E`, E', E^
		//(ch >= 0x00CC && ch <= 0x00CD) || 	//I`, I'
		//(ch >= 0x00D2 && ch <= 0x00D5) ||	//O`, O', O^, O~
		//(ch >= 0x00D9 && ch <= 0x00DA) ||	//U`, U'
		//(ch == 0x00DD)				 ||	//Y'
		//(ch >= 0x00E0 && ch <= 0x00E3) ||	//a`, a', a^, a~
		//(ch >= 0x00E8 && ch <= 0x00EA) ||	//e`, e', e^
		//(ch >= 0x00EC && ch <= 0x00ED) ||	//i`, i'
		//(ch >= 0x00F2 && ch <= 0x00F5) ||	//o`, o', o^, o~
		//(ch >= 0x00F9 && ch <= 0x00FA) ||	//u`, u'
		//(ch == 0x00FD)				 ||	//y'

		/*TODO:
		/* Below symbols is only Vietnamese font can show
		*/
		(ch >= 0x0102 && ch <= 0x0103) ||	//A-, a-
		(ch == 0x00D0)				   ||	//-D
		(ch >= 0x0110 && ch <= 0x0111) ||	//-D, -d
		(ch >= 0x0128 && ch <= 0x0129) ||	//I~, i~
		(ch >= 0x0168 && ch <= 0x0169) ||	//U~, u~
		(ch >= 0x01A0 && ch <= 0x01B0) ||	//O?, o?, U?, u? and some symbols not letter
		(ch >= 0x1EA0 && ch <= 0x1EF9);		//other Vietnamese letters
}

void UtilFunction::detectFontAndSetStringForLabel(cocos2d::Label * label, const std::string & font, const std::string & text)
{
	if (!label) return;

	bool isVietnameseUnicode = false;
	bool isCJKUnicode = false;

	u16string string16;
	if (StringUtils::UTF8ToUTF16(text, string16)) {
		for (auto _char : string16) {
			if (UtilFunction::isVietnameseUnicode(_char)) {
				isVietnameseUnicode = true;
				break;
			}
			else if (StringUtils::isCJKUnicode(_char)) {
				isCJKUnicode = true;
				break;
			}
		}
	}
	if (isVietnameseUnicode) {
		UtilFunction::setFontForLabel(label, FONT_VIETNAME, UtilFunction::getFontSizeFromLabel(label), TTF_FONT);
	}
	else if (isCJKUnicode) {
		UtilFunction::setFontForLabel(label, "Arial", UtilFunction::getFontSizeFromLabel(label), SYSTEM_FONT);
	}
	else {
		UtilFunction::setFontForLabel(label, font, UtilFunction::getFontSizeFromLabel(label), TTF_FONT);
	}
	label->setString(text);
}
