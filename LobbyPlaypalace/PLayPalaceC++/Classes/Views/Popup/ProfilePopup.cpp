#include "ProfilePopup.h"
#include "Constant/Defination.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/PluginManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/DownloadImageManager.h"
#include "Util/UtilFunction.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/ChangeNamePopup.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Configs.h"
#include "Constant/ResultCodeConstant.h"
#include "Helper/Helper4Sprite.h"
#include "Custom/Common/LabelAutoSize.h"

USING_NS_CC;
using namespace std;
using namespace GameSlot;

#define POPUP_AVATAR_SIZE 280
bool ProfilePopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}
	// preload img profile
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_PROFILE);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_PROFILE_POPUP_BACKGROUND);
	bg->setPosition(0, visibleSize.height / 2);
	this->addChild(bg);

	this->firstPosX = origin.x - bg->getContentSize().width / 2 - 100;
	this->endPosX = origin.x + bg->getContentSize().width / 2 - 50;

	auto avatarPos = bg->getPosition() + Vec2(14, 190);

	//MAKE AVATAR
	// create the sprite, which should be clipped
	this->oAvatar = Helper4Sprite::createOptimizeSprite(PNG_HEADER_AVATAR_ICON);
	this->oAvatar->setContentSize(Size(POPUP_AVATAR_SIZE, POPUP_AVATAR_SIZE));

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && CALL_NATIVE_CROP_AVATAR)
	this->oAvatar->setPosition(avatarPos);
	this->addChild(oAvatar);
#else
	auto circleMask = UtilFunction::createCircleMask(POPUP_AVATAR_SIZE / 2.0f);
	circleMask->addChild(this->oAvatar);
	circleMask->setPosition(avatarPos);
	// add the clipping node to the main node
	this->addChild(circleMask);
#endif

	this->oVipSymbol = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_CROWN_SLOT_ICON);
	this->oVipSymbol->setPosition(avatarPos + Vec2(-POPUP_AVATAR_SIZE * 0.75f, POPUP_AVATAR_SIZE) * 0.49f);
	this->addChild(this->oVipSymbol);

	this->oFacebookSymbol = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_PROFILE_FACEBOOK_ICON);
	this->oFacebookSymbol->setPosition(avatarPos - Vec2(POPUP_AVATAR_SIZE * 0.75f, POPUP_AVATAR_SIZE) * 0.4f);
	this->oFacebookSymbol->setScale(1.2f);
	this->addChild(this->oFacebookSymbol);

	this->oName = LabelAutoSize::createWithTTF("Anonymous", FONT_PassionOne_Regular, 60, Size::ZERO, TextHAlignment::CENTER);
	((LabelAutoSize*)this->oName)->setAutoFitType(LabelAutoFitType::TrimString);
	((LabelAutoSize*)this->oName)->setTextAreaSize(Size(bg->getContentSize().width * 0.6f, 0));
	this->oName->setPosition(avatarPos - Vec2(0, 200));
	this->addChild(this->oName);

	auto oStar = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_HEADER_START_LEVEL_ICON);
	oStar->setScale(0.6f);

	this->oLevel = cocos2d::ui::RichText::create();
	this->oLevel->setPosition(avatarPos - Vec2(0, 240));
	this->oLevel->pushBackElement(ui::RichElementCustomNode::create(0, Color3B::WHITE, 0xFF, oStar));
	this->oLevel->pushBackElement(ui::RichElementText::create(1, Color3B(235, 118, 228), 0xFF, "1", FONT_PassionOne_Regular, 40));
	this->addChild(this->oLevel);

	this->oExp = Label::createWithTTF("0 XP\nto level up", FONT_PassionOne_Regular, 40, Size::ZERO, TextHAlignment::CENTER);
	this->oExp->setTextColor(Color4B(235, 118, 228, 255));
	this->oExp->setPosition(avatarPos - Vec2(0, 350));
	this->addChild(this->oExp);

	this->oWin = Label::createWithTTF("WIN: 0%", FONT_PassionOne_Bold, 45, Size::ZERO, TextHAlignment::CENTER);
	this->oWin->setPosition(avatarPos - Vec2(0, 485));
	this->addChild(this->oWin);

	this->oNameBtn = CSpriteButton::createButtonWithSpriteFrameName(PNG_FRAME_PROFILE_BTN_NAME, nullptr, CC_CALLBACK_0(ProfilePopup::onChangeNameTouched, this));
	this->oNameBtn->setScaleEvent(0.9f, 1.0f);
	this->oNameBtn->setPosition(this->oName->getPosition() + Vec2(200, 0));
	this->addChild(oNameBtn);

	this->oAvatarBtn = CSpriteButton::createButtonWithSpriteFrameName(PNG_FRAME_PROFILE_BTN_AVATAR, nullptr, CC_CALLBACK_0(ProfilePopup::onChangeAvatarTouched, this));
	this->oAvatarBtn->setScaleEvent(0.9f, 1.0f);
	this->oAvatarBtn->setPosition(avatarPos - oAvatar->getContentSize() / 2 * 0.75f);
	this->addChild(oAvatarBtn);

	auto closeBtn = this->createCloseButton();
	closeBtn->setPosition(Vec2(
		bg->getPositionX() + bg->getContentSize().width / 2 - 40,
		bg->getPositionY() + bg->getContentSize().height / 2 - 40
	));
	this->addChild(closeBtn);

	this->imagePickerResult = new ImagePickerResult(this);

	return true;
}

