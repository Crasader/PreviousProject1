//
//  DissovleRoomDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 2017/7/10.
//
//

#include "mahjong/gameview/dissolve/DissovleRoomDialog.hpp"


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
    
    auto dissovlebg1 = Sprite::create("dissolve/dissovle_bg.png");
    dissovlebg1->setPosition(475,440);
    addChild(dissovlebg1);
    auto dissovlebg2 = Sprite::create("dissolve/dissovle_bg.png");
    dissovlebg2->setPosition(475,340);
    addChild(dissovlebg2);
    auto dissovlebg3 = Sprite::create("dissolve/dissovle_bg.png");
    dissovlebg3->setPosition(805,440);
    addChild(dissovlebg3);
    auto dissovlebg4 = Sprite::create("dissolve/dissovle_bg.png");
    dissovlebg4->setPosition(805,340);
    addChild(dissovlebg4);

    return true;
}


