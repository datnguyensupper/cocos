#include "CellLeaderboard.h"
#include "Util/UtilFunction.h"
#include "Constant/Defination.h"
#include "Configs.h"
#include "Manager/NetworkManager.h"
#include "Manager/DownloadImageManager.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;
#define RADIUS_CIRCLE_AVATAR 50
#define AVATAR_TAG 1
#define FACEBOOK_HEADER_URL "https://graph.facebook.com/"
#define FACEBOOK_TAIL_URL "/picture?type=normal&width=100&height=100"
CellLeaderboard * CellLeaderboard::create(LeaderboardTab _leaderboardTab, LeaderboardInfo *_leaderboardInfo, cocos2d::Size _cellSize)
{
	CellLeaderboard * ret = new (std::nothrow) CellLeaderboard();
	ret->leaderboardInfo = _leaderboardInfo;
	ret->cellSize = _cellSize;
	ret->leaderboardTab = _leaderboardTab;
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

bool CellLeaderboard::init()
{
	if (!ui::Widget::init()) {
		return false;
	}

	//INIT AVATAR
	// create the sprite, which should be clipped
	this->avatarSprite = Helper4Sprite::createOptimizeSprite(PNG_HEADER_AVATAR_ICON);
	this->avatarSprite->setScale(RADIUS_CIRCLE_AVATAR  * 2.0f / avatarSprite->getContentSize().width);
	auto avatarPos = Vec2(
		30,
		this->avatarSprite->getContentSize().height * this->avatarSprite->getScaleY() / 2
	);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && CALL_NATIVE_CROP_AVATAR)
	//this->avatarSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->avatarSprite->setScale(this->avatarSprite->getScale() * Configs::SCALE_RESOUCE_VALUE);
	this->avatarSprite->setPosition(avatarPos);
	this->addChild(this->avatarSprite);
#else
	auto avatar = UtilFunction::createCircleMask(RADIUS_CIRCLE_AVATAR);
	avatar->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	avatar->setCascadeOpacityEnabled(true);
	avatar->addChild(this->avatarSprite, 0, AVATAR_TAG);
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
		avatarPos.x + 80,
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
		nameLabel->getPosition().x + 330,
		nameLabel->getPosition().y
	);
	this->addChild(levelLabel);

	//COIN OR TOTAL BET
	this->coinOrTotalBetLabel = Label::createWithTTF(
		TTFConfig(FONT_PassionOne_Regular, 30),
		""
	);
	this->coinOrTotalBetLabel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	this->coinOrTotalBetLabel->setAlignment(TextHAlignment::LEFT, TextVAlignment::CENTER);
	this->coinOrTotalBetLabel->setPosition(
		levelLabel->getPosition().x + 150,
		levelLabel->getPosition().y
	);
	this->addChild(this->coinOrTotalBetLabel);

	this->updateCell(this->leaderboardInfo);
	return true;
}

void CellLeaderboard::updateCell(LeaderboardInfo * _leaderboardInfo)
{
	this->leaderboardInfo = _leaderboardInfo;
	this->avatarSprite->setTexture(TextureCache::getInstance()->getTextureForKey(PNG_HEADER_AVATAR_ICON));
	//AVATAR
	std::string urlAvatar = UtilFunction::getAvatarUrl(
		this->leaderboardInfo->facebookUID.empty() ? USER_ROLE::PLAYPALACE : USER_ROLE::FACEBOOK,
		this->leaderboardInfo->facebookUID,
		this->leaderboardInfo->urlFullAvatar
	);
	DownloadImageManager::getInstance()->loadImageFromCacheOrDownload(
	urlAvatar,
	[this, urlAvatar](cocos2d::Texture2D* texture)
	{
		if (!this
			|| !this->leaderboardInfo) 
		{
			return;
		}
		if (!this->leaderboardInfo->facebookUID.empty()
			&& urlAvatar != FACEBOOK_HEADER_URL + this->leaderboardInfo->facebookUID + FACEBOOK_TAIL_URL)
		{
			return;
		}
		else if (this->leaderboardInfo->facebookUID.empty()
			&& urlAvatar != this->leaderboardInfo->urlFullAvatar)
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
		UtilFunction::trimStringAndAdd3Dots(leaderboardInfo->name, 12));
	//LEVEL
	this->levelLabel->setString("Lv." + ToString(this->leaderboardInfo->level + 1));

	//COIN OR TOTALBET
	this->coinOrTotalBetLabel->setString(this->leaderboardInfo->coin != 0 ? UtilFunction::formatCoinNumber(this->leaderboardInfo->coin) : UtilFunction::formatCoinNumber(this->leaderboardInfo->slotTotalBet));

	//STAR DOM
	switch (leaderboardInfo->rank)
	{
	case 0:
		this->stardom->initWithSpriteFrameName(PNG_FRAME_GOLD_STARDOM);
		this->stardom->setVisible(true);
		break;
	case 1:
		this->stardom->initWithSpriteFrameName(PNG_FRAME_SLIVER_STARDOM);
		this->stardom->setVisible(true);
		break;
	case 2:
		this->stardom->initWithSpriteFrameName(PNG_FRAME_BRONZE_STARDOM);
		this->stardom->setVisible(true);
		break;
	default:
		this->stardom->setVisible(false);
		break;
	}
}
