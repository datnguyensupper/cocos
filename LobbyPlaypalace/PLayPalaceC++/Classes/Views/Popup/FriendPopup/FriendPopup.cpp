#include "FriendPopup.h"
#include "Custom/Common/ReuseItemListView_Vertical.h"
#include "Constant/Defination.h"
#include "Constant/LanguageConstant.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LobbyConstant.h"
#include "Configs.h"
#include "Helper/Helper4ParseJSON.h"
#include "Util/UtilFunction.h"
#include "Manager/LanguageManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"
#include "Manager/InfoManager.h"
#include "Manager/PluginManager.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LuckyBoxPopup.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Views/Lobby/bottom/BottomLobbyLayout.h"
#include "Helper/Helper4Sprite.h"

USING_NS_CC;

#define INBOX_TAB_SCROLL_VIEW_TAG 1
#define INBOX_TAB_EMPTY_GIFT_LABEL_TAG 2
#define FRIEND_TAB_SCROLL_VIEW_TAG 2
#define LEADERBOARD_TAB_SCROLL_VIEW_TAG 3

#define CELL_X_OFFSET 50
#define CELL_Y_OFFSET 50
#define CELL_HEIGHT 120
#define CELL_SPACING 5

#define NUMBER_TEAMPLATE_CELL 7

