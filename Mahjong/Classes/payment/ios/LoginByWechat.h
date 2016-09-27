//
//  LoginByWechat.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//

#import <UIKit/UIKit.h>

#import "payment/ios/wechat/WXApi.h"
#import "payment/ios/WXApiManager.h"

@interface LoginByWechat : UIViewController<WXApiManagerDelegate>

- (BOOL)sendAuthRequestScope;

@end