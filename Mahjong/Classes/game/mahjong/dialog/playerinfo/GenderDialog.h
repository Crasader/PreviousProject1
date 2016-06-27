#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class GenderDialog :public Layer{
public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	CREATE_FUNC(GenderDialog);
private:
	Sprite* nike;
	void showDialog();
	void choseGender(Ref* ref);
	void changeGender();
	void closeView();
};