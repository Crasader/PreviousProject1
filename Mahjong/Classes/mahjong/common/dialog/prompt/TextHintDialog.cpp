//
//  HintDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/6/7.
//
//

#include "mahjong/common/dialog/prompt/TextHintDialog.hpp"


TextHintDialog* TextHintDialog::create(std::string msg){
    TextHintDialog* ret = new TextHintDialog();
    if(ret &&ret->init(msg)){
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool TextHintDialog::init(std::string msg){
    if(!Layer::init()){
        return false;
    }

    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto dialogBg = Sprite::create("common/dialog_bg_small.png");
    dialogBg->setPosition(640, 360);
    addChild(dialogBg);
    
    auto title = Sprite::create("common/tishi_icon.png");
    title->setPosition(640, 500);
    addChild(title);
    
    auto thishiBg = Sprite::create("common/thishi_bg.png");
    thishiBg->setPosition(640, 375);
    addChild(thishiBg);
    
    Label* text = Label::createWithSystemFont(msg, "Arial", 30);
    text->setColor(Color3B(38,158,228));
    text->setPosition(640, 360);
    addChild(text);
    schedule([=](float dt){
        removeFromParent();
    }, 0, 0, 2.5f,"sug");
    return true;
}
