//
//  EnterRoomDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "game/mahjong/lobby/EnterRoomDialog.hpp"


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
    auto dialogBg = Sprite::create("shop/shop_bg_4.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("mjlobby/tuhao.png");
    title->setPosition(640, 500);
    this->addChild(title);
    
    auto thishiBg = Sprite::create("common/thishi_bg.png");
    thishiBg->setPosition(640, 375);
    addChild(thishiBg);
    
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
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       CC_CALLBACK_0(EnterRoomDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    closeMenu->setPosition(860, 490);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         CC_CALLBACK_0(EnterRoomDialog::closeView, this));
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 240);
    addChild(confirmMenu);
    return  true;
}


void EnterRoomDialog::closeView(){

}