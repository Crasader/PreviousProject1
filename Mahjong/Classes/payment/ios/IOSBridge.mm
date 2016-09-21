//
//  IOSBridge.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/19.
//
//

#include "payment/ios/IOSBridge.h"
#include "json/document.h"
#include "json/rapidjson.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "payment/ios/RechargeVC.h"
#endif

#define RETURN_IF(cond)           if((cond)) return

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

void IOSBridge::doPayEvent(std::string poxiaoId,int payId){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //获取商品的编号
    getProductId(poxiaoId,StringUtils::format("%d",payId));
#endif
}


void IOSBridge::getProductId(std::string poxiaoId,std::string payId){
    HttpRequest* request = new HttpRequest();
    request->setRequestType(HttpRequest::Type::GET);
    request->setUrl(StringUtils::format("http://183.129.206.54:1111/pay!getIosPoint.action?pay_point=%s&tbu_id=%s&poxiao_id=%s",payId.c_str(),TBU_ID,poxiaoId.c_str()).c_str());
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
    rapidjson::Document _mDoc;
    RETURN_IF(NULL == msg.c_str() || !msg.compare(""));
    _mDoc.Parse<0>(msg.c_str());
    RETURN_IF(_mDoc.HasParseError() || !_mDoc.IsObject());
    const rapidjson::Value &result = _mDoc["result"];
    if(result.GetInt() == 0){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        const rapidjson::Value &ios = _mDoc["ios"];
        const rapidjson::Value &pxOrderId = _mDoc["orderId"];
        NSString* productId=[NSString stringWithFormat:@"%s",ios.GetString()];
         NSString* orderId=[NSString stringWithFormat:@"%s",pxOrderId.GetString()];
        //iOS代码
        RechargeVC *re = [[RechargeVC alloc] init];
        [re buy:productId orderId:orderId];
#endif
    }else{
        //TODO
    }
}

