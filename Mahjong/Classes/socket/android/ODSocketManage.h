#ifndef __ODSocketManage_H__
#define __ODSocketManage_H__

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
private:
	ODSocketManage();
	static std::string allReciveInfo;
    static std::string heartMsg;
	static ODSocketManage* _instance;
    static int beatCount;
    const int kBeatLimit = 3;
	ODSocket socket;
    void sendHeartBeat();
	void receiveData();
    void disConnectSocket();
	int getMsgLength(std::string);
};
#endif
