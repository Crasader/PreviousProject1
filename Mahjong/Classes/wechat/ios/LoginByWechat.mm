//
//  LoginByWechat.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/9/26.
//
//

#import "wechat/ios/LoginByWechat.h"
#import "wechat/ios/WxLoginHandler.h"
#import "wechat/ios/WXApiManager.h"
#import "sys/utsname.h"
#include "mahjong/GameConfig.h"
#include "userdata/UserData.h"

@interface LoginByWechat ()<UITextViewDelegate,WXApiDelegate>

@end

@implementation LoginByWechat


static NSString *kAuthScope = @"snsapi_message,snsapi_userinfo,snsapi_friend,snsapi_contact";
static NSString *kAuthState = @"heisdoubi";

static NSString *kAppContentExInfo = @"<xml>extend info</xml>";
static NSString *kAppContnetExURL = @"http://weixin.qq.com";
static NSString *kAppMessageExt = @"这是第三方带的测试字段";
static NSString *kAppMessageAction = @"<action>dotaliTest</action>";

static NSString *GAME_VERSION = [[NSBundle mainBundle] objectForInfoDictionaryKey:@"CFBundleShortVersionString"];
static NSString *IMEI_IMSI= @"11111111111";
static NSString *HSMAN= @"APPLE";
static NSString *DEVICESTRING= @"iphone";


#pragma mark - LifeCycle

+(instancetype)sharedManager {
    static dispatch_once_t onceToken;
    static LoginByWechat *instance;
    dispatch_once(&onceToken, ^{
        instance = [[LoginByWechat alloc] init];
    });
    return instance;
}

- (void)dealloc {
    [super dealloc];
}

#pragma mark - View Lifecycle

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)viewDidAppear:(BOOL)animated{
    [super viewDidAppear:animated];
}

- (BOOL)isWenxinInstalled{
    return [WXApi isWXAppInstalled];
}

- (BOOL)sendAuthRequestScope{
    SendAuthReq* req    =[[SendAuthReq alloc]init];
    //        req.scope           = kAuthScope;
    req.scope           =@"snsapi_userinfo";
    req.state           = kAuthState;
    //第三方向微信终端发送一个SendAuthReq消息结构
    return [WXApi sendAuthReq:req viewController:self delegate:[WXApiManager sharedManager]];
}

