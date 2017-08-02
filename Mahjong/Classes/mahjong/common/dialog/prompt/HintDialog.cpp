//
//  HintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "mahjong/common/dialog/prompt/HintDialog.hpp"


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
    auto bg0 = LayerColor::create(Color4B(0, 0, 0, 100), 1280, 720);
    addChild(bg0);
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
	Menu* menu1 = Menu::create(item1, nullptr);
    this->addChild(menu1);
    
    auto dialogBg = Sprite::create("common/dialog_bg_small.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    
    Label* text = Label::createWithSystemFont(msg, "Arial", 30);
    text->setWidth(300);
    text->setAnchorPoint(Point::ANCHOR_MIDDLE);
    text->setColor(Color3B(124,37,7));
    text->setPosition(640, 380);
    addChild(text);
    
    
    
    auto close = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png",
                                       callback2);
	if (callback2 == nullptr){
        close->setCallback([=](Ref* ref){
            removeFromParent();
        });
    }
	auto closeMenu = Menu::create(close, nullptr);
    
    
    closeMenu->setPosition(890, 520);
    this->addChild(closeMenu);
    
    auto confirm = MenuItemImage::create("common/confirm_btn_1.png", "common/confirm_btn_2.png",
                                         callback1);
	if (callback1 == nullptr){
        confirm->setCallback([=](Ref* ref){
            removeFromParent();
        });
    }
	auto confirmMenu = Menu::create(confirm, nullptr);
    confirmMenu->setPosition(640, 255);
    addChild(confirmMenu);
    
    return true;
}
