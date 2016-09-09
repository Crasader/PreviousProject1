#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "../../../Classes/payment/android/CallAndroidMethod.h"
#include "../../../Classes/payment/android/MahjongPayHandler.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_payment_JniPayCallbackHelper_eventCallBack(JNIEnv* env, jclass jcl, jint eventId,jint result)
	{
//		jint *carr;
//		carr = env->GetIntArrayElements(propIds, false);
//		jint *carr1;
//		carr1 = env->GetIntArrayElements(propNums, false);
		MahjongPayHandler::getInstance()->dealEventCallBack(eventId,result);
	}
