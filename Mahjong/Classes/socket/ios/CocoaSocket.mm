//
//  ScoketManage.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

#import "socket/ios/CocoaSocket.h"
#import "socket/ios/cocoa/GCDAsyncSocket.h"
#import "socket/ios/CocoaSocketManage.h"

//static const NSInteger maxReconnection_times = 3;//最大重连次数设置为3.
static const NSInteger kBeatLimit = 3;//心跳丢失最大次数
static const NSInteger socket_timeout = 15;//超时时间

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
    
    self = [super init];
    if (!self) {
        return nil;
    }
    self.connectStatus = -1;
    return self;
}

//创建连接
- (bool)startConnectSocket {
    if (self.connectStatus != -1) {
        NSLog(@"Socket Connect: YES");
        return true;
    }
    
    self.connectStatus = 0;
    
    _asyncSocket = [[GCDAsyncSocket alloc] initWithDelegate:self delegateQueue:dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0)];
    NSError *error = nil;
    [_asyncSocket connectToHost:self.socketHost onPort:self.port error:&error];
    [_asyncSocket setIPv4PreferredOverIPv6:false];
    if (!error) {
        NSLog(@"服务开启成功");
        return true;
    } else {
        self.connectStatus = -1;
        NSLog(@"服务开启失败 %@", error);
        return false;
    }
}

//发送心跳
- (void)socketDidConnectBeginSendBeat:(NSString *)beatBody {
    //    NSLog(@"GCDAsyncSocket--->socketDidConnectBeginSendBeat");
    self.connectStatus = 1;
    self.reconnectionCount = 0;
    if (!self.beatTimer) {
        self.beatTimer = [NSTimer scheduledTimerWithTimeInterval:5.0
                                                          target:self
                                                        selector:@selector(sendBeat:)
                                                        userInfo:beatBody
                                                         repeats:YES];
        [[NSRunLoop mainRunLoop] addTimer:self.beatTimer forMode:NSRunLoopCommonModes];
    }
}


//连接断开代理
- (void)socketDidDisconnect:(GCDAsyncSocket *)sock withError:(NSError *)err;
{
    NSLog(@"GCDAsyncSocket--->socketDidDisconnect");
    self.connectStatus = -1;
    //目前无法解决NSTimer后台定时器的问题,将连接断开的消息发回给cocos2d-x
    [self.beatTimer invalidate];
    self.beatTimer = nil;
    self.beatCount = 0;
    [_asyncSocket setDelegate:nil];
    CocoaSocketManage::getInstance()->disConnectSocket();
}

//连接成功代理
- (void)socket:(GCDAsyncSocket *)sock didConnectToHost:(NSString *)host port:(uint16_t)port
{
    //    NSLog(@"GCDAsyncSocket--->didConnectToHost");
    [self socketBeginReadData];
}

//发送数据代理
- (void)socket:(GCDAsyncSocket *)sock didWriteDataWithTag:(long)tag
{
    //    NSLog(@"GCDAsyncSocket--->didWriteDataWithTag");
}

//接收数据代理
-(void)socket:(GCDAsyncSocket *)sock didReadData:(NSData *)data withTag:(long)tag
{
    NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
    jsonString = [jsonString stringByReplacingOccurrencesOfString:@"\r\n" withString:@""];
//    NSLog(@"receive = %@",jsonString);
    if(jsonString != nil){
        CocoaSocketManage::getInstance()->receiveScoketData([jsonString UTF8String]);
    }else{
        NSLog(@"didReadData error");
    }
    [self socketBeginReadData];
}


- (void)socketWriteData:(NSString *)data {
//    NSLog(@"send = %@",data);
    NSData *requestData = [data dataUsingEncoding:NSUTF8StringEncoding];
    [_asyncSocket writeData:requestData withTimeout:-1 tag:0];
    [self socketBeginReadData];
}

- (void)socketBeginReadData {
    [_asyncSocket readDataToData:[GCDAsyncSocket CRLFData] withTimeout:-1 tag:1]; //读到回车换行符才触发
}

- (void)disconnectSocket {
    self.reconnectionCount = -1;
    [_asyncSocket disconnect];
    [self.beatTimer invalidate];
    self.beatTimer = nil;
}

#pragma mark - public method
- (void)resetBeatCount {
    self.beatCount = 0;
}

#pragma mark - private method


- (void)sendBeat:(NSTimer *)timer {
    if (self.beatCount >= kBeatLimit) {
        self.beatCount=0;
        [self disconnectSocket];
        return;
    } else {
        self.beatCount++;
    }
    if (timer != nil) {
        [self socketWriteData:timer.userInfo];
    }
}

- (void)reconnection:(NSTimer *)timer {
    NSError *error = nil;
    if (![_asyncSocket connectToHost:self.socketHost onPort:self.port withTimeout:socket_timeout error:&error]) {
        self.connectStatus = -1;
    }
}

@end

