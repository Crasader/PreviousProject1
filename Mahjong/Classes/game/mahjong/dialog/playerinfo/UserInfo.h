#ifndef __USER_INFO_H__
#define __USER_INFO_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class UserInfo :public Layer{
public:
	virtual bool init();
	void updateNickname();
	void updateGender();
	CREATE_FUNC(UserInfo);
private:
	Label* nickNameLabel;
	Sprite* playerGender;
	Menu* changeNickName;
	void showUserInfo();
	void editHeadImage();
	void menuBtnClick(Ref* ref);
};
#endif