void ProfilePopup::prepareAndShow(cocos2d::Node * parent)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	this->setPosition(this->firstPosX, 0);

	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(parent);
	PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp(
		[this](bool isSuccess, LevelUpInfo* levelUpInfo) {
			this->reloadInfo(isSuccess, InfoManager::getInstance()->getUserInfo());
		}
	);
	//InfoManager::getInstance()->reloadUserInfo(CC_CALLBACK_2(ProfilePopup::reloadInfo, this));

	this->oParent = parent;
}

void ProfilePopup::onChangeNameTouched()
{
	PopupManager::getInstance()->getChangeNamePopup()->prepareAndShow(this->oParent);
}

void ProfilePopup::onChangeAvatarTouched()
{
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->oParent);
	//ImagePicker::getInstance()->pickImage(this->imagePickerResult);
	PluginManager::getInstance()->getImagePickerController()->pickImage(this->imagePickerResult);
}

void ProfilePopup::reloadInfo(bool isSuccess, UserInfo * userInfo)
{
	this->updateName(userInfo->name);

	this->oVipSymbol->setVisible(true);

	std::string levelAndVipTypeString = "";
	auto levelVipUser = userInfo->vip;

	switch (levelVipUser) {
	case USER_TYPE_VIP::SILVER:
		levelAndVipTypeString += ": Silver";
		break;
	case USER_TYPE_VIP::GOLD:
		levelAndVipTypeString += ": Gold";
		break;
	case USER_TYPE_VIP::PINK_DIAMOND:
		levelAndVipTypeString += ": Pink Diamond";
		break;
	case USER_TYPE_VIP::BLUE_SAPPHIRE:
		levelAndVipTypeString += ": Blue Sapphire";
		break;
	case USER_TYPE_VIP::GREEN_EMERALD:
		levelAndVipTypeString += ": Green Emerald";
		break;
	default:
		this->oVipSymbol->setVisible(false);
		break;
	}

	this->oNameBtn->setVisible(false);
	this->oAvatarBtn->setVisible(false);
	this->oFacebookSymbol->setVisible(false);

	switch (userInfo->role)
	{
	case USER_ROLE::GUEST:
		break;
	case USER_ROLE::PLAYPALACE:
		this->oNameBtn->setVisible(true);
		this->oAvatarBtn->setVisible(true);
		break;
	case USER_ROLE::FACEBOOK:
		this->oFacebookSymbol->setVisible(true);
		break;
	default:
		break;
	}

	this->oLevel->removeElement(1);
	this->oLevel->pushBackElement(ui::RichElementText::create(1, Color3B(235, 118, 228), 0xFF, ToString(userInfo->level + 1) + levelAndVipTypeString, FONT_PassionOne_Regular, 40));

	UtilFunction::setLabelFontByLanguage(this->oExp);
	this->oExp->setString(UtilFunction::FormatWithCommas(userInfo->remainingExp) + Language(nullptr, LanguageConstant::POPUP_PROFILE_TO_LEVEL_UP_LABLE));
	UtilFunction::setLabelFontByLanguage(this->oWin);
	this->oWin->setString(Language(nullptr, LanguageConstant::POPUP_PROFILE_SLOT_WIN) + ToString((int)userInfo->slot.percentWin) + "%");

	DownloadImageManager::getInstance()->loadImageFromCacheOrDownload(
		userInfo->getAvatarURL(),
		[this](cocos2d::Texture2D* texture)
	{
		this->updateAvatar(texture);

		BasePopup::showWithQueue(this->oParent);

		PopupManager::getInstance()->getLoadingAnimation()->hide();
	}
	);
}

