#pragma once

#include "cocos2d.h"
USING_NS_CC;

class DailyPride :public Layer{

public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	CREATE_FUNC(DailyPride);
	
private:
	EventListenerCustom* prideCallBackListener1;
    EventListenerCustom* prideCallBackListener2;
	Menu* startMenu;
	Sprite* m_turnBg;
	void showDailyPrideLayer();
	void beginPride();
    void updateData();
	std::string getImageNameById(int id);
	Point getPosByRotation(Point pos,float r,float a);//Ô²ÐÄ£¬°ë¾¶£¬½Ç¶È
};