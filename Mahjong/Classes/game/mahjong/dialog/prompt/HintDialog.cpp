//
//  HintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "game/mahjong/dialog/prompt/HintDialog.hpp"


HintDialog* HintDialog::create(std::string msg,const ccMenuCallback& callback1,const ccMenuCallback& callback2){
    HintDialog* ret = new HintDialog();
    if(ret &&ret->init(msg,callback1,callback2)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool HintDialog::init(std::string msg,const ccMenuCallback& callback1,const ccMenuCallback& callback2){
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
    
    Label* text = Label::createWithSystemFont(msg, "Arial", 30);
    text->setWidth(300);
    text->setAnchorPoint(Point::ANCHOR_MIDDLE);
    text->setColor(Color3B(38,158,228));
    text->setPosition(640, 360);
    addChild(text);
    
    
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       callback2);
    if(callback2 == NULL){
        close->setCallback([=](Ref* ref){
            removeFromParent();
        });
    }
    auto closeMenu = Menu::create(close, NULL);
    
    
    closeMenu->setPosition(860, 490);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         callback1);
    if(callback1 == NULL){
        confirm->setCallback([=](Ref* ref){
            removeFromParent();
        });
    }
    auto confirmMenu = Menu::create(confirm, NULL);
    confirmMenu->setPosition(640, 240);
    addChild(confirmMenu);
    
    return true;
}
