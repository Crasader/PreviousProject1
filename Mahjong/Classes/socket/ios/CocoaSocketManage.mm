//
//  CocoaSocketManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#import "socket/ios/CocoaSocketManage.h"
#import "socket/ios/CocoaSocket.h"

CocoaSocketManage* CocoaSocketManage::_instance = NULL;

CocoaSocketManage* CocoaSocketManage::getInstance(){
    if (_instance == NULL){
        _instance = new CocoaSocketManage();
    }
    return _instance;
}

CocoaSocketManage::CocoaSocketManage(){
    
}

void CocoaSocketManage::connectSocket(std::string host, int port){
    CocoaSocket *socket = [CocoaSocket sharedSocket];
    socket.port = port; // 端口
    socket.socketHost = [NSString stringWithUTF8String:host.c_str()];; //IP
    [socket startConnectSocket];
}


void CocoaSocketManage::sendScoketData(std::string msg){
    CocoaSocket *socket = [CocoaSocket sharedSocket];
    [socket socketWriteData:[NSString stringWithUTF8String:msg.c_str()]];
}

std::string CocoaSocketManage::receiveScoketData(){

    return "";
}

