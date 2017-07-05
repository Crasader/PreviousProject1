//
//  LoadResource.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/6.
//
//

#include "mahjong/splash/LoadResource.hpp"
#include "mahjong/splash/SplashScene.h"
#include "mahjong/common/audio/Audio.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/ios/CallIOSMethod.h"

Scene* LoadResource::createScene()
{
    auto scene = Scene::create();
    auto layer = LoadResource::create();
    scene->addChild(layer);
    return scene;
}


bool LoadResource::init(){
    if(!Layer::init()){
        return false;
    }
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    showHealthLayer();
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(NULL ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS||CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
    showNormalLayer();
    showLoadLayerAnim();
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(NULL ,path);
#endif
    
    return true;
}

void LoadResource::showHealthLayer(){
    auto health = Sprite::create("mainlogin/health.png");
    health->setPosition(640,360);
    addChild(health);
    NetworkManage::getInstance();//android 提前初始化连接
    health->runAction(Sequence::create(DelayTime::create(2.0f),CallFunc::create([=](){
        Director::getInstance()->replaceScene(TransitionFade::create(1.5f, SplashScene::createScene()));
    }),NULL));
}

void LoadResource::showNormalLayer(){
    auto loadBg = Sprite::create("mainlogin/splah_bg_.jpg");
    loadBg->setPosition(640,360);
    addChild(loadBg);
    
    auto desk = Sprite::create("mainlogin/login_desk.png");
    desk->setPosition(640,30);
    addChild(desk);
    
    auto loadProBg = Sprite::create("mainlogin/loading_pro_bg.png");
    loadProBg->setPosition(640,130);
    addChild(loadProBg);
    
    auto loadProgerss = ProgressTimer::create(Sprite::create("mainlogin/loading_pro_1.png"));
    loadProgerss->setPosition(640,130);
    addChild(loadProgerss,1);
    loadProgerss->setType(ProgressTimer::Type::BAR);
    loadProgerss->setBarChangeRate(Point(1,0));//设置进程条的变化速率
    loadProgerss->setType(ProgressTimer::Type::BAR);//设置进程条的类型
    loadProgerss->setMidpoint(Point(0,1));//设置进度的运动方向
    loadProgerss->runAction(Sequence::create(ProgressTo::create(2, 100),CallFunc::create([=](){
         Director::getInstance()->replaceScene(SplashScene::createScene());
        
    }),NULL));
}

void LoadResource::showLoadLayerAnim(){
    auto poker1 = Sprite::create("mainlogin/pai_img_3.png");
    poker1->setPosition(250,320);
    addChild(poker1,2);
    
    auto poker2 = Sprite::create("mainlogin/pai_img_2.png");
    poker2->setPosition(1050,308);
    addChild(poker2,2);
    
    auto poker3 = Sprite::create("mainlogin/pai_img_1.png");
    poker3->setPosition(1075,612);
    addChild(poker3,2);
}
