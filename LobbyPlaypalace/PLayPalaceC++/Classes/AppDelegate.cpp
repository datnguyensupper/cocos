#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "Configs.h"
#include "Scene/LoginScene.h"

//#ifdef SDKBOX_ENABLED
//#include "PluginIAP/PluginIAP.h"
//#endif
//#ifdef SDKBOX_ENABLED
//#include "PluginAdColony/PluginAdColony.h"
//#endif
//#ifdef SDKBOX_ENABLED
//#include "PluginFacebook/PluginFacebook.h"
//#endif

#include "Manager/PluginManager.h"
#include "Manager/DeviceManager.h"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 900);
static cocos2d::Size ipad2ResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size resolution = cocos2d::Size(1600, 900);

AppDelegate::AppDelegate()
{
#if IS_DEBUG
	/*test: turn on ipad resolution for game*/
	//resolution = ipad2ResolutionSize;
#endif
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
//#ifdef SDKBOX_ENABLED
//	sdkbox::IAP::init();
//#endif
//#ifdef SDKBOX_ENABLED
//	sdkbox::PluginAdColony::init();
//#endif
//#ifdef SDKBOX_ENABLED
//	sdkbox::PluginFacebook::init();
//#endif
	PluginManager::getInstance();
	DeviceManager::getInstance();
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("playpalace", cocos2d::Rect(0, 0, resolution.width, resolution.height));
#else
        glview = GLViewImpl::create("playpalace");
#endif
        director->setOpenGLView(glview);
    }
#if IS_DEBUG
	/*test: turn on display FPS*/
	director->setDisplayStats(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
	//director->setContentScaleFactor(MIN(frameSize.height / resolution.height, frameSize.width / resolution.width));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	if (DeviceManager::getInstance()->isLowRamDevice()) {
		director->setContentScaleFactor(1 / Configs::SCALE_RESOUCE_VALUE_LOW_RAM_DEVICE);
		//director->setContentScaleFactor(1.0 / Configs::SCALE_RESOUCE_VALUE);
	}else {
		director->setContentScaleFactor(1.0 / Configs::SCALE_RESOUCE_VALUE);
	}
	register_all_packages();
	if (DeviceManager::getInstance()->isLowRamDevice()) {
		FileUtils::getInstance()->addSearchPath("img80Percent");
	}else {
		FileUtils::getInstance()->addSearchPath("imgTiny");
	}
#else


#if IS_DEBUG
	director->setContentScaleFactor(1.0 / Configs::SCALE_RESOUCE_VALUE);
	register_all_packages();
	FileUtils::getInstance()->addSearchPath("img");
	/*test: test 80% resources*/
	/*director->setContentScaleFactor(80.0 / (Configs::SCALE_RESOUCE_VALUE*100.0));
	register_all_packages();
	FileUtils::getInstance()->addSearchPath("img80Percent");*/
#else
	director->setContentScaleFactor(1.0 / Configs::SCALE_RESOUCE_VALUE);
	register_all_packages();
	FileUtils::getInstance()->addSearchPath("img");
#endif

#endif

    // create a scene. it's an autorelease object
    auto scene = LoginScene::createScene("", "");

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
     //CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	//CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
