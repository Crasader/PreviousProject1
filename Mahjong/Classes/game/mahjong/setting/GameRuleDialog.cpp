//
//  GameRuleDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#include "game/mahjong/setting/GameRuleDialog.hpp"

bool GameRuleDialog::init(){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg,-1);
    
    auto  dialogBg = Sprite::create("friend/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(GameRuleDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 650);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 660);
    this->addChild(paodai);
    auto icon = Sprite::create("setting/rule_info.png");
    icon->setPosition(640, 680);
    addChild(icon);
    
    auto input_bg = Scale9Sprite::create("common/input_box_bg.png");
    input_bg->setContentSize(Size(700,560));
    input_bg->setPosition(640, 340);
    addChild(input_bg);

    return true;
}


void GameRuleDialog::closeView(){
    removeFromParent();
}