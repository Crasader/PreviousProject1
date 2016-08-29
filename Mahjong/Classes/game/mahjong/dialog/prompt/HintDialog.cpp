//
//  HintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "game/mahjong/dialog/prompt/HintDialog.hpp"


HintDialog* HintDialog::create(std::string msg,const ccMenuCallback& callback){
    HintDialog* ret = new HintDialog();
    if(ret &&ret->init(msg,callback)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool HintDialog::init(std::string msg,const ccMenuCallback& callback){
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
    
    Label* text = Label::create(msg, "Arial", 30);
    text->setColor(Color3B(38,158,228));
    text->setPosition(640, 360);
    addChild(text);
    
    
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       callback);
    if(callback == NULL){
        close->setCallback([=](Ref* ref){
            removeFromParent();
        });
    }
    auto closeMenu = Menu::create(close, NULL);
    
    
    closeMenu->setPosition(860, 490);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         callback);
    if(callback == NULL){
        confirm->setCallback([=](Ref* ref){
            removeFromParent();
        });
    }
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 240);
    addChild(confirmMenu);
    
    return true;
}