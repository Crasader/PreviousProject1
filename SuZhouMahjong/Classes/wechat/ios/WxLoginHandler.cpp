//
//  WxLoginHandler.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/27.
//
//

#include "wechat/ios/WxLoginHandler.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "http/image/UrlImageMannger.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/GameConfig.h"


WxLoginHandler* WxLoginHandler::_instance = 0;

WxLoginHandler::WxLoginHandler(){
    this->init();
}

bool WxLoginHandler::init(){
    return true;
}

WxLoginHandler* WxLoginHandler::getInstance(){
    if (_instance == 0){
        _instance = new WxLoginHandler();
    }
    return _instance;
}

void WxLoginHandler::doGameLogin(std::string openid,std::string unionid,std::string pic,std::string sex,std::string nickname,std::string hsman,std::string hstype,std::string imsi,std::string imei,std::string ver1){
    //发送登录请求到游戏服务器
    if("" == openid){
        //登录错误的提示
        log("mahjong game openid is null");
    }else{
        UserData::getInstance()->setHsman(hsman);
        UserData::getInstance()->setHstype(hstype);
        UserData::getInstance()->setImei(imei);
        UserData::getInstance()->setImsi(imsi);
        UserData::getInstance()->setAppVer(ver1);
        std::string msg =CommandManage::getInstance()->getThirdLoginCommand(openid,unionid,pic,sex,nickname,hsman,hstype,imsi,imei,ver1,UserData::getInstance()->getLongitude(),UserData::getInstance()->getLatitude());
        if(msg != ""){
            NetworkManage::getInstance()->connect();
            NetworkManage::getInstance()->sendMsg(msg);
            schedule(schedule_selector(WxLoginHandler::updateCount), 0, 0, 10);
        }
    }
}

void WxLoginHandler::updatePlayerInfo(std::string result){
    if(result != "IAP"){
        char* buf = const_cast<char*>(result.c_str());
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mahjong_pay_result",buf);
    }
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
}

void WxLoginHandler::shareSuccess(){
    GAMEDATA::getInstance()->setShareHongBaoFriendState(1);
}


void WxLoginHandler::shareFail(){
    GAMEDATA::getInstance()->setShareHongBaoFriendState(2);

}

void WxLoginHandler::updateCount(float dt){
    NetworkManage::getInstance()->changeSocketAddress(SERVER_ADDRESS_2);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getThirdLoginCommand(UserData::getInstance()->getWxOpenId(),UserData::getInstance()->getWxUnionid(),UserData::getInstance()->getPicture(),StringUtils::format("%d",UserData::getInstance()->getGender()),UserData::getInstance()->getNickName(),UserData::getInstance()->getHsman(),UserData::getInstance()->getHstype(),UserData::getInstance()->getImsi(),UserData::getInstance()->getImei(),UserData::getInstance()->getAppVer(),UserData::getInstance()->getLongitude(),UserData::getInstance()->getLatitude()));
}

void WxLoginHandler::addRoomByInvited(std::string roomid){
    GAMEDATA::getInstance()->setAutoRoomId(roomid);
}
