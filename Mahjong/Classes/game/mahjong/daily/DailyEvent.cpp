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
    
    dailyPrideListener = EventListenerCustom::create(MSG_PLAYER_DAILY_PRIDE, [=](EventCustom* event){
        if (dailyPrideLayer->isVisible()){
            dailyPrideLayer->updateData();
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(dailyPrideListener, 1);
    
}

void DailyEvent::onExit(){
    Layer::onExit();
    _eventDispatcher->removeEventListener(dailyPrideListener);
    
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


void DailyEvent::showDailyPride(Ref* ref){
    Audio::getInstance()->playSoundClick();
    NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDailyPrideCommand());//抽奖
    MenuItemToggle* temp = (MenuItemToggle*)ref;
    dailyPrideLayer->setVisible(true);
    dailyPrideLayer->setLocalZOrder(100);
}


void DailyEvent::closeView(){
    Audio::getInstance()->playSoundClick();
    removeFromParent();
}
