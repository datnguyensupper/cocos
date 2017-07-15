#import "DeviceManagerIOS.h"


@implementation DeviceManagerIOS

+ (DeviceManagerIOS *)sharedManager{
    
    static DeviceManagerIOS * sharedDeviceManager = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedDeviceManager = [[self alloc] init];
    });
    return sharedDeviceManager;
}

- (bool)isLowRamDevice{
    unsigned long long memoriesBytes = [NSProcessInfo processInfo].physicalMemory;
    unsigned long long memoriesMB = memoriesBytes / (1024*1024);
    
    return memoriesMB < 550;
}

@end
