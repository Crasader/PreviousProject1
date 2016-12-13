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

CocoaSocketManage::CocoaSocketManage(){
    
}


CocoaSocketManage* CocoaSocketManage::getInstance(){
    if (_instance == NULL){
        _instance = new CocoaSocketManage();
    }
    return _instance;
}

void CocoaSocketManage::connectSocket(){
    CocoaSocket *socket = [CocoaSocket sharedSocket];
    socket.port = 9999; // 端口
    socket.socketHost = @"183.129.206.54"; //IP
    [socket startConnectSocket];
}