#define COLOR_TURN_ON_LEADERBOAR Color3B::WHITE
#define COLOR_TURN_OFF_LEADERBOAR Color3B(102, 102, 102)
#define COLOR_TURN_ON_LABEL_LEADERBOAR Color3B(234, 202, 242)
#define COLOR_TURN_OFF_LABEL_LEADERBOAR Color3B(102, 102, 102)
void FriendPopup::initInboxTab()
{
	this->inboxTab = Node::create();
	this->inboxTab->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->inboxTab->setCascadeOpacityEnabled(true);
	this->inboxTab->setPosition(
		this->inboxButton.btn->getPosition().x + this->inboxButton.btn->getContentSize().width / 2.0f * this->inboxButton.btn->getScaleX() + 25,
		this->inboxButton.btn->getPosition().y + this->inboxButton.btn->getContentSize().height / 2.0f * this->inboxButton.btn->getScaleY()
	);

	//FRAME FOR CELLS
	auto bg = Helper4Sprite::createOptimizeSprite(PNG_FRIEND_POPUP_FRAME_FOR_CELLS);
	bg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg->setContentSize(
		Size(
			bg->getContentSize().width,
			bg->getContentSize().height - 80
		)
	);
	this->inboxTab->addChild(bg);

	//LIST CELL LIST VIEW 
	auto inboxTabScrollView = ReuseItemListView_Vertical::create();
	//inboxTabScrollView->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	inboxTabScrollView->setPosition(Vec2(
		bg->getPosition().x,
		bg->getPosition().y - bg->getContentSize().height * bg->getScaleY() + 15
	));
	inboxTabScrollView->setContentSize(Size(
		bg->getContentSize().width * bg->getScaleX(),
		bg->getContentSize().height * bg->getScaleY() - 30));
	inboxTabScrollView->setScrollBarEnabled(false);
	inboxTabScrollView->setCascadeOpacityEnabled(true);
	inboxTabScrollView->setUpdateItemCallback(CC_CALLBACK_2(FriendPopup::updateInboxCell, this));
	this->inboxTab->addChild(inboxTabScrollView, 0, INBOX_TAB_SCROLL_VIEW_TAG);
	
	//ACCEPT ALL GIFT BUTTON
	acceptAllButton = this->createGreenButton(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_INBOX_BUTTON_ACCEPT_ALL), 55);
	acceptAllButton->setScale(1920.0f / 1600);
	acceptAllButton->setCascadeOpacityEnabled(true);
	acceptAllButton->setPosition(Vec2(
		530,
		- (inboxTabScrollView->getContentSize().height + 110)
	));
	acceptAllButton->addTouchEventListener(CC_CALLBACK_2(FriendPopup::onAcceptGiftAllTouched, this));
	this->inboxTab->addChild(acceptAllButton);

	auto currentFontname = UtilFunction::getFontNameFromLanguage();
	//EMPTY LABEL NOTI
	auto emptyGiftLabel = Label::createWithTTF(TTFConfig(currentFontname, 50),"");
	emptyGiftLabel->setString(LanguageManager::getInstance()->getStringForKeys(emptyGiftLabel,LanguageConstant::POPUP_GIFT_INBOX_EMPTY));
	emptyGiftLabel->setPosition(Vec2(
		bg->getContentSize().width / 2,
		- 50
	));
	this->inboxTab->addChild(emptyGiftLabel, 0, INBOX_TAB_EMPTY_GIFT_LABEL_TAG);

	this->addChild(this->inboxTab);
}
void FriendPopup::initFriendTab()
{
	this->friendTab = Node::create();
	this->friendTab->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->friendTab->setCascadeOpacityEnabled(true);
	this->friendTab->setPosition(
		this->inboxTab->getPosition()
	);

	//FRAME FOR CELLS
	auto bg = Helper4Sprite::createOptimizeSprite(PNG_FRIEND_POPUP_FRAME_FOR_CELLS);
	bg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	bg->setContentSize(
		Size(
			bg->getContentSize().width,
			bg->getContentSize().height - 80
		)
	);
	this->friendTab->addChild(bg);

	//LIST CELL LIST VIEW 
	auto friendTabScrollView = ReuseItemListView_Vertical::create();
	//inboxTabScrollView->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	friendTabScrollView->setPosition(Vec2(
		bg->getPosition().x,
		bg->getPosition().y - bg->getContentSize().height * bg->getScaleY() + 15
	));
	friendTabScrollView->setContentSize(Size(
		bg->getContentSize().width * bg->getScaleX(),
		bg->getContentSize().height * bg->getScaleY() - 30));
	friendTabScrollView->setScrollBarEnabled(false);
	friendTabScrollView->setCascadeOpacityEnabled(true);
	friendTabScrollView->setUpdateItemCallback(CC_CALLBACK_2(FriendPopup::updateFriendCell, this));
	this->friendTab->addChild(friendTabScrollView, 0, FRIEND_TAB_SCROLL_VIEW_TAG);

	//SEND GIFT BUTTON
	sendGiftButton = this->createGreenButton(
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_INVITE_BTN_SENDGIFT),
		55);
	sendGiftButton->setScale(1);
	sendGiftButton->setCascadeOpacityEnabled(true);
	sendGiftButton->setPosition(Vec2(
		550,
		-(friendTabScrollView->getContentSize().height + 130)
	));
	sendGiftButton->addTouchEventListener(CC_CALLBACK_2(FriendPopup::onSendGiftTouched, this));
	this->friendTab->addChild(sendGiftButton);

	//INVITE BUTTON
	inviteButton = this->createPurpleButton(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_INVITE_BTN_INVITE),55);
	inviteButton->setScale(1);
	inviteButton->setCascadeOpacityEnabled(true);
	inviteButton->setPosition(Vec2(
		sendGiftButton->getPositionX() - sendGiftButton->getContentSize().width - 20,
		sendGiftButton->getPositionY()
	));
	inviteButton->addTouchEventListener(CC_CALLBACK_2(FriendPopup::onInviteTouched, this));
	this->friendTab->addChild(inviteButton);

	//INFO ICON
	auto infoIcon = Helper4Sprite::createOptimizeSprite(PNG_NOTIFICATIO_POPUP_INFO_ICON);
	infoIcon->setPosition(Vec2(
		bg->getPositionX() - 270,
		bg->getPositionY() - bg->getContentSize().height - 150
	));
	this->friendTab->addChild(infoIcon);

	auto currentFontname = UtilFunction::getFontNameFromLanguage();
	//INFO FRIEND LABEL
	infoFriendLabel = Label::createWithTTF(
		TTFConfig(currentFontname, 28),"",TextHAlignment::LEFT
	);
	infoFriendLabel->setString(LanguageManager::getInstance()->getStringForKeys(infoFriendLabel, LanguageConstant::POPUP_GIFT_INFO));
	infoFriendLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	infoFriendLabel->setPosition(Vec2(
		infoIcon->getPositionX() + infoIcon->getContentSize().width / 2.0f,
		infoIcon->getPositionY()
	));
	this->friendTab->addChild(infoFriendLabel);

	this->addChild(this->friendTab);
}
void FriendPopup::initLeaderboardTab()
{
	this->leaderboardTab = Node::create();
	this->leaderboardTab->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->leaderboardTab->setCascadeOpacityEnabled(true);
	this->leaderboardTab->setPosition(
		this->inboxTab->getPosition().x,
		this->inboxTab->getPosition().y - 80
	);

	//FRAME FOR CELLS
	auto bg = Helper4Sprite::createOptimizeSprite(PNG_FRIEND_POPUP_FRAME_FOR_CELLS);
	bg->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	/*bg->setContentSize(
		Size(
			bg->getContentSize().width,
			bg->getContentSize().height - 80
		)
	);*/
	this->leaderboardTab->addChild(bg);

	//LIST CELL SCROLL VIEW 
	auto leaderboardTabScrollView = ReuseItemListView_Vertical::create();
	leaderboardTabScrollView->setPosition(Vec2(
		bg->getPosition().x,
		bg->getPosition().y - bg->getContentSize().height * bg->getScaleY() + 15
	));
	leaderboardTabScrollView->setContentSize(Size(
		bg->getContentSize().width * bg->getScaleX(),
		bg->getContentSize().height * bg->getScaleY() - 30));
	leaderboardTabScrollView->setScrollBarEnabled(false);
	leaderboardTabScrollView->setCascadeOpacityEnabled(true);
	leaderboardTabScrollView->setUpdateItemCallback(CC_CALLBACK_2(FriendPopup::updateLeaderboardCell, this));
	this->leaderboardTab->addChild(leaderboardTabScrollView, 0, LEADERBOARD_TAB_SCROLL_VIEW_TAG);

	//COINS BUTTON
	this->coinsLeaderboardButton = ui::Button::create(PNG_LEADERBOARD_TOGGLE_LEFT);
	this->coinsLeaderboardButton->setScale(1.06f * (1920.0f / 1600));
	this->coinsLeaderboardButton->setZoomScale(0);
	this->coinsLeaderboardButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->coinsLeaderboardButton->setPosition(Vec2(
		this->coinsLeaderboardButton->getPosition().x,
		this->coinsLeaderboardButton->getPosition().y + 80
	));
	this->coinsLeaderboardButton->setTitleLabel(
		Label::createWithTTF(
			TTFConfig(FONT_PassionOne_Regular, 45),
			"Coins"
		)
	);
	this->coinsLeaderboardButton->setColor(COLOR_TURN_ON_LEADERBOAR);
	this->coinsLeaderboardButton->setTitleColor(COLOR_TURN_ON_LABEL_LEADERBOAR);
	this->leaderboardTab->addChild(this->coinsLeaderboardButton);

	//TOTAL BET BUTTON
	this->totalBetLeaderboardButton = ui::Button::create(PNG_LEADERBOARD_TOGGLE_RIGHT);
	this->totalBetLeaderboardButton->setScale(1.06f * (1920.0f / 1600));
	this->totalBetLeaderboardButton->setZoomScale(0);
	this->totalBetLeaderboardButton->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	this->totalBetLeaderboardButton->setPosition(Vec2(
		this->coinsLeaderboardButton->getPosition().x + this->coinsLeaderboardButton->getContentSize().width * this->coinsLeaderboardButton->getScaleX(),
		this->coinsLeaderboardButton->getPosition().y
	));
	//totalBetButton->setScaleX(-totalBetButton->getScaleX());
	this->totalBetLeaderboardButton->setTitleLabel(
		Label::createWithTTF(
			TTFConfig(FONT_PassionOne_Regular, 45),
			"Total bet"
		)
	);
	this->totalBetLeaderboardButton->setColor(COLOR_TURN_OFF_LEADERBOAR);
	this->totalBetLeaderboardButton->setTitleColor(COLOR_TURN_OFF_LABEL_LEADERBOAR);
	this->leaderboardTab->addChild(this->totalBetLeaderboardButton);

	this->coinsLeaderboardButton->addTouchEventListener([this](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED){
			return;
		}
		this->gotoChildLeaderboardTab(LeaderboardTab::COINS_TAB);
	});
	this->totalBetLeaderboardButton->addTouchEventListener([this](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->gotoChildLeaderboardTab(LeaderboardTab::TOTAL_BET_TAB);
	});
	this->addChild(this->leaderboardTab);
}
void FriendPopup::gotoChildLeaderboardTab(LeaderboardTab leaderboardTab)
{
	switch (leaderboardTab)
	{
	case COINS_TAB:
		this->coinsLeaderboardButton->setColor(COLOR_TURN_ON_LEADERBOAR);
		this->coinsLeaderboardButton->setTitleColor(COLOR_TURN_ON_LABEL_LEADERBOAR);
		this->totalBetLeaderboardButton->setColor(COLOR_TURN_OFF_LEADERBOAR);
		this->totalBetLeaderboardButton->setTitleColor(COLOR_TURN_OFF_LABEL_LEADERBOAR);
		break;
	case TOTAL_BET_TAB:
		this->coinsLeaderboardButton->setColor(COLOR_TURN_OFF_LEADERBOAR);
		this->coinsLeaderboardButton->setTitleColor(COLOR_TURN_OFF_LABEL_LEADERBOAR);
		this->totalBetLeaderboardButton->setColor(COLOR_TURN_ON_LEADERBOAR);
		this->totalBetLeaderboardButton->setTitleColor(COLOR_TURN_ON_LABEL_LEADERBOAR);
		break;
	default:
		break;
	}
	this->prepareDataLeaderboardTab(nullptr, leaderboardTab);
}
void FriendPopup::onAcceptGiftTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}

	CellInbox *cellInbox = (CellInbox*)sender;
	switch (static_cast<LobbyConstant::GiftType>(cellInbox->getGiftInfo()->type))
	{
	case LobbyConstant::GIFT_TYPE_LUCKY_BOX_1:
	case LobbyConstant::GIFT_TYPE_LUCKY_BOX_2:
	case LobbyConstant::GIFT_TYPE_LUCKY_BOX_3:

		PopupManager::getInstance()->getLuckyBoxPopup()->prepareAndShow(getParent(), GiftInfo::create(cellInbox->getGiftInfo()),/*number of box*/1,/*isCollectAll*/false, [this]() {
			this->prepareDataInboxTab(nullptr);
		});
		break;
	default:
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		NetworkManager::getInstance()->acceptGift(
			cellInbox->getGiftInfo()->id,
			[this](int coreResultCode,
				rapidjson::Value &response,
				std::string responseAsString) {
			if (coreResultCode == RESULT_CODE_VALID) {
				PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp(
					[this](bool isSucess, LevelUpInfo* levelupInfo) {
					//PopupManager::getInstance()->getLoadingAnimation()->hide();
					this->prepareDataInboxTab(nullptr);
				});
			}
			else {
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			}
		});

	}
}

