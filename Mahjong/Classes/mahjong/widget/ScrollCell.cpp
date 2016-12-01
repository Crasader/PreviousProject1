//
//  ScrollCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 2016/11/10.
//
//

#include "mahjong/widget/ScrollCell.hpp"


ScrollCell* ScrollCell::create(std::string msg){
    
    ScrollCell* ret = new ScrollCell();
    if(ret &&ret->init(msg)){
        
        ret->autorelease();
        return ret;
    }else{
        
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool ScrollCell::init(std::string msg){
    if(!Sprite::init()){
        return false;
    }
    setTexture("gameview/sroll_bg.png");
    _mLable = Label::createWithSystemFont(msg, "Arial", 24);
    _mLable->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _mLable->setColor(Color3B::YELLOW);
    addChild(_mLable);
    _mLable->setPosition(getContentSize().width/2,getContentSize().height/2);
    if(msg== ""||msg.size()==0){
        setVisible(false);
    }else{
        setVisible(true);
    }
    return true;
}

void ScrollCell::setString(std::string msg){
    _mLable->setString(msg);
    _mLable->setPosition(getContentSize().width/2,getContentSize().height/2);
    if(msg== ""||msg.size()==0){
        setVisible(false);
    }else{
        setVisible(true);
    }
}
