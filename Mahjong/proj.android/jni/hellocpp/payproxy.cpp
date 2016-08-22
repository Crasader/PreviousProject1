#include "cocos2d.h"
#include <jni.h>
#include "platform\android\jni\JniHelper.h"
#include "../../../Classes/payment/CallAndroidMethod.h"
#include "../../../Classes/payment/MahjongPayHandler.h"

using namespace cocos2d;

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventSuccess(JNIEnv* env, jclass jcl, jint eventId
		,jintArray propIds,jintArray propNums)
	{
		jint *carr;
		carr = env->GetIntArrayElements(propIds, false);
		jint *carr1;
		carr1 = env->GetIntArrayElements(propNums, false);
		jint length=env->GetArrayLength(propIds);
		MenuScenePayHandler::getInstance()->dealEventSuccess(eventId,carr,carr1,length);
	}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventClose(JNIEnv* env, jclass jcl, jint eventId){
	MenuScenePayHandler::getInstance()->dealEventClose(eventId);
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventFail(JNIEnv* env, jclass jcl, jint eventId){

	MenuScenePayHandler::getInstance()->dealEventFail(eventId);
}







