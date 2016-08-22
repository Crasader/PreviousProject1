#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "game/mahjong/state/GameData.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum TASKID{
    task1 =1,
    task2,
    task3,
    task4
};

class TaskCell :public Sprite{
public:
	virtual bool init(TASKID taskId);
	static TaskCell* create(TASKID type);
	void updateData();
	CC_SYNTHESIZE(TASKID, taskID, TaskID);
	CC_SYNTHESIZE(int,taskState,TaskState);
private:
	Scale9Sprite* taskProgress;
	LabelAtlas* taskFinishNum;
	Menu* finishMenu;
	Sprite* unfinish;
	Sprite* revcieved;
	Menu* chargeMenu;
	void recievePride(Ref* ref);
	void charge();
    std::string getPiaoDaiImageById(TASKID taskId);
    std::string getTitleImageById(TASKID taskId);
    std::string getContentImageById(TASKID taskId);
    std::string getPrideImageById(TASKID taskId);
    int getTaskFinishConditionById(TASKID taskId);
};