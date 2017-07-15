#include "GamePlugin.h"
using namespace cocos2d;


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/JniHelper.h"

extern "C" {

}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif

cocos2d::Image* GamePlugin::circleImage(unsigned char* data, size_t len)
{
	cocos2d::Image* newImg = nullptr;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/GamePlugin", "circleImage","([B)[B");
	if (result)
	{
		jbyteArray oldData = t.env->NewByteArray(len);
		t.env->SetByteArrayRegion(oldData, 0, len, reinterpret_cast<jbyte*>(data));
		jbyteArray newData = (jbyteArray)t.env->CallStaticObjectMethod(t.classID, t.methodID, oldData);
		if (newData != NULL) {
			jsize lengthOfArray = t.env->GetArrayLength(newData);
			jbyte* bufferPtr = t.env->GetByteArrayElements(newData, NULL);

			newImg = new Image();
			newImg->initWithImageData((unsigned char*)bufferPtr, lengthOfArray);

			t.env->ReleaseByteArrayElements(newData, bufferPtr, 0);
		}
		t.env->DeleteLocalRef(oldData);
		t.env->DeleteLocalRef(newData);
		t.env->DeleteLocalRef(t.classID);
	}
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#endif
	return newImg;
}
