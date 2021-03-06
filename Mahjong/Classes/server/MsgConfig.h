﻿#ifndef __MSG_CONFIG_H__
#define __MSG_CONFIG_H__


#define MSGCODE_HEARTBEAT  1 //心跳
#define MSGCODE_HEARTBEAT_RETURN  2//心跳回复

#define MSGCODE_QUNEWM_REQUEST  5//玩家群二维码版本号请求 {code:5,poxiaoId:"123"}
#define MSGCODE_QUNEWM_RESPONSE  6// 玩家群二维码版本号回复 {code:6,version:"1",desc:"33"}

#define MSGCODE_GET_GAME_LIST_REQUEST  102//获取游戏列表请求{code:102,poxiaoId:poxiaoId}
#define MSGCODE_GET_GAME_LIST_RESPONSE  103//返回游戏列表回复{code:103,poxiaoId:poxiaoId,game:[{gameid:"1",gamename:"上海麻将"},{gameid:"2",gamename:"长沙麻将"}]}
#define MSGCODE_CHART_REQUEST  104//聊天请求{code:104,poxiaoId:"123",content:"哈哈"}
#define MSGCODE_CHART_NOTIFY  105// 聊天通知{code:105,poxiaoId:"123",content:"哈哈"}
#define MSGCODE_GET_ROOMSTYLE_LIST_REQUEST  106//获取房间列表请求{code:106,poxiaoId:poxiaoId,gameid:1} 麻将游戏id为1
#define MSGCODE_GET_ROOMSTYLE_LIST_RESPONSE  107//返回房间列表回复{code:107,poxiaoId:poxiaoId,roomstyle:[{rsid:"1111",rsname:"初级场",min:123,max:456},{rsid:"1112",rsname:"中级场",min:123,max:456}]} -1为无上下限
#define MSGCODE_LOGIN_GUEST_REQUEST  108// 游客登陆请求{code:108,hsman:厂商,hstype:机型,imsi:imsi,imei:imei}
#define MSGCODE_MODIFY_GENDER_REQUEST  117// 修改性别请求{code:117,poxiaoId:"123",gender:"1"}
#define MSGCODE_MODIFY_GENDER_RESPONSE  118// 修改性别请求{code:118,result:"1"} 1成功 其他 失败
#define MSGCODE_QUIT_REQUEST 120//退出请求 {code:120,poxiaoId:poxiaoId}

#define MSGCODE_GONGGAO_REQUEST  140// 获取公告请求{code:140,poxiaoId:poxiaoId}
#define MSGCODE_GONGGAO_RESPONSE  141// 获取公告回复{code:141,poxiaoId:poxiaoId,content:"11111111"}
#define MSGCODE_MARQUEE_REQUEST  142// 获取走马灯请求{code:142,poxiaoId:poxiaoId}
#define MSGCODE_MARQUEE_RESPONSE  143// 获取走马灯回复{code:143,poxiaoId:poxiaoId,content:"11111111"}

#define MSGCODE_GETINFO_REQUEST  149// 获取用户信息请求{code:140,poxiaoId:poxiaoId}
#define MSGCODE_GETINFO_RESPONSE  150// 获取用户信息回复{code:141,poxiaoId:poxiaoId,lequan:11,bangzuan:22,diamond:33,gold:55,jifen:0}
#define MSGCODE_MODIFY_PIC_REQUEST  152// 修改图片请求{code:152,poxiaoId:"123",pic:"1"}
#define MSGCODE_MODIFY_PIC_RESPONSE  153// 修改图片回复{code:153,result:"1",gender:1} 1成功 其他 失败

#define MSGCODE_FEEDBACK_REQUEST  154// 用户反馈请求{code:154,poxiaoId:poxiaoId,content:"llllll"}
#define MSGCODE_FEEDBACK_RESPONSE  155// 用户反馈回复{code:155,poxiaoId:poxiaoId,result:"1"} 1成功 0 5分钟内发送一次
#define MSGCODE_OTHER_REPLACE  156// 用户在别的设备上登陆{code:156,poxiaoId:poxiaoId}

#define MSGCODE_APPLE_SWITCH_REQUEST  157// 苹果开关请求{code:157,poxiaoId:poxiaoId}
#define MSGCODE_APPLE_SWITCH_RESPONE  158// 苹果开关回复{code:158,poxiaoId:poxiaoId,result:0} 0关1开

#define MSGCODE_PLAY_BACK_REQUEST  159// 获取回放请求{code:159,poxiaoId:poxiaoId,recordid:"123"}
#define MSGCODE_PLAY_BACK_RESPONE  160// 获取回放回复{code:160,poxiaoId:poxiaoId,playback:"sfdsafd"}


#define MSGCODE_SPREAD_NEWUSER_REQUEST  161// 获取推广请求{code:161,poxiaoId:poxiaoId}
#define MSGCODE_SPREAD_NEWUSER_RESPONSE  162// 获取推广回复{code:162,poxiaoId:poxiaoId,reward:[{gold:50000},{fangka:1}],result:1,havegot:[{gold:50000},{fangka:1},{people:1}],willget:[{gold:50000},{fangka:1},{people:1}]}
#define MSGCODE_SPREAD_NEWUSER_REWARD_REQUEST  163// 领取推广奖励请求{code:163,poxiaoId:poxiaoId}
#define MSGCODE_SPREAD_NEWUSER_REWARD_RESPNOSE  164// 领取推广奖励回复{code:164,poxiaoId:poxiaoId,result:0}

#define MSGCODE_HUODONG_REQUEST  165// 获取活动请求{code:165,poxiaoId:poxiaoId}
#define MSGCODE_HUODONG_RESPONSE  166// 获取活动回复{code:166,poxiaoId:poxiaoId,content:[{pic:"http://1212.com",url:"11",time:"6"},{pic:"http://1212.com",url:"11",time:"6"}]}

#define MSGCODE_IDCARD_REQUEST  167// 实名认证请求{code:167,poxiaoId:poxiaoId,name:"",idcard:""}
#define MSGCODE_IDCARD_RESPONSE  168// 实名认证回复{code:168,poxiaoId:poxiaoId,result:0}


#define MSGCODE_YQM_REQUEST  169// 输入邀请码请求{code:169,poxiaoId:poxiaoId,yqm:"1235"}
#define MSGCODE_YQM_RESPONSE  170// 输入邀请码回复{code:170,poxiaoId:poxiaoId,result:0}  0输入错误 1正确

#define MSGCODE_DZP_REQUEST  171// 大转盘请求{code:171,poxiaoId:poxiaoId}
#define MSGCODE_DZP_RESPONSE  172// 大转盘回复{code:172,poxiaoId:poxiaoId,result:1,content:[{fangka:1,ratio:385},{fangka:5,ratio:40},{fangka:20,ratio:3},{fee:1.88,ratio:230},{fee:2.88,ratio:77},{fee:5.88,ratio:23},{fee:18.88,ratio:7},{fee:88.88,ratio:1},{iphone7:1,ratio:0},{nothing:1,ratio:234}]}
#define MSGCODE_DZP_Z_REQUEST  173// 大转盘转起来请求{code:173,poxiaoId:poxiaoId}
#define MSGCODE_DZP_Z_RESPONSE  174// 大转盘转起来回复{code:173,poxiaoId:poxiaoId,result:1,content:{fangka:1,ratio:385}} result为0则大转盘关闭
#define MSGCODE_DZP_Z_SHARE_REQUEST  175  // 大转盘转起来分享成功请求{code:175,poxiaoId:poxiaoId}
#define MSGCODE_DZP_B_SHARE_REQUEST  176// 大转盘分享成功请求{code:176,poxiaoId:poxiaoId}
#define MSGCODE_DZP_B_SHARE_RESPONSE  177// 大转盘分享成功回复{code:177,poxiaoId:poxiaoId,result:"1"} 1为有转盘机会 0表示没有

#define MSGCODE_PHB_REQUEST  178// 排行榜请求{code:178,poxiaoId:poxiaoId}
#define MSGCODE_PHB_RESPONSE  179// 排行榜回复{code:179,poxiaoId:poxiaoId,name1:"",tab1:[{key:"",value:""},{key:"",value:""}],name2:"",tab2:[{key:"",value:""},{key:"",value:""}],name3:"",tab3:[{key:"",value:""},{key:"",value:""}]}

