//
//  LoginByWechat.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//
//

#import "payment/ios/LoginByWechat.h"

@interface LoginByWechat ()

@end

@implementation LoginByWechat


static NSString *kAuthScope = @"snsapi_message,snsapi_userinfo,snsapi_friend,snsapi_contact";
//static NSString *kAuthOpenID = @"0c806938e2413ce73eef92cc3";
static NSString *kAuthState = @"xxx";

#pragma mark - View Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (BOOL)sendAuthRequestScope{
    //构造SendAuthReq结构体
    SendAuthReq* req    =[[SendAuthReq alloc]init];
    req.scope           = kAuthScope;
    req.state           = kAuthState;
    // req.openID          = kAuthOpenID;
    //第三方向微信终端发送一个SendAuthReq消息结构
    return [WXApi sendAuthReq:req
        viewController:self
              delegate:[WXApiManager sharedManager]];
//    return [WXApi sendReq:req];
}


@end