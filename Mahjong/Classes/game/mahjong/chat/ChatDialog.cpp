//
//  ChatDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/8/11.
//
//

#include "game/mahjong/chat/ChatDialog.hpp"

bool ChatDialog::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto  dialogBg = Sprite::create("friend/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(ChatDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 650);
    addChild(closeMenu);
    
    auto inputText = Scale9Sprite::create("chat/chat_bg.png");
    inputText->setContentSize(Size(720,565));
    inputText->setPosition(640,335);
    addChild(inputText);

    return true;
}

void ChatDialog::closeView(){
    removeFromParent();
}