GiftsInfo* FriendPopup::getSummaryLuckyBoxInfo() {

	GiftsInfo *giftsInfo = new GiftsInfo();
	giftsInfo->type = LobbyConstant::GIFT_TYPE_LUCKY_BOX_1;
	for (int i = 0; i < currentGiftInfoList.size(); i++) {
		auto gift = currentGiftInfoList[i];
		LuckyBox boxInfo;
		switch (static_cast<LobbyConstant::GiftType>(gift->type))
		{
		case LobbyConstant::GIFT_TYPE_LUCKY_BOX_1:
			boxInfo = InfoManager::getInstance()->getLuckyBoxConfig().box1;
			giftsInfo->numberOfGifts++;
			break;
		case LobbyConstant::GIFT_TYPE_LUCKY_BOX_2:
			boxInfo = InfoManager::getInstance()->getLuckyBoxConfig().box2;
			giftsInfo->numberOfGifts++;
			if(giftsInfo->type != LobbyConstant::GIFT_TYPE_LUCKY_BOX_3)
				giftsInfo->type = LobbyConstant::GIFT_TYPE_LUCKY_BOX_2;
			break;
		case LobbyConstant::GIFT_TYPE_LUCKY_BOX_3:
			boxInfo = InfoManager::getInstance()->getLuckyBoxConfig().box3;
			giftsInfo->numberOfGifts++;
			giftsInfo->type = LobbyConstant::GIFT_TYPE_LUCKY_BOX_3;
			break;
		}
		giftsInfo->coinReward += boxInfo.coins;
		giftsInfo->crownReward += boxInfo.crowns;
		giftsInfo->luckyWheelReward += boxInfo.luckyWheels;
	}


	return giftsInfo;
}