#define MSGCODE_THIRED_LOGIN_REQUEST  999//第三方登录请求{code:999,open_id:123,type:1,hsman:厂商,hstype:机型,imsi:imsi,imei:imei} typ为1表示微信
#define MSGCODE_INTO_ROOMSTYLE_REQUEST  1000 //进入房间请求{code:1000,poxiaoId:poxiaoId,rsid:1111,gameid:"1"}
#define MSGCODE_INTO_ROOMSTYLE_RESPONSE 1001 //进入房间回复{code:1001,poxiaoId:poxiaoId,result:"0",seatId:1,other:[{seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:1}]} result1为成功 2为金币低于下限 3为金币高于上线 4为其他错误
#define  MSGCODE_LOGIN_REQUEST  1003//{code:1003,username:username,password:password,hsman:厂商,hstype:机型,imsi:imsi,imei:imei}
#define MSGCODE_LOGIN_RESPONSE  1005// 服务端到客户端登陆回复{code:1005,result:0,poxiaoId:poxiaoId,username:"avc",password:"123",result:1,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:0,moblie:"1111"}result1成功 2 用户名已存在 3验证码错误  4其他错误   gender性别0女1男 ifready准备0未准备1准备
#define MSGCODE_READY_REQUEST  1006// 客户端到服务端准备请求{code:1006,poxiaoId:poxiaoId}
#define MSGCODE_LOGIN_NOTIFY  1008// 服务端到客户端登陆通知{code:1008,result:0,poxiaoId:poxiaoId,seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:0} gender性别0女1男 ifready准备0未准备1准备
#define MSGCODE_READY_NOTIFY  1009// 服务端到客户端准备通知{code:1009,poxiaoId:poxiaoId,seatId:1}
#define MSGCODE_DX_NOTIFY  1010// 服务端到客户端掉线通知{code:1010,poxiaoId:poxiaoId}


#define MSGCODE_LOTTERY_REQUEST  1022// 金币抽奖情况获取请求{code:1022,poxiaoId:poxiaoId}
#define MSGCODE_LOTTERY_RESPONSE  1023// 金币抽奖情况获取回复{code:1023,poxiaoId:poxiaoId,result:"1",gold:"50000",prize:[{gold:30000},{lequan:300},{lequan:800},{lequan:100},{bangzuan:80},{bangzuan:50},{bangzuan:20},{gold:60000},{diamond:11}],count:"1",max:"5"} result1为可以参加，0为不可参加 ，count为可以抽奖几次，max为最多能抽奖几次，prize奖品里面数值为整数
#define MSGCODE_LOTTERY_GET_REQUEST  1024// 金币抽奖奖励领取请求{code:1024,poxiaoId:poxiaoId}
#define MSGCODE_LOTTERY_GET_RESPONSE  1025// 金币抽奖奖励领取回复{code:1025,poxiaoId:poxiaoId,result:"1",prize:{gold:10}} 1为成功 0失败,prize为抽到的奖品，奖品里面数值为整数

#define MSGCODE_LEQUAN_MALL_REQUEST  1040// 乐券商城请求{code:1040,poxiaoId:poxiaoId}
#define MSGCODE_LEQUAN_MALL_RESPONSE  1041// 乐券商城回复{code:1041,poxiaoId:poxiaoId,mall:[{goodsId:"1",goodsName:"手机",goodsPrice:"100"},{goodsId:"2",goodsName:"流量",goodsPrice:"1000"}]}
#define MSGCODE_LEQUAN_MALL_EXCHANGE_REQUEST  1042// 乐券商城兑换请求{code:1042,poxiaoId:poxiaoId,phone:"13999999",address:"浙江杭州",name:"张三",goodsId:"1"}
#define MSGCODE_LEQUAN_MALL_EXCHANGE_RESPONSE  1043// 乐券商城兑换回复{code:1043,poxiaoId:poxiaoId,result:"1"} 1成功0失败

#define MSGCODE_CHARGE_LIST_REQUEST  1044// 充值列表请求{code:1044,poxiaoId:poxiaoId}
#define MSGCODE_CHARGE_LIST_RESPONSE  1045// 充值列表回复{code:1045,poxiaoId:poxiaoId,list:[{id:"1",money:"1000",diamond:"100"},{id:"2",money:"2000",diamond:"200"}]}
#define MSGCODE_CHARGE_REQUEST  1046// 充值下单请求{code:1046,poxiaoId:poxiaoId,gameId:"1",channelId:"lele",feecode:"12",money:"100",chargetype:"1"}
#define MSGCODE_CHARGE_RESPONSE  1047// 充值下单回复{code:1047,poxiaoId:poxiaoId,result:"1",orderId:"201601010111"} 1成功0失败

#define MSGCODE_EXCHANGE_LIST_REQUEST  1048// 兑换列表请求{code:1048,poxiaoId:poxiaoId}
#define MSGCODE_EXCHANGE_LIST_RESPONSE  1049// 兑换列表回复{code:1049,poxiaoId:poxiaoId,list:[{id:"1",gold:"1000",diamond:"100"},{id:"2",gold:"2000",diamond:"200"}]}
#define MSGCODE_EXCHANGE_REQUEST  1050// 兑换请求{code:1050,poxiaoId:poxiaoId,gold:"1000"}
#define MSGCODE_EXCHANGE_RESPONSE  1051// 兑换回复{code:1051,poxiaoId:poxiaoId,result:"1"} 1成功0失败

#define MSGCODE_FIRST_CHARGE_GET_REQUEST  1052// 首次充值獲取请求{code:1052,poxiaoId:poxiaoId}
#define MSGCODE_FIRST_CHARGE_GET_RESPONSE  1053// 首次充值获取回复{code:1053,poxiaoId:poxiaoId,gold:"123",diamond:"456"}
#define MSGCODE_FIRST_CHARGE_REQUEST  1054// 首次充值下单请求{code:1054,poxiaoId:poxiaoId,gameId:"1",channelId:"lele",feecode:"12",money:"100",chargetype:"1"}
#define MSGCODE_FIRST_CHARGE_RESPONSE  1055// 首次充值下单回复{code:1055,poxiaoId:poxiaoId,result:"1",orderId:"201601010111"} 1成功0失败

#define MSGCODE_LEQUAN_MALL_EXCHANGE_RECORD_REQUEST  1056// 乐券商城兑换记录请求{code:1056,poxiaoId:poxiaoId}
#define MSGCODE_LEQUAN_MALL_EXCHANGE_RECORD_RESPONSE  1057// 乐券商城兑换记录回复{code:1057,poxiaoId:poxiaoId,list:[{id:"1",status:"1"},{id:"2",status:"2"}]} //0兑换中 1已兑换

//#define MSGCODE_FEE_EXCHANGE_REQUEST  1066// 话费兑换请求{code:1066,poxiaoId:poxiaoId,phone:"13999999",goodsId:"1"}  goodsId 3为30话费 4为50话费 5为100话费
//#define MSGCODE_FEE_EXCHANGE_RESPONSE  1067// 话费兑换回复{code:1067,poxiaoId:poxiaoId,result:"1"} 1成功0失败
#define MSGCODE_FEE_EXCHANGE_RECORD_REQUEST  1068// 话费兑换记录请求{code:1068,poxiaoId:poxiaoId}
#define MSGCODE_FEE_EXCHANGE_RECORD_RESPONSE  1069// 话费兑换\房卡兑换记录回复{code:1069,poxiaoId:poxiaoId,list:[{id:"3",url:"",status:"1",fee:"",time:""},{id:"4",url:"",status:"2",fee:"",time:""}],list1:[{fangka:"3",url:"",time:""},{fangka:"4",url:"",time:""}]} //0兑换中 1已兑换
#define MSGCODE_FEE_LIST_REQUEST  1070// 话费兑换列表请求{code:1070,poxiaoId:poxiaoId}
#define MSGCODE_FEE_LIST_RESPONSE  1071// 话费兑换列表回复{code:1071,poxiaoId:poxiaoId,list:[{url:"http://web.5278-mobi.com:1112/30.jpg",goods_id:3},{url:"http://web.5278-mobi.com:1112/50.jpg",goods_id:4},{url:"http://web.5278-mobi.com:1112/100.jpg",goods_id:5},{url:"http://web.5278-mobi.com:1112/200.jpg",goods_id:6}]}



