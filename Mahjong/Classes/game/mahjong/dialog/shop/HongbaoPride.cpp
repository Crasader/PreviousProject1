//
//  HongbaoPride.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#include "game/mahjong/dialog/shop/HongbaoPride.hpp"

bool HongbaoPride::init(){
    if(!Layer::init()){
        
        return false;
    }
    
    showHongbaoPride();
    return true;
    
}

void HongbaoPride::showHongbaoPride(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(HongbaoPride::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto title = Sprite::create("shop/haoyoufahongbao.png");
    title->setPosition(640,610);
    addChild(title);
    
    
    auto btnImage = MenuItemImage::create("shop/fahongbao_btn_1.png","shop/fahongbao_btn_2.png");
    auto menu1= Menu::create(btnImage,NULL);
    menu1->setPosition(480,220);
    addChild(menu1);
    
}



void  HongbaoPride::closeView(){
    removeFromParent();
}
