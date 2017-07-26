#ifndef __FRIEND_ROOM_H__
#define __FRIEND_ROOM_H__

#include "cocos2d.h"
USING_NS_CC;

class FriendRoom :public Layer{
public:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    bool onTouchBegan(Touch *touch, Event  *event) override;
    void onTouchMoved(Touch *touch, Event  *event) override;
    void onTouchEnded(Touch *touch, Event  *event) override;
    CREATE_FUNC(FriendRoom);
private:
    int selectLayerIndex = 0;
    Sprite* hongZhong;
    Sprite* shangHai;
    Sprite* vertical;
    Sprite* shangHaiRoomText;
    Sprite* hongZhongRoomText;
    void closeView();
    void select2People();
    void select4People();
    void selectFangka8();
    void selectFangka4();
    void selectFangka16();
    void openRoom();
    void showShangHaiMahjong();
    void showHongZhongMahjong();
    void showChongMingMahjong();
    void showNanHuiMahjong();
};
#endif
