#ifndef __BASE_VIEW__
#define __BASE_VIEW__
#include "mahjong/gameview/player/base/PlayerBase.h"
#include "mahjong/gameview/player/PlayerLeft.h"
#include "mahjong/gameview/player/PlayerRight.h"
#include "mahjong/gameview/player/PlayerOpposite.h"
#include "mahjong/gameview/player/PlayerHero.h"
#include "mahjong/gameview/player/base/PlayerInfo.h"
#include "mahjong/gameview/widget/Orientation.h"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/state/DataStruct.h"
#include "mahjong/common/dialog/toast/InfoToast.hpp"
#include "userdata/UserData.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class BaseView : public cocos2d::Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(BaseView);
    virtual void onEnter() override;
    virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
    void setPlayPokerSignPosition(bool show,Point pos);//打牌标记的位置
    void setBigJongPosition(int poker,ClientSeatId seatId);
    void setBigJongEnable();
    void showPaiduiNum(int num);
protected:
    Menu* controllPad;//吃碰杠听胡显示板
    PlayerHero* playerHero;
    PlayerLeft* playerLeft;
    PlayerRight* playerRight;
    PlayerOpposite* playerOpposite;
    PlayerBase* getPlayerBySeatId(int sid);
    void addPlayerToRoom();//添加玩家到场景
    void dealJongFinish(MahjongFaPaiData data);
    void showGameBank(int heroSeatId,int bankId);//显示庄家
    void showGameTurn(int heroSeatId, int setaId);//显示轮到谁
    void clearRoomPlayer();
    void startCountdown();
    void resetCountdown();
    void updateRoomInfo();
    void hideDissovleBtn();
    void showMahjongDiec(std::string dian);
private:
    LabelAtlas* countdown;//场景中间的倒计时
    InfoToast* myToast;
    Orientation* orientation;
    Sprite* yellowSign;
    Sprite* bigJongBackground;//打出的牌展示背景
    Jong* bigJong;//打出的牌放大展示牌
    Menu* leftPlayerInvite;
    Menu* rightPlayerInvite;
    Menu* oppositePlayerInvite;
    int countdownTime = 10;
    
    EventListenerCustom* networkBreakListener;//断线重连
    EventListenerCustom* scrollTetxListener;//跑马灯
    EventListenerCustom* dissovelRoomSelectNotifyListener;//解散房间确认界面
    EventListenerCustom* playerRemoveListener;//移除玩家
    EventListenerCustom* addPlayersListener;//添加玩家
    EventListenerCustom* addOtherReadyListener;//其他玩家准备
    EventListenerCustom* playerReplaceLoginListener;//异地登录
    EventListenerCustom* goLobbyRespListener;//返回大厅
    EventListenerCustom* fangZhuLeaveListener;//房主离开，准备状态清除
    EventListenerCustom* playerOffLineListener;//掉线通知
    EventListenerCustom* ipConflictListener;//IP冲突
    
    void countDownUpdate(float dt);
    void showViewLayer();
    void initGameData();
    void updatePlayerView(int type,PlayerInfo* info);
    Point getBigJongPos(int type);
    void showInvitePlayer(int clientId);
    void hideInvitePlayer(int clientId);
    void chatButtonClick();
    void settingButtonClick();
    void quitButtonClick();
    void drawPlayerInvite();
    void showPlayerBill();
    void dissovleRoom();
    void invitePlayer(Ref* ref);
    void gameTest();
    void update(float dt) override;
};
#endif
