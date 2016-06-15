#pragma once
#include "cocos2d.h"
#include "http/HttpClientUtill.h"

using namespace cocos2d;



class HttpMannger {
    
public:
    static HttpMannger* getInstance();
    
    
    void httpToPostRequestToGetUrlImg(std::string url);
    void onHttpRequestCompletedForGetUrlImg(HttpClient *sender, HttpResponse *response);
    void httpToPostRequestToSendImage(std::string url,std::string postData);
    void onHttpRequestCompletedForSendImage(HttpClient *sender, HttpResponse *response);
    
private:
    HttpMannger();
    void init();
    static HttpMannger* _instance;
};


