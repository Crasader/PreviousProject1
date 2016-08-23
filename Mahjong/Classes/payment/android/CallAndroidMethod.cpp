#include "payment/android/CallAndroidMethod.h"
#include"payment/android/MahjongPayHandler.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
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



void CallAndroidMethod::requestEvent(int eventId){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"pay","(I)V");
		jint pay_point = eventId;
		if(isHave){
			jobject jobj;
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pay_point);
		}
#endif	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		MenuScenePayHandler::getInstance()->dealEventClose(eventId);
#endif	
}
