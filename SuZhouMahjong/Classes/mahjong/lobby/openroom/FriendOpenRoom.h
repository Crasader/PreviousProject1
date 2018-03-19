#ifndef __FRIEND_ROOM_H__
#define __FRIEND_ROOM_H__

#include "cocos2d.h"
USING_NS_CC;

class FriendOpenRoom :public Layer{
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    CREATE_FUNC(FriendOpenRoom);
private:
    int selectLayerIndex = 0;
    Sprite* suZhou;
    Sprite* hongZhong;
    Sprite* baiDa;
    Sprite* fanPaiBD;
    Sprite* vertical;
    
    void closeView();
    void showSuZhouMahjong();
    void showHongZhongMahjong();
    void showBaiDaMahjong();
    void showFanPaiBaiDaMahjong();
};
#endif
