/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "platform/ios/CCEAGLView-ios.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"
#import "wechat/ios/wechat/WXApi.h"
#import "wechat/ios/WXApiManager.h"
#import "wechat/ios/LoginByWechat.h"



#define IOS10_OR_LATER ([[[UIDevice currentDevice] systemVersion] floatValue] >= 10.0)
#define IOS9_OR_LATER ([[[UIDevice currentDevice] systemVersion] floatValue] >= 9.0)
#define IOS8_OR_LATER ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
#define IOS7_OR_LATER ([[[UIDevice currentDevice] systemVersion] floatValue] >= 7.0)

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    
    [self replyPushNotificationAuthorization:application];//ios推送
    
    cocos2d::Application *app = cocos2d::Application::getInstance();
    app->initGLContextAttrs();
    cocos2d::GLViewImpl::convertAttrs();
    
    // Override point for customization after application launch.
    
    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];
    
    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                         pixelFormat: (NSString*)cocos2d::GLViewImpl::_pixelFormat
                                         depthFormat: cocos2d::GLViewImpl::_depthFormat
                                  preserveBackbuffer: NO
                                          sharegroup: nil
                                       multiSampling: NO
                                     numberOfSamples: 0 ];
    
    // Enable or disable multiple touches
    [eaglView setMultipleTouchEnabled:NO];
    
    // Use RootViewController manage CCEAGLView
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;
    
    
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }
    
    [window makeKeyAndVisible];
    
    [[UIApplication sharedApplication] setStatusBarHidden:true];
    
    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLViewImpl::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);
    
    app->run();
    // 向微信注册
    [WXApi registerApp:AppID enableMTA:false];
    
    [[UIApplication sharedApplication] setIdleTimerDisabled:YES ] ;
    
    return YES;
}

- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url {
    return  [WXApi handleOpenURL:url delegate:[WXApiManager sharedManager]];
}

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation {
    NSLog(@"Calling Application Bundle ID: %@", sourceApplication);
    NSLog(@"URL scheme:%@", [url scheme]);
    NSLog(@"URL query: %@", [url query]);
    return [WXApi handleOpenURL:url delegate:[WXApiManager sharedManager]];
}

- (BOOL)application:(UIApplication *)app openURL:(NSURL *)url options:(NSDictionary*)options{
    return [WXApi handleOpenURL:url delegate:[WXApiManager sharedManager]];
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
    //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
    //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

#pragma mark - 申请通知权限
// 申请通知权限
- (void)replyPushNotificationAuthorization:(UIApplication *)application{
    
    if (IOS10_OR_LATER) {
        //iOS 10 later
        UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
        //必须写代理，不然无法监听通知的接收与点击事件
        center.delegate = self;
        [center requestAuthorizationWithOptions:(UNAuthorizationOptionBadge | UNAuthorizationOptionSound | UNAuthorizationOptionAlert) completionHandler:^(BOOL granted, NSError * _Nullable error) {
            if (!error && granted) {
                //用户点击允许
                NSLog(@"推送注册成功");
                [self createLocalizedUserNotification];
            }else{
                //用户点击不允许
                NSLog(@"推送注册失败");
            }
        }];
        
        // 可以通过 getNotificationSettingsWithCompletionHandler 获取权限设置
        //之前注册推送服务，用户点击了同意还是不同意，以及用户之后又做了怎样的更改我们都无从得知，现在 apple 开放了这个 API，我们可以直接获取到用户的设定信息了。注意UNNotificationSettings是只读对象哦，不能直接修改！
        [center getNotificationSettingsWithCompletionHandler:^(UNNotificationSettings * _Nonnull settings) {
            NSLog(@"用户推送设置 %@",settings);
        }];
    }else if (IOS8_OR_LATER){
        //iOS 8 - iOS 10系统
        UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert | UIUserNotificationTypeBadge | UIUserNotificationTypeSound categories:nil];
        [application registerUserNotificationSettings:settings];
    }else{
        //iOS 8.0系统以下
        [application registerForRemoteNotificationTypes:UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeAlert | UIRemoteNotificationTypeSound];
    }
    
    //注册远端消息通知获取device token
    [application registerForRemoteNotifications];
}


#pragma  mark - 获取device Token
//获取DeviceToken成功
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken{
    
    NSString *deviceString = [[deviceToken description] stringByTrimmingCharactersInSet:[NSCharacterSet characterSetWithCharactersInString:@"<>"]];
    deviceString = [deviceString stringByReplacingOccurrencesOfString:@" " withString:@""];
    
    NSLog(@"deviceToken = %@",deviceString);
}

