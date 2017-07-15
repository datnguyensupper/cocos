#include "DeviceManager.h"





using namespace std;
USING_NS_CC;
#pragma region init singleton
DeviceManager* DeviceManager::s_instance = nullptr;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "DeviceManagerIOS.h"
static DeviceManagerIOS* sharedDeviceManagerIOS = [DeviceManagerIOS sharedManager];
#endif

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
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _isLowRamDevice = [sharedDeviceManagerIOS isLowRamDevice];
#else
    _isLowRamDevice = false;
#endif

    
#if IS_DEBUG
    /*test: force low ram device*/
    //    _isLowRamDevice = true;
#endif
    
    log("<<________------ IsLowRamDevice : %s----------___",_isLowRamDevice?"true":"false");
}

