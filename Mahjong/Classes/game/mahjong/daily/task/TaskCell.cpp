#include "game/mahjong/daily/task/TaskCell.h"
#include "server/NetworkManage.h"

TaskCell* TaskCell::create(TASKID taskId){
    TaskCell* bRet = new TaskCell();
    if (bRet&&bRet->init(taskId))
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

bool TaskCell::init(TASKID taskId){
    if (!Sprite::init()){
        return false;
    }
    setTaskState(0);
    setTaskID(taskId);
    
    setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    initWithFile("daily/task/content_bg.png");
    
    auto piao_dai = Sprite::create(getPiaoDaiImageById(taskId));
    piao_dai->setPosition(100, 353);
    addChild(piao_dai);
    
    auto title = Sprite::create(getTitleImageById(taskId));
    title->setPosition(100, 353);
    addChild(title);
    
    auto content = Sprite::create(getContentImageById(taskId));
    content->setPosition(100, 258);
    addChild(content);
    
    
    auto pride = Sprite::create(getPrideImageById(taskId));
    pride->setPosition(100, 138);
    addChild(pride);
    
    drawTaskFinishStateById(taskId);
    
    updateData(taskId);
    
    return true;
}


void TaskCell::recievePride(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    temp->setEnabled(false);
    if (getTaskID() == task1){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskMQ3Command());
    }
    else if (getTaskID() == task2){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskPPH3Command());
    }
    else if (getTaskID() == task3){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskLZ4Command());
    }
    else{
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskMQ3Command());
    }
    
}

void TaskCell::charge(){
    
}

void TaskCell::drawTaskFinishStateById(TASKID taskId){
    if (taskId != task4){
        auto jindu_bg = Sprite::create("daily/task/jingdutiao_bg.png");
        jindu_bg->setPosition(100, 93);
        addChild(jindu_bg);
        
        taskProgress = Scale9Sprite::create("daily/task/jindutiao.png");
        taskProgress->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        taskProgress->setContentSize(Size(146 * 0 / getTaskFinishConditionById(taskId), 20));
        taskProgress->setPosition(25, 93);
        addChild(taskProgress);
        
        std::string num = StringUtils::format("%d:%d", 0, getTaskFinishConditionById(taskId));
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
    if (taskId != task4){
        std::string unfinishImage = cocos2d::String::createWithFormat("daily/task/task_info_%d.png", taskId)->_string;
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
    auto finish = MenuItemImage::create("daily/recieve_btn_1.png", "daily/recieve_btn_2.png","daily/recieve_btn_3.png",
                                        CC_CALLBACK_1(TaskCell::recievePride, this));
    finishMenu = Menu::create(finish, NULL);
    finishMenu->setPosition(100, 40);
    finishMenu->setVisible(false);
    addChild(finishMenu);
    
    revcieved = Sprite::create("daily/task/yilingqu.png");
    revcieved->setPosition(100, 40);
    revcieved->setVisible(false);
    addChild(revcieved);

}

void TaskCell::updateData(TASKID taskId){
    if (!isVisible()){
        return;
    }
    DailyTaskData data = GAMEDATA::getInstance()->getDailyTaskInfo();
    std::string result;
    if (getTaskID() == task1){
        result = data.task1;
    }
    else if (getTaskID() == task2){
        result = data.task2;
    }
    else if (getTaskID() == task3){
        result = data.task3;
    }
    else{
        result = data.task4;
    }
    if (getTaskID() != task4){
        if (result == "-1"){
            taskProgress->setContentSize(Size(146, 20));
            taskFinishNum->setString(cocos2d::String::createWithFormat("%d:%d", getTaskFinishConditionById(taskId),getTaskFinishConditionById(taskId))->_string);
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
            float rate =  1.0f*res / (getTaskFinishConditionById(taskId));
            if(rate>1){
                rate =1;
            }
            taskProgress->setContentSize(Size(146 *rate, 20));
            taskFinishNum->setString(cocos2d::String::createWithFormat("%d:%d",res,getTaskFinishConditionById(taskId))->_string);
            if (res == (getTaskFinishConditionById(taskId))){
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


std::string TaskCell:: getPiaoDaiImageById(TASKID taskId){
    std::string iamgeName = StringUtils::format("daily/task/piao_dai_%d.png",taskId == task4 ? 2 : 1);
    return iamgeName;
}

std::string TaskCell:: getTitleImageById(TASKID taskId){
    std::string iamgeName = StringUtils::format("daily/task/day_task_%d.png",taskId);
    return iamgeName;
}

std::string TaskCell::getContentImageById(TASKID taskId){
    std::string iamgeName = StringUtils::format("daily/task/gold_icon_%d.png",taskId == task4 ? 3 : 1);
    return iamgeName;
}

std::string TaskCell::getPrideImageById(TASKID taskId){
    std::string prideName = (taskId == task4 ? "daily/task/60_diamond_2w_gold.png" : "daily/task/pride_4000.png");
    return prideName;
}

int TaskCell::getTaskFinishConditionById(TASKID taskId){
    if(taskId == task1){
        return 3;
    }else if(taskId == task2){
        return 1;
    }else if(taskId == task3){
        return 2;
    }else if(taskId == task4){
        return 0;
    }
}
