#ifndef __ChongMingView_VIEW__
#define __ChongMingView_VIEW__
#include "mahjong/gameview/gui/GuiLayer.h"
#include "mahjong/gameview/player/base/PlayerBase.h"
#include "mahjong/gameview/player/PlayerLeft.h"
#include "mahjong/gameview/player/PlayerRight.h"
#include "mahjong/gameview/player/PlayerOpposite.h"
#include "mahjong/gameview/player/PlayerHero.h"
#include "mahjong/gameview/player/playerinfo/Player.h"
#include "mahjong/common/dialog/toast/InfoToast.hpp"
#include "mahjong/common/state/DataStruct.h"
#include "mahjong/common/jong/Jong.h"
#include "userdata/UserData.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace ui;

class ChongMingView : public cocos2d::Layer
{
public:
    
	virtual bool init() override;		
	CREATE_FUNC(ChongMingView);
	virtual void onEnter() override;
	virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
	void showHuGangControllPad(PlayerCpgtData cpg);
	void hideHuGangControllPad();
	void showGuiLayer();
	void startGameAgain();
    void startGameFirst();
	void removeHeroPlayedIcon();
    void dealJongFinish(ReplaceJongVec vec,PlayerCpgtData data);
    void showHandPokerOver(int seatId);//翻牌
    void showPaiduiNum(int num);
    void checkPlayerIpRepetition();
    int  getNumbersByPoker(string pokers);
    
private:
	std::mutex m_mutex;
	int currentReadyPlayer;
    HeroCpgRespData shmjHeroCpgtData;
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
	void drawCpgControllPad(PlayerCpgtData cpg);
	void showHeroChiUi(Ref* ref);
    void showHeroGangUi(Ref* ref);
	void heroDoChi(Ref* psend);
	void heroDoPeng(Ref* psend);
	void heroDoGang(Ref* psend);
	void heroDoCpgQi();
	void heroDoTing();
	void heroDoHuQi();
	void setCurrentJongVisible(int seatId);
	void playerTingAnim(int seatId);
	void clearRoomPlayer();
	void recoverGame();//恢复游戏场景
	void recoverPlayer(PlayerGameData data,int type, Player* playerInfo);
    void showOriention();
    void showHuPaiXing(std::string paixing);
    void firstReplaceFlower(ReplaceJongVec vec,PlayerCpgtData data);//首次杠花
    void heroDoQiHu();
    void playerApplyHu();
	PlayerBase* getPlayerBySeatId(int sid);
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
    EventListenerCustom* lobbyConncetAgainListener;
    EventListenerCustom* viewIntnetListener;
    EventListenerCustom* scrollTetxListener;
    EventListenerCustom* coreOpenFriendRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* coreLoginRespListener;
    EventListenerCustom* fangZhuLeaveListener;
    EventListenerCustom* networkBreakListener;
    EventListenerCustom* truNotifyListener;
    EventListenerCustom* dissovleRoomNew;
    EventListenerCustom* playeHuActionListener;
};
#endif
