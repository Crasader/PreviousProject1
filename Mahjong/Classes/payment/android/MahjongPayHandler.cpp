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

void MahjongPayHandler::dealEventCallBack(int eventId, int result){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if(result == 1){
        log("dealEventCallBack SUCCESS");
    }else{
        log("dealEventCallBack FAIL");
    }
    
#endif
    log("dealEventCallBack dealEventCallBack dealEventCallBack");
}
