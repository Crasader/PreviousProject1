//
//  SocketDataBack.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/1/12.
//
//

#include "socket/android/native/SocketDataBack.h"
#include "socket/GameSocketManage.hpp"


SocketDataBack* SocketDataBack::_instance = 0;

SocketDataBack::SocketDataBack(){
    
}
SocketDataBack* SocketDataBack::getInstance(){
    if(_instance == 0){
        _instance = new SocketDataBack();
    }
    return _instance;
}

void SocketDataBack::dealDataCallBack(std::string data){
//    log("recieve data = %s",data.c_str());
    GameSocketManage::getInstance()->receiveScoketData(data);
}

void SocketDataBack::onDisconnected(){
    GameSocketManage::getInstance()->disConnectSocket();
}
