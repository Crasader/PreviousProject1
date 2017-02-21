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
    Director::getInstance()->getScheduler()->schedule(schedule_selector(PxSocketManage::sendHeartBeat), this, 5.0f,CC_REPEAT_FOREVER, 0, false);
}

void PxSocketManage::sendHeartBeat(float dt){
    if (beatCount >= kBeatLimit) {
        log("心跳超限,断开连接");
        beatCount =0;
        GameSocketManage::getInstance()->disConnectSocket();
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(PxSocketManage::sendHeartBeat), this);
        return;
    } else {
        beatCount++;
    }
    sendScoketData(heartMsg);
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