#define MSGCODE_FEE_GET_REQUEST  1072// 红包领取请求{code:1072,poxiaoId:poxiaoId}
#define MSGCODE_FEE_GET_RESPONSE  1073// 红包领取回复{code:1073,poxiaoId:poxiaoId,result:1}1成功  0失败
#define MSGCODE_FEE_GIVEUP_REQUEST  1074// 红包领取放弃请求{code:1074,poxiaoId:poxiaoId}

#define MSGCODE_FEE_TO_FANGKA_LIST_REQUEST  1075// 话费兑换房卡列表请求{code:1075,poxiaoId:poxiaoId}
#define MSGCODE_FEE_TO_FANGKA_LIST_RESPONSE  1076// 话费兑换房卡列表回复{code:1076,poxiaoId:poxiaoId,list1:[{url:"http://web.5278-mobi.com:1112/30.jpg",fee:30,tofangka:30},{url:"http://web.5278-mobi.com:1112/50.jpg",fee:50,tofangka:50},{url:"http://web.5278-mobi.com:1112/100.jpg",fee:100,tofangka:100},{url:"http://web.5278-mobi.com:1112/200.jpg",fee:200,tofangka:200}],list2:[{url:"http://web.5278-mobi.com:1112/30.jpg",fangka:30,tofee:30},{url:"http://web.5278-mobi.com:1112/50.jpg",fangka:50,tofee:50},{url:"http://web.5278-mobi.com:1112/100.jpg",fangka:100,tofee:100},{url:"http://web.5278-mobi.com:1112/200.jpg",fangka:200,tofee:200}]}
#define MSGCODE_FEE_TO_FANGKA_REQUEST  1077// 话费兑换房卡请求{code:1077,poxiaoId:poxiaoId,fee:"30",phone:""}
#define MSGCODE_FEE_TO_FANGKA_RESPONSE  1078// 话费兑换房卡回复{code:1078,poxiaoId:poxiaoId,result:"1",fangka:"1",fee:"2"} 1成功0失败
#define MSGCODE_FANGKA_TO_FEE_REQUEST  1079// 房卡兑换房卡请求{code:1079,poxiaoId:poxiaoId,fangka:"30"}
#define MSGCODE_FANGKA_TO_FEE_RESPONSE  1080// 话费兑换房卡回复{code:1080,poxiaoId:poxiaoId,result:"1",fangka:"1",fee:"2"} 1成功0失败

#define MSGCODE_SPREAD_RESULT_REQUEST  1081// 获取推广结果请求{code:1081,poxiaoId:poxiaoId}
#define MSGCODE_SPREAD_RESULT_RESPONSE  1082//获取推广结果回复{code:1082,poxiaoId:poxiaoId,desc:"上方文字",content: [{nickname:"123",count:"1",money:"1"}]}

#define MSGCODE_MAJIANG_BACK_OUT_REQUEST 1992//后台切出请求{code:1992,poxiaoId:poxiaoId}

#define MSGCODE_GAME_CHART_REQUEST  1993//游戏内聊天请求{code:1993,poxiaoId:"123",content:"哈哈",pId:"11111"}
#define MSGCODE_GAME_CHART_NOTIFY 1994// 游戏内聊天通知{code:1994,poxiaoId:"456",nickname:"",content:"哈哈"}

#define MSGCODE_MAJIANG_AGAIN_REQUEST 1995//再来一局请求{code:1995,poxiaoId:poxiaoId}
#define MSGCODE_MAJIANG_AGAIN_RESPONSE 1996//再来一局回复{code:1996,poxiaoId:poxiaoId,result:1,rsid:1000}1为成功 2为金币小于下限 3为金币高于上限rsid为跳转房间
//#define MSGCODE_MAJIANG_BACK_RESUME_REQUEST 1997//后台切回请求{code:1997,poxiaoId:poxiaoId}
//#define MSGCODE_MAJIANG_BACK_RESUME_RESPONSE 1998//后台切回回复{code:1998,poxiaoId:poxiaoId,seatId:1,lord:1,rest:"123",status:1,all:[{seatId:1,hua:"1",chi:[{chi:"1,2,3",poker:"3"},{chi:"11,12,13",poker:"13"}],peng:[{peng:"11",peId:"1"},{peng:"12",peId:"2"}],gang:[{gang:"11",gaId:"1"},{gang:"12",gaId:"2"}],angang:"6",out:"11,22,33,44",gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',hand:"2",status:1}]} status1为听牌
#define MSGCODE_MAJIANG_KICKOUT_REQUEST  2000// 剔除玩家请求{code:2000,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_KICKOUT_NOTIFY  2001// 剔除玩家通知{code:2001,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_DISCARD_NOTIFY  2002// 开始游戏，发牌通知{code:2002,poxiaoId:poxiaoId,start:1,dice:"3,6",poker:1,2,4,5,6} start为开始的玩家座位号

#define MSGCODE_MAJIANG_DISPATCH_REQUEST  2004// 出牌请求{code:2004,poxiaoId:poxiaoId,seatId:seatId,poker:poker}
#define MSGCODE_MAJIANG_DISPATCH_NOTIFY  2005// 出牌通知{code:2005,poxiaoId:poxiaoId,seatId:seatId,poker:poker}

#define MSGCODE_MAJIANG_PLAYER_CPG_NOTIFY  2006//玩家吃碰杠通知{code:2006,poxiaoId:poxiaoId,seatId:seatId,poker:1,chi:[{chi:2,3},{chi:3,4}],peng:"1,2,3",gang:"1,1,1,1"}

#define MSGCODE_MAJIANG_CHI_REQUEST  2007// 确认吃牌请求{code:2007,poxiaoId:poxiaoId,seatId:seatId,chi:"1,2",poker:poker}
#define MSGCODE_MAJIANG_CHI_RESPONSE  2009// 吃牌回复{code:2009,poxiaoId:poxiaoId,seatId:seatId,result:1}  1成功0失败
#define MSGCODE_MAJIANG_NO_CHI_PENG_GANG_REQUEST  2008// 取消吃碰杠牌请求{code:2008,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_CHI_NOTIFY  2010// 吃牌通知{code:2010,poxiaoId:poxiaoId,seatId:seatId,chi:"1,2",poker:poker} seatId为吃牌人的座位号

#define MSGCODE_MAJIANG_PENG_REQUEST  2011// 碰牌请求{code:2011,poxiaoId:poxiaoId,seatId:seatId,peng:"1,2",poker:poker}
#define MSGCODE_MAJIANG_NO_CHI_PENG_GANG_RESPONSE  2012// 取消吃碰杠回复{code:2012,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_PENG_RESPONSE  2013// 碰牌回复{code:2013,poxiaoId:poxiaoId,seatId:seatId,result:1}  1成功0失败
#define MSGCODE_MAJIANG_PENG_NOTIFY  2014// 碰牌通知{code:2014,poxiaoId:poxiaoId,seatId:seatId,peng:"1,2",poker:poker} seatId为碰牌人的座位号

#define MSGCODE_MAJIANG_GANG_REQUEST  2015// 杠牌请求{code:2015,poxiaoId:poxiaoId,seatId:seatId,gang:"1,1,1",poker:poker,flag:0} flag 0为明杠1为暗杠,2碰杠
#define MSGCODE_MAJIANG_NO_TING_GANG_REQUEST  2016// 取消听牌杠牌请求{code:2016,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_GANG_RESPONSE  2017// 杠牌回复{code:2017,poxiaoId:poxiaoId,seatId:seatId,result:1}  1成功0失败
#define MSGCODE_MAJIANG_GANG_NOTIFY  2018// 杠牌通知{code:2018,poxiaoId:poxiaoId,seatId:seatId,gang:"1,1,1",poker:poker} seatId为杠牌人的座位号

#define MSGCODE_MAJIANG_POKER_NOTIFY  2019//游戏中发牌{code:2019,poxiaoId:poxiaoId,seatId:seatId,poker:{poker:1,hua:32,33}}poker为花时替换牌
#define MSGCODE_MAJIANG_TING_GANG_NOTIFY  2020// 听牌杠牌通知{code:2020,poxiaoId:poxiaoId,seatId:seatId,ting:"1,2,3",angang:"1,1,1,1",penggang:"1"} ting为打掉那张牌可以听牌
#define MSGCODE_MAJIANG_NO_TING_GANG_RESPONSE  2021// 取消吃碰杠回复{code:2021,poxiaoId:poxiaoId,seatId:seatId}

