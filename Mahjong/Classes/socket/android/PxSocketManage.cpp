#include "socket/android/PxSocketManage.h"
#include "socket/GameSocketManage.hpp"
#include "socket/android/native/CallAndroidSocket.hpp"

PxSocketManage* PxSocketManage::_instance = NULL;

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


void PxSocketManage::startScoketBeat(std::string send,std::string recieve){
    CallAndroidSocket::getInstance()->startHeatBeat(send, recieve);
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

void PxSocketManage::disConnectSocket(){
    
}
