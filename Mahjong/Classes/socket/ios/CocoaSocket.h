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

+ (instancetype)sharedSocket;
- (void)startConnectSocket;

@end
