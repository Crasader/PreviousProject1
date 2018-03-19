#import <UIKit/UIKit.h>
#ifdef NSFoundationVersionNumber_iOS_9_x_Max
#import <UserNotifications/UserNotifications.h>
#endif
#import <BMKLocationkit/BMKLocationComponent.h>
#import <BMKLocationkit/BMKLocationAuth.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate,UNUserNotificationCenterDelegate>{
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;

- (void)replyPushNotificationAuthorization:(UIApplication *)application;
- (void)createLocalizedUserNotification;
@end

