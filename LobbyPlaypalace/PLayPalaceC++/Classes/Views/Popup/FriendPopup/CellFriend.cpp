#include "CellFriend.h"
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

#define RADIUS_CIRCLE_AVATAR 50

USING_NS_CC;
CellFriend * CellFriend::create(FriendFBInfo *_friendFBInfo, cocos2d::Size _cellSize)
{
	CellFriend * ret = new (std::nothrow) CellFriend();
	ret->friendFBInfo = _friendFBInfo;
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

bool CellFriend::init()
{
	if (!ui::Widget::init()) {
		return false;
	}

	// create the sprite, which should be clipped
	this->avatarSprite = Helper4Sprite::createOptimizeSprite(PNG_HEADER_AVATAR_ICON);
	this->avatarSprite->setScale(RADIUS_CIRCLE_AVATAR  * 2.0f / avatarSprite->getContentSize().width);

	auto avatarPos = Vec2(
		30,
		this->avatarSprite->getContentSize().height * this->avatarSprite->getScaleY() / 2
	);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && CALL_NATIVE_CROP_AVATAR)
	//this->avatarSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->avatarSprite->setScale(avatarSprite->getScale() * Configs::SCALE_RESOUCE_VALUE);
	this->avatarSprite->setPosition(avatarPos);
	this->addChild(avatarSprite);
#else
	//INIT AVATAR
	auto avatar = UtilFunction::createCircleMask(RADIUS_CIRCLE_AVATAR);
	avatar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	avatar->setCascadeOpacityEnabled(true);
	avatar->addChild(this->avatarSprite);
	avatar->setPosition(avatarPos);
	this->addChild(avatar);
#endif
	this->stardom = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_GOLD_STARDOM);
	this->stardom->setScale(0.8f);
	this->stardom->setPosition(avatar->getPosition() + Vec2(-RADIUS_CIRCLE_AVATAR + 13, RADIUS_CIRCLE_AVATAR - 2));
	this->stardom->setVisible(false);
	this->addChild(this->stardom);

	//NAME
	this->nameLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 36),
		""
	);
	this->nameLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->nameLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->nameLabel->setPosition(
		avatarPos.x + 100,
		avatarPos.y - 20
	);
	this->addChild(this->nameLabel);

	//LEVEL
	this->levelLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 30),
		""
	);
	this->levelLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->levelLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->levelLabel->setPosition(
		nameLabel->getPosition().x + 320,
		nameLabel->getPosition().y
	);
	this->addChild(levelLabel);

	//TOGGLE
	this->toggleButton = ToggleButton::create(
		PNG_FRIEND_TOGGLE_OFF,
		PNG_FRIEND_TOGGLE_ON,
		PNG_FRIEND_TOGGLE_OFF,
		PNG_FRIEND_TOGGLE_ON
	);
	this->toggleButton->setPosition(Vec2(
		this->levelLabel->getPosition().x + 190,
		this->levelLabel->getPosition().y + 20));
	this->toggleButton->addTouchEventListener([this](cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != cocos2d::ui::Widget::TouchEventType::BEGAN) {
			return;
		}
		ToggleButton* toggleButton = (ToggleButton*)sender;
		this->friendFBInfo->_isSelected = toggleButton->isToggle();
	});
	this->addChild(toggleButton);

	this->updateCell(this->friendFBInfo);
	return true;
}

void CellFriend::updateCell(FriendFBInfo * _friendFBInfo)
{
	if (_friendFBInfo == nullptr) {
		return;
	}
	this->friendFBInfo = _friendFBInfo;
	this->avatarSprite->setTexture(TextureCache::getInstance()->getTextureForKey(PNG_HEADER_AVATAR_ICON));
	//AVATAR
	DownloadImageManager::getInstance()->loadImageFromCacheOrDownload(
		_friendFBInfo->_avatarURL,
		[this, _friendFBInfo](cocos2d::Texture2D* texture)
	{
		if (!this
			|| !this->friendFBInfo
			|| this->friendFBInfo != _friendFBInfo)
		{
			return;
		}
		if (texture
			&& this->avatarSprite) {
			this->avatarSprite->setTexture(texture);
		}
	}
	);

	//NAME
	
	UtilFunction::detectFontAndSetStringForLabel(this->nameLabel, 
		FONT_PassionOne_Regular, 
		UtilFunction::trimStringAndAdd3Dots(_friendFBInfo->_name, 12));

	if (_friendFBInfo->_isPPUser)
	{
		this->nameLabel->setTextColor(Color4B::WHITE);
		this->levelLabel->setString("Lv." + _friendFBInfo->_levelAsString);
	}
	else
	{
		this->nameLabel->setTextColor(Color4B(83, 72, 86, 255));
		this->levelLabel->setString("");
	}

	//TOGGLE
	this->toggleButton->setToggle(_friendFBInfo->_isSelected);
	this->updateToggleVisible();

	//STARDOM
	this->stardom->setVisible(_friendFBInfo->_isPPUser && InfoManager::getInstance()->getFacebookFriendInfo()->getFriendList()[_friendFBInfo->_facebookUID]->vip > 0);
}

void CellFriend::updateToggleVisible()
{
	if (this->friendFBInfo->_isPPUser)
	{
		auto allowSendGift
			= InfoManager::getInstance()->getFacebookFriendInfo()->getFriendList()[this->friendFBInfo->_facebookUID]->allowSendFreeGift;
		this->toggleButton->setVisible(!allowSendGift);
	}
	else
	{
		this->toggleButton->setVisible(true);
	}
}
