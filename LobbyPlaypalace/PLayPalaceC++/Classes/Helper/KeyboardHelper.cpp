#include "KeyboardHelper.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/JniHelper.h"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "KeyboardIOS.h"
#endif

USING_NS_CC;

static KeyboardHelper *_sharedKeyboardHelper = nullptr;
KeyboardHelper * KeyboardHelper::getInstance()
{
	if (!_sharedKeyboardHelper)
	{
		_sharedKeyboardHelper = new (std::nothrow) KeyboardHelper();
	}
	return _sharedKeyboardHelper;
}

void KeyboardHelper::copyText2ClipBoard(std::string textNeed2Copy) {
//	CCLog(("start copy to clip board with : " + textNeed2Copy).c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/Cocos2dxKeyboard"
		, "copyString2ClipBoard"
		, "(Ljava/lang/String;)V")){
//		CCLog("O lala 1");
		jstring stringArg1 = t.env->NewStringUTF(textNeed2Copy.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, stringArg1);
//		CCLog("O lala 2");
		t.env->DeleteLocalRef(stringArg1);
		t.env->DeleteLocalRef(t.classID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    KeyboardIOS::copyText2ClipBoard(textNeed2Copy);
#endif
}
