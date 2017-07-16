// Image Picker for cocos2d-x
// @Author: Kanglai Qian
// @url: https://github.com/qiankanglai/ImagePicker
#include "cocos2d.h"
#include "GamePlugin.h"

using namespace cocos2d;

cocos2d::Image* GamePlugin::circleImage(unsigned char* data, size_t len){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Image *img = new Image();
    
    @autoreleasepool
    {
        
        NSData *imageData = [NSData dataWithBytesNoCopy:data length:len freeWhenDone:YES];
        UIImage *image = [UIImage imageWithData:imageData];
        
        float radius = MIN(image.size.width, image.size.height) / 2;
        CGSize size;
        size.width = size.height = radius * 2;
        
        UIGraphicsBeginImageContextWithOptions(size, NO, 1.0);
        CGRect bounds=(CGRect){CGPointZero,size};
        [[UIBezierPath bezierPathWithRoundedRect:bounds
                                    cornerRadius:radius] addClip];
        [image drawInRect:bounds];
        UIImage *finalImage = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
        
        NSData *imgData = UIImagePNGRepresentation(finalImage);
        NSUInteger finalLen = [imgData length];
        
        Byte *byteData = (Byte*)malloc(finalLen);
        memcpy(byteData, [imgData bytes], finalLen);
    
        img->initWithImageData(byteData, finalLen);
        free(byteData);
    }
    
    return img;
#endif
    return nullptr;
}