#define MSGCODE_MAJIANG_TING_REQUEST  2022// 听牌请求{code:2022,poxiaoId:poxiaoId,seatId:seatId,poker:"1"} poker为打出的牌
#define MSGCODE_MAJIANG_TING_RESPONSE  2023// 听牌回复{code:2023,poxiaoId:poxiaoId,seatId:seatId,result:1}  1成功0失败
#define MSGCODE_MAJIANG_HU_NOTIFY  2024// 胡牌通知{code:2024,poxiaoId:poxiaoId,seatId:seatId,poker:1,hu:[{poxiaoId:1,seatId:1},{poxiaoId:1,seatId:1}]} 结算

#define MSGCODE_MAJIANG_TING_NOTIFY  2025// 听牌群发通知{code:2025,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_OUT_REQUEST  2026//退出游戏请求{code:2026,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_OUT_RESPONSE  2027// 退出游戏回复{code:2027,poxiaoId:poxiaoId,seatId:seatId,result:1}

#define MSGCODE_MAJIANG_TRUSTEESHIP_REQUEST  2028// 托管请求{code:2028,poxiaoId:poxiaoId,seatId:seatId}

#define MSGCODE_MAJIANG_TRUSTEESHIP_RESPONSE  2035// 托管回復{code:2035,poxiaoId:poxiaoId}
#define MSGCODE_MAJIANG_CANCEL_TRUSTEESHIP_REQUEST  2029// 取消托管请求{code:2029,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_MAJIANG_CANCEL_TRUSTEESHIP_RESPONSE  2030// 取消托管回复{code:2030,poxiaoId:poxiaoId,pId:pId}

#define MSGCODE_MAJIANG_OUTLINE_RESUME_NOTIFY  2031//断线续玩{code:2031,poxiaoId:poxiaoId,seatId:seatId,all:[{seatId:1,hua:"1,2,3",chi:"4,5,6",peng:"7,7,7",gang:"6,6,6,6",angang:"6,6,6,6",hand:"1,2,3,4,5",out:"11,22,33,44"},{seatId:2,hua:"1,2,3",chi:"4,5,6",peng:"7,7,7",gang:"6,6,6,6",angang:"6,6,6,6",hand:"1,2,3,4,5",out:"11,22,33,44"},{seatId:3,hua:"1,2,3",chi:"4,5,6",peng:"7,7,7",gang:"6,6,6,6",angang:"6,6,6,6",hand:"1,2,3,4,5",out:"11,22,33,44"},{seatId:4,hua:"1,2,3",chi:"4,5,6",peng:"7,7,7",gang:"6,6,6,6",angang:"6,6,6,6",hand:"1,2,3,4,5",out:"11,22,33,44"}]}
#define MSGCODE_MAJIANG_CHART_REQUEST  2032//{code:2032,poxiaoId:poxiaoId,seatId:seatId,no:"1"}
#define MSGCODE_MAJIANG_CHART_NOTIFY  2033//{code:2033,poxiaoId:poxiaoId,seatId:seatId,nickName:"12",content:"你好啊1234"}

#define MSGCODE_MAJIANG_TRUSTEESHIP_NOTIFY  2034// 托管通知{code:2034,poxiaoId:poxiaoId,pId:pId}

#define MSGCODE_FRIEND_GAME_REQUEST  2036// 好友开房请求{code:2036,poxiaoId:"123",pId:"456,789,333,444,555"}
#define MSGCODE_FRIEND_GAME_NOTIFY  2037// 好友开房通知{code:2037,poxiaoId:"123",nickname:"aaa",pId:"456"}
#define MSGCODE_FRIEND_GAME_RESPONSE  2038//好友开房回复{code:2038,poxiaoId:poxiaoId,result:"0",seatId:1}
#define MSGCODE_FRIEND_JOIN_GAME_REQUEST  2039// 好友加入房间请求{code:2039,poxiaoId:"123",pId:"456"}
#define MSGCODE_FRIEND_JOIN_GAME_RESPONSE  2040//好友进入房间回复{code:2040,poxiaoId:poxiaoId,result:0,seatId:1,other:[{seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:1,pic:"1"}]} result 1为成功 2为房间已满

#define MSGCODE_FRIEND_GAME_BILL_REQUEST  2041//获取账单请求{code:2041,poxiaoId:poxiaoId}
#define MSGCODE_FRIEND_GAME_BILL_RESPONSE  2042//获取账单回复{code:2042,poxiaoId:poxiaoId,bill:[{date:"2015-06-06 15:15",count:"10",billid:"8888888888",content:[{nickname:"张三",score:"1000"},{nickname:"李四",score:"2000"},{nickname:"王五",score:"1000"},{nickname:"赵六",score:"1100"}]}]}
#define MSGCODE_FRIEND_GAME_BILL_DETAIL_REQUEST  2043//获取账单明细请求{code:2043,poxiaoId:poxiaoId,billid:"8888"}
#define MSGCODE_FRIEND_GAME_BILL_DETAIL_RESPONSE  2044//获取账单明细回复{code:2044,poxiaoId:poxiaoId,detail:[{nickname:"张三",score:"1000"},{nickname:"李四",score:"2000"},{nickname:"王五",score:"-1000"},{nickname:"赵六",score:"-1100"}]}
#define MSGCODE_FRIEND_GAME_RESULT_NOTIFY  2045// 好友邀请结果通知{code:2045,poxiaoId:"123",pId:"456",result:1} result 为1是好友不在线 2是好友在游戏中，邀请成功不发送次通知
#define MSGCODE_FRIEND_JOIN_GAME_FJH_REQUEST  2046// 好友输入房间号加入房间请求{code:2046,poxiaoId:"123",prId:"456"}
#define MSGCODE_FRIEND_DISMISS_NOTIFY  2047// 私人房间可以解散通知{code:2047,poxiaoId:"123"}
#define MSGCODE_FRIEND_DISMISS_FZAGREE_REQUEST  2048//私人房间房主解散请求{code:2048,poxiaoId:poxiaoId}
#define MSGCODE_FRIEND_DISMISS_AGREE_NOTIFY  2049// 私人房间是否同意解散通知{code:2049,poxiaoId:"123"}
#define MSGCODE_FRIEND_DISMISS_AGREE_REQUEST  2050//私人房间是否同意解散请求{code:2050,poxiaoId:poxiaoId,agree:0} 0为不同意 1为同意
#define MSGCODE_FRIEND_DISMISS_AGREE_RESULT_NOTIFY  2051//私人房间是否同意解散通知{code:2051,poxiaoId:poxiaoId,pId:11,agree:0} 0为不同意 1为同意,pId为谁同意了或则不同意了
#define MSGCODE_FRIEND_DISMISS_FZ_REQUEST  2052//私人房间房主解散请求{code:2052,poxiaoId:poxiaoId}
#define MSGCODE_FANG_REQUEST  2053//开房进房前请求{code:2053,poxiaoId:poxiaoId}
#define MSGCODE_FANG_RESPONSE  2054//开房进房前回复{code:2054,poxiaoId:poxiaoId}
#define MSGCODE_FANG1_REQUEST  2055//开房进房前请求{code:2055,poxiaoId:poxiaoId}
#define MSGCODE_FANG1_RESPONSE  2056//开房进房前回复{code:2056,poxiaoId:poxiaoId}
#define MSGCODE_FANGZHU_OUT  2057//开房进房前回复{code:2057,poxiaoId:poxiaoId,seatId:1}

#define MSGCODE_MATCH_SIGN_REQUEST  2058//上海麻将比赛报名请求{code:2058,poxiaoId:poxiaoId,id:"1"}
#define MSGCODE_MATCH_SIGN_RESPONSE  2059//上海麻将比赛报名回复{code:2059,poxiaoId:poxiaoId,result:0} result0失败 1成功
#define MSGCODE_MATCH_OUT_REQUEST  2060//上海麻将比赛开始通知{code:2060,poxiaoId:poxiaoId}
#define MSGCODE_MATCH_OUT_RESPONSE  2061//上海麻将比赛退赛回复{code:2061,poxiaoId:poxiaoId,result:0} result0失败 1成功
#define MSGCODE_MATCH_START_NOTIFY  2062//上海麻将比赛开始通知{code:2062,poxiaoId:poxiaoId}
#define MSGCODE_MATCH_ADDPLAYER_NOTIFY  2063//比赛加人通知{code:2063,poxiaoId:poxiaoId}

