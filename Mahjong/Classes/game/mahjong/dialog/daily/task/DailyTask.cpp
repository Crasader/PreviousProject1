#include "DailyTask.h"
#include "game/mahjong/state/GameData.h"
#include "server/NetworkManage.h"
#include "userdata/UserData.h"
#include "game/utils/ParticleUtil.hpp"


bool DailyTask::init(){
    if (!Layer::init()){
        return false;
    }
    showDailyTaskLayer();
    return true;
}

void DailyTask::onEnter(){
    Layer::onEnter();
    mq3 = EventListenerCustom::create(MSG_PLAYER_DAILY_TASK_MQ3, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setGold(UserData::getInstance()->getGold()+4000);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(mq3, 1);
    
     pph3 = EventListenerCustom::create(MSG_PLAYER_DAILY_TASK_PPH3, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setGold(UserData::getInstance()->getGold()+4000);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(pph3, 1);
    
    lz2 = EventListenerCustom::create(MSG_PLAYER_DAILY_TASK_LZ2, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setGold(UserData::getInstance()->getGold()+4000);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(lz2, 1);
    
    charge = EventListenerCustom::create(MSG_PLAYER_DAILY_TASK_CHARGE, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::goldOnly);
            getParent()->addChild(util,5);
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(charge, 1);
    
    extra = EventListenerCustom::create(MSG_PLAYER_DAILY_TASK_EXTRA, [=](EventCustom* event){
        std::string result = static_cast<char*>(event->getUserData());
        if(result == "1"){
            UserData::getInstance()->setTicket(UserData::getInstance()->getTicket()+20);
            EventCustom ev(MSG_UPDATE_HERO_INFO);
            _eventDispatcher->dispatchEvent(&ev);
            ParticleUtil* util = ParticleUtil::create(MyParticleType::lequanOnly);
            getParent()->addChild(util,5);
        }
    });
    _eventDispatcher->addEventListenerWithFixedPriority(extra, 1);
}


void DailyTask::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(mq3);
    _eventDispatcher->removeEventListener(pph3);
    _eventDispatcher->removeEventListener(lz2);
    _eventDispatcher->removeEventListener(charge);
    _eventDispatcher->removeEventListener(extra);
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
        extraMenu->setEnabled(false);
        lingqu->setVisible(false);
    }
    else{
        extraMenu->setVisible(true);
        lingqu->setVisible(false);
    }
}


void DailyTask::updateData(){
    if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "-1"){
        extraMenu->setVisible(false);
        lingqu->setVisible(true);
    }
    else if (GAMEDATA::getInstance()->getDailyTaskInfo().extra == "0"){
        extraMenu->setEnabled(false);
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
    MenuItemImage* temp = (MenuItemImage*)ref;
    temp->setEnabled(false);
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getTaskExtraCommand());
}
