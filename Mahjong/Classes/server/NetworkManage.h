#ifndef __NETWORK_MANAGE_H__
#define __NETWORK_MANAGE_H__
#include "cocos2d.h"
#include <thread>
#include "server/MsgConfig.h"
#include "server/CommandManage.h"

USING_NS_CC;


class NetworkManage : public Node{
public:
    static NetworkManage* getInstance();
    void startSocketBeat(std::string msg);
    void sendMsg(std::string code);
    void receiveMsg(std::string msg);
    void resetBeatCount();
    void disConnectSocket();
    void reConnectSocket();
private:
    NetworkManage();
    static NetworkManage* _instance;
};
#endif
