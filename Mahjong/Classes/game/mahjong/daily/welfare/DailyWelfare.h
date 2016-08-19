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
    EventListenerCustom* JJJRespListener;
    EventListenerCustom* BZJJRespListener;
    EventListenerCustom* WXRespListener;
    EventListenerCustom* SJRespListener;
	void showDailyWelfareLayer();
	void recievePride(Ref* ref);

};