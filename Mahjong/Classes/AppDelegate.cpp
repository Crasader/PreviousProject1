#include "AppDelegate.h"
#include "audio/include/AudioEngine.h"
#include "mahjong/splash/LoadResource.hpp"
#include "mahjong/state/GameData.h"
#include "payment/android/CallAndroidMethod.h"
#include "server/NetworkManage.h"
#include "mahjong/audio/Audio.h"
#include "server/SocketDataManage.h"

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
    // run
    director->runWithScene(scene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    log("applicationDidEnterBackground");
    Director::getInstance()->stopAnimation();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getOutResumeCommand());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    log("applicationWillEnterForeground");
    Director::getInstance()->startAnimation();
    GAMEDATA::getInstance()->setWaitNetwork(true);
    SocketDataManage::getInstance()->cleanMsg();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //    if(resumeIndex == 0){
    //        resumeIndex++;
    //    }else{
    //         NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), GAMEDATA::getInstance()->getHsman(), GAMEDATA::getInstance()->getHstype(), GAMEDATA::getInstance()->getImsi(),GAMEDATA::getInstance()->getImei(),GAMEDATA::getInstance()->getAppVer(),true));
    //    }
    if(GAMEDATA::getInstance()->getIsInPay()){
        CallAndroidMethod::getInstance()->queryEventResult();
        GAMEDATA::getInstance()->setIsInPay(false);
    }
    AudioEngine::resumeAll();
#else
    //    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(), UserData::getInstance()->getPicture(), StringUtils::format("%d",UserData::getInstance()->getGender()), UserData::getInstance()->getNickName(), GAMEDATA::getInstance()->getHsman(), GAMEDATA::getInstance()->getHstype(), GAMEDATA::getInstance()->getImsi(),GAMEDATA::getInstance()->getImei(),GAMEDATA::getInstance()->getAppVer(),true));
#endif
    
}