#define MSGCODE_FUPAN_PLAYER_NOTIFY  10000//复盘玩家数据

/**
 红中麻将协议
 **/
#define MSGCODE_HH_MAJIANG_BACK_OUT_REQUEST 2997//后台切出请求{code:2997,poxiaoId:poxiaoId}
#define MSGCODE_HH_MAJIANG_AGAIN_REQUEST 2998//再来一局请求{code:2998,poxiaoId:poxiaoId}
#define MSGCODE_HH_MAJIANG_AGAIN_RESPONSE 2999//再来一局回复{code:2999,poxiaoId:poxiaoId,result:1,rsid:1000,kb:"1"}1为成功 2为金币小于下限 3为金币高于上限rsid为跳转房间

#define MSGCODE_HH_READY_REQUEST   3000// 晃晃麻将客户端到服务端准备请求{code:3000,poxiaoId:poxiaoId}
#define MSGCODE_HH_READY_RESPONSE   3001 // 晃晃麻将服务端到客户端准备回复{code:3001,poxiaoId:poxiaoId,result:1,rsid:'1111'}
#define MSGCODE_HH_LOGIN_NOTIFY   3002 // 晃晃麻将服务端到客户端登陆通知{code:3002,result:0,poxiaoId:poxiaoId,seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:0,pId:pId} gender性别0女1男 ifready准备0未准备1准备
#define MSGCODE_HH_READY_NOTIFY   3003 // 晃晃麻将服务端到客户端准备通知{code:3003,poxiaoId:poxiaoId,seatId:1}
#define MSGCODE_HH_MAJIANG_DISCARD_NOTIFY   3004 // 晃晃麻将开始游戏,发牌通知{code:3004,poxiaoId:poxiaoId,start:1,dice:"3,6",poker:"1,2,4,5,6",kb:"1",hf:"2",prjucount:1} 私人房间进行到的局数prjucount
#define MSGCODE_HH_MAJIANG_DISPATCH_REQUEST   3005 // 晃晃麻将出牌请求{code:3005,poxiaoId:poxiaoId,seatId:seatId,poker:poker}
#define MSGCODE_HH_MAJIANG_DISPATCH_NOTIFY   3006 // 晃晃麻将出牌通知{code:3006,poxiaoId:poxiaoId,seatId:seatId,poker:poker}
#define MSGCODE_HH_MAJIANG_PLAYER_CPG_NOTIFY   3007 //晃晃麻将玩家碰杠通知{code:3007,poxiaoId:poxiaoId,seatId:seatId,poker:1,peng:"1,2,3",gang:"1,1,1,1"}
#define MSGCODE_HH_MAJIANG_PENG_REQUEST   3008 // 晃晃麻将碰牌请求{code:3008,poxiaoId:poxiaoId,seatId:seatId,peng:"1,2",poker:poker}
#define MSGCODE_HH_MAJIANG_PENG_RESPONSE   3009 // 晃晃麻将碰牌回复{code:3009,poxiaoId:poxiaoId,seatId:seatId,result:1,ting:"1,2,3"}  1成功0失败
#define MSGCODE_HH_MAJIANG_PENG_NOTIFY   3010 // 晃晃麻将碰牌通知{code:3010,poxiaoId:poxiaoId,seatId:seatId,peng:"1,2",poker:poker,sId:2} seatId为碰牌人的座位号
#define MSGCODE_HH_MAJIANG_GANG_REQUEST   3011 // 晃晃麻将杠牌请求{code:3011,poxiaoId:poxiaoId,seatId:seatId,gang:"1,1,1",poker:poker,flag:0} flag 0为明杠1为暗杠,2碰杠
#define MSGCODE_HH_MAJIANG_GANG_RESPONSE   3012 // 晃晃麻将杠牌回复{code:3012,poxiaoId:poxiaoId,seatId:seatId,result:1}  1成功0失败
#define MSGCODE_HH_MAJIANG_GANG_NOTIFY   3013 // 晃晃麻将杠牌通知{code:3013,poxiaoId:poxiaoId,seatId:seatId,gang:"1,1,1",poker:poker,flag:0,sId:2} seatId为杠牌人的座位号 1暗杠 2碰杠 0普通杠
#define MSGCODE_HH_MAJIANG_NO_CHI_PENG_GANG_REQUEST   3014 // 晃晃麻将取消碰杠牌请求{code:3014,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_HH_MAJIANG_NO_CHI_PENG_GANG_RESPONSE   3015 // 晃晃麻将取消碰杠回复{code:3015,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_HH_MAJIANG_POKER_NOTIFY   3016 //晃晃麻将游戏中发牌{code:3016,poxiaoId:poxiaoId,seatId:seatId,poker:{poker:1,hua:32,33}}poker为花时替换牌
#define MSGCODE_HH_MAJIANG_FINISH_NOTIFY   3017 //晃晃麻将结算通知 ,结算,result0为平,1为自摸,2为放炮 3胡牌  4输
//{code:3017,flag:"1",poxiaoId:poxiaoId,seatId:seatId,poker:1,finish:[{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0,hua:1,poker:1,2,3},{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0,hua:1,poker:1,2,3}]}
#define MSGCODE_HH_MAJIANG_OUT_REQUEST   3018 //晃晃麻将退出游戏请求{code:3018,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_HH_MAJIANG_OUT_RESPONSE   3019 // 晃晃麻将退出游戏回复{code:3019,poxiaoId:poxiaoId,seatId:seatId,result:1}
#define MSGCODE_HH_MAJIANG_OUTLINE_RESUME_NOTIFY 3020 //断线续完{code:3020,poxiaoId:poxiaoId,seatId:1,lord:1,rest:"123",status:1,all:[{seatId:1,peng:[{peng:"11",peId:"1"},{peng:"12",peId:"2"}],gang:[{gang:"11",gaId:"1"},{gang:"12",gaId:"2"}],angang:"6",out:"11,22,33,44",gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',hand:"2",prId:"123",fzId:"456",prjucount:"1",prjushu:"2"}]}
#define MSGCODE_HH_FRIEND_GAME_REQUEST   3021 // 晃晃麻将好友开房请求{code:3021,poxiaoId:"123",difen:"",fanma:"",ftype:"8"
#define MSGCODE_HH_FRIEND_GAME_NOTIFY   3022 // 晃晃麻将好友开房通知{code:3022,poxiaoId:"123",nickname:"aaa",pId:"456"}
#define MSGCODE_HH_FRIEND_GAME_RESPONSE   3023 //晃晃麻将好友开房回复{code:3023,poxiaoId:poxiaoId,result:"0",seatId:1,prId:"1234",prjushu:"8"} prjushu 8\16
#define MSGCODE_HH_FRIEND_JOIN_GAME_REQUEST   3024 // 晃晃麻将好友加入房间请求{code:3024,poxiaoId:"123",pId:"456"}
#define MSGCODE_HH_FRIEND_JOIN_GAME_RESPONSE   3025 //晃晃麻将好友进入房间回复{code:3025,poxiaoId:poxiaoId,result:0,seatId:1,other:[{seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:1,pic:"1"}],prId:"1234",prjushu:"8",iflezi:"0"} iflezi为0表示无勒子1表示有勒子 result 0为自己在游戏中 1为成功 2为房间已满
//#define MSGCODE_HH_FRIEND_GAME_BILL_REQUEST   3026 //晃晃麻将获取账单请求{code:3026,poxiaoId:poxiaoId}
//#define MSGCODE_HH_FRIEND_GAME_BILL_RESPONSE   3027 //晃晃麻将获取账单回复{code:3027,poxiaoId:poxiaoId,bill:[{date:"2015-06-06 15:15",count:"10",prId:"123",atype:"0",billid:"8888888888",content:[{nickname:"张三",score:"1000"},{nickname:"李四",score:"2000"},{nickname:"王五",score:"1000"},{nickname:"赵六",score:"1100"}]}]}
#define MSGCODE_HH_FRIEND_GAME_RESULT_NOTIFY   3028 // 晃晃麻将好友邀请结果通知{code:3028,poxiaoId:"123",pId:"456",result:1,nickname:"xxx"} result 为1是好友不在线 2是好友在游戏中，邀请成功不发送次通知
#define MSGCODE_HH_FRIEND_JOIN_GAME_FJH_REQUEST   3029 // 晃晃麻将好友输入房间号加入房间请求{code:3029,poxiaoId:"123",prId:"456"}

