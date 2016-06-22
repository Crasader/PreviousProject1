//
//  GoldNotEnoughDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/12.
//
//

#include "game/mahjong/dialog/shop/GoldNotEnoughDialog.hpp"
#include "game/mahjong/lobby/LobbyScene.h"

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
    
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    auto dialogBg = Sprite::create("shop/gold_not_enough.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("shop/lobby_charge_title_icon.png");
    title->setPosition(640, 580);
    this->addChild(title);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(GoldNotEnoughDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(905, 535);
    this->addChild(closeMenu);
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setScale(0.8f);
    bg_2->setPosition(645,370);
    addChild(bg_2);
    
    auto textInfo = Sprite::create();
    textInfo->setPosition(640, 400);
    addChild(textInfo);
    
    auto goldIcon = Sprite::create("mjitem/gold_iocn.png");
    goldIcon->setPosition(570, 340);
    goldIcon->setScale(0.8f);
    addChild(goldIcon);
    
    auto cheng = Sprite::create("shop/cheng_hao.png");
    cheng->setPosition(610, 340);
    addChild(cheng);
    
    Label* alt = Label::create("0","arial",30);
    alt->setColor(Color3B::YELLOW);
    alt->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    alt->setPosition(630, 340);
    addChild(alt);
    
    auto confirm = MenuItemImage::create("shop/lobby_charge_btn_bg_1.png", "shop/lobby_charge_btn_bg_2.png",
                                         CC_CALLBACK_0(GoldNotEnoughDialog::chargeGold, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 220);
    addChild(confirmMenu);
    
    auto diamondNum = Label::create(cocos2d::String::createWithFormat("%d",0)->_string,"arial",30);
    diamondNum->setColor(Color3B::YELLOW);
    diamondNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    diamondNum->setPosition(605, 225);
    addChild(diamondNum);
    
    auto diamond = Sprite::create("mjitem/diamond.png");
    diamond->setScale(0.7f);
    diamond->setPosition(630, 225);
    addChild(diamond);
    
    auto chongZhi = Sprite::create("shop/lobby_charge_title.png");
    chongZhi->setPosition(680, 225);
    addChild(chongZhi);
    
    auto ico = Sprite::create();
    ico->setPosition(730, 215);
    addChild(ico);
    
    if (type == ROOM_1){
        textInfo->setTexture("shop/gold_less_1w.png");
        alt->setString("50000");
        diamondNum->setString("50");
        ico->setTexture("shop/5_yuan_icon.png");
    }else if(type == ROOM_2){
        textInfo->setTexture("shop/gold_less_15w.png");
        alt->setString("150000");
        ico->setTexture("shop/15_yuan_icon.png");
        diamondNum->setString("150");
    }else if(type == ROOM_3){
        textInfo->setTexture("shop/gold_less_210w.png");
        alt->setString("2580000");
        ico->setTexture("shop/258_yuan_icon.png");
         diamondNum->setString("2580");
    }
    
    return true;
}

void GoldNotEnoughDialog::closeView(){
    removeFromParent();
}


void GoldNotEnoughDialog::chargeGold(){
   //TODO
}