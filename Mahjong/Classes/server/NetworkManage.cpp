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
    GameSocketManage::getInstance()->startSocketBeat(CommandManage::getInstance()->getHeartCommmand());
}

void NetworkManage::sendMsg(std::string code) {
    GameSocketManage::getInstance()->sendScoketData(code);
}

void NetworkManage::receiveMsg(std::string msg){
    SocketDataManage::getInstance()->pushMsg(msg);
}
