//
//  ToastCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/30.
//
//

#include "game/mahjong/dialog/toast/ToastCell.hpp"


ToastCell* ToastCell::create(std::string msg){
    
    ToastCell* ret = new ToastCell();
    
    if(ret &&ret->init(msg)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ToastCell::init(std::string msg){
    if(!Sprite::init()){
        return false;
    }
    auto bg = ui::Scale9Sprite::create("common/toast_bg.png");
    bg->setPosition(0,0);
    addChild(bg);
    
    auto showMsg = Label::createWithSystemFont(msg, "Arial", 24);
    showMsg->setAnchorPoint(Point::ANCHOR_MIDDLE);
    showMsg->setPosition(0,0);
    addChild(showMsg);
    
    return true;
}
