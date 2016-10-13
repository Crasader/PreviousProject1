#include "game/mahjong/daily/DailyEvent.h"
#include "game/utils/Audio.h"

bool DailyEvent::init(){
    if (!Layer::init()){
        return false;
    }
    return true;
}

void DailyEvent::onEnter(){
    Layer::onEnter();
    dailyTaskListener = EventListenerCustom::create(MSG_PLAYER_DAILY_TASK, [=](EventCustom* event){
        if (dailyTaskLayer->isVisible()){
            dailyTaskLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailyTaskListener, 1);
    
    dailyWelfareListener = EventListenerCustom::create(MSG_PLAYER_WELFARE_INFO, [=](EventCustom* event){
        if (dailyWelfareLayer->isVisible()){
            dailyWelfareLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailyWelfareListener, 1);
    
    dailyPrideListener = EventListenerCustom::create(MSG_PLAYER_DAILY_PRIDE, [=](EventCustom* event){
        if (dailyPrideLayer->isVisible()){
            dailyPrideLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailyPrideListener, 1);
    
    dailySignListener = EventListenerCustom::create(MSG_PLAYER_DAILY_SIGN, [=](EventCustom* event){
        if (dailySignLayer->isVisible()){
            dailySignLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailySignListener, 1);
}

void DailyEvent::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(dailyTaskListener);
    _eventDispatcher->removeEventListener(dailyWelfareListener);
    _eventDispatcher->removeEventListener(dailyPrideListener);
    _eventDispatcher->removeEventListener(dailySignListener);
}

void DailyEvent::showDailyEvent(DailyType type){
    
    if(type == DailyType::pride){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyPrideCommand());//任务
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1,-1);
    
    auto day_bg = Sprite::create("daily/daily_bg.png");
    day_bg->setPosition(640, 360);
    addChild(day_bg);
    
    //add close btn to layer
    auto close = MenuItemImage::create("daily/close_btn_1.png", "daily/close_btn_2.png",
                                       CC_CALLBACK_0(DailyEvent::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(1050, 610);
    addChild(closeMenu,1);
    
    dailyPrideLayer = DailyPride::create();
    dailyPrideLayer->setVisible(true);
    addChild(dailyPrideLayer);
    
}


void DailyEvent::showDailyTask(Ref* ref){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyTaskCommand());//任务
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    taskToggle->setSelectedIndex(1);
    welfareToggle->setSelectedIndex(0);
    prideToggle->setSelectedIndex(0);
    signToggle->setSelectedIndex(0);
    dailyTask->setTexture("daily/daily_task_2.png");
    dailyWelfare->setTexture("daily/daily_welfare_1.png");
    dailyPride->setTexture("daily/daily_pride_1.png");
    dailySign->setTexture("daily/daily_sign_1.png");
    dailyTaskLayer->setVisible(true);
    dailyTaskLayer->setLocalZOrder(100);
    dailyWelfareLayer->setVisible(false);
    dailySignLayer->setVisible(false);
    dailyPrideLayer->setVisible(false);
}

void DailyEvent::showWelFare(Ref* ref){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getWelfareCommand());//福利
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    taskToggle->setSelectedIndex(0);
    welfareToggle->setSelectedIndex(1);
    prideToggle->setSelectedIndex(0);
    signToggle->setSelectedIndex(0);
    dailyTask->setTexture("daily/daily_task_1.png");
    dailyWelfare->setTexture("daily/daily_welfare_2.png");
    dailyPride->setTexture("daily/daily_pride_1.png");
    dailySign->setTexture("daily/daily_sign_1.png");
    dailyTaskLayer->setVisible(false);
    dailyWelfareLayer->setVisible(true);
    dailyWelfareLayer->setLocalZOrder(100);
    dailyPrideLayer->setVisible(false);
    dailySignLayer->setVisible(false);
}

void DailyEvent::showDailyPride(Ref* ref){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyPrideCommand());//抽奖
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    taskToggle->setSelectedIndex(0);
    welfareToggle->setSelectedIndex(0);
    prideToggle->setSelectedIndex(1);
    signToggle->setSelectedIndex(0);
    dailyTask->setTexture("daily/daily_task_1.png");
    dailyWelfare->setTexture("daily/daily_welfare_1.png");
    dailyPride->setTexture("daily/daily_pride_2.png");
    dailySign->setTexture("daily/daily_sign_1.png");
    dailyTaskLayer->setVisible(false);
    dailyWelfareLayer->setVisible(false);
    dailyPrideLayer->setVisible(true);
    dailyPrideLayer->setLocalZOrder(100);
    dailySignLayer->setVisible(false);
}

void DailyEvent::showDailySign(Ref* ref){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailySignCommand());//签到
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    taskToggle->setSelectedIndex(0);
    welfareToggle->setSelectedIndex(0);
    prideToggle->setSelectedIndex(0);
    signToggle->setSelectedIndex(1);
    dailyTask->setTexture("daily/daily_task_1.png");
    dailyWelfare->setTexture("daily/daily_welfare_1.png");
    dailyPride->setTexture("daily/daily_pride_1.png");
    dailySign->setTexture("daily/daily_sign_2.png");
    dailyTaskLayer->setVisible(false);
    dailyWelfareLayer->setVisible(false);
    dailyPrideLayer->setVisible(false);
    dailySignLayer->setVisible(true);
    dailySignLayer->setLocalZOrder(100);
}

void DailyEvent::closeView(){
    Audio::getInstance()->playSoundClick();
    removeFromParent();
}
