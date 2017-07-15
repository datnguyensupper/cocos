#include "IAPController.h"
#include "Configs.h"
#include "Manager/NetworkManager.h"
#include "Constant/ResultCodeConstant.h"

USING_NS_CC;


IAPController::IAPController()
{

#ifdef SDKBOX_ENABLED
	if (Configs::printConsoleLog)
	{
		CCLOG("INIT API IN CONTRUCTOR FUNCTION");
	}
	sdkbox::IAP::init();
	sdkbox::IAP::setListener(this);
#endif
	refresh();
}

void IAPController::refresh()
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: REFRESH");
	}
#ifdef SDKBOX_ENABLED
	sdkbox::IAP::refresh();
#endif
}

bool IAPController::purchase(std::string nameIAP, std::function<void(int core_result_code, MobilePaymentInfo mobilePaymentInfo)> callbackAfterVerify, std::function<void(sdkbox::Product const&p)> callbackSuccess, std::function<void(sdkbox::Product const&p, const std::string&msg)> callbackFail, std::function<void(sdkbox::Product const&p)> callbackCancel)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: PURCHASE ITEM NAME : %s", nameIAP.c_str());
	}
	this->callbackAfterVerify = callbackAfterVerify;
	this->callbackSuccess = callbackSuccess;
	this->callbackFail = callbackFail;
	this->callbackCancel = callbackCancel;

#ifdef SDKBOX_ENABLED
	sdkbox::IAP::purchase(nameIAP);
	return true;
#else
	return false;
#endif
}

void IAPController::onInitialized(bool ok)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: ON INITIALIZED : %s", ok ? "true" : "false");
	}

#ifdef SDKBOX_ENABLED
	if (ok)
	{
		sdkbox::IAP::enableUserSideVerification(true);
		sdkbox::IAP::refresh();
	}
#endif
}

void IAPController::onSuccess(sdkbox::Product const & p)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: ON SUCCESS PURCHASE :");
		CCLOG("id = %s", p.id.c_str());
		CCLOG("name = %s", p.name.c_str());
		CCLOG("currencyCode = %s", p.currencyCode.c_str());
		CCLOG("description = %s", p.description.c_str());
		CCLOG("price = %s", p.price.c_str());
		CCLOG("priceValue = %f", p.priceValue);
		CCLOG("receipt = %s", p.receipt.c_str());
		CCLOG("receiptCipheredPayload = %s", p.receiptCipheredPayload.c_str());
		CCLOG("title = %s", p.title.c_str());
		CCLOG("transactionID = %s", p.transactionID.c_str());
	}
#ifdef SDKBOX_ENABLED
    if (this->callbackSuccess){
		this->callbackSuccess(p);
		this->callbackSuccess = nullptr;
	}
    
//    verifyPayment
    std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callbackPurchase =
    [this,p](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString){
        
        //RESTORE IF VALIDATE FAIL FROM SERVER
		if (coreResultCode != RESULT_CODE_VALID) sdkbox::IAP::restore();
		if (this->callbackAfterVerify){
			MobilePaymentInfo mobilePaymentInfo;
			if (coreResultCode == RESULT_CODE_VALID) mobilePaymentInfo.updateInfoByValue(responseAsDocument);
			this->callbackAfterVerify(coreResultCode, mobilePaymentInfo);
			this->callbackAfterVerify = nullptr;
		}
        
    };
    
    
    if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        NetworkManager::getInstance()->verifyIOSPayment(p.receipt,p.receiptCipheredPayload,callbackPurchase);
    else
		NetworkManager::getInstance()->verifyAndroidPayment(p.receipt,p.receiptCipheredPayload,callbackPurchase);
	
#endif
}

void IAPController::forceCallApiPurchase2Server(std::string receiptCipheredPayload){
#ifdef SDKBOX_ENABLED
    std::function<void(int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString)> callbackPurchase =
    [this](int coreResultCode, rapidjson::Value &responseAsDocument, std::string responseAsString){
        //RESTORE IF VALIDATE FAIL FROM SERVER
        if (coreResultCode != RESULT_CODE_VALID) sdkbox::IAP::restore();
    };
    NetworkManager::getInstance()->verifyIOSPayment("",receiptCipheredPayload,callbackPurchase);
#endif
}

