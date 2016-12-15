//
//  GameSocketManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#include "socket/GameSocketManage.hpp"
#import "socket/ios/CocoaSocketManage.h"
#include "server/NetworkManage.h"

const char* ip = "172.23.1.251";
//const char* ip = "183.129.206.54";
//const char* ip = "127.0.0.1";
const int port = 9999;

GameSocketManage* GameSocketManage::_instance = NULL;

GameSocketManage* GameSocketManage::getInstance(){
    
    if (_instance == NULL){
        _instance = new GameSocketManage();
    }
    return _instance;
}

GameSocketManage::GameSocketManage(){
    
}

void GameSocketManage::socketConnect(){
    
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->connectSocket(ip,port);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
#endif
}

void GameSocketManage::startSocketBeat(std::string msg){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->startScoketBeat(msg);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
#endif
}

void GameSocketManage::sendScoketData(std::string msg){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->sendScoketData(msg);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    
#endif
    
}
void GameSocketManage::receiveScoketData(std::string msg){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    NetworkManage::getInstance()->receiveMsg(msg);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    return "";
#endif
}

void GameSocketManage::resetBeatCount(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->resetBeatCount();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    //    return "";
#endif
}

void GameSocketManage::disConnectSocket(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    NetworkManage::getInstance()->disConnectSocket();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    //    return "";
#endif
}
