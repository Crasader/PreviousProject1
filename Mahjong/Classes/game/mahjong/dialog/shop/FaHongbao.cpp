//
//  FaHongbao.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#include "FaHongbao.hpp"

bool FaHongbao::init(){
    if(!Layer::init()){
    
        return false;
    }

    showFaHongbao();
    return true;

}

void FaHongbao::showFaHongbao(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(FaHongbao::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto title = Sprite::create("shop/haoyoufahongbao.png");
    title->setPosition(640,610);
    addChild(title);

    auto box = Scale9Sprite::create("shop/red_box.png");
    box->setContentSize(Size(270,310));
    box->setPosition(480,350);
    addChild(box);
    
    auto piaodai = Sprite::create("shop/lvse_piaodai.png");
    piaodai->setPosition(480,473);
    addChild(piaodai);
    
    auto text = Sprite::create("shop/wxhy_text.png");
    text->setPosition(480,473);
    addChild(text);
    
    auto icon = Sprite::create("shop/wx_icon.png");
    icon->setPosition(480,348);
    addChild(icon);
    
    auto btnImage = MenuItemImage::create("shop/fahongbao_btn_1.png","shop/fahongbao_btn_2.png");
    auto menu1= Menu::create(btnImage,NULL);
    menu1->setPosition(480,220);
    addChild(menu1);
    //box2
    
    auto box2 = Scale9Sprite::create("shop/red_box.png");
    box2->setContentSize(Size(270,310));
    box2->setPosition(820,350);
    addChild(box2);
    
    auto piaodai2 = Sprite::create("shop/lvse_piaodai.png");
    piaodai2->setPosition(820,473);
    addChild(piaodai2);
    
    auto text2 = Sprite::create("shop/wxhy_text.png");
    text2->setPosition(820,473);
    addChild(text2);
    
    auto icon2 = Sprite::create("shop/wx_icon.png");
    icon2->setPosition(820,348);
    addChild(icon2);
    
    auto btnImage2 = MenuItemImage::create("shop/fahongbao_btn_1.png","shop/fahongbao_btn_2.png");
    auto menu2= Menu::create(btnImage2,NULL);
    menu2->setPosition(820,220);
    addChild(menu2);
    
}



void  FaHongbao::closeView(){
    removeFromParent();
}
