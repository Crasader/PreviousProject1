#ifndef __PLAYER_BASE__
#define __PLAYER_BASE__
#include "cocos2d.h"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/utils/SeatIdUtil.h"
#include "mahjong/common/audio/Audio.h"
#include "mahjong/gameview/player/base/PlayerInfo.h"
USING_NS_CC;
using namespace cocos2d::ui;

class PlayerBase :public Layer{
public:
    static	const int jongNum = 13;//基准手牌数量
    Vector<Jong*> playerHandJongs;//玩家手牌
    Vector<Jong*> playerPlayedJongs;//玩家出的牌
    Vector<Jong*> playerHuaJongs;//玩家出的花
    vector<PlayerCpgRecord>  playerCpgRecords;//玩家吃碰杠记录
    
    virtual bool init() override;
    void onEnter() override;
    void onExit() override;
    virtual void removeLastJong(){};// 移除最后一张牌
    virtual void doEventTimeOver(int type){};
    virtual Point getCpgShowPostion(int index){ return Point(0, 0); };
    void initPlayer(PlayerInfo* playerInfo);//初始化玩家UI
    void showPlayedJong(int ctype);//玩家打牌
    void showPlayerZhuang(bool show);
    void showPlayerPeng(PlayerCpgtData data,PlayerBase* playerBase);//玩家碰牌
    void showPlayerGang(PlayerCpgtData data, PlayerBase* playerBase);//玩家杠牌
    void setIsReady(bool b);//准备状态
    void setIsOffLine(bool b);//是否断线
    void setIsTrusteeship(bool b);
    void showPlayerInfo();//显示玩家信息
    void startTimeClockAnim();
    void startTimeClockAnim(int time, int type);
    void stopTimeClockAnim();
    void playerCpgAnim(CpgType cpgType, ClientSeatId type);//玩家吃碰杠动画
    void updatePlayerInfo(int num);//刷新头像下的金币或者积分信息
    void recoverHua(std::string hua);//断线后花恢复
    void recoverPlayed(std::string played);//断线后打出的牌恢复
    void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang);//断线后吃碰杠牌恢复
    void recoverHand(std::string hand);//断线后手牌恢复
    void recoverLastPlayJong();//场上最后一张牌
    void hideHandJongs();//隐藏玩家的手牌
    void playSoundHuPai();
    void updatePlayerHeadImage();
    void showPlayerHua(int num);
    void replaceTurnHuaMingpai(PlayerTurnData data);
    Jong* getCurrentJong();
    CC_SYNTHESIZE(PlayerInfo*, playerInfo, PlayerInfo);
    CC_SYNTHESIZE(int,clientSeat,ClientSeat);
    CC_SYNTHESIZE(bool,stateCpg,StateCpg);//吃碰杠状态
    CC_SYNTHESIZE(int,chiNumber,ChiNumber);//吃的数量
    CC_SYNTHESIZE(int,pokerNumber,PokerNumber);//打牌数量
    CC_SYNTHESIZE(int,lastPoker,LastPoker);//最近一次出牌
    CC_SYNTHESIZE(bool,isPlayHuaChi,IsPlayHuaChi);//花痴音效
    CREATE_FUNC(PlayerBase);
    
private:
    
    bool isReady;
    int mCDTime;
    std::vector<Jong*> needReplace;//需要替换的花牌
    EventListenerCustom* roomChatListener;
    EventListenerCustom* wechatImageListener;
    Sprite* playerHua;
    Menu* headimage;
    Label* nickName;
    Label* moneyNumber;
    LabelAtlas* timeClock;
    LabelAtlas* playerHuaCount;
    ProgressTimer* mProgressTimer;
    Layer* chatShowLayer;//聊天显示图层
    void initData();
    void updateTime(float dt);
    Point getPostionBySeat(int seatId);
    Point getReadyPosBySeat(int seatId);
    Point getHuaNumPos(int type);
    Point getZhuangPos(int type);
    Point getVec2BySeatId(int seatId);
    void checkQuickChatSound(std::string msg);
};

#endif
