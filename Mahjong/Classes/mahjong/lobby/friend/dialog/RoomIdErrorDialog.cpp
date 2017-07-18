
//
//  RoomIdErrorDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/26.
//
//
#include "mahjong/lobby/friend/dialog/RoomIdErrorDialog.hpp"


bool RoomIdErrorDialog::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto dialog_bg = Sprite::create("common/dialog_bg_small.png");
    dialog_bg->setPosition(640,350);
    addChild(dialog_bg);
    
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(RoomIdErrorDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(890, 505);
    addChild(closeMenu);
    
    
    auto bg_2 = Sprite::create("shop/first_charge_bg_2.png");
    bg_2->setPosition(645,375);
    addChild(bg_2);
    
    
    auto chargeImage = Sprite::create("friend/wu_fang_hao.png");
    chargeImage->setPosition(640,380);
    addChild(chargeImage);
    
    auto image = MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_2.png",
                                       CC_CALLBACK_0(RoomIdErrorDialog::closeView, this));
    Menu* menu = Menu::create(image,NULL);
    menu->setPosition(640,240);
    addChild(menu);
    
    return true;
}

void RoomIdErrorDialog::closeView(){
    removeFromParent();
}
