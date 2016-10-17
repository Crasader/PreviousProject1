#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/heroinfo/UserInfo.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HeroInfoEdit : public Layer{
public:
    static HeroInfoEdit* create(int type);
	virtual bool init(int type);
    void onEnter() override;
    void onExit() override;
private:
    EventListenerCustom* closeDialogListener;
	UserInfo* userInfoLayer;
    void drawHeroInfoEdit(int type);
    void closeView();
};