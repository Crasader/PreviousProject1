#ifndef __SUZHOU_REVIEW__H__
#define __SUZHOU_REVIEW__H__
#include "mahjong/gameview/baseview/BaseView.h"
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class SuZhouReview : public BaseView
{
public:
    
    virtual bool init() override;
    CREATE_FUNC(SuZhouReview);
    virtual void onEnter() override;
    virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
    void dealJongFinish(MahjongFaPaiData data);//发牌结束处理
    void showSuZHouControllPad(PlayerCpgtData cpgtData);//显示碰杠胡控制板
    void hideSuZHouControllPad();//隐藏碰杠胡控制板
    void showHuPaiXing(std::string paixing);
    void showHandPokerOver(int seatId);
private:
    
    float interval =0;
    int fupanStep = 0;
    int currentMaxStep =0;
    bool playing = true;
    std::vector<PlayMingpaiRecord> myPlayMingpaiRecord;
    MenuItemImage* image1;
    MenuItemImage* image3;
    
    void initSuZhouMahjong();
    void checkHeroHandPoker();//检查手牌,锁住非花的牌
    void doRecoverGame();
    void doRecoverPlayer(PlayerGameData data, int type, PlayerInfo* playerInfo);
    void doSuZhouQiAction(Ref* ref);
    void doSuZhouHuAction(Ref* ref);
    void doSuZhouPengAction(Ref* ref);
    void doSuZhouGangAction(Ref* ref);
    void showSuZhouGangChoice(Ref* ref);
    
    void controlDown();
    void controlPause();
    void controlUp();
    void controlBack();
    void update(float dt) override;
    EventListenerCustom* turnListener;//轮到出牌
    EventListenerCustom* otherPlayerPlayedListener;//其他玩家出牌
    EventListenerCustom* playerCpgListener;//碰杠操作
    EventListenerCustom* gameResultListener;//结算
    EventListenerCustom* othersPengListener;//其他玩家碰
    EventListenerCustom* othersGangListener;//其他玩家杠
    EventListenerCustom* trusteeshipNotifyListener;//托管通知
    EventListenerCustom* trusteeshipCancelListener;//取消托管
    EventListenerCustom* conncetAgainListener;//重新连接
    EventListenerCustom* openFriendRoomListener;//好友房间游戏未开始重新连接
    EventListenerCustom* enterFriendRoomListener;//好友房间游戏未开始重新连接
    EventListenerCustom* playeHuActionListener;//可以胡牌通知
    EventListenerCustom* fupanPlayerInfoListener;
};
#endif
