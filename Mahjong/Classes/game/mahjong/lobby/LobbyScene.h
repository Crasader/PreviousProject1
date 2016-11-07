#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "game/utils/StringUtil.h"
#include "game/mahjong/loading/Loading.h"
#include "game/mahjong/state/GameData.h"
#include "game/mahjong/core/MjGameScene.h"
#include "game/mahjong/setting/UserSetting.h"
#include "game/mahjong/friend/FriendListView.h"
#include "game/mahjong/friend/FriendRoom.h"
#include "game/mahjong/bill/BillInfo.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
#include "userdata/UserData.h"

USING_NS_CC;

class LobbyScene : public cocos2d::Scene
{
public:

    virtual bool init() override;
	virtual void onEnter() override;
	virtual void onExit() override;
    CREATE_FUNC(LobbyScene);
private:
    
	Label* nickName;
	LabelAtlas* goldNum;
	LabelAtlas* fangkaNum;
	LabelAtlas* lequanNum;
    MenuItemImage* first_chaege;
    
    EventListenerCustom* enterRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* openFriendRoomListener;
    EventListenerCustom* friendInviteListener;
    EventListenerCustom* updateHeroInfoListener;
    EventListenerCustom* lobbyConncetAgainListener;
    EventListenerCustom* intnetListener;
    EventListenerCustom* loginReplaceListener;
    EventListenerCustom* inviteReplaceListener;
    EventListenerCustom* friendChatListener;
    EventListenerCustom* payDialogListener;
    EventListenerCustom* payResultListener;
    EventListenerCustom* imageUpdateListener;
    EventListenerCustom* firstChargeListenr;
    EventListenerCustom* openRoomAskListener;
    EventListenerCustom* enterRoomAskListener;
    
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
	void showDayTask();
	void showAddFriend();
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