//获取DeviceToken失败
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error{
    NSLog(@"[DeviceToken Error]:%@\n",error.description);
}

- (void)createLocalizedUserNotification{
    
    // 设置触发条件 UNNotificationTrigger
    
    NSDateComponents *components1 = [[NSDateComponents alloc] init];
    components1.weekday =1;
    components1.hour = 12;
    components1.minute = 0;
    UNCalendarNotificationTrigger *timeTrigger1 = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components1 repeats:YES];
    // 创建通知内容 UNMutableNotificationContent, 注意不是 UNNotificationContent ,此对象为不可变对象。
    UNMutableNotificationContent *content1 = [[UNMutableNotificationContent alloc] init];
    content1.title = @"小白相上海麻将";
    content1.subtitle = [NSString stringWithFormat:@""];
    content1.body = @"崇明拉西胡、南汇拉西胡全新上线，二人模式无作弊";
    content1.badge = @0;
    content1.sound = [UNNotificationSound defaultSound];
    content1.userInfo = @{@"key1":@"value1",@"key2":@"value2"};
    // 创建通知标示
    NSString *requestIdentifier1 = @"Mahjong.Week.Sunday";
    // 创建通知请求 UNNotificationRequest 将触发条件和通知内容添加到请求中
    UNNotificationRequest *request1 = [UNNotificationRequest requestWithIdentifier:requestIdentifier1 content:content1 trigger:timeTrigger1];
    
    
    NSDateComponents *components2 = [[NSDateComponents alloc] init];
    components2.weekday =2;
    components2.hour = 12;
    components2.minute = 0;
    UNCalendarNotificationTrigger *timeTrigger2 = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components2 repeats:YES];
    // 创建通知内容 UNMutableNotificationContent, 注意不是 UNNotificationContent ,此对象为不可变对象。
    UNMutableNotificationContent *content2 = [[UNMutableNotificationContent alloc] init];
    content2.title = @"小白相上海麻将";
    content2.subtitle = [NSString stringWithFormat:@""];
    content2.body = @"躺着做老板！年入10万+，4000元创业基金+金牌培训师，小白相上海麻将诚招代理";
    content2.badge = @0;
    content2.sound = [UNNotificationSound defaultSound];
    content2.userInfo = @{@"key1":@"value1",@"key2":@"value2"};
    // 创建通知标示
    NSString *requestIdentifier2 = @"Mahjong.Week.Monday";
    
    // 创建通知请求 UNNotificationRequest 将触发条件和通知内容添加到请求中
    UNNotificationRequest *request2 = [UNNotificationRequest requestWithIdentifier:requestIdentifier2 content:content2 trigger:timeTrigger2];
    

    NSDateComponents *components3 = [[NSDateComponents alloc] init];
    components3.weekday =3;
    components3.hour = 12;
    components3.minute = 0;
    UNCalendarNotificationTrigger *timeTrigger3 = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components3 repeats:YES];
    // 创建通知内容 UNMutableNotificationContent, 注意不是 UNNotificationContent ,此对象为不可变对象。
    UNMutableNotificationContent *content3 = [[UNMutableNotificationContent alloc] init];
    content3.title = @"小白相上海麻将";
    content3.subtitle = [NSString stringWithFormat:@""];
    content3.body = @"崇明拉西胡、南汇拉西胡全新上线，二人模式无作弊";
    content3.badge = @0;
    content3.sound = [UNNotificationSound defaultSound];
    content3.userInfo = @{@"key1":@"value1",@"key2":@"value2"};
    // 创建通知标示
    NSString *requestIdentifier3 = @"Mahjong.Week.Tuesday";
    // 创建通知请求 UNNotificationRequest 将触发条件和通知内容添加到请求中
    UNNotificationRequest *request3 = [UNNotificationRequest requestWithIdentifier:requestIdentifier3 content:content3 trigger:timeTrigger3];

    
    NSDateComponents *components4 = [[NSDateComponents alloc] init];
    components4.weekday =4;
    components4.hour = 12;
    components4.minute = 0;
    UNCalendarNotificationTrigger *timeTrigger4 = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components4 repeats:YES];
    // 创建通知内容 UNMutableNotificationContent, 注意不是 UNNotificationContent ,此对象为不可变对象。
    UNMutableNotificationContent *content4 = [[UNMutableNotificationContent alloc] init];
    content4.title = @"小白相上海麻将";
    content4.subtitle = [NSString stringWithFormat:@""];
    content4.body = @"躺着做老板！年入10万+，4000元创业基金+金牌培训师，小白相上海麻将诚招代理";
    content4.badge = @0;
    content4.sound = [UNNotificationSound defaultSound];
    content4.userInfo = @{@"key1":@"value1",@"key2":@"value2"};
    // 创建通知标示
    NSString *requestIdentifier4 = @"Mahjong.Week.Wednesday";
    
    // 创建通知请求 UNNotificationRequest 将触发条件和通知内容添加到请求中
    UNNotificationRequest *request4 = [UNNotificationRequest requestWithIdentifier:requestIdentifier4 content:content4 trigger:timeTrigger4];
    
    
    NSDateComponents *components5 = [[NSDateComponents alloc] init];
    components5.weekday =5;
    components5.hour = 12;
    components5.minute = 0;
    UNCalendarNotificationTrigger *timeTrigger5 = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components5 repeats:YES];
    // 创建通知内容 UNMutableNotificationContent, 注意不是 UNNotificationContent ,此对象为不可变对象。
    UNMutableNotificationContent *content5 = [[UNMutableNotificationContent alloc] init];
    content5.title = @"小白相上海麻将";
    content5.subtitle = [NSString stringWithFormat:@""];
    content5.body = @"崇明拉西胡、南汇拉西胡全新上线，二人模式无作弊";
    content5.badge = @0;
    content5.sound = [UNNotificationSound defaultSound];
    content5.userInfo = @{@"key1":@"value1",@"key2":@"value2"};
    // 创建通知标示
    NSString *requestIdentifier5 = @"Mahjong.Week.Thursday";
    // 创建通知请求 UNNotificationRequest 将触发条件和通知内容添加到请求中
    UNNotificationRequest *request5 = [UNNotificationRequest requestWithIdentifier:requestIdentifier5 content:content5 trigger:timeTrigger5];
    
    
    NSDateComponents *components6 = [[NSDateComponents alloc] init];
    components6.weekday =6;
    components6.hour = 12;
    components6.minute = 0;
    UNCalendarNotificationTrigger *timeTrigger6 = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components6 repeats:YES];
    // 创建通知内容 UNMutableNotificationContent, 注意不是 UNNotificationContent ,此对象为不可变对象。
    UNMutableNotificationContent *content6 = [[UNMutableNotificationContent alloc] init];
    content6.title = @"小白相上海麻将";
    content6.subtitle = [NSString stringWithFormat:@""];
    content6.body = @"躺着做老板！年入10万+，4000元创业基金+金牌培训师，小白相上海麻将诚招代理";
    content6.badge = @0;
    content6.sound = [UNNotificationSound defaultSound];
    content6.userInfo = @{@"key1":@"value1",@"key2":@"value2"};
    // 创建通知标示
    NSString *requestIdentifier6 = @"Mahjong.Week.Friday";
    
    // 创建通知请求 UNNotificationRequest 将触发条件和通知内容添加到请求中
    UNNotificationRequest *request6 = [UNNotificationRequest requestWithIdentifier:requestIdentifier6 content:content6 trigger:timeTrigger6];
    
    
    
    NSDateComponents *components7 = [[NSDateComponents alloc] init];
    components7.weekday =7;
    components7.hour = 12;
    components7.minute = 0;
    UNCalendarNotificationTrigger *timeTrigger7 = [UNCalendarNotificationTrigger triggerWithDateMatchingComponents:components7 repeats:YES];
    // 创建通知内容 UNMutableNotificationContent, 注意不是 UNNotificationContent ,此对象为不可变对象。
    UNMutableNotificationContent *content7 = [[UNMutableNotificationContent alloc] init];
    content7.title = @"小白相上海麻将";
    content7.subtitle = [NSString stringWithFormat:@""];
    content7.body = @"崇明拉西胡、南汇拉西胡全新上线，二人模式无作弊";
    content7.badge = @0;
    content7.sound = [UNNotificationSound defaultSound];
    content7.userInfo = @{@"key1":@"value1",@"key2":@"value2"};
    // 创建通知标示
    NSString *requestIdentifier7 = @"Mahjong.Week.Saturday";
    // 创建通知请求 UNNotificationRequest 将触发条件和通知内容添加到请求中
    UNNotificationRequest *request7 = [UNNotificationRequest requestWithIdentifier:requestIdentifier7 content:content7 trigger:timeTrigger7];
    
    UNUserNotificationCenter* center = [UNUserNotificationCenter currentNotificationCenter];
    // 将通知请求 add 到 UNUserNotificationCenter
    [center addNotificationRequest:request1 withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"推送已添加成功 %@", requestIdentifier1);
        }
    }];
    [center addNotificationRequest:request2 withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"推送已添加成功 %@", requestIdentifier2);
        }
    }];
    [center addNotificationRequest:request3 withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"推送已添加成功 %@", requestIdentifier3);
        }
    }];
    [center addNotificationRequest:request4 withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"推送已添加成功 %@", requestIdentifier4);
        }
    }];
    [center addNotificationRequest:request5 withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"推送已添加成功 %@", requestIdentifier5);
        }
    }];
    [center addNotificationRequest:request6 withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"推送已添加成功 %@", requestIdentifier6);
        }
    }];
    [center addNotificationRequest:request7 withCompletionHandler:^(NSError * _Nullable error) {
        if (!error) {
            NSLog(@"推送已添加成功 %@", requestIdentifier7);
        }
    }];
}

