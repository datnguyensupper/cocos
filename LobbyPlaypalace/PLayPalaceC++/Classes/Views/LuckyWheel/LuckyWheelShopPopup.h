#pragma once
#include "Views/Popup/BasePopup.h"

namespace LuckyWheel {
	struct PackageInfo {
		enum PackageType {
			Crown,
			Money
		};
		enum SpinAmount {
			_10 = 10,
			_20 = 20,
			_30 = 30,
		};
		std::string key;
		PackageType type;
		SpinAmount numSpins;
		double price;
		/// <summary>
		/// package purchase info
		/// </summary>
		/// <param name="key"></param>
		/// <param name="type"></param>
		/// <param name="numSpins">number of lucky spin</param>
		/// <param name="price"></param>
		PackageInfo(const std::string& key, PackageType type, SpinAmount numSpins, double price) {
			this->key = key;
			this->type = type;
			this->numSpins = numSpins;
			this->price = price;
		}
	};

	class LuckyWheelShopPopup : public BasePopup
	{
	private:
		std::vector<PackageInfo> aPackageInfo;
		std::function<void()> callbackBuy;
		/**
		* create Buy Button
		* @param pos:
		* @param type: type package
		* @param spinAmount: spin Amount
		*/
		void createBuyButton(int index, const cocos2d::Vec2& pos, PackageInfo::PackageType type, PackageInfo::SpinAmount spinAmount);
		/// <summary>
		/// buy package at index
		/// </summary>
		/// <param name="index"></param>
		void buyPackage(int index);
	public:
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

		/**
		* prepare and show
		*/
		void prepareAndShow(const std::function<void()>& callbackBuy);

		/// <summary>
	/// define create function
	/// </summary>
	/// <param name="">name of class</param>
	/// <returns>return class object</returns>
	CREATE_FUNC(LuckyWheelShopPopup);
	};
}