#include "mahjong/chat/chatAndroid/ChatAndroidMethod.h"
#include "mahjong/state/GameData.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

#define JAVA_SRC getJniPath()

ChatAndroidMethod* ChatAndroidMethod::_instance = 0;

ChatAndroidMethod::ChatAndroidMethod(){
	_jniPath = "org/cocos2dx/cpp";
}
ChatAndroidMethod* ChatAndroidMethod::getInstance(){
	if(_instance == 0){
		_instance = new ChatAndroidMethod();
	}
	return _instance;
}

const char*  ChatAndroidMethod::getJniPath()
{
	return _jniPath.c_str();
}

void ChatAndroidMethod::loginChatServer(std::string poxiaoId){
    log("ChatAndroidMethod—>loginChatServer");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"loginChatServer","(Ljava/lang/String;)V");
    if(isHave){
        jstring pid = JniHelper::getEnv()->NewStringUTF(poxiaoId.c_str());
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pid);
        JniHelper::getEnv()->DeleteLocalRef(pid);
    }
#endif
}

void ChatAndroidMethod::createChatRoom(std::string poxiaoId){
    log("ChatAndroidMethod—>createChatRoom");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"createRoom","(Ljava/lang/String;)V");
    if(isHave){
        jstring pid = JniHelper::getEnv()->NewStringUTF(poxiaoId.c_str());
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pid);
        JniHelper::getEnv()->DeleteLocalRef(pid);
    }
#endif
}


void ChatAndroidMethod::addMember(std::string myPoxiaoId,std::string poxiaoId){
    log("ChatAndroidMethod—>addMember");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"addMenber","(Ljava/lang/String;Ljava/lang/String;)V");
    if(isHave){
        jstring pid1 = JniHelper::getEnv()->NewStringUTF(myPoxiaoId.c_str());
        jstring pid2 = JniHelper::getEnv()->NewStringUTF(poxiaoId.c_str());
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pid1,pid2);
        JniHelper::getEnv()->DeleteLocalRef(pid1);
        JniHelper::getEnv()->DeleteLocalRef(pid2);
    }
#endif
}

void ChatAndroidMethod::sendChatInfo(std::string poxiaoId,std::string msg){
    log("ChatAndroidMethod—>sendChatInfo");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"sendChatInfo","(Ljava/lang/String;Ljava/lang/String;)V");
    if(isHave){
        jstring pid1 = JniHelper::getEnv()->NewStringUTF(poxiaoId.c_str());
        jstring pid2 = JniHelper::getEnv()->NewStringUTF(msg.c_str());
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pid1,pid2);
        JniHelper::getEnv()->DeleteLocalRef(pid1);
        JniHelper::getEnv()->DeleteLocalRef(pid2);
    }
#endif
}

void ChatAndroidMethod::beginRecordAudio()
{
    log("ChatAndroidMethod—>beginRecordAudio");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path = String::createWithFormat("%s%s", JAVA_SRC, "/chat/RecordUtil");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "beginRecordAudio", "()V");
    if (isHave) {
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    }
#endif
}

void ChatAndroidMethod::endRecordAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path = String::createWithFormat("%s%s", JAVA_SRC, "/chat/RecordUtil");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "endRecordAudio", "()V");
    if (isHave) {
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    }
#endif
}

void ChatAndroidMethod::playAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path = String::createWithFormat("%s%s", JAVA_SRC, "/chat/RecordUtil");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "playAudio", "()V");
    if (isHave) {
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    }
#endif
}

void ChatAndroidMethod::deleteAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path = String::createWithFormat("%s%s", JAVA_SRC, "/chat/RecordUtil");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "deleteFile", "()V");
    if (isHave) {
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
    }
#endif
}


std::string ChatAndroidMethod::getRecordFilePath(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/chat/RecordUtil");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"getRecordFilePath","()Ljava/lang/String;");
    if(isHave){
       	jstring str = (jstring)JniHelper::getEnv()->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        JniHelper::getEnv()->DeleteLocalRef(methodInfo.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        JniHelper::getEnv()->DeleteLocalRef(str);
        return ret->getCString();
    }
#endif
    return "";
}

