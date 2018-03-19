#include "server/NetworkManage.h"
#include "server/SocketDataManage.h"
#include "server/socket/NativeSocket.hpp"
#include "mahjong/common/state/GameData.h"
#include "mahjong/GameConfig.h"


NetworkManage* NetworkManage::_instance = NULL;

NetworkManage* NetworkManage::getInstance() {
    if (NULL == _instance) {
        _instance = new NetworkManage();
    }
    return _instance;
}

NetworkManage::NetworkManage() {
    
}

bool NetworkManage::connect() {
    beatCount =0 ;
    return NativeSocket::getInstance()->creatConnect(SERVER_ADDRESS, SERVER_PORT);
}

void NetworkManage::changeSocketAddress(std::string address){
    //TODO
}

bool NetworkManage::sendMsg(std::string code) {
    if(code.size()>0&&code != ""){
        log("send msg : %s",code.c_str());
        return NativeSocket::getInstance()->sendMsg(code.c_str());
    }
    return false;
}

void NetworkManage::startSocketBeat(std::string send){
    heartMsg = send;
    Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkManage::sendHeartBeat), this);
    Director::getInstance()->getScheduler()->schedule(schedule_selector(NetworkManage::sendHeartBeat), this, 5.0f,CC_REPEAT_FOREVER, 0, false);
}

void NetworkManage::sendHeartBeat(float dt){
    if (beatCount >= kBeatLimit) {
        log("心跳超限,断开连接");
        beatCount =0;
        NativeSocket::getInstance()->closeSocket();
        Director::getInstance()->getScheduler()->unschedule(schedule_selector(NetworkManage::sendHeartBeat), this);
        return;
    } else {
        beatCount++;
    }
    sendMsg(heartMsg);
}

void NetworkManage::receiveMsg(std::string msg){
    SocketDataManage::getInstance()->pushMsg(msg);
}

void NetworkManage::resetBeatCount(){
    beatCount = 0;
}

void NetworkManage::disConnectSocket(){
    Director ::getInstance ()-> getScheduler()-> performFunctionInCocosThread ([&, this ]{
        //可以执行UI线程
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_NETWORK_BREAK_INFO);
    });
}