#define MSGCODE_HH_FRIEND_DISMISS_NOTIFY   3030 // 晃晃麻将私人房间可以解散通知{code:3030,poxiaoId:"123"}
#define MSGCODE_HH_FRIEND_DISMISS_FZAGREE_REQUEST   3031 //晃晃麻将私人房间房主解散请求{code:3031,poxiaoId:poxiaoId}
#define MSGCODE_HH_FRIEND_DISMISS_AGREE_NOTIFY   3032 // 晃晃麻将私人房间是否同意解散通知{code:3032,poxiaoId:"123"}
#define MSGCODE_HH_FRIEND_DISMISS_AGREE_REQUEST   3033 //晃晃麻将私人房间是否同意解散请求{code:3033,poxiaoId:poxiaoId,agree:0} 0为不同意 1为同意
#define MSGCODE_HH_FRIEND_DISMISS_AGREE_RESULT_NOTIFY   3034 //晃晃麻将私人房间是否同意解散通知{code:3034,poxiaoId:poxiaoId,pId:11,agree:0} 0为不同意 1为同意,pId为谁同意了或则不同意了
#define MSGCODE_HH_FRIEND_DISMISS_FZ_REQUEST   3035 //晃晃麻将私人房间房主解散请求{code:3035,poxiaoId:poxiaoId}
//#define MSGCODE_HH_FANMA_DISMISS_NOTIFY   3036 // 晃晃麻将翻码通知{code:3036,poxiaoId:"123",ma:"1,2,3"}
#define MSGCODE_HH_IFHU_NOTIFY  3037// 晃晃麻将可以胡通知{code:3037,poxiaoId:"123"}
#define MSGCODE_HH_IFHU_REQUEST  3038// 晃晃麻将胡牌请求{code:3038,poxiaoId:"123",flag:"1"} flag为1是确认胡牌，2是取消胡牌


/*  崇明麻将的协议   */
#define MSGCODE_CM_MAJIANG_BACK_OUT_REQUEST 4000  //后台切出请求{code:4000,poxiaoId:poxiaoId}
#define MSGCODE_CM_MAJIANG_AGAIN_REQUEST 4001  //再来一局请求{code:4001,poxiaoId:poxiaoId}
#define MSGCODE_CM_MAJIANG_AGAIN_RESPONSE 4002  //再来一局回复{code:4002,poxiaoId:poxiaoId,result:1,rsid:1000,kb:"1"}1为成功 2为金币小于下限 3为金币高于上限rsid为跳转房间
#define MSGCODE_CM_READY_REQUEST   4003  // 崇明麻将客户端到服务端准备请求{code:4003,poxiaoId:poxiaoId}
#define MSGCODE_CM_LOGIN_NOTIFY   4005  // 崇明麻将服务端到客户端登陆通知{code:4005,result:0,poxiaoId:poxiaoId,seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:0,pId:pId} gender性别0女1男 ifready准备0未准备1准备
#define MSGCODE_CM_READY_NOTIFY   4006  // 崇明麻将服务端到客户端准备通知{code:5006,poxiaoId:poxiaoId,seatId:1}
#define MSGCODE_CM_MAJIANG_DISCARD_NOTIFY   4008  // 开始游戏,发牌通知{code:4008,poxiaoId:poxiaoId,start:1,dice:"3,6",poker:"1,2,4,5,6",kb:"1",hf:"2",prjucount:1,matchname:"10元比赛"} 私人房间进行到的局数prjucount

#define MSGCODE_CM_MAJIANG_DISPATCH_REQUEST   4010  // 出牌请求{code:4010,poxiaoId:poxiaoId,seatId:seatId,poker:poker}
#define MSGCODE_CM_MAJIANG_DISPATCH_NOTIFY   4011  // 出牌通知{code:4011,poxiaoId:poxiaoId,seatId:seatId,poker:poker}
#define MSGCODE_CM_MAJIANG_PLAYER_CPG_NOTIFY   4012  //玩家胡吃碰杠通知{code:4012,poxiaoId:poxiaoId,seatId:seatId,poker:1,hu:"1",chi:[{chi:1,2,3},{chi:2,3,4}],peng:"1,2,3",gang:"1,1,1,1"}
#define MSGCODE_CM_MAJIANG_CHI_REQUEST   4013  // 确认吃牌请求{code:4013,poxiaoId:poxiaoId,seatId:seatId,chi:"1,2",poker:poker}
#define MSGCODE_CM_MAJIANG_CHI_RESPONSE   4014  // 吃牌回复{code:4014,poxiaoId:poxiaoId,seatId:seatId,result:1}  1成功0失败
#define MSGCODE_CM_MAJIANG_CHI_NOTIFY   4015  // 吃牌通知{code:4015,poxiaoId:poxiaoId,seatId:seatId,chi:"1,2",poker:poker,sId:2} seatId为吃牌人的座位号
#define MSGCODE_CM_MAJIANG_PENG_REQUEST   4016  // 碰牌请求{code:4016,poxiaoId:poxiaoId,seatId:seatId,peng:"1,2",poker:poker}
#define MSGCODE_CM_MAJIANG_PENG_RESPONSE   4017  // 碰牌回复{code:4017,poxiaoId:poxiaoId,seatId:seatId,result:1,ting:"1,2,3"}  1成功0失败
#define MSGCODE_CM_MAJIANG_PENG_NOTIFY   4018  // 碰牌通知{code:4018,poxiaoId:poxiaoId,seatId:seatId,peng:"1,2",poker:poker,sId:2} seatId为碰牌人的座位号
#define MSGCODE_CM_MAJIANG_GANG_REQUEST   4019  // 杠牌请求{code:4019,poxiaoId:poxiaoId,seatId:seatId,gang:"1,1,1",poker:poker,flag:0} flag 0为明杠1为暗杠,2碰杠
#define MSGCODE_CM_MAJIANG_GANG_RESPONSE   4020  // 杠牌回复{code:4020,poxiaoId:poxiaoId,seatId:seatId,result:1}  1成功0失败
#define MSGCODE_CM_MAJIANG_GANG_NOTIFY   4021  // 杠牌通知{code:4021,poxiaoId:poxiaoId,seatId:seatId,gang:"1,1,1",poker:poker,flag:0,sId:2} seatId为杠牌人的座位号 1暗杠 2碰杠 0普通杠
#define MSGCODE_CM_MAJIANG_NO_CHI_PENG_GANG_REQUEST   4022  // 取消吃碰杠牌请求{code:4022,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_CM_MAJIANG_NO_CHI_PENG_GANG_RESPONSE   4023  // 取消吃碰杠回复{code:4023,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_CM_MAJIANG_POKER_NOTIFY   4024  //游戏中发牌{code:4024,poxiaoId:poxiaoId,seatId:seatId,poker:{poker:1,hua:32,33},hu:"1",angang:"",penggang:""}poker为花时替换牌,hu为是否可以胡牌,angang暗杠 penggang 碰杠
#define MSGCODE_CM_MAJIANG_TING_GANG_NOTIFY   4025  // 杠牌通知{code:4025,poxiaoId:poxiaoId,seatId:seatId,ting:"1,2,3",angang:"1,1,1,1",penggang:"1"} ting为打掉那张牌可以听牌
#define MSGCODE_CM_MAJIANG_NO_TING_GANG_REQUEST   4026  // 取消杠牌请求{code:4026,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_CM_MAJIANG_NO_TING_GANG_RESPONSE   4027  // 取消杠牌回复{code:4027,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_CM_MAJIANG_FINISH_NOTIFY   4028  //结算通知 ,结算,result0为平,1为自摸,2为放炮 3胡牌  4输
//{code:4028,flag:"1",poxiaoId:poxiaoId,seatId:seatId,poker:1,finish:[{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0,hua:1,poker:1,2,3},{result:1,hutype:1,2,3,seatId:1,nickname:"rr",gold:0,diamond:0,jifen:0,lequan:0,golddelta:0,diamonddelta:0,jifendelta:0,lequandelta:0,hua:1,poker:1,2,3}]}
#define MSGCODE_CM_MAJIANG_OUT_REQUEST   4029  //退出游戏请求{code:4029,poxiaoId:poxiaoId,seatId:seatId}
#define MSGCODE_CM_MAJIANG_OUT_RESPONSE   4030  // 退出游戏回复{code:4030,poxiaoId:poxiaoId,seatId:seatId,result:1}
#define MSGCODE_CM_MAJIANG_OUTLINE_RESUME_NOTIFY 4031
//断线续完{code:4031,poxiaoId:poxiaoId,seatId:1,lord:1,rest:"123",status:1,all:[{seatId:1,hua:"1",chi:[{chi:"1,2,3",poker:"3"},{chi:"11,12,13",poker:"13"}],peng:[{peng:"11",peId:"1"},{peng:"12",peId:"2"}],gang:[{gang:"11",gaId:"1"},{gang:"12",gaId:"2"}],angang:"6",out:"11,22,33,44",gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',hand:"2",status:1,prId:"123",fzId:"456",prjucount:"1",prjushu:"2"}],matchname:"10元比赛"} status1为听牌
#define MSGCODE_CM_FRIEND_GAME_REQUEST   4032  // 好友开房请求{code:4032,poxiaoId:"123",ftype:"1",ifkb:"0",size:"4",fcy:"1",dihua:"1",lz:"1"} ftype 1为打八局 2为打4局3为16局 ifkb 0为无开宝,1为有开宝 size4为4人2为2人,fcy飞苍蝇0为无,1为有,dihua 0为1/1 1为2/2 2为6/2 3为5/5,lz0为20勒子 1为50勒子 2为100勒子 3为无勒子
#define MSGCODE_CM_FRIEND_GAME_RESPONSE  4034  //好友开房回复{code:4034,poxiaoId:poxiaoId,result:"0",seatId:1,prId:"1234",prjushu:"8"} prjushu 8\16