- (void)sendLoginMsg2Server:(NSString*) code{
    
    //第一步，创建URL
    NSString *urlstring = [NSString stringWithFormat:@"%s?appid=%@&code=%@",APP_WECHAT_LOGIN,AppID,code];
    NSURL *url = [NSURL URLWithString:urlstring];
    //第二步，创建请求
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:10];
    //第三步，连接服务器
    NSData *received = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
    NSString *result = [[NSString alloc]initWithData:received encoding:NSUTF8StringEncoding];
    //    NSLog(@"received = %@",result);
    //解析返回的json数据
    NSData *returnedData = [result dataUsingEncoding:NSUTF8StringEncoding];;
    if(NSClassFromString(@"NSJSONSerialization"))
    {
        NSError *error = nil;
        id object = [NSJSONSerialization
                     JSONObjectWithData:returnedData
                     options:0
                     error:&error];
        
        if(error) {
            UserData::getInstance()->setWxOpenId("unknow");
            NSLog(@"sendLoginMsg2Server json 格式有错误1");
        }
        if([object isKindOfClass:[NSDictionary class]])
        {
            NSDictionary *results = object;
            NSObject *myresult = [results objectForKey:@"result"];
            NSString *resultstr = [NSString stringWithFormat:@"%@", myresult];
            if(strcmp(std::string([resultstr UTF8String]).c_str(),"0") == 0){
                NSObject *openid = [results objectForKey:@"openid"];
                NSString *openidstr = [NSString stringWithFormat:@"%@", openid];
                NSObject *unionid = [results objectForKey:@"unionid"];
                NSString *unionidstr = [NSString stringWithFormat:@"%@", unionid];
                NSObject *headimgurl = [results objectForKey:@"headimgurl"];
                NSString *headimgurlstr = [NSString stringWithFormat:@"%@", headimgurl];
                NSObject *sex = [results objectForKey:@"sex"];
                NSString *sexStr = [NSString stringWithFormat:@"%@", sex];
                NSObject *nickname = [results objectForKey:@"nickname"];
                NSString *nicknameStr = [NSString stringWithFormat:@"%@", nickname];
                NSString *woman = @"2";
                NSLog(@"wechat sex log = %@",sexStr);
                if([sexStr isEqualToString:woman]){
                    UserData::getInstance()->setGender(0);
                }else{
                    UserData::getInstance()->setGender(1);
                }
//                NSLog(@"IOS WEI XIN OPENID = %s",std::string([openidstr UTF8String]).c_str());
                UserData::getInstance()->setWxOpenId(std::string([openidstr UTF8String]));
                UserData::getInstance()->setWxUnionid(std::string([unionidstr UTF8String]));
                UserData::getInstance()->setPicture(std::string([headimgurlstr UTF8String]));
                UserData::getInstance()->setNickName(std::string([nicknameStr UTF8String]));
                UserData::getInstance()->setHsman(std::string([HSMAN UTF8String]));
                UserData::getInstance()->setHstype(std::string([DEVICESTRING UTF8String]));
                UserData::getInstance()->setImei(std::string([IMEI_IMSI UTF8String]));
                UserData::getInstance()->setImsi(std::string([IMEI_IMSI UTF8String]));
                UserData::getInstance()->setAppVer(std::string([GAME_VERSION UTF8String]));
                WxLoginHandler::getInstance()->doGameLogin(std::string([openidstr UTF8String]), std::string([unionidstr UTF8String]),std::string([headimgurlstr UTF8String]),StringUtils::format("%d",UserData::getInstance()->getGender()),std::string([nicknameStr UTF8String]),std::string([HSMAN UTF8String]),std::string([DEVICESTRING UTF8String]),std::string([IMEI_IMSI UTF8String]),std::string([IMEI_IMSI UTF8String]),std::string([GAME_VERSION UTF8String]));
            }else{
                UserData::getInstance()->setWxOpenId("unknow");
            }
            
        }
        else
        {
            UserData::getInstance()->setWxOpenId("unknow");
            NSLog(@"sendLoginMsg2Server json 格式有错误2");
        }
    }
    else
    {
        UserData::getInstance()->setWxOpenId("unknow");
        NSLog(@"系统版本过低");
    }
}


- (BOOL)checkTokenOutTime{
    //第一步，创建URL
    NSString *openidstr = [NSString stringWithFormat:@"%s", UserData::getInstance()->getWxOpenId().c_str()];
    NSString *urlstring = [NSString stringWithFormat:@"%s?openId=%@",APP_WECHAT_TOKEN_CHECK,openidstr];
    NSURL *url = [NSURL URLWithString:urlstring];
    //第二步，创建请求
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc]initWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:10];
    //第三步，连接服务器
    NSData *received = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
    NSString *result = [[NSString alloc]initWithData:received encoding:NSUTF8StringEncoding];
    //    NSLog(@"received = %@",result);
    //解析返回的json数据
    NSData *returnedData = [result dataUsingEncoding:NSUTF8StringEncoding];;
    if(NSClassFromString(@"NSJSONSerialization"))
    {
        NSError *error = nil;
        id object = [NSJSONSerialization
                     JSONObjectWithData:returnedData
                     options:0
                     error:&error];
        
        if(error) {
            NSLog(@"json 格式有错误1");
        }
        if([object isKindOfClass:[NSDictionary class]])
        {
            NSDictionary *results = object;
            NSObject *myresult = [results objectForKey:@"result"];
            NSString *resultstr = [NSString stringWithFormat:@"%@", myresult];
            if(strcmp(std::string([resultstr UTF8String]).c_str(),"0") == 0){
                NSObject *head = [results objectForKey:@"head"];
                NSString *headstr = [NSString stringWithFormat:@"%@", head];
                UserData::getInstance()->setPicture(std::string([headstr UTF8String]));
                NSObject *sex = [results objectForKey:@"sex"];
                NSString *sexStr = [NSString stringWithFormat:@"%@", sex];
                NSObject *unionid = [results objectForKey:@"unionid"];
                NSString *unionidstr = [NSString stringWithFormat:@"%@", unionid];
                UserData::getInstance()->setWxUnionid(std::string([unionidstr UTF8String]));
                NSString *woman = @"2";
                if([sexStr isEqualToString:woman]){
                    UserData::getInstance()->setGender(0);
                }else{
                    UserData::getInstance()->setGender(1);
                }
                return true;
            }
            
        }
        else
        {
            NSLog(@"json 格式有错误2");
        }
    }
    else
    {
        NSLog(@"系统版本过低");
    }
    UserData::getInstance()->setWxOpenId("unknow");
    [self sendAuthRequestScope];
    return false;
}

