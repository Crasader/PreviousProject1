#include "socket/android/PxSocketManage.h"
#include "socket/GameSocketManage.hpp"

ODSocketManage* ODSocketManage::_instance = NULL;

ODSocketManage* ODSocketManage::getInstance() {
    if (NULL == _instance) {
        _instance = new ODSocketManage();
    }
    return _instance;
}

ODSocketManage::ODSocketManage() {
    // TODO
}


bool ODSocketManage::connectSocket(std::string host,int port){

    return false;
}


void ODSocketManage::startScoketBeat(std::string msg){
    log("开启心跳");
}


void ODSocketManage::sendScoketData(std::string msg){
    log("send command = %s", msg.c_str());
}

void ODSocketManage::receiveScoketData(std::string msg){
    GameSocketManage::getInstance()->receiveScoketData(msg);
}

void ODSocketManage::resetBeatCount(){
    beatCount =0;
}

void ODSocketManage::disConnectSocket(){
    
}
