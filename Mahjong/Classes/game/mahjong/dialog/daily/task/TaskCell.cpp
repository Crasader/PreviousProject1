#include "game/mahjong/dialog/daily/task/TaskCell.h"
#include "server/NetworkManage.h"

TaskCell* TaskCell::create(TaskType type){
	TaskCell* bRet = new TaskCell();
	if (bRet&&bRet->init(type))
	{
		bRet->autorelease();
		return bRet;
	}
	else
	{
		delete bRet;
		bRet = NULL;
		return NULL;
	}
}

bool TaskCell::init(TaskType type){
	if (!Sprite::init()){
		return false;
	}
	setTaskState(0);
	setMyTaskType(type);
	this->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	initWithFile("daily/task/content_bg.png");

	std::string piaoName = cocos2d::String::createWithFormat("daily/task/piao_dai_%d.png", type == task4 ? 2 : 1)->_string;
	auto piao_dai = Sprite::create(piaoName);
	piao_dai->setPosition(100, 353);
	addChild(piao_dai);

	std::string imageName = cocos2d::String::createWithFormat("daily/task/day_task_%d.png", type)->_string;
	auto title = Sprite::create(imageName);
	title->setPosition(100, 353);
	addChild(title);

	std::string contentName = cocos2d::String::createWithFormat("daily/task/gold_icon_%d.png", type == task4 ? 3 : 1)->_string;
	auto content = Sprite::create(contentName);
	content->setPosition(100, 258);
	addChild(content);

	std::string prideName = (type == task4 ? "daily/task/60_diamond_2w_gold.png" : "daily/task/pride_4000.png");
	auto pride = Sprite::create(prideName);
	pride->setPosition(100, 138);
	addChild(pride);

	if (type != task4){
		auto jindu_bg = Sprite::create("daily/task/jingdutiao_bg.png");
		jindu_bg->setPosition(100, 93);
		addChild(jindu_bg);

		taskProgress = Scale9Sprite::create("daily/task/jindutiao.png");
		taskProgress->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		taskProgress->setContentSize(Size(146 * 0 / (type == task3 ? 2 : 3), 20));
		taskProgress->setPosition(25, 93);
		addChild(taskProgress);

		std::string num = cocos2d::String::createWithFormat("%d:%d", 0, type == task3 ? 2 : 3)->_string;
		taskFinishNum = LabelAtlas::create(num, "daily/task/num.png", 16, 24, '0');
		taskFinishNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
		taskFinishNum->setPosition(100, 93);
		addChild(taskFinishNum);

	}
	else{
		auto charge = Sprite::create("daily/task/charge_6_yuan.png");
		charge->setPosition(100, 93);
		addChild(charge);
	}
	auto finish = MenuItemImage::create("daily/recieve_btn_1.png", "daily/recieve_btn_2.png","daily/recieve_btn_3.png",
		CC_CALLBACK_1(TaskCell::recievePride, this));
	finishMenu = Menu::create(finish, NULL);
	finishMenu->setPosition(100, 40);
	finishMenu->setVisible(false);
	addChild(finishMenu);
	if (type != task4){
		std::string unfinishImage = cocos2d::String::createWithFormat("daily/task/task_info_%d.png", type)->_string;
		unfinish = Sprite::create(unfinishImage);
		unfinish->setPosition(100, 40);
		unfinish->setVisible(false);
		addChild(unfinish);
	}
	else{
		auto chargeItem = MenuItemImage::create("daily/task/charge_btn_1.png", "daily/task/charge_btn_2.png",
			CC_CALLBACK_0(TaskCell::charge, this));
		chargeMenu = Menu::create(chargeItem, NULL);
		chargeMenu->setPosition(100, 40);
		chargeMenu->setVisible(false);
		addChild(chargeMenu);
	}
	revcieved = Sprite::create("daily/task/yilingqu.png");
	revcieved->setPosition(100, 40);
	revcieved->setVisible(false);
	addChild(revcieved);
	updateData();
	return true;
}


void TaskCell::recievePride(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    temp->setEnabled(false);
	if (getMyTaskType() == task1){
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskMQ3Command());
	}
	else if (getMyTaskType() == task2){
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskPPH3Command());
	}
	else if (getMyTaskType() == task3){
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskLZ4Command());
	}
	else{
		NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskMQ3Command());
	}

}

void TaskCell::charge(){

}

void TaskCell::updateData(){
	if (!isVisible()){
		return;
	}
	DailyTaskData data = GAMEDATA::getInstance()->getDailyTaskInfo();
	std::string result;
	if (getMyTaskType() == task1){
		result = data.task1;
	}
	else if (getMyTaskType() == task2){
		result = data.task2;
	}
	else if (getMyTaskType() == task3){
		result = data.task3;
	}
	else{
		result = data.task4;
	}
	if (getMyTaskType() != task4){
		if (result == "-1"){
			taskProgress->setContentSize(Size(146, 20));
			taskFinishNum->setString(cocos2d::String::createWithFormat("%d:%d", getMyTaskType() == task3 ? 2 : 3, getMyTaskType() == task3 ? 2 : 3)->_string);
			setTaskState(2);
			finishMenu->setVisible(false);
			unfinish->setVisible(false);
			revcieved->setVisible(true);
		}
		else {
			int res = atoi(result.c_str());
			finishMenu->setVisible(false);
			unfinish->setVisible(true);
			revcieved->setVisible(false);
            float rate =  res / (getMyTaskType() == task3 ? 2 : 3);
            if(rate>1){
                rate =1;
            }
			taskProgress->setContentSize(Size(146 *rate, 20));
			taskFinishNum->setString(cocos2d::String::createWithFormat("%d:%d",res, getMyTaskType() == task3 ? 2 : 3)->_string);
			if (res == (getMyTaskType() == task3 ? 2 : 3)){
				setTaskState(1);
				finishMenu->setVisible(true);
				unfinish->setVisible(false);
				revcieved->setVisible(false);
			}
		}
	}
	else{
		if (result == "-1"){
			chargeMenu->setVisible(false);
			revcieved->setVisible(true);
		}
		else{
			chargeMenu->setVisible(true);
			revcieved->setVisible(false);
		}
	}

}