#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: AnimationManager.h, AnimationManager.cpp
 */
#include "cocos2d.h"
#include "Constant/Defination.h"

class DeviceManager
{
private:
    DeviceManager();
    static DeviceManager* s_instance;
    bool _isLowRamDevice = false;
public:
    /**
     * 2017-02-09: Kiet: get instance class
     */
    static DeviceManager* getInstance();
    
    
    bool isLowRamDevice(){
        return _isLowRamDevice;
    }
};


