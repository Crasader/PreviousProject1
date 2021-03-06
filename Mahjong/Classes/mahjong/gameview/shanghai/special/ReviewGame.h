#ifndef _REVIEW_MAHJONG_GAME_H_
#define _REVIEW_MAHJONG_GAME_H_
#include "cocos2d.h"
#include "mahjong/gameview/gui/GuiLayer.h"
#include "mahjong/gameview/player/base/PlayerBase.h"
#include "mahjong/gameview/player/PlayerLeft.h"
#include "mahjong/gameview/player/PlayerRight.h"
#include "mahjong/gameview/player/PlayerOpposite.h"
#include "mahjong/gameview/player/PlayerHero.h"
#include "mahjong/gameview/player/playerinfo/Player.h"
#include "mahjong/common/jong/Jong.h"
#include "mahjong/common/dialog/toast/InfoToast.hpp"
#include "mahjong/common/state/GameData.h"
#include "userdata/UserData.h"
USING_NS_CC;

class ReviewGame : public cocos2d::Layer
{
public:
    
	virtual bool init() override;		
	CREATE_FUNC(ReviewGame);
	virtual void onEnter() override;
	virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
	void showTingGangControllPad(PlayerCpgtData tingData);
	void hideTingGangControllPad();
    void showGuiLayer();
	void removeHeroPlayedIcon();
    void showPaiduiNum(int num);
    
private:
	std::mutex m_mutex;
	int currentReadyPlayer;
    float interval =0;
    int fupanStep = 0;
    int currentMaxStep =0;
    bool playing = true;
	std::string  selectedChi;
	Sprite* choiceMenu;
    Menu* controllPad;
    InfoToast* tao;
	GuiLayer* guiLayer;
    PlayerHero* playerHero;
    PlayerLeft* playerLeft;
    PlayerRight* playerRight;
    PlayerOpposite* playerOpposite;
    PlayerCpgtData  shmjPlayerCpgtData;
    HeroCpgRespData shmjHeroCpgtData;
    std::vector<PlayMingpaiRecord> myPlayMingpaiRecord;
    MenuItemImage* image1;
    MenuItemImage* image3;


	void update(float dt) override;
	void initData();
	void loadView();
	void addTouchListener();
	void drawCpgControllPad(PlayerCpgtData newData);
	void showHeroChiUi(Ref* ref);
    void showHeroGangUi(Ref* ref);
	void heroDoChi(Ref* psend);
	void heroDoPeng(Ref* ref);
	void heroDoGang(Ref* ref);
	void heroDoCpgQi();
	void heroDoTing();
	void heroDoTingQi();
	void setCurrentJongVisible(int seatId);
	void playerTingAnim(int seatId);
	void clearRoomPlayer();
    void showOriention();
    void showGamePaidui(int num);
    void showHuPaiXing(std::string paixing);
    void createPlayer(PlayerGameData data, int type, Player* playerInfo);
    
	PlayerBase* getPlayerBySeatId(int sid);

	EventListenerCustom* dealJongsListener;
	EventListenerCustom* turnListener;
	EventListenerCustom* otherListener;
	EventListenerCustom* playerCpgListener;
	EventListenerCustom* gameResultListener;
	EventListenerCustom* othersChiListener;
	EventListenerCustom* othersPengListener;
	EventListenerCustom* othersGangListener;
	EventListenerCustom* playerTingNotifyListener;
	EventListenerCustom* tingNotifyListener;
	EventListenerCustom* tingRespListener;
	EventListenerCustom* trusteeshipRespListener;
	EventListenerCustom* trusteeshipNotifyListener;
	EventListenerCustom* trusteeshipCancelListener;
	EventListenerCustom* heroChiRespListener;
	EventListenerCustom* heroPengRespListener;
	EventListenerCustom* heroGangRespListener;
    EventListenerCustom* viewIntnetListener;
    EventListenerCustom* coreOpenFriendRoomListener;
    EventListenerCustom* coreLoginRespListener;
    EventListenerCustom* fupanPlayerInfoListener;

	void addCoustomListener();
    
    void controlDown();
    void controlPause();
    void controlUp();
    void controlBack();
};
#endif
