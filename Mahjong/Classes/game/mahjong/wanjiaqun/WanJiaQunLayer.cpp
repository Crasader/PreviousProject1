//
//  WanJiaQunLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/9.
//
//

#include "game/mahjong/wanjiaqun/WanJiaQunLayer.hpp"

bool WanJiaQunLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(WanJiaQunLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto titleIcon = Sprite::create("wanjiaqun/wj_title.png");
    titleIcon->setPosition(640, 590);
    addChild(titleIcon);

    return true;
}


void WanJiaQunLayer::closeView(){
    removeFromParent();
}