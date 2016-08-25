#pragma once

#include "cocos2d.h"
USING_NS_CC;

class DailyWelfare :public Layer{
public :
	virtual bool init();
    void onEnter() override;
    void onExit() override;
	CREATE_FUNC(DailyWelfare);
    void updateData();
private:
    EventListenerCustom* WXRespListener;
    EventListenerCustom* SJRespListener;
	void showDailyWelfareLayer();
	void recievePride(Ref* ref);

};