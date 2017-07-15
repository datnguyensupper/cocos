#pragma once

#include "cocos2d.h"
namespace GameSlot {
	class CSlotSettings {
	private:
		int* aSymbolAnimFrames = nullptr;
		cocos2d::Vec2* aAnchorPoint = nullptr;
		std::vector<int> aSymbolsOccurence;
	public:
		/** Returns the shared instance of the CSlotSettings.
		* @return The instance of the CSlotSettings.
		*/
		static CSlotSettings* getInstance();

		~CSlotSettings();
		/**
		* Init Slot Settings
		*/
		void initSlotSettings(int* aSymbolAnimFrames, cocos2d::Vec2* aAnchorPoint = nullptr);
		/**
		* release
		*/
		void release();

#pragma region getter
		int* getSymbolAnimFrames() { return this->aSymbolAnimFrames; }
		cocos2d::Vec2* getAnchorPoints() { return this->aAnchorPoint; }
		const std::vector<int>& getSymbolsOccurence() { return this->aSymbolsOccurence; }
#pragma endregion

	};
}