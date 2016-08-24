#include "payment/android/MahjongPayHandler.h"
#include "payment/android/CallAndroidMethod.h"

static MahjongPayHandler* _instance = nullptr;
MahjongPayHandler* MahjongPayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new MahjongPayHandler();
	}
	return _instance;
}

void MahjongPayHandler::dealEventCallBack(int eventId, int result,int propIds[], int propNums[], int count){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//	log("dealEventSuccess eventId=%d", eventId);
#endif
//	log("dealEventSuccess eventId=" + eventId);
    log("pay pay pay pay pay");
}