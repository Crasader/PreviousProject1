//
//  NativeSocket.hpp
//  cocos2dx
//
//  Created by stone
//  Copyright (c) cocos2d-x. All rights reserved.
//

#ifndef NativeSocket_hpp
#define NativeSocket_hpp
#include <functional>
#ifdef WIN32
#include <windows.h>
#include <WinSock.h>
#include <process.h>
#pragma comment( lib, "ws2_32.lib" )
#else
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "base/CCScriptSupport.h"

#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#endif

using namespace cocos2d;
#include "cocos2d.h"

enum {
    //! Default tag
    TCP_INITIALIZED = 0,
    TCP_CONNECTING ,
    TCP_CONNECTED ,
    TCP_CLOSED
};


#define CACHE_SIZE 1024 * 100

class  NativeSocket : public Ref
{
public:
    NativeSocket(void);
    virtual ~NativeSocket(void);
    static NativeSocket* getInstance();
    bool creatConnect(const char* pszServerIP, int nServerPort);
    bool sendMsg(const char * data);
    void closeSocket();
    bool hasError();
    bool checkState();
private:
    static NativeSocket* _instance;
    SOCKET m_sockClient;
    int m_tcpState;
    unsigned int sequenceNum;
    void init();
    void registerReceiveSchedule();
    void unregisterReceiveSchedule();
    void selectFunc(float f);
    unsigned char rawdata[CACHE_SIZE];
    std::string receiveData;
};

#endif /* NativeSocket_hpp */
