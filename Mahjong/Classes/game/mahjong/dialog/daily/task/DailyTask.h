#ifndef __DAILYTASK_H__
#define __DAILYTASK_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/state/GameData.h"
#include "TaskCell.h"
USING_NS_CC;
USING_NS_CC_EXT;

class DailyTask :public Layer{
public :
	virtual bool init();
    void onEnter() override;
    void onExit() override;
	void updateData();
	CREATE_FUNC(DailyTask);
private:
    EventListenerCustom* mq3;
    EventListenerCustom* pph3;
    EventListenerCustom* lz2;
    EventListenerCustom* charge;
    EventListenerCustom* extra;
    
	TaskCell* cell1;
	TaskCell* cell2;
	TaskCell* cell3;
	TaskCell* cell4;
	Menu * extraMenu;
	Sprite* lingqu;
	MenuItemImage* extraImage;
	void showDailyTaskLayer();
	void recieveExtraPride(Ref* ref);
};
#endif
