#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class UserInfo :public Layer{
public:
    virtual bool init() override;
    void onEnter() override;
    void onExit() override;
    void updateGender();
    void updateHeadImage();
    CREATE_FUNC(UserInfo);
private:
    EventListenerCustom* updateImageListener;
    Sprite* playerGender;
    void showUserInfo();
    void editHeadImage();
    void cleanAccountRercord();
};
