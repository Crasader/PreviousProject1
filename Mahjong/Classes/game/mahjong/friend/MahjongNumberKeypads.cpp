//
//  NumberKeypads.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/10/17.
//
//

#include "game/mahjong/friend/MahjongNumberKeypads.hpp"
#include "server/NetworkManage.h"


bool MahjongNumberKeypads::init(){
    
    if(!Layer::init()){
        return false;
    }
    enterRoomNumber="";
    
    auto numbg = Sprite::create("friend/numberkeypads_bg.png");
    numbg->setPosition(640,350);
    addChild(numbg);
    
    numberShow = Label::createWithSystemFont("", "arial", 50);
    numberShow->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    numberShow->setPosition(820,480);
    addChild(numberShow);
    
    auto numberMenu = Menu::create();
    numberMenu->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(numberMenu);
    for(int i=0;i<12;i++){
        auto numebrBtn = MenuItemImage::create("friend/num_btn_1.png", "friend/num_btn_2.png", CC_CALLBACK_1(MahjongNumberKeypads::clickNumber, this));
        numebrBtn->setTag(i);
        numberMenu->addChild(numebrBtn);
        numebrBtn->setPosition(-120+(i%3)*125,35-(i/3)*75);
        if(i<10){
            auto numberLabel = Label::createWithSystemFont(StringUtils::format("%d",(i+1)%10), "arial", 30);
            numberLabel->setPosition(55,40);
            numebrBtn->addChild(numberLabel);
        }else if (i==10){
            auto del = Sprite::create("friend/num_deleta.png");
            del->setPosition(55,40);
            numebrBtn->addChild(del);
        }else{
            auto ok = Sprite::create("friend/confirm_iamge.png");
            ok->setPosition(55,40);
            numebrBtn->addChild(ok);
        }
        
    }
    
    return true;
}

void MahjongNumberKeypads::clickNumber(Ref* ref){
    MenuItemImage* temp = (MenuItemImage*) ref;
    int index = temp->getTag();
    if(index == 11){
        NetworkManage::getInstance()->sendMsg(CommandManage::getInstance()->getEnterRoomByIdCommand(numberShow->getString()));
        removeFromParent();
    }else if(index == 10){
        //delete
        enterRoomNumber = enterRoomNumber.substr(0,enterRoomNumber.size()-1);
        numberShow->setString(enterRoomNumber);
    }else{
        enterRoomNumber = enterRoomNumber+ StringUtils::format("%d",(index+1)%10);
        numberShow->setString(enterRoomNumber);
    }
}