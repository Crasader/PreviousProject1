//
//  GameConfig.h
//  Mahjong
//
//  Created by qiuzhong on 16/8/19.
//
//

#ifndef GameConfig_h
#define GameConfig_h

#define PAY_PLAT_VALUE "51" //ios审核版本51，应用宝审核版本52. 奇数是IOS,偶数是Android

//#define SERVER_ADDRESS "aliyun.5278-mobi.com"
#define SERVER_ADDRESS "ceshi.5278-mobi.com"
#define SERVER_ADDRESS_2 "aliyun.kx5278.com"
#define SERVER_PORT 9999

#define ENTER_ROOM_1_GOLD 60000// 进入第1个房间需要的最低金币
#define ENTER_ROOM_2_GOLD 150000// 进入第2个房间需要的最低金币
#define ENTER_ROOM_3_GOLD 1200000// 进入第3个房间需要的最低金币userbk

#define APPLE_STORE_PAY_LIST "http://pay.5278-mobi.com/pay!getIosPoint.action"

#define APP_WECHAT_LOGIN "http://pay.5278-mobi.com/pay!getWxAccessToken.action"

#define APP_STORE_PAY_ORDER "http://pay.5278-mobi.com/pay!iosOrderVerify.action"

#define APP_WECHAT_TOKEN_CHECK "http://pay.5278-mobi.com/login!getIfExpire.action"

#define APP_WECHAT_PAY "http://pay.5278-mobi.com/pay!generateOrd.action"

#define PAY_WECHAT_QUERY_ORDER "http://pay.5278-mobi.com/pay!findOrd.action"

#define WECHAT_SHARE_BILL_DETAIL "http://web1.5278-mobi.com:1112/hongbao.jsp"

#define WECHAT_SHARE_LINK_PATH_1 "https://open.weixin.qq.com/connect/oauth2/authorize?appid=wxfce3a9ed72a95342&redirect_uri=http%3a%2f%2fwyhl.5278-mobi.com%2fcallback!getWxUserInfo.action&response_type=code&scope=snsapi_userinfo&state="
#define WECHAT_SHARE_LINK_PATH_2 "&connect_redirect=1#wechat_redirect"

#define IAMGE_LOADING "image_loading"
#define SHARE_TEXT_1 "小白相上海敲麻——正宗敲麻，红中麻将随意选择。"
#define SHARE_TEXT_2 "最方便的手机麻将馆，随时组局，简单好玩！点击即可下载游戏!"
#define SHARE_TEXT_3 "来来来,房间开好了,麻将搓起来!"

#endif /* GameConfig_h */
