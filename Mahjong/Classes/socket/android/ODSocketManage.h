#ifndef __NETWORK_MANAGE_H__
#define __NETWORK_MANAGE_H__
#include "cocos2d.h"
#include <thread>
#include "socket/android/ODSocket/ODSocket.h"

USING_NS_CC;


class ODSocketManage : public Node{
public:
	static ODSocketManage* getInstance();
	void heartbeat();
	void sendMsg(std::string code);
private:
	ODSocketManage();
	static std::string allReciveInfo;
	static ODSocketManage* _instance;
	ODSocket socket;
	void sendHeartBeat();
	void receiveData();
	void connectServer();
	int getMsgLength(std::string);
	void parserJson();
};
#endif
