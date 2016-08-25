#include "game/mahjong/daily/task/DailyTask.h"
#include "game/mahjong/state/GameData.h"
#include "game/utils/ParticleUtil.hpp"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"



bool DailyTask::init(){
    if (!Layer::init()){
        return false;
    }
    showDailyTaskLayer();
    return true;
}

void DailyTask::onEnter(){
    Layer::onEnter();
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_DAILY_TASK_MQ3, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setGold(UserData::getInstance()->getGold()+4000);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_DAILY_TASK_PPH3, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setGold(UserData::getInstance()->getGold()+4000);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_DAILY_TASK_LZ2, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setGold(UserData::getInstance()->getGold()+4000);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_DAILY_TASK_CHARGE, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    
    Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PLAYER_DAILY_TASK_EXTRA, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setTicket(UserData::getInstance()->getTicket()+20);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::lequanOnly);
            getParent()->addChild(util,5);
        }
    });
}


void DailyTask::onExit(){
    Layer::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_DAILY_TASK_MQ3);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_DAILY_TASK_PPH3);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_DAILY_TASK_LZ2);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_DAILY_TASK_CHARGE);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(MSG_PLAYER_DAILY_TASK_EXTRA);
}


void DailyTask::showDailyTaskLayer(){
    
    cell1 = TaskCell::create(TASKID::task1);
    cell1->setPosition(307, 355);
    addChild(cell1);
    
    cell2 = TaskCell::create(TASKID::task2);
    cell2->setPosition(307+222, 355);
    addChild(cell2);
    
    cell3 = TaskCell::create(TASKID::task3);
    cell3->setPosition(307 + 222*2, 355);
    addChild(cell3);
    
    cell4 = TaskCell::create(TASKID::task4);
    cell4->setPosition(307+222*3, 355);
    addChild(cell4);
    
    auto text_info = Sprite::create("daily/task/wanchen_renwu.png");
    text_info->setPosition(410, 125);
    addChild(text_info);
    
    extraImage = MenuItemImage::create("daily/recieve_btn_small_1.png", "daily/recieve_btn_small_2.png","daily/recieve_btn_small_3.png",
                                       CC_CALLBACK_1(DailyTask::recieveExtraPride, this));
    extraMenu = Menu::create(extraImage, NULL);
    extraMenu->setPosition(660, 125);
    
    addChild(extraMenu);
    
    lingqu = Sprite::create("daily/task/yilingqu.png");
    lingqu->setPosition(660, 125);
    addChild(lingqu);
    
    if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "-1"){
        extraMenu->setVisible(false);
        lingqu->setVisible(true);
    }else if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "0"){
        extraImage->setEnabled(false);
        lingqu->setVisible(false);
    }
    else{
        extraMenu->setVisible(true);
        extraImage->setEnabled(true);
        lingqu->setVisible(false);
    }
}


void DailyTask::updateData(){
    if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "-1"){
        extraMenu->setVisible(false);
        lingqu->setVisible(true);
    }
    else if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "0"){
        extraImage->setEnabled(false);
        lingqu->setVisible(false);
    }
    else{
        extraMenu->setVisible(true);
        extraImage->setEnabled(true);
        lingqu->setVisible(false);
    }
    cell1->updateData(task1);
    cell2->updateData(task2);
    cell3->updateData(task3);
    cell4->updateData(task4);
}

void DailyTask::recieveExtraPride(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*)ref;
    temp->setEnabled(false);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskExtraCommand());
}