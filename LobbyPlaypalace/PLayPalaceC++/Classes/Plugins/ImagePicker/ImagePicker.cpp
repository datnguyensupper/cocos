// Image Picker for cocos2d-x
// @Author: Kanglai Qian
// @url: https://github.com/qiankanglai/ImagePicker

#include "ImagePicker.h"
#include "ImagePickerImpl.h"

#include "cocos2d.h"

using namespace cocos2d;

ImagePicker::ImagePicker(){
    _delegate = nullptr;
}

void ImagePicker::pickImage(ImagePickerDelegate *delegate) {
    _delegate = delegate;
    
    ImagePickerImpl::openImage();
}

void ImagePicker::finishImage(cocos2d::Image* image, int orientation){
    if(_delegate != nullptr){
        _delegate->didFinishPickingWithResult(image, orientation);
    }
}