#define MSGCODE_CM_FRIEND_JOIN_GAME_RESPONSE   4036  //好友进入房间回复{code:4036,poxiaoId:poxiaoId,result:0,seatId:1,other:[{seatId:seatId,gold:0,diamond:0,jifen:0,lequan:0,gender:0,nickname:'aaa',ifready:1,pic:"1"}],prId:"1234",prjushu:"8",iflezi:"0"} iflezi为0表示无勒子1表示有勒子 result 0为自己在游戏中 1为成功 2为房间已满
#define MSGCODE_CM_FRIEND_JOIN_GAME_FJH_REQUEST   4037  // 好友输入房间号加入房间请求{code:4037,poxiaoId:"123",prId:"456"}

#define MSGCODE_CM_FRIEND_DISMISS_NOTIFY   4038  // 私人房间可以解散通知{code:4038,poxiaoId:"123"}
#define MSGCODE_CM_FRIEND_DISMISS_FZAGREE_REQUEST   4039  //私人房间解散请求{code:4039,poxiaoId:poxiaoId}
#define MSGCODE_CM_FRIEND_DISMISS_AGREE_NOTIFY   4040  // 私人房间是否同意解散通知{code:4040,poxiaoId:"123"}
#define MSGCODE_CM_FRIEND_DISMISS_AGREE_REQUEST   4041  //私人房间是否同意解散请求{code:4041,poxiaoId:poxiaoId,agree:0} 0为不同意 1为同意
#define MSGCODE_CM_FRIEND_DISMISS_AGREE_RESULT_NOTIFY   4042  //私人房间是否同意解散通知{code:4042,poxiaoId:poxiaoId,pId:11,agree:0} 0为不同意 1为同意,pId为谁同意了或则不同意了
#define MSGCODE_CM_FRIEND_DISMISS_FZ_REQUEST   4043  //私人房间房主解散请求{code:4043,poxiaoId:poxiaoId}
#define MSGCODE_CM_IFHU_NOTIFY   4044  // 崇明麻将可以胡通知{code:4044,poxiaoId:"123"}
#define MSGCODE_CM_IFHU_REQUEST   4045  // 崇明麻将胡牌请求{code:4045,poxiaoId:"123",flag:"1"} flag为1是确认胡牌，2是取消胡牌

