//
//  GameConfig.h
//  Mahjong
//
//  Created by qiuzhong on 16/8/19.
//
//

#ifndef GameConfig_h
#define GameConfig_h

#define PAY_PLAT_VALUE "11" //ios支付版本

#define SERVER_ADDRESS "aliyun.5278-mobi.com"
#define SERVER_PORT 9999

#define ENTER_ROOM_1_GOLD 60000// 进入第1个房间需要的最低金币
#define ENTER_ROOM_2_GOLD 150000// 进入第2个房间需要的最低金币
#define ENTER_ROOM_3_GOLD 1200000// 进入第3个房间需要的最低金币
#define DIAMOND_TO_GOLD_RATE 10//钻石兑换金币的比例

#define APPLE_STORE_PAY_LIST "http://aliyun.5278-mobi.com:1111/pay!getIosPoint.action"

#define APP_WECHAT_LOGIN "http://aliyun.5278-mobi.com:1111/pay!getWxAccessToken.action"

#define APP_STORE_PAY_ORDER "http://aliyun.5278-mobi.com:1111/pay!iosOrderVerify.action"

#define APP_WECHAT_TOKEN_CHECK "http://aliyun.5278-mobi.com:1111/login!getIfExpire.action"

#define APP_WECHAT_PAY "http://aliyun.5278-mobi.com:1111/pay!generateOrd.action"

#define PAY_WECHAT_QUERY_ORDER "http://aliyun.5278-mobi.com:1111/pay!findOrd.action"

#define WECHAT_SHARE_HONGBAO_URL "http://aliyun.5278-mobi.com:1112/hongbao.jsp"
#define WECHAT_SHARE_FRIEND_URL "http://aliyun.5278-mobi.com:1112/majiang.html"

#define WECHAT_WAN_JIA_QUN_URL "http://aliyun.5278-mobi.com:1112/qunewm.png"
#define WECHAT_DAI_LI_QUN_URL "http://aliyun.5278-mobi.com:1112/dlewm.png"

#define WECHAT_SHARE_LINK_PATH_1 "https://open.weixin.qq.com/connect/oauth2/authorize?appid=wxfce3a9ed72a95342&redirect_uri=http%3a%2f%2faliyun.5278-mobi.com%2fcallback!getWxUserInfo.action&response_type=code&scope=snsapi_userinfo&state="
#define WECHAT_SHARE_LINK_PATH_2 "&connect_redirect=1#wechat_redirect"

#define IAMGE_LOADING "image_loading"
#define SHARE_TEXT_1 "小白相上海敲麻——有无勒子,2摸3冲随意选择"
#define SHARE_TEXT_2 "最方便的手机麻将馆,随时组局,玩金币房还可以用乐券换话费,是模子才告诉侬格!点击即可下载!"
#define SHARE_TEXT_3 "来来来,房间开好了,麻将搓起来!"
#endif /* GameConfig_h */