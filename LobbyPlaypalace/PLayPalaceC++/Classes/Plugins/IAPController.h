#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-01
* file: IAPController.h, IAPController.cpp
*/
//THAM KHAO: https://github.com/sdkbox/sdkbox-sample-iap
//THAM KHAO: http://docs.sdkbox.com/en/plugins/iap/v3-cpp/
#include "cocos2d.h"
#include "Info/BaseItemInfo.h"
//#ifdef SDKBOX_ENABLED
//#include "PluginIAP/PluginIAP.h"
//#else
#include "proj.android-studio/app/jni/pluginiap/PluginIAP.h"
//#endif

struct MobilePaymentInfo : public BaseItemInfo
{
	double coinReward;
	int crownReward;
	long boosterLevelUpBonusDurationTimeReward;
	int spinOfLuckyWheelReward;

	int magicItem100PercentWinReward;
	int magicItemLuckySpinType1Reward;
	int magicItemLuckySpinType2Reward;
	long magicItemDoubleExpDurationTimeReward;
	long magicItemLuckySymbolDurationTimeReward;

	double packagePrice;
	std::string currency;
	int productType;
	/// <summary>
	/// update payment info after verify from pp server
	/// </summary>
	/// <param name="data"></param>
	void updateInfoByValue(rapidjson::Value &data)
	{
		BaseItemInfo::updateBaseItemInfoByValue(data);
		if (data.HasMember(JSONFieldConstant::COIN_REWARD.c_str()))
		{
			this->coinReward = data[JSONFieldConstant::COIN_REWARD.c_str()].GetDouble();
		}
		if (data.HasMember(JSONFieldConstant::CROWN_REWARD.c_str()))
		{
			this->crownReward = data[JSONFieldConstant::CROWN_REWARD.c_str()].GetInt();
		}
		if (data.HasMember(JSONFieldConstant::BOOSTER_LEVEL_UP_BONUS_DURATION_TIME_REWARD.c_str()))
		{
			this->boosterLevelUpBonusDurationTimeReward = data[JSONFieldConstant::BOOSTER_LEVEL_UP_BONUS_DURATION_TIME_REWARD.c_str()].GetInt64();
		}
		if (data.HasMember(JSONFieldConstant::SPIN_OF_LUCKY_WHEEL_REWARD.c_str()))
		{
			this->spinOfLuckyWheelReward = data[JSONFieldConstant::SPIN_OF_LUCKY_WHEEL_REWARD.c_str()].GetInt();
		}
		if (data.HasMember(JSONFieldConstant::MAGIC_ITEM_100_PERCENT_MEGA_WIN_REWARD.c_str()))
		{
			this->magicItem100PercentWinReward = data[JSONFieldConstant::MAGIC_ITEM_100_PERCENT_MEGA_WIN_REWARD.c_str()].GetInt();
		}
		if (data.HasMember(JSONFieldConstant::MAGIC_ITEM_LUCKY_SPIN_TYPE_1_REWARD.c_str()))
		{
			this->magicItemLuckySpinType1Reward = data[JSONFieldConstant::MAGIC_ITEM_LUCKY_SPIN_TYPE_1_REWARD.c_str()].GetInt();
		}
		if (data.HasMember(JSONFieldConstant::MAGIC_ITEM_LUCKY_SPIN_TYPE_2_REWARD.c_str()))
		{
			this->magicItemLuckySpinType2Reward = data[JSONFieldConstant::MAGIC_ITEM_LUCKY_SPIN_TYPE_2_REWARD.c_str()].GetInt();
		}
		if (data.HasMember(JSONFieldConstant::MAGIC_ITEM_DOUBLE_EXP_DURATION_TIME_REWARD.c_str()))
		{
			this->magicItemDoubleExpDurationTimeReward = data[JSONFieldConstant::MAGIC_ITEM_DOUBLE_EXP_DURATION_TIME_REWARD.c_str()].GetInt64();
		}
		if (data.HasMember(JSONFieldConstant::MAGIC_ITEM_LUCKY_SYMBOL_DURATION_TIME_REWARD.c_str()))
		{
			this->magicItemLuckySymbolDurationTimeReward = data[JSONFieldConstant::MAGIC_ITEM_LUCKY_SYMBOL_DURATION_TIME_REWARD.c_str()].GetInt64();
		}
		if (data.HasMember(JSONFieldConstant::PACKAGE_PRICE.c_str()))
		{
            this->packagePrice = data[JSONFieldConstant::PACKAGE_PRICE.c_str()].GetDouble();
		}
		if (data.HasMember(JSONFieldConstant::CURRENCY.c_str()))
		{
            this->currency = data[JSONFieldConstant::CURRENCY.c_str()].GetString();
		}
		if (data.HasMember(JSONFieldConstant::PRODUCT_TYPE.c_str()))
		{
			this->productType = data[JSONFieldConstant::PRODUCT_TYPE.c_str()].GetInt64();
		}

	}
};

