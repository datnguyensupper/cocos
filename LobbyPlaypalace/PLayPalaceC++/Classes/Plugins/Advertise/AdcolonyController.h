#pragma once
/**
* creator: Kiet Duong
* date: 2017-03-01
* file: IAPController.h, IAPController.cpp
*/
//THAM KHAO: https://github.com/sdkbox/sdkbox-sample-adcolony
//THAM KHAO: http://docs.sdkbox.com/en/plugins/adcolony/v3-cpp/
#include "cocos2d.h"

//#ifdef SDKBOX_ENABLED
//#include "PluginAdColony/PluginAdColony.h"
//#else
#include "proj.android-studio/app/jni/pluginadcolony/PluginAdColony.h"
//#endif

class AdcolonyController : public sdkbox::AdColonyListener
{
private:
	std::string customIdFirstSetup = "";
	// vì khi đổi custom id, adcolony sẽ không đổi ngay mà phải play video 1 lần mới đổi được
	//-> previous custom id trước sẽ nhận được tiền thưởng
	//-> thêm biến này khi đổi custom id ( check previous custom id có trùng với custom id được set mới không 
	//-> nếu không trùng -> set can show video = false )
	bool canShowVideo = true; 
	/**
	* 2017-03-01: Kiet: callbacks and listeners
	*/
	std::function<void(const sdkbox::AdColonyAdInfo& info,const std::string& currencyName, int amount, bool success)> callbackReward = nullptr;
	void onAdColonyChange(const sdkbox::AdColonyAdInfo& info, bool available);
	/// <summary>
	/// reward after watch video
	/// </summary>
	/// <param name="info">ad info</param>
	/// <param name="currencyName">reward currency</param>
	/// <param name="amount">reward amount</param>
	/// <param name="success">does user watch video success?</param>
	void onAdColonyReward(const sdkbox::AdColonyAdInfo& info,const std::string& currencyName, int amount, bool success);
	void onAdColonyStarted(const sdkbox::AdColonyAdInfo& info);
	void onAdColonyFinished(const sdkbox::AdColonyAdInfo& info);


	/**
	* 2017-02-03: Kiet: set custom id (only call 1 time)
	*/
	void setCustomId(const std::string &customId);
public:
	AdcolonyController();
	/**
	* 2017-13-03: Kiet: show video adcolony
	*/
	void initWithCustomId(std::string customId);
	/**
	* 2017-02-03: Kiet: show video adcolony
	*/
	void showVideo(std::function<void(const sdkbox::AdColonyAdInfo& info,
		const std::string& currencyName, int amount, bool success)> _callbackReward);
	/**
	* 2017-02-03: Kiet: Check the availability of the adcolony video ads
	*/
	sdkbox::AdColonyAdStatus getVideoStatus();
	/// <summary>
	/// get customer id
	/// </summary>
	/// <returns></returns>
	std::string getCustomIdFirstSetup() {
		return this->customIdFirstSetup;
	}
};
