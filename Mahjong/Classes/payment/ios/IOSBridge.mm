//
//  IOSBridge.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/19.
//
//

#import "payment/ios/IOSBridge.h"
#import "json/document.h"
#import "json/rapidjson.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "payment/ios/RechargeVC.h"
#import "payment/ios/LoginByWechat.h"
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


void IOSBridge::doWechatLogin(){
    LoginByWechat* loginByWechat = [LoginByWechat alloc] ;
    [loginByWechat sendAuthRequestScope];
    //    [loginByWechat wechatShare:@"红包口令" ContentDescription:@"123456789"];
}

void IOSBridge::doWechatShareWeb(std::string url,std::string title,std::string content){
    NSString* wxUrl = [[NSString alloc] initWithFormat:@"%s",url.c_str()];
    NSString* wxTitle = [[NSString alloc] initWithFormat:@"%s",title.c_str()];
    NSString* wxContent = [[NSString alloc] initWithFormat:@"%s",content.c_str()];
    LoginByWechat* loginByWechat = [LoginByWechat alloc] ;
    [loginByWechat wechatShareWeb:wxUrl ContentTile:wxTitle ContentDescription:wxContent];

}


void IOSBridge::doWechatShareApp(std::string title,std::string content){
    NSString* wxTitle = [[NSString alloc] initWithFormat:@"%s",title.c_str()];
    NSString* wxContent = [[NSString alloc] initWithFormat:@"%s",content.c_str()];
    LoginByWechat* loginByWechat = [LoginByWechat alloc];
    [loginByWechat wechatShareApp:wxTitle ContentDescription:wxContent];
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
        const rapidjson::Value &myOrderId = _mDoc["orderId"];
        const rapidjson::Value &mypoxiaoId = _mDoc["poxiao_id"];
        //iOS代码
        NSString* pxProductId = [[NSString alloc] initWithFormat:@"%s",ios.GetString()];
        NSString* pxOrderId = [[NSString alloc] initWithFormat:@"%s",myOrderId.GetString()];
        NSString* poXiaoId = [[NSString alloc] initWithFormat:@"%s",mypoxiaoId.GetString()];
        RechargeVC* rechargeVC = [RechargeVC shareInstance] ;
        [rechargeVC buy:pxOrderId productId:pxProductId poxiaoId:poXiaoId];
#endif
    }else{
        UIAlertView *alerView2 = [[UIAlertView alloc] initWithTitle:@"提示" message:@"你今天购买次数过多" delegate:nil cancelButtonTitle:NSLocalizedString(@"关闭",nil) otherButtonTitles:nil];
        [alerView2 show];
    }
}

