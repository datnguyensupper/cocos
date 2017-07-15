// Image Picker for cocos2d-x
// @Author: Kanglai Qian
// @url: https://github.com/qiankanglai/ImagePicker

#include "KeyboardIOS.h"

#include "cocos2d.h"

using namespace cocos2d;

void KeyboardIOS::copyText2ClipBoard(std::string text)
{
    UIPasteboard *pasteboard = [UIPasteboard generalPasteboard];
    pasteboard.string = [NSString stringWithCString:text.c_str() encoding:[NSString defaultCStringEncoding]];
}