//微信分享
- (void) wechatShareApp:(NSString*) contentTile ContentDescription:(NSString*) contentDescription{
    
    Byte* pBuffer = (Byte *)malloc(1024 * 100);
    memset(pBuffer, 0, 1024 * 100);
    NSData* data = [NSData dataWithBytes:pBuffer length:1024 * 100];
    free(pBuffer);
    WXAppExtendObject *ext = [WXAppExtendObject object];
    ext.extInfo = kAppContentExInfo;
    ext.url = kAppContnetExURL;
    ext.fileData = data;
    WXMediaMessage *message = [WXMediaMessage message];
    message.title = contentTile;
    message.description = contentDescription;
    message.mediaObject = ext;
    message.messageExt = kAppMessageExt;
    message.messageAction = kAppMessageAction;
    message.mediaTagName = nil;
    [message setThumbImage:nil];
    SendMessageToWXReq *req = [[[SendMessageToWXReq alloc] init] autorelease];
    req.message = message;
    [WXApi sendReq:req];
}

- (void) wechatShareWeb:(NSString*) url ContentTile:(NSString*) contentTile ContentDescription:(NSString*) contentDescription Scene:(int) inScene{
    WXWebpageObject *ext = [WXWebpageObject object];
    ext.webpageUrl = url;
    
    WXMediaMessage *message = [WXMediaMessage message];
    message.title = contentTile;
    message.description = contentDescription;
    message.mediaObject = ext;
    message.messageExt = kAppMessageExt;
    message.messageAction = kAppMessageAction;
    message.mediaTagName = nil;
    UIImage *thumbImage = [UIImage imageNamed:@"Icon-180.png"];
    [message setThumbImage:thumbImage];
    SendMessageToWXReq *req = [[[SendMessageToWXReq alloc] init] autorelease];
    req.message = message;
    req.scene = inScene;
    [WXApi sendReq:req];
}


- (void) wechatShareImg:(NSData*) imageData Scene:(int) inScene{
    WXImageObject *ext = [WXImageObject object];
    ext.imageData = imageData;
    WXMediaMessage *message = [WXMediaMessage message];
    message.title = nil;
    message.description = nil;
    message.mediaObject = ext;
    message.messageExt = kAppMessageExt;
    message.messageAction = kAppMessageAction;
    message.mediaTagName = nil;
    NSData *newImageData = imageData;
    // 压缩图片data大小
    newImageData = UIImageJPEGRepresentation([UIImage imageWithData:newImageData scale:0.1], 0.1f);
    UIImage *image = [UIImage imageWithData:newImageData];
    // 压缩图片分辨率(因为data压缩到一定程度后，如果图片分辨率不缩小的话还是不行)
    CGSize newSize = CGSizeMake(150, 150);
    UIGraphicsBeginImageContext(newSize);
    [image drawInRect:CGRectMake(0,0,newSize.width,newSize.height)];
    UIImage* newImage = UIGraphicsGetImageFromCurrentImageContext();
    [message setThumbImage:newImage];
    SendMessageToWXReq* req = [[[SendMessageToWXReq alloc] init] autorelease];
    req.message = message;
    req.scene = inScene;
    [WXApi sendReq:req];
}

- (void) updateClientAppVersion {
    UserData::getInstance()->setAppVer(std::string([GAME_VERSION UTF8String]));
}

