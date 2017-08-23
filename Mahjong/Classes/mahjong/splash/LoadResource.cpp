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
    CallAndroidMethod::getInstance()->updateClientAppVersion();
    showHealthLayer();
    std::string path =StringUtils::format("%s/mahjong_screen_shot.png",CallAndroidMethod::getInstance()->getSdCardDir().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(NULL ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    CallIOSMethod::getInstance()->updateClientAppVersion();
    showNormalLayer();
    showLoadLayerAnim();
    std::string path =StringUtils::format("%smahjong_screen_shot.png",FileUtils::getInstance()->getWritablePath().c_str());
    log("screenShot path = %s",path.c_str());
    utils::captureScreen(NULL ,path);
#endif
#if(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
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
    auto loadBg = Sprite::create("common/shang_hai_bg.jpg");
    loadBg->setPosition(640,360);
    addChild(loadBg);
    
    auto log = Sprite::create("mainlogin/logo.png");
    log->setPosition(640,530);
    addChild(log);
    
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
    loadProgerss->runAction(Sequence::create(ProgressFromTo::create(2.1,12,100),CallFunc::create([=](){
         Director::getInstance()->replaceScene(SplashScene::createScene());
    }),NULL));
    
    auto dice = Sprite::create("mainlogin/game_loading_1.png");
    dice->setPosition(280,130);
    addChild(dice,2);
    showDiceAnim(dice);
}

void LoadResource::showLoadLayerAnim(){
    auto poker1 = Sprite::create("mainlogin/pai_img_3.png");
    poker1->setPosition(250,320);
    addChild(poker1,2);
    poker1->runAction(Repeat::create(Sequence::create(MoveTo::create(0.8,Point(250,300)),MoveTo::create(0.8,Point(250,320)),NULL), CC_REPEAT_FOREVER));
    
    auto poker2 = Sprite::create("mainlogin/pai_img_2.png");
    poker2->setPosition(1050,308);
    addChild(poker2,2);
    poker2->runAction(Repeat::create(Sequence::create(MoveTo::create(0.9,Point(1050,280)),MoveTo::create(0.9,Point(1050,308)),NULL), CC_REPEAT_FOREVER));
    
    auto poker3 = Sprite::create("mainlogin/pai_img_1.png");
    poker3->setPosition(1075,612);
    addChild(poker3,2);
    poker3->runAction(Repeat::create(Sequence::create(MoveTo::create(0.7,Point(1075,595)),MoveTo::create(0.7,Point(1075,612)),NULL), CC_REPEAT_FOREVER));
    
    auto hua1 = Sprite::create("mainlogin/flower_1.png");
    hua1->setPosition(270,730);
    addChild(hua1);
    hua1->runAction(Spawn::create(MoveTo::create(2,Point(960,420)),FadeTo::create(2,0),NULL));
    
    auto hua2 = Sprite::create("mainlogin/flower_2.png");
    hua2->setPosition(-10,420);
    addChild(hua2);
    hua2->runAction(Spawn::create(MoveTo::create(2,Point(480,200)),FadeTo::create(2,0),NULL));
    
    auto hua3 = Sprite::create("mainlogin/flower_2.png");
    hua3->setPosition(500,730);
    addChild(hua3);
    hua3->runAction(Spawn::create(MoveTo::create(2,Point(1060,510)),FadeTo::create(2,0),NULL));
    
    auto hua4 = Sprite::create("mainlogin/flower_3.png");
    hua4->setPosition(-10,260);
    addChild(hua4);
    hua4->runAction(Spawn::create(MoveTo::create(2,Point(770,110)),FadeTo::create(2,0),NULL));
}


void LoadResource::showDiceAnim(Sprite* spr){
    auto animation = Animation::create();
    for( int i=1;i<17;i++)
    {
        std::string imageName = StringUtils::format("mainlogin/game_loading_%d.png",i);
        animation->addSpriteFrameWithFile(imageName);
    }
    // should last 1 seconds. And there are 24 frames.
    animation->setDelayPerUnit(3.0f / 24.0f);
    animation->setRestoreOriginalFrame(false);
    auto action = Animate::create(animation);
    spr->runAction(Spawn::create(action, MoveTo::create(2.0f,Point(1120,130)),NULL));
}

