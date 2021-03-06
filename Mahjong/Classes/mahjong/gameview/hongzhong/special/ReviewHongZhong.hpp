//
//  ReviewHongZhong.hpp
//  Mahjong
//
//  Created by qiuzhong on 2017/4/5.
//
//

#ifndef ReviewHongZhong_hpp
#define ReviewHongZhong_hpp

#include "mahjong/gameview/gui/GuiLayer.h"
#include "mahjong/gameview/player/base/PlayerBase.h"
#include "mahjong/gameview/player/PlayerLeft.h"
#include "mahjong/gameview/player/PlayerRight.h"
#include "mahjong/gameview/player/PlayerOpposite.h"
#include "mahjong/gameview/player/PlayerHero.h"
#include "mahjong/gameview/player/playerinfo/Player.h"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/dialog/toast/InfoToast.hpp"
#include "mahjong/common/state/DataStruct.h"
#include "userdata/UserData.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class ReviewHongZhong : public Layer{
public:
    
    virtual bool init() override;
    CREATE_FUNC(ReviewHongZhong);
    virtual void onEnter() override;
    virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
    void showHuGangControllPad(PlayerCpgtData cpg);
    void hideHuGangControllPad();
    void showGuiLayer();
    void startGameAgain();
    void startGameFirst();
    void removeHeroPlayedIcon();
    void dealJongFinish(ReplaceJongVec vec,PlayerCpgtData data);
    void showHandPokerOver(int seatId);//翻牌
    void showPaiduiNum(int num);
    void checkPlayerIpRepetition();
    int  getNumbersByPoker(string pokers);
    
private:
    float interval =0;
    int fupanStep = 0;
    int currentMaxStep =0;
    bool playing = true;
    std::mutex m_mutex;
    int currentReadyPlayer;
    std::string  selectedChi;
    HeroCpgRespData shmjHeroCpgtData;
    Sprite* choiceMenu;
    Menu* controllPad;
    InfoToast* tao;
    GuiLayer* guiLayer;
    PlayerHero* playerHero;
    PlayerLeft* playerLeft;
    PlayerRight* playerRight;
    PlayerOpposite* playerOpposite;
    bool showRepeatDialog = false;
    std::vector<PlayMingpaiRecord> myPlayMingpaiRecord;
    MenuItemImage* image1;
    MenuItemImage* image3;
    
    void update(float dt) override;
    void initData();
    void loadView();
    void addPlayer2Room();
    void updatePlayerView(int type,Player* info);
    void addTouchListener();
    void drawCpgControllPad(PlayerCpgtData cpg);
    void playerApplyHu();
    void showHeroGangUi(Ref* ref);
    void heroDoHZPeng(Ref* psend);
    void heroDoHZGang(Ref* psend);
    void heroDoCpgQi();
    void heroDoQiHu();
    void setCurrentJongVisible(int seatId);
    void playerTingAnim(int seatId);
    void clearRoomPlayer();
    void recoverGame();//恢复游戏场景
    void recoverPlayer(PlayerGameData data,int type, Player* playerInfo);
    void showOriention();
    void showHuPaiXing(std::string paixing);
    void firstPlayPoker(ReplaceJongVec vec,PlayerCpgtData data);
    void createPlayer(PlayerGameData data, int type, Player* playerInfo);
    PlayerBase* getPlayerBySeatId(int sid);
    
    void controlDown();
    void controlPause();
    void controlUp();
    void controlBack();
    
    EventListenerCustom* addOtherReadyListener;
    EventListenerCustom* loginRespListener;
    EventListenerCustom* addPlayersListener;
    EventListenerCustom* turnListener;
    EventListenerCustom* otherListener;
    EventListenerCustom* playerCpgListener;
    EventListenerCustom* gameResultListener;
    EventListenerCustom* othersPengListener;
    EventListenerCustom* othersGangListener;
    EventListenerCustom* playerTingNotifyListener;
    EventListenerCustom* playeHuActionListener;
    EventListenerCustom* tingNotifyListener;
    EventListenerCustom* tingRespListener;
    EventListenerCustom* trusteeshipRespListener;
    EventListenerCustom* trusteeshipNotifyListener;
    EventListenerCustom* trusteeshipCancelListener;
    EventListenerCustom* heroPengRespListener;
    EventListenerCustom* heroGangRespListener;
    EventListenerCustom* playerRemoveListener;
    EventListenerCustom* playerOffLineListener;
    EventListenerCustom* playerResumeListener;
    EventListenerCustom* playerReplaceLoginListener;
    EventListenerCustom* dissovelRoomSelectNotifyListener;
    EventListenerCustom* lobbyConncetAgainListener;
    EventListenerCustom* viewIntnetListener;
    EventListenerCustom* scrollTetxListener;
    EventListenerCustom* coreOpenFriendRoomListener;
    EventListenerCustom* hzEnterFriendRoomListener;
    EventListenerCustom* coreLoginRespListener;
    EventListenerCustom* fangZhuLeaveListener;
    EventListenerCustom* networkBreakListener;
    EventListenerCustom* fupanPlayerInfoListener;
};
#endif /* ReviewHongZhong_hpp */
