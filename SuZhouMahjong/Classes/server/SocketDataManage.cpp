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
    if (Director::getInstance()->getEventDispatcher()->isEnabled())
    {
        m_mutex.lock();
        if(!m_msgList.empty()){
            MsgHandler::getInstance()->handleMsg(m_msgList.front());
            m_msgList.pop();
        }
        m_mutex.unlock();
    }
    
}

void SocketDataManage::pushMsg(std::string msg){
    m_mutex.lock();
    trim((char*)msg.c_str());//去除首尾的换行符
    log("receive msg = %s",msg.c_str());
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

void  SocketDataManage::trim(char *str){
    char *start = str - 1;
    char *end = str;
    char *p = str;
    while(*p)
    {
        switch(*p)
        {
            case ' ':
            case '\r':
            case '\n':
            {
                if(start + 1==p)
                    start = p;
            }
                break;
            default:
                break;
        }
        ++p;
    }
    //现在来到了字符串的尾部 反向向前
    --p;
    ++start;
    if(*start == 0)
    {
        //已经到字符串的末尾了
        *str = 0 ;
        return;
    }
    end = p + 1;
    while(p > start)
    {
        switch(*p)
        {
            case ' ':
            case '\r':
            case '\n':
            {
                if(end - 1 == p)
                    end = p;
            }
                break;
            default:
                break;
        }
        --p;
    }
    memmove(str,start,end-start);
    *(str + (int)(size_t)end - (int)(size_t)start) = 0;
}
