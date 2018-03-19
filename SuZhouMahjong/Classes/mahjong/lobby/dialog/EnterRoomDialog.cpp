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
    auto dialogBg = Sprite::create("shop/first_chage_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("shop/charge/tuhao_title.png");
    title->setPosition(640, 590);
    this->addChild(title);
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(EnterRoomDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(990, 595);
    this->addChild(closeMenu);
    
    auto levelMid = Sprite::create("shop/charge/tu_hao_text.png");
    levelMid->setPosition(640, 390);
    addChild(levelMid);
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         CC_CALLBACK_0(EnterRoomDialog::confirm, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 160);
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
