#ifndef __PLAYER_HERO__
#define __PLAYER_HERO__
#include "cocos2d.h"
#include "mahjong/gameview/player/base/PlayerBase.h"
#include "mahjong/gameview/player/base/PlayerInfo.h"
USING_NS_CC;
using namespace std;

class PlayerHero : public PlayerBase
{
public:
    static const int MAX_JONG_NUM = 14;
    static const int JONG_POS_START_X = 170;
    static const int JONG_POS_13_X = 1110;//最后一张摸到的牌的位置
    static const int NEW_JONG_POS_X = 1200;
    static const int JONG_POS_Y = 70;
    static const int JONG_SEL_POS_Y = 120;
    static const int JONG_WIDTH = 78;
    
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    void removeLastJong() override;
    void doEventTimeOver(int type) override;
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    void setIsReady(bool b);
    void showPlayedJongSign(bool show);
    void hidePlayedBigJong();
    void showInviteButton();
    void hideInviteButton();
    void drawPlayerHero(std::string hand);
    void drawReady(bool b);
    void sortHandJongs(int posx,bool isTurn);
    void settleHandJongs(int pos);//手牌整理
    void checkSuZhouHeroHandPoker();
    void checkHongZhongHeroHandPoker();
    void checkBaiDaHeroHandPoker();
    void checkFanPaiHeroHandPoker(int poker);
    void playerTurnToPlay(PlayerTurnData data);
    //玩家吃碰杠
    void drawHeroPeng(HeroCpgRespData resp, PlayerBase* playerBase);
    void drawHeroGang(HeroCpgRespData resp, PlayerBase* playerBase);
    
    void drawPlayerTrue(bool state);
    
    void actionTing(HeroCpgRespData ht);
    void actionQi();
    void eraseHeroJong(Jong* jong);
    void drawPlayedJong(int type);//听牌后出牌
    
    void recoverHua(std::string hua);
    void recoverPlayed(std::string played);
    void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang);
    void recoverHand(std::string hand,std::string lastpoker);
    void updateHandJongs(std::string jongs,bool hu);
    
    Vector<Jong*> getSelfHandJongs();
    CC_SYNTHESIZE(bool, isAllowPlay, IsAllowPlay);
    CC_SYNTHESIZE(bool, isAllowTouch, IsAllowTouch);
    CC_SYNTHESIZE(float, handPosX, HandPosX);
    CC_SYNTHESIZE(int, cpgPostionX, CpgPostionX);
    
    void drawPlayedJongMingpai(int type);
    void playerTurnReplaceMingpai(PlayerTurnData data);
    void updateMingpai(Vector<Jong*> playerHandJongs,Vector<Jong*> playerPlayedJongs,Vector<Jong*> myPlayerHuaJongs,std::vector<PlayerCpgRecord> playerCpgRecords);
    void drawHeroPengMingpai(HeroCpgRespData resp, PlayerBase* playerBase);
    void drawHeroGangMingpai(HeroCpgRespData resp, PlayerBase* playerBase);
    
    CREATE_FUNC(PlayerHero);
    
private:
    std::mutex j_mutex;
    std::vector<std::string> pokerV;
    std::vector<std::string> replaceV;
    std::vector<HeroHuPaiData> heroHuData;
    Point preTouchPosition;//上一次点击的位置
    Jong* currentJong;
    Jong* selectJong;
    Jong* doubleClickJong;
    
    void initData();
    void addTouchListener();
    void resetHandJongsY(Jong* jong);
    void resetHandJongsX(Jong* jong);
    void arrangeHandJongs();
    void readyGo();
    void inviteWechatFriend();
    void sendTingRequest(int poker);
    void sendPokerRequest(int poker);
    void playPokerByHand(Jong* jong);//手动出牌
    void updateSelectedInfo(Jong* jong);
    void showHuPaiTiShi(std::vector<HeroHuPaiData> heroHu);
    float distance(Point pos1, Point pos2);
    Point getHeroPlayedNormalPos(int index);//获取打出手牌的位置
    Point getHeroPlayedHuaPos(int index);//获取打出花的位置
    Vector<Jong*>  upsetJongs(Vector<Jong*> jongs);
    Jong* getTouchJong(Touch *touch);
    Point  getMultiplePosition(Point p1,Point p2,float xi);
    
};
#endif
