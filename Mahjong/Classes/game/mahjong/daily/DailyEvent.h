#ifndef __DAILYEVENT_H__
#define __DAILYEVENT_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/daily/sign/DailySign.h"
#include "game/mahjong/daily/task/DailyTask.h"
#include "game/mahjong/daily/pride/DailyPride.h"
#include "game/mahjong/daily/welfare/DailyWelfare.h"
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
	Sprite* dailyTask;
	Sprite* dailyPride;
	Sprite* dailyWelfare;
	Sprite* dailySign;
	DailySign* dailySignLayer;
	DailyWelfare* dailyWelfareLayer;
	DailyTask* dailyTaskLayer;
	DailyPride* dailyPrideLayer;
	MenuItemToggle* prideToggle;
	MenuItemToggle* welfareToggle;
	MenuItemToggle* taskToggle;
	MenuItemToggle* signToggle;
    
	EventListenerCustom* dailyTaskListener;
    EventListenerCustom* dailyWelfareListener;
    EventListenerCustom* dailyPrideListener;
    EventListenerCustom* dailySignListener;
    
	void showDailyTask(Ref* ref);
	void showWelFare(Ref* ref);
	void showDailyPride(Ref* ref);
	void showDailySign(Ref* ref);
	void closeView();
};
#endif