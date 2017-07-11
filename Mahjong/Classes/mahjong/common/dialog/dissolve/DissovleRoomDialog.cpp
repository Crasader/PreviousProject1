//
//  DissovleRoomDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/10.
//
//

#include "mahjong/common/dialog/dissolve/DissovleRoomDialog.hpp"
#include "mahjong/common/state/GameData.h"
#include "userdata/UserData.h"

bool DissovleRoomDialog::init(){

    if(!Layer::init()){
        return false;
    }
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
    
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    
    auto titleIcon = Sprite::create("dissolve/dissovle_room.png");
    titleIcon->setPosition(640, 575);
    addChild(titleIcon);
    
    //显示谁主动提出解散房间
    auto wanjia = Label::createWithSystemFont(StringUtils::format("玩家%s要求解散房间,是否同意",GAMEDATA::getInstance()->getDissolveName().c_str()), "arial", 30);
    wanjia->setColor(Color3B(70,40,20));
    wanjia->setPosition(327,525);
    wanjia->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    addChild(wanjia);
    
    auto time = Label::createWithSystemFont(StringUtils::format("%d后自动同意",residueTime), "arial", 30);
    time->setColor(Color3B(70,40,20));
    time->setPosition(640,275);
    addChild(time);
    
    for(int i=0;i<GAMEDATA::getInstance()->getPlayersInfo().size();i++){
        DissolveItem* item = DissolveItem::create(GAMEDATA::getInstance()->getPlayersInfo().at(i)->getNickname());
        item->setPosition(475+330*(i%2),440-(i/2)*100);
        addChild(item);
        items.push_back(item);
    }
    
    auto img1 = MenuItemImage::create("dissolve/agree_1.png", "dissolve/agree_2.png", CC_CALLBACK_0(DissovleRoomDialog::doAgree,this));
    auto img2 = MenuItemImage::create("dissolve/dis_agree_1.png", "dissolve/dis_agree_2.png", CC_CALLBACK_0(DissovleRoomDialog::doNotAgree, this));
    auto menu = Menu::create(img1,img2,NULL);
    menu->alignItemsHorizontallyWithPadding(50);
    menu->setPosition(640,200);
    addChild(menu);
    return true;
}

void DissovleRoomDialog::doAgree(){
    for(int i=0; i<items.size();i++){
        if(items.at(i)->getNickName() == UserData::getInstance()->getNickName()){
            items.at(i)->updateState(1);
        }
    }
    //TODO 发送协议
}


void DissovleRoomDialog::doNotAgree(){
    for(int i=0; i<items.size();i++){
        if(items.at(i)->getNickName() == UserData::getInstance()->getNickName()){
            items.at(i)->updateState(2);
        }
    }
    //TODO 发送协议
}


