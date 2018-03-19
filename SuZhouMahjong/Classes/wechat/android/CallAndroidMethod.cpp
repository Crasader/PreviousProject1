#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "wechat/android/CallAndroidMethod.h"
#include "wechat/android/MahjongPayHandler.h"
#include "mahjong/common/state/GameData.h"
#define JAVA_SRC getJniPath()

CallAndroidMethod* CallAndroidMethod::_instance = 0;

CallAndroidMethod::CallAndroidMethod(){
	_jniPath = "org/cocos2dx/cpp/payment";
}
CallAndroidMethod* CallAndroidMethod::getInstance(){
	if(_instance == 0){
		_instance = new CallAndroidMethod();
	}
	return _instance;
}

const char*  CallAndroidMethod::getJniPath()
{
	return _jniPath.c_str();
}



void CallAndroidMethod::requestEvent(std::string poxiaoId,std::string payId){
    GAMEDATA::getInstance()->setIsInPay(true);
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mahjong_start_pay");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"requestEvent","(Ljava/lang/String;Ljava/lang/String;)V");
		if(isHave){
            jstring poxiao_id = JniHelper::getEnv()->NewStringUTF(poxiaoId.c_str());
            jstring pay_point = JniHelper::getEnv()->NewStringUTF(payId.c_str());;
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,poxiao_id,pay_point);
		}
#endif	
}

void CallAndroidMethod::queryEventResult(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"queryPayResult","()V");
    if(isHave){
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    }
#endif
}


void CallAndroidMethod::shareToWeChat(std::string url,string title,string content,bool friends){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"shareToWeChat","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
    if(isHave){
        jstring share_url = JniHelper::getEnv()->NewStringUTF(url.c_str());
        jstring share_title = JniHelper::getEnv()->NewStringUTF(title.c_str());
        jstring share_content = JniHelper::getEnv()->NewStringUTF(content.c_str());
        jboolean share_friends = friends;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,share_url,share_title,share_content,friends);
    }
#endif
}

void CallAndroidMethod::shareImageToWeChat(std::string imagePath,bool friends){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"shareImageToWeChat","(Ljava/lang/String;Z)V");
    if(isHave){
        jstring share_url = JniHelper::getEnv()->NewStringUTF(imagePath.c_str());
        jboolean share_friends = friends;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,share_url,friends);
        JniHelper::getEnv()->DeleteLocalRef(share_url);
    }
#endif
}

void CallAndroidMethod::shareSDCardImageToWeChat(std::string imagePath,bool friends){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"shareSDCardImageToWeChat","(Ljava/lang/String;Z)V");
    if(isHave){
        jstring share_url = JniHelper::getEnv()->NewStringUTF(imagePath.c_str());
        jboolean share_friends = friends;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,share_url,friends);
        JniHelper::getEnv()->DeleteLocalRef(share_url);
    }
#endif
}

void CallAndroidMethod::weChatLogin(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"weChatLogin","()V");
    if(isHave){
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    }
#endif
}

void CallAndroidMethod::clearWechatOpenId(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    UserData::getInstance()->setWxOpenId("unknow");
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"clearWechatOpenId","()V");
    if(isHave){
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    }
#endif
}

std::string CallAndroidMethod::getSdCardDir(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"getSdCardDir","()Ljava/lang/String;");
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

std::string CallAndroidMethod::getBatteryPersent(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s","org/cocos2dx/cpp","/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"getBatteryPersent","()Ljava/lang/String;");
    if(isHave){
       	jstring str = (jstring)JniHelper::getEnv()->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        JniHelper::getEnv()->DeleteLocalRef(methodInfo.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        JniHelper::getEnv()->DeleteLocalRef(str);
        return ret->getCString();
    }
#endif
    return "100";
}

void CallAndroidMethod::copyToPasteboard(std::string msg){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s","org/cocos2dx/cpp","/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"copyToPasteboard","(Ljava/lang/String;)V");
    if(isHave){
        jstring share_url = JniHelper::getEnv()->NewStringUTF(msg.c_str());
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,share_url);
        JniHelper::getEnv()->DeleteLocalRef(share_url);
    }
#endif
}

void CallAndroidMethod::downLoadAndroidApk(std::string url){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s","org/cocos2dx/cpp","/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"downLoadApk","(Ljava/lang/String;)V");
    if(isHave){
        jstring share_url = JniHelper::getEnv()->NewStringUTF(url.c_str());
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,share_url);
        JniHelper::getEnv()->DeleteLocalRef(share_url);
    }
#endif
}

void CallAndroidMethod::updateClientAppVersion(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s","org/cocos2dx/cpp","/AppActivity");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"getAndroidAppVersion","()Ljava/lang/String;");
    if(isHave){
        jstring str = (jstring)JniHelper::getEnv()->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        JniHelper::getEnv()->DeleteLocalRef(methodInfo.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        JniHelper::getEnv()->DeleteLocalRef(str);
        UserData::getInstance()->setAppVer(ret->getCString());
    }
#endif
}