#pragma mark - iOS10 收到通知（本地和远端） UNUserNotificationCenterDelegate

//App处于前台接收通知时
- (void)userNotificationCenter:(UNUserNotificationCenter *)center willPresentNotification:(UNNotification *)notification withCompletionHandler:(void (^)(UNNotificationPresentationOptions))completionHandler{
    
    //收到推送的请求
    UNNotificationRequest *request = notification.request;
    
    //收到推送的内容
    UNNotificationContent *content = request.content;
    
    //收到用户的基本信息
    NSDictionary *userInfo = content.userInfo;
    
    //收到推送消息的角标
    NSNumber *badge = content.badge;
    
    //收到推送消息body
    NSString *body = content.body;
    
    //推送消息的声音
    UNNotificationSound *sound = content.sound;
    
    // 推送消息的副标题
    NSString *subtitle = content.subtitle;
    
    // 推送消息的标题
    NSString *title = content.title;
    
    if([notification.request.trigger isKindOfClass:[UNPushNotificationTrigger class]]) {
        NSLog(@"iOS10 收到远程通知:%@",userInfo);
        
    }else {
        // 判断为本地通知
        //此处省略一万行需求代码。。。。。。
        NSLog(@"iOS10 收到本地通知:{nbody:%@,ntitle:%@,nsubtitle:%@,nbadge:%@,nsound:%@,nuserInfo:%@}",body,title,subtitle,badge,sound,userInfo);
    }
    
    
    // 需要执行这个方法，选择是否提醒用户，有Badge、Sound、Alert三种类型可以设置
    completionHandler(UNNotificationPresentationOptionBadge|
                      UNNotificationPresentationOptionSound|
                      UNNotificationPresentationOptionAlert);
    
}


