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

void  MahjongPayHandler::dealRewardProp(int propId, int propNum){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//	log("dealEventSuccess propId=%d,propNum=%d", propId,propNum);
#endif
	switch (propId)
	{
	
	default:
		break;
	}
}
void  MahjongPayHandler::dealEventClose(int eventId){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//	log("dealEventClose eventId=%d", eventId);
#endif
	

}
void MahjongPayHandler::dealEventSuccess(int eventId, int propIds[], int propNums[], int count){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//	log("dealEventSuccess eventId=%d", eventId);
#endif
//	log("dealEventSuccess eventId=" + eventId);
	
}

void MahjongPayHandler::dealEventFail(int eventId){
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
//	log("dealEventFail eventId=%d",eventId);
#endif
	
}