//
//  PublicResultLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef HZ_NormalResultLayer_hpp
#define HZ_NormalResultLayer_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class HZNormalResultLayer :public  Layer{
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    CREATE_FUNC(HZNormalResultLayer);
private:
    EventListenerCustom* continueAgainLisetner;
    EventListenerCustom* playerReplaceLoginListener;
    EventListenerCustom* myCoreLoginRespListener;
    EventListenerCustom* networkBreakListener;
    EventListenerCustom* openFriendRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* hzEnterFriendRoomListener;
    EventListenerCustom* dissovelRoomSelectNotifyListener;
    int totalTime = 5;
    LabelAtlas* timeLabel;
    bool showDissolveDialog = false;
    void showGameResult();
    void showRoomInfo();
    void showHZMa();
    void showPlayerResluts();
    void showLayerBtn();
    void shareResult();
    void continueGame();
    void gotoLobby();
    void updateTime(float dt);
    void afterCaptured(bool succeed, const std::string &outputFile);
    void updatePlayerData();
    void showPrideAnim(GameResultData data);
};
#endif /* PublicResultLayer_hpp */
