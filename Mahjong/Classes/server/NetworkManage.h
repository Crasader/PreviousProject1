#ifndef __NETWORK_MANAGE_H__
#define __NETWORK_MANAGE_H__

#include "cocos2d.h"
#include "server/CommandManage.h"
#include "server/MsgConfig.h"
USING_NS_CC;
class NetworkManage : public Node{
public:
    static NetworkManage* getInstance();
    void startSocketBeat(std::string send);
    void sendMsg(std::string code);
    void receiveMsg(std::string msg);
    void resetBeatCount();
    void disConnectSocket();
    bool reConnectSocket();
private:
    NetworkManage();
    static NetworkManage* _instance;
};
#endif
