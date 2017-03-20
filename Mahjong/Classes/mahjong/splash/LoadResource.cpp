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
#include "payment/android/CallAndroidMethod.h"
#include "payment/ios/IOSBridge.h"

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
    showHealthLayer();
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    showHealthLayer();
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(NULL ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    showNormalLayer();
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::sharedFileUtils()->getWritablePath().c_str());
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
    
    auto dragon = Sprite::create("mainlogin/loading_dragon.png");
    dragon->setPosition(640,360);
    addChild(dragon);

    auto mahjong = Sprite::create("mainlogin/feipai.png");
    mahjong->setPosition(640,360);
    addChild(mahjong);
    
    auto girl = Sprite::create("mainlogin/loading_image.png");
    girl->setPosition(640,360);
    addChild(girl);
    
    auto loadBotBg = Sprite::create("mainlogin/loading_bot_bg.png");
    loadBotBg->setPosition(640,360);
    addChild(loadBotBg);
   
    for(int i=1;i<11;i++){
        auto loadText = Sprite::create();
        loadText->setTag(100+i);
        int index =0;
        if(i>=8){
            index = 8;
        }else{
            index = i;
        }
        loadText->setTexture(StringUtils::format("mainlogin/loading_text_%d.png",index));
        loadText->setPosition(120+i*45,130);
        addChild(loadText);
    }
    
    auto loadProBg = Sprite::create("mainlogin/loading_pro_bg.png");
    loadProBg->setPosition(640,60);
    addChild(loadProBg);
    
    auto loadProgerss = ProgressTimer::create(Sprite::create("mainlogin/loading_pro_1.png"));
    loadProgerss->setPosition(640,60);
     addChild(loadProgerss,1);
    loadProgerss->setType(ProgressTimer::Type::BAR);
    loadProgerss->setBarChangeRate(Point(1,0));//设置进程条的变化速率
    loadProgerss->setType(ProgressTimer::Type::BAR);//设置进程条的类型
    loadProgerss->setMidpoint(Point(0,1));//设置进度的运动方向
    loadProgerss->runAction(Sequence::create(ProgressTo::create(2, 100),CallFunc::create([=](){
        Director::getInstance()->replaceScene(SplashScene::createScene());
    }),NULL));
}

