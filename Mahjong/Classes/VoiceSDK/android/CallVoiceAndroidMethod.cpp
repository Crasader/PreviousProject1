#include "voicesdk/android/CallVoiceAndroidMethod.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define JAVA_SRC getJniPath()

CallVoiceAndroidMethod* CallVoiceAndroidMethod::_instance = 0;

CallVoiceAndroidMethod::CallVoiceAndroidMethod(){
	_jniPath = "org/cocos2dx/cpp/voicesdk";
}

CallVoiceAndroidMethod* CallVoiceAndroidMethod::getInstance() {
	if(_instance == 0){
		_instance = new CallVoiceAndroidMethod();
	}
	return _instance;
}

const char*  CallVoiceAndroidMethod::getJniPath()
{
	return _jniPath.c_str();
}



void CallVoiceAndroidMethod::requestEvent(std::string poxiaoId,std::string payId){
    //GAMEDATA::getInstance()->setIsInPay(true);
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

void CallVoiceAndroidMethod::queryEventResult(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"queryPayResult","()V");
    if(isHave){
        jobject jobj;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    }
#endif
}

void CallVoiceAndroidMethod::shareToWeChat(std::string url,std::string title, std::string content,bool friends){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"shareToWeChat","(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
    jstring share_url = JniHelper::getEnv()->NewStringUTF(url.c_str());
    jstring share_title = JniHelper::getEnv()->NewStringUTF(title.c_str());
    jstring share_content = JniHelper::getEnv()->NewStringUTF(content.c_str());
    jboolean share_friends = friends;
    if(isHave){
        jobject jobj;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,share_url,share_title,share_content,friends);
    }
#endif
}

void CallVoiceAndroidMethod::shareImageToWeChat(std::string imagePath,bool friends){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"shareImageToWeChat","(Ljava/lang/String;Z)V");
    jstring share_url = JniHelper::getEnv()->NewStringUTF(imagePath.c_str());
    jboolean share_friends = friends;
    if(isHave){
        jobject jobj;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,share_url,friends);
    }
#endif
}

/*
 * 录音相关  v1   start 
 */

void CallVoiceAndroidMethod::beginRecordAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/RecordUtil");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "beginRecordAudio", "()V");
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void CallVoiceAndroidMethod::endRecordAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/RecordUtil");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "endRecordAudio", "()V");
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void CallVoiceAndroidMethod::playAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/RecordUtil");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "playAudio", "()V");
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void CallVoiceAndroidMethod::deleteAudio()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/RecordUtil");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "deleteFile", "()V");
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

/*
*录音相关  v1   end
*/

/*
* china good voice  v2   start
*/
void CallVoiceAndroidMethod::prepare(std::string filename)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/VoiceRecorder");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "prepare", "(Ljava/lang/String;)V");
	jstring filename_j = JniHelper::getEnv()->NewStringUTF(filename.c_str());
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, filename_j);
	}
#endif
}

void CallVoiceAndroidMethod::release()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/VoiceRecorder");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "release", "()V");
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void CallVoiceAndroidMethod::cancel()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/VoiceRecorder");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "cancel", "()V");
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void CallVoiceAndroidMethod::play(std::string filename)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/VoicePlayer");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "play", "(Ljava/lang/String;)V");
	jstring filename_j = JniHelper::getEnv()->NewStringUTF(filename.c_str());
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, filename_j);
	}
#endif
}

void CallVoiceAndroidMethod::stop()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/VoicePlayer");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "stop", "()V");
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void CallVoiceAndroidMethod::getVoiceLevel()
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//	JniMethodInfo methodInfo;
//	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/VoiceRecorder");
//	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "getVoiceLevel", "()V");
//	if (isHave) {
//		jobject jobj;
//		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
//	}
//#endif
}

void CallVoiceAndroidMethod::setStorageDir(std::string dir)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/VoiceRecorder");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "setStorageDir", "(Ljava/lang/String;)V");
	jstring dir_j = JniHelper::getEnv()->NewStringUTF(dir.c_str());
	if (isHave) {
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, dir_j);
	}
#endif
}
/*
* china good voice  v2   end
*/











void CallVoiceAndroidMethod::weChatLogin(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/RecordUtil");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"weChatLogin","()V");
    if(isHave){
        jobject jobj;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    }
#endif
}

void CallVoiceAndroidMethod::clearWechatOpenId(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"clearWechatOpenId","()V");
    if(isHave){
        jobject jobj;
        JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
    }
#endif
}

std::string CallVoiceAndroidMethod::getSdCardDir(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo methodInfo;
    auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/Payment");
    bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"getSdCardDir","()Ljava/lang/String;");
    if(isHave){
       	jstring str = (jstring)methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
        methodInfo.env->DeleteLocalRef(methodInfo.classID);
        CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
        ret->autorelease();
        methodInfo.env->DeleteLocalRef(str);
        return ret->getCString();
    }
#endif
    return "";
}

void CallVoiceAndroidMethod::getNetInfo(int &netType, int &netLevel)
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	JniMethodInfo t;
	bool isHave = JniHelper::getStaticMethodInfo(t,  "org/cocos2dx/cpp/AppActivity", "getNetInfo", "()[I");
	if (isHave)
	{
		jintArray msg = (jintArray)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		int len = t.env->GetArrayLength(msg);
		jint* elems = t.env->GetIntArrayElements(msg, 0);
		if (2 == len)
		{
			netType = elems[0];
			netLevel = elems[1];
		}
		t.env->ReleaseIntArrayElements(msg,elems,0);
		t.env->DeleteLocalRef(t.classID);
	}
	else
	{

	}
	return;
#endif
	netType = 1; netLevel = 1;
}

int CallVoiceAndroidMethod::getBatteryPersent(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	jint r = 0;
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "getBatteryPercent", "()I")) {
		r = t.env->CallStaticIntMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	return r;
#endif
	return 50;
}

void CallVoiceAndroidMethod::showFeedBackDialog()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "showFeedDialogOnUiThread", "()V");
	if (isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

bool CallVoiceAndroidMethod::isInstalledWX()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/payment/Payment", "isWxinstalled", "()Z");
	if (isHave){
		
		auto jbool = JniHelper::getEnv()->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
		return jbool;
	}
#endif
	return false;
}
