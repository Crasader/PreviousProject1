#ifndef __PLAYER_LEFT__
#define __PLAYER_LEFT__
#include "cocos2d.h"
#include "mahjong/gameview/player/base/PlayerBase.h"
USING_NS_CC;

class PlayerLeft : public PlayerBase{
    
public:
    virtual bool init() override;
    void drawHandJong();
    void drawPlayedJong(int ctype);
    
    void removeLastJong() override;
    void showCurrentPlayedJongIcon(bool isShow) override;
    void doEventTimeOver(int type) override;
    void drawLeftPlayerTurn();
    
    void drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase);
    void drawPlayerPeng(PlayerCpgtData data,PlayerBase* playerBase);
    void drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase);
    void recoverHua(int hua);
    void recoverPlayed(std::string played);
    void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang);
    void recoverHand(std::string hand);
    
    void updateHandJongs(std::string jongs,bool hu);
    Point getCpgShowPostion(int index) override;
    Point getPlayedJongPos(int count);
    
    
    void drawMingPai(std::string hand);
    void settleJongMingpai();
    void drawLeftPlayerTurnMingpai(int jong);
    void drawPlayerMingpaiGang(PlayerCpgtData data, PlayerBase* playerBase);
    void drawPlayerMingpaiChi(PlayerCpgtData data, PlayerBase* playerBase);
    void drawPlayerMingpaiPeng(PlayerCpgtData data,PlayerBase* playerBase);
    void updateMingpai(Vector<Jong*> playerHandJongs,Vector<Jong*> playerPlayedJongs,std::vector<PlayerCpgRecord> playerCpgRecords);
    void drawPlayedJongMingpai(int ctype);
    CREATE_FUNC(PlayerLeft);
private:
    static const int LEFT_POS_X = 170;
    static const int LEFT_POS_Y = 250;
    static const int LEFT_POKER_WIDTH = 27;
    Point getHuaJongPos(int number);
};
#endif 