void ProfilePopup::updateAvatar(cocos2d::Texture2D * texture)
{
	this->oAvatar->setTexture(texture);
}

void ProfilePopup::updateName(const std::string & newName)
{
	UtilFunction::detectFontAndSetStringForLabel(this->oName, FONT_PassionOne_Regular, newName);
}

std::vector<cocos2d::Action*> ProfilePopup::animationHidePopup()
{
	//return BasePopup::animationHidePopup();
	//Animation hide popup
	auto ease_in_back = EaseBackIn::create(MoveTo::create(0.5f, Vec2(this->firstPosX, 0)));

	std::vector<Action*> actionlist;
	actionlist.push_back(ease_in_back);
	return actionlist;
}

std::vector<cocos2d::Action*> ProfilePopup::animationShowPopup()
{
	//return BasePopup::animationShowPopup();
	this->setOpacity(255);
	this->setScale(1.0f);
	this->setVisible(true);
	//Animation show popup
	auto ease_out_back = EaseBackOut::create(MoveTo::create(0.5f, Vec2(this->endPosX, 0)));

	std::vector<Action*> actionlist;
	actionlist.push_back(ease_out_back);
	return actionlist;
}

ImagePickerResult::ImagePickerResult(ProfilePopup* profile): ImagePickerDelegate(),
profile(profile)
{

}

void ImagePickerResult::didFinishPickingWithResult(cocos2d::Image* image, int orientation)
{
	if (image) {
		log("Orientation: %i", orientation);

		auto newImg = image;

		auto fileName = newImg->getFilePath();

		bool isTempImage = false;

		//if this image's dimension invalid -> resize image -> save it -> read data -> delete image 
		//we need file's data to send to server
		if (image->getWidth() != LobbyConstant::AVATAR_SIZE ||
			image->getHeight() != LobbyConstant::AVATAR_SIZE) {

			auto path = FileUtils::getInstance()->getWritablePath();
			fileName = path + "avatar_temp.png";

			newImg = UtilFunction::fixAvatarImage(image, LobbyConstant::AVATAR_SIZE, orientation);

			newImg->saveToFile(fileName);

//            int newWidth = newImg->getWidth();
//            int newHeight = newImg->getHeight();
            
			isTempImage = true;
		}

		Data data = FileUtils::getInstance()->getDataFromFile(fileName);

		if (isTempImage) {
			FileUtils::getInstance()->removeFile(fileName);
		}

		NetworkManager::getInstance()->uploadAvatar(
			(const char*)data.getBytes(), data.getSize(),
			[this, newImg](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString) {
			if (coreResultCode == RESULT_CODE_VALID) {
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->profile->getParent(), 
					LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "title") ,
					LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "success"), Language(nullptr, LanguageConstant::OK), "");
				InfoManager::getInstance()->reloadUserInfo([this, newImg](bool isSuccess, UserInfo* userInfo) {
					auto tex = TextureCache::getInstance()->addImage(newImg, userInfo->getAvatarURL());

					this->profile->updateAvatar(tex);
					PopupManager::getInstance()->getHeaderLobbyLayout()->updateAvatar(tex);
					PopupManager::getInstance()->getLoadingAnimation()->hide();
				});
			}
			else {
				newImg->release();

				PopupManager::getInstance()->getLoadingAnimation()->hide();
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->profile->getParent(),
					LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "title"),
					LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "fail"), Language(nullptr, LanguageConstant::OK), "");
			}
		},
			[this, newImg](std::string result) {
			newImg->release();

			PopupManager::getInstance()->getLoadingAnimation()->hide();
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->profile->getParent(),
				LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "title"),
				LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "fail"), Language(nullptr, LanguageConstant::OK), "");
		}, [this, newImg](std::string result) {
			newImg->release();

			PopupManager::getInstance()->getLoadingAnimation()->hide();
			PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->profile->getParent(),
				LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "title"),
				LanguageText(nullptr, LanguageConstant::POPUP_PROFILE_CHANGE_AVATAR, "fail"), Language(nullptr, LanguageConstant::OK), "");
		});
	}
	else {
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	}
}
