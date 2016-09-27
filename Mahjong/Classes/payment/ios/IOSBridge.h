//
//  IOSBridge.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/19.
//
//

#ifndef IOSBridge_hpp
#define IOSBridge_hpp


#include "cocos2d.h"
#include "network/HttpClient.h"

#define TBU_ID "201617"

using namespace cocos2d;
using namespace network;

class IOSBridge{
public:
    static IOSBridge* getInstance();
    void doPayEvent(std::string poxiaoId,int payId);
    void doWechatLogin();
private:
    IOSBridge();
    static IOSBridge* _instance;
    void init();
    void getProductId(std::string poxiaoId,std::string payId);
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
};
#endif /* IOSBridge_hpp */
