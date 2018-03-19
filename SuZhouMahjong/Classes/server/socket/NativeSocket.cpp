//
//  NativeSocket.cpp
//  cocos2dx
//
//  Created by stone
//  Copyright (c) cocos2d-x. All rights reserved.
//

#include "server/socket/NativeSocket.hpp"
#include <memory.h>
#ifndef  WIN32
#include <unistd.h>
#endif // ! WIN32
#include "platform/CCCommon.h"
#include "cocos2d.h"
#include "base/CCScriptSupport.h"
#include "base/ZipUtils.h"
#include "network/HttpClient.h"
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
#include <netdb.h>
#include <sys/socket.h>
#endif
#include "server/NetworkManage.h"
using namespace cocos2d;
using namespace cocos2d::network;


NativeSocket* NativeSocket::_instance = NULL;

NativeSocket* NativeSocket::getInstance() {
    if (NULL == _instance) {
        _instance = new NativeSocket();
    }
    return _instance;
}

NativeSocket::NativeSocket()
{
	init();
}

void NativeSocket::init()
{
	m_tcpState = TCP_INITIALIZED;
	sequenceNum = 0;
}

NativeSocket:: ~NativeSocket(void)
{
	log("NativeSocket free ....");
	if (m_sockClient != INVALID_SOCKET) {
#ifdef WIN32
		closesocket(m_sockClient);
#else
		close((int)m_sockClient);
#endif
	}
	unregisterReceiveSchedule();
}

bool NativeSocket::creatConnect(const char* pszServerIP, int nServerPort)
{
	bool bKeepAlive = true;
	
#ifdef WIN32
	static int win32_initsizied = 0;
	
	if(!win32_initsizied){
		WSADATA wsaData;
		WORD version = MAKEWORD(2, 0);
		int ret = WSAStartup(version, &wsaData);//win sock start up
		if (ret != 0) {
			return false;
		}
		win32_initsizied = true;
	}
#endif
	
	//create socket
	m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_sockClient == INVALID_SOCKET) {
        log("INVALID SOCKET pos1...");
		closeSocket();
		return false;
	}
	
	// set keep alive
	if(bKeepAlive)
	{
		int        optval=1;
		if(setsockopt(m_sockClient, SOL_SOCKET, SO_KEEPALIVE, (char *) &optval, sizeof(optval)))
		{
            log("INVALID SOCKET pos2...");
			closeSocket();
			return false;
		}
	}
	
#ifdef WIN32
	DWORD nMode = 1;
	int nRes = ioctlsocket(m_sockClient, FIONBIO, &nMode);
	if (nRes == SOCKET_ERROR) {
        log("INVALID SOCKET pos3...");
		closeSocket();
		return false;
	}
#else
	//non block
	fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
	
#endif
	int ipLen = strlen(pszServerIP);
	char *pTempIp = (char *)pszServerIP;
	bool isHostName = false;
	for (int i = 0; i < ipLen; i++)
	{
		char ch = pTempIp[i];
		if (ch != '.' && ( ch <'0' || ch > '9'))
		{
			isHostName = true;
			break;
		}
	}
	
	if (isHostName)
	{
		
		struct hostent *host = gethostbyname(pszServerIP);
		if (!host){
            log("INVALID SOCKET pos4...");
			closeSocket();
			return false;
		}
		
		for (int i = 0; host->h_addr_list[i]; i++){
			pszServerIP = inet_ntoa(*(struct in_addr*)host->h_addr_list[i]);
			log("IP addr %d: %s\n", i + 1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
		}
		
	}
	
	unsigned int serveraddr = inet_addr(pszServerIP);
	if (serveraddr == INADDR_NONE)    //check ip
	{
        log("INVALID SOCKET pos5...");
		closeSocket();
		return false;
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	//start
	void* svraddr = nullptr;
	int error = -1, svraddr_len;
	bool ret = true;
	struct sockaddr_in svraddr_4;
	struct sockaddr_in6 svraddr_6;
	
	//获取网络协议
	struct addrinfo *result;
	error = getaddrinfo(pszServerIP, NULL, NULL, &result);
	const struct sockaddr *sa = result->ai_addr;
	socklen_t maxlen = 128;
	switch (sa->sa_family) {
		case AF_INET://ipv4
			if ((m_sockClient = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
				perror("socket create failed");
				ret = false;
				break;
			}
			
			if (inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),(char *)pszServerIP, maxlen) < (void*)0){
				perror(pszServerIP);
				ret = false;
				break;
			}
			svraddr_4.sin_family = AF_INET;
			svraddr_4.sin_addr.s_addr = inet_addr(pszServerIP);
			svraddr_4.sin_port = htons(nServerPort);
			svraddr_len = sizeof(svraddr_4);
			svraddr = &svraddr_4;
			break;
		case AF_INET6://ipv6
			if ((m_sockClient = socket(AF_INET6, SOCK_STREAM, 0)) < 0) {
				perror("socket create failed");
				ret = false;
				break;
			}
			inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),(char *)pszServerIP, maxlen);
			
			printf("socket created ipv6/n");
			
			bzero(&svraddr_6, sizeof(svraddr_6));
			svraddr_6.sin6_family = AF_INET6;
			svraddr_6.sin6_port = htons(nServerPort);
			if (inet_pton(AF_INET6, pszServerIP, &svraddr_6.sin6_addr) < 0) {
				perror(pszServerIP);
				ret = false;
				break;
			}
			svraddr_len = sizeof(svraddr_6);
			svraddr = &svraddr_6;
			break;
			
		default:
			printf("Unknown AF\ns");
			ret = false;
	}
	freeaddrinfo(result);
	if (!ret)
	{
		fprintf(stderr, "Cannot Connect the server!n");
		return false;
	}
	//end
