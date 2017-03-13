//
//  GameSocketManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#include "socket/GameSocketManage.hpp"
#include "socket/ios/CocoaSocketManage.h"
#include "socket/android/PxSocketManage.h"
#include "server/NetworkManage.h"
#include "mahjong/GameConfig.h"


GameSocketManage* GameSocketManage::_instance = NULL;

GameSocketManage* GameSocketManage::getInstance(){
    
    if (_instance == NULL){
        _instance = new GameSocketManage();
    }
    return _instance;
}

GameSocketManage::GameSocketManage(){
    
}

bool GameSocketManage::socketConnect(){
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    return  CocoaSocketManage::getInstance()->connectSocket(SERVER_ADDRESS,SERVER_PORT);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return PxSocketManage::getInstance()->connectSocket(SERVER_ADDRESS,SERVER_PORT);
#endif
}

void GameSocketManage::startSocketBeat(std::string send){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->startScoketBeat(send);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    PxSocketManage::getInstance()->startScoketBeat(send);
#endif
}

void GameSocketManage::sendScoketData(std::string msg){
    log("send msg = %s",msg.c_str());
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->sendScoketData(msg);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    PxSocketManage::getInstance()->sendScoketData(msg);
#endif
    
}
void GameSocketManage::receiveScoketData(std::string msg){
    //    log("receive msg = %s",msg.c_str());
    NetworkManage::getInstance()->receiveMsg(msg);
}

void GameSocketManage::resetBeatCount(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->resetBeatCount();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    PxSocketManage::getInstance()->resetBeatCount();
#endif
}

void GameSocketManage::disConnectSocket(){
     NetworkManage::getInstance()->disConnectSocket();    
}

void GameSocketManage::disConnectSelf(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->disConnectSelf();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    PxSocketManage::getInstance()->disConnectSelf();
#endif
}
