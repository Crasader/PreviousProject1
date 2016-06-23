//
//  LequanExchangeRecord.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/14.
//
//

#include "LequanExchangeRecord.hpp"

bool LequanExchangeRecord::init(){
    if(!Layer::init()){
        return false;
    }
    showLequanExchangeRecord();
    return true;
}

void LequanExchangeRecord::showLequanExchangeRecord(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto all_bg = Sprite::create("common/all_bg.jpg");
    all_bg->setPosition(640, 360);
    addChild(all_bg);
    
    auto dialog_bg = Sprite::create("shop/shop_bg.png");
    dialog_bg->setPosition(640,360);
    addChild(dialog_bg);
    
    auto title = Sprite::create("shop/title_info.png");
    title->setPosition(654,660);
    addChild(title);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(LequanExchangeRecord::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(1050, 610);
    addChild(closeMenu);
//    duihuanjilu_box.png
}

void LequanExchangeRecord::closeView(){
    removeFromParent();
}
