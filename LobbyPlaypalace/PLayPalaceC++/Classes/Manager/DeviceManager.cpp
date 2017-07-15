#include "DeviceManager.h"


#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)



using namespace std;
USING_NS_CC;
#pragma region init singleton
DeviceManager* DeviceManager::s_instance = nullptr;

DeviceManager* DeviceManager::getInstance()
{
	if (s_instance == nullptr) {
		s_instance = new DeviceManager();
	}
	//CC_SAFE_DELETE(s_instance);
	//CC_SAFE_DELETE_ARRAY();
	
	return s_instance;
}
#pragma endregion

DeviceManager::DeviceManager(){
#if IS_DEBUG
	/*test: force set app is low ram device*/
	//_isLowRamDevice = true;
#endif
}

#endif
