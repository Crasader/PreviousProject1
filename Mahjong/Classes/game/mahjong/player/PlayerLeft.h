#ifndef __PLAYER_LEFT__
#define __PLAYER_LEFT__
#include "cocos2d.h"
#include "game/mahjong/player/base/PlayerBase.h"
USING_NS_CC;

class PlayerLeft : public PlayerBase{

public:
	virtual bool init();
	void removeLastJong() override;
	void showCurrentPlayedJongIcon(bool isShow) override;
	Point getCpgShowPostion(int index) override;
	void drawHandJong();
	void drawPlayedJong(int ctype);
	void drawHuaJong();
	void drawLeftPlayerTurn();
	void playerTurnReplace(PlayerTurnData data);
	void drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase);
	void drawPlayerPeng(PlayerCpgtData data,PlayerBase* playerBase);
	void drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase);
	Point getPlayedJongPos(int count);
	void recoverHua(int hua);
	void recoverPlayed(std::string played);
	void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang);
	void recoverHand(std::string hand);
    void updateHandJongs(std::string jongs);
	CREATE_FUNC(PlayerLeft);
private:
	static const int LEFT_POS_X = 170;
	static const int LEFT_POS_Y = 250;
	Point getHuaJongPos(int number);
};
#endif 