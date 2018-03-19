//
//  CallIOSMethod.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/19.
//
//

#ifndef CallIOSMethod_hpp
#define CallIOSMethod_hpp


#include "cocos2d.h"
#include "network/HttpClient.h"

#define TBU_ID "201710"

using namespace cocos2d;
using namespace network;

class CallIOSMethod{
public:
    static CallIOSMethod* getInstance();
    void doPayEvent(std::string poxiaoId,int payId);
    void doWechatLogin();
    bool isWenxinInstalled();
    std::string getBatteryPersent();
    void doWechatShareWeb(std::string url,std::string title,std::string content,int scene);
    void doWechatShareApp(std::string title,std::string content);
    void doWechatShareImg(std::string filepath,int scene);
    void copyToPasteboard(std::string str);
    void updateClientAppVersion();
private:
    CallIOSMethod();
    static CallIOSMethod* _instance;
    void init();
    void getProductId(std::string poxiaoId,std::string payId);
    void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
};
#endif /* CallIOSMethod_hpp */
