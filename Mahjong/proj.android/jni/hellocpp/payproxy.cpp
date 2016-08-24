#include "cocos2d.h"
#include <jni.h>
#include "platform\android\jni\JniHelper.h"
#include "../../../Classes/payment/android/CallAndroidMethod.h"
#include "../../../Classes/payment/android/MahjongPayHandler.h"

using namespace cocos2d;

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_payment_JniPayCallbackHelper_eventCallBack(JNIEnv* env, jclass jcl, jint eventId,jint result,
		,jintArray propIds,jintArray propNums)
	{
		jint *carr;
		carr = env->GetIntArrayElements(propIds, false);
		jint *carr1;
		carr1 = env->GetIntArrayElements(propNums, false);
		jint length=env->GetArrayLength(propIds);
		MahjongPayHandler::getInstance()->dealEventCallBack(eventId,result,carr,carr1,length);
	}







