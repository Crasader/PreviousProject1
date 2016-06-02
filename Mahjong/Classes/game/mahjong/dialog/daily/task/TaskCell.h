#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;
USING_NS_CC_EXT;
enum TaskType{
	task1=1,
	task2,
	task3,
	task4
};
class TaskCell :public Sprite{
public:
	virtual bool init(TaskType type);
	static TaskCell* create(TaskType type);
	void updateData();
	CC_SYNTHESIZE(TaskType, myTaskType, MyTaskType);
	CC_SYNTHESIZE(int,taskState,TaskState);
private:
	Scale9Sprite* taskProgress;
	LabelAtlas* taskFinishNum;
	Menu* finishMenu;
	Sprite* unfinish;
	Sprite* revcieved;
	Menu* chargeMenu;
	void recievePride();
	void charge();
};