void FriendPopup::onAcceptGiftAllTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	if (this->currentGiftInfoList.size() == 0) {
		return;
	}
	GiftsInfo *giftsInfo = getSummaryLuckyBoxInfo();
	if (giftsInfo->coinReward > 0) {
		PopupManager::getInstance()->getLuckyBoxPopup()->prepareAndShow(getParent(), giftsInfo,/*number of box*/giftsInfo->numberOfGifts,/*isCollectAll*/true, [this]() {
			this->prepareDataInboxTab([this]() {
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
					this->getParent(),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SUCCESS),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_ACCEPT_SUCCESS),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
					""
				);
			});
		});
	}else {
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		NetworkManager::getInstance()->acceptGiftAll(
			[this](int coreResultCode,
				rapidjson::Value &response,
				std::string responseAsString){
			if (coreResultCode == RESULT_CODE_VALID){
				PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp(
					[this](bool isSucess, LevelUpInfo* levelupInfo){
					this->prepareDataInboxTab([this](){
						PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
							this->getParent(),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SUCCESS),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_ACCEPT_SUCCESS),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
							""
						);
					});
				});
			}else{
				PopupManager::getInstance()->getLoadingAnimation()->hide();
				PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
					this->getParent(),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_WARNING),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_WARNING_MESSAGE),
					LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
					""
				);
			}
		});
	}
}
void FriendPopup::onSendGiftTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	std::vector<std::string> idsSendGift;
	for (auto child : this->currentFriendInfoList)
	{
		if (child.second->_isPPUser
			&& child.second->_isSelected)
		{
			idsSendGift.push_back(child.second->_facebookUID);
		}
	}
	if (idsSendGift.size() <= 0)
	{
		PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
			this->getParent(),
			"",
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SELECT),
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
			""
		);
	}
	else
	{
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		PluginManager::getInstance()->getFacebookController()->sendGifts(
			idsSendGift,
			[this, idsSendGift](bool result, const std::string& msg)
		{
			if (result)
			{
				std::vector<std::string> userIdList;
				auto friendList = InfoManager::getInstance()->getFacebookFriendInfo()->getFriendList();
				for (auto fbUID : idsSendGift)
				{
					if (friendList[fbUID])
					{
						userIdList.push_back(ToString(friendList[fbUID]->id));
					}
				}
				NetworkManager::getInstance()->sendGiftToUserList(
					userIdList,
					[this](int coreResultCode,
						rapidjson::Value &response,
						std::string responseAsString)
				{
					if (coreResultCode == RESULT_CODE_VALID)
					{
						PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
							this->getParent(),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SUCCESS),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SEND_FREE_GIFT_SUCCESS),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
							""
						);

						for (auto child : this->currentFriendInfoList)
						{
							if (child.second->_isPPUser
								&& child.second->_isSelected)
							{
								child.second->_isSelected = false;
								auto friendInfo
									= InfoManager::getInstance()->getFacebookFriendInfo()->getFriendList()[child.second->_facebookUID];
								if (friendInfo)
								{
									friendInfo->allowSendFreeGift = 1;
								}
							}
						}

						auto listView = this->friendTab->getChildByTag(FRIEND_TAB_SCROLL_VIEW_TAG);
						for (auto child : listView->getChildren())
						{
							((CellFriend*)child->getChildren().at(0))->updateToggleVisible();
						}
					}
					PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp();
					PopupManager::getInstance()->getLoadingAnimation()->hide();
				}
				);
			}
			else
			{
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			}
		}
		);
	}
}
void FriendPopup::onInviteTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) {
		return;
	}
	std::vector<std::string> idsInviteFriends;
	for (auto child : this->currentFriendInfoList)
	{
		if (!child.second->_isPPUser
			&& child.second->_isSelected)
		{
			idsInviteFriends.push_back(child.second->_facebookUID);
		}
	}
	if (idsInviteFriends.size() <= 0)
	{
		PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
			this->getParent(),
			"",
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SELECT),
			LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
			""
		);
	}
	else
	{
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		PluginManager::getInstance()->getFacebookController()->inviteFriends(
			idsInviteFriends,
			[this, idsInviteFriends](bool result, const std::string& msg)
		{
			if (result)
			{
				NetworkManager::getInstance()->sendInviteFriend(
					idsInviteFriends,
					[this](int coreResultCode,
						rapidjson::Value &response,
						std::string responseAsString)
				{
					if (coreResultCode == RESULT_CODE_VALID)
					{
						PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
							this->getParent(),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_SUCCESS),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_INVITE_SUCCESS),
							LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
							""
						);
					}
					PopupManager::getInstance()->getLoadingAnimation()->hide();
				}
				);
			}
			else
			{
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			}
		}
		);
	}
}

bool FriendPopup::prepareDataAndShowInboxTab(cocos2d::Node* parent) {
	this->gotoInboxTab();
	prepareDataInboxTab(nullptr);
	return true;
}

void FriendPopup::gotoInboxTab()
{
	this->titleLabel->setString(LanguageManager::getInstance()->getStringForKeys(titleLabel,LanguageConstant::POPUP_GIFT_INBOX));

	//this->inboxButton->loadTextures(PNG_SWITCH_TAB_BUTTON_ON, PNG_SWITCH_TAB_BUTTON_ON);
	this->radioButtonGroup->setSelectedButtonWithoutEvent(this->inboxButton.btn);
	this->inboxTab->setVisible(true);

	//this->friendButton->loadTextures(PNG_SWITCH_TAB_BUTTON_OFF, PNG_SWITCH_TAB_BUTTON_OFF);
	this->friendTab->setVisible(false);

	//this->leaderboardButton->loadTextures(PNG_SWITCH_TAB_BUTTON_OFF, PNG_SWITCH_TAB_BUTTON_OFF);
	this->leaderboardTab->setVisible(false);
}
void FriendPopup::gotoFriendTab()
{
	this->titleLabel->setString(LanguageManager::getInstance()->getStringForKeys(titleLabel,LanguageConstant::POPUP_GIFT_FRIENDS));

	//this->inboxButton->loadTextures(PNG_SWITCH_TAB_BUTTON_OFF, PNG_SWITCH_TAB_BUTTON_OFF);
	this->inboxTab->setVisible(false);

	this->radioButtonGroup->setSelectedButtonWithoutEvent(this->friendButton.btn);
	//this->friendButton->loadTextures(PNG_SWITCH_TAB_BUTTON_ON, PNG_SWITCH_TAB_BUTTON_ON);
	this->friendTab->setVisible(true);

	//this->leaderboardButton->loadTextures(PNG_SWITCH_TAB_BUTTON_OFF, PNG_SWITCH_TAB_BUTTON_OFF);
	this->leaderboardTab->setVisible(false);
}
void FriendPopup::gotoLeaderboardTab()
{
	this->titleLabel->setString(LanguageManager::getInstance()->getStringForKeys(titleLabel, LanguageConstant::POPUP_GIFT_LEADERBOARD));

	//this->inboxButton->loadTextures(PNG_SWITCH_TAB_BUTTON_OFF, PNG_SWITCH_TAB_BUTTON_OFF);
	this->inboxTab->setVisible(false);

	//this->friendButton->loadTextures(PNG_SWITCH_TAB_BUTTON_OFF, PNG_SWITCH_TAB_BUTTON_OFF);
	this->friendTab->setVisible(false);

	this->radioButtonGroup->setSelectedButtonWithoutEvent(this->leaderboardButton.btn);
	//this->leaderboardButton->loadTextures(PNG_SWITCH_TAB_BUTTON_ON, PNG_SWITCH_TAB_BUTTON_ON);
	this->leaderboardTab->setVisible(true);
}


