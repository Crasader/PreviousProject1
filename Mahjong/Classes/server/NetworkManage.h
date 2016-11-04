#ifndef __NETWORK_MANAGE_H__
#define __NETWORK_MANAGE_H__
#include "cocos2d.h"
#include <thread>
#include "socket/ODSocket.h"
#include "server/MsgConfig.h"
#include "server/CommandManage.h"

USING_NS_CC;


class NetworkManage : public Node{
public:
	static NetworkManage* getInstance();
	void heartbeat();
	void sendMsg(std::string code);
private:
	NetworkManage();
	static std::string allReciveInfo;
	static NetworkManage* _instance;
	ODSocket socket;
	void sendHeartBeat();
	void receiveData();
	void connectServer();
	int getMsgLength(std::string);
	void parserJson();
};
#endif
