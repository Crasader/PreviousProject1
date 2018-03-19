//
//  FanPaiView.hpp
//  SuZhouMahjong
//
//  Created by qiuzhong on 2017/11/7.
//

#ifndef FanPaiView_hpp
#define FanPaiView_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "mahjong/gameview/baseview/BaseView.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class FanPaiView : public BaseView
{
public:
    
    virtual bool init() override;
    CREATE_FUNC(FanPaiView);
    virtual void onEnter() override;
    virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
    void dealJongFinish(MahjongFaPaiData data);//发牌结束处理
    void showBaiDaControllPad(PlayerCpgtData cpgtData);//显示碰杠胡控制板
    void hideBaiDaControllPad();//隐藏碰杠胡控制板
    void showHuPaiXing(std::string paixing);
    void showHandPokerOver(int seatId);
private:
    bool turnHeroSelf = false;
    void initFanPaiMahjong();
    void checkHeroHandPoker();//检查手牌,锁住非花的牌
    void doRecoverGame();
    void doRecoverPlayer(PlayerGameData data, int type, PlayerInfo* playerInfo);
    void doBaiDaQiAction(Ref* ref);
    void doBaiDaHuAction(Ref* ref);
    void doBaiDaPengAction(Ref* ref);
    void doBaiDaGangAction(Ref* ref);
    void showBaiDaGangChoice(Ref* ref);
    
    EventListenerCustom* faPaiNotifyListener;//发牌
    EventListenerCustom* turnListener;//轮到出牌
    EventListenerCustom* otherPlayerPlayedListener;//其他玩家出牌
    EventListenerCustom* playerCpgListener;//碰杠操作
    EventListenerCustom* gameResultListener;//结算
    EventListenerCustom* othersPengListener;//其他玩家碰
    EventListenerCustom* othersGangListener;//其他玩家杠
    EventListenerCustom* trusteeshipNotifyListener;//托管通知
    EventListenerCustom* trusteeshipCancelListener;//取消托管
    EventListenerCustom* heroPengRespListener;//碰牌回复
    EventListenerCustom* heroGangRespListener;//杠牌回复
    EventListenerCustom* conncetAgainListener;//重新连接
    EventListenerCustom* openFriendRoomListener;//好友房间游戏未开始重新连接
    EventListenerCustom* enterFriendRoomListener;//好友房间游戏未开始重新连接
    EventListenerCustom* playeHuActionListener;//可以胡牌通知
};
#endif /* FanPaiView_hpp */
