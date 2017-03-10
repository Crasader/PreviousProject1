//
//  SwitchHttp.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/2/22.
//
//

#include "SwitchHttp.hpp"
#include "mahjong/GameConfig.h"

SwitchHttp* SwitchHttp::_instance = 0;

SwitchHttp* SwitchHttp::getInstance(){
    if (_instance == 0){
        _instance = new SwitchHttp();
    }
    return _instance;
}

SwitchHttp::SwitchHttp(){


}


void SwitchHttp::getSwitchState(){
    HttpRequest* request = new HttpRequest();
    request->setUrl(StringUtils::format("http://wyhl.5278-mobi.com:1111/switch!getShmjSwitch?plat=%s",PAY_PLAT_VALUE).c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(SwitchHttp::onHttpRequestCompleted,this));
    request->setTag("GET SWITCH");
    cocos2d::network::HttpClient::getInstance()->send(request);
    request->release();
}

void SwitchHttp::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response){


}
