#ifndef __SOCKETDATAMANAGE_H__
#define __SOCKETDATAMANAGE_H__
#include "cocos2d.h"
USING_NS_CC;

class SocketDataManage : public Ref{
public:
	static SocketDataManage* getInstance();
	virtual bool init();
	virtual void update(float dt);
	void pushMsg(std::string msg);
    void cleanMsg();
private:
	static SocketDataManage* instance;
	CREATE_FUNC(SocketDataManage);
	std::mutex m_mutex;
	std::queue<std::string> m_msgList;
};
#endif
