#include "AddRefereeCodePopup.h"
#include "Manager/InfoManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/PopupManager.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Popup/ProfilePopup.h"
#include "Views/Popup/SettingPopup.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Info/AdditionalInfo.h"
#include "Util/UtilFunction.h"
#include "Custom/Common/LabelAutoSize.h"
#include "Configs.h"
USING_NS_CC;
using namespace std;


bool AddRefereeCodePopup::init()
{
	if (!ChangeNamePopup::init()) {
		return false;
	}

	this->titleLabel->setColor(Color3B(177, 71, 198));
	auto title = LanguageText(titleLabel,LanguageConstant::POPUP_REFERENCE, "title");
	ToUpper(title);
	this->titleLabel->setString(title);
	this->bodyLabel->setVisible(false);
	btnCancel->setVisible(false);
	btnSend->setPositionX(origin.x + visibleSize.width / 2);
	((LabelAutoSize*)btnSend->getTitleLabel())->setTextAreaSize(Size(((LabelAutoSize*)btnSend->getTitleLabel())->getTextAreaSize().width-30, ((LabelAutoSize*)btnSend->getTitleLabel())->getTextAreaSize().height-30));
	titleLabel->setPositionY(titleLabel->getPositionY() - 40);


	return true;
}

void AddRefereeCodePopup::sendButtonTouched(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	if (type != ui::Widget::TouchEventType::ENDED) 	return;

	std::string referenceCode = this->nameEditBox->getText();

	this->hide();

	if (referenceCode.empty()) {
		PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->getParent(), 
			LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "title"), LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "not_exist"));
	}
	else {
		PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
		NetworkManager::getInstance()->submitReferenceCode(referenceCode,
			[this, referenceCode](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString) {
			PopupManager::getInstance()->getLoadingAnimation()->hide();
			std::string message = "";
			switch (coreResultCode){
				case RESULT_CODE_VALID:{
					message = LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "success");
					InfoManager::getInstance()->getAdditionalInfo()->referenceCodeInfo->refereeReferenceCode = referenceCode;
					PopupManager::getInstance()->getSettingPopup()->updateRefereeCode();
				}
				break;
				case RESULT_CODE_ALREADY_SEND_GIFT_FROM_REFERENCE_CODE:
					message = LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "already_send");
					break;
				case RESULT_CODE_REFERENCE_CODE_NOT_EXIT:
					message = LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "not_exist");
					break;
				case RESULT_CODE_REFERENCE_CODE_MAX_TIME_REFER:
					message = LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "max");
					break;
				case RESULT_CODE_REFERENCE_CODE_YOUR_OWN_CODE:
					message = LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "own_code");
					break;
				default:
					message = LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "not_exist");
					break;
			}
			if(message != "") PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(this->getParent(),LanguageText(nullptr, LanguageConstant::POPUP_REFERENCE, "title"), message);
		});
	}
}

void AddRefereeCodePopup::prepareAndShow(cocos2d::Node * parent)
{
	ChangeNamePopup::prepareAndShow(parent);
	auto confirmTxt = LanguageText(btnSend->getTitleLabel(),LanguageConstant::POPUP_REFERENCE, "confirm");
	ToUpper(confirmTxt);
	btnSend->getTitleLabel()->setString(confirmTxt);
}
