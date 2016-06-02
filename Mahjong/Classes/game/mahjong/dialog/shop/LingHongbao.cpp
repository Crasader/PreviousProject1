//
//  LingHongbao.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/21.
//
//

#include "game/mahjong/dialog/shop/LingHongbao.hpp"

bool LingHongbao::init(){
    if(!Layer::init()){
        
        return false;
    }
    
    showLingHongbao();
    return true;
    
}

void LingHongbao::showLingHongbao(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu0 = Menu::create(item1, NULL);
    this->addChild(menu0);
    
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(LingHongbao::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    
    auto title = Sprite::create("shop/linhongbao.png");
    title->setPosition(640,610);
    addChild(title);
    
    auto text = Sprite::create("shop/shurukoulin.png");
    text->setPosition(640,480);
    addChild(text);
    
    EditBox* _editPwd  = EditBox::create(Size(445, 81), Scale9Sprite::create());
    _editPwd->setPosition(Point(720, 395));
    _editPwd->setFont("American Typewriter", 24);
    _editPwd->setInputFlag(EditBox::InputFlag::PASSWORD);
    _editPwd->setInputMode(EditBox::InputMode::SINGLE_LINE);
    _editPwd->setTag(1);
    addChild(_editPwd);
    
    
    auto btnImage = MenuItemImage::create("shop/fahongbao_btn_1.png","shop/fahongbao_btn_2.png");
    auto menu1= Menu::create(btnImage,NULL);
    menu1->setPosition(640,220);
    addChild(menu1);

    
}



void  LingHongbao::closeView(){
    removeFromParent();
}
