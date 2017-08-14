//
//  PublicResultLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef CMNormalResultLayer_hpp
#define CMNormalResultLayer_hpp
#include "cocos2d.h"
#include "mahjong/common/state/GameData.h"
USING_NS_CC;

class CMNormalResultLayer :public  Layer{
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    CREATE_FUNC(CMNormalResultLayer);
private:
    EventListenerCustom* continueAgainLisetner;
    EventListenerCustom* playerReplaceLoginListener;
    EventListenerCustom* myCoreLoginRespListener;
    EventListenerCustom* networkBreakListener;
    EventListenerCustom* openFriendRoomListener;
    EventListenerCustom* enterFriendRoomListener;
    EventListenerCustom* dissovelRoomSelectNotifyListener;
    int totalTime = 5;
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
    void showCangYin();
};
#endif /* PublicResultLayer_hpp */
