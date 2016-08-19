#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/playerinfo/UserInfo.h"
#include "game/mahjong/playerinfo/BoundPhone.h"
#include "game/mahjong/playerinfo/ChangePassword.h"
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
	Sprite* heroInfo;
	Sprite* boundPhone;
	Sprite* editPassword;
	MenuItemToggle* heroInfoImage;
	MenuItemToggle* boundPhoneImage;
	MenuItemToggle* editPasswordImage;
	UserInfo* userInfoLayer;
	BoundPhone* boundPhoneLayer;
	ChangePassword* changePasswordLayer;
	void clickTabBtn(Ref* ref);
    void drawHeroInfoEdit(int type);
    void closeView();
    void showTabelLayer1();
    void showTabelLayer2();
    void showTabelLayer3();
};