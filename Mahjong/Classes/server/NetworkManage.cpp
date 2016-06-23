#include "server/NetworkManage.h"
#include "server/SocketDataManage.h"

NetworkManage* NetworkManage::_instance = NULL;
std::string NetworkManage::allReciveInfo;

NetworkManage* NetworkManage::getInstance() {
    if (NULL == _instance) {
        _instance = new NetworkManage();
    }
    return _instance;
}

NetworkManage::NetworkManage() {
    connectServer();
}

void NetworkManage::connectServer() {
    try {
        // ODSocket socket;
        socket.Init();
        socket.Create(AF_INET, SOCK_STREAM, 0);
//        const char* ip = "172.23.1.251";
        const char* ip = "183.129.206.54";
        int port = 9999;
        bool result = socket.Connect(ip, port);
        int retryTimes = 0;
        while (result == false && retryTimes < 3) {
            log("retry connecting...");
            result = socket.Connect(ip, port);
            retryTimes++;
#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32)
            Sleep(1000);
#else
            sleep(1);
#endif
        }
        if (result) {
            //            socket.Bind(port);
            log("connect to server success!");
            std::thread recvThread = std::thread(&NetworkManage::receiveData,
                                                 this);
            recvThread.detach();
        }
        else {
            log("can not connect to server result = %d", result);
            return;
        }
    }
    catch (char* str) {
        log("connect server error");
    }
}

void NetworkManage::sendMsg(std::string code) {
    log("send command = %s", code.c_str());
    int sendResult = socket.Send(code.c_str(), getMsgLength(code));
    if (sendResult < 0) {
        log("scoket connect again ...(^_^)");
        //connectServer();
    }
}

void NetworkManage::heartbeat() {
    std::thread recvThread = std::thread(&NetworkManage::sendHeartBeat, this);
    recvThread.detach();
}

void NetworkManage::sendHeartBeat() {
    while (true) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        Sleep(5000);
#else
        sleep(5);
#endif
        sendMsg(CommandManage::getInstance()->getHeartCommmand());
    }
    
}

void NetworkManage::receiveData() {
    while (true) {
        char data[3 * 1024] = "";
        int result = socket.Recv(data, sizeof(data), 0);
        allReciveInfo += data;
        log("allReciveInfo = %s", allReciveInfo.c_str());
        while (allReciveInfo.size() > 0) {
            const char* mark1 = "PX+";
            const char* mark2 = "+PX";
            int pos1 = allReciveInfo.find(mark1);
            int pos2 = allReciveInfo.find(mark2);
            if (pos1 >= 0 && pos2 >= 0) {
                std::string msg = allReciveInfo.substr(pos1 + 3, pos2 - 3);
                allReciveInfo = allReciveInfo.substr(pos2 + 3, allReciveInfo.size());
                log("allReciveInfo substr = %s", allReciveInfo.c_str());
                if (msg.size() > 0) {
                    SocketDataManage::getInstance()->pushMsg(msg);
                }
            }
            else {
                log("receiveData break");
                break;
            }
        }
        if (result <= 0) {
            log("client lost connect to server");
            break;
        }
    }
    log("client socket close");
    socket.Close();
}

int NetworkManage::getMsgLength(std::string str) {
    return str.length();
}
