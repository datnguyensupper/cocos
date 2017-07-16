#include "PluginVungle.h"
using namespace cocos2d;
#if (CC_TARGET_PLATFORM != CC_PLATFORM_IOS)

static VungleListener* vungleListener = nullptr;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/JniHelper.h"

extern "C" {
    void Java_org_cocos2dx_cpp_plugins_PluginVungleNative_onAdStart(JNIEnv *env, jobject thiz)
    {
        if(vungleListener){
            vungleListener->onAdStart();
        }
    }
    void Java_org_cocos2dx_cpp_plugins_PluginVungleNative_onAdUnavailable(JNIEnv *env, jobject thiz, jstring reason)
    {
        if(vungleListener){
            auto result = env->GetStringUTFChars(reason, 0);
            vungleListener->onAdUnavailable(result);
            env->ReleaseStringUTFChars(reason, result);
        }
    }
    void Java_org_cocos2dx_cpp_plugins_PluginVungleNative_onAdEnd(JNIEnv *env, jobject thiz, jboolean wasSuccessfulView, jboolean wasCallToActionClicked)
    {
        if(vungleListener){
            vungleListener->onAdEnd(wasSuccessfulView);
        }
    }
    void Java_org_cocos2dx_cpp_plugins_PluginVungleNative_onAdPlayableChanged(JNIEnv *env, jobject thiz, jboolean isAdPlayable)
    {
        if(vungleListener){
            vungleListener->onAdPlayableChanged(isAdPlayable);
        }
    }
}
#endif
void PluginVungle::init(const std::string &appID) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/plugins/PluginVungleNative", "init","(Ljava/lang/String;)V");
    if (result)
    {
        jstring jString = t.env->NewStringUTF(appID.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jString);
        t.env->DeleteLocalRef(jString);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void PluginVungle::playAd() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/plugins/PluginVungleNative", "playAd","()V");
    if (result)
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void PluginVungle::playAdIncentivized(const std::string& userID) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/plugins/PluginVungleNative", "playAdIncentivized","(Ljava/lang/String;)V");
    if (result)
    {
        jstring jString = t.env->NewStringUTF(userID.c_str());
        t.env->CallStaticVoidMethod(t.classID, t.methodID, jString);
        t.env->DeleteLocalRef(jString);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

void PluginVungle::clearEventListeners() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/plugins/PluginVungleNative", "clearEventListeners","()V");
    if (result)
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
}

bool PluginVungle::isPlayable() {
    bool isPlayable = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo t;
    bool result = JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/plugins/PluginVungleNative", "isPlayable","()Z");
    if (result)
    {
        isPlayable = (bool)t.env->CallStaticBooleanMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
#endif
    return isPlayable;
}

void PluginVungle::setListener(VungleListener *listener) {
    vungleListener = listener;
}
#endif
