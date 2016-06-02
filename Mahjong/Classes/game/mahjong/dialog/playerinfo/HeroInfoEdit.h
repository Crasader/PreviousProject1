#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/dialog/playerinfo/UserInfo.h"
#include "game/mahjong/dialog/playerinfo/BoundPhone.h"
#include "game/mahjong/dialog/playerinfo/ChangePassword.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HeroInfoEdit : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(HeroInfoEdit);
private:
	void drawHeroInfoEdit();
	void closeView();
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
	
};