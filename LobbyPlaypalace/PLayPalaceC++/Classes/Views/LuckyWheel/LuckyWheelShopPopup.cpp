#include "LuckyWheelShopPopup.h"
#include "Constant/Defination.h"
#include "Constant/ResultCodeConstant.h"
#include "Constant/LobbyConstant.h"
#include "Manager/InfoManager.h"
#include "Manager/PopupManager.h"
#include "Manager/NetworkManager.h"
#include "Manager/StrategyManager.h"
#include "Manager/PluginManager.h"
#include "Info/AdditionalInfo.h"
#include "Views/Popup/NotificationPopup.h"
#include "Views/Popup/MissingPopup.h"
#include "Views/Popup/LoadingAnimation.h"
#include "Views/Lobby/header/HeaderLobbyLayout.h"
#include "SlotGame/base/utils/CSpriteButton.h"

USING_NS_CC;
using namespace std;

namespace LuckyWheel {
	bool LuckyWheelShopPopup::init()
	{
		if (!BasePopup::init()) {
			return false;
		}

		this->aPackageInfo = {
			PackageInfo(ToString(LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_WHEEL_1), PackageInfo::PackageType::Crown, PackageInfo::SpinAmount::_10, 100),
			PackageInfo(ToString(LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_WHEEL_2), PackageInfo::PackageType::Crown, PackageInfo::SpinAmount::_20, 180),
			PackageInfo(ToString(LobbyConstant::APPLE_PRODUCT_TYPE_LUCKY_WHEEL_3), PackageInfo::PackageType::Crown, PackageInfo::SpinAmount::_30, 240),
			PackageInfo(IAP_LUCKY_WHEEL_P1, PackageInfo::PackageType::Money, PackageInfo::SpinAmount::_10, 20),
			PackageInfo(IAP_LUCKY_WHEEL_P2, PackageInfo::PackageType::Money, PackageInfo::SpinAmount::_20, 36),
			PackageInfo(IAP_LUCKY_WHEEL_P3, PackageInfo::PackageType::Money, PackageInfo::SpinAmount::_30, 48)
		};

		auto visibleSize = Director::getInstance()->getVisibleSize();
		auto origin = Director::getInstance()->getVisibleOrigin();

		auto bg = Sprite::createWithSpriteFrameName("lucky_wheel_popup_buy_bg");
		bg->setPosition(origin + visibleSize / 2);
		this->addChild(bg);

		auto txtBottom = Label::create("SPINS TO GET COOL STUFF", FONT_PassionOne_Bold, 50);
		txtBottom->setPosition(bg->getPosition() - Vec2(0, bg->getContentSize().height / 2.25f));
		this->addChild(txtBottom);

		float xOffSet = bg ->getPositionX() - 350;
		float yOffSet = bg->getPositionY() + 110;
		float xDis = 350;
		float yDis = 250;

		float x = xOffSet;
		float y = yOffSet;

		int i = 0;
		for (auto package : this->aPackageInfo) {
			this->createBuyButton(i++, Vec2(x, y), package.type, package.numSpins);
			x += xDis;
			if(i % 3 == 0) {
				x = xOffSet;
				y -= yDis;
			}
		}

		auto closeBtn = this->createCloseButton();
		closeBtn->setPosition(Vec2(
			origin.x + visibleSize.width / 2 + bg->getContentSize().width / 2.05f,
			origin.y + visibleSize.height / 2 + bg->getContentSize().height / 2.05f
		));
		this->addChild(closeBtn);

		return true;
	}

	void LuckyWheelShopPopup::createBuyButton(
		int index,
		const cocos2d::Vec2& pos, 
		PackageInfo::PackageType type,
		PackageInfo::SpinAmount spinAmount)
	{
		std::string package_type = (type == PackageInfo::PackageType::Crown ? "crown_" : "money_") + ToString((int)spinAmount);
		auto btn = GameSlot::CSpriteButton::createButtonWithSpriteFrameName("lucky_wheel_package_" + package_type, nullptr, [this, index]() {
			this->buyPackage(index);
		});
		btn->setScaleEvent(0.9f);
		btn->setPosition(pos);
		this->addChild(btn);
	}

	void LuckyWheelShopPopup::buyPackage(int index)
	{
		auto info = this->aPackageInfo[index];
		if (info.type == PackageInfo::PackageType::Crown) {
			if (InfoManager::getInstance()->getUserInfo()->crown >= info.price) {
				PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
				NetworkManager::getInstance()->buyLuckyWheelUsingCrow(info.key,
					[this](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString) {
					PopupManager::getInstance()->getLoadingAnimation()->hide();
					if (coreResultCode == RESULT_CODE_VALID) {
						InfoManager::getInstance()->getAdditionalInfo()->luckyWheelInfo->updateInfoByValue(responseAsDocument);
						PopupManager::getInstance()->getHeaderLobbyLayout()->reloadUIHeaderAndCheckShowPopupLevelUp();
						if (callbackBuy) {
							callbackBuy();
						}
					}
					else {
						NetworkFailProcessInfo failInfo;
						failInfo.core_result_code = coreResultCode;
						StrategyManager::getInstance()->handleFailResultNewStrategy(failInfo, true, false);
					}
				});
			}
			else {
				this->hide();
				//PopupManager::getInstance()->getNotificationPopup()->showPopupMissingCrown(this->getParent(), info.price - InfoManager::getInstance()->getUserInfo()->crown);
				PopupManager::getInstance()->getMissingPopup()->prepareAndShow(this->getParent(), ppEnum::PPCurrency::CROWN_CURRENCY, info.price - InfoManager::getInstance()->getUserInfo()->crown);
			}
		}
		else if (info.type == PackageInfo::PackageType::Money){
#ifdef SDKBOX_ENABLED
			PopupManager::getInstance()->getLoadingAnimation()->prepareAndShow(this->getParent());
			PluginManager::getInstance()->getIAPController()->purchase(
				info.key,
				[this](int core_result_code, MobilePaymentInfo mobilePaymentInfo)
			{
				if (core_result_code != RESULT_CODE_VALID)
				{
					PopupManager::getInstance()->getNotificationPopup()->prepareAndShow(
						this->getParent(),
						"",
						LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::POPUP_SHOP_TRANSACTION_CANCELLED),
						LanguageManager::getInstance()->getStringForKeys(nullptr, LanguageConstant::OK),
						""
					);
				}
				else {
					InfoManager::getInstance()->getAdditionalInfo()->luckyWheelInfo->remainingSpin += mobilePaymentInfo.spinOfLuckyWheelReward;
					if (callbackBuy) {
						callbackBuy();
					}
				}
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			},
				nullptr,
				[](sdkbox::Product const&p, const std::string&msg)
			{
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			},
				[](sdkbox::Product const&p)
			{
				PopupManager::getInstance()->getLoadingAnimation()->hide();
			}
			);
#else
			PopupManager::getInstance()->getNotificationPopup()->showDontSupportPopup(
				this->getParent()
			);
#endif
		}
	}

	void LuckyWheelShopPopup::prepareAndShow(const std::function<void()>& callbackBuy)
	{
		this->callbackBuy = callbackBuy;
		BasePopup::showWithQueue(this->getParent());
	}
}