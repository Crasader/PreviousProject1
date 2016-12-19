#include "socket/android/ODSocketManage.h"
#include "socket/GameSocketManage.hpp"

ODSocketManage* ODSocketManage::_instance = NULL;
std::string ODSocketManage::allReciveInfo;
std::string ODSocketManage::heartMsg;

ODSocketManage* ODSocketManage::getInstance() {
    if (NULL == _instance) {
        _instance = new ODSocketManage();
    }
    return _instance;
}

ODSocketManage::ODSocketManage() {
    // TODO
}


void ODSocketManage::connectSocket(std::string host, int port){
    try {
        // ODSocket socket;
        socket.Init();
        socket.Create(AF_INET, SOCK_STREAM, 0);
        
        bool result = socket.Connect(host.c_str(), port);
        int retryTimes = 0;
        while (result == false && retryTimes < 3) {
            log("尝试重新连接...");
            result = socket.Connect(host.c_str(), port);
            retryTimes++;
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32)
            Sleep(1000);
#else
            sleep(1);
#endif
        }
        if (result) {
            log("成功连接到服务端,开启数据接收");
            std::thread recvThread = std::thread(&ODSocketManage::receiveData,
                                                 this);
            recvThread.detach();
        }
        else {
            log("连接服务端失败 = %d", result);
            return;
        }
    }
    catch (char* str) {
        log("Socket 连接出错");
    }
}


void ODSocketManage::startScoketBeat(std::string msg){
    heartMsg = msg;
    std::thread recvThread = std::thread(&ODSocketManage::sendHeartBeat, this);
    recvThread.detach();
}


void ODSocketManage::sendScoketData(std::string msg){
    log("send command = %s", msg.c_str());
    int sendResult = socket.Send(msg.c_str(), getMsgLength(msg));
    if (sendResult < 0) {
        log("无法向服务端发送消息");
        socket.Close();
        log("重新连接网络");
        disConnectSocket();
    }
}

void ODSocketManage::receiveScoketData(std::string msg){
    GameSocketManage::getInstance()->receiveScoketData(msg);
}

void ODSocketManage::resetBeatCount(){
    
}

void ODSocketManage::disConnectSocket(){
    GameSocketManage::getInstance()->disConnectSocket();
}


void ODSocketManage::sendHeartBeat() {
    while (true) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        Sleep(5000);
#else
        sleep(5);
#endif
        sendScoketData(heartMsg);
    }
}

void ODSocketManage::receiveData() {
    while (true) {
        char data[3 * 1024] = "";
        int result = socket.Recv(data, sizeof(data), 0);
        allReciveInfo += data;
        while (allReciveInfo.size() > 0) {
            const char* mark1 = "PX+";
            const char* mark2 = "+PX";
            long pos1 = allReciveInfo.find(mark1);
            long pos2 = allReciveInfo.find(mark2);
            if (pos1 >= 0 && pos2 >= 0) {
                std::string msg = allReciveInfo.substr(pos1 + 3, pos2 - 3);
                allReciveInfo = allReciveInfo.substr(pos2 + 3, allReciveInfo.size());
                if (msg.size() > 0 ) {
                    log("server msg = %s", msg.c_str());
                    receiveScoketData(msg);
                }
            }
            else {
                log("receiveData break");
                break;
            }
        }
        if (result <= 0) {
            log("已经与服务端失去连接");
            break;
        }
    }
    log("socket 连接关闭");
    socket.Close();
}

int ODSocketManage::getMsgLength(std::string str) {
    return (int)str.length();
}
