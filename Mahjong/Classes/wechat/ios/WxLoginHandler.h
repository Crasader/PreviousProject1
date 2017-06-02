//
//  WxLoginHandler.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/27.
//
//

#ifndef WxLoginHandler_hpp
#define WxLoginHandler_hpp

#include "cocos2d.h"
using namespace cocos2d;

class WxLoginHandler{
public:
    static WxLoginHandler* getInstance();
    void doGameLogin(std::string openid,std::string unionid,std::string pic,std::string sex,std::string nickname,std::string hsman,std::string hstype,std::string imsi,std::string imei,std::string ver1);
    void updatePlayerInfo(std::string result);
    void shareSuccess();
    void shareFail();
private:
    WxLoginHandler();
    static WxLoginHandler* _instance;
    void init();
};

#endif /* WxLoginHandler_hpp */
