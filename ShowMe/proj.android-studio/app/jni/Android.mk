LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../../Classes/Controller4Score.cpp \
                   ../../../Classes/EnemyController.cpp \
                   ../../../Classes/SoundController.cpp \
                   ../../../Classes/Helper4Calculate.cpp \
                   ../../../Classes/Helper4Sprite.cpp \
                   ../../../Classes/PhysicBodyAdjustRotation.cpp \
                   ../../../Classes/SpritePath.cpp \
                   ../../../Classes/ToggleButton.cpp \
                   ../../../Classes/BaseScene.cpp \
                   ../../../Classes/LevelOneScene.cpp \
                   ../../../Classes/SplashScene.cpp \
                   ../../../Classes/AppDelegate.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
