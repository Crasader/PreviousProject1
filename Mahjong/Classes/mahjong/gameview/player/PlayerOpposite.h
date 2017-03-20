#ifndef __PLAYER_OPPOSSITE__
#define __PLAYER_OPPOSSITE__
#include "cocos2d.h"
#include "mahjong/gameview/player/base/PlayerBase.h"
USING_NS_CC;

class PlayerOpposite : public PlayerBase{

public:
	virtual bool init() override;
	void removeLastJong() override;
	void showCurrentPlayedJongIcon(bool isShow) override;
	Point getCpgShowPostion(int index) override;
    void doEventTimeOver(int type) override;
    void drawHandJong();
    void drawPlayedJong(int ctype);
	void drawOppositePlayerTurn();
	void drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase);
	void drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase);
	void drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase);
	Point getPlayedJongPos(int count);
	void recoverHua(int hua);
	void recoverPlayed(std::string played);
	void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang);
	void recoverHand(std::string hand);
    void updateHandJongs(std::string jongs,bool hu);
    
    void drawMingPai(std::string hand);
    void settleJongMingpai();
    void drawOppositePlayerTurnMingpai(int jong);
    void drawPlayerMingpaiGang(PlayerCpgtData data, PlayerBase* playerBase);
    void drawPlayerMingpaiChi(PlayerCpgtData data, PlayerBase* playerBase);
    void drawPlayerMingpaiPeng(PlayerCpgtData data,PlayerBase* playerBase);
    void updateMingpai(Vector<Jong*> playerHandJongs,Vector<Jong*> playerPlayedJongs,std::vector<PlayerCpgRecord> playerCpgRecords);
    void drawPlayedJongMingpai(int ctype);
    
	CREATE_FUNC(PlayerOpposite);

private:
	static const int OPPOSITE_POS_X = 295;
	static const int OPPOSITE_POS_Y = 675;
    static const int OPPOSITE_POKER_WIDTH = 34;
	Point getHuaJongPos(int number);
};
#endif 
