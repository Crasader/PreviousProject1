#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "mahjong/common/utils/StringUtil.h"
#include "mahjong/common/loading/Loading.h"
#include "mahjong/common/state/GameData.h"
#include "mahjong/common/setting/UserSetting.h"
#include "mahjong/common/bill/BillInfo.h"
#include "mahjong/gameview/MjGameScene.h"
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
    bool showDissolveDialog;
	Label* nickName;
	Label* fangkaNum;
    bool isShowRoomlist = false;
    
    EventListenerCustom* enterRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* hzEnterFriendRoomListener;
    EventListenerCustom* openFriendRoomListener;
    EventListenerCustom* hzOpenFriendRoomListener;
    EventListenerCustom* lobbyConncetAgainListener;
    EventListenerCustom* hzLobbyConncetAgainListener;
    EventListenerCustom* intnetListener;
    EventListenerCustom* loginReplaceListener;
    EventListenerCustom* payDialogListener;
    EventListenerCustom* payResultListener;
    EventListenerCustom* imageUpdateListener;
    EventListenerCustom* openRoomAskListener;
    EventListenerCustom* enterRoomAskListener;
    EventListenerCustom* scrollTetxListener;
    EventListenerCustom* noticeUrlLitener;
    EventListenerCustom* upateLequanShopLitener;
    EventListenerCustom* showLoobyLoadingLayer;
    EventListenerCustom* gameFupanListener;
    EventListenerCustom* roomListRespListener;
    EventListenerCustom* gongGaoInfoListener;
    EventListenerCustom* networkBreakListener;
    EventListenerCustom* coreLoginRespListener;
    EventListenerCustom* cmOpenRoomListener;
    EventListenerCustom* cmEnterFriendRoomListener;
    EventListenerCustom* cmLobbyConncetAgainListener;
    EventListenerCustom* fpOpenRoomListener;
    EventListenerCustom* fpEnterFriendRoomListener;
    EventListenerCustom* agencyRoomListener;
    EventListenerCustom* agencyBillListener;
    EventListenerCustom* agencyResultListener;
	void initView();
	void drawSceneMid();
	void drawSceneTop();
	void drawSceneBot();
    void openRoom();
    void joinRoom();
    void chargeGold();
    void chargeFangka();
    void exchangeLequan();
    void exchangeHuafei();
	void showFirstCharge();
	void showRedWallet();
    void showLaXinLayer();
    void showShiMing();
    void showWanJiaQun();
	void showDayTask();
    void showTeamwork();
	void showPlayerBill();
	void showGameSetting();
	void showHotActivity();
	void showHeroInfo();
    void showLoading();
    void spreadGoldRoom();
    void removeLoading();
    void showLobbyAnim();
	void addEventListener();
    void scrollLightSpot(float dt);
    void signUpdate(float dt);
    void updateHeroInfo();
    void showGongZhongHao();
};
#endif
