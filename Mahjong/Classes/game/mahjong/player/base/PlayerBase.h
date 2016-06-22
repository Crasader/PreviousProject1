#ifndef __PLAYER_BASE__
#define __PLAYER_BASE__
#include "cocos2d.h"
#include "Player.h"
#include "Jong.h"
#include "GameData.h"
#include "StringUtil.h"
#include "SeatIdUtil.h"
#include "Audio.h"

USING_NS_CC;

class PlayerBase :public Layer{
public:
    int huaIndex;
	Layer* playerJongLayer;
	static	const int jongNum = 13;
	Vector<Jong*> playerHandJongs;
    Vector<Jong*> playerPlayedJongs;
	vector<PlayerCpgRecord>  playerCpgRecords;
    std::vector<Jong*> needReplace;
	static Sprite* biaoji;
	static Sprite* currentBigJongBg;
	static Jong* currentBigJong;

	virtual bool init();
	void initPlayer(Player* playerInfo, int clientSeatId);

	
	virtual void removeLastJong(){};
    virtual void doEventTimeOverUi(){};
	virtual void doEventTimeOver(int type){};
	virtual void showCurrentPlayedJongIcon(bool isShow){};
    virtual void JongShowdown(vector<int> jongs){};
	virtual Point getCpgShowPostion(int index){ return Point(0, 0); };

	void showPlayerHua(Point pos,int num);
	void showCurrentBigJong(int cType,Vec2 pos);
	void hideCurrentBigJong();
    
    void showPlayerInfo();
	
	void setIsReady(bool b);
	void setIsTing(bool b);
	void startTimeClockAnim();
	void startTimeClockAnim(int time, int type);
	void stopTimeClockAnim();
	void playerCpgAnim(CpgType cpgType, ClientSeatId type);

    void updatePlayerInfo(int num);
	void recoverHua(std::string hua);
	void recoverPlayed(std::string played);
    void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang) ;
	void recoverHand(std::string hand);
	void cleanPlayerUI();
	Jong* getCurrentJong();
    
    //隐藏玩家的手牌
    void hideHandJongs();
    CC_SYNTHESIZE(Player*, playerInfo, PlayerInfo);
	CC_SYNTHESIZE(ReplaceJong, replacePoker, ReplacePoker);
	CC_SYNTHESIZE(int, clientSeat, ClientSeat);
	CC_SYNTHESIZE(bool, playerEnable, PlayerEnable);
    CC_SYNTHESIZE(int,huaNum,HuaNum);
    CC_SYNTHESIZE(bool, stateCpg, StateCpg);//吃碰杠状态
	CREATE_FUNC(PlayerBase);

private:
	bool isReady;
	int mCDTime;
	Menu* headimage;
	Sprite* tingTitle;
	Label* nickName;
	LabelAtlas* diamondNum;
	LabelAtlas* timeClock;
	LabelAtlas* playerHuaCount;
	Sprite* playerHua;
	ProgressTimer* mProgressTimer;

	void initData();
	void updateTime(float dt);
	Point getPostionBySeat(int seatId);
	std::string getHeadImageName(std::string id);
};

#endif