-(void) payWeChat:(NSString*) poxiaoId PayPoint:(NSString*) payPoint{
    NSString* urlString= [NSString stringWithFormat:@"%s?charge_type=1&tbu_id=201617&pay_platform=apple&game_version=1&hsman=ios&hstype=ios&imei=123456789&imsi=46000&channel_id=apple&request_pay_amount=1&poxiao_id=%@&pay_point=%@",APP_WECHAT_PAY,poxiaoId,payPoint];
    NSLog(@"url:%@",urlString);
    //解析服务端返回json数据
    //加载一个NSURL对象
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    //第三步，连接服务器
    NSData *received = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
    NSString *result = [[NSString alloc]initWithData:received encoding:NSUTF8StringEncoding];
    //    NSLog(@"received = %@",result);
    //解析返回的json数据
    NSData *returnedData = [result dataUsingEncoding:NSUTF8StringEncoding];;
    if(NSClassFromString(@"NSJSONSerialization"))
    {
        NSError *error = nil;
        id object = [NSJSONSerialization
                     JSONObjectWithData:returnedData
                     options:0
                     error:&error];
        
        if(error) {
            NSLog(@"json 格式有错误");
        }
        if([object isKindOfClass:[NSDictionary class]])
        {
            
            NSDictionary *results = object;
            NSObject *myresult = [results objectForKey:@"result"];
            NSString *resultstr = [NSString stringWithFormat:@"%@", myresult];
            if(strcmp(std::string([resultstr UTF8String]).c_str(),"0") == 0){
                NSObject *px_order_id = [results objectForKey:@"px_order_id"];
                NSString* poxiaoOrderId = [NSString stringWithFormat:@"%@", px_order_id];
                UserData::getInstance()->setPoxiaoOrderID(std::string([poxiaoOrderId UTF8String]));
                NSLog(@"poxiaoOrderId == %@",poxiaoOrderId);
                //                NSObject *wx_order_id = [results objectForKey:@"wx_order_id"];
                //                NSString *wxOrderId = [NSString stringWithFormat:@"%@", wx_order_id];
                NSObject *wx_nonce_str = [results objectForKey:@"wx_nonce_str"];
                NSString *wxNonceStr = [NSString stringWithFormat:@"%@", wx_nonce_str];
                NSObject *wx_prepayid = [results objectForKey:@"wx_prepayid"];
                NSString *wxPrepayid = [NSString stringWithFormat:@"%@", wx_prepayid];
                NSObject *wx_sign = [results objectForKey:@"wx_sign"];
                NSString *wxSign = [NSString stringWithFormat:@"%@", wx_sign];
                NSObject *wx_timestamp = [results objectForKey:@"wx_timestamp"];
                int wxTimestamp = [(NSNumber*)wx_timestamp intValue];
                //调起微信支付
                PayReq* req             = [[[PayReq alloc] init]autorelease];
                req.partnerId           = @"1380518102";
                req.prepayId            = wxPrepayid;
                req.nonceStr            = wxNonceStr;
                req.timeStamp           = wxTimestamp;
                req.package             = @"Sign=WXPay";
                req.sign                = wxSign;
                [WXApi sendReq:req];
            }
        }
        else
        {
            NSLog(@"数据格式有错误");
        }
    }
    else
    {
        NSLog(@"系统版本过低");
    }
}


- (BOOL) queryPayResult{
    //    NSLog(@"poxiaoOrderId == %@",poxiaoOrderId);
    NSString* urlString= [NSString stringWithFormat:@"%s?order_id=%s",PAY_WECHAT_QUERY_ORDER,UserData::getInstance()->getPoxiaoOrderID().c_str()];
    NSLog(@"url:%@",urlString);
    //解析服务端返回json数据
    //加载一个NSURL对象
    NSURLRequest *request = [NSURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    //第三步，连接服务器
    NSData *received = [NSURLConnection sendSynchronousRequest:request returningResponse:nil error:nil];
    NSString *result = [[NSString alloc]initWithData:received encoding:NSUTF8StringEncoding];
    //    NSLog(@"received = %@",result);
    //解析返回的json数据
    NSData *returnedData = [result dataUsingEncoding:NSUTF8StringEncoding];;
    if(NSClassFromString(@"NSJSONSerialization"))
    {
        NSError *error = nil;
        id object = [NSJSONSerialization
                     JSONObjectWithData:returnedData
                     options:0
                     error:&error];
        
        if(error) {
            NSLog(@"json 格式有错误");
        }
        if([object isKindOfClass:[NSDictionary class]])
        {
            
            NSDictionary *results = object;
            NSObject *myresult = [results objectForKey:@"result"];
            NSString *resultstr = [NSString stringWithFormat:@"%@", myresult];
            if(strcmp(std::string([resultstr UTF8String]).c_str(),"0") == 1){
                return true;
            }else{
                return false;
            }
        }
        else
        {
            NSLog(@"数据格式有错误");
        }
    }
    else
    {
        NSLog(@"系统版本过低");
    }
    return false;
}

@end
