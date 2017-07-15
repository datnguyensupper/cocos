#pragma once
/**
* creator: Dat
* date: 2017-02-09
* file: AnimationManager.h, AnimationManager.cpp
 */
#include "cocos2d.h"

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

@interface DeviceManagerIOS : NSObject{
    
}

+ (id)sharedManager;
- (bool)isLowRamDevice;

@end


