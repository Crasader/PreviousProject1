//
//  WxLoginHandler.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/27.
//
//

#include "payment/ios/WxLoginHandler.h"
#include "mahjong/state/GameData.h"
#include "server/NetworkManage.h"
#include "http/image/UrlImageMannger.h"
#include "userdata/UserData.h"


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

void WxLoginHandler::doGameLogin(std::string openid,std::string pic,std::string sex,std::string nickname){
    //发送登录请求到游戏服务器
    if("" == openid){
        //登录错误的提示
        log("mahjong game openid is null");
    }else{
        std::string msg =CommandManage::getInstance()->getThirdLoginCommand(openid,pic,sex,nickname);
        if(msg != ""){
            NetworkManage::getInstance()->sendMsg(msg);
        }
    }
}

void WxLoginHandler::updatePlayerInfo(std::string result){
    char* buf = const_cast<char*>(result.c_str());
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("mahjong_pay_result",buf);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getPlayerInfoCommand());
}
