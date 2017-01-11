//
//  CallAndroidSocket.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/1/11.
//
//

#include "socket/android/native/CallAndroidSocket.hpp"
#include "mahjong/state/GameData.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define JAVA_SRC getJniPath()

CallAndroidSocket* CallAndroidSocket::_instance = 0;

CallAndroidSocket::CallAndroidSocket(){
    _jniPath = "org/cocos2dx/cpp/payment";
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

void CallAndroidSocket::requestEvent(std::string poxiaoId,std::string payId){
    GAMEDATA::getInstance()->setIsInPay(true);
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mahjong_start_pay");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"requestEvent","(Ljava/lang/String;Ljava/lang/String;)V");
    jstring poxiao_id = JniHelper::getEnv()->NewStringUTF(poxiaoId.c_str());
    jstring pay_point = JniHelper::getEnv()->NewStringUTF(payId.c_str());;
    if(isHave){
        jobject jobj;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,poxiao_id,pay_point);
    }
#endif
}