/**
*  Dat: update noti for inbox tab ( call to server get data ) then call callback
*/
void FriendPopup::updateNotificationForInboxTab() {
	
	this->inboxButton.reloadNotification(InfoManager::getInstance()->getGiftInfoList().size());
	
}

void FriendPopup::prepareDataInboxTab(std::function<void()> callback)
{
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
	InfoManager::getInstance()->reloadGiftInfoList(
		[this, callback](bool isSuccess, std::vector<GiftInfo *> result)
	{
		this->inboxButton.reloadNotification(result.size());
		PopupManager::getInstance()->getBottomLobbyLayout()->updateNotificationGifts(result);
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		if (!isSuccess)
		{
			if (callback)
			{
				callback();
			}
			return;
		}
		// clear gift list info
		this->currentGiftInfoList.clear();

		//get list view
		auto listView = this->inboxTab->getChildByTag(INBOX_TAB_SCROLL_VIEW_TAG);
		std::vector<ui::Widget*> cellInboxTeamplateItems;

		int listSize = result.size();
		for (int i = listSize - 1; i >= 0; i--)
		{
			this->currentGiftInfoList.insert(std::pair<long, GiftInfo*>(i, result[i]));
		}
		//set empty gift label if size current list gift <= 0
		auto emptyGiftLabel = this->inboxTab->getChildByTag(INBOX_TAB_EMPTY_GIFT_LABEL_TAG);
		if (this->currentGiftInfoList.size() <= 0) {
			acceptAllButton->setVisible(false);
			emptyGiftLabel->setVisible(true);
			listView->setVisible(false);
		}else{
			acceptAllButton->setVisible(true);
			emptyGiftLabel->setVisible(false);
			listView->setVisible(true);
		}

		bool isCreateChilds = listView->getChildren().size() <= 0;
		for (int i = 0; i < NUMBER_TEAMPLATE_CELL; i++)
		{
			CellInbox *cellInbox = nullptr;
			if (isCreateChilds)
			{
				cellInbox = CellInbox::create(nullptr, Size(listView->getContentSize().width, CELL_HEIGHT));
				cellInbox->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				cellInbox->setCascadeOpacityEnabled(true);
				cellInbox->setPosition(Vec2(
					cellInbox->getPosition().x + CELL_X_OFFSET,
					cellInbox->getPosition().y
				));
				cellInbox->setContentSize(Size(listView->getContentSize().width, CELL_HEIGHT));
				((ButtonAdjustClikableAreaSize*)cellInbox)->setClickableAreaSize(Size(listView->getContentSize().width, CELL_HEIGHT));
				((ButtonAdjustClikableAreaSize*)cellInbox)->setAnchorClickableAreaSize(Vec2::ANCHOR_BOTTOM_LEFT);
				cellInbox->addTouchEventListener(CC_CALLBACK_2(FriendPopup::onAcceptGiftTouched, this));
				cellInboxTeamplateItems.push_back(cellInbox);
			}
			else
			{
				cellInbox = (CellInbox*)listView->getChildren().at(i)->getChildren().at(0);
			}
			if (i < listSize)
			{
				GiftInfo *giftInfo = this->currentGiftInfoList[i];
				cellInbox->setVisible(true);
				cellInbox->updateCell(giftInfo);
			}
			else
			{
				cellInbox->setVisible(false);
			}
		}
		if (isCreateChilds)
		{
			((ReuseItemListView_Vertical*)listView)->initWithNewData(
				cellInboxTeamplateItems,
				listSize,
				CELL_HEIGHT,
				CELL_SPACING,
				CELL_HEIGHT + CELL_SPACING + 15);
		}
		else
		{
			((ReuseItemListView_Vertical*)listView)->jumpToTopWithNewTotalCount(listSize);
		}
		auto totalHeight = CELL_HEIGHT * listSize + (listSize - 1) * CELL_SPACING;
		((ReuseItemListView_Vertical*)listView)->setInnerContainerSize(Size(
			listView->getContentSize().width,
			totalHeight));

		if (callback)
		{
			callback();
		}
	}
	);
}
void FriendPopup::prepareDataFriendTab(std::function<void()> callback)
{
	auto prepareAndShow = [this, callback]()
	{
		auto facebookFriendsInfo = InfoManager::getInstance()->getFacebookFriendInfo();
		//clear gift list info
		for (auto &child : this->currentFriendInfoList) {
			CC_SAFE_DELETE(child.second);
		}
		this->currentFriendInfoList.clear();
		//get friend from friend list
		int index = 0;
		for (auto &child : facebookFriendsInfo->getFriendList()) {
			FriendFBInfo *friendFBInfo = new FriendFBInfo(
				true,
				child.second->name,
				ToString(child.second->level + 1),
				child.second->facebookUID,
				child.second->getAvatarURL(100, 100)
			);
			this->currentFriendInfoList.insert(std::pair<long, FriendFBInfo*>(index, friendFBInfo));
			index++;
		}
		//get friend from invitable friend list
		for (auto &child : facebookFriendsInfo->getInvitableFriendList()) {
			FriendFBInfo *friendFBInfo = new FriendFBInfo(
				false,
				child.second->name,
				"",
				child.second->facebookUID,
				child.second->pictureURL
			);
			this->currentFriendInfoList.insert(std::pair<long, FriendFBInfo*>(index, friendFBInfo));
			index++;
		}

		//get list view
		auto listView = this->friendTab->getChildByTag(FRIEND_TAB_SCROLL_VIEW_TAG);
		std::vector<ui::Widget*> cellFriendTeamplateItems;

		//parse data and sort
		auto listSize = this->currentFriendInfoList.size();

		bool isCreateChilds = listView->getChildren().size() <= 0;
		//create teamplate items
		for (int i = 0; i < NUMBER_TEAMPLATE_CELL; i++)
		{
			if (i < listSize)
			{
				FriendFBInfo *friendFBInfo = this->currentFriendInfoList[i];
				if (isCreateChilds)
				{
					CellFriend *cellFriend = CellFriend::create(
						friendFBInfo,
						Size(listView->getContentSize().width, CELL_HEIGHT)
					);
					cellFriend->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
					cellFriend->setCascadeOpacityEnabled(true);
					cellFriend->setPosition(Vec2(
						cellFriend->getPosition().x + CELL_X_OFFSET,
						cellFriend->getPosition().y
					));
					cellFriend->setContentSize(Size(listView->getContentSize().width, CELL_HEIGHT));
					cellFriendTeamplateItems.push_back(cellFriend);
				}
				else
				{
					((CellFriend*)listView->getChildren().at(i)->getChildren().at(0))->updateCell(friendFBInfo);
				}
			}
		}
		if (isCreateChilds)
		{
			((ReuseItemListView_Vertical*)listView)->initWithNewData(
				cellFriendTeamplateItems,
				listSize,
				CELL_HEIGHT,
				CELL_SPACING,
				CELL_HEIGHT + CELL_SPACING + 15);
		}
		else
		{
			((ReuseItemListView_Vertical*)listView)->jumpToTopWithNewTotalCount(listSize);
		}
		auto totalHeight = CELL_HEIGHT * listSize + (listSize - 1) * CELL_SPACING;
		((ReuseItemListView_Vertical*)listView)->setInnerContainerSize(Size(
			listView->getContentSize().width,
			totalHeight));
		if (callback)
		{
			callback();
		}
	};
	if (utils::getTimeInMilliseconds() - InfoManager::getInstance()->getFacebookFriendInfo()->getLastTsGetFriendList()
		>= InfoManager::getInstance()->getServerConfigsInfo()->deltaTimeCallUpdateFriend) 
	{
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		InfoManager::getInstance()->reloadFriendListOnly([prepareAndShow](bool isSuccess, FacebookFriendInfo *newFbFriendInfo)
		{
			prepareAndShow();
			PopupManager::getInstance()->getLoadingAnimation()->hide();
		});
	}
	else
	{
		prepareAndShow();
		PopupManager::getInstance()->getLoadingAnimation()->hide();
	}
}
void FriendPopup::prepareDataLeaderboardTab(std::function<void()> callback, LeaderboardTab leaderboardTab)
{
	PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
	NetworkManager::getInstance()->getLeaderboard(
		static_cast<int>(leaderboardTab),
		[this, callback, leaderboardTab](
			int coreResultCode,
			rapidjson::Value &response,
			std::string responseAsString)
	{
		PopupManager::getInstance()->getLoadingAnimation()->hide();
		if (coreResultCode == RESULT_CODE_VALID)
		{
			//clear gift list info
			for (auto &child : this->currentLeaderboardInfoList) {
				CC_SAFE_DELETE(child.second);
			}
			this->currentLeaderboardInfoList.clear();

			//get list view
			auto listView = this->leaderboardTab->getChildByTag(LEADERBOARD_TAB_SCROLL_VIEW_TAG);
			std::vector<ui::Widget*> cellLeaderboardTeamplateItems;

			//parse data and sort
			auto members = Helper4ParseJSON::getMember(response);
			auto listSize = Helper4ParseJSON::getListSize(response);
			for (int i = listSize - 1; i >= 0; i--)
			{
				LeaderboardInfo *leaderboardInfo = new LeaderboardInfo();
				leaderboardInfo->updateInfoByValue(members[i]);
				leaderboardInfo->rank = i;

				this->currentLeaderboardInfoList.insert(std::pair<long, LeaderboardInfo*>(i, leaderboardInfo));
			}

			bool isCreateChilds = listView->getChildren().size() <= 0;
			//create teamplate items
			for (int i = 0; i < NUMBER_TEAMPLATE_CELL; i++)
			{
				if (i < listSize)
				{
					LeaderboardInfo *leaderboardInfo = this->currentLeaderboardInfoList[i];
					if (isCreateChilds)
					{
						CellLeaderboard *cellLeaderboard = CellLeaderboard::create(
							leaderboardTab,
							leaderboardInfo,
							Size(listView->getContentSize().width, CELL_HEIGHT)
						);
						cellLeaderboard->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
						cellLeaderboard->setCascadeOpacityEnabled(true);
						cellLeaderboard->setPosition(Vec2(
							cellLeaderboard->getPosition().x + CELL_X_OFFSET,
							cellLeaderboard->getPosition().y
						));
						cellLeaderboard->setContentSize(Size(listView->getContentSize().width, CELL_HEIGHT));
						cellLeaderboardTeamplateItems.push_back(cellLeaderboard);
					}
					else
					{
						((CellLeaderboard*)listView->getChildren().at(i)->getChildren().at(0))->updateCell(leaderboardInfo);
					}
				}
			}
			if (isCreateChilds)
			{
				((ReuseItemListView_Vertical*)listView)->initWithNewData(
					cellLeaderboardTeamplateItems,
					listSize,
					CELL_HEIGHT,
					CELL_SPACING,
					CELL_HEIGHT + CELL_SPACING + 15);
			}
			else
			{
				((ReuseItemListView_Vertical*)listView)->jumpToTopWithNewTotalCount(listSize);
			}
			auto totalHeight = CELL_HEIGHT * listSize + (listSize - 1) * CELL_SPACING;
			((ReuseItemListView_Vertical*)listView)->setInnerContainerSize(Size(
				listView->getContentSize().width,
				totalHeight));
		}
		if (callback)
		{
			callback();
		}
	}
	);
}
void FriendPopup::updateInboxCell(int newItemID, cocos2d::ui::Widget* templateItem)
{
	auto giftInfo = this->currentGiftInfoList[newItemID];
	if (giftInfo) 
	{
		((CellInbox*)templateItem)->updateCell(giftInfo);
	}
}
void FriendPopup::updateLeaderboardCell(int newItemID, cocos2d::ui::Widget * templateItem)
{
	auto leaderboardInfo = this->currentLeaderboardInfoList[newItemID];
	if (leaderboardInfo)
	{
		((CellLeaderboard*)templateItem)->updateCell(leaderboardInfo);
	}
}
void FriendPopup::updateFriendCell(int newItemID, cocos2d::ui::Widget * templateItem)
{
	auto friendFBInfo = this->currentFriendInfoList[newItemID];
	if (friendFBInfo)
	{
		((CellFriend*)templateItem)->updateCell(friendFBInfo);
	}
}
void FriendPopup::scheduleCheckAlreadyGotFriends(float dt)
{
	auto isRequestingInvitableFriend 
		= PluginManager::getInstance()->getFacebookController()->getIsRequestingInvitableFriendList();
	CCLOG("scheduleCheckAlreadyGotFriends : %s", isRequestingInvitableFriend ? "true" : "false");
	if (!isRequestingInvitableFriend) {
		this->gotoFriendTab();
		this->prepareDataFriendTab(nullptr);
		this->unschedule(schedule_selector(FriendPopup::scheduleCheckAlreadyGotFriends));
	}
}
bool FriendPopup::init()
{
	if (!BasePopup::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto fontName = UtilFunction::getFontNameFromLanguage();
	//BACKGROUND
	auto background = Helper4Sprite::createOptimizeSprite(PNG_FRIEND_POPUP_BACKGROUND);
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(background);

	//TITLE POPUP
	this->titleLabel = Label::createWithTTF("LABEL", FONT_PassionOne_Regular, 50);
	this->titleLabel->setPosition(Vec2(
		background->getPosition().x,
		background->getPosition().y + background->getContentSize().height / 2.3f
	));
	this->titleLabel->setTextColor(Color4B(234, 202, 242, 255));
	this->titleLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	this->addChild(this->titleLabel);

	//TITLE
	auto setLabelTitle = [fontName](ui::Button *target, std::string title)
	{
		auto label = Label::createWithTTF(
			TTFConfig(fontName, 50),
			title
		);

		label->enableShadow();
		target->setTitleLabel(label);
	};
	//BUTTON SWAP TABS
	Size buttonContentSize = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_SWITCH_TAB_BUTTON_ON)->getContentSize();
	radioButtonGroup = ui::RadioButtonGroup::create();
	this->addChild(radioButtonGroup, 1);

	this->inboxButton.createRadioButton(
		this,
		radioButtonGroup,
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_INBOX),
		Vec2(
			background->getPosition().x - background->getContentSize().width * background->getScaleX() / 2 + buttonContentSize.width / 1.4f,
			background->getPosition().y + background->getContentSize().height * background->getScaleY() / 3.3f
		),
		[this](cocos2d::ui::RadioButton * ratioButton, ui::RadioButton::EventType eventType)
		{
			if (eventType != ui::RadioButton::EventType::SELECTED) {
				return;
			}
			prepareDataAndShowInboxTab(nullptr);
		});
	this->inboxButton.reloadNotification(InfoManager::getInstance()->getGiftInfoList().size());
	this->friendButton.createRadioButton(
		this,
		radioButtonGroup,
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_FRIENDS),
		Vec2(
			this->inboxButton.btn->getPositionX(),
			this->inboxButton.btn->getPositionY() - (buttonContentSize.height + 10)
		),
		[this](cocos2d::ui::RadioButton * ratioButton, ui::RadioButton::EventType eventType)
	{
		if (eventType != ui::RadioButton::EventType::SELECTED) {
			return;
		}
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		this->gotoFriendTab();
		this->schedule(schedule_selector(FriendPopup::scheduleCheckAlreadyGotFriends), 1);
	});
	this->friendButton.reloadNotification(0);
	this->leaderboardButton.createRadioButton(
		this,
		radioButtonGroup,
		LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_LEADERBOARD),
		Vec2(
			this->inboxButton.btn->getPosition().x,
			this->inboxButton.btn->getPosition().y - 2 * (buttonContentSize.height + 10)
		),
		[this](cocos2d::ui::RadioButton * ratioButton, ui::RadioButton::EventType eventType)
	{
		if (eventType != ui::RadioButton::EventType::SELECTED) {
			return;
		}
		this->gotoLeaderboardTab();
		this->gotoChildLeaderboardTab(LeaderboardTab::COINS_TAB);
	});
	this->leaderboardButton.reloadNotification(0);


	/*this->inboxButton = cocos2d::ui::Button::create(PNG_SWITCH_TAB_BUTTON_OFF);
	setLabelTitle(this->inboxButton, LanguageManager::getInstance()->getStringForKeys(LanguageConstant::POPUP_GIFT_INBOX));
	this->inboxButton->setPosition(Vec2(
		background->getPosition().x - background->getContentSize().width * background->getScaleX() / 2 + this->inboxButton->getContentSize().width / 1.4f,
		background->getPosition().y + background->getContentSize().height * background->getScaleY() / 3.3f
	));
	this->inboxButton->addTouchEventListener([this](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		prepareDataAndShowInboxTab(nullptr);
	});
	this->addChild(this->inboxButton);

	this->friendButton = cocos2d::ui::Button::create(PNG_SWITCH_TAB_BUTTON_OFF);
	setLabelTitle(this->friendButton, LanguageManager::getInstance()->getStringForKeys(LanguageConstant::POPUP_GIFT_FRIENDS));
	this->friendButton->setPosition(Vec2(
		this->inboxButton->getPosition().x,
		this->inboxButton->getPosition().y - (this->inboxButton->getContentSize().height + 10)
	));
	this->friendButton->addTouchEventListener([this](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		this->gotoFriendTab();
		this->schedule(schedule_selector(FriendPopup::scheduleCheckAlreadyGotFriends), 1);
	});
	this->addChild(this->friendButton);

	this->leaderboardButton = cocos2d::ui::Button::create(PNG_SWITCH_TAB_BUTTON_OFF);
	setLabelTitle(this->leaderboardButton, LanguageManager::getInstance()->getStringForKeys(LanguageConstant::POPUP_GIFT_LEADERBOARD));
	this->leaderboardButton->setPosition(Vec2(
		this->inboxButton->getPosition().x,
		this->inboxButton->getPosition().y - 2 * (this->inboxButton->getContentSize().height + 10)
	));
	this->leaderboardButton->addTouchEventListener([this](cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type != ui::Widget::TouchEventType::ENDED) {
			return;
		}
		this->gotoLeaderboardTab();
		this->gotoChildLeaderboardTab(LeaderboardTab::COINS_TAB);
	});
	this->addChild(this->leaderboardButton);*/

	//INBOX TAB
	this->initInboxTab();
	//FRIEND TAB
	this->initFriendTab();
	//LEADERBOARD TAB
	this->initLeaderboardTab();

	//CLOSE BUTTON
	auto closeButton = this->createCloseButton();
	closeButton->setPosition(Vec2(
		background->getPosition().x + background->getContentSize().width / 2 * background->getScaleX() - 30,
		background->getPosition().y + background->getContentSize().height / 2 * background->getScaleY() - 30
	));
	this->addChild(closeButton);

	return true;
}



