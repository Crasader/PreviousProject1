//
//  CocoaSocketManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#import "socket/ios/CocoaSocketManage.h"
#import "socket/ios/CocoaSocket.h"
#include "socket/GameSocketManage.hpp"

CocoaSocketManage* CocoaSocketManage::_instance = NULL;

CocoaSocketManage* CocoaSocketManage::getInstance(){
    if (_instance == NULL){
        _instance = new CocoaSocketManage();
    }
    return _instance;
}

CocoaSocketManage::CocoaSocketManage(){
    
}

void CocoaSocketManage::connectSocket(std::string host, int port){
    CocoaSocket *socket = [CocoaSocket sharedSocket];
    socket.port = port; // 端口
    socket.socketHost = [NSString stringWithUTF8String:host.c_str()]; //IP
    [socket startConnectSocket];
}

/**
 开始发送心跳
 **/
void CocoaSocketManage::startScoketBeat(std::string msg){
    CocoaSocket *socket = [CocoaSocket sharedSocket];
    [socket socketDidConnectBeginSendBeat:[NSString stringWithUTF8String:msg.c_str()]];
}

void CocoaSocketManage::sendScoketData(std::string msg){
    CocoaSocket *socket = [CocoaSocket sharedSocket];
    [socket socketWriteData:[NSString stringWithUTF8String:msg.c_str()]];
}

void CocoaSocketManage::receiveScoketData(std::string msg){
    GameSocketManage::getInstance()->receiveScoketData(msg);
}

void CocoaSocketManage::resetBeatCount(){
    CocoaSocket *socket = [CocoaSocket sharedSocket];
    [socket resetBeatCount];
}

void CocoaSocketManage::disConnectSocket(){
    GameSocketManage::getInstance()->disConnectSocket();
}

