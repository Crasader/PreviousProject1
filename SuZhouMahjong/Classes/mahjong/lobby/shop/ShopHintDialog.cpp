//
//  ShopHintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/31.
//
//

#include "mahjong/lobby/shop/ShopHintDialog.hpp"
#include "server/MsgConfig.h"

bool ShopHintDialog::init(){
    if(!Layer::init()){
        return false;
    }
    showDialog();
    return true;
}
void ShopHintDialog::showDialog(){
    
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 50), 1280, 720);
    addChild(bg0);
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto tishiBg = Sprite::create("common/dialog_bg_small.png");
    tishiBg->setPosition(640,360);
    tishiBg->setScale(0.7f);
    addChild(tishiBg);

    auto continueImage =  MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_1.png",CC_CALLBACK_0(ShopHintDialog::confirm, this));
    continueImage->setScale(0.7f);
    auto menu = Menu::create(continueImage,NULL);
    menu->setPosition(640,295);
    addChild(menu);
}

void ShopHintDialog::showText(std::string msg){
    auto label = Label::createWithSystemFont(msg,"arial",30);
    label->setPosition(640,380);
    label->setColor(Color3B(137,7,0));
    label->setTag(666);
    addChild(label);
}

void ShopHintDialog::showImage(std::string image){
    auto sprite = Sprite::create(image);
    sprite->setPosition(640,380);
    sprite->setTag(667);
    addChild(sprite);
}

void ShopHintDialog::confirm(){
    removeFromParent();
}
