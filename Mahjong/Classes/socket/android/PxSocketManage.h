#ifndef __ODSocketManage_H__
#define __ODSocketManage_H__

#include "cocos2d.h"
#include <thread>
#include <unistd.h>
USING_NS_CC;


class PxSocketManage : public Node{
public:
	static PxSocketManage* getInstance();
    bool connectSocket(std::string host, int port);
    void startScoketBeat(std::string send);
    void sendScoketData(std::string msg);
    void receiveScoketData(std::string msg);
    void resetBeatCount();
    void disConnectSelf();
private:
	PxSocketManage();
    int beatCount;
    static std::string heartMsg;
    const int kBeatLimit = 3;
    void sendHeartBeat(float dt);
	static PxSocketManage* _instance;
};
#endif
