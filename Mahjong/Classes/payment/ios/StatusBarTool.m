//
//  StatusBarTool.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/30.
//
//

#import "StatusBarTool.h"

@implementation StatusBarTool

+(NSString *)currentBatteryPercent{
    NSArray *infoArray = [[[[UIApplication sharedApplication] valueForKeyPath:@"statusBar"] valueForKeyPath:@"foregroundView"] subviews];
    
    for (id info in infoArray)
    {
        if ([info isKindOfClass:NSClassFromString(@"UIStatusBarBatteryPercentItemView")])
        {
            NSString *percentString = [info valueForKeyPath:@"percentString"];
            NSLog(@"电量为：%@",percentString);
            return percentString;
        }
    }
    return @"";
}
+(NetWorkType)currentNetworkType{
    
    NSArray *infoArray = [[[[UIApplication sharedApplication] valueForKeyPath:@"statusBar"] valueForKeyPath:@"foregroundView"] subviews];
    
    NetWorkType type;
    for (id info in infoArray)
    {
        if ([info isKindOfClass:NSClassFromString(@"UIStatusBarDataNetworkItemView")]) {
            type = [[info valueForKeyPath:@"dataNetworkType"] integerValue];
            NSLog(@"----%lu", (unsigned long)type);
            
            return (NetWorkType)type;
        }
        
    }
    return NetWorkTypeNone;
}
+(NSString *)currentTimeString{
    NSArray *infoArray = [[[[UIApplication sharedApplication] valueForKeyPath:@"statusBar"] valueForKeyPath:@"foregroundView"] subviews];
    
    for (id info in infoArray)
    {
        if ([info isKindOfClass:NSClassFromString(@"UIStatusBarTimeItemView")])
        {
            NSString *timeString = [info valueForKeyPath:@"timeString"];
            NSLog(@"当前显示时间为：%@",timeString);
            return timeString;
        }
    }
    return @"";
}

+(NSString *)serviceCompany{
    NSArray *infoArray = [[[[UIApplication sharedApplication] valueForKeyPath:@"statusBar"] valueForKeyPath:@"foregroundView"] subviews];
    
    for (id info in infoArray)
    {
        if ([info isKindOfClass:NSClassFromString(@"UIStatusBarServiceItemView")])
        {
            NSString *serviceString = [info valueForKeyPath:@"serviceString"];
            NSLog(@"公司为：%@",serviceString);
            return serviceString;
        }
    }
    return @"";
}
@end

