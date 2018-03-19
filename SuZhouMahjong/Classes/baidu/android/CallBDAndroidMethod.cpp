#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "baidu/android/CallBDAndroidMethod.h"
#include "mahjong/common/state/GameData.h"
#define JAVA_SRC getJniPath()

CallBDAndroidMethod* CallBDAndroidMethod::_instance = 0;

CallBDAndroidMethod::CallBDAndroidMethod(){
	_jniPath = "org/cocos2dx/cpp";
}
CallBDAndroidMethod* CallBDAndroidMethod::getInstance(){
	if(_instance == 0){
		_instance = new CallBDAndroidMethod();
	}
	return _instance;
}

const char*  CallBDAndroidMethod::getJniPath()
{
	return _jniPath.c_str();
}

void CallBDAndroidMethod::updateLongitude(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"getLongitude","()Ljava/lang/String;");
    if(isHave){
        jstring str = (jstring)JniHelper::getEnv()->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        JniHelper::getEnv()->DeleteLocalRef(methodInfo.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        JniHelper::getEnv()->DeleteLocalRef(str);
        UserData::getInstance()->setLongitude(ret->getCString());
    }
#endif
}

void CallBDAndroidMethod::updateLatitude(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"getLatitude","()Ljava/lang/String;");
    if(isHave){
        jstring str = (jstring)JniHelper::getEnv()->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        JniHelper::getEnv()->DeleteLocalRef(methodInfo.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        JniHelper::getEnv()->DeleteLocalRef(str);
        UserData::getInstance()->setLatitude(ret->getCString());
    }
#endif
}
