#ifndef __MAHJONG_VIEW__
#define __MAHJONG_VIEW__
#include "cocos2d.h"
#include "mahjong/core/gui/GuiLayer.h"
#include "mahjong/jong/Jong.h"
#include "mahjong/player/base/PlayerBase.h"
#include "mahjong/player/PlayerLeft.h"
#include "mahjong/player/PlayerRight.h"
#include "mahjong/player/PlayerOpposite.h"
#include "mahjong/player/PlayerHero.h"
#include "mahjong/player/playerinfo/Player.h"
#include "mahjong/dialog/toast/InfoToast.hpp"
#include "userdata/UserData.h"
USING_NS_CC;

class MahjongView : public cocos2d::Layer
{
public:
    
	virtual bool init() override;		
	CREATE_FUNC(MahjongView);
	virtual void onEnter() override;
	virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
	void showTingGangControllPad();
	void hideTingGangControllPad();
	void showGuiLayer();
	void startGameAgain();
    void startGameFirst();
	void removeHeroPlayedIcon();
    void dealJongFinish();
    void showHandPokerOver(int seatId);
    
private:
	std::mutex m_mutex;
	int currentReadyPlayer;
    float countTime;
	std::string  selectedChi;
	Sprite* choiceMenu;
    Menu* controllPad;
    InfoToast* tao;
	GuiLayer* guiLayer;
    PlayerHero* playerHero;
    PlayerLeft* playerLeft;
    PlayerRight* playerRight;
    PlayerOpposite* playerOpposite;


	void update(float dt) override;
	void initData();
	void loadView();
	void addPlayer2Room();
	void updatePlayerView(int type,Player* info);
	void addTouchListener();
	void drawCpgControllPad();
	void showHeroChiUi();
	void heroDoChi(Ref* psend);
	void heroDoPeng();
	void heroDoGang();
	void heroDoCpgQi();
	void heroDoTing();
	void heroDoTingQi();
	void heroDoPengGangAndAGang();
	void setCurrentJongVisible(int seatId);
	void playerTingAnim(int seatId);
	void clearRoomPlayer();
	void recoverGame();//恢复游戏场景
	void recoverPlayer(PlayerGameData data,int type, Player* playerInfo);
    void showOriention();
    void showGamePaidui(int num);
    void showHuPaiXing(std::string paixing);
	PlayerBase* getPlayerBySeatId(int sid);


	EventListenerCustom* addOtherReadyListener;
	EventListenerCustom* loginRespListener;
	EventListenerCustom* addPlayersListener;
	EventListenerCustom* replaceListener;
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
    EventListenerCustom* playerRemoveListener;
    EventListenerCustom* playerOffLineListener;
    EventListenerCustom* playerResumeListener;
    EventListenerCustom* friendOpenRoomListener;
    EventListenerCustom* playerReplaceLoginListener;
    EventListenerCustom* dissovelRoomNotifyListener;
    EventListenerCustom* dissovelRoomSelectNotifyListener;
    EventListenerCustom* lobbyConncetAgainListener;
    EventListenerCustom* viewIntnetListener;
    EventListenerCustom* scrollTetxListener;
    
	void addCoustomListener();
	void addOthersReadyListener();
	void addDealJongListener();
	void addCoustomReplaceFlower();
	void addPlayerTurnListener();
	void addJongPlayedListener();
	void addHeroCpgListener();//自己吃碰杠通知
    void addHeroChiRespListener();//自己吃回复
    void addHeroPengRespListener();//自己碰回复
    void addHeroGangRespListener();//自己杠回复
	void addGameResultListener();//胡牌结算
	void addOthersChiListener();//其余玩家吃牌
	void addOthersPengListener();//其余玩家碰牌
	void addOthersGangListener();//其余玩家杠牌
	void addPlayerTingNotifyListener();
	void addHeroTingNotifyListener();
	void addHeroTingRespListener();
	void addLostConnectListener();
	void addFriendInviteMeListener();
    void addPlayerRemoveListener();
    void addPlayerOffLineListener();
    void addPlayerResumeListener();
};
#endif
