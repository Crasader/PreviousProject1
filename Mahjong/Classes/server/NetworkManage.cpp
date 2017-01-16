#include "server/NetworkManage.h"
#include "server/SocketDataManage.h"
#include "mahjong/state/GameData.h"
#include "socket/GameSocketManage.hpp"

NetworkManage* NetworkManage::_instance = NULL;

NetworkManage* NetworkManage::getInstance() {
    if (NULL == _instance) {
        _instance = new NetworkManage();
    }
    return _instance;
}

NetworkManage::NetworkManage() {
    GameSocketManage::getInstance()->socketConnect();
}

void NetworkManage::sendMsg(std::string code) {
    if(code.size()>0&&code != ""){
        GameSocketManage::getInstance()->sendScoketData(code);
    }
}

void NetworkManage::startSocketBeat(std::string send){
    GameSocketManage::getInstance()->startSocketBeat(send);
}

void NetworkManage::receiveMsg(std::string msg){
    SocketDataManage::getInstance()->pushMsg(msg);
}

void NetworkManage::resetBeatCount(){
    GameSocketManage::getInstance()->resetBeatCount();
}

void NetworkManage::disConnectSocket(){
    GAMEDATA::getInstance()->setWaitNetwork(true);
}

bool NetworkManage::reConnectSocket(){
   return  GameSocketManage::getInstance()->socketConnect();
}
