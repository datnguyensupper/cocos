#ifndef __ImagePicker__ImagePicker__
#define __ImagePicker__ImagePicker__

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

class Image;

class ImagePickerDelegate {
public:
	/// <summary>
	/// finish picking image
	/// </summary>
	/// <param name="image"></param>
	/// <param name="orientation"></param>
    virtual void didFinishPickingWithResult(cocos2d::Image* image, int orientation) = 0;
    virtual ~ImagePickerDelegate() {};
};

class CC_DLL ImagePicker{
public:
    ImagePicker();
    /// <summary>
    /// set pick image callback
    /// </summary>
    /// <param name="delegate"></param>
    void pickImage(ImagePickerDelegate *delegate);
	/// <summary>
	/// call back after chose image
	/// </summary>
	/// <param name="image"></param>
	/// <param name="orientation"></param>
    void finishImage(cocos2d::Image* image, int orientation = 1);
private:
    ImagePickerDelegate *_delegate;
};

NS_CC_END

#endif