//
//  WxLoginHandler.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/27.
//
//

#include "wechat/ios/WxLoginHandler.h"
#include "mahjong/common/state/GameData.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "http/image/UrlImageMannger.h"


WxLoginHandler* WxLoginHandler::_instance = 0;

WxLoginHandler::WxLoginHandler(){
    this->init();
}

void WxLoginHandler::init(){
    //TODO
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
        GAMEDATA::getInstance()->setHsman(hsman);
        GAMEDATA::getInstance()->setHstype(hstype);
        GAMEDATA::getInstance()->setImsi(imsi);
        GAMEDATA::getInstance()->setImei(imei);
        GAMEDATA::getInstance()->setAppVer(ver1);
        std::string msg =CommandManage::getInstance()->getThirdLoginCommand(openid,unionid,pic,sex,nickname,hsman,hstype,imsi,imei,ver1);
        if(msg != ""){
            NetworkManage::getInstance()->sendMsg(msg);
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