void IAPController::onFailure(sdkbox::Product const & p, const std::string & msg)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: ON FAILURE PURCHASE :");
		CCLOG("id = %s", p.id.c_str());
		CCLOG("name = %s", p.name.c_str());
		CCLOG("currencyCode = %s", p.currencyCode.c_str());
		CCLOG("description = %s", p.description.c_str());
		CCLOG("price = %s", p.price.c_str());
		CCLOG("priceValue = %f", p.priceValue);
		CCLOG("receipt = %s", p.receipt.c_str());
		CCLOG("receiptCipheredPayload = %s", p.receiptCipheredPayload.c_str());
		CCLOG("title = %s", p.title.c_str());
		CCLOG("transactionID = %s", p.transactionID.c_str());
		CCLOG("error msg : %s", msg.c_str());
	}
	if (this->callbackFail)
	{
		this->callbackFail(p, msg);
		this->callbackFail = nullptr;
	}
}

void IAPController::onCanceled(sdkbox::Product const & p)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: ON CANCEL PURCHASE :");
		CCLOG("id = %s", p.id.c_str());
		CCLOG("name = %s", p.name.c_str());
		CCLOG("currencyCode = %s", p.currencyCode.c_str());
		CCLOG("description = %s", p.description.c_str());
		CCLOG("price = %s", p.price.c_str());
		CCLOG("priceValue = %f", p.priceValue);
		CCLOG("receipt = %s", p.receipt.c_str());
		CCLOG("receiptCipheredPayload = %s", p.receiptCipheredPayload.c_str());
		CCLOG("title = %s", p.title.c_str());
		CCLOG("transactionID = %s", p.transactionID.c_str());
	}
	if (this->callbackCancel)
	{
		this->callbackCancel(p);
		this->callbackCancel = nullptr;
	}
}

void IAPController::onRestored(sdkbox::Product const & p)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: ON RESTORED PURCHASE :");
		CCLOG("id = %s", p.id.c_str());
		CCLOG("name = %s", p.name.c_str());
		CCLOG("currencyCode = %s", p.currencyCode.c_str());
		CCLOG("description = %s", p.description.c_str());
		CCLOG("price = %s", p.price.c_str());
		CCLOG("priceValue = %f", p.priceValue);
		CCLOG("receipt = %s", p.receipt.c_str());
		CCLOG("receiptCipheredPayload = %s", p.receiptCipheredPayload.c_str());
		CCLOG("title = %s", p.title.c_str());
		CCLOG("transactionID = %s", p.transactionID.c_str());
	}
}

void IAPController::onProductRequestSuccess(std::vector<sdkbox::Product> const & products)
{
	if (Configs::printConsoleLog)
	{
		CCLOG("IAP: ON PRODUCT REQUEST SUCCESS:");
		for (auto &product : products)
		{
			CCLOG("id = %s", product.id.c_str());
			CCLOG("name = %s", product.name.c_str());
			CCLOG("currencyCode = %s", product.currencyCode.c_str());
			CCLOG("description = %s", product.description.c_str());
			CCLOG("price = %s", product.price.c_str());
			CCLOG("priceValue = %f", product.priceValue);
			CCLOG("receipt = %s", product.receipt.c_str());
			CCLOG("receiptCipheredPayload = %s", product.receiptCipheredPayload.c_str());
			CCLOG("title = %s", product.title.c_str());
			CCLOG("transactionID = %s\n", product.transactionID.c_str());
		}
	}
}

void IAPController::onProductRequestFailure(const std::string & msg)
{
	if (Configs::printConsoleLog) CCLOG("IAP: ON PRODUCT REQUEST FAILURE WITH MES: %s", msg.c_str());
	
}

void IAPController::onRestoreComplete(bool ok, const std::string & msg)
{
	if (Configs::printConsoleLog) CCLOG("IAP: ON RESTORE COMPLETE: %d:%s", ok, msg.c_str());
//    sdkbox::IAP::purchase("4mcoin");
    
}
