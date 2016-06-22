#include "MsgHandler.h"
#include "SocketDataManage.h"

SocketDataManage* SocketDataManage::instance = nullptr;

SocketDataManage* SocketDataManage::getInstance(){
	if (nullptr == instance){
		instance = SocketDataManage::create();
		instance->retain();//不加这个会有bug
	}
	return instance;
}

bool SocketDataManage::init(){
	Director::getInstance()->getScheduler()->schedule(schedule_selector(SocketDataManage::update), this, 0.108f, false);
	return true;
}

void SocketDataManage::update(float dt){
	m_mutex.lock();
	
	for (auto value : m_msgList){
		//log("server msg : %s", value.c_str());
		MsgHandler::getInstance()->handleMsg(value);
	}
	m_msgList.clear();
	m_mutex.unlock();
}

void SocketDataManage::pushMsg(std::string msg){
	m_mutex.lock();
	m_msgList.push_back(msg);
	m_mutex.unlock();
}