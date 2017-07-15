#include "CSlotSettings.h"
#include "CSettings.h"

USING_NS_CC;
namespace GameSlot {
	static CSlotSettings* _sharedCSlotSettings = nullptr;
	CSlotSettings * CSlotSettings::getInstance()
	{
		if (!_sharedCSlotSettings)
		{
			_sharedCSlotSettings = new (std::nothrow) CSlotSettings();
		}

		return _sharedCSlotSettings;
	}
	CSlotSettings::~CSlotSettings()
	{
		CC_SAFE_DELETE_ARRAY(aSymbolAnimFrames);
		CC_SAFE_DELETE_ARRAY(aAnchorPoint);
	}
	void CSlotSettings::initSlotSettings(int* aSymbolAnimFrames, cocos2d::Vec2* aAnchorPoint)
	{
		this->aSymbolAnimFrames = aSymbolAnimFrames;
		this->aAnchorPoint = aAnchorPoint;

		int* arrayOccurence = new int[13]{ 14, 14, 12, 12, 10, 10, 8, 8, 7, 5, 3, 2, 1};

		for (int i = 0; i < CSettings::NUM_SYMBOLS; ++i) {
			for (int j = 0; j < arrayOccurence[i]; ++j) {
				this->aSymbolsOccurence.push_back(i);
			}
		}

		CC_SAFE_DELETE_ARRAY(arrayOccurence);
	}
	void CSlotSettings::release()
	{
		CC_SAFE_DELETE(_sharedCSlotSettings);
	}
}
