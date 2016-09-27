//
//  LoginByWechat.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//
//

#import "payment/ios/LoginByWechat.h"
#include "payment/ios/WxLoginHandler.hpp"

@implementation LoginByWechat


static NSString *kAuthScope = @"snsapi_message,snsapi_userinfo,snsapi_friend,snsapi_contact";
static NSString *kAuthState = @"heisdoubi";


#pragma mark - LifeCycle

+(instancetype)sharedManager {
    static dispatch_once_t onceToken;
    static LoginByWechat *instance;
    dispatch_once(&onceToken, ^{
        instance = [[LoginByWechat alloc] init];
    });
    return instance;
}

- (void)dealloc {
    [super dealloc];
}

#pragma mark - View Lifecycle

- (BOOL)sendAuthRequestScope{
    //构造SendAuthReq结构体
    SendAuthReq* req    =[[SendAuthReq alloc]init];
    req.scope           = kAuthScope;
    req.state           = kAuthState;
    //第三方向微信终端发送一个SendAuthReq消息结构
    return [WXApi sendReq:req];
}

#pragma mark - WXApiDelegate
- (void)onResp:(BaseResp *)resp {
    if ([resp isKindOfClass:[SendAuthResp class]]) {
        SendAuthResp *authResp = (SendAuthResp *)resp;
        //发送请求到服务端
        //第一步，创建URL
        NSString *urlstring = [NSString stringWithFormat:@"http://183.129.206.54:1111/pay!getWxAccessToken.action?appid=%@&code=%@",AppID,authResp.code];
        NSURL *url = [NSURL URLWithString:urlstring];
        //第二步，创建请求
        NSMutableURLRequest *request = [[NSMutableURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:10];
        //第三步，连接服务器
        NSData *received = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
        NSString *result = [[NSString alloc]initWithData:received encoding:NSUTF8StringEncoding];
        NSLog(@"received = %@",result);
        //解析返回的json数据
        NSData *returnedData = [result dataUsingEncoding:NSUTF8StringEncoding];;
        if(NSClassFromString(@"NSJSONSerialization"))
        {
            NSError *error = nil;
            id object = [NSJSONSerialization
                         JSONObjectWithData:returnedData
                         options:0
                         error:&error];
            
            if(error) {
                NSLog(@"json 格式有错误");
            }
            if([object isKindOfClass:[NSDictionary class]])
            {
                NSDictionary *results = object;
                NSObject *openid = [results objectForKey:@"openid"];
                NSObject *headimgurl = [results objectForKey:@"headimgurl"];
                NSString *openidstr = [NSString stringWithFormat:@"%@", openid];
                NSString *headimgurlstr = [NSString stringWithFormat:@"%@", headimgurl];
                WxLoginHandler::getInstance()->doGameLogin(std::string([openidstr UTF8String]), std::string([headimgurlstr UTF8String]));
            }
            else
            {
                NSLog(@"json 格式有错误");
            }
        }
        else
        {
            NSLog(@"系统版本过低");
        }
    }
}

- (void)onReq:(BaseReq *)req {
    
}

@end