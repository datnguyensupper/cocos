#ifndef __ImagePicker__ImagePickerIos_
#define __ImagePicker__ImagePickerIos_

#import <UIKit/UIKit.h>

@interface ImagePickerIOS : UIViewController<UINavigationControllerDelegate, UIImagePickerControllerDelegate, UIPopoverControllerDelegate>
{
}

-(void) takePicture;
@end

#endif  // __ImagePicker__ImagePickerIos_