class IAPController : public sdkbox::IAPListener
{
private:
	/**
	* 2017-03-01: Kiet: callbacks and listeners
	*/
	std::function<void(int core_result_code, MobilePaymentInfo mobilePaymentInfo)> callbackAfterVerify = nullptr;
	std::function<void(sdkbox::Product const& p)> callbackSuccess = nullptr;
	std::function<void(sdkbox::Product const& p, const std::string &msg)> callbackFail = nullptr;
	std::function<void(sdkbox::Product const& p)> callbackCancel = nullptr;

	/// <summary>
	/// start initialize product
	/// </summary>
	/// <param name="ok"></param>
	virtual void onInitialized(bool ok) override;
	/// <summary>
	/// success purchase product
	/// </summary>
	/// <param name="p"></param>
	virtual void onSuccess(sdkbox::Product const& p) override;
	/// <summary>
	/// call api purchase for testing purpose
	/// </summary>
	/// <param name="receiptCipheredPayload"></param>
    void forceCallApiPurchase2Server(std::string receiptCipheredPayload);
	/// <summary>
	/// purchase fail
	/// </summary>
	/// <param name="p"></param>
	/// <param name="msg"></param>
	virtual void onFailure(sdkbox::Product const& p, const std::string &msg) override;
	/// <summary>
	/// cancel product
	/// </summary>
	/// <param name="p"></param>
	virtual void onCanceled(sdkbox::Product const& p) override;
	/// <summary>
	/// start restore product event
	/// </summary>
	/// <param name="p"></param>
	virtual void onRestored(sdkbox::Product const& p) override;
	/// <summary>
	/// get product info success
	/// </summary>
	/// <param name="products"></param>
	virtual void onProductRequestSuccess(std::vector<sdkbox::Product> const &products) override;
	/// <summary>
	/// get product info fail
	/// </summary>
	/// <param name="msg"></param>
	virtual void onProductRequestFailure(const std::string &msg) override;
	/// <summary>
	/// restore purchase item complete
	/// </summary>
	/// <param name="ok"></param>
	/// <param name="msg"></param>
	void onRestoreComplete(bool ok, const std::string &msg);
    
//    std::string previousReceipt = "";
public:
	IAPController();

	void refresh();
	/** 
	* 2017-03-01: Kiet: make a purchase, if verify from server fail -> call restore
	* @param key: name is the name of the IAP item in your config file under items tag, not the product id you set in iTunes or GooglePlay 
	* @param callbackVerifySuccess: after call to PP server to verify and get response, this callback will be called
	* @param callbackSuccess: purchase in appstore success
	* @param callbackFail: purchase in appstore fail
	* @param callbackCancel: purchase in appstore cancel
	*/
	bool purchase(
		std::string nameIAP,
		std::function<void(int core_result_code, MobilePaymentInfo mobilePaymentInfo)> callbackAfterVerify,
		std::function<void(sdkbox::Product const& p)> callbackSuccess = nullptr,
		std::function<void(sdkbox::Product const& p, const std::string &msg)> callbackFail = nullptr,
		std::function<void(sdkbox::Product const& p)> callbackCancel = nullptr
	);
};
