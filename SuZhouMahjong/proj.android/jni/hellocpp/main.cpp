#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "../../../Classes/wechat/android/CallAndroidMethod.h"
#include "../../../Classes/wechat/android/MahjongPayHandler.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init(JNIEnv* env) {
	LOGD("cocos_android_app_init");
	AppDelegate *pAppDelegate = new AppDelegate();
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_payment_JniPayCallbackHelper_eventCallBack(JNIEnv* env, jclass jcl, jint eventId,jint result)
{
	MahjongPayHandler::getInstance()->dealEventCallBack(eventId,result);
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_payment_JniPayCallbackHelper_loginThirdPlatform(JNIEnv* env, jclass jcl,jstring openid,jstring unionid,jstring url,jstring sex,jstring nickname,jstring hsman,jstring hstype,jstring imsi,jstring imei,jstring version,jstring jd,jstring wd)
{
	char* newOPenId;
	newOPenId = (char*)env->GetStringUTFChars(openid,0);
	char* newUnionid;
	newUnionid = (char*)env->GetStringUTFChars(unionid,0);
	char* newUrl;
	newUrl = (char*)env->GetStringUTFChars(url,0);
	char* newSex;
	newSex = (char*)env->GetStringUTFChars(sex,0);

	char* newNickName;
	newNickName = (char*)env->GetStringUTFChars(nickname,0);

	char* newHsman;
	newHsman = (char*)env->GetStringUTFChars(hsman,0);

	char* newHstype;
	newHstype = (char*)env->GetStringUTFChars(hstype,0);

	char* newImsi;
	newImsi = (char*)env->GetStringUTFChars(imsi,0);

	char* newImei;
	newImei = (char*)env->GetStringUTFChars(imei,0);

	char* newVersion;
	newVersion = (char*)env->GetStringUTFChars(version,0);

	char* newjd;
	newjd = (char*)env->GetStringUTFChars(jd,0);

	char* newwd;
	newwd = (char*)env->GetStringUTFChars(wd,0);

	MahjongPayHandler::getInstance()->loginThirdPlatform(newOPenId,newUnionid,newUrl,newSex,newNickName,newHsman,newHstype,newImsi,newImei,newVersion,newjd,newwd);
}


extern "C" JNIEXPORT jstring JNICALL
Java_org_cocos2dx_cpp_payment_JniPayCallbackHelper_getWriteablePath(JNIEnv* env, jclass jcl)
{
	auto writepath = FileUtils::getInstance()->getWritablePath();
	jstring jstr = JniHelper::getEnv()->NewStringUTF(writepath.c_str());
	return jstr;
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_cocos2dx_cpp_payment_JniPayCallbackHelper_shareHongbaoPride(JNIEnv* env, jclass jcl,jboolean result)
{
	MahjongPayHandler::getInstance()->shareHongbaoPride(result);
}

extern "C" JNIEXPORT jstring JNICALL
Java_org_cocos2dx_cpp_payment_JniPayCallbackHelper_addRoomByInvited(JNIEnv* env, jclass jcl , jstring roomid)
{
	char* newOPenId;
	newOPenId = (char*)env->GetStringUTFChars(roomid,0);
	MahjongPayHandler::getInstance()->addRoomByInvited(newOPenId);
}
