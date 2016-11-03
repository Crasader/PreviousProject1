//
//  HintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "game/mahjong/friend/dialog/DissovleRoomDialog.hpp"


bool DissovleRoomDialog::init(){
    if(!Layer::init()){
        return false;
    }

    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto dialogBg = Sprite::create("common/dialog_bg_small.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto title = Sprite::create("common/tishi_icon.png");
    title->setPosition(640, 500);
    this->addChild(title);
    
    auto thishiBg = Sprite::create("common/thishi_bg.png");
    thishiBg->setPosition(640, 375);
    addChild(thishiBg);
    
    Label* text = Label::createWithSystemFont("", "Arial", 30);
    text->setColor(Color3B(38,158,228));
    text->setPosition(640, 360);
    addChild(text);
    
    
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",CC_CALLBACK_0(DissovleRoomDialog::closeView, this));
    auto closeMenu = Menu::create(close, NULL);
    
    
    closeMenu->setPosition(860, 490);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("common/agree_btn_1.png", "common/agree_btn_2.png",
                                         CC_CALLBACK_0(DissovleRoomDialog::agree, this));
    auto disagree = MenuItemImage::create("common/dis_agree_btn_1.png", "common/dis_agree_btn_2.png",
                                         CC_CALLBACK_0(DissovleRoomDialog::agree, this));
    auto confirmMenu = Menu::create(confirm,disagree, NULL);
    confirmMenu->alignItemsHorizontallyWithPadding(5);
    confirmMenu->setPosition(640, 240);
    addChild(confirmMenu);
    
    return true;
}

void DissovleRoomDialog::agree(){

}

void DissovleRoomDialog::disAgree(){


}

void DissovleRoomDialog::closeView(){

}