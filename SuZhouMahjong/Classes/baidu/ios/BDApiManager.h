//
//  WXApiManager.h
//  Mahjong
//

#import <Foundation/Foundation.h>
#import <BMKLocationkit/BMKLocationComponent.h>
#import <BMKLocationkit/BMKLocationAuth.h>

@interface BDApiManager : NSObject<BMKLocationManagerDelegate,BMKLocationAuthDelegate>

@property(nonatomic, copy) BMKLocatingCompletionBlock completionBlock;

+ (instancetype)sharedManager;
-(void)initLocation;
-(void)initBlock;
-(void)checkPermisionWithKey;
- (void)getMapLoction;
@end
