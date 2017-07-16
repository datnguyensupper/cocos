//
//  FirstViewController.m
//  Vungle Sample App
//
//  Created by Vungle on 3/24/14.
//  Copyright (c) 2014 Vungle. All rights reserved.
//

#import "PluginVungle-ios.h"

@interface PluginVungleIOS ()

@end

@implementation PluginVungleIOS

#pragma mark - UIViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //Set VungleSDK Delegate
    [[VungleSDK sharedSDK] setDelegate:self];
}

- (BOOL)shouldAutorotate {
    return NO;
}

- (void)dealloc {
    [[VungleSDK sharedSDK] setDelegate:nil];
    [super dealloc];
}

#pragma mark - VungleSDK Delegate

- (void)vungleSDKAdPlayableChanged:(BOOL)isAdPlayable {
    if(self.vungleListener != nullptr){
        self.vungleListener->onAdPlayableChanged(isAdPlayable);
    }
}

- (void)vungleSDKwillShowAd {
    if(self.vungleListener != nullptr){
        self.vungleListener->onAdStart();
    }
}

- (void)vungleSDKwillCloseAdWithViewInfo:(NSDictionary *)viewInfo willPresentProductSheet:(BOOL)willPresentProductSheet {
    if(self.vungleListener != nullptr){
        self.vungleListener->onAdEnd((bool)[viewInfo objectForKey:@"completedView"]);
    }
}

#pragma mark - FirstView Methods
-(void) init:(NSString*)appID{
    VungleSDK *sdk = [VungleSDK sharedSDK];
    [sdk startWithAppId:appID];
}

-(bool) isPlayable{
    VungleSDK *sdk = [VungleSDK sharedSDK];
    return [sdk isAdPlayable];
}

-(void) setListener:(VungleListener *)listener{
    self.vungleListener = listener;
}

-(void) clearEventListeners{
    [[VungleSDK sharedSDK] setDelegate:nil];
}

- (IBAction)playAd: (NSDictionary*) option{
    // Play a Vungle ad (with default options)
    VungleSDK *sdk = [VungleSDK sharedSDK];
    NSError *error;
    if(option == nullptr){
        [sdk playAd:self error:&error];
    }else{
        [sdk playAd:self withOptions:option error:&error];
    }
    if (error) {
        if(self.vungleListener != nullptr){
            self.vungleListener->onAdUnavailable(std::string([[error localizedDescription] UTF8String]));
        }
    }
}

- (IBAction)playAdIncentivized:(NSString*) userID{
    // Grab instance of Vungle SDK
    VungleSDK *sdk = [VungleSDK sharedSDK];
    
    // Dict to set custom ad options
    NSDictionary *options = @{VunglePlayAdOptionKeyIncentivized: @YES,
                              VunglePlayAdOptionKeyUser: userID,
                              VunglePlayAdOptionKeyIncentivizedAlertBodyText : @"If the video isn't completed you won't get your reward! Are you sure you want to close early?",
                              VunglePlayAdOptionKeyIncentivizedAlertCloseButtonText : @"Close",
                              VunglePlayAdOptionKeyIncentivizedAlertContinueButtonText : @"Keep Watching",
                              VunglePlayAdOptionKeyIncentivizedAlertTitleText : @"Careful!"};
    
    // Pass in dict of options, play ad
    NSError *error;
    [sdk playAd:self withOptions:options error:&error];
    if (error) {
        if(self.vungleListener != nullptr){
            self.vungleListener->onAdUnavailable(std::string([[error localizedDescription] UTF8String]));
        }
    }
}

@end
