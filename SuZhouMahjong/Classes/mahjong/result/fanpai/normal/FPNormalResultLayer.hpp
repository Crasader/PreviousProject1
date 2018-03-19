//
//  PublicResultLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef FPNormalResultLayer_hpp
#define FPNormalResultLayer_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class FPNormalResultLayer :public  Layer{
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    CREATE_FUNC(FPNormalResultLayer);
private:
    EventListenerCustom* continueAgainLisetner;
    EventListenerCustom* playerReplaceLoginListener;
    EventListenerCustom* myCoreLoginRespListener;
    EventListenerCustom* networkBreakListener;
    EventListenerCustom* openFriendRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* dissovelRoomSelectNotifyListener;
    int totalTime = 7;
    LabelAtlas* timeLabel;
    bool showDissolveDialog = false;
    void showGameResult();
    void showRoomInfo();
    void showPlayerResluts();
    void showLayerBtn();
    void shareResult();
    void continueGame();
    void gotoLobby();
    void updateTime(float dt);
    void afterCaptured(bool succeed, const std::string &outputFile);
    void updatePlayerData();
    void showPrideAnim(GameResultData data);
    void showBDFanPai();
};
#endif /* PublicResultLayer_hpp */
