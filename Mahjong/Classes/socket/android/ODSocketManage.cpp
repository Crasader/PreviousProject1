#include "socket/android/ODSocketManage.h"


ODSocketManage* ODSocketManage::_instance = NULL;
std::string ODSocketManage::allReciveInfo;

ODSocketManage* ODSocketManage::getInstance() {
    if (NULL == _instance) {
        _instance = new ODSocketManage();
    }
    return _instance;
}

ODSocketManage::ODSocketManage() {
    connectServer();
}

void ODSocketManage::connectServer() {
//    try {
//        // ODSocket socket;
//        socket.Init();
//        socket.Create(AF_INET, SOCK_STREAM, 0);
//        
//        bool result = socket.Connect(ip, port);
//        int retryTimes = 0;
//        while (result == false && retryTimes < 3) {
//            log("尝试重新连接...");
//            result = socket.Connect(ip, port);
//            retryTimes++;
//#if(CC_TARGET_PLATFORM ==  CC_PLATFORM_WIN32)
//            Sleep(1000);
//#else
//            sleep(1);
//#endif
//        }
//        if (result) {
//            log("成功连接到服务端,开启心跳");
//            std::thread recvThread = std::thread(&ODSocketManage::receiveData,
//                                                 this);
//            recvThread.detach();
//        }
//        else {
//            log("连接服务端失败 = %d", result);
//            return;
//        }
//    }
//    catch (char* str) {
//        log("Socket 连接出错");
//    }
}

void ODSocketManage::sendMsg(std::string code) {
    log("send command = %s", code.c_str());
//    int sendResult = socket.Send(code.c_str(), getMsgLength(code));
//    if (sendResult < 0) {
//        log("无法向服务端发送消息");
//        socket.Close();
//        log("重新连接网络");
//        connectServer();
//    }
}

void ODSocketManage::heartbeat() {
    std::thread recvThread = std::thread(&ODSocketManage::sendHeartBeat, this);
    recvThread.detach();
}

void ODSocketManage::sendHeartBeat() {
    while (true) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        Sleep(3000);
#else
        sleep(3);
#endif
//        sendMsg(CommandManage::getInstance()->getHeartCommmand());
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
//                    SocketDataManage::getInstance()->pushMsg(msg);
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
