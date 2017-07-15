// Image Picker for cocos2d-x
// @Author: Kanglai Qian
// @url: https://github.com/qiankanglai/ImagePicker

#import <QuartzCore/QuartzCore.h>

#import "ImagePicker.h"
#import "ImagePicker-ios.h"
#import "PluginManager.h"

#include "cocos2d.h"

using namespace cocos2d;

@implementation ImagePickerIOS

// **ATTENTION**: if you encounter any crash here, please check the device orientation
// https://github.com/qiankanglai/ImagePicker/issues/2
-(void) takePicture
{
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    [imagePicker setSourceType:UIImagePickerControllerSourceTypePhotoLibrary];
    [imagePicker setDelegate:self];
    imagePicker.wantsFullScreenLayout = YES;
    
    // CCEAGLView is a subclass of UIView
    UIView *view = (UIView *)Director::getInstance()->getOpenGLView()->getEAGLView();
    [view addSubview:imagePicker.view];
}

-(void) imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    Image *image = new Image();
    int orientation = 0;
    @autoreleasepool
    {
        UIImage *img = [info objectForKey:UIImagePickerControllerOriginalImage];
        NSData *imgData = UIImagePNGRepresentation(img);
        NSUInteger len = [imgData length];
        
        Byte *byteData = (Byte*)malloc(len);
        memcpy(byteData, [imgData bytes], len);
        
        image->initWithImageData(byteData, len);
        
        orientation = img.imageOrientation;
        
        free(byteData);
    }
    
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([image, orientation]{
        //Texture2D* texture = new Texture2D();
        //texture->initWithImage(image);
        //texture->autorelease();
        //image->release();
        
        PluginManager::getInstance()->getImagePickerController()->finishImage(image, orientation);
    });
    
    [picker.view removeFromSuperview];
    [picker release];
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker{
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([]{
        PluginManager::getInstance()->getImagePickerController()->finishImage(nullptr, 1);
    });
    [picker.view removeFromSuperview];
    [picker release];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
}

@end
