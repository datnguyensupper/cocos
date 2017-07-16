#include "CellInbox.h"
#include "Configs.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Constant/LobbyConstant.h"
#include "Constant/Defination.h"
#include "Constant/LanguageConstant.h"
#include "Constant/ResultCodeConstant.h"
#include "Util/UtilFunction.h"
#include "Manager/LanguageManager.h"
#include "Manager/DownloadImageManager.h"
#include "Manager/InfoManager.h"
#include "Helper/Helper4Sprite.h"

#define ADMIN_ICON "admin_icon"
#define INBOX_VOUCHER_ICON "inbox_voucher_icon"
#define COMMONER_TREASURE_CHEST_ICON "commoner_treasure_chest_icon"
#define NOBLE_TREASURE_CHEST_ICON "noble_treasure_chest_icon"
#define KING_TREASURE_CHEST_ICON "king_treasure_chest_icon"
#define RADIUS_CIRCLE_AVATAR 50

USING_NS_CC;
CellInbox * CellInbox::create(GiftInfo *_giftInfo, cocos2d::Size _cellSize)
{
	CellInbox * ret = new (std::nothrow) CellInbox();
	ret->giftInfo = _giftInfo;
	ret->cellSize = _cellSize;
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}

bool CellInbox::init()
{
	if (!ButtonAdjustClikableAreaSize::init()) {
		return false;
	}

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(PLIST_INBOX_ICONS);
	//INIT AVATAR ICON
	avatarIconSprite = Sprite::createWithSpriteFrameName(ADMIN_ICON);
	avatarIconSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->addChild(avatarIconSprite);

	// create the sprite, which should be clipped
	avatarUserSprite = Helper4Sprite::createOptimizeSprite(PNG_HEADER_AVATAR_ICON);
	avatarUserSprite->setScale(RADIUS_CIRCLE_AVATAR  * 2.0f / avatarUserSprite->getContentSize().width);

	auto avatarPos = Vec2(
		15 + RADIUS_CIRCLE_AVATAR / 2.0f,
		avatarUserSprite->getContentSize().height * avatarUserSprite->getScaleY() / 2
	);
	//INIT AVATAR USER
#if (CALL_NATIVE_CROP_AVATAR)
	//avatarUserSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	avatarUserSprite->setPosition(avatarPos);
	this->addChild(avatarUserSprite);
#else
	avatarUserClippingNode = UtilFunction::createCircleMask(RADIUS_CIRCLE_AVATAR);
	avatarUserClippingNode->setCascadeOpacityEnabled(true);
	avatarUserClippingNode->addChild(avatarUserSprite);
	avatarUserClippingNode->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	avatarUserClippingNode->setPosition(avatarPos);
	this->addChild(avatarUserClippingNode);
#endif


	//INIT MESSAGE
	messageLabel = LabelAutoSize::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 30),
		"DEMO"
	);
	messageLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	messageLabel->setVerticalAlignment(TextVAlignment::CENTER);
	messageLabel->setHorizontalAlignment(TextHAlignment::LEFT);
	messageLabel->setPosition(Vec2(
		avatarIconSprite->getPosition().x + avatarIconSprite->getContentSize().width + 35,
		avatarIconSprite->getPosition().y - 5
	));
	messageLabel->setDimensions(this->cellSize.width - avatarUserSprite->getContentSize().width * avatarUserSprite->getScaleX() - 100, this->cellSize.height);
	((LabelAutoSize*)messageLabel)->setTextAreaSize(Size(
		this->cellSize.width - avatarIconSprite->getContentSize().width - 100,
		this->cellSize.height
	));
	this->addChild(messageLabel);

	this->updateCell(this->giftInfo);
	return true;
}

