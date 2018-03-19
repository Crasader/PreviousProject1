//
//  LoginByWechat.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "WXApi.h"
#import "cocos2d.h"

#define AppID       @"wx4a615e9366697d31"

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

- (void) updateClientAppVersion;

@end