void FriendPopup::prepareAndShow(cocos2d::Node *parent, OpenTab openTab)
{
	updateNotificationForInboxTab();
	if (_isShowing) {
		return;
	}

	updateAfterChangeLanguage();

	switch (openTab)
	{
	case Inbox:
		if (!prepareDataAndShowInboxTab(parent))//show friend tab i
			return;
		break;
	case Friend:
		this->gotoFriendTab();
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this);
		//check each 1 seccond, is got invitable friend list to show popup
		this->schedule(schedule_selector(FriendPopup::scheduleCheckAlreadyGotFriends), 1);
		break;
	case Leaderboard:
		this->gotoLeaderboardTab();
		this->gotoChildLeaderboardTab(LeaderboardTab::COINS_TAB);
		break;
	default:
		break;
	}

	auto userInfo = InfoManager::getInstance()->getUserInfo();
	if (!userInfo->facebookUID.empty()) {
		this->friendButton.btn->setVisible(true);
		this->leaderboardButton.btn->setPosition(Vec2(
			this->inboxButton.btn->getPosition().x,
			this->inboxButton.btn->getPosition().y - 2 * (this->inboxButton.btn->getContentSize().height + 10)
		));
	}
	else {
		this->friendButton.btn->setVisible(false);
		this->leaderboardButton.btn->setPosition(this->friendButton.btn->getPosition());
	}
	BasePopup::showWithQueue(parent);
}

