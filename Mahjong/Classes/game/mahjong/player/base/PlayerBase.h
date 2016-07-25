#ifndef __PLAYER_BASE__
#define __PLAYER_BASE__
#include "cocos2d.h"
#include "game/mahjong/player/playerinfo/Player.h"
#include "game/mahjong/jong/Jong.h"
#include "game/mahjong/state/GameData.h"
#include "game/utils/StringUtil.h"
#include "game/utils/SeatIdUtil.h"
#include "game/utils/Audio.h"

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
    static set<int> playedPokers;//全部玩家打出过的牌,不重复
	virtual bool init();
	void initPlayer(Player* playerInfo, int clientSeatId);//初始化玩家UI
    void drawPlayedJong(int ctype);//玩家打牌
    void drawPlayerChi(string chiPoker, PlayerBase* playerBase);//玩家吃牌
    void drawPlayerPeng(PlayerCpgtData data,PlayerBase* playerBase);//玩家碰牌
    void drawPlayerGang(PlayerCpgtData data, PlayerBase* playerBase);//玩家杠牌
	void showPlayerHua(Point pos,int num);//显示玩家花数
    void setPlayerTingState(bool b);
    
	virtual void removeLastJong(){};
    virtual void doEventTimeOverUi(){};
    
    
    
	virtual void doEventTimeOver(int type){};
	virtual void showCurrentPlayedJongIcon(bool isShow){};
    virtual void JongShowdown(vector<int> jongs){};
	virtual Point getCpgShowPostion(int index){ return Point(0, 0); };

	
	void showCurrentBigJong(int cType,Vec2 pos);
	void hideCurrentBigJong();
    
    void showPlayerInfo();
	
	void setIsReady(bool b);//准备状态
    void setPlayerIsOffLine(bool b);//是否断线
    void setPlayerTrustee(bool b);
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
    CC_SYNTHESIZE(int, chiNumber, ChiNumber);//吃的数量
    CC_SYNTHESIZE(int, pokerNumber, PokerNumber);//打牌数量
    CC_SYNTHESIZE(int, lastPoker, LastPoker);//最近一次出牌
    CC_SYNTHESIZE(bool, isPlayHuaChi, IsPlayHuaChi);//花痴音效
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