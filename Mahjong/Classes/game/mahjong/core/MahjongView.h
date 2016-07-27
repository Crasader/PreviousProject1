#ifndef __MAHJONG_VIEW__
#define __MAHJONG_VIEW__
#include "cocos2d.h"
#include "game/mahjong/core/gui/GuiLayer.h"
#include "game/mahjong/jong/Jong.h"
#include "game/mahjong/player/base/PlayerBase.h"
#include "game/mahjong/player/PlayerLeft.h"
#include "game/mahjong/player/PlayerRight.h"
#include "game/mahjong/player/PlayerOpposite.h"
#include "game/mahjong/player/PlayerHero.h"
#include "game/mahjong/player/playerinfo/Player.h"
#include "game/mahjong/dialog/trusteeship/Trusteeship.h"
#include "userdata/UserData.h"
USING_NS_CC;

class MahjongView : public cocos2d::Layer
{
public:
    
	virtual bool init();		
	CREATE_FUNC(MahjongView);
	virtual void onEnter() override;
	virtual void onExit() override;
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
	std::string  selectedChi;
	PlayerHero* playerHero;
	PlayerLeft* playerLeft;
	PlayerRight* playerRight;
	PlayerOpposite* playerOpposite;

	Menu* controllPad;
	Sprite* choiceMenu;
	Trusteeship* trusteeship;
	GuiLayer* guiLayer;


	void update(float dt);
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
	void recoverGame();
	void recoverPlayer(PlayerGameData data,int type, Player* playerInfo);
    void showOriention();
    void showGamePaidui(int num);
    void showHuPaiXing(std::string paixing);
    void resumePlayerUI(PlayerResumeData data,int type);
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
	EventListenerCustom* friendInviteMeListener;
	EventListenerCustom* enterFrinedRoomListener;
    EventListenerCustom* playerRemoveListener;
    EventListenerCustom* playerOffLineListener;
    EventListenerCustom* playerResumeListener;

	void addCoustomListener();
	void addOthersReadyListener();
	void addPlayerListener();
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
	void addTrusteeShipRespListener();
	void addTrusteeShipNotifyListener();
	void addTrusteeShipCancelListener();
	void addLostConnectListener();
	void addFriendInviteMeListener();
	void addEnterFriendRoomListener();
    void addPlayerRemoveListener();
    void addPlayerOffLineListener();
    void addPlayerResumeListener();
};
#endif