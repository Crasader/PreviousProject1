#ifndef __PLAYER_RIGHT__
#define __PLAYER_RIGHT__
#include "cocos2d.h"
#include "mahjong/player/base/PlayerBase.h"
USING_NS_CC;

class PlayerRight : public PlayerBase{

public:

	virtual bool init() override;
	void drawHandJong();
	void drawPlayedJong(int ctype);
	void drawRightPlayerTurn();
	void showCurrentPlayedJongIcon(bool isShow) override;
	Point getCpgShowPostion(int index) override;
    void doEventTimeOver(int type) override;
	void removeLastJong() override;
	void drawPlayerChi(PlayerCpgtData data, PlayerBase* playerBase);
	void drawPlayerPeng(PlayerCpgtData data, PlayerBase* playerBase);
	void drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase);

	Point getPlayedJongPos(int count);//
	void recoverHua(int hua);
	void recoverPlayed(std::string played);
	void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang);
	void recoverHand(std::string hand);
    void updateHandJongs(std::string jongs,bool hu);
	CREATE_FUNC(PlayerRight);

private:
	static const int RIGHT_POS_X = 1110;
	static const int RIGHT_POS_Y = 640;
    static const int RIGHT_POKER_WIDTH = 27;
	Point getHuaJongPos(int number);
};
#endif 
