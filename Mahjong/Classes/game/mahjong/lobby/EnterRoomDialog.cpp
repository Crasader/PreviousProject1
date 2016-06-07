//
//  EnterRoomDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "game/mahjong/lobby/EnterRoomDialog.hpp"
#include "game/mahjong/dialog/shop/ChargeDiamond.hpp"
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
    
    if(msg == EnterRoomDialogType::goldNotEnough){
        Label* text = Label::create("金币不足请充值", "Arial", 30);
        text->setColor(Color3B(38,158,228));
        text->setPosition(640, 360);
        addChild(text);
    }else if (msg == EnterRoomDialogType::goldMoreLeve1){
        auto levelMid = Sprite::create("mjlobby/gold_enter_mid.png");
        levelMid->setPosition(640, 360);
        addChild(levelMid);
    }else if(msg == EnterRoomDialogType::goldMoreLeve2){
        auto levelHigh = Sprite::create("mjlobby/gold_enter_high.png");
        levelHigh->setPosition(640, 360);
        addChild(levelHigh);
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
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getDiamondChangeListCommand());
        ChargeDiamond* charge = ChargeDiamond::create();
        getParent()->addChild(charge,3);
    }
    removeFromParent();
}