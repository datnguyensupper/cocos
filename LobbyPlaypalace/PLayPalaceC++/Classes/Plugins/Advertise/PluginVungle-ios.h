#ifndef _PluginVungleIOS_
#define _PluginVungleIOS_

#import <UIKit/UIKit.h>
#import <VungleSDK/VungleSDK.h>

#include "PluginVungle.h"

@interface PluginVungleIOS : UIViewController<VungleSDKDelegate>

-(void) init:(NSString*)appID;
-(bool) isPlayable;
-(IBAction)playAd: (NSDictionary*)option;
-(IBAction)playAdIncentivized:(NSString*)userID;
-(void)setListener: (VungleListener*)listener;
-(void)clearEventListeners;

@property VungleListener* vungleListener;

@end
#endif  // _PluginVungleIOS_
