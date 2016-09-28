//
//  LoginByWechat.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//

#import <Foundation/Foundation.h>

#import "payment/ios/wechat/WXApi.h"

#define AppID       @"wx650e2a97e8b7b265"

@interface LoginByWechat : NSObject<WXApiDelegate>

+ (instancetype)sharedManager;

- (BOOL)sendAuthRequestScope;

- (void)sendLoginMsg2Server:(NSString*) code;

- (BOOL)checkTokenOutTime;

- (void) wechatShare;

@end