void FriendPopup::updateAfterChangeLanguage() {
	
	int fontSize = (LanguageManager::getInstance()->getCurrentLanguage() == vn) ? 40 : 50;

	infoFriendLabel->setString(LanguageManager::getInstance()->getStringForKeys(infoFriendLabel, LanguageConstant::POPUP_GIFT_INFO));

	this->acceptAllButton->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(this->acceptAllButton->getTitleLabel(), LanguageConstant::POPUP_INBOX_BUTTON_ACCEPT_ALL));

	this->inviteButton->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(this->inviteButton->getTitleLabel(), LanguageConstant::POPUP_INVITE_BTN_INVITE));

	this->sendGiftButton->getTitleLabel()->setString(LanguageManager::getInstance()->getStringForKeys(this->sendGiftButton->getTitleLabel(), LanguageConstant::POPUP_INVITE_BTN_SENDGIFT));

	UtilFunction::setLabelFontByLanguage(this->inboxButton.btn->getTitleRenderer(),"",fontSize);
	this->inboxButton.btn->getTitleRenderer()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_INBOX));

	UtilFunction::setLabelFontByLanguage(this->friendButton.btn->getTitleRenderer(),"",fontSize);
	this->friendButton.btn->getTitleRenderer()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_FRIENDS));

	UtilFunction::setLabelFontByLanguage(this->leaderboardButton.btn->getTitleRenderer(),"",fontSize);
	this->leaderboardButton.btn->getTitleRenderer()->setString(LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_GIFT_LEADERBOARD));

}

