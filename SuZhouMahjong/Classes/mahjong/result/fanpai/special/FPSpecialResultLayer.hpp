//
//  PublicResultLayer.hpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/21.
//
//

#ifndef FPSpecialResultLayer_hpp
#define FPSpecialResultLayer_hpp
#include "cocos2d.h"
USING_NS_CC;

class FPSpecialResultLayer :public  Layer{
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    CREATE_FUNC(FPSpecialResultLayer);
private:
    void showResultTitle();
    void showGameReslut();
    void showLayerBtn();
    void shareResult();
    void gotoLobby();
    void afterCaptured(bool succeed, const std::string &outputFile);
    void update(float dt);
    EventListenerCustom* myCoreLoginRespListener;
    EventListenerCustom* networkBreakListener;

};
#endif /* PublicResultLayer_hpp */
