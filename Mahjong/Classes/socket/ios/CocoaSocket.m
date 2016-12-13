//
//  ScoketManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#import "socket/ios/CocoaSocket.h"
#import "socket/ios/cocoa/GCDAsyncSocket.h"

@interface CocoaSocket ()<GCDAsyncSocketDelegate>
@property (nonatomic, strong) GCDAsyncSocket *asyncSocket;
@end

@implementation CocoaSocket

+ (instancetype)sharedSocket {
    static CocoaSocket *scoket;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        scoket = [[self alloc] init];
    });
    return scoket;
}

/*
 全局队列（代理的方法是在子线程被调用）
 dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT,0)
 
 主队列（代理的方法会在主线程被调用）
 dispatch_get_main_queue()
 代理里的动作是耗时的动作，要在子线程中操作
 代理里的动作不是耗时的动作，就可以在主线程中调用
 看情况写队列
 */
- (instancetype)init {
    if (self = [super init]) {
        _asyncSocket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)];
    }
    return self;
}

- (void)startConnectSocket {
    
    NSError *error = nil;
    [_asyncSocket acceptOnPort:self.port error:&error];
    
    if (!error) {
        NSLog(@"服务开启成功");
    } else {
        NSLog(@"服务开启失败 %@", error);
    }
}

@end

