#include "payment/CallAndroidMethod.h"
#include"payment/MahjongPayHandler.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define JAVA_SRC getJniPath()

CallAndroidMethod* CallAndroidMethod::_instance = 0;

CallAndroidMethod::CallAndroidMethod(){

	std::string filename = "ConfigJnipath.json";
	rapidjson::Document doc;
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	_jniPath = doc["JniPath"].GetString();
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
//		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Pause;
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/PayService");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"pay","(I)V");
		jint pay_point = eventId;
		if(isHave){
			jobject jobj;
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pay_point);
		}
#endif	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Pause;
		MenuScenePayHandler::getInstance()->dealEventClose(eventId);
#endif	
}
