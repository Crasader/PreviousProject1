#ifndef __USER_SETTING_H__
#define __USER_SETTING_H__
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "mahjong/common/dialog/base/BaseDialog.h"
USING_NS_CC;
USING_NS_CC_EXT;


class UserSetting :public BaseDialog{
public:
	virtual bool init();
	CREATE_FUNC(UserSetting);
private:
    void showGameHelp();
    void feedBack();
    void dissolveRoom();
	void drawDialog() override;
    void slideCallback(Ref *sender, Control::EventType controlEvent);
};
#endif