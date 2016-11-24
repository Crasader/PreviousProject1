#include "AppDelegate.h"
#include "audio/include/AudioEngine.h"
#include "game/mahjong/splash/LoadResource.hpp"
#include "game/mahjong/state/GameData.h"
#include "payment/android/CallAndroidMethod.h"
#include "server/NetworkManage.h"
#include "game/utils/Audio.h"

//#include "game/mahjong/result/ResultScene.hpp"

USING_NS_CC;
using namespace experimental;

AppDelegate::AppDelegate() {
    
}

AppDelegate::~AppDelegate()
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    resumeIndex =0;
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
    
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::create("Mahjong");
        director->setOpenGLView(glview);
    }
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    glview->setFrameSize(1280, 720);
    glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_MAC)
    glview->setFrameSize(960, 540);
    glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::EXACT_FIT);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Size visibleSize = Director::getInstance()->getVisibleSize();
    glview->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
#endif
    
    // turn on display FPS
    //    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    // create a scene. it's an autorelease object
    auto scene = LoadResource::createScene();
    
// auto scene = ResultScene::createScene(0);
    // run
    director->runWithScene(scene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    log("applicationDidEnterBackground");
    Director::getInstance()->stopAnimation();
    GAMEDATA::getInstance()->setNeedShowLayer(true);
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    log("applicationWillEnterForeground");
    Director::getInstance()->startAnimation();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(resumeIndex == 0){
        resumeIndex++;
    }else{
        if("" != CommandManage::getInstance()->getOnResumeCommand()){
            NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOnResumeCommand());
        }
    }
    if(GAMEDATA::getInstance()->getIsInPay()){
        CallAndroidMethod::getInstance()->queryEventResult();
        GAMEDATA::getInstance()->setIsInPay(false);
    }
#else
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOnResumeCommand());
    
#endif
    
}
