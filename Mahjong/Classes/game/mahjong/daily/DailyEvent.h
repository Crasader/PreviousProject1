#ifndef __DAILYEVENT_H__
#define __DAILYEVENT_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/daily/pride/DailyPride.h"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"
#include "server/CommandManage.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum DailyType{
	task,
	pride,
	welfare,
	sign
};

class DailyEvent :public Layer{
public:
	virtual bool init();
	void onEnter() override;
	void onExit() override;
	void showDailyEvent(DailyType type);
	CREATE_FUNC(DailyEvent);
private:
	DailyPride* dailyPrideLayer;
    EventListenerCustom* dailyPrideListener;
    void showDailyPride(Ref* ref);
    void closeView();
};
#endif