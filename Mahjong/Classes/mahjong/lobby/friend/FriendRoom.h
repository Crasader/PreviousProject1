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
    bool  shangHaiSelected = true;
    Sprite* hongZhong;
    Sprite* shangHai;
    Sprite* vertical;
    Sprite* shangHaiRoomText;
    Sprite* hongZhongRoomText;
    void openRoom();
    void closeView();
    void selectFangka8();
    void selectFangka4();
    void selectFangka16();
    void selectLeziType1();
    void selectLeziType2();
    void selectLeziType3();
    void selectLeziType4();
    void selectLeziType5();
    void selectLeziType6();
    void selectWukaibao();
    void select2mo3chong();
    void selectMa159zh();
    void selectMa159();
    void selectMa1();
    void selectDifen2();
    void selectDifen1();
    void selectDifen5();
};
#endif
