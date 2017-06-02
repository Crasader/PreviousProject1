//
//  WXApiManager.m
//  SDKSample
//
//  Created by Jeason on 16/07/2015.
//
//

#import "wechat/ios/WXApiManager.h"
#import "wechat/ios/LoginByWechat.h"
#import "wechat/ios/WxLoginHandler.h"
#include "userdata/UserData.h"

@implementation WXApiManager

#pragma mark - LifeCycle
+(instancetype)sharedManager {
    static dispatch_once_t onceToken;
    static WXApiManager *instance;
    dispatch_once(&onceToken, ^{
        instance = [[WXApiManager alloc] init];
    });
    return instance;
}

- (void)dealloc {
    [super dealloc];
}

#pragma mark - WXApiDelegate
- (void)onResp:(BaseResp *)resp {
    if ([resp isKindOfClass:[SendAuthResp class]]) {
        SendAuthResp *authResp = (SendAuthResp *)resp;
        //发送请求到服务端
        LoginByWechat* loginByWechat = [LoginByWechat sharedManager] ;
        [loginByWechat sendLoginMsg2Server:authResp.code];
    }
    if ([resp isKindOfClass:[PayResp class]]){
        PayResp*response=(PayResp*)resp;
        switch(response.errCode){
            case WXSuccess:
                //服务器端查询支付通知或查询API返回的结果再提示成功
            {
                NSLog(@"支付成功");
                LoginByWechat* loginByWechat = [LoginByWechat sharedManager] ;
                BOOL result = [loginByWechat queryPayResult];
                if(result){
                    WxLoginHandler::getInstance()->updatePlayerInfo("1");
                }else{
                    WxLoginHandler::getInstance()->updatePlayerInfo("0");
                }
                break;
            }
            default:
                NSLog(@"支付失败，retcode=%d",resp.errCode);
                break;
        }
    }
    
    if ([resp isKindOfClass:[SendMessageToWXResp class]]){
        SendMessageToWXResp *messageResp = (SendMessageToWXResp *)resp;
        if(messageResp.errCode == 0){
            //分享成功返回结果
            WxLoginHandler::getInstance()->shareSuccess();
        }else{
            WxLoginHandler::getInstance()->shareFail()();
        }
    }

}

- (void)onReq:(BaseReq *)req {
    //TODO
}

@end
