#include "wechat/android/MahjongPayHandler.h"
#include "wechat/android/CallAndroidMethod.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "http/image/UrlImageMannger.h"

static MahjongPayHandler* _instance = nullptr;
MahjongPayHandler* MahjongPayHandler::getInstance() {
	if (!_instance) {
		_instance = new MahjongPayHandler();
	}
	return _instance;
}

void MahjongPayHandler::dealEventCallBack(int eventId, int result) {
	Director::getInstance()->getScheduler()->performFunctionInCocosThread(
			[=]() {
				GAMEDATA::getInstance()->setIsInPay(false);
				std::string res = StringUtils::format("%d",result);
				char* buf = const_cast<char*>(res.c_str());
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mahjong_pay_result",buf);
                if(eventId == 1 && result == 1){
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("hide_first_charge_btn");
                }
			});
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#endif
}

void MahjongPayHandler::loginThirdPlatform(std::string openid,std::string unionid, std::string url,
		std::string sex, std::string nickname,std::string hsman,std::string hstype,std::string imsi,std::string imei,std::string ver1) {
	if ("" == openid) {
		//登录错误的提示
		log("mahjong game openid is null");
	} else {
        UserData::getInstance()->setWxOpenId(openid);
        UserData::getInstance()->setWxUnionid(unionid);
		UserData::getInstance()->setPicture(url);
		UserData::getInstance()->setNickName(nickname);
		if (sex == "0") {
			UserData::getInstance()->setGender(0);
		} else {
			UserData::getInstance()->setGender(1);
		}
		UrlImageMannger::getInstance()->loadHeadImgByUrl(url);
        UserData::getInstance()->setHsman(hsman);
        UserData::getInstance()->setHstype(hstype);
        UserData::getInstance()->setImei(imei);
        UserData::getInstance()->setImsi(imsi);
        UserData::getInstance()->setAppVer(ver1);
		std::string msg = CommandManage::getInstance()->getThirdLoginCommand(
				openid,unionid, url,sex,nickname,hsman,hstype,imsi,imei,ver1);
		if (msg != "") {
			NetworkManage::getInstance()->sendMsg(msg);
		}
	}
}

