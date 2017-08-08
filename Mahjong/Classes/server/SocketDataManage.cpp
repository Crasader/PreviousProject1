#include "server/SocketDataManage.h"
#include "server/MsgHandler.h"


SocketDataManage* SocketDataManage::instance = nullptr;

SocketDataManage* SocketDataManage::getInstance(){
    if (nullptr == instance){
        instance = SocketDataManage::create();
        instance->retain();//添加计数,否则会有bug
    }
    return instance;
}

bool SocketDataManage::init(){
    Director::getInstance()->getScheduler()->schedule(schedule_selector(SocketDataManage::update), this, 0.016f, false);
    return true;
}

void SocketDataManage::update(float dt){
    m_mutex.lock();
    if(!m_msgList.empty()){
        MsgHandler::getInstance()->handleMsg(m_msgList.front());
        m_msgList.pop();
    }
    
    m_mutex.unlock();
}

void SocketDataManage::pushMsg(std::string msg){
    m_mutex.lock();
    m_msgList.push(msg);
    m_mutex.unlock();
}

void SocketDataManage::cleanMsg(){
    m_mutex.lock();
    while (!m_msgList.empty()) {
        m_msgList.pop();
    }
    m_mutex.unlock();
}
