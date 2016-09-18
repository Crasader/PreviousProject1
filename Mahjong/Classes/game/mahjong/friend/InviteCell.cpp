//
//  InviteCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "game/mahjong/friend/InviteCell.hpp"


InviteCell* InviteCell::create(HeadImage* headImgae,std::string name){
    InviteCell* cell = new InviteCell();
    if(cell&& cell->init(headImgae, name)){
        cell->autorelease();
        return cell;
    }else{
        CC_SAFE_DELETE(cell);
        return nullptr;
    }
}



bool InviteCell::init(HeadImage* headImgae,std::string name){
    if(!Sprite::init()){
        return false;
    }
    addChild(headImgae);
    Label* nickName = Label::create(name,"arial",20);
    addChild(nickName);
    return true;
}