#include "payment/android/MahjongPayHandler.h"
#include "payment/android/CallAndroidMethod.h"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"
#include "http/image/UrlImageMannger.h"

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
    Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        GAMEDATA::getInstance()->setIsInPay(false);
        std::string res = StringUtils::format("%d",result);
        char* buf = const_cast<char*>(res.c_str());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mahjong_pay_result",buf);
        log("dealEventCallBack dealEventCallBack dealEventCallBack");
    });
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
#endif
}


void MahjongPayHandler::loginThirdPlatform(std::string openid){
    if("" == openid){
        //登录错误的提示
        log("mahjong game openid is null");
    }else{
        std::string msg =CommandManage::getInstance()->getThirdLoginCommand(openid,UserData::getInstance()->getPicture());
        if(msg != ""){
            NetworkManage::getInstance()->sendMsg(msg);
        }
    }
}


void MahjongPayHandler::loadImageByURL(std::string url){
    UserData::getInstance()->setPicture(url);
    UrlImageMannger::getInstance()->loadImgByUrl(url);
}