#define LOGIN_SUCCESS "login_success"
#define MSG_VISITOR_LOGIN_RESP  "msg_visitor_login_resp"
#define MSG_LOGIN_RESP  "msg_login_resp"
#define MSG_ROOM_LIST_RESP "msg_room_list_resp"
#define MSG_ENTER_ROOM_RESP "msg_enter_room_resp"
#define MSG_ENTER_FRIEND_ROOM_RESP "msg_enter_friend_room_resp"
#define MSG_READY_RESP "msg_ready_resp"
#define MSG_READY_NOTIFY "msg_ready_notify"
#define MSG_OTHER_PALYER_JONG "msg_other_palyer_jong"
#define MSG_GAME_START_FAPAI_NOTIFY "MSG_GAME_START_FAPAI_NOTIFY"
#define MSG_PLAYER_TURN_WHO "msg_player_turn_who"
#define MSG_PLAYER_CPG "msg_player_cpg"
#define MSG_OTHER_PLAYER_CHI "msg_other_player_chi"
#define MSG_OTHER_PLAYER_PENG "msg_other_player_peng"
#define MSG_OTHER_PLAYER_GANG "msg_other_player_gang"
#define MSG_HERO_TING_GANG "msg_hero_ting_gang"
#define MSG_PLAYER_TING_RESP "msg_player_ting_resp"
#define MSG_GAME_RESULT "msg_game_result"
#define MSG_PLAYER_TING_NOTIFY "msg_player_ting_notify"
#define MSG_OUTLINE_RESUME_NOTIFY "msg_outline_resume_notify"
#define MSG_CHANGE_NICKNAME_RESP "msg_change_nickname_resp"
#define MSG_CHANGE_GENDER_RESP "msg_change_gender_resp"
#define MSG_HERO_CHI_RESP "msg_hero_chi_resp"
#define MSG_HERO_PENG_RESP "msg_hero_peng_resp"
#define MSG_HERO_GANG_RESP "msg_hero_gang_resp"
#define MSG_PLAYER_REMOVE "msg_player_remove"
#define MSG_FRIEND_OPEN_ROOM_RESP "msg_friend_open_room_resp"
#define MSG_FRIEND_OPEN_ROOM_NOTIFY "msg_friend_open_room_notify"
#define MSG_FRIEND_ENTER_ROOM_RESP "msg_friend_enter_room_resp"
#define MSG_PLAYER_CHAT_NOTIFY "msg_player_chat_notify"
#define MSG_PLAYER_CONNECT_AGAIN "msg_player_connect_again"
#define MSG_PLAYER_BILL "msg_player_bill"
#define MSG_PLAYER_BILL_DETAIL "msg_player_bill_detail"
#define MSG_PLAYER_DAILY_PRIDE "msg_player_daily_pride"
#define MSG_PLAYER_TODAY_PRIDE "msg_player_today_pride"
#define MSG_PLAYER_FIRST_CHARGE "msg_player_first_charge"
#define MSG_PLAYER_GOLD_CHANGE_LIST "msg_player_gold_change_list"
#define MSG_PLAYER_GOLD_CHANGE_RESP "msg_player_gold_change_resp"
#define MSG_PLAYER_LEQUAN_CHANGE_LIST "msg_player_lequan_change_list"
#define MSG_UPDATE_HEAD_IMAGE "msg_update_head_image"
#define MSG_PLAYER_LEQUAN_EXCHANGE "msg_player_lequan_exchange"
#define MSG_PLAYER_LEQUAN_EXCHANGE_RECORD "msg_player_lequan_exchange_record"
#define MSG_HERO_CONTINUE_RESP "msg_hero_continue_resp"
#define MSG_PLAYER_OFF_LINE_NOTIFY "msg_player_off_line_notify"
#define MSG_PLAYER_CHANGE_HEAD_RESP "msg_player_change_head_resp"
#define MSG_PLAYER_FEED_BACK_RESP "msg_player_feed_back_resp"
#define MSG_PLAYER_RESUME_GAME "msg_player_resume_game"
#define MSG_PLAYER_ROOM_CHAT_SHOW "msg_player_room_chat_show"
#define MSG_LOBBY_ASK_OPEN_ROOM "MSG_LOBBY_ASK_OPEN_ROOM"
#define MSG_LOBBY_ASK_ENTER_ROOM "MSG_LOBBY_ASK_ENTER_ROOM"
#define MSG_DISSOVLE_ROOM_NOTIFY "MSG_DISSOVLE_ROOM_NOTIFY"
#define MSG_FANGZHU_DISSOVLE_ROOM_NOTIFY "MSG_FANGZHU_DISSOVLE_ROOM_NOTIFY"
#define MSG_DISSOVLE_ROOM_SELECTED_NOTIFY "MSG_DISSOVLE_ROOM_SELECTED_NOTIFY"
#define MSG_QUIR_GAME_VIEW_RESP "MSG_QUIR_GAME_VIEW_RESP"
#define MSG_SCROLL_TEXT "MSG_SCROLL_TEXT"
#define MSG_WAN_JIA_WEI_XIN_QUN "MSG_WAN_JIA_WEI_XIN_QUN"
#define MSG_WAN_JIA_GONG_GAO "MSG_WAN_JIA_GONG_GAO"
#define MSG_UPDATE_LEQUAN_SHANG_CHEN_SHOW "MSG_UPDATE_LEQUAN_SHANG_CHEN_SHOW"
#define MSG_WAN_JIA_GONG_GAO_SHOW_DIALOG "MSG_WAN_JIA_GONG_GAO_SHOW_DIALOG"
#define MSG_UPDATE_SHOP_PROP_IMAG "MSG_UPDATE_SHOP_PROP_IMAG"
#define GET_JJJ_RESPONSE_REMOVE_LOADING "get_jjj_response_remove_loading"
#define UPDATE_JJJ_COUNT_RESP "update_jjj_count_resp"
#define UPDATE_DICE_KAOBAO_STATE "update_dice_kaibao_dtate"
#define FRIEND_IS_PLAYING_GAME "friend_is_playing_game" //好友在游戏中
#define MSG_PLAYER_REPLACE_LOGIN "msg_player_replace_login"//在其他的机子上登录
#define MSG_UPDATE_PLAYER_WECHAT_IMAGE "MSG_UPDATE_PLAYER_WECHAT_IMAGE"
#define MSG_GAME_SHOW_LAYER "MSG_GAME_SHOW_LAYER"
#define MSG_LOBBY_SHOW_LOADING_LAYER "MSG_LOBBY_SHOW_LOADING_LAYER"
#define MSG_GAME_FU_PAN_NOTIFY "MSG_GAME_FU_PAN_NOTIFY"
#define MSG_GAME_FU_PAN_PLAYER_NOTIFY "MSG_GAME_FU_PAN_PLAYER_NOTIFY"
#define MSG_GAME_FANG_ZHU_LEAVE "MSG_GAME_FANG_ZHU_LEAVE"
#define MSG_GET_TUI_GUANG_PRIDE "MSG_GET_TUI_GUANG_PRIDE"
#define MSG_GET_WAN_JIA_GONG_GAO "MSG_GET_WAN_JIA_GONG_GAO"
#define MSG_GET_WAN_JIA_SHI_MING "MSG_GET_WAN_JIA_SHI_MING"
#define MSG_NETWORK_BREAK_INFO "MSG_NETWORK_BREAK_INFO"
/** 红中麻将**/
#define MSG_ENTER_FRIEND_ROOM_HONGZHONG_RESP "MSG_ENTER_FRIEND_ROOM_HONGZHONG_RESP"
#define MSG_HZ_ENTER_FRIEND_ROOM_RESP "MSG_HZ_ENTER_FRIEND_ROOM_RESP"
#define MSG_HZ_OTHER_PALYER_JONG "MSG_HZ_OTHER_PALYER_JONG"
#define MSG_HZ_PLAYER_TURN_WHO "MSG_HZ_PLAYER_TURN_WHO"
#define MSG_HZ_GAME_START_FAPAI_NOTIFY "MSG_HZ_GAME_START_FAPAI_NOTIFY"
#define MSG_HZ_PLAYER_CONNECT_AGAIN "MSG_HZ_PLAYER_CONNECT_AGAIN"
#define MSG_HZ_PLAYER_PG "MSG_HZ_PLAYER_PG"
#define MSG_HZ_GAME_RESULT "MSG_HZ_GAME_RESULT"
#define MSG_HZ_GAME_HU_ACTION "MSG_HZ_GAME_HU_ACTION"
#define MSG_HZ_DISSOVLE_ROOM_SELECTED_NOTIFY "MSG_HZ_DISSOVLE_ROOM_SELECTED_NOTIFY"
#define MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_HZ "MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_HZ"
#define MSG_HZ_PLAYER_PENG "MSG_HZ_PLAYER_PENG"
#define MSG_HZ_PLAYER_PENG_RESP "MSG_HZ_PLAYER_PENG_RESP"
#define MSG_HZ_PLAYER_GANG "MSG_HZ_PLAYER_GANG"
#define MSG_HZ_HERO_CONTINUE_RESP "MSG_HZ_HERO_CONTINUE_RESP"
#define MSG_INVITE_CODE_RESP "MSG_INVITE_CODE_RESP"
#define MSG_JOIN_COMPETITION_RESP "MSG_JOIN_COMPETITION_RESP"
#define MSG_COMPETITION_QUEUE_RESP "MSG_COMPETITION_QUEUE_RESP"
#define MSG_QUIT_COMPETITON_RESP "MSG_QUIT_COMPETITON_RESP"
#define MSG_COMPETITION_START_NOTIFY "MSG_COMPETITION_START_NOTIFY"
#define MSG_COMPETITION_ADD_PLAYER_NOTIFY "MSG_COMPETITION_ADD_PLAYER_NOTIFY"
#define MSG_PLAYER_HUAFEI_CHANGE_LIST  "MSG_PLAYER_HUAFEI_CHANGE_LIST"
#define MSG_PLAYER_HUAFEI_CHANGE_RESP  "MSG_PLAYER_HUAFEI_CHANGE_RESP"
#define MSG_PLAYER_HAUFEI_EXCHANGE_RECORD "MSG_PLAYER_DUIHUAN_EXCHANGE_RECORD"
#define MSG_PLAYER_TRU_NOTIFY "MSG_PLAYER_TRU_NOTIFY"
#define MSG_UPDATE_LOBBY_RANK "MSG_UPDATE_LOBBY_RANK"
#define MSG_PLAYER_TURNTABLE_PRIDE "MSG_PLAYER_TURNTABLE_PRIDE"
#define MSG_PLAYER_TURNTABLE_PRIDE_RESULT "MSG_PLAYER_TURNTABLE_PRIDE_RESULT"
#define MSG_PLAYER_TURNTABLE_PRIDE_SHARE "MSG_PLAYER_TURNTABLE_PRIDE_SHARE"
#define MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_NEW "MSG_DISSOVLE_ROOM_SELECTED_NOTIFY_NEW"
/*崇明麻将*/
#define MSG_CM_FRIEND_OPEN_ROOM_RESP "MSG_CM_FRIEND_OPEN_ROOM_RESP"
#define MSG_CM_ENTER_FRIEND_ROOM_RESP "MSG_CM_ENTER_FRIEND_ROOM_RESP"
#define MSG_PLAYER_CM_CONNECT_AGAIN "MSG_PLAYER_CM_CONNECT_AGAIN"
#define MSG_CM_OTHER_PALYER_JONG "MSG_CM_OTHER_PALYER_JONG"
#define MSG_CM_PLAYER_TURN_WHO "MSG_CM_PLAYER_TURN_WHO"
#define MSG_CM_PLAYER_CPG "MSG_CM_PLAYER_CPG"
#define MSG_CM_GAME_HU_ACTION "MSG_CM_GAME_HU_ACTION"
#define MSG_PLAYER_LA_XIN_DATA "MSG_PLAYER_LA_XIN_DATA"
#endif
