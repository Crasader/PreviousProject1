//
//  ShopHintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/5/31.
//
//

#include "game/mahjong/shop/ShopHintDialog.hpp"

bool ShopHintDialog::init(){
    if(!Layer::init()){
        return false;
    }
    showDialog();
    return true;
}
void ShopHintDialog::showDialog(){
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg);
    
    auto tishiBg = Sprite::create("shop/shop_bg_4.png");
    tishiBg->setPosition(640,360);
    tishiBg->setScale(0.7f);
    addChild(tishiBg);
    
    auto title = Sprite::create("common/tishi_icon.png");
    title->setPosition(640,480);
    addChild(title);
    

    
    auto continueImage =  MenuItemImage::create("common/confirm_btn_1.png","common/confirm_btn_1.png",CC_CALLBACK_0(ShopHintDialog::confirm, this));
    continueImage->setScale(0.7f);
    auto menu = Menu::create(continueImage,NULL);
    menu->setPosition(640,260);
    addChild(menu);
}

void ShopHintDialog::showText(std::string msg){
    auto label = Label::create(msg,"arial",30);
    label->setPosition(640,380);
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
