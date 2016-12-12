//
//  LoginByWechat.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//

#import <Foundation/Foundation.h>
#import "payment/ios/wechat/WXApi.h"
#import <UIKit/UIKit.h>
#import "cocos2d.h"

#define AppID       @"wx650e2a97e8b7b265"

@interface LoginByWechat : UIViewController

+ (instancetype)sharedManager;

- (BOOL)isWenxinInstalled;

- (BOOL)sendAuthRequestScope;

- (void)sendLoginMsg2Server:(NSString*) code;

- (BOOL)checkTokenOutTime;

- (void) wechatShareApp:(NSString*) contentTile ContentDescription:(NSString*) contentDescription;

- (void) wechatShareWeb:(NSString*) url ContentTile:(NSString*) contentTile ContentDescription:(NSString*) contentDescription Scene:(int) inScene;

- (void) wechatShareImg:(NSData*) imageData  Scene:(int) inScene;

- (void) payWeChat: (NSString*) poxiaoId PayPoint:(NSString*) payPoint;

- (BOOL) queryPayResult;

+ (NSString*) getDeviceString;
@end
