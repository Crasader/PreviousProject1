//
//  InviteCodeLayer.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/5/4.
//
//

#include "mahjong/lobby/invitecode/InviteCodeLayer.hpp"

bool InviteCodeLayer::init(){
    if(!Layer::init()){
        return false;
    }
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto tishiBg = Sprite::create("shop/shop_bg_4.png");
    tishiBg->setPosition(640,360);
    addChild(tishiBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(InviteCodeLayer::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(880, 540);
    addChild(closeMenu);
    
    auto title = Sprite::create("shop/invite_code_title.png");
    title->setPosition(640,530);
    addChild(title);
    
    auto codeBg = Sprite::create("shop/invite_code_bg.png");
    codeBg->setPosition(640,380);
    addChild(codeBg);
    
    auto inputBox = Sprite::create("shop/invite_code_input.png");
    inputBox->setPosition(640,390);
    addChild(inputBox);
    
    auto codeText = Sprite::create("shop/invite_code_text.png");
    codeText->setPosition(640,315);
    addChild(codeText);
    
    auto money = Label::createWithSystemFont("99", "arial", 30);
    money->setAnchorPoint(Point::ANCHOR_MIDDLE);
    money->setPosition(660,315);
    addChild(money);
    
    auto continueImage =  MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_1.png",CC_CALLBACK_0(InviteCodeLayer::confirm, this));
    auto menu = Menu::create(continueImage,NULL);
    menu->setPosition(640,220);
    addChild(menu);

    return true;
}

void InviteCodeLayer::confirm(){

}

void InviteCodeLayer::closeView(){
    removeFromParent();
}
