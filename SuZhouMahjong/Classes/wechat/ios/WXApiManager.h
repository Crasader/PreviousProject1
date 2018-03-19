//
//  LoginByWechat.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//

#import <Foundation/Foundation.h>
#import "WXApi.h"

@interface WXApiManager : NSObject<WXApiDelegate>

+ (instancetype)sharedManager;

@end
