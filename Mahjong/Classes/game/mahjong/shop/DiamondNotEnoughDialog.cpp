//
//  GoldNotEnoughDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#include "game/mahjong/shop/DiamondNotEnoughDialog.hpp"
#include "game/mahjong/lobby/LobbyScene.h"
#include "payment/android/CallAndroidMethod.h"

DiamondNotEnoughDialog* DiamondNotEnoughDialog::create(){
    DiamondNotEnoughDialog* ret = new DiamondNotEnoughDialog();
    if(ret &&ret->init()){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool DiamondNotEnoughDialog::init(){
    if(!Layer::init()){
        return false;
    }
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
    content->setTexture("shop/charge/diamond_less_2.png");
    content->setPosition(640,365);
    addChild(content);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(DiamondNotEnoughDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(905, 535);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("shop/charge/charge_btn_1.png", "shop/charge/charge_btn_2.png",
                                         CC_CALLBACK_0(DiamondNotEnoughDialog::chargeDiamond, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 220);
    addChild(confirmMenu);
    
    return true;
}

void DiamondNotEnoughDialog::closeView(){
    removeFromParent();
}


void DiamondNotEnoughDialog::chargeDiamond(){
    CallAndroidMethod::getInstance()->requestEvent(UserData::getInstance()->getPoxiaoId(),"1");}