//
//  LequanLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/9.
//
//

#include "game/mahjong/activities/LequanLayer.hpp"
#include "game/mahjong/daily/DailyEvent.h"



bool LequanLayer::init(){
    if(!Layer::init()){
        return false;
    }
    drawLayerUi();
    return true;
}

void LequanLayer::onEnter(){
    Layer::onEnter();
}

void LequanLayer::onExit(){
    Layer::onExit();
}

void LequanLayer::drawLayerUi(){
    //box1
    auto boxBg1 = Scale9Sprite::create("shop/red_box.png");
    boxBg1->setContentSize(Size(270,360));
    boxBg1->setPosition(360,290);
    addChild(boxBg1);
    
    auto title1 = Sprite::create("activities/title_sign.png");
    title1->setPosition(360,440);
    addChild(title1);
    
    auto light1 = Sprite::create("shop/prop_light.png");
    light1->setScale(0.8f);
    light1->setPosition(360,345);
    addChild(light1);
    
    auto icon1 = Sprite::create("common/lequan_icon.png");
    icon1->setPosition(360,360);
    icon1->setScale(2.5f);
    addChild(icon1);
    
    auto textinfo1 = Sprite::create("activities/text_sign.png");
    textinfo1->setPosition(360,240);
    addChild(textinfo1);
    
    auto btnImage1 = MenuItemImage::create("activities/go_sign_1.png","activities/go_sign_2.png",CC_CALLBACK_0(LequanLayer::doFunction1,this));
    Menu* mymenu1 = Menu::create(btnImage1,NULL);
    mymenu1->setPosition(360,160);
    addChild(mymenu1);

    
    //box2
    auto boxBg2 = Scale9Sprite::create("shop/red_box.png");
    boxBg2->setContentSize(Size(270,360));
    boxBg2->setPosition(650,290);
    addChild(boxBg2);
    
    auto title2 = Sprite::create("activities/title_lequan.png");
    title2->setPosition(650,440);
    addChild(title2);
    
    auto light2 = Sprite::create("shop/prop_light.png");
    light2->setPosition(650,345);
    light2->setScale(0.8f);
    addChild(light2);
    
    auto icon2 = Sprite::create("common/lequan_icon.png");
    icon2->setPosition(650,360);
    icon2->setScale(2.5f);
    addChild(icon2);
    
    auto textinfo2 = Sprite::create("activities/text_task.png");
    textinfo2->setPosition(650,240);
    addChild(textinfo2);
    
    auto btnImage2 = MenuItemImage::create("activities/check_task_1.png","activities/check_task_2.png",CC_CALLBACK_0(LequanLayer::doFunction2,this));
    Menu* mymenu2 = Menu::create(btnImage2,NULL);
    mymenu2->setPosition(650,160);
    addChild(mymenu2);

    
    //box3
    auto boxBg3 = Scale9Sprite::create("shop/red_box.png");
    boxBg3->setContentSize(Size(270,360));
    boxBg3->setPosition(930,290);
    addChild(boxBg3);
    
    auto title3 = Sprite::create("activities/title_game.png");
    title3->setPosition(930,440);
    addChild(title3);
    
    auto light3 = Sprite::create("shop/prop_light.png");
    light3->setPosition(930,345);
    light3->setScale(0.8f);
    addChild(light3);
    
    auto icon3 = Sprite::create("common/lequan_icon.png");
    icon3->setPosition(930,360);
    icon3->setScale(2.5f);
    addChild(icon3);
    
    auto textinfo3 = Sprite::create("activities/text_lequan.png");
    textinfo3->setPosition(930,240);
    addChild(textinfo3);
    
    
    auto btnImage3 = MenuItemImage::create("activities/go_game_1.png","activities/go_game_2.png",CC_CALLBACK_0(LequanLayer::doFunction3,this));
    Menu* mymenu3 = Menu::create(btnImage3,NULL);
    mymenu3->setPosition(930,160);
    addChild(mymenu3);

}



void LequanLayer::doFunction1(){
    DailyEvent* day = DailyEvent::create();
    day->showDailyEvent(DailyType::sign);
    getParent()->getParent()-> addChild(day,3);
    getParent()-> removeFromParent();
}


void LequanLayer::doFunction2(){
    DailyEvent* day = DailyEvent::create();
    day->showDailyEvent(DailyType::task);
    getParent()->getParent()-> addChild(day,3);
    getParent()->removeFromParent();
}


void LequanLayer::doFunction3(){
    removeFromParent();
}