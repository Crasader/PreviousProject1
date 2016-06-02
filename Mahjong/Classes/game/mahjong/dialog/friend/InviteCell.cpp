//
//  InviteCell.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/4/19.
//
//

#include "game/mahjong/dialog/friend/InviteCell.hpp"


InviteCell* InviteCell::create(std::string filepath,std::string name){
    InviteCell* cell = new InviteCell();
    if(cell&& cell->init(filepath, name)){
        cell->autorelease();
        return cell;
    }else{
        CC_SAFE_DELETE(cell);
        return nullptr;
    }
}



bool InviteCell::init(std::string filepath,std::string name){
    if(!Sprite::init()){
        return false;
    }
    auto head = Sprite::create("gameview/head_image_1.png");
    addChild(head);
    Label* nickName = Label::create(name,"arial",20);
    addChild(nickName);
    return true;
}