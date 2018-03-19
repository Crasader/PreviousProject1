//
//  HongZhongView.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/4/5.
//
//

#ifndef HongZhongView_hpp
#define HongZhongView_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "mahjong/gameview/baseview/BaseView.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class HongZhongView : public BaseView{
public:
    
    virtual bool init() override;
    CREATE_FUNC(HongZhongView);
    virtual void onEnter() override;
    virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
    void dealJongFinish(MahjongFaPaiData data);//发牌结束处理
    void showHongZhongControllPad(PlayerCpgtData cpgtData);//显示碰杠胡控制板
    void hideHongZhongControllPad();//隐藏碰杠胡控制板
    void showHuPaiXing(std::string paixing);
    void showHandPokerOver(int seatId);
private:
    bool turnHeroSelf = false;
    void initHongZhongMahjong();
    void update(float dt) override;
    void doRecoverGame();
    void firstPlayPoker(PlayerCpgtData data);
    void doRecoverPlayer(PlayerGameData data, int type, PlayerInfo* playerInfo);
    void doHongZhongQiAction(Ref* ref);
    void doHongZhongHuAction(Ref* ref);
    void doHongZhongPengAction(Ref* ref);
    void doHongZhongGangAction(Ref* ref);
    void showHongZhongGangChoice(Ref* ref);
    void checkHeroHandPoker();
    
    EventListenerCustom* faPaiNotifyListener;//发牌
    EventListenerCustom* turnListener;//出牌
    EventListenerCustom* otherListener;//其他玩家出牌
    EventListenerCustom* playerCpgListener;//碰杠操作
    EventListenerCustom* gameResultListener;//结算
    EventListenerCustom* othersPengListener;//其他玩家碰
    EventListenerCustom* othersGangListener;//其他玩家杠
    EventListenerCustom* hzPengRespListener;//碰牌回复
    EventListenerCustom* playeHuActionListener;//可以胡牌通知
    EventListenerCustom* trusteeshipNotifyListener;//托管通知
    EventListenerCustom* trusteeshipCancelListener;//取消托管
    EventListenerCustom* lobbyConncetAgainListener;//重新连接
    EventListenerCustom* hzEnterFriendRoomListener;//好友房间游戏未开始重新连接
    EventListenerCustom* hzOpenFriendRoomListener;//好友房间游戏未开始重新连接
};
#endif /* HongZhongView_hpp */