//App通知的点击事件
- (void)userNotificationCenter:(UNUserNotificationCenter *)center didReceiveNotificationResponse:(UNNotificationResponse *)response withCompletionHandler:(void (^)())completionHandler{
    //收到推送的请求
    UNNotificationRequest *request = response.notification.request;
    
    //收到推送的内容
    UNNotificationContent *content = request.content;
    
    //收到用户的基本信息
    NSDictionary *userInfo = content.userInfo;
    
    //收到推送消息的角标
    NSNumber *badge = content.badge;
    
    //收到推送消息body
    NSString *body = content.body;
    
    //推送消息的声音
    UNNotificationSound *sound = content.sound;
    
    // 推送消息的副标题
    NSString *subtitle = content.subtitle;
    
    // 推送消息的标题
    NSString *title = content.title;
    
    if([response.notification.request.trigger isKindOfClass:[UNPushNotificationTrigger class]]) {
        NSLog(@"iOS10 收到远程通知:%@",userInfo);
        
    }else {
        // 判断为本地通知
        NSLog(@"iOS10 收到本地通知:{nbody:%@,ntitle:%@,nsubtitle:%@,nbadge:%@,nsound:%@,nuserInfo:%@}",body,title,subtitle,badge,sound,userInfo);
    }
    completionHandler(); // 系统要求执行这个方法
}

#pragma mark -iOS 10之前收到通知

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
    NSLog(@"iOS6及以下系统，收到通知:%@", userInfo);
    //此处省略一万行需求代码。。。。。。
}

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo fetchCompletionHandler:(void (^)(UIBackgroundFetchResult))completionHandler {
    NSLog(@"iOS7及以上系统，收到通知:%@", userInfo);
    completionHandler(UIBackgroundFetchResultNewData);
    //此处省略一万行需求代码。。。。。。
}

#pragma mark -
#pragma mark Memory management

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}


@end
