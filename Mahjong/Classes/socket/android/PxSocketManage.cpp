#include "socket/android/PxSocketManage.h"
#include "socket/GameSocketManage.hpp"
#include "socket/android/native/CallAndroidSocket.hpp"

PxSocketManage* PxSocketManage::_instance = NULL;

std::string PxSocketManage::heartMsg = "";

PxSocketManage* PxSocketManage::getInstance() {
    if (NULL == _instance) {
        _instance = new PxSocketManage();
    }
    return _instance;
}

PxSocketManage::PxSocketManage() {
    // TODO
}


bool PxSocketManage::connectSocket(std::string host,int port){
   beatCount =0;
   return CallAndroidSocket::getInstance()->connectSocket(host, StringUtils::format("%d",port));
}


void PxSocketManage::startScoketBeat(std::string msg){
    heartMsg = msg;
    std::thread recvThread = std::thread(&PxSocketManage::sendHeartBeat, this);
    recvThread.detach();
}

void PxSocketManage::sendHeartBeat(){
    while (true) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        Sleep(5000);
#else
        sleep(5);
#endif
        if (beatCount >= kBeatLimit) {
            log("心跳超限,断开连接");
            GameSocketManage::getInstance()->disConnectSocket();
            return;
        } else {
            beatCount++;
        }
        sendScoketData(heartMsg);
    }
}

void PxSocketManage::sendScoketData(std::string msg){
    if(msg.size()>2)
        CallAndroidSocket::getInstance()->sendDataSever(msg);
}

void PxSocketManage::receiveScoketData(std::string msg){
    GameSocketManage::getInstance()->receiveScoketData(msg);
}

void PxSocketManage::resetBeatCount(){
    beatCount =0;
}
