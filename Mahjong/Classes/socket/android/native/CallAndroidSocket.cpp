//
//  CallAndroidSocket.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/1/11.
//
//

#include "socket/android/native/CallAndroidSocket.hpp"
#include "mahjong/common/state/GameData.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

CallAndroidSocket* CallAndroidSocket::_instance = 0;

CallAndroidSocket::CallAndroidSocket(){
    _jniPath = "org/cocos2dx/cpp/network";
}
CallAndroidSocket* CallAndroidSocket::getInstance(){
    if(_instance == 0){
        _instance = new CallAndroidSocket();
    }
    return _instance;
}

const char*  CallAndroidSocket::getSocketJniPath()
{
    return _jniPath.c_str();
}

bool CallAndroidSocket::connectSocket(std::string host,std::string port){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",getSocketJniPath(),"/AndroidSocketJni");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"connectSocket","(Ljava/lang/String;Ljava/lang/String;)V");
    if(isHave){
//        jobject jobj;
        jstring hostIP = JniHelper::getEnv()->NewStringUTF(host.c_str());
        jstring socketport = JniHelper::getEnv()->NewStringUTF(port.c_str());;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,hostIP,socketport);
        JniHelper::getEnv()->DeleteLocalRef(hostIP);
        JniHelper::getEnv()->DeleteLocalRef(socketport);
    }
#endif
    return true;
}

void CallAndroidSocket::disConnectSelf(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",getSocketJniPath(),"/AndroidSocketJni");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"disConnectSelf","()V");
    if(isHave){
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    }
#endif
}

void CallAndroidSocket::sendDataSever(std::string data){
    log("send data = %s",data.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",getSocketJniPath(),"/AndroidSocketJni");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"sendDataSever","(Ljava/lang/String;)V");
    if(isHave){
        jstring msg = JniHelper::getEnv()->NewStringUTF(data.c_str());
//        jobject jobj;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,msg);
        JniHelper::getEnv()->DeleteLocalRef(msg);
    }
#endif
}
