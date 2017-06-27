//
//  EnterRoomDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "mahjong/lobby/dialog/EnterRoomDialog.hpp"
#include "mahjong/lobby/shop/gold/ChargeGold.hpp"
#include "server/NetworkManage.h"



EnterRoomDialog* EnterRoomDialog::create(EnterRoomDialogType msg){
    EnterRoomDialog* ret = new EnterRoomDialog();
    if(ret &&ret->init(msg)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}
bool EnterRoomDialog::init(EnterRoomDialogType msg){
    if(!Layer::init()){
        return false;
    }
    setDialogType(msg);
    auto dialogBg = Sprite::create("shop/shop_bg_4.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("mjlobby/tuhao.png");
    title->setPosition(640, 580);
    this->addChild(title);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(EnterRoomDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(875, 525);
    this->addChild(closeMenu);
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setScale(0.8f);
    bg_2->setPosition(645,370);
    addChild(bg_2);
    
    auto levelMid = Sprite::create("mjlobby/tuhao_text.png");
    levelMid->setPosition(640, 390);
    addChild(levelMid);
    auto levelText = Sprite::create("mjlobby/fangjian_di.png");
    levelText->setPosition(670, 350);
    addChild(levelText);
    auto nume = Label::createWithSystemFont("5000", "arial", 30);
    nume->setColor(Color3B(241,208,90));
    nume->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    nume->setPosition(570,350);
    addChild(nume);
    
    if (msg == EnterRoomDialogType::goldMoreLeve1){
        nume->setString("5000");
    }else if(msg == EnterRoomDialogType::goldMoreLeve2){
        nume->setString("10000");
    }
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         CC_CALLBACK_0(EnterRoomDialog::confirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 220);
    addChild(confirmMenu);
    return  true;
}


void EnterRoomDialog::closeView(){
    removeFromParent();
}


void EnterRoomDialog::confirm(){
    if(getDialogType() == EnterRoomDialogType::goldNotEnough){
        ChargeGold* gold = ChargeGold::create();
        addChild(gold);
    }
    removeFromParent();
}
