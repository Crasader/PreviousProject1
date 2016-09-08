//
//  GoldNotEnoughDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#include "game/mahjong/shop/GoldNotEnoughDialog.hpp"
#include "game/mahjong/shop/ChargeGold.hpp"
#include "game/mahjong/lobby/LobbyScene.h"
#include "payment/android/CallAndroidMethod.h"
#include "game/utils/GameConfig.h"

GoldNotEnoughDialog* GoldNotEnoughDialog::create(int type){
    GoldNotEnoughDialog* ret = new GoldNotEnoughDialog();
    if(ret &&ret->init(type)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool GoldNotEnoughDialog::init(int type){
    if(!Layer::init()){
        return false;
    }
    setRoomType(type);
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    auto dialogBg = Sprite::create("shop/gold_not_enough.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("shop/charge/get_gold_title.png");
    title->setPosition(640, 580);
    this->addChild(title);
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setPosition(645,375);
    addChild(bg_2);
    
    auto content = Sprite::create();
    if (type == ROOM_1){
        content->setTexture("shop/charge/gold_less_1w.png");
    }else if(type == ROOM_2){
        content->setTexture("shop/charge/gold_less_15w.png");    }
    else if(type == ROOM_3){
        content->setTexture("shop/charge/gold_less_128w.png");
    }
    content->setPosition(640,365);
    addChild(content);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(GoldNotEnoughDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(905, 535);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("shop/charge/charge_btn_1.png", "shop/charge/charge_btn_2.png",
                                         CC_CALLBACK_0(GoldNotEnoughDialog::chargeGold, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 220);
    addChild(confirmMenu);
    
    return true;
}

void GoldNotEnoughDialog::closeView(){
    removeFromParent();
}


void GoldNotEnoughDialog::chargeGold(){
    if(UserData::getInstance()->getDiamond() >= getMinGoldEnterRoom(getRoomType())/1000){
        ChargeGold* gold = ChargeGold::create();
        getParent()-> addChild(gold,4);
        removeFromParent();
    }else{
        CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),"1");
    }
}

int GoldNotEnoughDialog::getMinGoldEnterRoom(int type){
    if (type == ROOM_1){
        return ENTER_ROOM_1_GOLD;
    }else if(type == ROOM_2){
        return ENTER_ROOM_2_GOLD;

    }else if(type == ROOM_3){
        return ENTER_ROOM_3_GOLD;
    }else {
        return 0;
    }
}