void CellInbox::updateCell(GiftInfo * _giftInfo)
{
	this->giftInfo = _giftInfo;
	if (!this->giftInfo) {
		return;
	}
	std::string coinRerwardWithCommaFormat = UtilFunction::FormatWithCommas(this->giftInfo->coinReward);
	auto languageManager = LanguageManager::getInstance();
	std::string spriteFrame = ADMIN_ICON;
	std::string message = this->giftInfo->getMessage();
	bool isUserAvatar = false;
    float scaleRatioForAvatarIcon = 1;
    Vec2 translateForAvatarIcon = Vec2::ZERO;
	UtilFunction::setLabelFontByLanguage(messageLabel);
	switch (static_cast<LobbyConstant::GiftType>(this->giftInfo->type))
	{
        case LobbyConstant::GIFT_SECRET_KEY_FROM_USER:
            scaleRatioForAvatarIcon = 1.3;
            translateForAvatarIcon = Vec2(-17,0);
		spriteFrame = ADMIN_ICON;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_REQUESTKEY);
		break;
        case LobbyConstant::GIFT_FROM_SYSTEM:
            scaleRatioForAvatarIcon = 1.3;
            translateForAvatarIcon = Vec2(-17,0);
		spriteFrame = ADMIN_ICON;
		if (this->giftInfo->message.empty()) {
			message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_SYSTEMGIFT, "text1") + coinRerwardWithCommaFormat + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_SYSTEMGIFT, "text2");
		}
		break;
	case LobbyConstant::GIFT_FOR_PROMOTION_001:
	case LobbyConstant::GIFT_FOR_PROMOTION_002:
        case LobbyConstant::GIFT_FOR_PROMOTION_003:
            scaleRatioForAvatarIcon = 1.3;
            translateForAvatarIcon = Vec2(-17,0);
		spriteFrame = ADMIN_ICON;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_PROMOTE, "text1") + coinRerwardWithCommaFormat + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_PROMOTE, "text2");
		break;
	case LobbyConstant::GIFT_FOR_PROMOTION_VIP_UP:
        scaleRatioForAvatarIcon = 1.3;
        translateForAvatarIcon = Vec2(-17,0);
		spriteFrame = ADMIN_ICON;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_VIP, "text1") + coinRerwardWithCommaFormat + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_VIP, "text2");
		break;
        case LobbyConstant::GIFT_FROM_BONUS_FOR_TOP_PLAYER:
            scaleRatioForAvatarIcon = 1.3;
            translateForAvatarIcon = Vec2(-17,0);
		spriteFrame = ADMIN_ICON;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_TOP_PLAYER_GIFT, "text1") + coinRerwardWithCommaFormat + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_TOP_PLAYER_GIFT, "text2");
		break;
	case LobbyConstant::GIFT_FROM_PLAY_WITH_FRIEND_WITH_BENEFIT:
		spriteFrame = INBOX_VOUCHER_ICON;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_FRIEND_BENEFIT, "text1") + coinRerwardWithCommaFormat + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_FRIEND_BENEFIT, "text2");
		break;
	case LobbyConstant::GIFT_FROM_REFERENCE_CODE:
		spriteFrame = INBOX_VOUCHER_ICON;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_REFERENCE_CODE, "text1") + " " + coinRerwardWithCommaFormat+ languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_REFERENCE_CODE, "text2");
		break;
	case LobbyConstant::GIFT_FROM_USER:
	case LobbyConstant::GIFT_FREE_FROM_USER:
		isUserAvatar = true;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_GIFT, "text1") + coinRerwardWithCommaFormat + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_GIFT, "text2");
		break;
	case LobbyConstant::GIFT_TYPE_LUCKY_BOX_1:
		spriteFrame = COMMONER_TREASURE_CHEST_ICON;
		break;
	case LobbyConstant::GIFT_TYPE_LUCKY_BOX_2:
		spriteFrame = NOBLE_TREASURE_CHEST_ICON;
		break;
	case LobbyConstant::GIFT_TYPE_LUCKY_BOX_3:
		spriteFrame = KING_TREASURE_CHEST_ICON;
		break;
	case LobbyConstant::GIFT_TYPE_FREE_MAGIC_ITEM_WATCHING_VIDEO: {
		std::string numberOfConsecutiveVideos = ToString(InfoManager::getInstance()->getMagicItemConfig()->minNumberOfConsecutiveVideoViewToReceiveMagicItemReward);
		spriteFrame = INBOX_VOUCHER_ICON;
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_FREE_MAGIC_ITEM_WATCHING_VIDEO, "text1") + numberOfConsecutiveVideos + languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_FREE_MAGIC_ITEM_WATCHING_VIDEO, "text2");
		break;
	}
	default:
		message = languageManager->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_MESSAGE_DEFAULT_GIFT);
		spriteFrame = INBOX_VOUCHER_ICON;
		break;
	}
	UtilFunction::detectFontAndSetStringForLabel(messageLabel,
		FONT_PassionOne_Regular, message);
	if (isUserAvatar)
	{
#if (CALL_NATIVE_CROP_AVATAR)
		this->avatarUserSprite->setVisible(true);
#else
		this->avatarUserClippingNode->setVisible(true);
#endif
		this->avatarUserSprite->setTexture(TextureCache::getInstance()->getTextureForKey(PNG_HEADER_AVATAR_ICON));
		this->avatarIconSprite->setVisible(false);

		std::string facebookUID = "";
		auto friendList = InfoManager::getInstance()->getFacebookFriendInfo()->getFriendList();
		for (auto friendInfo : friendList) {
			if (friendInfo.second->id == this->giftInfo->fromUserId) {
				facebookUID = friendInfo.second->facebookUID;
			}
		}
		if (facebookUID.empty()) {
			return;
		}

		std::string urlAvatar = UtilFunction::getAvatarUrl(
			USER_ROLE::FACEBOOK,
			facebookUID,
			""
		);

		DownloadImageManager::getInstance()->loadImageFromCacheOrDownload(
		urlAvatar,
		[this](cocos2d::Texture2D* texture)
		{
			this->avatarUserSprite->setTexture(texture);
		}
		);
	}
	else
	{
		this->avatarIconSprite->setVisible(true);
        this->avatarIconSprite->setScale(scaleRatioForAvatarIcon, scaleRatioForAvatarIcon);
        this->avatarIconSprite->setPosition(translateForAvatarIcon);
        
#if (CALL_NATIVE_CROP_AVATAR)
		this->avatarUserSprite->setVisible(false);
#else
		this->avatarUserClippingNode->setVisible(false);
#endif
		this->avatarIconSprite->initWithSpriteFrameName(spriteFrame);
		avatarIconSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	}
}
