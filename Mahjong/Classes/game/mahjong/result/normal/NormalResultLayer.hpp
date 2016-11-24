//
//  PublicResultLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef NormalResultLayer_hpp
#define NormalResultLayer_hpp
#include "cocos2d.h"
USING_NS_CC;

class NormalResultLayer :public  Layer{
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    CREATE_FUNC(NormalResultLayer);
private:
    EventListenerCustom* continueAgainLisetner;
    EventListenerCustom* playerReplaceLoginListener;
    int timeToatal;//自动再来一局的时间
    void showGameResult();
    void showRoomInfo();
    void showPlayerResluts();
    void showLayerBtn();
    void shareResult();
    void continueGame();
    void gotoLobby();
    void updateTime(float dt);
    void afterCaptured(bool succeed, const std::string &outputFile);
    void updateplayerData();
};
#endif /* PublicResultLayer_hpp */
