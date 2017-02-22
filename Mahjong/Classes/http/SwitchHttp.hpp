//
//  SwitchHttp.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/2/22.
//
//
//获取支付开关 http 请求


#ifndef SwitchHttp_hpp
#define SwitchHttp_hpp

#include "network/HttpClient.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::network;

class SwitchHttp {
public:
    static SwitchHttp* getInstance();
    void getSwitchState();
private:
    static SwitchHttp* _instance;
    SwitchHttp();
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
};
#endif /* SwitchHttp_hpp */
