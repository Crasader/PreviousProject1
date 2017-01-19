#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "mahjong/utils/StringUtil.h"
#include "mahjong/loading/Loading.h"
#include "mahjong/state/GameData.h"
#include "mahjong/core/MjGameScene.h"
#include "mahjong/setting/UserSetting.h"
#include "mahjong/friend/FriendRoom.h"
#include "mahjong/bill/BillInfo.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"

USING_NS_CC;

class LobbyScene : public cocos2d::Scene
{
public:

    virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
    void onEnterTransitionDidFinish() override;
    CREATE_FUNC(LobbyScene);
private:
    
	Label* nickName;
	Label* goldNum;
	Label* fangkaNum;
	Label* lequanNum;
    Menu* firstMenu;
    Sprite* ganTanhao;
    
    EventListenerCustom* enterRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* openFriendRoomListener;
    EventListenerCustom* lobbyConncetAgainListener;
    EventListenerCustom* intnetListener;
    EventListenerCustom* loginReplaceListener;
    EventListenerCustom* payDialogListener;
    EventListenerCustom* payResultListener;
    EventListenerCustom* imageUpdateListener;
    EventListenerCustom* firstChargeListenr;
    EventListenerCustom* openRoomAskListener;
    EventListenerCustom* enterRoomAskListener;
    EventListenerCustom* scrollTetxListener;
    EventListenerCustom* wanjiaqunListener;
    EventListenerCustom* noticeUrlLitener;
    EventListenerCustom* upateLequanShopLitener;
    EventListenerCustom* showLoobyLoadingLayer;
    EventListenerCustom* gameFupanListener;
    
	void initView();
	void drawSceneMid();
	void drawSceneTop();
	void drawSceneBot();
    void openRoom();
    void joinRoom();
    void showGoldRoomPad();
    void chargeGold();
    void chargeFangka();
    void exchangeLequan();
	void showFirstCharge();
	void showRedWallet();
    void showWanJiaQun();
	void showDayTask();
	void showPlayerBill();
	void showGameSetting();
	void showHotActivity();
	void showHeroInfo();
    void showLoading();
    void removeLoading();
    void showLobbyAnim();
	void addEventListener();
    void scrollLightSpot(float dt);
    void signUpdate(float dt);
    void updateHeroInfo();
};
#endif
