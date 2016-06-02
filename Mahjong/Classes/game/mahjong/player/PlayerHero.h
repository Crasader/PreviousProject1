#ifndef __PLAYER_HERO__
#define __PLAYER_HERO__
#include "cocos2d.h"
#include "game/mahjong/player/base/PlayerBase.h"

USING_NS_CC;
using namespace std;

class PlayerHero : public PlayerBase
{
public:
	static const int MAX_JONG_NUM = 14;
	static const int JONG_POS_START_X = 180;
	static const int NEW_JONG_POS_X = 1200;
	static const int JONG_POS_Y = 70;
	static const int JONG_SEL_POS_Y = 120;
	static const int JONG_WIDTH = 78;

	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
	void removeLastJong() override;
	void doEventTimeOver(int type) override;
	void showCurrentPlayedJongIcon(bool isShow) override;
	bool onTouchBegan(Touch *touch, Event  *event) override;
	void onTouchMoved(Touch *touch, Event  *event) override;
	void onTouchEnded(Touch *touch, Event  *event) override;
	void drawPlayerHero();
	void drawReady(bool b);
	void hideReadyButton();
	void sortHandJongs(int posx,bool isTurn);
	void replaceFlower();
	void playerTurnReplace(PlayerTurnData data);
    //玩家吃碰杠
	void drawHeroChi(HeroCpgRespData resp, std::vector<string> chipai, PlayerBase* playerBase);
	void drawHeroPeng(HeroCpgRespData resp, PlayerCpgtData data, PlayerBase* playerBase);
	void drawHeroMingGang(HeroCpgRespData resp, PlayerCpgtData data, PlayerBase* playerBase);
	void drawPengGangAndAGang(PlayerCpgtData cpg);
    
	void actionTing();
	void actionQi();
	void eraseHeroJong(Jong* jong);
	void removePlayedIcon();
	Vector<Jong*> getSelfHandJongs();
	Vector<Jong*>  sortJongs(Vector<Jong*> jongs);
	void recoverHua(int hua);
	void recoverPlayed(std::string played);
	void recoverCpg(vector<PlayerChiData> chi,vector<PlayerPengData> peng,vector<PlayerGangData> gang,std::string angang);
	void recoverHand(std::string hand);
    void updateHandJongs(std::string jongs);
    void drawHeroPlayerPlay(int type);
    
	CC_SYNTHESIZE(bool, isAllowPlay, IsAllowPlay);
	CC_SYNTHESIZE(bool, isAllowTouch, IsAllowTouch);
	CC_SYNTHESIZE(float, handPosX, HandPosX);
    CC_SYNTHESIZE(int, cpgPostionX, CpgPostionX);
	CREATE_FUNC(PlayerHero);
private:
	int index;
	std::mutex j_mutex;
	Sprite* playedIcon;
	std::vector<std::string> pokerV;
	std::vector<std::string> replaceV;
	Menu* start;
	Jong* currentJong;
	Jong* selectJong;
	Jong* virtualJong;
	Jong* doubleClickJong;

	void initData();
	void addTouchListener();
	void resetHandJongsY(Jong* jong);
	void arrangeHandJongs();
	void readyGo();
	void sendTingRequest(int poker);
	void sendPokerRequest(int poker);
	void playedPokerAuto(bool send);
	void playPokerByHand(Jong* jong);
	float distance(Point pos1, Point pos2);
	Point getHeroPlayedJongsPos(int index);
	Vector<Jong*>  upsetJongs(Vector<Jong*> jongs);
	Jong* getTouchJong(Touch *touch);
	
};
#endif