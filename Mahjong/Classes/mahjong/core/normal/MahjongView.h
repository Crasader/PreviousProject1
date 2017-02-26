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
#include "mahjong/state/DataStruct.h"
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
	void showTingGangControllPad(PlayerCpgtData* cpg);
	void hideTingGangControllPad();
    void heroPlayPokerAuto(int poker);
	void showGuiLayer();
	void startGameAgain();
    void startGameFirst();
	void removeHeroPlayedIcon();
    void dealJongFinish(ReplaceJongVec vec,PlayerCpgtData data);
    void showHandPokerOver(int seatId);//翻牌
    void showPaiduiNum(int num);
    void checkPlayerIpRepetition();
    
private:
	std::mutex m_mutex;
	int currentReadyPlayer;
	std::string  selectedChi;
    PlayerCpgtData*  myCpgtData = new PlayerCpgtData();
	Sprite* choiceMenu;
    Menu* controllPad;
    InfoToast* tao;
	GuiLayer* guiLayer;
    PlayerHero* playerHero;
    PlayerLeft* playerLeft;
    PlayerRight* playerRight;
    PlayerOpposite* playerOpposite;
    bool showRepeatDialog = false;

	void update(float dt) override;
	void initData();
	void loadView();
	void addPlayer2Room();
	void updatePlayerView(int type,Player* info);
	void addTouchListener();
	void drawCpgControllPad(PlayerCpgtData* cpg);
	void showHeroChiUi(Ref* ref);
	void heroDoChi(Ref* psend);
	void heroDoPeng(Ref* psend);
	void heroDoGang(Ref* psend);
	void heroDoCpgQi();
	void heroDoTing();
	void heroDoTingQi();
	void heroDoPengGangAndAGang(Ref* ref);
	void setCurrentJongVisible(int seatId);
	void playerTingAnim(int seatId);
	void clearRoomPlayer();
	void recoverGame();//恢复游戏场景
	void recoverPlayer(PlayerGameData data,int type, Player* playerInfo);
    void showOriention();
    void showHuPaiXing(std::string paixing);
    void firstReplaceFlower(ReplaceJongVec vec,PlayerCpgtData data);//首次杠花
	PlayerBase* getPlayerBySeatId(int sid);


    EventListenerCustom* gameFaPaiListener;
	EventListenerCustom* addOtherReadyListener;
	EventListenerCustom* loginRespListener;
	EventListenerCustom* addPlayersListener;
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
    EventListenerCustom* playerReplaceLoginListener;
    EventListenerCustom* dissovelRoomNotifyListener;
    EventListenerCustom* dissovelRoomSelectNotifyListener;
    EventListenerCustom* lobbyConncetAgainListener;
    EventListenerCustom* viewIntnetListener;
    EventListenerCustom* scrollTetxListener;
    EventListenerCustom* coreOpenFriendRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* coreLoginRespListener;
    EventListenerCustom* fangZhuLeaveListener;
    
	void addCoustomListener();
    void addOthersReadyListener();
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
    void addPlayerRemoveListener();
    void addPlayerOffLineListener();
    void addPlayerResumeListener();
};
#endif
