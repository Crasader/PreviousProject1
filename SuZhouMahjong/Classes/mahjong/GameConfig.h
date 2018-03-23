//
//  GameConfig.h
//  Mahjong
//
//  Created by qiuzhong on 16/8/19.
//
//

#ifndef GameConfig_h
#define GameConfig_h

#define PAY_PLAT_VALUE "18" //ios审核版本18

#define SERVER_ADDRESS "cs.5278-mobi.com"
#define SERVER_ADDRESS_2 "cs.5278-mobi.com"
//#define SERVER_ADDRESS "test.5278-mobi.com"
//#define SERVER_ADDRESS_2 "test.5278-mobi.com"
#define SERVER_PORT 5555

#define APPLE_STORE_PAY_LIST "http://sz.5278-mobi.com:9090/pay/getIosPoint.htm"

#define APP_STORE_PAY_ORDER "http://sz.5278-mobi.com:9090/pay/iosOrderVerify.htm"

#define APP_WECHAT_LOGIN "http://sz.5278-mobi.com:9090/pay/getWxAccessToken.htm"

#define APP_WECHAT_TOKEN_CHECK "http://sz.5278-mobi.com:9090/pay/getIfExpire.htm"

#define APP_WECHAT_PAY "http://sz.5278-mobi.com:9090/pay/generateOrd.htm"

#define PAY_WECHAT_QUERY_ORDER "http://sz.5278-mobi.com:9090/pay/findOrd.htm"

#define WECHAT_SHARE_BILL_DETAIL "http://web1.5278-mobi.com:1112/szmj/szmj.jsp"

#define WECHAT_SHARE_LINK_PATH_1 "https://open.weixin.qq.com/connect/oauth2/authorize?appid=wxfce3a9ed72a95342&redirect_uri=http%3a%2f%2fwyhl.5278-mobi.com%2fcallback!getWxUserInfo.action&response_type=code&scope=snsapi_userinfo&state="
#define WECHAT_SHARE_LINK_PATH_2 "&connect_redirect=1#wechat_redirect"

#define IAMGE_LOADING "image_loading"

#define ROOM_SIZE  "4"

#endif /* GameConfig_h */
