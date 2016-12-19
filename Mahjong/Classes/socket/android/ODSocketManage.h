#ifndef __NETWORK_MANAGE_H__
#define __NETWORK_MANAGE_H__
#include "cocos2d.h"
#include <thread>
#include "socket/android/ODSocket/ODSocket.h"

USING_NS_CC;


class ODSocketManage : public Node{
public:
	static ODSocketManage* getInstance();
    void connectSocket(std::string host, int port);
    void startScoketBeat(std::string msg);
    void sendScoketData(std::string msg);
    void receiveScoketData(std::string msg);
    void resetBeatCount();
    void disConnectSocket();
private:
	ODSocketManage();
	static std::string allReciveInfo;
    static std::string heartMsg;
	static ODSocketManage* _instance;
	ODSocket socket;
    void sendHeartBeat();
	void receiveData();
	int getMsgLength(std::string);
};
#endif