void ButtonPagesGroupNode::createRadioButton(
	cocos2d::Node * parent,
	cocos2d::ui::RadioButtonGroup * group, 
	const std::string & text,
	const cocos2d::Vec2 & pos, 
	std::function<void(cocos2d::ui::RadioButton*btn, cocos2d::ui::RadioButton::EventType type)> cb)
{
	btn = CRadioButton::create(PNG_FRAME_SWITCH_TAB_BUTTON_OFF, PNG_FRAME_TRANSPARENT, PNG_FRAME_SWITCH_TAB_BUTTON_ON, PNG_FRAME_TRANSPARENT, PNG_FRAME_TRANSPARENT,ui::Widget::TextureResType::PLIST);
	btn->setName(text);
	btn->setZoomScale(-0.1f);
	btn->addEventListener(cb);
	btn->setPosition(pos);
	//btn->setTitleRenderer(text, FONT_PassionOne_Regular, 50, Color4B::WHITE, Color4B::WHITE);
	btn->setTitleRenderer(text, UtilFunction::getFontNameFromLanguage(), 50, Color4B::WHITE, Color4B::WHITE);
	btn->getTitleRenderer()->enableShadow();
	group->addRadioButton(btn);

	oNotiBG = Helper4Sprite::createWithSpriteFrameName(PNG_FRAME_RED_NOTIFICATION);
	oNotiBG->setAnchorPoint(Vec2(1, 0.5f));
	oNotiBG->setCascadeOpacityEnabled(true);
	oNotiBG->setPosition((Vec2)btn->getContentSize() + Vec2(10, -10));
	btn->addChild(oNotiBG);

	oNotiLabel = Label::createWithTTF("0", FONT_PassionOne_Regular, 30);
	oNotiLabel->setPosition(oNotiBG->getContentSize() / 2);
	oNotiLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
	oNotiBG->addChild(oNotiLabel);

	parent->addChild(btn);
}