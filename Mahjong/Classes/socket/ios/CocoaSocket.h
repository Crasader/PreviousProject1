//
//  ScoketManage.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/12/13.
//
//

@interface CocoaSocket : NSObject

@property (nonatomic, assign) uint16_t port; // 端口
@property (nonatomic, copy) NSString *socketHost; // 服务器地址

/**
 *  连接状态：1已连接，-1未连接，0连接中
 */
@property (nonatomic, assign) NSInteger connectStatus;
@property (nonatomic, assign) NSInteger reconnectionCount;  // 建连失败重连次数

@property (nonatomic, assign) NSInteger beatCount;      // 发送心跳次数，用于重连
@property (nonatomic, strong) NSTimer *beatTimer;       // 心跳定时器
@property (nonatomic, strong) NSTimer *reconnectTimer;  // 重连定时器


+ (instancetype)sharedSocket;

/**
 *  socket 创建socket连接
 */
- (void)startConnectSocket;
/**
 *  socket 连接成功后发送心跳的操作
 */
- (void)socketDidConnectBeginSendBeat:(nonnull NSString *)beatBody;



/**
 *  向服务器发送数据
 *
 *  @param body 数据
 */
- (void)socketWriteData:(nonnull NSString *)data;

/**
 *  socket 读取数据
 */
- (void)socketBeginReadData;

/**
 *  socket 主动断开连接
 */
- (void)disconnectSocket;

/**
 *  重设心跳次数
 */
- (void)resetBeatCount;

@end
