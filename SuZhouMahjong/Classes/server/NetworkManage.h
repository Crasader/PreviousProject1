#ifndef __NETWORK_MANAGE_H__
#define __NETWORK_MANAGE_H__

#include "cocos2d.h"
#include "server/CommandManage.h"
#include "server/MsgConfig.h"
USING_NS_CC;
class NetworkManage : public Node{
public:
    static NetworkManage* getInstance();
    bool connect();
    bool sendMsg(std::string code);
    void receiveMsg(std::string msg);
    void disConnectSocket();
    void startSocketBeat(std::string send);
    void sendHeartBeat(float dt);
    void resetBeatCount();
    void changeSocketAddress(std::string address);
private:
    NetworkManage();
    static NetworkManage* _instance;
    int beatCount;
    std::string heartMsg;
    const int kBeatLimit = 3;
};
#endif
