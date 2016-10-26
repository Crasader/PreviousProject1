#ifndef __FRIEND_ROOM_H__
#define __FRIEND_ROOM_H__

#include "cocos2d.h"
USING_NS_CC;

class FriendRoom :public Layer{
public:
    virtual bool init();
    virtual void onEnter() override;
    virtual void onExit() override;
    CREATE_FUNC(FriendRoom);
private:
    void openRoom();
    void closeView();
    void selectFangka8();
    void selectFangka16();
};
#endif