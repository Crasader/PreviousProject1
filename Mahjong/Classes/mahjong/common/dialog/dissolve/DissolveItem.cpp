//
//  DissolveItem.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/11.
//
//

#include "mahjong/common/dialog/dissolve/DissolveItem.hpp"


DissolveItem* DissolveItem::create(std::string name){
    DissolveItem* ret = new DissolveItem();
    if(ret &&ret->init(name)){
        ret->autorelease();
        return ret;
    }else{
        CC_SAFE_DELETE(ret);
        return NULL;
    }
}

bool DissolveItem::init(std::string name){
    if(!Sprite::init()){
        return false;
    }
    setNickName(name);
    auto dissovlebg1 = Sprite::create("dissolve/dissovle_bg.png");
    dissovlebg1->setPosition(0,0);
    addChild(dissovlebg1);
    
    auto nickName = Label::createWithSystemFont(name, "arial", 30);
    nickName->setColor(Color3B(70,40,20));
    nickName->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    nickName->setPosition(-135,0);
    addChild(nickName);
    
    state = Sprite::create("dissolve/wen_hao.png");
    state->setPosition(135,0);
    addChild(state);
    
    return true;
}

void DissolveItem::updateState(int sta){
    if(sta == 1){
        state->setTexture("dissolve/agree_img.png");
    }else if(sta == 2){
        state->setTexture("dissolve/dis_agree_img.png");
    }else{
        state->setTexture("dissolve/wen_hao.png");
    }
}
