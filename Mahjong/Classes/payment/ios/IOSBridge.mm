//
//  IOSBridge.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/19.
//
//

#include "payment/ios/IOSBridge.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "payment/ios/RechargeVC.h"
#endif

IOSBridge* IOSBridge::_instance = 0;

IOSBridge::IOSBridge(){
    this->init();
}

void IOSBridge::init(){
    //TODO
}

IOSBridge* IOSBridge::getInstance(){
    if (_instance == 0){
        _instance = new IOSBridge();
    }
    return _instance;
}

void IOSBridge::doPayEvent(int payId){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //获取商品的编号
    getProductId(StringUtils::format("%d",payId));
#endif
}


void IOSBridge::getProductId(std::string payId){
    HttpRequest* request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setUrl(StringUtils::format("http://183.129.206.54:1111/pay!getIosPoint.action?pay_point=%s&tbu_id=%s",payId.c_str(),TBU_ID).c_str());
    request->setResponseCallback(CC_CALLBACK_2(IOSBridge::onHttpRequestCompleted, this));
    request->setTag("Get Product ID");
    HttpClient::getInstance()->send(request);
    request->release();
}

void IOSBridge::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response){
    std::vector<char> *buffer;
    while (true)
    {
        if (!response)
        {
            return;
        }
        if (!response->isSucceed())
        {
            return;
        }
        buffer = response->getResponseData();
        break;
    }
    std::string msg(buffer->begin(),buffer->end());;
    log("onHttpRequestCompleted response = %s",msg.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
    RechargeVC *re = [[RechargeVC alloc] init];
    [re buy:1];
#endif
}

