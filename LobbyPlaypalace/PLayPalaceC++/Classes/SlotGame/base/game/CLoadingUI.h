#pragma once

#include "cocos2d.h"

using namespace std;

namespace GameSlot {
	class CMainBase;
	class CLoadingUI : public cocos2d::Node
	{
	private:
		CMainBase* oMain;
		bool bLoadMainThread;
		vector<std::string> aResources;
		std::function<void()> callbackComplete;
	protected:
		cocos2d::Node* loaderGroup = nullptr;
		cocos2d::Sprite* bg = nullptr;
		cocos2d::Sprite* loaderIcon = nullptr;
		cocos2d::Label* label = nullptr;
		/*
		* Function called when start loading resources
		* @param dt: delay time
		*/
		void startLoading(float dt);
	public:
		CLoadingUI(CMainBase* oMain);
		/// <summary>
	/// init UI
	/// </summary>
	/// <returns>is init success</returns>
	virtual bool init();

		void setBackgroundLoading(const std::string& fileName);
		/*
		* Prepare and call loading resources
		* @param aResources: vector string contains resources
		* @param callbackComplete (optional): callback after loaded all resources
		*/
		void preload(const vector<std::string>& aResources, const std::function<void()>& callbackComplete, bool bLoadMainThread = true);
		/*
		* Show loading UI - should call before load
		*/
		void showLoading(int progress = 1);
		/*
		* Hiding loading UI - should call when loading complete
		*/
		void hideLoading(const std::function<void()>& callback = nullptr);
	};
}
