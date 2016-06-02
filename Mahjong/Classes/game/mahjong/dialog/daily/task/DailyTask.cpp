#include "game/mahjong/dialog/daily/task/DailyTask.h"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"


bool DailyTask::init(){
	if (!Layer::init()){
		return false;
	}
	showDailyTaskLayer();
	return true;
}

void DailyTask::onEnter(){
    Layer::onEnter();
}


void DailyTask::onExit(){
    Layer::onExit();
}


void DailyTask::showDailyTaskLayer(){

	cell1 = TaskCell::create(TaskType::task1);
	cell1->setPosition(307, 355);
	addChild(cell1);

	cell2 = TaskCell::create(TaskType::task2);
	cell2->setPosition(307+222, 355);
	addChild(cell2);

	cell3 = TaskCell::create(TaskType::task3);
	cell3->setPosition(307 + 222*2, 355);
	addChild(cell3);

	cell4 = TaskCell::create(TaskType::task4);
	cell4->setPosition(307+222*3, 355);
	addChild(cell4);

	auto text_info = Sprite::create("daily/task/wanchen_renwu.png");
	text_info->setPosition(410, 125);
	addChild(text_info);

	extra = MenuItemImage::create("daily/recieve_btn_small_1.png", "daily/recieve_btn_small_2.png","daily/recieve_btn_small_3.png",
		CC_CALLBACK_1(DailyTask::recieveExtraPride, this));
	extraMenu = Menu::create(extra, NULL);
	extraMenu->setPosition(660, 125);

	addChild(extraMenu);

	lingqu = Sprite::create("daily/task/yilingqu.png");
	lingqu->setPosition(660, 125);
	addChild(lingqu);

	if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "-1"){
		extraMenu->setVisible(false);
		lingqu->setVisible(true);
	}else if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "0"){
		extra->setEnabled(false);
		lingqu->setVisible(false);
	}
	else{
        extraMenu->setVisible(false);
		lingqu->setVisible(false);
	}
}


void DailyTask::updateData(){
	if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "-1"){
		extraMenu->setVisible(false);
		lingqu->setVisible(true);
	}
	else if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "0"){
		extra->setEnabled(false);
		lingqu->setVisible(false);
	}
	else{
		lingqu->setVisible(false);
	}
	cell1->updateData();
	cell2->updateData();
	cell3->updateData();
	cell4->updateData();
}

void DailyTask::recieveExtraPride(Ref* ref){
	//MenuItemImage* temp = (MenuItemImage*)ref;
	//temp->setEnabled(false);
}