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


const char* ip = "183.129.206.54";//线网服务器地址
const int port = 9999;//端口号
//const int port = 8080;//测试端口号
//const char* ip = "172.23.1.251";//测试地址
//const int port = 9999;//端口号


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
   return  CocoaSocketManage::getInstance()->connectSocket(ip,port);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    return ODSocketManage::getInstance()->connectSocket(ip,port);
#endif
}

void GameSocketManage::startSocketBeat(std::string msg){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->startScoketBeat(msg);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    ODSocketManage::getInstance()->startScoketBeat(msg);
#endif
}

void GameSocketManage::sendScoketData(std::string msg){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->sendScoketData(msg);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    ODSocketManage::getInstance()->sendScoketData(msg);
#endif
    
}
void GameSocketManage::receiveScoketData(std::string msg){
    NetworkManage::getInstance()->receiveMsg(msg);
}

void GameSocketManage::resetBeatCount(){
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC
    CocoaSocketManage::getInstance()->resetBeatCount();
#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    ODSocketManage::getInstance()->resetBeatCount();
#endif
}

void GameSocketManage::disConnectSocket(){
    NetworkManage::getInstance()->disConnectSocket();
}