#else
	sockaddr_in    addr_in;
	memset((void *)&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(nServerPort);
	addr_in.sin_addr.s_addr = serveraddr;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	if(connect(m_sockClient, (struct sockaddr*)svraddr, svraddr_len) == SOCKET_ERROR)
#else
		if(connect(m_sockClient, (sockaddr *)&addr_in, sizeof(addr_in)) == SOCKET_ERROR)
#endif
		{
			if (hasError()) {
                log("INVALID SOCKET pos6...");
				closeSocket();
				return false;
			}
			else    // WSAWOLDBLOCK
			{
				timeval timeout;
				timeout.tv_sec    = 1;
				timeout.tv_usec    = 0;
				fd_set writeset, exceptset;
				FD_ZERO(&writeset);
				FD_ZERO(&exceptset);
				FD_SET(m_sockClient, &writeset);
				FD_SET(m_sockClient, &exceptset);
				
				int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
				if (ret < 0) {
                    log("INVALID SOCKET pos7...");
					closeSocket();
					return false;
				} else    // ret > 0
				{
					ret = FD_ISSET(m_sockClient, &exceptset);
					if(ret)        // or (!FD_ISSET(m_sockClient, &writeset)
					{
						log("INVALID SOCKET pos8...");
                        closeSocket();
						return false;
					}
				}
			}
		}
	
	struct linger so_linger;
	so_linger.l_onoff = 0;
	so_linger.l_linger = 500;
	setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));
	
	m_tcpState = TCP_CONNECTING;
    registerReceiveSchedule();
	return true;
}




bool NativeSocket::sendMsg(const char * data)
{
    int cursended;
    int sended = 0;
    int toSend = (int)strlen(data);
	while (sended < toSend) {
		cursended = (int)send(m_sockClient, (const char*)data, toSend - sended, 0);
		if (cursended < 0) {
            log("INVALID SOCKET pos8...");
			closeSocket();
			return false;
		}
		sended += cursended;
	}
	return true;
}

void NativeSocket::closeSocket()
{
	log("closeSocket... -_-...");
	if (m_sockClient != INVALID_SOCKET) {
#ifdef WIN32
		closesocket(m_sockClient);
#else
		fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
		close((int)m_sockClient);
#endif
	}
	
	m_tcpState = TCP_CLOSED;
	
	m_sockClient = INVALID_SOCKET;
	
    NetworkManage::getInstance()->disConnectSocket();
	unregisterReceiveSchedule();
	
}

void NativeSocket::selectFunc(float f){
	timeval timeout;
	timeout.tv_sec    = 0;
	timeout.tv_usec    = 0;
	fd_set writeset, readset,exceptset;
	FD_ZERO(&writeset);
	FD_ZERO(&exceptset);
	FD_ZERO(&readset);
	FD_SET(m_sockClient, &writeset);
	FD_SET(m_sockClient, &exceptset);
	FD_SET(m_sockClient, &readset);
	
	int ret = select(FD_SETSIZE, &readset, &writeset, &exceptset, &timeout);
	
	if (ret < 0) {
        log("INVALID SOCKET pos9...");
		closeSocket();
		return ;
	} else
	{
		ret = FD_ISSET(m_sockClient, &exceptset);
		if(ret)
		{
            log("INVALID SOCKET pos10...");
			closeSocket();
			return ;
		}
		
		if (FD_ISSET(m_sockClient, &readset)) {
            memset(rawdata,0,sizeof(rawdata)/sizeof(char));//清空char数组
            int readsize = (int)recv(m_sockClient, (char*)rawdata, CACHE_SIZE, 0);
            if (readsize > 0) {
                std::string append = (char*)rawdata;
                receiveData.append(append);
                while (receiveData.size() > 0) {
                    const char* mark = "\r\n";//和服务端的约定,每条协议已"\r\n"结尾
                    long pos = receiveData.find(mark);
                    if (pos >= 0) {
                        std::string msg = receiveData.substr(0, pos);
                        receiveData = receiveData.substr(pos+1, receiveData.size());
                        if (msg.size() > 0 ) {
                            NetworkManage::getInstance()->receiveMsg(msg);
                        }
                    }
                    else {
                        break;
                    }
                }
            }else {
                log("INVALID SOCKET pos11...");
                closeSocket();
				return ;
			}
		}
		
		if (FD_ISSET(m_sockClient, &writeset)) {
			
			if (m_tcpState == TCP_CONNECTING) {
				
				m_tcpState = TCP_CONNECTED;
			}
		}
		
	}
	
}

void NativeSocket::registerReceiveSchedule(){
	unregisterReceiveSchedule();
	Director::getInstance()->getScheduler()->schedule(schedule_selector(NativeSocket::selectFunc),this,0.1,false);
}

void NativeSocket::unregisterReceiveSchedule(){
	Director::getInstance()->getScheduler()->unschedule(schedule_selector(NativeSocket::selectFunc),this);
}

bool NativeSocket::hasError(){
#ifdef WIN32
	int err = WSAGetLastError();
	if(err != WSAEWOULDBLOCK) {
#else
		int err = errno;
		if(err != EINPROGRESS && err != EAGAIN) {
#endif
			return true;
		}
		
		return false;
	}
	
